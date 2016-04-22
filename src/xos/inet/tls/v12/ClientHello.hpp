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
///   File: ClientHello.hpp
///
/// Author: $author$
///   Date: 4/21/2016
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_INET_TLS_V12_CLIENTHELLO_HPP
#define _XOS_INET_TLS_V12_CLIENTHELLO_HPP

#include "xos/inet/tls/ClientHello.hpp"
#include "xos/inet/tls/v12/ProtocolVersion.hpp"
#include "xos/inet/tls/v12/HeartbeatExtension.hpp"

namespace xos {
namespace tls {
namespace v12 {

///////////////////////////////////////////////////////////////////////
///  Class: ClientHello
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS ClientHello
: virtual public tls::ClientHello::Implements, public tls::ClientHello {
public:
    typedef tls::ClientHello::Implements Implements;
    typedef tls::ClientHello Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    ClientHello
    (uint32_t gmt_unix_time, opaque_t random_byte,
     opaque_t session_id, uint16_t cipher_suite)
    : Extends(gmt_unix_time, random_byte, session_id, cipher_suite) {
        set_client_version(ProtocolVersion());
    }
    virtual ~ClientHello() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Write(io::Writer& writer) {
        ssize_t count = Extends::Write(writer);
        ssize_t amount = 0;
        if (0 < (amount = m_heartbeat_extension.Write(writer))) {
            count += amount;
        }
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t SizeOf() const {
        ssize_t count = Extends::SizeOf();
        count += m_heartbeat_extension.SizeOf();
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    HeartbeatExtension m_heartbeat_extension;
};

} // namespace v12 
} // namespace tls 
} // namespace xos 

#endif // _XOS_INET_TLS_V12_CLIENTHELLO_HPP
