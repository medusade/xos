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
///   File: HttpServletResponse.hpp
///
/// Author: $author$
///   Date: 2/25/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_JAVAX_SERVLET_HTTP_HTTPSERVLETRESPONSE_HPP
#define _XOS_JAVAX_SERVLET_HTTP_HTTPSERVLETRESPONSE_HPP

#include "xos/jdk/javax/servlet/ServletResponse.hpp"
#include "xos/jdk/javax/servlet/http/Cookie.hpp"
#include "xos/jdk/java/util/Collection.hpp"

namespace xos {
namespace javax {
namespace servlet {
namespace http {

typedef ServletResponse HttpServletResponseImplement;
///////////////////////////////////////////////////////////////////////
///  Class: HttpServletResponse
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS HttpServletResponse: virtual public HttpServletResponseImplement {
public:
    typedef HttpServletResponseImplement Implements;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool addCookie(const Cookie& cookie) = 0;
    virtual bool addDateHeader(const java::lang::String& name, long_t date) = 0;
    virtual bool addHeader(const java::lang::String& name, const java::lang::String& value) = 0;
    virtual bool addIntHeader(const java::lang::String& name, int_t value) = 0;
    virtual boolean_t containsHeader(const java::lang::String& name) const = 0;
    virtual java::lang::String encodeRedirectUrl(const java::lang::String& url) = 0;
    virtual java::lang::String encodeRedirectURL(const java::lang::String& url) = 0;
    virtual java::lang::String encodeUrl(const java::lang::String& url) = 0;
    virtual java::lang::String encodeURL(const java::lang::String& url) = 0;
    virtual java::lang::String getHeader(const java::lang::String& name) const = 0;
    virtual java::util::Collection<java::lang::String> getHeaderNames() const = 0;
    virtual java::util::Collection<java::lang::String> getHeaders(const java::lang::String& name) const = 0;
    virtual int_t getStatus() const = 0;
    virtual bool sendError(int_t sc) = 0;
    virtual bool sendError(int_t sc, const java::lang::String& msg) = 0;
    virtual bool sendRedirect(const java::lang::String& location) = 0;
    virtual bool setDateHeader(const java::lang::String& name, long_t date) = 0;
    virtual bool setHeader(const java::lang::String& name, const java::lang::String& value) = 0;
    virtual bool setIntHeader(const java::lang::String& name, int_t value) = 0;
    virtual bool setStatus(int_t sc) = 0;
    virtual bool setStatus(int_t sc, const java::lang::String& msg) = 0;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

typedef HttpServletResponse NullHttpServletResponseImplement;
typedef NullServletResponse NullHttpServletResponseExtend;
///////////////////////////////////////////////////////////////////////
///  Class: NullHttpServletResponse
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS NullHttpServletResponse
: virtual public NullHttpServletResponseImplement, public NullHttpServletResponseExtend {
public:
    typedef NullHttpServletResponseImplement Implements;
    typedef NullHttpServletResponseExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    NullHttpServletResponse() {
    }
    virtual ~NullHttpServletResponse() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool addCookie(const Cookie& cookie) {
        return false;
    }
    virtual bool addDateHeader(const java::lang::String& name, long_t date) {
        return false;
    }
    virtual bool addHeader(const java::lang::String& name, const java::lang::String& value) {
        return false;
    }
    virtual bool addIntHeader(const java::lang::String& name, int_t value) {
        return false;
    }
    virtual boolean_t containsHeader(const java::lang::String& name) const {
        return false;
    }
    virtual java::lang::String encodeRedirectUrl(const java::lang::String& url) {
        return java::lang::String();
    }
    virtual java::lang::String encodeRedirectURL(const java::lang::String& url) {
        return java::lang::String();
    }
    virtual java::lang::String encodeUrl(const java::lang::String& url) {
        return java::lang::String();
    }
    virtual java::lang::String encodeURL(const java::lang::String& url) {
        return java::lang::String();
    }
    virtual java::lang::String getHeader(const java::lang::String& name) const {
        return java::lang::String();
    }
    virtual java::util::Collection<java::lang::String> getHeaderNames() const {
        return java::util::Collection<java::lang::String>();
    }
    virtual java::util::Collection<java::lang::String> getHeaders(const java::lang::String& name) const {
        return java::util::Collection<java::lang::String>();
    }
    virtual int_t getStatus() const {
        return 0;
    }
    virtual bool sendError(int_t sc) {
        return false;
    }
    virtual bool sendError(int_t sc, const java::lang::String& msg) {
        return false;
    }
    virtual bool sendRedirect(const java::lang::String& location) {
        return false;
    }
    virtual bool setDateHeader(const java::lang::String& name, long_t date) {
        return false;
    }
    virtual bool setHeader(const java::lang::String& name, const java::lang::String& value) {
        return false;
    }
    virtual bool setIntHeader(const java::lang::String& name, int_t value) {
        return false;
    }
    virtual bool setStatus(int_t sc) {
        return false;
    }
    virtual bool setStatus(int_t sc, const java::lang::String& msg) {
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool flushBuffer() {
        return false;
    }
    virtual int_t getBufferSize() const {
        return 0;
    }
    virtual java::lang::String getCharacterEncoding() const {
        return java::lang::String();
    }
    virtual java::lang::String getContentType() const {
        return java::lang::String();
    }
    virtual java::util::Locale getLocale() const {
        return java::util::NullLocale();
    }
    virtual ServletOutputStream& getOutputStream() const {
        return (ServletOutputStream&)(m_nullStream);
    }
    virtual java::io::PrintWriter& getWriter() const {
        return (java::io::NullPrintWriter&)(m_nullWriter);
    }
    virtual boolean_t isCommitted() const {
        return false;
    }
    virtual bool reset() {
        return false;
    }
    virtual bool resetBuffer() {
        return false;
    }
    virtual bool setBufferSize(int_t size) {
        return false;
    }
    virtual bool setCharacterEncoding(const java::lang::String& charset) {
        return false;
    }
    virtual bool setContentLength(int_t len) {
        return false;
    }
    virtual bool setContentLengthLong(long_t len) {
        return false;
    }
    virtual bool setContentType(const java::lang::String& type) {
        return false;
    }
    virtual bool setLocale(const java::util::Locale& loc) {
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

typedef NullHttpServletResponseImplement BaseHttpServletResponseImplement;
typedef NullHttpServletResponse BaseHttpServletResponseExtend;
///////////////////////////////////////////////////////////////////////
///  Class: BaseHttpServletResponse
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS BaseHttpServletResponse
: virtual public BaseHttpServletResponseImplement, public BaseHttpServletResponseExtend {
public:
    typedef BaseHttpServletResponseImplement Implements;
    typedef BaseHttpServletResponseExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    BaseHttpServletResponse() {
    }
    virtual ~BaseHttpServletResponse() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace http
} // namespace servlet 
} // namespace javax 
} // namespace xos 

#endif // _XOS_JAVAX_SERVLET_HTTP_HTTPSERVLETRESPONSE_HPP 
