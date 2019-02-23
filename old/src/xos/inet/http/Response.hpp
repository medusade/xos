///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2013 $organization$
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
///   File: Response.hpp
///
/// Author: $author$
///   Date: 11/23/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_HTTP_RESPONSE_HPP
#define _XOS_HTTP_RESPONSE_HPP

#include "xos/inet/http/Request.hpp"

namespace xos {
namespace http {

typedef String::Implements ResponseImplement;
typedef String ResponseExtend;
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Response: virtual public ResponseImplement, public ResponseExtend {
public:
    typedef ResponseImplement Implements;
    typedef ResponseExtend Extends;

    typedef String::Implements StatusImplement;
    typedef String StatusExtend;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    class _EXPORT_CLASS Status: virtual public StatusImplement, public StatusExtend {
    public:
        typedef StatusImplement Implements;
        typedef StatusExtend Extends;
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        Status(const String& value): Extends(value) {
        }
        Status(const char* value): Extends(value) {
        }
        Status() {
        }
        virtual ~Status() {
        }
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
    };

    typedef String::Implements ReasonImplement;
    typedef String ReasonExtend;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    class _EXPORT_CLASS Reason: virtual public ReasonImplement, public ReasonExtend {
    public:
        typedef ReasonImplement Implements;
        typedef ReasonExtend Extends;
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        Reason(const String& value): Extends(value) {
        }
        Reason(const char* value): Extends(value) {
        }
        Reason() {
        }
        virtual ~Reason() {
        }
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
    };

    typedef String::Implements LineImplement;
    typedef String LineExtend;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    class _EXPORT_CLASS Line: virtual public LineImplement, public LineExtend {
    public:
        typedef LineImplement Implements;
        typedef LineExtend Extends;
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        Line(const Version& version, const Status& status, const Reason& reason)
        : m_version(version), m_status(status), m_reason(reason) {
        }
        Line(const Status& status, const Reason& reason)
        : m_status(status), m_reason(reason) {
        }
        Line(const Version& version)
        : m_version(version) {
        }
        Line() {
        }
        virtual ~Line() {
        }

        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        virtual bool Combine(const Version& version, const Status& status, const Reason& reason) {
            m_version = version;
            m_status = status;
            m_reason = reason;
            return Combine();
        }
        virtual bool Combine(const Status& status, const Reason& reason) {
            m_status = status;
            m_reason = reason;
            return Combine();
        }
        virtual bool Combine() {
            if ((m_version.Length()) && (m_status.Length())) {
                Assign(m_version);
                Append(" ");
                Append(m_status);
                Append(" ");
                Append(m_reason);
                Append("\r\n");
                return true;
            }
            return false;
        }
        ///////////////////////////////////////////////////////////////////////
        virtual bool Separate(Version& version, Status& status, Reason& reason) {
            if ((Separate())) {
                version = m_version;
                status = m_status;
                reason = m_reason;
                return true;
            }
            return false;
        }
        virtual bool Separate() {
            return false;
        }

        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        virtual Line& Set(const Version& version, const Status& status, const Reason& reason) {
            Combine(version, status, reason);
            return *this;
        }
        virtual Line& Set(const Status& status, const Reason& reason) {
            Combine(status, reason);
            return *this;
        }

        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        virtual String SetVersion(const String& to) {
            String m_version = to;
            return m_version;
        }
        virtual String GetVersion() const {
            return m_version;
        }
        ///////////////////////////////////////////////////////////////////////
        virtual String SetStatus(const String& to) {
            m_status = to;
            return m_status;
        }
        virtual String GetStatus() const {
            return m_status;
        }
        ///////////////////////////////////////////////////////////////////////
        virtual String SetReason(const String& to) {
            m_reason = to;
            return m_reason;
        }
        virtual String GetReason() const {
            return m_reason;
        }

        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        virtual Version& version() const {
            return (Version&)(m_version);
        }
        ///////////////////////////////////////////////////////////////////////
        virtual Status& status() const {
            return (Status&)(m_status);
        }
        ///////////////////////////////////////////////////////////////////////
        virtual Reason& reason() const {
            return (Reason&)(m_reason);
        }

        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
    protected:
        Version m_version;
        Status m_status;
        Reason m_reason;
    };

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Response(CharWriter& messageWriter, const Request& request)
    : m_line(request.GetLine().GetVersion()), m_message(messageWriter) {
    }
    Response(const Request& request): m_line(request.GetLine().GetVersion()) {
    }
    Response(const Line& line, const Headers& headers, const Message& message)
    : m_line(line), m_headers(headers), m_message(message) {
    }
    Response(CharWriter& messageWriter): m_message(messageWriter) {
    }
    Response() {
    }
    virtual ~Response() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual String SetVersion (const String& to) {
        m_line.version() = to;
        return m_line.version();
    }
    virtual String GetVersion() const {
        return m_line.version();
    }
    ///////////////////////////////////////////////////////////////////////
    virtual String SetStatus(const String& to) {
        m_line.status() = to;
        return m_line.status();
    }
    virtual String GetStatus() const {
        return m_line.status();
    }
    ///////////////////////////////////////////////////////////////////////
    virtual String SetReason(const String& to) {
        m_line.reason() = to;
        return m_line.reason();
    }
    virtual String GetReason() const {
        return m_line.reason();
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual String SetContentType(const String& to) {
        return m_headers.SetContentType(to);
    }
    virtual String GetContentType() const {
        return m_headers.GetContentType();
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t SetContentLengthNo(ssize_t to) {
        return m_headers.SetContentLengthNo(to);
    }
    virtual ssize_t GetContentLengthNo() const {
        return m_headers.GetContentLengthNo();
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual CharWriter& GetMessageWriter() const {
        return m_message.GetWriter();
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual Line& line() const {
        return (Line&)(m_line);
    }
    ///////////////////////////////////////////////////////////////////////
    virtual Headers& headers() const {
        return (Headers&)(m_headers);
    }
    ///////////////////////////////////////////////////////////////////////
    virtual Message& message() const {
        return (Message&)(m_message);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    Line m_line;
    Headers m_headers;
    Message m_message;
};

} // namespace http 
} // namespace xos 

#endif // _XOS_HTTP_RESPONSE_HPP 
