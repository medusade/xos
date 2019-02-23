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
///   File: ServletRequest.hpp
///
/// Author: $author$
///   Date: 3/2/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_INET_HTTP_SERVER_JAVAX_SERVLETREQUEST_HPP
#define _XOS_INET_HTTP_SERVER_JAVAX_SERVLETREQUEST_HPP

#include "xos/jdk/javax/servlet/http/HttpServletRequest.hpp"
#include "xos/inet/http/Request.hpp"
#include "xos/base/Wrapper.hpp"

namespace xos {
namespace http {
namespace server {
namespace javax {

typedef xos::javax::servlet::http::BaseHttpServletRequestImplement ServletRequestImplement;
typedef Wrapper
<const xos::http::Request, xos::javax::servlet::http::BaseHttpServletRequest,
 ServletRequestImplement> ServletRequestExtend;
///////////////////////////////////////////////////////////////////////
///  Class: ServletRequest
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS ServletRequest
: virtual public ServletRequestImplement, public ServletRequestExtend {
public:
    typedef ServletRequestImplement Implements;
    typedef ServletRequestExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    ServletRequest(const xos::http::Request& request): Extends(request) {
    }
    virtual ~ServletRequest() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual java::lang::String getMethod() const {
        return java::lang::String(m_wrapped.GetMethod().Chars());
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace javax 
} // namespace server 
} // namespace http 
} // namespace xos 

#endif // _XOS_INET_HTTP_SERVER_JAVAX_SERVLETREQUEST_HPP 
