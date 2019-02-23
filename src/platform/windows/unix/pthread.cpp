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
///   File: pthread.cpp
///
/// Author: $author$
///   Date: 10/10/2012
///////////////////////////////////////////////////////////////////////
#include "xos/os/unix/Mutex.hpp"
#include <pthread.h>
#include <errno.h>

//
// mutex
//

int pthread_mutexattr_init
(pthread_mutexattr_t* mutexattr)
{
    int err = 0;
    return err;
}
int pthread_mutexattr_destroy
(pthread_mutexattr_t* mutexattr)
{
    int err = 0;
    return err;
}
int pthread_mutexattr_settype
(pthread_mutexattr_t* mutexattr, int type)
{
    int err = EINVAL;
    return err;
}
int pthread_mutexattr_gettype
(const pthread_mutexattr_t* mutexattr, int* type)
{
    int err = EINVAL;
    return err;
}
int pthread_mutexattr_setpshared
(pthread_mutexattr_t* mutexattr, int type)
{
    int err = EINVAL;
    return err;
}
int pthread_mutexattr_getpshared
(const pthread_mutexattr_t* mutexattr, int* type)
{
    int err = EINVAL;
    return err;
}

int pthread_mutex_init
(pthread_mutex_t* mutex, 
 const pthread_mutexattr_t* mutexattr)
{
    int err = EFAULT;
    if ((mutex->m_mutex.Create())) {
        err = 0;
    }
    return err;
}
int pthread_mutex_destroy
(pthread_mutex_t* mutex)
{
    int err = EFAULT;
    if ((mutex->m_mutex.Destroy())) {
        err = 0;
    }
    return err;
}
int pthread_mutex_lock
(pthread_mutex_t* mutex)
{
    int err = EFAULT;
    if ((mutex->m_mutex.Lock())) {
        err = 0;
    }
    return err;
}
int pthread_mutex_unlock
(pthread_mutex_t* mutex)
{
    int err = EFAULT;
    if ((mutex->m_mutex.Unlock())) {
        err = 0;
    }
    return err;
}
int pthread_mutex_trylock
(pthread_mutex_t* mutex)
{
    int err = EFAULT;
    xos::Mutex::Status status;
    if (xos::Mutex::Success == (status = mutex->m_mutex.TryLock())) {
        err = 0;
    } else {
        switch(status) {
            case xos::Mutex::Busy:
                err = ETIMEDOUT;
                break;
            case xos::Mutex::Interrupted:
                err = EINTR;
                break;
        }
    }
    return err;
}
int pthread_mutex_timedlock
(pthread_mutex_t* mutex, const struct timespec* timespec)
{
    int err = EFAULT;
    mseconds_t waitMilliseconds = (timespec->tv_sec*1000)+(timespec->tv_nsec/1000);
    xos::Mutex::Status status;
    if (xos::Mutex::Success == (status = mutex->m_mutex.TimedLock(waitMilliseconds))) {
        err = 0;
    } else {
        switch(status) {
            case xos::Mutex::Busy:
                err = ETIMEDOUT;
                break;
            case xos::Mutex::Interrupted:
                err = EINTR;
                break;
        }
    }
    return err;
}

//
// thread
//

namespace xos {
namespace windows {
namespace unix {

class Thread: public xos::windows::Thread {
public:
    typedef xos::windows::Thread Extends;
    class Run: public xos::Thread::Run {
    public:
        Run(void* (*start_routine)(void*), void* arg)
        : m_start_routine(start_routine), m_arg(arg) {}
        virtual void operator()(){
            (*m_start_routine)(m_arg);
        }
    protected:
        void* (*m_start_routine)(void*);
        void* m_arg;
    };
    Thread(Run*& run, void* (*start_routine)(void*), void* arg)
    : Extends(*(run = new Run(start_routine, arg))) {
        m_run = run;
    }
    virtual ~Thread() {
        if ((m_run)) {
            if ((Closed())) {
                delete m_run;
            }
        }
    }
protected:
    Run* m_run;
};

} // namespace unix 
} // namespace windows 
} // namespace xos 

int pthread_attr_init(pthread_attr_t *attr)
{
    int err = 0;
    return err;
}
int pthread_attr_destroy(pthread_attr_t *attr)
{
    int err = 0;
    return err;
}

int pthread_create
(pthread_t *thread, const pthread_attr_t *attr,
 void *(*start_routine)(void*), void *arg)
{
    xos::windows::unix::Thread::Run* run = 0;
    int err = EINVAL;
    if ((thread->m_thread.Set(new xos::windows::unix::Thread(run, start_routine, arg)))) {
        err = 0;
    }
    return err;
}
int pthread_join
(pthread_t thread, void **value_ptr)
{
    int err = EINVAL;
    if ((thread.m_thread)) {
        if ((thread.m_thread->Join())) {
            thread.m_thread.Clear();
            value_ptr = 0;
            err = 0;
        }
    } else {
        err = 0;
    }
    return err;
}

int pthread_tryjoin_np(pthread_t thread, void **value_ptr)
{
    int err = EINVAL;
    xos::Thread::Status status;
    if (xos::Thread::Success == (status = thread.m_thread->TryJoin())) {
        thread.m_thread.Clear();
        value_ptr = 0;
        err = 0;
    } else {
        switch(status) {
            case xos::Thread::Busy:
                err = ETIMEDOUT;
                break;
            case xos::Thread::Interrupted:
                err = EINTR;
                break;
        }
    }
    return err;
}
int pthread_timedjoin_np
(pthread_t thread, void **value_ptr, const struct timespec* timespec)
{
    int err = EINVAL;
    mseconds_t waitMilliseconds = (timespec->tv_sec*1000)+(timespec->tv_nsec/1000);
    xos::Thread::Status status;
    if (xos::Thread::Success == (status = thread.m_thread->TimedJoin(waitMilliseconds))) {
        thread.m_thread.Clear();
        value_ptr = 0;
        err = 0;
    } else {
        switch(status) {
            case xos::Thread::Busy:
                err = ETIMEDOUT;
                break;
            case xos::Thread::Interrupted:
                err = EINTR;
                break;
        }
    }
    return err;
}

int pthread_detach(pthread_t thread)
{
    int err = EINVAL;
    return err;
}
void pthread_exit(void *value_ptr)
{
}

namespace xos {
namespace unix {

} // namespace unix 
} // namespace xos 
