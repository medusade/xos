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
///   Date: 10/14/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_OS_MACOSX_SEMAPHORE_HPP
#define _XOS_OS_MACOSX_SEMAPHORE_HPP

#include "xos/os/Semaphore.hpp"
#include "xos/base/Created.hpp"
#include "xos/os/Logger.hpp"
#include <mach/task.h>
#include <mach/mach.h>
#include <mach/semaphore.h>

namespace xos {
namespace macosx {

typedef xos::Semaphore SemaphoreImplement;
typedef Attached<semaphore_t*, int, 0, ExportBase, SemaphoreImplement> SemaphoreAttached;
typedef Created<semaphore_t*, int, 0, SemaphoreAttached, SemaphoreImplement> SemaphoreExtend;

class _EXPORT_CLASS Semaphore: virtual public SemaphoreImplement, public SemaphoreExtend {
public:
    typedef SemaphoreImplement Implements;
    typedef SemaphoreExtend Extends;

    Semaphore(semaphore_t* detached, bool isCreated = false)
    : Extends(detached, isCreated) {}
    Semaphore() {
        if (!(Create())) {
            XOS_LOG_ERROR("failed on Create()");
            throw (Error(Error::Failed));
        }
    }
    virtual ~Semaphore() {
        if (!(Destroyed())) {
            XOS_LOG_ERROR("failed on Destroyed()");
        }
    }

    virtual bool Create(size_t initialCount = 0, ssize_t maximumCount = -1) {
        if ((Destroyed())) {
            task_t task = mach_task_self();
            sync_policy_t syncPolicy = SYNC_POLICY_FIFO;
            bool isCreated = false;
            int err;
            if ((isCreated = (KERN_SUCCESS == (err = semaphore_create(task, &m_sem, syncPolicy, initialCount))))) {
                Attach(&m_sem, isCreated);
                return true;
            } else {
                XOS_LOG_ERROR("failed " << err << " on semaphore_create()");
            }
        }
        return false; 
    }
    virtual bool Destroy() {
        task_t task = mach_task_self();
        semaphore_t* sem = 0;
        if ((sem = Detach())) {
            int err = 0;
            if (KERN_SUCCESS == (err = semaphore_destroy(task, *sem))) {
                return true;
            } else {
                XOS_LOG_ERROR("failed " << err << " on semaphore_destroy()");
            }
        }
        return false; 
    }

    virtual bool Acquire() { 
        semaphore_t* sem = 0;
        if ((sem = m_attachedTo)) {
            int err = 0;
            XOS_LOG_TRACE("wait on semaphore_wait()...");
            if (KERN_SUCCESS == (err = semaphore_wait(*sem))) {
                XOS_LOG_TRACE("...waited on semaphore_wait()");
                return true;
            } else {
                XOS_LOG_ERROR("...failed " << err << " on semaphore_wait()");
            }
        }
        return false; 
    }
    virtual bool Release() { 
        semaphore_t* sem = 0;
        if ((sem = m_attachedTo)) {
            int err = 0;
            if (KERN_SUCCESS == (err = semaphore_signal(*sem))) {
                return true;
            } else {
                XOS_LOG_ERROR("failed " << err << " on semaphore_signal()");
            }
        }
        return false; 
    }
    virtual bool isAcquired() const { 
        return false; 
    }

    virtual ssize_t Acquire(size_t amount) { 
        return -(ssize_t)(Failed); 
    }
    virtual ssize_t Release(size_t amount) {
        ssize_t count = -(ssize_t)(Failed);
        return count; 
    }
    virtual ssize_t AmountAcquired() const { 
        return -(ssize_t)(Failed); 
    }

    virtual Status TryAcquire() { 
        return TimedAcquire(0); 
    }
    virtual Status TimedAcquire(mseconds_t waitMilliseconds) { 
        semaphore_t* sem = 0;
        if ((sem = m_attachedTo)) {
            int err = 0;
            if (0 <= (waitMilliseconds)) {
                mach_timespec_t waitTime;
                waitTime.tv_sec = waitMilliseconds/1000;
                waitTime.tv_nsec = (waitMilliseconds%1000)*1000;
                XOS_LOG_TRACE("wait on semaphore_timedwait()...");
                if (KERN_SUCCESS == (err = semaphore_timedwait(*sem, waitTime))) {
                    XOS_LOG_TRACE("...waited on semaphore_timedwait()");
                    return Success;
                } else {
                    if (KERN_OPERATION_TIMED_OUT == (err)) {
                        XOS_LOG_TRACE("...KERN_OPERATION_TIMED_OUT on semaphore_timedwait()");
                        return Busy;
                    } else {
                        if (KERN_ABORTED == (err)) {
                            XOS_LOG_TRACE("...KERN_ABORTED on semaphore_timedwait()");
                            return Interrupted;
                        } else {
                            XOS_LOG_TRACE("...failed " << err << " on semaphore_timedwait()");
                        }
                    }
                }
            } else {
                XOS_LOG_TRACE("wait on semaphore_wait()...");
                if (KERN_SUCCESS == (err = semaphore_wait(*sem))) {
                    XOS_LOG_TRACE("...waited on semaphore_wait()");
                    return Success;
                } else {
                    XOS_LOG_ERROR("...failed " << err << " on semaphore_wait()");
                }
            }
        }
        return Failed; 
    }

protected:
    semaphore_t m_sem;
};

} // namespace macosx 
} // namespace xos 

#endif // _XOS_OS_MACOSX_SEMAPHORE_HPP 
