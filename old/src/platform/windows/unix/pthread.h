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
///   File: pthread.h
///
/// Author: $author$
///   Date: 10/10/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_WINDOWS_UNIX_PTHREAD_H
#define _XOS_WINDOWS_UNIX_PTHREAD_H

#include "xos/os/windows/Mutex.hpp"
#include "xos/os/windows/Thread.hpp"
#include "xos/base/Reference.hpp"
#include "xos/base/Wrapped.hpp"
#include <sys/time.h>

#define PTHREAD_PROCESS_PRIVATE 0
#define PTHREAD_PROCESS_SHARED  1
#define PTHREAD_SCOPE_PROCESS   PTHREAD_PROCESS_PRIVATE
#define PTHREAD_SCOPE_SYSTEM    PTHREAD_PROCESS_SHARED

#if !defined(_POSIX_TIMEOUTS)
#define _POSIX_TIMEOUTS 1
#endif // !defined(_POSIX_TIMEOUTS)

//
// mutex
//
typedef struct pthread_mutex pthread_mutex_t;
typedef struct pthread_mutexattr pthread_mutexattr_t;

#define PTHREAD_MUTEX_NORMAL     0
#define PTHREAD_MUTEX_ERRORCHECK 1
#define PTHREAD_MUTEX_RECURSIVE  2
#define PTHREAD_MUTEX_DEFAULT    3

int pthread_mutexattr_init(pthread_mutexattr_t* mutexattr);
int pthread_mutexattr_destroy(pthread_mutexattr_t* mutexattr);

int pthread_mutexattr_setpshared(pthread_mutexattr_t* mutexattr, int pshared);
int pthread_mutexattr_getpshared(const pthread_mutexattr_t* attr, int* pshared);

int pthread_mutexattr_settype(pthread_mutexattr_t* mutexattr, int type);
int pthread_mutexattr_gettype(const pthread_mutexattr_t* mutexattr, int* type);

int pthread_mutex_init
(pthread_mutex_t* mutex, const pthread_mutexattr_t* mutexattr);
int pthread_mutex_destroy(pthread_mutex_t* mutex);

int pthread_mutex_lock(pthread_mutex_t* mutex);
int pthread_mutex_unlock(pthread_mutex_t* mutex);

int pthread_mutex_trylock(pthread_mutex_t* mutex);
int pthread_mutex_timedlock
(pthread_mutex_t* mutex, const struct timespec* timespec);

struct pthread_mutexattr {
    xos::Wrapped<SECURITY_ATTRIBUTES> m_attr;
    pthread_mutexattr(): m_attr(0) {}
};
struct pthread_mutex {
    xos::windows::Mutex m_mutex;
    pthread_mutex(): m_mutex(0) {}
};

//
// thread
//
typedef struct pthread_attr pthread_attr_t;
typedef struct pthread pthread_t;

int pthread_attr_init(pthread_attr_t *attr);
int pthread_attr_destroy(pthread_attr_t *attr);

int pthread_create
(pthread_t *thread, const pthread_attr_t *attr,
 void *(*start_routine)(void*), void *arg);
int pthread_join(pthread_t thread, void **value_ptr);

int pthread_tryjoin_np(pthread_t thread, void **value_ptr);
int pthread_timedjoin_np
(pthread_t thread, void **value_ptr, const struct timespec* timespec);

int pthread_detach(pthread_t thread);
void pthread_exit(void *value_ptr);

struct pthread_attr {
    xos::Wrapped<SECURITY_ATTRIBUTES> m_attr;
    pthread_attr(): m_attr(0) {}
};
struct pthread {
    xos::Reference<xos::windows::Thread> m_thread;
    pthread(struct pthread& copy): m_thread(copy.m_thread) {}
    pthread(): m_thread(0) {}
};

namespace xos {

} // namespace xos 

#endif // _XOS_WINDOWS_UNIX_PTHREAD_H 
