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
///   File: mach.h
///
/// Author: $author$
///   Date: 10/14/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_WINDOWS_MACOSX_MACH_MACH_H
#define _XOS_WINDOWS_MACOSX_MACH_MACH_H

#include "xos/base/Base.hpp"
#include <sys/time.h>

#define KERN_SUCCESS 0
#define KERN_INVALID_ARGUMENT 1
#define KERN_RESOURCE_SHORTAGE 2
#define KERN_INVALID_RIGHT 3
#define KERN_TERMINATED 4
#define KERN_ABORTED 5

#define SYNC_POLICY_FIFO 0
#define SYNC_POLICY_FIXED_PRIORITY 1

typedef int kern_return_t;
typedef int sync_policy_t;
typedef timespec_t mach_timespec_t;

namespace xos {

} // namespace xos 

#endif // _XOS_WINDOWS_MACOSX_MACH_MACH_H 
