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
///   File: ServerHello.hpp
///
/// Author: $author$
///   Date: 4/25/2016
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_INET_TLS_SERVERHELLO_HPP
#define _XOS_INET_TLS_SERVERHELLO_HPP

#include "xos/inet/tls/ProtocolVersion.hpp"
#include "xos/inet/tls/Random.hpp"
#include "xos/inet/tls/SessionID.hpp"
#include "xos/inet/tls/CipherSuite.hpp"
#include "xos/inet/tls/CompressionMethod.hpp"
#include "xos/inet/tls/Base.hpp"

namespace xos {
namespace tls {

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS ServerHello: virtual public Implement, public Extend {
public:
    typedef Implement Implements;
    typedef Extend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    ServerHello() {
    }
    virtual ~ServerHello() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Read(io::Reader& reader) {
        ssize_t count = 0;
        ssize_t amount = 0;
        if (amount  = (m_server_version.Read(reader))) {
            count += amount;
            if (amount  = (m_random.Read(reader))) {
                count += amount;
                if (amount  = (m_session_id.Read(reader))) {
                    count += amount;
                    if (amount  = (m_cipher_suite.Read(reader))) {
                        count += amount;
                        if (amount  = (m_compression_method.Read(reader))) {
                            count += amount;
                        }
                    }
                }
            }
        }
        return count;
    }
    virtual ssize_t Write(io::Writer& writer) {
        ssize_t count = 0;
        ssize_t amount = 0;
        if (amount  = (m_server_version.Write(writer))) {
            count += amount;
            if (amount  = (m_random.Write(writer))) {
                count += amount;
                if (amount  = (m_session_id.Write(writer))) {
                    count += amount;
                    if (amount  = (m_cipher_suite.Write(writer))) {
                        count += amount;
                        if (amount  = (m_compression_method.Write(writer))) {
                            count += amount;
                        }
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
        count += m_server_version.SizeOf();
        count += m_random.SizeOf();
        count += m_session_id.SizeOf();
        count += m_cipher_suite.SizeOf();
        count += m_compression_method.SizeOf();
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ProtocolVersion& set_server_version(const ProtocolVersion& to) {
        m_server_version = to;
        return m_server_version;
    }
    virtual const ProtocolVersion& server_version() const {
        return m_server_version;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    ProtocolVersion m_server_version;
    Random m_random;
    SessionID m_session_id;
    CipherSuite m_cipher_suite;
    CompressionMethod m_compression_method;
};

} // namespace tls 
} // namespace xos 

#endif // _XOS_INET_TLS_SERVERHELLO_HPP 
