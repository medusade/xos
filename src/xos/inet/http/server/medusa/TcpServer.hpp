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
///   File: TcpServer.hpp
///
/// Author: $author$
///   Date: 5/25/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_INET_HTTP_SERVER_MEDUSA_TCPSERVER_HPP
#define _XOS_INET_HTTP_SERVER_MEDUSA_TCPSERVER_HPP

#include "xos/inet/http/server/medusa/request/HeadersReader.hpp"
#include "xos/inet/http/server/medusa/request/HeaderReader.hpp"
#include "xos/inet/http/server/medusa/request/LineReader.hpp"
#include "xos/inet/http/server/medusa/TcpServerConfig.hpp"
#include "xos/inet/http/server/medusa/TcpConnection.hpp"
#include "xos/inet/http/server/medusa/TcpAccept.hpp"
#include "xos/inet/http/server/medusa/TcpService.hpp"
#include "xos/inet/http/server/medusa/Server.hpp"
#include "xos/inet/http/server/medusa/Service.hpp"
#include "xos/inet/http/server/Processor.hpp"
#include "xos/inet/http/Response.hpp"
#include "xos/inet/http/Request.hpp"
#include "xos/network/Sockets.hpp"
#include "xos/mt/os/Thread.hpp"

namespace xos {
namespace http {
namespace server {
namespace medusa {

typedef ServerImplement TcpServerImplement;
typedef Server TcpServerExtend;
///////////////////////////////////////////////////////////////////////
///  Class: TcpServer
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS TcpServer: virtual public TcpServerImplement, public TcpServerExtend {
public:
    typedef TcpServerImplement Implements;
    typedef TcpServerExtend Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    TcpServer
    (Processor& processor, const TcpServerConfig& config, bool start = false)
    : Extends(processor, config),
      m_config(config),
      m_host(config.ListenHost()),
      m_port(config.ListenPort()),
      m_ipVersion(config.ListenIpVersion()) {
        if (start) {
            if (!(Start())) {
                Exception e = FailedToStart;
                throw (e);
            }
        }
    }
    /*TcpServer
    (const TcpServerConfig& config, bool start = false)
    : Extends(config),
      m_config(config),
      m_host(config.ListenHost()),
      m_port(config.ListenPort()),
      m_ipVersion(config.ListenIpVersion()) {
        if (start) {
            if (!(Start())) {
                Exception e = FailedToStart;
                throw (e);
            }
        }
    }*/
    virtual ~TcpServer() {
        if (!(Finish())) {
            Exception e = FailedToFinish;
            throw (e);
        }
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Start() {
        network::Endpoint* ep;
        network::Socket* ls;
        TcpService* sv;
        TcpAccept* ac;
        mt::Thread* t;
        XOS_LOG_DEBUG("in...");
        if ((ep = Endpoint(m_host, m_port))) {
            XOS_LOG_DEBUG("...endpoint");
            if ((ls = Listen(*ep))) {
                XOS_LOG_DEBUG("...listen");
                if ((sv = Service(m_processor, m_connections, m_config))) {
                    XOS_LOG_DEBUG("...service");
                    if ((ac = Accept(m_connections, *sv, *ep, *ls))) {
                        XOS_LOG_DEBUG("...accept");
                        size_t n = 1, i;
                        for (i = 0; i < n; ++i) {
                            if ((t = Thread(*sv))) {
                                XOS_LOG_DEBUG("...service thread[" << i << "]");
                                m_threads.push_back(t);
                            }
                        }
                        if (i >= n) {
                            if ((t = Thread(*ac))) {
                                XOS_LOG_DEBUG("...accept thread");
                                m_threads.push_back(t);
                                m_accepts.push_back(ac);
                                m_services.push_back(sv);
                                m_sockets.push_back(ls);
                                m_endpoints.push_back(ep);
                                return true;
                            }
                        }
                        while (m_threads.begin() != m_threads.end()) {
                            t = m_threads.back();
                            m_threads.pop_back();
                            mt::Thread::Delete(t);
                        }
                        TcpAccept::Delete(ac);
                    }
                    TcpService::Delete(sv);
                }
                network::Socket::Delete(ls);
            }
            network::Endpoint::Delete(ep);
        }
        XOS_LOG_DEBUG("...out");
        return false;
    }
    virtual bool Finish() {
        bool success = true;
        network::Endpoint* ep;
        network::Socket* ls;
        TcpService* sv;
        TcpAccept* ac;
        mt::Thread* t;
        XOS_LOG_DEBUG("deleteing threads...");
        while (m_threads.begin() != m_threads.end()) {
            t = m_threads.back();
            m_threads.pop_back();
            mt::Thread::Delete(t);
        }
        XOS_LOG_DEBUG("deleteing accepts...");
        while (m_accepts.begin() != m_accepts.end()) {
            ac = m_accepts.back();
            m_accepts.pop_back();
            TcpAccept::Delete(ac);
        }
        XOS_LOG_DEBUG("deleteing services...");
        while (m_services.begin() != m_services.end()) {
            sv = m_services.back();
            m_services.pop_back();
            TcpService::Delete(sv);
        }
        XOS_LOG_DEBUG("deleteing sockets...");
        while (m_sockets.begin() != m_sockets.end()) {
            ls = m_sockets.back();
            m_sockets.pop_back();
            network::Socket::Delete(ls);
        }
        XOS_LOG_DEBUG("deleteing endpoints...");
        while (m_endpoints.begin() != m_endpoints.end()) {
            ep = m_endpoints.back();
            m_endpoints.pop_back();
            network::Endpoint::Delete(ep);
        }
        return success;
    }
    virtual bool Stop() {
        bool success = true;
        TcpService* sv;
        TcpAccept* ac;
        XOS_LOG_DEBUG("stopping accepts...");
        for (std::deque<TcpAccept*>::iterator i = m_accepts.begin(); i != m_accepts.end(); ++i) {
            if ((ac = (*i))) {
                ac->Stop();
            }
        }
        XOS_LOG_DEBUG("stopping services...");
        for (std::deque<TcpService*>::iterator i = m_services.begin(); i != m_services.end(); ++i) {
            if ((sv = (*i))) {
                sv->Stop();
            }
        }
        return success;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual mt::Thread* Thread(TcpService& sv) {
        mt::Thread* t = new mt::os::Thread(sv);
        return t;
    }
    virtual mt::Thread* Thread(TcpAccept& ac) {
        mt::Thread* t = new mt::os::Thread(ac);
        return t;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual TcpAccept* Accept
    (TcpConnections& connections, TcpService& service,
     network::Endpoint& endpoint, network::Socket& listen) {
        TcpAccept* accept = new TcpAccept
        (connections, service, endpoint, listen);
        return accept;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual TcpService* Service
    (Processor& processor, TcpConnections& connections, const TcpServerConfig& serverConfig) {
        TcpService* service = new TcpService(processor, connections, serverConfig);
        return service;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual network::Socket* Listen(network::Endpoint& ep) {
        network::Socket* s = 0;
        if (s = (network::Socket::New(ep.GetFamily(), network::ip::tcp::Transport::Type, network::ip::tcp::Transport::Protocol))) {
            if ((s->Bind(ep.SocketAddress(), ep.SocketAddressLen()))) {
                if ((s->Listen())) {
                    return s;
                }
            }
            network::Socket::Delete(s);
        }
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual network::Endpoint* Endpoint(const String& host, unsigned port) {
        if (6 == (m_ipVersion))
            return Ipv6Endpoint(host, port);
        return Ipv4Endpoint(host, port);
    }
    virtual network::Endpoint* Ipv4Endpoint(const String& host, unsigned port) {
        network::Endpoint* ep = new network::ip::v4::Endpoint(host, port);
        return ep;
    }
    virtual network::Endpoint* Ipv6Endpoint(const String& host, unsigned port) {
        network::Endpoint* ep = new network::ip::v6::Endpoint(host, port);
        return ep;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    const TcpServerConfig& m_config;
    String m_host;
    unsigned m_port;
    int m_ipVersion;
    TcpConnections m_connections;
    std::deque<network::Endpoint*> m_endpoints;
    std::deque<network::Socket*> m_sockets;
    std::deque<TcpService*> m_services;
    std::deque<TcpAccept*> m_accepts;
    std::deque<mt::Thread*> m_threads;
};

} // namespace medusa 
} // namespace server 
} // namespace http 
} // namespace xos 

#endif // _XOS_INET_HTTP_SERVER_MEDUSA_TCPSERVER_HPP 
