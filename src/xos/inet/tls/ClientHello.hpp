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
///   File: ClientHello.hpp
///
/// Author: $author$
///   Date: 4/26/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_TLS_CLIENTHELLO_HPP
#define _XOS_TLS_CLIENTHELLO_HPP

#include "xos/inet/tls/GmtUnixTime.hpp"
#include "xos/inet/tls/Random.hpp"
#include "xos/inet/tls/SessionID.hpp"
#include "xos/inet/tls/CipherSuites.hpp"
#include "xos/inet/tls/CompressionMethods.hpp"
#include "xos/inet/tls/Handshake.hpp"
#include "xos/inet/tls/Plaintext.hpp"

namespace xos {
namespace tls {

/* RFC 2246
    struct {
        ProtocolVersion client_version;
        Random random;
        SessionID session_id;
        CipherSuite cipher_suites<2..2^16-1>;
        CompressionMethod compression_methods<1..2^8-1>;
    } ClientHello;
*/

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS ClientHello: virtual public Implement, virtual public Extend {
public:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    ClientHello
    (uint32_t gmt_unix_time, opaque random_byte,
     opaque session_id, uint16_t cipher_suite)
     : m_random(gmt_unix_time, random_byte),
       m_session_id(session_id),
       m_cipher_suites(cipher_suite) {
    }
    ClientHello() {}
    virtual ~ClientHello() {}
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Read(io::Reader& reader) {
        ssize_t count = 0;
        return count;
    }
    virtual ssize_t Write(io::Writer& writer) {
        ssize_t count = 0;
        ssize_t amount = 0;
        if (amount  = (m_client_version.Write(writer))) {
            count += amount;
            if (amount  = (m_random.Write(writer))) {
                count += amount;
                if (amount  = (m_session_id.Write(writer))) {
                    count += amount;
                    if (amount  = (m_cipher_suites.Write(writer))) {
                        count += amount;
                        if (amount  = (m_compression_methods.Write(writer))) {
                            count += amount;
                        }
                    }
                }
            }
        }
        return count;
    }
    virtual ssize_t SizeOf() const {
        ssize_t count = 0;
        count += m_client_version.SizeOf();
        count += m_random.SizeOf();
        count += m_session_id.SizeOf();
        count += m_cipher_suites.SizeOf();
        count += m_compression_methods.SizeOf();
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    ProtocolVersion m_client_version;
    Random m_random;
    SessionID m_session_id;
    CipherSuites m_cipher_suites;
    CompressionMethods m_compression_methods;
};

} // namespace tls
} // namespace xos 

#endif // _XOS_TLS_CLIENTHELLO_HPP 
