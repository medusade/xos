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
///   Date: 10/10/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_OS_UNIX_SEMAPHORE_HPP
#define _XOS_OS_UNIX_SEMAPHORE_HPP

#include "xos/os/Semaphore.hpp"
#include "xos/base/Created.hpp"
#include "xos/os/Logger.hpp"
#include <semaphore.h>
#include <errno.h>

#if defined(_POSIX_TIMEOUTS) && (_POSIX_TIMEOUTS >=0 )
#define SEM_HAS_TIMEDWAIT
#endif // defined(_POSIX_TIMEOUTS) && (_POSIX_TIMEOUTS >=0 )

#define SEMAPHORE_PROCESS_PRIVATE 0
#define SEMAPHORE_PROCESS_SHARED  1

namespace xos {
namespace unix {

typedef xos::Semaphore SemaphoreImplement;
typedef Attached<sem_t*, int, 0, ExportBase, SemaphoreImplement> SemaphoreAttached;
typedef Created<sem_t*, int, 0, SemaphoreAttached, SemaphoreImplement> SemaphoreExtend;

class _EXPORT_CLASS Semaphore: virtual public SemaphoreImplement, public SemaphoreExtend {
public:
    typedef SemaphoreImplement Implements;
    typedef SemaphoreExtend Extends;

    Semaphore(sem_t* detached, bool isCreated = false)
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
            int pshared = SEMAPHORE_PROCESS_PRIVATE;
            bool isCreated = false;
            sem_t* sem = 0;
            int err = 0;
            if ((isCreated = !(err = sem_init(&m_sem, pshared, initialCount)))) {
                Attach(&m_sem, isCreated);
                return true;
            } else {
                XOS_LOG_ERROR("failed " << err << " on sem_init()");
            }
        }
        return false; 
    }
    virtual bool Destroy() {
        sem_t* sem = 0;
        if ((sem = Detach())) {
            int err = 0;
            if (!(err = sem_destroy(sem))) {
                return true;
            } else {
                XOS_LOG_ERROR("failed " << err << " on sem_destroy()");
            }
        }
        return false; 
    }

    virtual bool Acquire() { 
        sem_t* sem = 0;
        if ((sem = m_attachedTo)) {
            int err = 0;
            XOS_LOG_TRACE("wait on sem_wait()...");
            if (!(err = sem_wait(sem))) {
                XOS_LOG_TRACE("...waited on sem_wait()");
                return true;
            } else {
                XOS_LOG_ERROR("...failed " << err << " on sem_wait()");
            }
        }
        return false; 
    }
    virtual bool Release() { 
        sem_t* sem = 0;
        if ((sem = m_attachedTo)) {
            int err = 0;
            if (!(err = sem_post(sem))) {
                return true;
            } else {
                XOS_LOG_ERROR("failed " << err << " on sem_post()");
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
        sem_t* sem = 0;
        if ((sem = m_attachedTo)) {
            int err = 0;
            XOS_LOG_TRACE("wait on sem_trywait()...");
            if (!(err = sem_trywait(sem))) {
                XOS_LOG_TRACE("...waited on sem_trywait()");
                return Success;
            } else {
                XOS_LOG_TRACE("...failed " << err << " on sem_trywait()");
            }
        }
        return Failed; 
    }
    virtual Status TimedAcquire(mseconds_t waitMilliSeconds) { 
#if defined(SEM_HAS_TIMEDWAIT)
        sem_t* sem = 0;
        if ((sem = m_attachedTo)) {
            int err = 0;
            if (0 < (waitMilliSeconds)) {
                struct timespec untilTime;
                clock_gettime(CLOCK_REALTIME, &untilTime);
                untilTime.tv_sec +=  waitMilliSeconds/1000;
                untilTime.tv_nsec +=  (waitMilliSeconds%1000)*1000;
                XOS_LOG_TRACE("wait on sem_timedwait()...");
                if (!(err = sem_timedwait(sem, &untilTime))) {
                    XOS_LOG_TRACE("...waited on sem_timedwait()");
                    return Success;
                } else {
                    if (ETIMEDOUT == (errno)) {
                        XOS_LOG_TRACE("...ETIMEDOUT on semaphore_timedwait()");
                        return Busy;
                    } else {
                        if (EINTR == (errno)) {
                            XOS_LOG_TRACE("...EINTR on semaphore_timedwait()");
                            return Interrupted;
                        } else {
                            XOS_LOG_TRACE("...failed " << err << " on semaphore_timedwait()");
                        }
                    }
                }
            } else {
                if (0 == (waitMilliSeconds)) {
                    XOS_LOG_TRACE("wait on sem_trywait()...");
                    if (!(err = sem_trywait(sem))) {
                        XOS_LOG_TRACE("...waited on sem_trywait()");
                        return Success;
                    } else {
                        XOS_LOG_TRACE("...failed " << err << " on sem_trywait()");
                    }
                } else {
                    XOS_LOG_TRACE("wait on sem_wait()...");
                    if (!(err = sem_wait(sem))) {
                        XOS_LOG_TRACE("...waited on sem_wait()");
                        return Success;
                    } else {
                        XOS_LOG_ERROR("...failed " << err << " on sem_wait()");
                    }
                }
            }
        }
        return Failed; 
#else // defined(SEM_HAS_TIMEDWAIT)
        return Invalid;
#endif // defined(SEM_HAS_TIMEDWAIT)
    }
protected:
    sem_t m_sem;
};

} // namespace unix 
} // namespace xos 

#endif // _XOS_OS_UNIX_SEMAPHORE_HPP 
