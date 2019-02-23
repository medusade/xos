///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2012 $organization$
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
///   File: Endpoint.hpp
///
/// Author: $author$
///   Date: 9/26/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_NETWORK_IP_V4_ENDPOINT_HPP
#define _XOS_NETWORK_IP_V4_ENDPOINT_HPP

#include "xos/network/ip/Endpoint.hpp"
#include "xos/network/ip/v4/Address.hpp"
#include "xos/os/Logger.hpp"

namespace xos {
namespace network {
namespace ip {
namespace v4 {

typedef ip::Endpoint EndpointImplement;
typedef Address EndpointExtend;

class _EXPORT_CLASS Endpoint
: virtual public EndpointImplement,
  public EndpointExtend
{
public:
    typedef EndpointImplement Implements;
    typedef EndpointExtend Extends;

    Endpoint(const String& host, u_short port) {
        if (!(Implements::Init(host.Chars(), port))) {
            throw Error(Error::Failed);
        }
    }
    Endpoint(const char* host, u_short port) {
        if (!(Implements::Init(host, port))) {
            throw Error(Error::Failed);
        }
    }
    Endpoint(const struct sockaddr* socketAddress, socklen_t socketAddressLen, u_short port) {
        if (!(Init(socketAddress, socketAddressLen, port))) {
            throw Error(Error::Failed);
        }
    }
    Endpoint(u_short port = 0) {
        if (!(Init(port))) {
            throw Error(Error::Failed);
        }
    }
    virtual ~Endpoint() {
        if (!(Fini())) {
            throw Error(Error::Failed);
        }
    }

    virtual bool Init(const struct sockaddr* socketAddress, socklen_t socketAddressLen, u_short port) {
        Init(port);
        if ((socketAddress) && (socketAddressLen == (m_socketAddressLen))) {
            if (Family == (socketAddress->sa_family)) {
                const struct sockaddr_in& socketAddressIn = (const struct sockaddr_in&)(*socketAddress);
                m_socketAddress.sin_addr.s_addr = socketAddressIn.sin_addr.s_addr;
                return true;
            }
        }
        return false;
    }
    virtual bool Init(u_short port = 0) {
        memset(&m_socketAddress, 0, m_socketAddressLen = (sizeof(m_socketAddress)));
        m_socketAddress.sin_family = Family;
        m_socketAddress.sin_addr.s_addr = INADDR_ANY;
        m_socketAddress.sin_port = htons(port);
        return true;
    }

    virtual struct sockaddr* SocketAddress() const {
        return (struct sockaddr*)(&m_socketAddress);
    }
    virtual socklen_t& SocketAddressLen() const {
        return (socklen_t&)(m_socketAddressLen);
    }

protected:
    socklen_t m_socketAddressLen;
    struct sockaddr_in m_socketAddress;
};

} // namespace v4 
} // namespace ip 
} // namespace network 
} // namespace xos 

#endif // _XOS_NETWORK_IP_V4_ENDPOINT_HPP 
