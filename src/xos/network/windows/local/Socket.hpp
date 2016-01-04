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
///   Date: 10/1/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_NETWORK_WINDOWS_LOCAL_SOCKET_HPP
#define _XOS_NETWORK_WINDOWS_LOCAL_SOCKET_HPP

#include "xos/network/Socket.hpp"
#include "xos/network/local/Endpoint.hpp"
#include "xos/os/windows/NamedPipe.hpp"
#include "xos/os/Logger.hpp"
#include "xos/base/String.hpp"

namespace xos {
namespace network {
namespace windows {
namespace local {

typedef network::Socket SocketImplement;
typedef ExportBase SocketExtend;

class _EXPORT_CLASS Socket
: virtual public SocketImplement,
  public SocketExtend
{
public:
    typedef SocketImplement Implements;
    typedef SocketExtend Extends;

    Socket(){}
    virtual ~Socket() {
        if ((m_pipe.IsOpen())) {
            if (!(m_pipe.Close())) {
                XOS_LOG_ERROR("failed on Close()");
                throw (Error(Error::Failed));
            }
        }
    }
    virtual bool Close() { 
        return m_pipe.Close(); }
    virtual bool Shutdown() { 
        return Shutdown(SD_BOTH); }
    virtual bool Shutdown(int how) { 
        return false; }

    virtual bool Connect(const struct sockaddr* addr, socklen_t addrlen) { 
        if (!(m_pipe.IsOpen())) {
            if ((addr) && (sizeof(struct sockaddr_un) == (addrlen))) {
                if (network::local::Endpoint::Family == (addr->sa_family)) {
                    struct sockaddr_un& addrUn = (struct sockaddr_un&)(*addr);
                    xos::StringT<tchar_t> path(addrUn.sun_path);
                    if ((m_pipe.Open(path.c_str()))) {
                        return true;
                    }
                }
            }
        }
        return false; }
    virtual bool Bind(const struct sockaddr* addr, socklen_t addrlen) { 
        if (!(m_pipe.IsOpen())) {
            if ((addr) && (sizeof(struct sockaddr_un) == (addrlen))) {
                if (network::local::Endpoint::Family == (addr->sa_family)) {
                    struct sockaddr_un& addrUn = (struct sockaddr_un&)(*addr);
                    m_bound.assign(addrUn.sun_path);
                    return true;
                }
            }
        }
        return false; }

    virtual bool Listen() { 
        return Listen(SOMAXCONN); }
    virtual bool Listen(int backlog) { 
        if ((!(m_pipe.IsOpen())) && (0 < m_bound.length())) {
            xos::StringT<tchar_t> named(m_bound.c_str());
            if ((m_pipe.Create(named.c_str()))) {
                return true;
            }
        }
        return false; }
    virtual network::Socket* Accept(struct sockaddr* addr, socklen_t* addrlen) { 
        Socket* s = 0; 
        if ((m_pipe.Connect())) {
            if ((s = new Socket())) {
                s->m_pipe.AttachConnected(m_pipe.AttachedTo());
            }
        }
        return s; }

    virtual ssize_t Send(const void* buf, size_t len, int flags) { 
        ssize_t count = m_pipe.Write(buf, len); 
        return count; }
    virtual ssize_t Recv(void* buf, size_t len, int flags) { 
        ssize_t count = m_pipe.Read(buf, len); 
        return count; }

    virtual ssize_t SendTo
    (const void* buf, size_t len, int flags, 
     const struct sockaddr* addr, socklen_t addrlen) { 
        ssize_t count = -1; 
        return count; }
    virtual ssize_t RecvFrom
    (void* buf, size_t len, int flags, 
     struct sockaddr* addr, socklen_t* addrlen) { 
        ssize_t count = -1; 
        return count; }

    virtual ssize_t SendMsg(const struct msghdr* msg, int flags) { 
        ssize_t count = -1; 
        return count; }
    virtual ssize_t RecvMsg(struct msghdr* msg, int flags) { 
        ssize_t count = -1; 
        return count; }

    virtual bool SetDelayOpt(bool isOn = true) {
        return false; }
    virtual bool SetNoDelayOpt(bool isOn = true) {
        return false; }
    virtual bool SetLingerOpt(bool isOn = true, int lingerSeconds = -1) {
        return false; }
    virtual bool SetDontLingerOpt(bool isOn = true, int lingerSeconds = 0) {
        return false; }
    virtual bool SetOpt(int level, int name, const void* value, socklen_t length) {
        return false; }
protected:
    std::string m_bound;
    os::windows::NamedPipe m_pipe;
};

} // namespace local 
} // namespace windows 
} // namespace network 
} // namespace xos 

#endif // _XOS_NETWORK_WINDOWS_LOCAL_SOCKET_HPP 
        

