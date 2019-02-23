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
///   File: Semaphore.hpp
///
/// Author: $author$
///   Date: 7/30/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_MT_UNIX_SEMAPHORE_HPP
#define _XOS_MT_UNIX_SEMAPHORE_HPP

#include "xos/mt/Semaphore.hpp"
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
namespace mt {
namespace unix {

typedef xos::mt::Semaphore SemaphoreImplement;
typedef Attached<sem_t*, int, 0, ExportBase, SemaphoreImplement> SemaphoreAttached;
typedef Created<sem_t*, int, 0, SemaphoreAttached, SemaphoreImplement> SemaphoreExtend;
///////////////////////////////////////////////////////////////////////
///  Class: SemaphoreT
///////////////////////////////////////////////////////////////////////
template
<class TExtend = SemaphoreExtend,
 class TImplement = SemaphoreImplement>

class _EXPORT_CLASS SemaphoreT: virtual public TImplement, public TExtend {
public:
    typedef TImplement Implements;
    typedef TExtend Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    SemaphoreT(sem_t* attachedTo, bool isCreated): Extends(attachedTo, isCreated) {
    }
    SemaphoreT(sem_t* attachedTo): Extends(attachedTo) {
    }
    SemaphoreT(size_t initialCount) {
        if ((this->InitiallyCreated())) {
            if (!(this->Create(initialCount))) {
                Creator::Exception e = Creator::FailedToCreate;
                throw (e);
            }
        }
    }
    SemaphoreT() {
        if ((this->InitiallyCreated())) {
            if (!(this->Create())) {
                Creator::Exception e = Creator::FailedToCreate;
                throw (e);
            }
        }
    }
    virtual ~SemaphoreT() {
        if (!(this->Destroyed())) {
            Creator::Exception e = Creator::FailedToDestroy;
            throw (e);
        }
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Create() {
        return Create(0);
    }
    virtual bool Create(size_t initialCount) {
        if ((this->Destroyed())) {
            int pshared = SEMAPHORE_PROCESS_PRIVATE;
            sem_t* sem = 0;
            int err = 0;
            if ((!(err = sem_init(&m_sem, pshared, initialCount)))) {
                this->AttachCreated(&m_sem);
                return true;
            } else {
                XOS_LOG_ERROR("failed " << err << " on sem_init()");
            }
        }
        return false;
    }
    virtual bool Destroy() {
        sem_t* sem = 0;
        if ((sem = this->Detach())) {
            int err = 0;
            if (!(err = sem_destroy(sem))) {
                return true;
            } else {
                XOS_LOG_ERROR("failed " << err << " on sem_destroy()");
            }
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Acquire() {
        sem_t* sem = 0;
        if ((sem = this->AttachedTo())) {
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
        if ((sem = this->AttachedTo())) {
            int err = 0;
            if (!(err = sem_post(sem))) {
                return true;
            } else {
                XOS_LOG_ERROR("failed " << err << " on sem_post()");
            }
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual wait::Status TryAcquire() {
        sem_t* sem = 0;
        if ((sem = this->AttachedTo())) {
            int err = 0;
            XOS_LOG_TRACE("wait on sem_trywait()...");
            if (!(err = sem_trywait(sem))) {
                XOS_LOG_TRACE("...waited on sem_trywait()");
                return wait::Success;
            } else {
                XOS_LOG_TRACE("...failed " << err << " on sem_trywait()");
            }
        }
        return wait::Failed;
    }
    virtual wait::Status TimedAcquire(mseconds_t waitMilliSeconds) {
        sem_t* sem = 0;
        if ((sem = this->AttachedTo())) {
            int err = 0;
            if (0 < (waitMilliSeconds)) {
#if defined(SEM_HAS_TIMEDWAIT)
                struct timespec untilTime;
                clock_gettime(CLOCK_REALTIME, &untilTime);
                untilTime.tv_sec +=  waitMilliSeconds/1000;
                untilTime.tv_nsec +=  (waitMilliSeconds%1000)*1000;
                XOS_LOG_TRACE("wait on sem_timedwait()...");
                if (!(err = sem_timedwait(sem, &untilTime))) {
                    XOS_LOG_TRACE("...waited on sem_timedwait()");
                    return wait::Success;
                } else {
                    if (ETIMEDOUT == (errno)) {
                        XOS_LOG_TRACE("...ETIMEDOUT on semaphore_timedwait()");
                        return wait::Busy;
                    } else {
                        if (EINTR == (errno)) {
                            XOS_LOG_TRACE("...EINTR on semaphore_timedwait()");
                            return wait::Interrupted;
                        } else {
                            XOS_LOG_TRACE("...failed " << err << " on semaphore_timedwait()");
                        }
                    }
                }
#else // defined(SEM_HAS_TIMEDWAIT)
                return wait::Invalid;
#endif // defined(SEM_HAS_TIMEDWAIT)
            } else {
                if (0 > (waitMilliSeconds)) {
                    XOS_LOG_TRACE("wait on sem_trywait()...");
                    if (!(err = sem_trywait(sem))) {
                        XOS_LOG_TRACE("...waited on sem_trywait()");
                        return wait::Success;
                    } else {
                        if (ETIMEDOUT == (errno)) {
                            XOS_LOG_TRACE("...ETIMEDOUT on semaphore_trywait()");
                            return wait::Busy;
                        } else {
                            if (EINTR == (errno)) {
                                XOS_LOG_ERROR("...EINTR on semaphore_trywait()");
                                return wait::Interrupted;
                            } else {
                                XOS_LOG_ERROR("...failed " << err << " on semaphore_trywait()");
                            }
                        }
                    }
                } else {
                    XOS_LOG_TRACE("wait on sem_wait()...");
                    if (!(err = sem_wait(sem))) {
                        XOS_LOG_TRACE("...waited on sem_wait()");
                        return wait::Success;
                    } else {
                        if (EINTR == (errno)) {
                            XOS_LOG_TRACE("...EINTR on semaphore_wait()");
                            return wait::Interrupted;
                        } else {
                            XOS_LOG_TRACE("...failed " << err << " on semaphore_wait()");
                        }
                    }
                }
            }
        }
        return wait::Failed;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    sem_t m_sem;
};
typedef SemaphoreT<> Semaphore;

} // namespace unix 
} // namespace mt 
} // namespace xos 

#endif // _XOS_MT_UNIX_SEMAPHORE_HPP 
