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
///   File: HttpServletRequest.hpp
///
/// Author: $author$
///   Date: 2/25/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_JAVAX_SERVLET_HTTP_HTTPSERVLETREQUEST_HPP
#define _XOS_JAVAX_SERVLET_HTTP_HTTPSERVLETREQUEST_HPP

#include "xos/jdk/javax/servlet/ServletRequest.hpp"
#include "xos/jdk/javax/servlet/ProtocolHandler.hpp"
#include "xos/jdk/javax/servlet/http/HttpUpgradeHandler.hpp"
#include "xos/jdk/javax/servlet/http/HttpSession.hpp"
#include "xos/jdk/javax/servlet/http/Cookie.hpp"
#include "xos/jdk/javax/servlet/http/Part.hpp"
#include "xos/jdk/java/security/Principal.hpp"
#include "xos/jdk/java/lang/StringBuffer.hpp"
#include "xos/jdk/java/util/Collection.hpp"

namespace xos {
namespace javax {
namespace servlet {
namespace http {

class _EXPORT_CLASS HttpServletResponse;
typedef ServletRequest HttpServletRequestImplement;
///////////////////////////////////////////////////////////////////////
///  Class: HttpServletRequest
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS HttpServletRequest: virtual public HttpServletRequestImplement {
public:
    typedef HttpServletRequestImplement Implements;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual boolean_t authenticate(HttpServletResponse& response) const = 0;
    virtual java::lang::String changeSessionId() const = 0;
    virtual java::lang::String getAuthType() const = 0;
    virtual java::lang::String getContextPath() const = 0;
    virtual java::util::Array<Cookie> getCookies() const = 0;
    virtual long_t getDateHeader(const java::lang::String& name) const = 0;
    virtual java::lang::String getHeader(const java::lang::String& name) const = 0;
    virtual java::util::Enumeration<java::lang::String> getHeaderNames() const = 0;
    virtual java::util::Enumeration<java::lang::String> getHeaders(const java::lang::String& name) const = 0;
    virtual int_t getIntHeader(const java::lang::String& name) const = 0;
    virtual java::lang::String getMethod() const = 0;
    virtual Part& getPart(const java::lang::String& name) const = 0;
    virtual java::util::Collection<Part> getParts() const = 0;
    virtual java::lang::String getPathInfo() const = 0;
    virtual java::lang::String getPathTranslated() const = 0;
    virtual java::lang::String getQueryString() const = 0;
    virtual java::lang::String getRemoteUser() const = 0;
    virtual java::lang::String getRequestedSessionId() const = 0;
    virtual java::lang::String getRequestURI() const = 0;
    virtual java::lang::String getRequestURL() const = 0;
    virtual java::lang::String getServletPath() const = 0;
    virtual HttpSession& getSession() const = 0;
    virtual HttpSession& getSession(boolean_t create) const = 0;
    virtual java::security::Principal& getUserPrincipal() const = 0;
    virtual boolean_t isRequestedSessionIdFromCookie() const = 0;
    virtual boolean_t isRequestedSessionIdFromUrl() const = 0;
    virtual boolean_t isRequestedSessionIdFromURL() const = 0;
    virtual boolean_t isRequestedSessionIdValid() const = 0;
    virtual boolean_t isUserInRole(const java::lang::String& role) const = 0;
    virtual bool login(const java::lang::String& username, const java::lang::String& password) = 0;
    virtual bool logout() = 0;
    virtual HttpUpgradeHandler& upgrade(ProtocolHandler& to) = 0;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

typedef HttpServletRequest NullHttpServletRequestImplement;
typedef NullServletRequest NullHttpServletRequestExtend;
///////////////////////////////////////////////////////////////////////
///  Class: NullHttpServletRequest
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS NullHttpServletRequest
: virtual public NullHttpServletRequestImplement, public NullHttpServletRequestExtend {
public:
    typedef NullHttpServletRequestImplement Implements;
    typedef NullHttpServletRequestExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    NullHttpServletRequest() {
    }
    virtual ~NullHttpServletRequest() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual boolean_t authenticate(HttpServletResponse& response) const {
        return false;
    }
    virtual java::lang::String changeSessionId() const {
        return java::lang::String();
    }
    virtual java::lang::String getAuthType() const {
        return java::lang::String();
    }
    virtual java::lang::String getContextPath() const {
        return java::lang::String();
    }
    virtual java::util::Array<Cookie> getCookies() const {
        return java::util::Array<Cookie>();
    }
    virtual long_t getDateHeader(const java::lang::String& name) const {
        return 0;
    }
    virtual java::lang::String getHeader(const java::lang::String& name) const {
        return java::lang::String();
    }
    virtual java::util::Enumeration<java::lang::String> getHeaderNames() const {
        return java::util::Enumeration<java::lang::String>();
    }
    virtual java::util::Enumeration<java::lang::String> getHeaders(const java::lang::String& name) const {
        return java::util::Enumeration<java::lang::String>();
    }
    virtual int_t getIntHeader(const java::lang::String& name) const {
        return 0;
    }
    virtual java::lang::String getMethod() const {
        return java::lang::String();
    }
    virtual Part& getPart(const java::lang::String& name) const {
        return (Part&)(m_nullPart);
    }
    virtual java::util::Collection<Part> getParts() const {
        return java::util::Collection<Part>();
    }
    virtual java::lang::String getPathInfo() const {
        return java::lang::String();
    }
    virtual java::lang::String getPathTranslated() const {
        return java::lang::String();
    }
    virtual java::lang::String getQueryString() const {
        return java::lang::String();
    }
    virtual java::lang::String getRemoteUser() const {
        return java::lang::String();
    }
    virtual java::lang::String getRequestedSessionId() const {
        return java::lang::String();
    }
    virtual java::lang::String getRequestURI() const {
        return java::lang::String();
    }
    virtual java::lang::String getRequestURL() const {
        return java::lang::String();
    }
    virtual java::lang::String getServletPath() const {
        return java::lang::String();
    }
    virtual HttpSession& getSession() const {
        return (HttpSession&)(m_nullHttpSession);
    }
    virtual HttpSession& getSession(boolean_t create) const {
        return (HttpSession&)(m_nullHttpSession);
    }
    virtual java::security::Principal& getUserPrincipal() const {
        return (java::security::Principal&)(m_nullSecurityPrincipal);
    }
    virtual boolean_t isRequestedSessionIdFromCookie() const {
        return false;
    }
    virtual boolean_t isRequestedSessionIdFromUrl() const {
        return false;
    }
    virtual boolean_t isRequestedSessionIdFromURL() const {
        return false;
    }
    virtual boolean_t isRequestedSessionIdValid() const {
        return false;
    }
    virtual boolean_t isUserInRole(const java::lang::String& role) const {
        return false;
    }
    virtual bool login(const java::lang::String& username, const java::lang::String& password) {
        return false;
    }
    virtual bool logout() {
        return false;
    }
    virtual HttpUpgradeHandler& upgrade(ProtocolHandler& to) {
        return (HttpUpgradeHandler&)(m_nullHttpUpgradeHandler);
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    NullHttpUpgradeHandler m_nullHttpUpgradeHandler;
    java::security::NullPrincipal m_nullSecurityPrincipal;
    HttpSession m_nullHttpSession;
    NullPart m_nullPart;
};

typedef NullHttpServletRequestImplement BaseHttpServletRequestImplement;
typedef NullHttpServletRequest BaseHttpServletRequestExtend;
///////////////////////////////////////////////////////////////////////
///  Class: BaseHttpServletRequest
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS BaseHttpServletRequest
: virtual public BaseHttpServletRequestImplement, public BaseHttpServletRequestExtend {
public:
    typedef BaseHttpServletRequestImplement Implements;
    typedef BaseHttpServletRequestExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    BaseHttpServletRequest() {
    }
    virtual ~BaseHttpServletRequest() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace http
} // namespace servlet
} // namespace javax
} // namespace xos 

#endif // _XOS_JAVAX_SERVLET_HTTP_HTTPSERVLETREQUEST_HPP
