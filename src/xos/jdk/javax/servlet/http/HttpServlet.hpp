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
///   File: HttpServlet.hpp
///
/// Author: $author$
///   Date: 2/23/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_JAVAX_SERVLET_HTTP_HTTPSERVLET_HPP
#define _XOS_JAVAX_SERVLET_HTTP_HTTPSERVLET_HPP

#include "xos/jdk/javax/servlet/http/HttpServletRequest.hpp"
#include "xos/jdk/javax/servlet/http/HttpServletResponse.hpp"
#include "xos/jdk/javax/servlet/GenericServlet.hpp"
#include "xos/inet/http/Request.hpp"

namespace xos {
namespace javax {
namespace servlet {
namespace http {

typedef GenericServletImplement HttpServletImplement;
typedef GenericServlet HttpServletExtend;
///////////////////////////////////////////////////////////////////////
///  Class: HttpServlet
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS HttpServlet
: virtual public HttpServletImplement, public HttpServletExtend {
public:
    typedef HttpServletImplement Implements;
    typedef HttpServletExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    HttpServlet(const java::lang::String& servletName)
    : m_servletConfig(servletName) {
    }
    HttpServlet() {
    }
    virtual ~HttpServlet() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool service(const HttpServletRequest& req, HttpServletResponse& resp) {
        bool serviced = false;
        xos::http::Request::Method method(req.getMethod());
        switch(method.ToWhich()) {
        case xos::http::Request::Method::Get:
            serviced = doGet(req, resp);
            break;
        case xos::http::Request::Method::Post:
            serviced = doPost(req, resp);
            break;
        case xos::http::Request::Method::Put:
            serviced = doPut(req, resp);
            break;
        case xos::http::Request::Method::Delete:
            serviced = doDelete(req, resp);
            break;
        case xos::http::Request::Method::Connect:
            serviced = doConnect(req, resp);
            break;
        case xos::http::Request::Method::Trace:
            serviced = doTrace(req, resp);
            break;
        case xos::http::Request::Method::Head:
            serviced = doHead(req, resp);
            break;
        case xos::http::Request::Method::Options:
            serviced = doOptions(req, resp);
            break;
        default:
            serviced = doNone(req, resp);
        }
        return serviced;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void setServletName(const java::lang::String& servletName) {
        m_servletConfig.setServletName(servletName);
    }
    virtual java::lang::String getServletName() const {
        return m_servletConfig.getServletName();
    }
protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool doGet(const HttpServletRequest& req, HttpServletResponse& resp) {
        bool serviced = doAny(req, resp);
        return serviced;
    }
    virtual bool doPost(const HttpServletRequest& req, HttpServletResponse& resp) {
        bool serviced = doAny(req, resp);
        return serviced;
    }
    virtual bool doPut(const HttpServletRequest& req, HttpServletResponse& resp) {
        bool serviced = doAny(req, resp);
        return serviced;
    }
    virtual bool doDelete(const HttpServletRequest& req, HttpServletResponse& resp) {
        bool serviced = doAny(req, resp);
        return serviced;
    }
    virtual bool doTrace(const HttpServletRequest& req, HttpServletResponse& resp) {
        bool serviced = doAny(req, resp);
        return serviced;
    }
    virtual bool doConnect(const HttpServletRequest& req, HttpServletResponse& resp) {
        bool serviced = doAny(req, resp);
        return serviced;
    }
    virtual bool doOptions(const HttpServletRequest& req, HttpServletResponse& resp) {
        bool serviced = doAny(req, resp);
        return serviced;
    }
    virtual bool doHead(const HttpServletRequest& req, HttpServletResponse& resp) {
        bool serviced = doAny(req, resp);
        return serviced;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool doAny(const HttpServletRequest& req, HttpServletResponse& resp) {
        bool serviced = false;
        return serviced;
    }
    virtual bool doNone(const HttpServletRequest& req, HttpServletResponse& resp) {
        bool serviced = false;
        return serviced;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    BaseServletConfig m_servletConfig;
};

typedef HttpServletImplement BaseHttpServletImplement;
typedef HttpServlet BaseHttpServletExtend;
///////////////////////////////////////////////////////////////////////
///  Class: BaseHttpServlet
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS BaseHttpServlet
: virtual public BaseHttpServletImplement, public BaseHttpServletExtend {
public:
    typedef BaseHttpServletImplement Implements;
    typedef BaseHttpServletExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    BaseHttpServlet(const java::lang::String& servletName)
    : Extends(servletName) {
    }
    BaseHttpServlet() {
    }
    virtual ~BaseHttpServlet() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace http
} // namespace servlet 
} // namespace javax 
} // namespace xos 

#endif // _XOS_JAVAX_SERVLET_HTTP_HTTPSERVLET_HPP 
