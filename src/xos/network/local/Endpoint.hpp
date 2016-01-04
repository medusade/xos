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
#ifndef _XOS_NETWORK_LOCAL_ENDPOINT_HPP
#define _XOS_NETWORK_LOCAL_ENDPOINT_HPP

#include "xos/network/Endpoint.hpp"
#include "xos/network/local/Address.hpp"

namespace xos {
namespace network {
namespace local {

typedef network::Endpoint EndpointImplement;
typedef Address EndpointExtend;

class _EXPORT_CLASS Endpoint
: virtual public EndpointImplement,
  public EndpointExtend
{
public:
    typedef EndpointImplement Implements;
    typedef EndpointExtend Extends;

    Endpoint(const char* path){
        Init(path);
    }
    Endpoint(){
        Init();
    }
    virtual ~Endpoint(){}

    virtual bool Init(const char* path) {
        Init();
        strncpy(m_socketAddress.sun_path, path, sizeof(m_socketAddress.sun_path)-1);
        m_socketAddress.sun_path[sizeof(m_socketAddress.sun_path)-1] = 0;
        return true;
    }
    virtual bool Init() {
        memset(&m_socketAddress, 0, m_socketAddressLen = (sizeof(m_socketAddress)));
        m_socketAddress.sun_family = Family;
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
    struct sockaddr_un m_socketAddress;
};

} // namespace local 
} // namespace network 
} // namespace xos 

#endif // _XOS_NETWORK_LOCAL_ENDPOINT_HPP 
