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
#ifndef _XOS_NETWORK_ENDPOINT_HPP
#define _XOS_NETWORK_ENDPOINT_HPP

#include "xos/network/Address.hpp"
#include "xos/os/Logger.hpp"

namespace xos {
namespace network {

typedef AddressImplement EndpointImplement;

class _EXPORT_CLASS Endpoint
: virtual public EndpointImplement
{
public:
    typedef EndpointImplement Implements;

    virtual ~Endpoint() {}

    virtual bool Init(const char* host, u_short port) {
        struct addrinfo* addrs = 0;
        int err = 0;
        XOS_LOG_DEBUG("getting address info...");
        if (!(err = getaddrinfo(host, 0, 0, &addrs))) {
            struct addrinfo* addr = 0;
            XOS_LOG_DEBUG("...got address info");
            for (addr = addrs; addr; addr = addr->ai_next) {
                char addrHost[NI_MAXHOST];
                if (!(err = getnameinfo(addr->ai_addr, addr->ai_addrlen, addrHost, sizeof(addrHost)-1, 0, 0, 0))) {
                    addrHost[sizeof(addrHost)-1] = 0;
                    XOS_LOG_DEBUG("Host:\"" << addrHost << "\"");
                    if (GetFamily() == (addr->ai_family)) {
                        XOS_LOG_DEBUG("...found address");
                        Init(addr->ai_addr, addr->ai_addrlen, port);
                        return true;
                    }
                } else {
                    XOS_LOG_ERROR("failed " << Sockets::GetLastError() << " on getnameinfo()");
                }
            }
            freeaddrinfo(addrs);
        } else {
            XOS_LOG_ERROR("failed " << Sockets::GetLastError() << " on getaddrinfo(\"" << host << "\",...)");
        }
        return false;
    }
    virtual bool Init(const struct sockaddr* socketAddress, socklen_t socketAddressLen, u_short port) {
        return false;
    }
    virtual bool Init(u_short port) {
        return false;
    }
    virtual bool Init() {
        return true;
    }
    virtual bool Fini() {
        return true;
    }

    virtual struct sockaddr* SocketAddress() const {
        return 0;
    }
    virtual socklen_t& SocketAddressLen() const {
        static socklen_t socketAddressLen = 0;
        return socketAddressLen;
    }
    virtual operator struct sockaddr* () const {
        return SocketAddress();
    }

    static void Delete(Endpoint* instance) {
        delete instance;
    }
};

} // namespace xos 
} // namespace network 

#endif // _XOS_NETWORK_ENDPOINT_HPP 
