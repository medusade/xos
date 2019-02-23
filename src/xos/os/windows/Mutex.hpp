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
///   File: Mutex.hpp
///
/// Author: $author$
///   Date: 10/5/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_OS_WINDOWS_MUTEX_HPP
#define _XOS_OS_WINDOWS_MUTEX_HPP

#include "xos/os/Mutex.hpp"
#include "xos/base/Created.hpp"

namespace xos {
namespace windows {

typedef xos::Mutex MutexImplement;
typedef Attached<HANDLE, int, 0, ExportBase, MutexImplement> MutextAttached;
typedef Created<HANDLE, int, 0, MutextAttached, MutexImplement> MutexExtend;

class _EXPORT_CLASS Mutex: virtual public MutexImplement,  public MutexExtend {
public:
    typedef MutexImplement Implements;
    typedef MutexExtend Extends;

    Mutex(HANDLE detached, bool isCreated = false): Extends(detached, isCreated) {}
    Mutex() {
        if (!(Create())) {
            throw (Error(Error::Failed));
        }
    }
    virtual ~Mutex() {}

    virtual bool Create() {
        BOOL bInitialOwner = FALSE;
        LPCTSTR lpName = 0;
        LPSECURITY_ATTRIBUTES lpSecurityAttributes = 0;
        bool isCreated = false;
        HANDLE detached = 0;
        if ((detached = m_attachedTo)) {
            if ((isCreated = m_isCreated)) {
                if (!(Destroy())) {
                    return false;
                }
            }
        }
        if ((isCreated = (0 != (detached = CreateMutex(lpSecurityAttributes, bInitialOwner, lpName))))) {
            Attach(detached, isCreated);
            return true;
        }
        return false;
    }
    virtual bool Destroy() {
        bool isCreated = false;
        HANDLE detached = 0;
        if ((detached = Detach(isCreated))) {
            if ((CloseHandle(detached))) {
                return true;
            }
        }
        return false;
    }

    virtual bool Lock() {
        if (Success == (TimedLock(INFINITE))) {
            return true;
        }
        return false; }
    virtual bool Unlock() {
        HANDLE detached = 0;
        if ((detached = m_attachedTo)) {
            if ((ReleaseMutex(detached))) {
                return true;
            }
        }
        return false; }

    virtual Status TryLock() {
        return TimedLock(0); }
    virtual Status TimedLock(mseconds_t waitMilliseconds) {
        HANDLE detached = 0;
        if ((detached = m_attachedTo)) {
            DWORD result = 0;
            if (WAIT_OBJECT_0 == (result = WaitForSingleObject(detached, (DWORD)(waitMilliseconds)))) {
                return Success;
            } else {
                switch(result) {
                case WAIT_TIMEOUT:
                    return Busy;
                    break;
                case WAIT_ABANDONED:
                    return Interrupted;
                    break;
                }
            }
        }
        return Failed; }
};

} // namespace windows 
} // namespace xos 

#endif // _XOS_OS_WINDOWS_MUTEX_HPP 
