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
///   File: LineReader.hpp
///
/// Author: $author$
///   Date: 5/26/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_INET_HTTP_SERVER_MEDUSA_REQUEST_LINEREADER_HPP
#define _XOS_INET_HTTP_SERVER_MEDUSA_REQUEST_LINEREADER_HPP

#include "xos/inet/http/Request.hpp"
#include "xos/io/Reader.hpp"

namespace xos {
namespace http {
namespace server {
namespace medusa {
namespace request {

///////////////////////////////////////////////////////////////////////
///  Class: LineReaderT
///////////////////////////////////////////////////////////////////////
template
<typename TLine = http::Request::Line,
 class TReader = io::Reader,
 class TExtend = ExportBase,
 class TImplement = InterfaceBase>

class _EXPORT_CLASS LineReaderT: virtual public TImplement, public TExtend {
public:
    typedef TImplement Implements;
    typedef TExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    LineReaderT(): m_onRead(0), m_onReadDone(0) {
    }
    virtual ~LineReaderT() {
    }

    ///////////////////////////////////////////////////////////////////////
    /// RFC 2068
    ///
    /// 5.1 Request-Line
    ///
    ///   The Request-Line begins with a method token, followed by the
    ///   Request-URI and the protocol version, and ending with CRLF. The
    ///   elements are separated by SP characters. No CR or LF are allowed
    ///   except in the final CRLF sequence.
    ///
    ///          Request-Line   = Method SP Request-URI SP HTTP-Version CRLF
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Read(TLine& line, TReader& reader) {
        ssize_t count = 0;
        ssize_t amount;
        char c;

        m_text.Clear();
        m_onRead = &Derives::OnReadMethod;
        m_onReadDone = &Derives::OnReadFailed;

        do {
            if (0 > (amount = reader.Read(&c, 1))) {
                return amount;
            } else {
                count += amount;
                if (0 > (amount = (this->*m_onRead)(line, c))) {
                    return amount;
                }
            }
        } while (0 < (amount));

        if (0 > (amount = (this->*m_onReadDone)(line))) {
            return amount;
        }
        return count;
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnReadMethod(TLine& line, const char& c) {
        ssize_t count = 1;
        switch (c) {
        case SP:
            if ((0 < (m_text.Length()))) {
                XOS_LOG_DEBUG("method = \"" << m_text << "\"");
                line.SetMethod(m_text);
                m_text.Clear();
                m_onRead = &Derives::OnReadUri;
            } else {
                return -1;
            }
            break;
        case CR:
        case LF:
            return -1;
            break;
        default:
            m_text.Append(&c, 1);
        }
        return count;
    }
    virtual ssize_t OnReadUri(TLine& line, const char& c) {
        ssize_t count = 1;
        switch (c) {
        case SP:
            if ((0 < (m_text.Length()))) {
                XOS_LOG_DEBUG("uri = \"" << m_text << "\"");
                line.SetUri(m_text);
                m_text.Clear();
                m_onRead = &Derives::OnReadProtocol;
            } else {
                return -1;
            }
            break;
        case CR:
        case LF:
            return -1;
            break;
        default:
            m_text.Append(&c, 1);
        }
        return count;
    }
    virtual ssize_t OnReadProtocol(TLine& line, const char& c) {
        ssize_t count = 1;
        switch (c) {
        case '/':
            if ((0 < (m_text.Length()))) {
                XOS_LOG_DEBUG("protocol = \"" << m_text << "\"");
                line.SetProtocol(m_text);
                m_text.Clear();
                m_onRead = &Derives::OnReadProtocolVersionMajor;
            } else {
                return -1;
            }
            break;
        case SP:
        case CR:
        case LF:
            return -1;
            break;
        default:
            m_text.Append(&c, 1);
        }
        return count;
    }
    virtual ssize_t OnReadProtocolVersionMajor(TLine& line, const char& c) {
        ssize_t count = 1;
        switch (c) {
        case '.':
            if ((0 < (m_text.Length()))) {
                XOS_LOG_DEBUG("version major = \"" << m_text << "\"");
                line.SetProtocolVersionMajor(m_text);
                m_text.Clear();
                m_onRead = &Derives::OnReadProtocolVersionMinor;
            } else {
                return -1;
            }
            break;
        case SP:
        case CR:
        case LF:
            return -1;
            break;
        default:
            m_text.Append(&c, 1);
        }
        return count;
    }
    virtual ssize_t OnReadProtocolVersionMinor(TLine& line, const char& c) {
        ssize_t count = 1;
        switch (c) {
        case CR:
            if ((0 < (m_text.Length()))) {
                XOS_LOG_DEBUG("version minor = \"" << m_text << "\"");
                line.SetProtocolVersionMinor(m_text);
                m_text.Clear();
                m_onRead = &Derives::OnReadLF;
            } else {
                return -1;
            }
            break;
        case SP:
        case LF:
            return -1;
            break;
        default:
            m_text.Append(&c, 1);
        }
        return count;
    }
    virtual ssize_t OnReadLF(TLine& line, const char& c) {
        ssize_t count = -1;
        switch (c) {
        case LF:
            m_onReadDone = &Derives::OnReadDone;
            return 0;
            break;
        }
        return count;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnReadFailed(TLine& line) {
        ssize_t count = -1;
        m_onReadDone = 0;
        return count;
    }
    virtual ssize_t OnReadDone(TLine& line) {
        ssize_t count = 1;
        m_onReadDone = 0;
        return count;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    typedef LineReaderT Derives;
    typedef ssize_t (Derives::*MOnRead)(TLine& line, const char& c);
    typedef ssize_t (Derives::*MOnReadDone)(TLine& line);
    enum { SP = ' ', CR = '\r', LF = '\n' };

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    MOnRead m_onRead;
    MOnReadDone m_onReadDone;
    String m_text;
};

typedef LineReaderT<> LineReader;

} // namespace request 
} // namespace medusa 
} // namespace server 
} // namespace http 
} // namespace xos 

#endif // _XOS_INET_HTTP_SERVER_MEDUSA_REQUEST_LINEREADER_HPP 
