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
///   File: Libwebsockets.hpp
///
/// Author: $author$
///   Date: 12/30/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_HTTP_SERVER_LIBWEBSOCKETS_LIBWEBSOCKETS_HPP
#define _XOS_HTTP_SERVER_LIBWEBSOCKETS_LIBWEBSOCKETS_HPP

#include "xos/base/Base.hpp"

#if defined(WINDOWS)
#define ssize_t lws_size_t
#include <libwebsockets.h>
#undef lws_size_t
#else // defined(WINDOWS)
#include <libwebsockets.h>
#endif // defined(WINDOWS)

namespace xos {
namespace http {
namespace server {
namespace libwebsockets {

} // namespace libwebsockets 
} // namespace server 
} // namespace http 
} // namespace xos 

#endif // _XOS_HTTP_SERVER_LIBWEBSOCKETS_LIBWEBSOCKETS_HPP 
