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
///   File: Thread.hpp
///
/// Author: $author$
///   Date: 10/3/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_OS_WINDOWS_THREAD_HPP
#define _XOS_OS_WINDOWS_THREAD_HPP

#include "xos/os/windows/handle/Joined.hpp"
#include "xos/os/Thread.hpp"
#include "xos/os/Logger.hpp"
#include "xos/base/Opened.hpp"

namespace xos {
namespace windows {

typedef xos::Thread ThreadImplement;
typedef ThreadImplement::Status ThreadStatus;
typedef Attached<HANDLE, int, 0, ExportBase, ThreadImplement> ThreadAttached;
typedef handle::Joined<HANDLE, ThreadStatus, ThreadAttached, ThreadImplement> ThreadJoined;
typedef Opened<HANDLE, int, 0, ThreadJoined, ThreadImplement> ThreadExtend;

class _EXPORT_CLASS Thread: virtual public ThreadImplement, public ThreadExtend {
public:
    typedef ThreadImplement Implements;
    typedef ThreadExtend Extends;

    Thread(Run& run): m_run(run) {
        if (!(Start())) {
            XOS_LOG_ERROR("failed on Start()");
            throw (Error(Error::Failed));
        }
    }
    virtual ~Thread() {
        if (!(Closed())) {
            XOS_LOG_ERROR("failed on Closed()");
        }
    }

    virtual bool Start() {
        bool isStarted = false;
        HANDLE detached = 0;
        LPSECURITY_ATTRIBUTES lpSecurityAttributes = 0;
        DWORD dwStackSize = 0;
        DWORD dwCreationFlags = 0;
        DWORD dwThreadId;

        if ((isStarted = (0 != (detached = (HANDLE)(CreateThread
            (lpSecurityAttributes, dwStackSize, StartRoutine, 
             (LPVOID)(this), dwCreationFlags, &dwThreadId)))))) {
            Attach(detached, isStarted);
        }
        return isStarted;
    }
    virtual bool Close() {
        if ((Join())) {
            HANDLE handle = 0;
            if ((handle = Detach())) {
                XOS_LOG_TRACE("CloseHandle()...");
                if (FALSE != (CloseHandle(handle))) {
                    XOS_LOG_TRACE("...CloseHandle()");
                    return true;
                } else {
                    XOS_LOG_ERROR("failed " << GetLastError() << " on CloseHandle()");
                }
            }
        }
        return false;
    }

    virtual bool Join() {
        return (Success == (TimedJoin(INFINITE))); }

    virtual Status TryJoin() {
        return TimedJoin(0); }

    virtual Status TimedJoin(mseconds_t waitMilliSeconds) {
        return Extends::TimedJoin(waitMilliSeconds); }

protected:
    static DWORD WINAPI StartRoutine(LPVOID lpParameter) {
        DWORD result = 0;
        Thread* t = 0;
        XOS_LOG_TRACE("in...");
        if ((t = (Thread*)(lpParameter))) {
            XOS_LOG_TRACE("t->m_run()...");
            t->m_run();
            XOS_LOG_TRACE("...t->m_run()");
        } else {
            XOS_LOG_ERROR("LPVOID lpParameter == 0");
        }
        XOS_LOG_TRACE("...out");
        return result;
    }
    Run& m_run;
};

} // namespace windows 
} // namespace xos 

#endif // _XOS_OS_WINDOWS_THREAD_HPP 
