///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2013 $organization$
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
///   File: Time.hpp
///
/// Author: $author$
///   Date: 12/25/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_OS_OS_TIME_HPP
#define _XOS_OS_OS_TIME_HPP

#include "xos/os/os/Os.hpp"

#if defined(WINDOWS)
// Windows
#include "xos/os/windows/Time.hpp"
#else // defined(WINDOWS)
// Unix
#include "xos/os/unix/Time.hpp"
#endif // defined(WINDOWS)

namespace xos {
namespace os {

typedef os::Time Time;

} // namespace os
} // namespace xos 

#endif // _XOS_OS_OS_TIME_HPP 
