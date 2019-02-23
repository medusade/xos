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
///   File: Pthread.hpp
///
/// Author: $author$
///   Date: 10/11/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_OS_UNIX_PTHREAD_HPP
#define _XOS_OS_UNIX_PTHREAD_HPP

#include "xos/base/Base.hpp"
#include <pthread.h>
#include <time.h>
#include <errno.h>

#if defined(_POSIX_TIMEOUTS) && (_POSIX_TIMEOUTS >=0 )
#define PTHREAD_MUTEX_HAS_TIMEDLOCK
#define PTHREAD_COND_HAS_TIMEDWAIT
#define PTHREAD_HAS_TIMEDJOIN
#define PTHREAD_HAS_TRYJOIN
#endif // defined(_POSIX_TIMEOUTS) && (_POSIX_TIMEOUTS >=0 )

namespace xos {
namespace unix {

} // namespace unix 
} // namespace xos 

#endif // _XOS_OS_UNIX_PTHREAD_HPP 
