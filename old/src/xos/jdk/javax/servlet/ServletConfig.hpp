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
///   File: ServletConfig.hpp
///
/// Author: $author$
///   Date: 2/23/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_JAVAX_SERVLET_SERVLETCONFIG_HPP
#define _XOS_JAVAX_SERVLET_SERVLETCONFIG_HPP

#include "xos/jdk/javax/servlet/ServletContext.hpp"
#include "xos/jdk/java/util/Enumeration.hpp"
#include "xos/jdk/java/util/List.hpp"
#include "xos/jdk/java/lang/String.hpp"

namespace xos {
namespace javax {
namespace servlet {

typedef InterfaceBase ServletConfigImplement;
///////////////////////////////////////////////////////////////////////
///  Class: ServletConfig
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS ServletConfig: virtual public ServletConfigImplement {
public:
    typedef ServletConfigImplement Implements;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual java::lang::String getInitParameter(const java::lang::String& name) const = 0;
    virtual java::util::Enumeration<java::lang::String> getInitParameterNames() const = 0;
    virtual const ServletContext& getServletContext() const = 0;
    virtual java::lang::String getServletName() const = 0;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

typedef ServletConfig NullServletConfigImplement;
typedef ExportBase NullServletConfigExtend;
///////////////////////////////////////////////////////////////////////
///  Class: NullServletConfig
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS NullServletConfig
: virtual public NullServletConfigImplement, public NullServletConfigExtend {
public:
    typedef NullServletConfigImplement Implements;
    typedef NullServletConfigExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    NullServletConfig() {
    }
    virtual ~NullServletConfig() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual java::lang::String getInitParameter(const java::lang::String& name) const {
        return java::lang::String();
    }
    virtual java::util::Enumeration<java::lang::String> getInitParameterNames() const {
        return java::util::Enumeration<java::lang::String>();
    }
    virtual const ServletContext& getServletContext() const {
        static const NullServletContext context;
        return context;
    }
    virtual java::lang::String getServletName() const {
        return java::lang::String();
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

typedef NullServletConfigImplement BaseServletConfigImplement;
typedef NullServletConfig BaseServletConfigExtend;
///////////////////////////////////////////////////////////////////////
///  Class: BaseServletConfig
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS BaseServletConfig
: virtual public BaseServletConfigImplement, public BaseServletConfigExtend {
protected:
    ///////////////////////////////////////////////////////////////////////
    /// Struct: InitParameter
    ///////////////////////////////////////////////////////////////////////
    struct InitParameter {
        java::lang::String name;
        java::lang::String value;
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        InitParameter
        (const java::lang::String& p_name,
         const java::lang::String& p_value)
        : name(p_name), value(p_value) {
        }
        InitParameter() {
        }
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
    };
public:
    typedef BaseServletConfigImplement Implements;
    typedef BaseServletConfigExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    BaseServletConfig(const java::lang::String& servletName)
    : m_servletName(servletName) {
    }
    BaseServletConfig() {
    }
    virtual ~BaseServletConfig() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void setServletName(const java::lang::String& servletName) {
        m_servletName = servletName;
    }
    virtual java::lang::String getServletName() const {
        return m_servletName;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void setInitParameter
    (const java::lang::String& name, const java::lang::String& value) {
        java::util::List<InitParameter>::Iterator i = m_initParameters.iterator();
        while (i.hasNext()) {
            java::util::List<InitParameter>::Iterator j = i;
            InitParameter& p = i.next();
            if (!p.name.compareTo(name)) {
                p.value = value;
                return;
            }
        }
        m_initParameters.add(InitParameter(name, value));
    }
    virtual java::lang::String getInitParameter(const java::lang::String& name) const {
        java::util::List<InitParameter>::Iterator i = m_initParameters.iterator();
        while (i.hasNext()) {
            InitParameter p = i.next();
            if (!p.name.compareTo(name))
                return p.value;
        }
        return java::lang::String();
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    java::util::List<InitParameter> m_initParameters;
    java::lang::String m_servletName;
};

} // namespace servlet
} // namespace javax 
} // namespace xos 

#endif // _XOS_JAVAX_SERVLET_SERVLETCONFIG_HPP 
