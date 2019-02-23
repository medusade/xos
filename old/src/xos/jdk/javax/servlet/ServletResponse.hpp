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
///   File: ServletResponse.hpp
///
/// Author: $author$
///   Date: 2/23/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_JAVAX_SERVLET_SERVLETRESPONSE_HPP
#define _XOS_JAVAX_SERVLET_SERVLETRESPONSE_HPP

#include "xos/jdk/javax/servlet/ServletOutputStream.hpp"
#include "xos/jdk/java/io/PrintWriter.hpp"
#include "xos/jdk/java/util/Locale.hpp"
#include "xos/jdk/java/lang/String.hpp"
#include "xos/jdk/java/Types.hpp"
#include "xos/base/Base.hpp"

namespace xos {
namespace javax {
namespace servlet {

typedef InterfaceBase ServletResponseImplement;
///////////////////////////////////////////////////////////////////////
///  Class: ServletResponse
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS ServletResponse: virtual public ServletResponseImplement {
public:
    typedef ServletResponseImplement Implements;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool flushBuffer() = 0;
    virtual int_t getBufferSize() const = 0;
    virtual java::lang::String getCharacterEncoding() const = 0;
    virtual java::lang::String getContentType() const = 0;
    virtual java::util::Locale getLocale() const = 0;
    virtual ServletOutputStream& getOutputStream() const = 0;
    virtual java::io::PrintWriter& getWriter() const = 0;
    virtual boolean_t isCommitted() const = 0;
    virtual bool reset() = 0;
    virtual bool resetBuffer() = 0;
    virtual bool setBufferSize(int_t size) = 0;
    virtual bool setCharacterEncoding(const java::lang::String& charset) = 0;
    virtual bool setContentLength(int_t len) = 0;
    virtual bool setContentLengthLong(long_t len) = 0;
    virtual bool setContentType(const java::lang::String& type) = 0;
    virtual bool setLocale(const java::util::Locale& loc) = 0;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

typedef ServletResponse NullServletResponseImplement;
typedef ExportBase NullServletResponseExtend;
///////////////////////////////////////////////////////////////////////
///  Class: NullServletResponse
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS NullServletResponse: virtual public NullServletResponseImplement,public NullServletResponseExtend {
public:
    typedef NullServletResponseImplement Implements;
    typedef NullServletResponseExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    NullServletResponse() {
    }
    virtual ~NullServletResponse() {
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
protected:
    NullServletOutputStream m_nullStream;
    java::io::NullPrintWriter m_nullWriter;
};

///////////////////////////////////////////////////////////////////////
///  Class: ServletResponseBase
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS ServletResponseBase
: virtual public NullServletResponseImplement, public NullServletResponse {
public:
    typedef NullServletResponseImplement Implements;
    typedef NullServletResponse Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    ServletResponseBase() {
    }
    virtual ~ServletResponseBase() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace servlet
} // namespace javax 
} // namespace xos 

#endif // _XOS_JAVAX_SERVLET_SERVLETRESPONSE_HPP 
