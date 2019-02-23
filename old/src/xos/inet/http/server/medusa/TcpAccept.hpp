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
///   File: TcpAccept.hpp
///
/// Author: $author$
///   Date: 5/26/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_INET_HTTP_SERVER_MEDUSA_TCPACCEPT_HPP
#define _XOS_INET_HTTP_SERVER_MEDUSA_TCPACCEPT_HPP

#include "xos/inet/http/server/medusa/TcpConnection.hpp"
#include "xos/inet/http/server/medusa/TcpService.hpp"
#include "xos/mt/os/Thread.hpp"

namespace xos {
namespace http {
namespace server {
namespace medusa {

typedef mt::RunImplement TcpAcceptImplement;
typedef mt::Run TcpAcceptExtend;
///////////////////////////////////////////////////////////////////////
///  Class: TcpAccept
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS TcpAccept
: virtual public TcpAcceptImplement, public TcpAcceptExtend {
public:
    typedef TcpAcceptImplement Implements;
    typedef TcpAcceptExtend Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    TcpAccept
    (TcpConnections& connections, TcpService& service,
     network::Endpoint& endpoint, network::Socket& listen)
    : m_connections(connections), m_service(service),
      m_endpoint(endpoint), m_listen(listen),
      m_done(false) {
    }
    virtual ~TcpAccept() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Stop() {
        SetDone();
        return m_listen.Close();
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool SetDone(bool isTrue = true) {
        m_done = isTrue;
        return m_done;
    }
    virtual bool Done() {
        return m_done;
    }
    static void Delete(TcpAccept* instance) {
        delete instance;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void operator()(){
        network::Socket* sock = 0;
        XOS_LOG_DEBUG("in...");
        do {
            XOS_LOG_TRACE("accept socket...");
            if ((sock = m_listen.Accept(m_endpoint.SocketAddress(), &m_endpoint.SocketAddressLen()))) {
                XOS_LOG_DEBUG("...accepted socket");
                network::SocketReference sockref(sock);
                TcpConnection connection(sockref);
                m_connections.Add(connection);
            } else {
                XOS_LOG_DEBUG("...failed on accept socket");
                break;
            }
        } while (!(Done()));
        XOS_LOG_DEBUG("...out");
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    TcpConnections& m_connections;
    TcpService& m_service;
    network::Endpoint& m_endpoint;
    network::Socket& m_listen;
    bool m_done;
};

} // namespace medusa
} // namespace server 
} // namespace http 
} // namespace xos 

#endif // _XOS_INET_HTTP_SERVER_MEDUSA_TCPACCEPT_HPP 
