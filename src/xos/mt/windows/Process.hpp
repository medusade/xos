///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2014 $organization$
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
///   Date: 9/21/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_MT_WINDOWS_PROCESS_HPP
#define _XOS_MT_WINDOWS_PROCESS_HPP

#include "xos/mt/Process.hpp"
#include "xos/mt/Forked.hpp"
#include "xos/os/Logger.hpp"
#include "xos/base/Creator.hpp"
#include "xos/base/Attacher.hpp"
#include "xos/base/Wrapped.hpp"
#include "xos/base/String.hpp"
#include "xos/base/Array.hpp"

#include <process.h>

namespace xos {
namespace mt {
namespace windows {

typedef ForkerImplementT<mt::Process> ProcessForkerImplement;
typedef CreatorImplementT<ProcessForkerImplement> ProcessAttacherImplement;
typedef ExportBase ProcessAttachedExtend;
typedef HANDLE ProcessAttachedT;
typedef AttacherT<HANDLE, int, 0, ProcessAttacherImplement> ProcessAttacher;
typedef AttachedT<HANDLE, int, 0, ProcessAttacher, ProcessAttachedExtend> ProcessAttached;
typedef ForkedT<HANDLE, int, 0, ProcessAttacher, ProcessAttached> ProcessForked;
typedef CreatedT<HANDLE, int, 0, ProcessAttacher, ProcessForked> ProcessCreated;
typedef ProcessAttacher ProcessImplements;
typedef ProcessCreated ProcessExtends;
///////////////////////////////////////////////////////////////////////
///  Class: ProcessT
///////////////////////////////////////////////////////////////////////
template
<typename TChar = char, typename TEnd = TChar, TEnd VEnd = 0,
 class TImplement = ProcessImplements, class TExtend = ProcessExtends>

class _EXPORT_CLASS ProcessT: virtual public TImplement, public TExtend {
public:
    typedef TImplement Implements;
    typedef TExtend Extends;

    typedef TChar CharT;
    typedef TEnd EndT;
    enum { End = VEnd };

	///////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////
	ProcessT
    (const CharT* path, CharT** argv, CharT** env,
     HANDLE* fdup = 0, HANDLE** pdup = 0, bool isDetached = false)
    : m_thread(0) {
        if (!(this->Create(path, argv, env, fdup, pdup, isDetached))) {
            XOS_LOG_ERROR("...throwing Creator::FailedToCreate");
            Creator::Exception e = Creator::FailedToCreate;
            throw (e);
        }
    }
	ProcessT
    (HANDLE hProcess, HANDLE hThread, bool isCreated = false)
    : Extends(hProcess, isCrated), m_thread(hThread) {
        SetIsForked(isCreated);
    }
	ProcessT(const ProcessT& copy): m_thread(0) {
        XOS_LOG_ERROR("...throwing Creator::FailedToCreate");
        Creator::Exception e = Creator::FailedToCreate;
        throw (e);
    }
	ProcessT(): m_thread(0) {
    }
    virtual ~ProcessT() {
        if (!(this->Destroyed())) {
            XOS_LOG_ERROR("...throwing Creator::FailedToDestroy");
            Creator::Exception e = Creator::FailedToDestroy;
            throw (e);
        }
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Create
    (const CharT* path, CharT** argv, CharT** env,
     HANDLE* fdup = 0, HANDLE** pdup = 0, bool isDetached = false) {
        if ((this->Destroyed())) {
            ApplicationName applicationName(path);
            CommandLine commandLine(argv);
            Environment environment(env);
            StartupInfo startupInfo(0);
            ProcessInformation processInformation(0);
            LPCTSTR lpApplicationName = (applicationName.length())?(applicationName.c_str()):(0);
            LPTSTR lpCommandLine = (commandLine.length())?(commandLine.str()):(0);
            LPSECURITY_ATTRIBUTES lpProcessAttributes = 0;
            LPSECURITY_ATTRIBUTES lpThreadAttributes = 0;
            BOOL bInheritHandles = FALSE;
            DWORD dwCreationFlags = (isDetached)?(DETACHED_PROCESS):(0);
            LPVOID lpEnvironment = (environment.length())?(environment.str()):(0);
            LPTSTR lpCurrentDirectory = 0;
            LPSTARTUPINFO lpStartupInfo = &startupInfo.wrapped();
            LPPROCESS_INFORMATION lpProcessInformation = &processInformation.wrapped();
            HANDLE hProcess = 0;
            HANDLE hThread = 0;

            XOS_LOG_TRACE("CreateProcess()...");
            if (FALSE != (CreateProcess
                (lpApplicationName, lpCommandLine, 
                 lpProcessAttributes,lpThreadAttributes, bInheritHandles, dwCreationFlags,
                 lpEnvironment, lpCurrentDirectory, lpStartupInfo, lpProcessInformation))) {
                hProcess = processInformation.wrapped().hProcess;
                hThread = processInformation.wrapped().hThread;
                this->AttachCreated(hProcess, hThread);
                XOS_LOG_TRACE("...CreateProcess()");
                return true;
            } else {
                String applicationName(path);
                XOS_LOG_ERROR("failed " << GetLastError() << " on CreateProcess(\"" << applicationName << "\", ...)");
            }
        }
        return false;
    }
    virtual bool Destroy() {
        if ((this->Joined())) {
            HANDLE hProcess = 0;
            HANDLE hThread = 0;

            if ((hProcess = this->Detach(hThread))) {
                bool isTrue = false;

                if ((hThread)) {
                    XOS_LOG_TRACE("CloseHandle()...");
                    if (!(isTrue = (FALSE != CloseHandle(hThread)))) {
                        XOS_LOG_ERROR("failed " << GetLastError() << " on CloseHandle()");
                    } else {
                        XOS_LOG_TRACE("...CloseHandle()");
                    }
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
        return false;
    }

	///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Joined() {
        if ((this->IsForked())) {
            return this->Join();
        }
        return true;
    }
    virtual bool Join() {
        return this->Wait();
    }
    virtual wait::Status TryJoin() {
        return this->TryWait();
    }
    virtual wait::Status TimedJoin(mseconds_t waitMilliseconds) {
        return this->TimedWait(waitMilliseconds);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Continue() { 
        this->SetIsForked(false);
        return true;
    }
    virtual bool Wait() {
        return (wait::Success == (TimedWait(wait::Forever)));
    }
    virtual wait::Status TryWait() {
        return (TimedWait(wait::Now));
    }
    virtual wait::Status TimedWait(mseconds_t waitMilliSeconds) {
        HANDLE handle = 0;

        if ((handle = this->AttachedTo())) {
            DWORD dwWaitMilliSeconds = (DWORD)(wait::Forever != waitMilliSeconds)?(waitMilliSeconds):(INFINITE);
            DWORD dwResult = 0;

            XOS_LOG_TRACE("wait on WaitForSingleObject()...");
            if (WAIT_OBJECT_0 == (dwResult = WaitForSingleObject(handle, dwWaitMilliSeconds))) {
                XOS_LOG_TRACE("...WAIT_OBJECT_0 on WaitForSingleObject()");
                this->Continue();
                return wait::Success;
            } else {
                switch(dwResult) {
                case WAIT_TIMEOUT:
                    XOS_LOG_TRACE("...WAIT_TIMEOUT on WaitForSingleObject()");
                    return wait::Busy;
                    break;

                case WAIT_ABANDONED:
                     XOS_LOG_ERROR("...WAIT_ABANDONED on WaitForSingleObject()");
                     this->Continue();
                     return wait::Interrupted;
                    break;

                default:
                    this->Continue();
                    XOS_LOG_ERROR("...failed on WaitForSingleObject()");
                }
            }
        }
        return wait::Failed;
    }

	///////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////
    virtual HANDLE AttachCreated(HANDLE hProcess, HANDLE hThread, bool isCreated = true) {
        this->m_thread = hThread;
        return Extends::AttachCreated(hProcess, isCreated);
    }
    virtual HANDLE Attach(HANDLE hProcess, HANDLE hThread) {
        this->m_thread = hThread;
        return Extends::Attach(hProcess);
    }
    virtual HANDLE DetachCreated(HANDLE& hThread, bool& isCreated) {
        hThread = this->m_thread;
        return Extends::DetachCreated(isCreated);
    }
    virtual HANDLE Detach(HANDLE& hThread) {
        hThread = this->m_thread;
        return this->Detach();
    }

protected:
	///////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////
    virtual HANDLE Detach() {
        this->m_thread = 0;
        return Extends::Detach();
    }

	///////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////
protected:
    typedef Wrapped<PROCESS_INFORMATION> ProcessInformation;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    class _EXPORT_CLASS StartupInfo: public Wrapped<STARTUPINFO> {
    public:
        typedef Wrapped<STARTUPINFO> Extends;
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        StartupInfo(InitializedT initialized): Extends(initialized) {
            m_wrapped.cb = sizeof(STARTUPINFO);
        }
    };
    typedef StringT<tchar_t> ApplicationName;
	///////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////
    class _EXPORT_CLASS CommandLine: public StringT<tchar_t> {
    public:
	    ///////////////////////////////////////////////////////////////////////
    	///////////////////////////////////////////////////////////////////////
        CommandLine(char** argv) {
            tchar_t null = 0;
            const char* arg = 0;
            if ((arg = *(argv++))) {
                Append(arg);
                while ((arg = *(argv++))) {
                    Append(" ");
                    Append(arg);
                }
            }
            m_str.Append(c_str(), length());
            m_str.Append(&null, 1);
        }
        CommandLine(wchar_t** argv) {
            tchar_t null = 0;
            const wchar_t* arg = 0;
            if ((arg = *(argv++))) {
                Append(arg);
                while ((arg = *(argv++))) {
                    Append(" ");
                    Append(arg);
                }
            }
            m_str.Append(c_str(), length());
            m_str.Append(&null, 1);
        }
    	///////////////////////////////////////////////////////////////////////
	    ///////////////////////////////////////////////////////////////////////
        inline tchar_t* str() const { 
            return m_str.Elements(); }
    	///////////////////////////////////////////////////////////////////////
	    ///////////////////////////////////////////////////////////////////////
    protected:
        Array<tchar_t> m_str;
    };
	///////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////
    class _EXPORT_CLASS Environment: public StringT<tchar_t> {
    public:
	    ///////////////////////////////////////////////////////////////////////
    	///////////////////////////////////////////////////////////////////////
        Environment(char** argv) {
            tchar_t null = 0;
            const char* arg = 0;
            if ((arg = *(argv++))) {
                do {
                    Append(arg);
                    Append(&null, 1);
                } while ((arg));
                m_str.Append(c_str(), length());
            } else {
                m_str.Append(&null, 1);
            }
            m_str.Append(&null, 1);
        }
        Environment(wchar_t** argv) {
            tchar_t null = 0;
            const wchar_t* arg = 0;
            if ((arg = *(argv++))) {
                do {
                    Append(arg);
                    Append(&null, 1);
                } while ((arg));
                m_str.Append(c_str(), length());
            } else {
                m_str.Append(&null, 1);
            }
            m_str.Append(&null, 1);
        }
    	///////////////////////////////////////////////////////////////////////
	    ///////////////////////////////////////////////////////////////////////
        inline tchar_t* str() const { 
            return m_str.Elements(); }
    	///////////////////////////////////////////////////////////////////////
	    ///////////////////////////////////////////////////////////////////////
    protected:
        Array<tchar_t> m_str;
    };

	///////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////
protected:
	HANDLE m_thread;
};
typedef ProcessT<char> Process;
typedef ProcessT<tchar_t> TProcess;
typedef ProcessT<wchar_t> WProcess;

} // namespace windows 
} // namespace mt 
} // namespace xos 

#endif // _XOS_MT_WINDOWS_PROCESS_HPP
