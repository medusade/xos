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
///   File: HeaderReader.hpp
///
/// Author: $author$
///   Date: 5/27/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_INET_HTTP_SERVER_MEDUSA_HEADERREADER_HPP
#define _XOS_INET_HTTP_SERVER_MEDUSA_HEADERREADER_HPP

#include "xos/inet/http/Request.hpp"
#include "xos/io/Reader.hpp"

namespace xos {
namespace http {
namespace server {
namespace medusa {

///////////////////////////////////////////////////////////////////////
///  Class: HeaderReaderT
///////////////////////////////////////////////////////////////////////
template
<typename THeader = http::Header,
 class TReader = io::Reader,
 class TExtend = ExportBase,
 class TImplement = InterfaceBase>

class _EXPORT_CLASS HeaderReaderT: virtual public TImplement, public TExtend {
public:
    typedef TImplement Implements;
    typedef TExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    HeaderReaderT() {
    }
    virtual ~HeaderReaderT() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////
    /// RFC 2068
    ///
    /// 4.2 Message Headers
    ///
    ///    HTTP header fields, which include general-header (section 4.5),
    ///    request-header (section 5.3), response-header (section 6.2), and
    ///    entity-header (section 7.1) fields, follow the same generic format as
    ///    that given in Section 3.1 of RFC 822 [9]. Each header field consists
    ///    of a name followed by a colon (":") and the field value. Field names
    ///    are case-insensitive. The field value may be preceded by any amount
    ///    of LWS, though a single SP is preferred. Header fields can be
    ///    extended over multiple lines by preceding each extra line with at
    ///    least one SP or HT.  Applications SHOULD follow "common form" when
    ///    generating HTTP constructs, since there might exist some
    ///    implementations that fail to accept anything beyond the common forms.
    ///
    ///           message-header = field-name ":" [ field-value ] CRLF
    ///
    ///           field-name     = token
    ///           field-value    = *( field-content | LWS )
    ///
    ///           field-content  = <the OCTETs making up the field-value
    ///                            and consisting of either *TEXT or combinations
    ///                            of token, tspecials, and quoted-string>
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Read(THeader& header, TReader& reader) {
        ssize_t count = 0;
        ssize_t amount;
        char c;

        m_name.Clear();
        m_value.Clear();
        m_onRead = &Derives::OnReadName;
        m_onReadDone = &Derives::OnReadFailed;

        do {
            if (0 > (amount = reader.Read(&c, 1))) {
                return amount;
            } else {
                count += amount;
                if (0 > (amount = (this->*m_onRead)(header, c))) {
                    return amount;
                }
            }
        } while (0 < (amount));

        if (0 >= (amount = (this->*m_onReadDone)(header))) {
            return amount;
        }
        return count;
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnReadName(THeader& header, const char& c) {
        ssize_t count = 1;
        switch (c) {
        case ':':
            if (0 < (m_name.Length())) {
                XOS_LOG_DEBUG("name = \"" << m_name << "\"");
                header.SetName(m_name);
                m_onRead = &Derives::OnReadValue;
            } else {
                XOS_LOG_DEBUG("invalid char = <" << ((int)c) << ">");
                return -1;
            }
            break;
        case SP:
            if (0 < (m_value.Length())) {
                XOS_LOG_DEBUG("<SP>...continued value");
                m_onRead = &Derives::OnReadValue;
            } else {
                XOS_LOG_DEBUG("invalid char = <" << ((int)c) << ">");
                return -1;
            }
            break;
        case HT:
            if (0 < (m_value.Length())) {
                XOS_LOG_DEBUG("<HT>...continued value");
                m_onRead = &Derives::OnReadValue;
            } else {
                XOS_LOG_DEBUG("invalid char = <" << ((int)c) << ">");
                return -1;
            }
            break;
        case CR:
            if (0 < (m_value.Length())) {
                XOS_LOG_DEBUG("invalid char = <" << ((int)c) << ">");
                return -1;
            } else {
                XOS_LOG_DEBUG("<CR>...end all headers");
                m_onRead = &Derives::OnReadLF;
            }
            break;
        case LF:
            XOS_LOG_DEBUG("invalid char = <" << ((int)c) << ">");
            return -1;
            break;
        default:
            m_name.Append(&c, 1);
        }
        return count;
    }
    virtual ssize_t OnReadValue(THeader& header, const char& c) {
        ssize_t count = 1;
        switch (c) {
        case CR:
            XOS_LOG_DEBUG("value = \"" << m_value << "\"");
            header.SetValue(m_value);
            m_onRead = &Derives::OnReadLF;
            break;
        case LF:
            XOS_LOG_DEBUG("invalid char = <" << ((int)c) << ">");
            return -1;
            break;
        case SP:
        case HT:
            if (1 > (m_value.Length())) {
                XOS_LOG_DEBUG("leading white space = <" << ((int)c) << ">");
                return 1;
            }
        default:
            m_value.Append(&c, 1);
        }
        return count;
    }
    virtual ssize_t OnReadLF(THeader& header, const char& c) {
        ssize_t count = 1;
        switch (c) {
        case LF:
            if (1 > (m_name.Length())) {
                XOS_LOG_DEBUG("<LF>end all headers");
                m_onReadDone = &Derives::OnReadAllDone;
                return 0;
            } else {
                XOS_LOG_DEBUG("<LF>end header");
                m_onReadDone = &Derives::OnReadDone;
                return 0;
            }
            break;
        case SP:
        case HT:
        case CR:
        default:
            XOS_LOG_DEBUG("invalid char = <" << ((int)c) << ">");
            return -1;
        }
        return count;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnReadFailed(THeader& header) {
        ssize_t count = -1;
        return count;
    }
    virtual ssize_t OnReadDone(THeader& header) {
        ssize_t count = 1;
        return count;
    }
    virtual ssize_t OnReadAllDone(THeader& header) {
        ssize_t count = 0;
        return count;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    typedef HeaderReaderT Derives;
    typedef ssize_t (Derives::*MOnRead)(THeader& header, const char& c);
    typedef ssize_t (Derives::*MOnReadDone)(THeader& header);
    enum { SP = ' ', HT = '\t', CR = '\r', LF = '\n' };

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    MOnRead m_onRead;
    MOnReadDone m_onReadDone;
    String m_name, m_value;
};

typedef HeaderReaderT<> HeaderReader;

} // namespace medusa 
} // namespace server 
} // namespace http 
} // namespace xos 

#endif // _XOS_INET_HTTP_SERVER_MEDUSA_HEADERREADER_HPP 
