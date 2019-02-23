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
///   File: Socket.hpp
///
/// Author: $author$
///   Date: 9/26/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_NETWORK_SOCKET_HPP
#define _XOS_NETWORK_SOCKET_HPP

#include "xos/network/Endpoint.hpp"
#include "xos/base/Reference.hpp"
#include <sys/socket.h>

#define DEFAULT_SOCKET_LINGER_SECONDS 10

namespace xos {
namespace network {

typedef InterfaceBase SocketImplement;
///////////////////////////////////////////////////////////////////////
/// Class: Socket
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Socket: virtual public SocketImplement {
public:
    typedef SocketImplement Implements;

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ~Socket(){}

public:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    static Socket* New(int domain, int type, int protocol);
    static void Delete(Socket* s);

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Close() = 0;
    virtual bool Shutdown() = 0;
    virtual bool Shutdown(int how) = 0;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Connect(const struct sockaddr* addr, socklen_t addrlen) = 0;
    virtual bool Bind(const struct sockaddr* addr, socklen_t addrlen) = 0;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Listen() = 0;
    virtual bool Listen(int backlog) = 0;
    virtual Socket* Accept(struct sockaddr* addr, socklen_t* addrlen) = 0;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Send(const void* buf, size_t len, int flags) = 0;
    virtual ssize_t Recv(void* buf, size_t len, int flags) = 0;

    virtual ssize_t SendTo
    (const void* buf, size_t len, int flags, 
     const struct sockaddr* addr, socklen_t addrlen) = 0;
    virtual ssize_t RecvFrom
    (void* buf, size_t len, int flags, 
     struct sockaddr* addr, socklen_t* addrlen) = 0;

    virtual ssize_t SendMsg(const struct msghdr* msg, int flags) = 0;
    virtual ssize_t RecvMsg(struct msghdr* msg, int flags) = 0;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool SetDelayOpt(bool isOn = true) = 0;
    virtual bool SetNoDelayOpt(bool isOn = true) = 0;
    virtual bool SetLingerOpt(bool isOn = true, int lingerSeconds = -1) = 0;
    virtual bool SetDontLingerOpt(bool isOn = true, int lingerSeconds = 0) = 0;
    virtual bool SetOpt(int level, int name, const void* value, socklen_t length) = 0;
};

} // namespace network
} // namespace xos 

namespace xos {
///////////////////////////////////////////////////////////////////////
/// Class: Reference<network::Socket>
///////////////////////////////////////////////////////////////////////
template<>
void Reference<network::Socket>::Delete(network::Socket* instance);
} // namespace xos

namespace xos {
namespace network {

typedef Reference<Socket> SocketReference;

} // namespace network
} // namespace xos

#endif // _XOS_NETWORK_SOCKET_HPP
