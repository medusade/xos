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
///   File: Servlet.hpp
///
/// Author: $author$
///   Date: 2/24/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_JAVAX_SERVLET_SERVLET_HPP
#define _XOS_JAVAX_SERVLET_SERVLET_HPP

#include "xos/jdk/javax/servlet/ServletRequest.hpp"
#include "xos/jdk/javax/servlet/ServletResponse.hpp"
#include "xos/jdk/javax/servlet/ServletConfig.hpp"
#include "xos/jdk/java/lang/String.hpp"
#include "xos/base/Base.hpp"

namespace xos {
namespace javax {
namespace servlet {

typedef InterfaceBase ServletImplement;
///////////////////////////////////////////////////////////////////////
///  Class: Servlet
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Servlet: virtual public ServletImplement {
public:
    typedef ServletImplement Implements;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool init(const ServletConfig& config) = 0;
    virtual bool destroy() = 0;
    virtual bool service(const ServletRequest& req, ServletResponse& resp) = 0;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const ServletConfig& getServletConfig() const = 0;
    virtual java::lang::String getServletInfo() const = 0;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

typedef Servlet NullServletImplement;
typedef ExportBase NullServletExtend;
///////////////////////////////////////////////////////////////////////
///  Class: NullServlet
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS NullServlet: virtual public NullServletImplement,public NullServletExtend {
public:
    typedef NullServletImplement Implements;
    typedef NullServletExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    NullServlet() {
    }
    virtual ~NullServlet() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool init(const ServletConfig& config) {
        return true;
    }
    virtual bool destroy() {
        return true;
    }
    virtual bool service(const ServletRequest& req, ServletResponse& resp) {
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const ServletConfig& getServletConfig() const {
        static const NullServletConfig config;
        return config;
    }
    virtual java::lang::String getServletInfo() const {
        return java::lang::String();
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace servlet
} // namespace javax 
} // namespace xos 

#endif // _XOS_JAVAX_SERVLET_SERVLET_HPP 
