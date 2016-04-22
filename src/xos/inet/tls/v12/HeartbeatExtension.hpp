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
///   File: HeartbeatExtension.hpp
///
/// Author: $author$
///   Date: 4/21/2016
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_INET_TLS_V12_HEARTBEATEXTENSION_HPP
#define _XOS_INET_TLS_V12_HEARTBEATEXTENSION_HPP

#include "xos/inet/tls/Extension.hpp"

namespace xos {
namespace tls {
namespace v12 {

/* RFC 6520
   enum {
      peer_allowed_to_send(1),
      peer_not_allowed_to_send(2),
      (255)
   } HeartbeatMode;

   struct {
      HeartbeatMode mode;
   } HeartbeatExtension;
*/

enum {
    HEARTBEAT_MODE_UNKNOWN = -1,

    HEARTBEAT_MODE_PEER_ALLOWED_TO_SEND = 1,
    HEARTBEAT_MODE_PEER_NOT_ALLOWED_TO_SEND = 2
};
#define HEARTBEAT_MODE_DEFAULT HEARTBEAT_MODE_PEER_ALLOWED_TO_SEND

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS HeartbeatMode: virtual public Implement, public Extend {
public:
    typedef Implement Implements;
    typedef Extend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    HeartbeatMode
    (uint8_t which = HEARTBEAT_MODE_DEFAULT): m_which(which) {
    }
    HeartbeatMode(const HeartbeatMode& copy): m_which(copy.Which()) {
    }
    virtual ~HeartbeatMode() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual uint8_t SetWhich(uint8_t to) {
        m_which = to;
        return m_which;
    }
    virtual uint8_t Which() const {
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

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS HeartbeatExtension
: virtual public Extension::Implements, public Extension {
public:
    typedef Extension::Implements Implements;
    typedef Extension Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    HeartbeatExtension(uint8_t which = HEARTBEAT_MODE_DEFAULT)
    : Extends(EXTENSION_HEARTBEAT), m_mode(which) {
    }
    HeartbeatExtension(const HeartbeatMode& mode)
    : Extends(EXTENSION_HEARTBEAT), m_mode(mode) {
    }
    HeartbeatExtension(const HeartbeatExtension& copy)
    : Extends(copy), m_mode(copy.mode()) {
    }
    virtual ~HeartbeatExtension() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual HeartbeatMode& set_mode(const HeartbeatMode& to) {
        m_mode = to;
        return m_mode;
    }
    virtual const HeartbeatMode& mode() const {
        return m_mode;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Write(io::Writer& writer) {
        ssize_t count = Extends::Write(writer);
        ssize_t amount = 0;
        if (0 < (amount = m_mode.Write(writer))) {
            count += amount;
        }
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t SizeOf() const {
        ssize_t count = Extends::SizeOf();
        count += m_mode.SizeOf();
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    HeartbeatMode m_mode;
};

} // namespace v12 
} // namespace tls 
} // namespace xos 

#endif // _XOS_INET_TLS_V12_HEARTBEATEXTENSION_HPP 
