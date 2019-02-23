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
///   Date: 10/10/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_OS_UNIX_MUTEX_HPP
#define _XOS_OS_UNIX_MUTEX_HPP

#include "xos/os/unix/Pthread.hpp"
#include "xos/os/Mutex.hpp"
#include "xos/base/Created.hpp"

namespace xos {
namespace unix {

typedef xos::Mutex MutexImplement;
typedef Attached<pthread_mutex_t*, int, 0, ExportBase, MutexImplement> MutextAttached;
typedef Created<pthread_mutex_t*, int, 0, MutextAttached, MutexImplement> MutexExtend;

class _EXPORT_CLASS Mutex: virtual public MutexImplement, public MutexExtend {
public:
    typedef MutexImplement Implements;
    typedef MutexExtend Extends;

    Mutex
    (pthread_mutex_t* mutex, 
     pthread_mutexattr_t* mutexattr, 
     bool isCreated = false)
    : Extends(mutex, isCreated), 
      m_mutexattrAttachedTo(mutexattr) {}
    Mutex() {
        if (!(Create())) {
            throw (Error(Error::Failed));
        }
    }
    virtual ~Mutex() {
    }

    virtual bool Create() {
        if ((Destroyed())) {
            int err = 0;
            if (!(err = pthread_mutexattr_init(&m_mutexattr))) {
                bool isCreated = false;
                if ((isCreated = !(err = pthread_mutex_init(&m_mutex, &m_mutexattr)))) {
                    Attach(&m_mutex, &m_mutexattr, isCreated);
                    return true;
                } else {
                    pthread_mutexattr_destroy(&m_mutexattr);
                }
            }
        }
        return false;
    }
    virtual bool Destroy() {
        pthread_mutex_t* mutex = 0;
        pthread_mutexattr_t* mutexattr = 0;
        bool isCreated = false;

        if ((mutex = Detach(mutexattr, isCreated))) {
            int err = 0;
            if (!(err = pthread_mutex_destroy(mutex))) {
                if (!(err = pthread_mutexattr_destroy(mutexattr))) {
                    return true;
                }
            }
        }
        return false;
    }

    virtual pthread_mutex_t* Attach(pthread_mutex_t* mutex, pthread_mutexattr_t* mutexattr, bool isCreated) {
        m_mutexattrAttachedTo = mutexattr;
        return Extends::Attach(mutex, isCreated);
    }
    virtual pthread_mutex_t* Detach(pthread_mutexattr_t*& mutexattr, bool isCreated) {
        mutexattr = m_mutexattrAttachedTo;
        m_mutexattrAttachedTo = 0;
        return Extends::Detach(isCreated);
    }

    virtual bool Lock() {
        pthread_mutex_t* mutex = 0;
        int err = 0;
        if ((mutex = m_attachedTo)) {
            if (!(err = pthread_mutex_lock(mutex))) {
                return true;
            }
        }
        return false; 
    }
    virtual bool Unlock() {
        pthread_mutex_t* mutex = 0;
        int err = 0;
        if ((mutex = m_attachedTo)) {
            if (!(err = pthread_mutex_unlock(mutex))) {
                return true;
            }
        }
        return false; 
    }

    virtual Status TryLock() {
        pthread_mutex_t* mutex = 0;
        if ((mutex = m_attachedTo)) {
            int err = 0;
            if (!(err =  pthread_mutex_trylock(mutex))) {
                return Success;
            }
            switch(err) {
            case ETIMEDOUT:
                return Busy;
            case EINTR:
                return Interrupted;
            }
        }
        return Failed; 
    }
    virtual Status TimedLock(mseconds_t waitMilliseconds) {
#if defined(PTHREAD_MUTEX_HAS_TIMEDLOCK)
        pthread_mutex_t* mutex = 0;
        if ((mutex = m_attachedTo)) {
            int err = 0;
            if (0 < waitMilliseconds) {
                struct timespec untilTime;
                clock_gettime(CLOCK_REALTIME, &untilTime);
                untilTime.tv_sec +=  waitMilliseconds/1000;
                untilTime.tv_nsec +=  (waitMilliseconds%1000)*1000;
                if (!(err = pthread_mutex_timedlock(mutex, &untilTime)))
                    return Success;
            } else {
                if (0 == waitMilliseconds) {
                    if (!(err =  pthread_mutex_trylock(mutex)))
                        return Success;
                } else {
                    if (!(err =  pthread_mutex_lock(mutex)))
                        return Success;
                }
            }
            switch(err) {
            case ETIMEDOUT:
                return Busy;
            case EINTR:
                return Interrupted;
            }
        }
        return Failed; 
#else // defined(PTHREAD_MUTEX_HAS_TIMEDLOCK)
        return Invalid; 
#endif // defined(PTHREAD_MUTEX_HAS_TIMEDLOCK)
    }
protected:
    pthread_mutexattr_t* m_mutexattrAttachedTo;
    pthread_mutexattr_t m_mutexattr;
    pthread_mutex_t m_mutex;
};

} // namespace unix 
} // namespace xos 

#endif // _XOS_OS_UNIX_MUTEX_HPP 
