///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2016 $organization$
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
///   File: HeartbeatMessage.hpp
///
/// Author: $author$
///   Date: 4/22/2016
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_INET_TLS_HEARTBEATMESSAGE_HPP
#define _XOS_INET_TLS_HEARTBEATMESSAGE_HPP

#include "xos/inet/tls/Base.hpp"

namespace xos {
namespace tls {

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
enum {
    HEARTBEAT_MESSAGE_TYPE_UNKNOWN = -1,

    HEARTBEAT_MESSAGE_TYPE_HEARTBEAT_REQUEST  = 1,
    HEARTBEAT_MESSAGE_TYPE_HEARTBEAT_RESPONSE = 2
};
#define DEFAULT_HEARTBEAT_MESSAGE_TYPE HEARTBEAT_MESSAGE_TYPE_HEARTBEAT_REQUEST

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS HeartbeatMessageType: virtual public Implement, public Extend {
public:
    typedef Implement Implements;
    typedef Extend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    HeartbeatMessageType(uint8_t which = DEFAULT_HEARTBEAT_MESSAGE_TYPE)
    : m_which(which) {
    }
    HeartbeatMessageType(const HeartbeatMessageType& copy)
    : m_which(copy.which()) {
    }
    virtual ~HeartbeatMessageType() {
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
    virtual ssize_t Write(io::Writer& writer) {
        ssize_t count = 0;
        ssize_t amount = 0;
        if (0 < (amount = WriteMsb(writer, m_which, sizeof(m_which)))) {
            count += amount;
        }
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t SizeOf() const {
        ssize_t count = sizeof(m_which);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    uint8_t m_which;
};

typedef xos::Array<opaque_t> HeartbeatMessagePayload;

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS HeartbeatMessage: virtual public Implement, public Extend {
public:
    typedef Implement Implements;
    typedef Extend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    HeartbeatMessage
    (uint8_t payload, uint16_t payload_length,
     uint8_t which = DEFAULT_HEARTBEAT_MESSAGE_TYPE)
    : m_type(which), m_payload_length(payload_length) {
        set_payload(payload, payload_length);
    }
    HeartbeatMessage(const HeartbeatMessage& copy)
    : m_type(copy.type()),
      m_payload_length(copy.payload_length()),
      m_payload(copy.payload()) {
    }
    virtual ~HeartbeatMessage() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual HeartbeatMessageType& set_type(const HeartbeatMessageType& to) {
        m_type = to;
        return m_type;
    }
    virtual const HeartbeatMessageType& type() const {
        return m_type;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual uint16_t set_payload_length(uint16_t to) {
        m_payload_length = to;
        return m_payload_length;
    }
    virtual uint16_t payload_length() const {
        return m_payload_length;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual HeartbeatMessagePayload& set_payload(uint8_t to, uint16_t length) {
        m_payload.Set(to, length);
        return m_payload;
    }
    virtual const HeartbeatMessagePayload& payload() const {
        return m_payload;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Write(io::Writer& writer) {
        ssize_t count = 0;
        ssize_t amount = 0;
        if (0 < (amount = m_type.Write(writer))) {
            count += amount;
            if (0 < (amount = WriteMsb
                (writer, m_payload_length, sizeof(m_payload_length)))) {
                count += amount;
                if (0 < (amount = WriteOpaque
                    (writer, m_payload.Elements(), m_payload.Length()))) {
                    count += amount;
                }
            }
        }
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t SizeOf() const {
        ssize_t count = m_type.SizeOf();
        count += sizeof(m_payload_length);
        count += m_payload.Length();
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    HeartbeatMessageType m_type;
    uint16_t m_payload_length;
    HeartbeatMessagePayload m_payload;
};

} // namespace tls 
} // namespace xos 

#endif // _XOS_INET_TLS_HEARTBEATMESSAGE_HPP 
