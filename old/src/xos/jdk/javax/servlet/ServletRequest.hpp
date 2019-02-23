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
///   Date: 2/23/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_JAVAX_SERVLET_SERVLETREQUEST_HPP
#define _XOS_JAVAX_SERVLET_SERVLETREQUEST_HPP

#include "xos/jdk/javax/servlet/RequestDispatcher.hpp"
#include "xos/jdk/javax/servlet/ServletInputStream.hpp"
#include "xos/jdk/javax/servlet/AsyncContext.hpp"
#include "xos/jdk/javax/servlet/DispatcherType.hpp"
#include "xos/jdk/java/util/Locale.hpp"
#include "xos/jdk/java/util/Array.hpp"
#include "xos/jdk/java/util/Map.hpp"
#include "xos/jdk/java/util/Enumeration.hpp"
#include "xos/jdk/java/io/BufferedReader.hpp"
#include "xos/jdk/java/io/InputStream.hpp"
#include "xos/jdk/java/lang/Object.hpp"
#include "xos/jdk/java/lang/String.hpp"
#include "xos/base/Base.hpp"

namespace xos {
namespace javax {
namespace servlet {

class _EXPORT_CLASS ServletResponse;
typedef InterfaceBase ServletRequestImplement;
///////////////////////////////////////////////////////////////////////
///  Class: ServletRequest
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS ServletRequest: virtual public ServletRequestImplement {
public:
    typedef ServletRequestImplement Implements;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual AsyncContext& getAsyncContext() const = 0;
    virtual java::lang::Object getAttribute(const java::lang::String& name) const = 0;
    virtual java::util::Enumeration<java::lang::String> getAttributeNames() const = 0;
    virtual java::lang::String getCharacterEncoding() const = 0;
    virtual int_t getContentLength() const = 0;
    virtual long_t getContentLengthLong() const = 0;
    virtual java::lang::String getContentType() const = 0;
    virtual DispatcherType getDispatcherType() const = 0;
    virtual ServletInputStream& getInputStream() const = 0;
    virtual java::lang::String getLocalAddr() const = 0;
    virtual java::util::Locale getLocale() const = 0;
    virtual java::util::Enumeration<java::util::Locale> getLocales() const = 0;
    virtual java::lang::String getLocalName() const = 0;
    virtual int_t getLocalPort() const = 0;
    virtual java::lang::String getParameter(const java::lang::String& name) const = 0;
    virtual java::util::Map<java::lang::String, java::util::Array<java::lang::String> > getParameterMap() const = 0;
    virtual java::util::Enumeration<java::lang::String> getParameterNames() const = 0;
    virtual java::util::Array<java::lang::String> getParameterValues(const java::lang::String& name) const = 0;
    virtual java::lang::String getProtocol() const = 0;
    virtual java::io::BufferedReader& getReader() const = 0;
    virtual java::lang::String getRealPath(const java::lang::String& path) const = 0;
    virtual java::lang::String getRemoteAddr() const = 0;
    virtual java::lang::String getRemoteHost() const = 0;
    virtual int_t getRemotePort() const = 0;
    virtual RequestDispatcher& getRequestDispatcher(const java::lang::String& path) const = 0;
    virtual java::lang::String getScheme() const = 0;
    virtual java::lang::String getServerName() const = 0;
    virtual int_t getServerPort() const = 0;
    virtual boolean_t isAsyncStarted() const = 0;
    virtual boolean_t isAsyncSupported() const = 0;
    virtual boolean_t isSecure() const = 0;
    virtual bool removeAttribute(const java::lang::String& name) = 0;
    virtual bool setAttribute(const java::lang::String& name, const java::lang::Object& value) = 0;
    virtual bool setCharacterEncoding(const java::lang::String& value) = 0;
    virtual AsyncContext& setAsync() = 0;
    virtual AsyncContext& startAsync
    (const ServletRequest& servletRequest, ServletResponse& servletResponse) = 0;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

typedef ServletRequest NullServletRequestImplement;
typedef ExportBase NullServletRequestExtend;
///////////////////////////////////////////////////////////////////////
///  Class: NullServletRequest
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS NullServletRequest
: virtual public NullServletRequestImplement, public NullServletRequestExtend {
public:
    typedef NullServletRequestImplement Implements;
    typedef NullServletRequestExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    NullServletRequest() {
    }
    virtual ~NullServletRequest() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual AsyncContext& getAsyncContext() const {
        return (AsyncContext&)(m_nullContext);
    }
    virtual java::lang::Object getAttribute(const java::lang::String& name) const {
        return java::lang::NullObject();
    }
    virtual java::util::Enumeration<java::lang::String> getAttributeNames() const {
        return java::util::Enumeration<java::lang::String>();
    }
    virtual java::lang::String getCharacterEncoding() const {
        return java::lang::String();
    }
    virtual int_t getContentLength() const {
        return 0;
    }
    virtual long_t getContentLengthLong() const {
        return 0;
    }
    virtual java::lang::String getContentType() const {
        return java::lang::String();
    }
    virtual DispatcherType getDispatcherType() const {
        return NullDispatcherType();
    }
    virtual ServletInputStream& getInputStream() const {
        return (ServletInputStream&)(m_nullInputStream);
    }
    virtual java::lang::String getLocalAddr() const {
        return java::lang::String();
    }
    virtual java::util::Locale getLocale() const {
        return java::util::Locale();
    }
    virtual java::util::Enumeration<java::util::Locale> getLocales() const {
        return java::util::Enumeration<java::util::Locale>();
    }
    virtual java::lang::String getLocalName() const {
        return java::lang::String();
    }
    virtual int_t getLocalPort() const {
        return 0;
    }
    virtual java::lang::String getParameter(const java::lang::String& name) const {
        return java::lang::String();
    }
    virtual java::util::Map<java::lang::String, java::util::Array<java::lang::String> > getParameterMap() const {
        return java::util::Map<java::lang::String, java::util::Array<java::lang::String> >();
    }
    virtual java::util::Enumeration<java::lang::String> getParameterNames() const {
        return java::util::Enumeration<java::lang::String>();
    }
    virtual java::util::Array<java::lang::String> getParameterValues(const java::lang::String& name) const {
        return java::util::Array<java::lang::String>();
    }
    virtual java::lang::String getProtocol() const {
        return java::lang::String();
    }
    virtual java::io::BufferedReader& getReader() const {
        return (java::io::BufferedReader&)(m_nullReader);
    }
    virtual java::lang::String getRealPath(const java::lang::String& path) const {
        return java::lang::String();
    }
    virtual java::lang::String getRemoteAddr() const {
        return java::lang::String();
    }
    virtual java::lang::String getRemoteHost() const {
        return java::lang::String();
    }
    virtual int_t getRemotePort() const {
        return 0;
    }
    virtual RequestDispatcher& getRequestDispatcher(const java::lang::String& path) const {
        return (RequestDispatcher&)(m_nullDispatcher);
    }
    virtual java::lang::String getScheme() const {
        return java::lang::String();
    }
    virtual java::lang::String getServerName() const {
        return java::lang::String();
    }
    virtual int_t getServerPort() const {
        return 0;
    }
    virtual boolean_t isAsyncStarted() const {
        return false;
    }
    virtual boolean_t isAsyncSupported() const {
        return false;
    }
    virtual boolean_t isSecure() const {
        return false;
    }
    virtual bool removeAttribute(const java::lang::String& name) {
        return false;
    }
    virtual bool setAttribute(const java::lang::String& name, const java::lang::Object& value) {
        return false;
    }
    virtual bool setCharacterEncoding(const java::lang::String& value) {
        return false;
    }
    virtual AsyncContext& setAsync() {
        return (AsyncContext&)(m_nullContext);
    }
    virtual AsyncContext& startAsync
    (const ServletRequest& servletRequest, ServletResponse& servletResponse) {
        return (AsyncContext&)(m_nullContext);
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    NullAsyncContext m_nullContext;
    NullServletInputStream m_nullInputStream;
    java::io::NullBufferedReader m_nullReader;
    NullRequestDispatcher m_nullDispatcher;
};

///////////////////////////////////////////////////////////////////////
///  Class: ServletRequestBase
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS ServletRequestBase
: virtual public NullServletRequestImplement, public NullServletRequest {
public:
    typedef NullServletRequestImplement Implements;
    typedef NullServletRequest Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    ServletRequestBase() {
    }
    virtual ~ServletRequestBase() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace servlet
} // namespace javax 
} // namespace xos 

#endif // _XOS_JAVAX_SERVLET_SERVLETREQUEST_HPP 
