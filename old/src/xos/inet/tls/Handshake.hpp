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
///   File: Handshake.hpp
///
/// Author: $author$
///   Date: 4/26/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_TLS_HANDSHAKE_HPP
#define _XOS_TLS_HANDSHAKE_HPP

#include "xos/inet/tls/Base.hpp"

namespace xos {
namespace tls {

/* RFC 2246
    enum {
        hello_request(0), client_hello(1), server_hello(2),
        certificate(11), server_key_exchange (12),
        certificate_request(13), server_hello_done(14),
        certificate_verify(15), client_key_exchange(16),
        finished(20), (255)
    } HandshakeType;

    struct {
        HandshakeType msg_type;
        uint24 length;
        select (HandshakeType) {
            case hello_request:       HelloRequest;
            case client_hello:        ClientHello;
            case server_hello:        ServerHello;
            case certificate:         Certificate;
            case server_key_exchange: ServerKeyExchange;
            case certificate_request: CertificateRequest;
            case server_hello_done:   ServerHelloDone;
            case certificate_verify:  CertificateVerify;
            case client_key_exchange: ClientKeyExchange;
            case finished:            Finished;
        } body;
    } Handshake;
*/

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS HandshakeType: virtual public Implement, virtual public Extend {
public:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    HandshakeType(uint8_t which = HANDSHAKE_TYPE_UKNOWN): m_which(which) {}
    HandshakeType(const HandshakeType& copy): m_which(copy.which()) {}
    virtual ~HandshakeType() {}
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Read(io::Reader& reader) {
        ssize_t count = 0;
        ssize_t amount = 0;
        if (0 < (amount = ReadMsb(reader, m_which, sizeof(m_which)))) {
            count += amount;
            switch (m_which) {
            case HANDSHAKE_TYPE_HELLO_REQUEST:
                XOS_LOG_MESSAGE_DEBUG("...HANDSHAKE_TYPE_HELLO_REQUEST which = " << m_which << " on " << __XOS_LOGGER_CLASS__ << "::Read()");
                break;
            case HANDSHAKE_TYPE_CLIENT_HELLO:
                XOS_LOG_MESSAGE_DEBUG("...HANDSHAKE_TYPE_CLIENT_HELLO which = " << m_which << " on " << __XOS_LOGGER_CLASS__ << "::Read()");
                break;
            case HANDSHAKE_TYPE_SERVER_HELLO:
                XOS_LOG_MESSAGE_DEBUG("...HANDSHAKE_TYPE_SERVER_HELLO which = " << m_which << " on " << __XOS_LOGGER_CLASS__ << "::Read()");
                break;
            case HANDSHAKE_TYPE_CLIENT_KEY_EXCHANGE:
                XOS_LOG_MESSAGE_DEBUG("...HANDSHAKE_TYPE_CLIENT_KEY_EXCHANGE which = " << m_which << " on " << __XOS_LOGGER_CLASS__ << "::Read()");
                break;
            case HANDSHAKE_TYPE_SERVER_KEY_EXCHANGE:
                XOS_LOG_MESSAGE_DEBUG("...HANDSHAKE_TYPE_SERVER_KEY_EXCHANGE which = " << m_which << " on " << __XOS_LOGGER_CLASS__ << "::Read()");
                break;
            case HANDSHAKE_TYPE_SERVER_HELLO_DONE:
                XOS_LOG_MESSAGE_DEBUG("...HANDSHAKE_TYPE_SERVER_HELLO_DONE which = " << m_which << " on " << __XOS_LOGGER_CLASS__ << "::Read()");
                break;
            case HANDSHAKE_TYPE_CERTIFICATE:
                XOS_LOG_MESSAGE_DEBUG("...HANDSHAKE_TYPE_CERTIFICATE which = " << m_which << " on " << __XOS_LOGGER_CLASS__ << "::Read()");
                break;
            case HANDSHAKE_TYPE_CERTIFICATE_REQUEST:
                XOS_LOG_MESSAGE_DEBUG("...HANDSHAKE_TYPE_CERTIFICATE_REQUEST which = " << m_which << " on " << __XOS_LOGGER_CLASS__ << "::Read()");
                break;
            case HANDSHAKE_TYPE_CERTIFICATE_VERIFY:
                XOS_LOG_MESSAGE_DEBUG("...HANDSHAKE_TYPE_CERTIFICATE_VERIFY which = " << m_which << " on " << __XOS_LOGGER_CLASS__ << "::Read()");
                break;
            case HANDSHAKE_TYPE_FINISHED:
                XOS_LOG_MESSAGE_DEBUG("...HANDSHAKE_TYPE_FINISHED which = " << m_which << " on " << __XOS_LOGGER_CLASS__ << "::Read()");
                break;
            default:
                XOS_LOG_MESSAGE_DEBUG("...unexpected which = " << m_which << " on " << __XOS_LOGGER_CLASS__ << "::Read()");
                count = 0;
                break;
            }
        }
        return count;
    }
    virtual ssize_t Write(io::Writer& writer) {
        ssize_t count = 0;
        count = WriteMsb(writer, m_which, sizeof(m_which));
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t SizeOf() const {
        ssize_t count = 0;
        count += sizeof(m_which);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual uint8_t set_which(uint8_t to) {
        m_which = to;
        return m_which;
    }
    virtual uint8_t which() const {
        return m_which;
    }
    virtual operator uint8_t() const {
        return m_which;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    uint8_t m_which;
};

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Handshake: virtual public Implement, virtual public Extend {
public:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Handshake(uint8_t type, Implement& msg)
    : m_msg_type(type), m_msg(msg), m_length(msg.SizeOf()) {}
    Handshake(): m_msg(m_null_msg) {}
    virtual ~Handshake() {}
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t ReadMsgType(io::Reader& reader) {
        ssize_t count = 0;
        ssize_t amount = 0;
        XOS_LOG_MESSAGE_DEBUG("" << __XOS_LOGGER_CLASS__ << "::ReadMsgType()...");
        if (0 < (amount = m_msg_type.Read(reader))) {
            count += amount;
            XOS_LOG_MESSAGE_DEBUG("..." << count << " = " << __XOS_LOGGER_CLASS__ << "::ReadMsgType()");
        }
        return count;
    }
    virtual ssize_t ReadLength(io::Reader& reader) {
        ssize_t count = 0;
        ssize_t amount = 0;
        XOS_LOG_MESSAGE_DEBUG("" << __XOS_LOGGER_CLASS__ << "::ReadLength()...");
        if (0 < (amount = m_length.Read(reader))) {
            count += amount;
            XOS_LOG_MESSAGE_DEBUG("..." << count << " = " << __XOS_LOGGER_CLASS__ << "::ReadLength()");
        }
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Write(io::Writer& writer) {
        ssize_t count = 0;
        ssize_t amount = 0;
        XOS_LOG_MESSAGE_DEBUG("" << __XOS_LOGGER_CLASS__ << "::Write()...");
        if (0 < (amount = m_length.Value())) {
            XOS_LOG_MESSAGE_DEBUG("handshake length = " << m_length.Value() << "");
            if (0 < (amount = m_msg_type.Write(writer))) {
                count += amount;
                if (0 < (amount = m_length.Write(writer))) {
                    count += amount;
                    if (0 < (amount = m_msg.Write(writer))) {
                        count += amount;
                        XOS_LOG_MESSAGE_DEBUG("..." << count << " = " << __XOS_LOGGER_CLASS__ << "::Write()");
                    }
                }
            }
        }
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t SizeOf() const {
        ssize_t count = 0;
        count += m_msg_type.SizeOf();
        count += m_length.SizeOf();
        count += m_length.Value();
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual HandshakeType& set_msg_type(const HandshakeType& to) {
        m_msg_type = to;
        return m_msg_type;
    }
    virtual const HandshakeType& msg_type() const {
        return m_msg_type;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual Uint24& set_length(const Uint24& to) {
        m_length = to;
        return m_length;
    }
    virtual const Uint24& length() const {
        return m_length;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    HandshakeType m_msg_type;
    Uint24 m_length;
    Base m_null_msg;
    Implement& m_msg;
};

} // namespace tls
} // namespace xos 

#endif // _XOS_TLS_HANDSHAKE_HPP 
