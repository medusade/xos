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
///   File: Semaphore.hpp
///
/// Author: $author$
///   Date: 10/6/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_OS_WINDOWS_SEMAPHORE_HPP
#define _XOS_OS_WINDOWS_SEMAPHORE_HPP

#include "xos/os/Semaphore.hpp"
#include "xos/base/Created.hpp"
#include "xos/os/Logger.hpp"

namespace xos {
namespace windows {

typedef xos::Semaphore SemaphoreImplement;
typedef Attached<HANDLE, int, 0, ExportBase, SemaphoreImplement> SemaphoreAttached;
typedef Created<HANDLE, int, 0, SemaphoreAttached, SemaphoreImplement> SemaphoreExtend;

class _EXPORT_CLASS Semaphore: virtual public SemaphoreImplement, public SemaphoreExtend {
public:
    typedef SemaphoreImplement Implements;
    typedef SemaphoreExtend Extends;

    Semaphore(HANDLE detached, bool isCreated = false)
    : Extends(detached, isCreated) {}
    Semaphore() {
        if (!(Create())) {
            XOS_LOG_ERROR("failed on Create()");
            throw (Error(Error::Failed));
        }
    }
    virtual ~Semaphore() {
        if ((IsCreated())) {
            if (!(Destroy())) {
                XOS_LOG_ERROR("failed on Destroy()");
            }
        }
    }

    virtual bool Create(size_t initialCount = 0, ssize_t maximumCount = -1) {
        LONG lInitialCount = (LONG)(initialCount);
        LONG lMaximumCount =(LONG)((0 > maximumCount)?(((ULONG)(-1))>>1):(maximumCount));
        LPSECURITY_ATTRIBUTES lpSecurityAttributes = 0;
        LPCTSTR lpName = 0;
        bool isCreated = false;
        HANDLE detached = 0;

        if ((m_attachedTo)) {
            if ((IsCreated())) {
                if (!(Destroy())) {
                    return false;
                }
            } else {
                Detach();
            }
        }

        if ((isCreated = (0 != (detached = CreateSemaphore(lpSecurityAttributes, lInitialCount, lMaximumCount, lpName))))) {
            Attach(detached, isCreated);
            return true;
        } else {
            XOS_LOG_ERROR("failed " << GetLastError() << " on CreateSemaphore()");
        }
    return false; }
    virtual bool Destroy() {
        bool isCreated = false;
        HANDLE detached = 0;
        if ((detached = Detach(isCreated))) {
            if ((CloseHandle(detached))) {
                return true;
            } else {
                XOS_LOG_ERROR("failed " << GetLastError() << " on CloseHandle()");
            }
        }
    return false; }

    virtual bool Acquire() { 
        if (Success == (TimedAcquire(INFINITE))) {
            return true;
        }
        return false; }
    virtual bool Release() { 
        if (0 <= (Release(1))) {
            return true;
        }
        return false; }
    virtual bool isAcquired() const { 
        return false; }

    virtual ssize_t Acquire(size_t amount) { 
        return -(ssize_t)(Failed); }
    virtual ssize_t Release(size_t amount) {
        ssize_t count = -(ssize_t)(Failed);
        HANDLE detached = 0;
        if ((detached = m_attachedTo)) {
            LONG lReleaseCount = (LONG)(amount);
            LONG lPreviousCount = 0;
            if ((ReleaseSemaphore(detached, lReleaseCount, &lPreviousCount))) {
                count = lPreviousCount;
            } else {
                XOS_LOG_ERROR("failed " << GetLastError() << " on ReleaseSemaphore()");
            }
        }
        return count; }
    virtual ssize_t AmountAcquired() const { 
        return -(ssize_t)(Failed); }

    virtual Status TryAcquire() { 
        return TimedAcquire(0); }
    virtual Status TimedAcquire(mseconds_t waitMilliSeconds) { 
        HANDLE detached = 0;
        if ((detached = m_attachedTo)) {
            DWORD dwMilliSeconds = (DWORD)(waitMilliSeconds);
            DWORD dwResult = 0;
            XOS_LOG_TRACE("waiting on WaitForSingleObject()...");
            if (WAIT_OBJECT_0 == (dwResult = WaitForSingleObject(detached, dwMilliSeconds))) {
                XOS_LOG_TRACE("...WAIT_OBJECT_0 on WaitForSingleObject()");
                return Success;
            } else {
                switch(dwResult) {
                case WAIT_ABANDONED:
                    XOS_LOG_TRACE("...WAIT_ABANDONED on WaitForSingleObject()");
                    return Interrupted;
                    break;
                case WAIT_TIMEOUT:
                    XOS_LOG_TRACE("...WAIT_TIMEOUT on WaitForSingleObject()");
                    return Busy;
                    break;
                default:
                    XOS_LOG_TRACE("...failed on WaitForSingleObject()");
                }
            }
        }
        return Failed; }
};

} // namespace windows 
} // namespace xos 

#endif // _XOS_OS_WINDOWS_SEMAPHORE_HPP 
