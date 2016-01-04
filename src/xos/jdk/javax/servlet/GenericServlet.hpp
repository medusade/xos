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
///   File: GenericServlet.hpp
///
/// Author: $author$
///   Date: 2/23/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_JAVAX_SERVLET_GENERICSERVLET_HPP
#define _XOS_JAVAX_SERVLET_GENERICSERVLET_HPP

#include "xos/jdk/javax/servlet/Servlet.hpp"
#include "xos/jdk/java/io/Serializable.hpp"
#include "xos/jdk/java/lang/Object.hpp"
#include "xos/jdk/java/util/Enumeration.hpp"

namespace xos {
namespace javax {
namespace servlet {

///////////////////////////////////////////////////////////////////////
///  Class: GenericServletImplement
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS GenericServletImplement
: virtual public Servlet,
  virtual public ServletConfig,
  virtual public java::io::Serializable {
public:
};
typedef java::lang::Object GenericServletExtend;
///////////////////////////////////////////////////////////////////////
///  Class: GenericServlet
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS GenericServlet
: virtual public GenericServletImplement, public GenericServletExtend {
public:
    typedef GenericServletImplement Implements;
    typedef GenericServletExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    GenericServlet() {
    }
    virtual ~GenericServlet() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual java::lang::String getInitParameter(const java::lang::String& name) const {
        return m_nullString;
    }
    virtual java::util::Enumeration<java::lang::String> getInitParameterNames() const {
        return m_nullNames;
    }
    virtual const ServletContext& getServletContext() const {
        return m_nullContext;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool init(const ServletConfig& config) {
        bool success = true;
        return success;
    }
    virtual bool destroy() {
        bool success = true;
        return success;
    }
    virtual bool service(const ServletRequest& req, ServletResponse& resp) {
        bool serviced = false;
        return serviced;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const ServletConfig& getServletConfig() const {
        return m_nullConfig;
    }
    virtual java::lang::String getServletInfo() const {
        return m_nullString;
    }
    virtual java::lang::String getServletName() const {
        return m_nullString;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    const java::lang::String m_nullString;
    const java::util::Enumeration<java::lang::String> m_nullNames;
    const NullServletContext m_nullContext;
    const NullServletConfig m_nullConfig;
};

} // namespace servlet
} // namespace javax 
} // namespace xos 

#endif // _XOS_JAVAX_SERVLET_GENERICSERVLET_HPP 
