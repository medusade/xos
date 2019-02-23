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
///   File: RootHttpServlet.hpp
///
/// Author: $author$
///   Date: 3/2/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_JAVAX_SERVLET_HTTP_ROOTHTTPSERVLET_HPP
#define _XOS_JAVAX_SERVLET_HTTP_ROOTHTTPSERVLET_HPP

#include "xos/jdk/javax/servlet/http/HttpServlet.hpp"
#include "xos/os/Logger.hpp"

namespace xos {
namespace javax {
namespace servlet {
namespace http {

typedef BaseHttpServletImplement RootHttpServletImplement;
typedef BaseHttpServlet RootHttpServletExtend;
///////////////////////////////////////////////////////////////////////
///  Class: RootHttpServlet
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS RootHttpServlet
: virtual public RootHttpServletImplement, public RootHttpServletExtend {
public:
    typedef RootHttpServletImplement Implements;
    typedef RootHttpServletExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    RootHttpServlet() {
    }
    virtual ~RootHttpServlet() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool service(const HttpServletRequest& req, HttpServletResponse& resp) {
        bool serviced = false;
        HttpServlet* servlet;
        if ((servlet = getServletToService(req, resp)))
            serviced = servlet->service(req, resp);
        else
        serviced = Extends::service(req, resp);
        return serviced;
    }
    static RootHttpServlet& getTheInstance();
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool doAny(const HttpServletRequest& req, HttpServletResponse& resp) {
        bool serviced = false;
        serviced = doHello(req, resp);
        return serviced;
    }
    virtual bool doHello(const HttpServletRequest& req, HttpServletResponse& resp) {
        java::lang::String contentType("text/html");
        if ((resp.setContentType(contentType))) {
            java::io::PrintWriter& writer = resp.getWriter();
            java::lang::String content("<b>Hello</b><br>\n");
            if (0 < (writer.print(content))) {
                return true;
            } else {
                XOS_LOG_TRACE("failed on writer.print(\"" << content << "\")");
            }
        } else {
            XOS_LOG_TRACE("failed on resp.setContentType(\"" << contentType << "\")");
        }
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual HttpServlet* getServletToService
    (const HttpServletRequest& req, HttpServletResponse& resp) const {
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace http 
} // namespace servlet 
} // namespace javax 
} // namespace xos 

#endif // _XOS_JAVAX_SERVLET_HTTP_ROOTHTTPSERVLET_HPP 
