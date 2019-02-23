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
///   File: Os.hpp
///
/// Author: $author$
///   Date: 2/18/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_NETWORK_UNIQUE_OS_OS_HPP
#define _XOS_NETWORK_UNIQUE_OS_OS_HPP

#include "xos/base/Base.hpp"

namespace xos {
namespace network {
namespace unique {
namespace windows { }
namespace unix { }
namespace os {

#if defined(WINDOWS)
// Windows
namespace os = windows;
#else // defined(WINDOWS)
// Unix
namespace os = unix;
#endif // defined(WINDOWS)

} // namespace os
} // namespace unique 
} // namespace network 
} // namespace xos 

#endif // _XOS_NETWORK_UNIQUE_OS_OS_HPP 
