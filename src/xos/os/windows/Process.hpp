///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2012 $organization$
///
/// This software is provided by the author and contributors ``as is'' 
/// and any express or implied warranties, including, but not limited to, 
/// the implied warranties of merchantability and fitness for a particular 
/// purpose are disclaimed. In no event shall the author or contributors 
/// be liable for any direct, indirect, incidental, special, exemplary, 
/// or consequential damages (including, but not limited to, procurement 
/// of substitute goods or services; loss of use, data, or profits; or 
/// business interruption) however caused and on any theory of liability, 
/// whether in contract, strict liability, or tort (including negligence 
/// or otherwise) arising in any way out of the use of this software, 
/// even if advised of the possibility of such damage.
///
///   File: Process.hpp
///
/// Author: $author$
///   Date: 10/6/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_OS_WINDOWS_PROCESS_HPP
#define _XOS_OS_WINDOWS_PROCESS_HPP

#include "xos/os/windows/handle/Joined.hpp"
#include "xos/os/Process.hpp"
#include "xos/os/Logger.hpp"
#include "xos/base/Created.hpp"
#include "xos/base/Wrapped.hpp"
#include "xos/base/String.hpp"
#include "xos/base/Array.hpp"
#include <process.h>

namespace xos {
namespace windows {

typedef xos::Process ProcessImplement;
typedef ProcessImplement::Status ProcessStatus;
typedef Attached<HANDLE, int, 0, ExportBase, ProcessImplement> ProcessAttached;
typedef handle::Joined<HANDLE, ProcessStatus, ProcessAttached, ProcessImplement> ProcessJoined;
typedef Created<HANDLE, int, 0, ProcessJoined, ProcessImplement> ProcessExtend;

class _EXPORT_CLASS Process: virtual public ProcessImplement, public ProcessExtend {
public:
    typedef ProcessImplement Implements;
    typedef ProcessExtend Extends;

    Process(const char* path, char** argv, char** env, bool isDetached = false)
    : m_thread(0) {
        if (!(Create(path, argv, env, isDetached))) {
            XOS_LOG_ERROR("failed on Create()");
            throw(Error(Error::Failed));
        }
    }
    Process(const char* path, char** argv, bool isDetached = false)
    : m_thread(0) {
        if (!(Create(path, argv, isDetached))) {
            XOS_LOG_ERROR("failed on Create()");
            throw(Error(Error::Failed));
        }
    }
    Process(HANDLE hProcess, HANDLE hThread, bool isCreated = false)
    : Extends(hProcess, isCreated), m_thread(hThread) {}
    virtual ~Process() {
        if (!(Destroyed())) {
            XOS_LOG_ERROR("failed on Destroyed()");
        }
    }

    virtual bool Create(const char* path, char** argv, char** env, bool isDetached = false) {
        StringT<tchar_t> ApplicationName(path);
        CommandLine commandLine(argv);
        LPCTSTR lpApplicationName = ApplicationName.c_str();
        LPTSTR lpCommandLine = commandLine.str();
        LPSECURITY_ATTRIBUTES lpProcessAttributes = 0;
        LPSECURITY_ATTRIBUTES lpThreadAttributes = 0;
        BOOL bInheritHandles = FALSE;
        DWORD dwCreationFlags = (isDetached)?(DETACHED_PROCESS):(0);
        LPVOID lpEnvironment = env;
        LPTSTR lpCurrentDirectory = 0;
        StartupInfo startup(0);
        LPSTARTUPINFO lpStartupInfo = &startup.wrapped();
        ProcessInformation process(0);
        LPPROCESS_INFORMATION lpProcessInformation = &process.wrapped();
        bool isCreated = false;
        HANDLE hProcess = 0;
        HANDLE hThread = 0;

        if (!(Destroyed())) {
            return false; }

        XOS_LOG_TRACE("CreateProcess()...");
        if ((isCreated = (FALSE != (CreateProcess
            (lpApplicationName, lpCommandLine, 
             lpProcessAttributes,lpThreadAttributes, bInheritHandles, dwCreationFlags,
             lpEnvironment, lpCurrentDirectory, lpStartupInfo, lpProcessInformation))))) {
            hProcess = process.wrapped().hProcess;
            hThread = process.wrapped().hThread;
            Attach(hProcess, hThread, isCreated);
            XOS_LOG_TRACE("...CreateProcess()");
            return true;
        } else {
            XOS_LOG_ERROR("failed " << GetLastError() << " on CreateProcess(\"" << path << "\", ...)");
        }
        return false; }
    virtual bool Create(const char* path, char** argv, bool isDetached = false) {
        return Create(path, argv, 0, isDetached); }
    virtual bool Destroy() {
        if ((Join())) {
            HANDLE hProcess = 0;
            HANDLE hThread = 0;
            if ((hProcess = Detach(hThread))) {
                if ((hThread)) {
                    bool isTrue = false;
                    XOS_LOG_TRACE("CloseHandle()...");
                    if (!(isTrue = (FALSE != CloseHandle(hThread)))) {
                        XOS_LOG_ERROR("failed " << GetLastError() << " on CloseHandle()");
                    } else {
                        XOS_LOG_TRACE("...CloseHandle()");
                    }
                    XOS_LOG_TRACE("CloseHandle()...");
                    if (FALSE != (CloseHandle(hProcess))) {
                        XOS_LOG_TRACE("...CloseHandle()");
                        return isTrue;
                    } else {
                        XOS_LOG_ERROR("failed " << GetLastError() << " on CloseHandle()");
                    }
                }
            }
        }
        return false; }

    virtual HANDLE Attach(HANDLE hProcess, HANDLE hThread, bool isCreated = false) {
        m_thread = hThread;
        return Extends::Attach(hProcess, isCreated);
    }
    virtual HANDLE Detach() {
        bool isCreated = false;
        return Detach(isCreated);
    }
    virtual HANDLE Detach(HANDLE& hThread) {
        bool isCreated = false;
        return Detach(hThread, isCreated);
    }
    virtual HANDLE Detach(bool& isCreated) {
        HANDLE hThread = 0;
        return Detach(hThread, isCreated);
    }
    virtual HANDLE Detach(HANDLE& hThread, bool& isCreated) {
        hThread = m_thread;
        m_thread = 0;
        return Extends::Detach(isCreated);
    }

    virtual bool Join() {
        if (Success == (TimedJoin(INFINITE))) {
            return true;
        }
        return false; }
    virtual bool Separate() {
        Detach();
        return true; }

    virtual Status TryJoin() {
        return TimedJoin(0); }

    virtual Status TimedJoin(mseconds_t waitMilliSeconds) {
        return Extends::TimedJoin(waitMilliSeconds); }

protected:
    typedef Wrapped<PROCESS_INFORMATION> ProcessInformation;
    typedef Wrapped<STARTUPINFO> StartupInfo;

    class _EXPORT_CLASS CommandLine: public StringT<tchar_t> {
    public:
        CommandLine(char** argv) {
            tchar_t null = 0;
            const char* arg = 0;
            if ((arg = *(argv++))) {
                do {
                    Append(arg);
                    if ((arg = *(argv++))) {
                        Append(" "); }
                } while ((arg));
            }
            m_str.Append(c_str(), length());
            m_str.Append(&null, 1);
        }
        inline tchar_t* str() const { 
            return m_str.Elements(); }
    protected:
        Array<tchar_t> m_str;
    };

    HANDLE m_thread;
};

} // namespace windows 
} // namespace xos 

#endif // _XOS_OS_WINDOWS_PROCESS_HPP 
