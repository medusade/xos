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
///   File: time.h
///
/// Author: $author$
///   Date: 10/10/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_WINDOWS_UNIX_SYS_TIME_H
#define _XOS_WINDOWS_UNIX_SYS_TIME_H

#include "xos/base/Platform.hpp"
#include <errno.h>

#if !defined(ETIMEDOUT)
#define ETIMEDOUT EBUSY
#endif // !defined(ETIMEDOUT)

#if !defined(_POSIX_TIMERS)
#define _POSIX_TIMERS 1
#endif // !defined(_POSIX_TIMERS)

#if defined(_POSIX_TIMERS) && (_POSIX_TIMERS >= 0)
#define TIME_HAS_CLOCK_GETTIME
#endif /* defined(_POSIX_TIMERS) && (_POSIX_TIMERS >= 0) */

typedef int clockid_t;
enum
{
    CLOCK_REALTIME,
    CLOCK_MONOTONIC
};

typedef struct timespec
{
    time_t tv_sec;
    time_t tv_nsec;
} timespec_t;

int clock_gettime(clockid_t clockid, struct timespec* timespec);
struct tm *localtime_r(const time_t *timep, struct tm *result);
struct tm *gmtime_r(const time_t *timep, struct tm *result);

namespace xos {

} // namespace xos 

#endif // _XOS_WINDOWS_UNIX_SYS_TIME_H 
