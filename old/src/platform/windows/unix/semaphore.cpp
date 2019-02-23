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
///   File: semaphore.cpp
///
/// Author: $author$
///   Date: 10/10/2012
///////////////////////////////////////////////////////////////////////
#include "xos/os/unix/semaphore.hpp"
#include <semaphore.h>

int sem_init(sem_t *sem, int pshared, unsigned int value) { 
    int err = EFAULT;
    if (SEMAPHORE_PROCESS_PRIVATE == (pshared)) {
        if ((sem->m_sem.Create(value))) {
            err = 0;
        }
    } else {
        err = EINVAL;
    }
    return err;
}
int sem_destroy(sem_t *sem) { 
    int err = EFAULT;
    if ((sem->m_sem.Destroy())) {
        err = 0;
    }
    return err;
}
int sem_post(sem_t *sem) { 
    int err = EFAULT;
    if ((sem->m_sem.Release())) {
        err = 0;
    }
    return err;
}
int sem_getvalue(sem_t *sem, int *sval) { 
    return EFAULT; 
}
int sem_wait(sem_t *sem) { 
    int err = EFAULT;
    if ((sem->m_sem.Acquire())) {
        err = 0;
    }
    return err;
}
int sem_trywait(sem_t *sem) { 
    int err = EFAULT;
    xos::Semaphore::Status status;
    if (xos::Semaphore::Success == (status = sem->m_sem.TryAcquire())) {
        err = 0;
    } else {
        switch(status) {
            case xos::Semaphore::Busy:
                err = ETIMEDOUT;
                break;
            case xos::Semaphore::Interrupted:
                err = EINTR;
                break;
        }
    }
    return err;
}
int sem_timedwait(sem_t *sem, const struct timespec* timespec) { 
    int err = EFAULT;
    mseconds_t waitMilliseconds = (timespec->tv_sec*1000)+(timespec->tv_nsec/1000);
    xos::Semaphore::Status status;
    if (xos::Semaphore::Success == (status = sem->m_sem.TimedAcquire(waitMilliseconds))) {
        err = 0;
    } else {
        switch(status) {
            case xos::Semaphore::Busy:
                err = ETIMEDOUT;
                break;
            case xos::Semaphore::Interrupted:
                err = EINTR;
                break;
        }
    }
    return err;
}

namespace xos {

} // namespace xos 
