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
///   File: Mutex.hpp
///
/// Author: $author$
///   Date: 4/15/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_MT_UNIX_MUTEX_HPP
#define _XOS_MT_UNIX_MUTEX_HPP

#include "xos/mt/Mutex.hpp"
#include "xos/base/Creator.hpp"
#include "xos/base/Attacher.hpp"
#include "xos/os/Logger.hpp"

#include <pthread.h>
#include <time.h>
#include <errno.h>

#if defined(_POSIX_TIMEOUTS) && (_POSIX_TIMEOUTS >=0 )
#if !defined(PTHREAD_MUTEX_HAS_TIMEDLOCK)
#define PTHREAD_MUTEX_HAS_TIMEDLOCK
#endif // !defined(PTHREAD_MUTEX_HAS_TIMEDLOCK)
#endif // defined(_POSIX_TIMEOUTS) && (_POSIX_TIMEOUTS >=0 )

namespace xos {
namespace mt {
namespace unix {

typedef CreatorImplementT<mt::Mutex> MutexAttacherImplement;
typedef ExportBase MutexAttachedExtend;
typedef pthread_mutex_t* MutexAttachedT;
typedef AttacherT<pthread_mutex_t*, int, 0, MutexAttacherImplement> MutexAttacher;
typedef AttachedT<pthread_mutex_t*, int, 0, MutexAttacher, MutexAttachedExtend> MutexAttached;
typedef CreatedT<pthread_mutex_t*, int, 0, MutexAttacher, MutexAttached> MutexCreated;
typedef MutexAttacher MutexImplements;
typedef MutexCreated MutexExtends;
///////////////////////////////////////////////////////////////////////
///  Class: MutexT
///////////////////////////////////////////////////////////////////////
template
<class TAttached = MutexAttachedT,
 class TExtend = MutexExtends,
 class TImplement = MutexImplements>

class _EXPORT_CLASS MutexT: virtual public TImplement, public TExtend {
public:
    typedef TImplement Implements;
    typedef TExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    MutexT(TAttached attachedTo, bool isCreated): Extends(attachedTo, isCreated) {
    }
    MutexT(TAttached attachedTo): Extends(attachedTo) {
    }
    MutexT(bool initallyLocked) {
        if (!(Create(initallyLocked))) {
            Creator::Exception e = Creator::FailedToCreate;
            throw (e);
        }
    }
    MutexT() {
        if (!(Create())) {
            Creator::Exception e = Creator::FailedToCreate;
            throw (e);
        }
    }
    virtual ~MutexT() {
        if (!(this->Destroyed())) {
            Creator::Exception e = Creator::FailedToDestroy;
            throw (e);
        }
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Create(bool initallyLocked) {
        if (!(initallyLocked))
            return this->Create();
        return false;
    }
    virtual bool Create() {
        if ((this->Destroyed())) {
            int err = 0;
            if (!(err = pthread_mutexattr_init(&m_mutexattr))) {
                bool isCreated = false;
                if ((isCreated = !(err = pthread_mutex_init(&m_mutex, &m_mutexattr)))) {
                    this->AttachCreated(&m_mutex, isCreated);
                    if ((err = pthread_mutexattr_destroy(&m_mutexattr))) {
                        if ((Logging()))
                        { XOS_LOG_ERROR("failed err = " << err << " on pthread_mutexattr_destroy()"); }
                    }
                    return true;
                }
                if ((err = pthread_mutexattr_destroy(&m_mutexattr))) {
                    if ((Logging()))
                    { XOS_LOG_ERROR("failed err = " << err << " on pthread_mutexattr_destroy()"); }
                }
            }
        }
        return false;
    }
    virtual bool Destroy() {
        pthread_mutex_t* mutex = 0;
        bool isCreated = false;
        if ((mutex = this->DetachCreated(isCreated))) {
            int err = 0;
            if ((err = pthread_mutex_destroy(mutex))) {
                if ((Logging()))
                { XOS_LOG_ERROR("failed err = " << err << " on pthread_mutex_destroy()"); }
            } else {
                return true;
            }
        }
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Lock() {
        pthread_mutex_t* mutex = 0;
        int err = 0;
        if ((mutex = this->m_attachedTo)) {
            if ((err = pthread_mutex_lock(mutex))) {
                if ((Logging()))
                { XOS_LOG_ERROR("failed err = " << err << " on pthread_mutex_lock()"); }
            } else {
                return true;
            }
        }
        return false;
    }
    virtual bool Unlock() {
        pthread_mutex_t* mutex = 0;
        int err = 0;
        if ((mutex = this->m_attachedTo)) {
            if ((err = pthread_mutex_unlock(mutex))) {
                if ((Logging()))
                { XOS_LOG_ERROR("failed err = " << err << " on pthread_mutex_unlock()"); }
            } else {
                return true;
            }
        }
        return false;
    }
    virtual wait::Status TryLock() {
        pthread_mutex_t* mutex = 0;
        if ((mutex = this->m_attachedTo)) {
            int err = 0;
            if ((err =  pthread_mutex_trylock(mutex))) {
                switch(err) {
                case ETIMEDOUT:
                    if ((Logging()))
                    { XOS_LOG_TRACE("timedout err = " << err << " on pthread_mutex_trylock()"); }
                    return wait::Busy;
                case EINTR:
                    if ((Logging()))
                    { XOS_LOG_ERROR("interrupted err = " << err << " on pthread_mutex_trylock()"); }
                    return wait::Interrupted;
                default:
                    if ((Logging()))
                    { XOS_LOG_ERROR("failed err = " << err << " on pthread_mutex_trylock()"); }
                }
            } else {
                return wait::Success;
            }
        }
        return wait::Failed;
    }
    virtual wait::Status TimedLock(mseconds_t waitMilliseconds) {
        pthread_mutex_t* mutex = 0;
        if ((mutex = this->m_attachedTo)) {
            int err = 0;
            if (0 < waitMilliseconds) {
#if defined(PTHREAD_MUTEX_HAS_TIMEDLOCK)
                struct timespec untilTime;
                clock_gettime(CLOCK_REALTIME, &untilTime);
                untilTime.tv_sec +=  waitMilliseconds/1000;
                untilTime.tv_nsec +=  (waitMilliseconds%1000)*1000;
                if ((err = pthread_mutex_timedlock(mutex, &untilTime))) {
                    switch(err) {
                    case ETIMEDOUT:
                        if ((Logging()))
                        { XOS_LOG_TRACE("timedout err = " << err << " on pthread_mutex_timedlock()"); }
                        return wait::Busy;
                    case EINTR:
                        if ((Logging()))
                        { XOS_LOG_ERROR("interrupted err = " << err << " on pthread_mutex_timedlock()"); }
                        return wait::Interrupted;
                    default:
                        if ((Logging()))
                        { XOS_LOG_ERROR("failed err = " << err << " on pthread_mutex_timedlock()"); }
                    }
                } else {
                    return wait::Success;
                }
#else // defined(PTHREAD_MUTEX_HAS_TIMEDLOCK)
                if ((Logging()))
                { XOS_LOG_ERROR("failed invalid operation pthread_mutex_timedlock()"); }
                return wait::Invalid;
#endif // defined(PTHREAD_MUTEX_HAS_TIMEDLOCK)
            } else {
                if (0 == waitMilliseconds) {
                    if ((err =  pthread_mutex_trylock(mutex))) {
                        switch(err) {
                        case ETIMEDOUT:
                            if ((Logging()))
                            { XOS_LOG_TRACE("timedout err = " << err << " on pthread_mutex_trylock()"); }
                            return wait::Busy;
                        case EINTR:
                            if ((Logging()))
                            { XOS_LOG_ERROR("interrupted err = " << err << " on pthread_mutex_trylock()"); }
                            return wait::Interrupted;
                        default:
                            if ((Logging()))
                            { XOS_LOG_ERROR("failed err = " << err << " on pthread_mutex_trylock()"); }
                        }
                    } else {
                        return wait::Success;
                    }
                } else {
                    if ((err =  pthread_mutex_lock(mutex))) {
                        if ((Logging()))
                        { XOS_LOG_ERROR("failed err = " << err << " on pthread_mutex_lock()"); }
                    } else {
                        return wait::Success;
                    }
                }
            }
        }
        return wait::Failed;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Logging() const {
        return true;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    pthread_mutexattr_t m_mutexattr;
    pthread_mutex_t m_mutex;
};
typedef MutexT<> Mutex;

} // namespace unix 
} // namespace mt 
} // namespace xos 

#endif // _XOS_MT_UNIX_MUTEX_HPP 
