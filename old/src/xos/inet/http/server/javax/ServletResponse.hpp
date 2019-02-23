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
///   Date: 3/2/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_INET_HTTP_SERVER_JAVAX_SERVLETRESPONSE_HPP
#define _XOS_INET_HTTP_SERVER_JAVAX_SERVLETRESPONSE_HPP

#include "xos/jdk/javax/servlet/http/HttpServletResponse.hpp"
#include "xos/inet/http/Response.hpp"
#include "xos/base/Wrapper.hpp"

namespace xos {
namespace http {
namespace server {
namespace javax {

typedef xos::javax::servlet::http::BaseHttpServletResponseImplement ServletResponseImplement;
typedef Wrapper
<xos::http::Response, xos::javax::servlet::http::BaseHttpServletResponse,
 ServletResponseImplement> ServletResponseExtend;
///////////////////////////////////////////////////////////////////////
///  Class: ServletResponse
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS ServletResponse
: virtual public ServletResponseImplement, public ServletResponseExtend {
public:
    typedef ServletResponseImplement Implements;
    typedef ServletResponseExtend Extends;

    typedef xos::java::io::BasePrintWriterImplement MessagePrintWriterImplement;
    typedef Wrapper
    <Message, xos::java::io::BasePrintWriter,
     MessagePrintWriterImplement> MessagePrintWriterExtend;
    ///////////////////////////////////////////////////////////////////////
    ///  Class: MessagePrintWriter
    ///////////////////////////////////////////////////////////////////////
    class _EXPORT_CLASS MessagePrintWriter
    : virtual public MessagePrintWriterImplement, public MessagePrintWriterExtend {
    public:
        typedef MessagePrintWriterImplement Implements;
        typedef MessagePrintWriterExtend Extends;
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        MessagePrintWriter(Message& message): Extends(message) {
        }
        virtual ~MessagePrintWriter() {
        }
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        virtual ssize_t print(java::char_t c) {
            size_t oldLength = m_wrapped.Length();
            m_wrapped.Append(&c, 1);
            return (m_wrapped.Length() - oldLength);
        }
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
    };

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    ServletResponse(xos::http::Response& response)
    : Extends(response), m_messagePrintWriter(m_wrapped.message()) {
    }
    virtual ~ServletResponse() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool setContentLength(java::int_t len) {
        m_wrapped.SetContentLengthNo(len);
        return true;
    }
    virtual bool setContentType(const java::lang::String& type) {
        m_wrapped.SetContentType(String(type));
        return true;
    }
    virtual java::io::PrintWriter& getWriter() const {
        return (MessagePrintWriter&)(m_messagePrintWriter);
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    MessagePrintWriter m_messagePrintWriter;
};

} // namespace javax 
} // namespace server 
} // namespace http 
} // namespace xos 

#endif // _XOS_INET_HTTP_SERVER_JAVAX_SERVLETRESPONSE_HPP 
