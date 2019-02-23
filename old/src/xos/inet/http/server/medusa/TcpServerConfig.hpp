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
///   File: TcpServerConfig.hpp
///
/// Author: $author$
///   Date: 6/6/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_INET_HTTP_SERVER_MEDUSA_TCPSERVERCONFIG_HPP
#define _XOS_INET_HTTP_SERVER_MEDUSA_TCPSERVERCONFIG_HPP

#include "xos/inet/http/server/medusa/ServerConfig.hpp"

#define XOS_INET_HTTP_SERVER_MEDUSA_TCPSERVERCONFIG_LISTEN_HOST "localhost"
#define XOS_INET_HTTP_SERVER_MEDUSA_TCPSERVERCONFIG_LISTEN_PORT 8080
#define XOS_INET_HTTP_SERVER_MEDUSA_TCPSERVERCONFIG_LISTEN_IP_VERSION 4

namespace xos {
namespace http {
namespace server {
namespace medusa {

typedef ServerConfigImplement TcpServerConfigImplement;
typedef ServerConfig TcpServerConfigExtend;
///////////////////////////////////////////////////////////////////////
///  Class: TcpServerConfig
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS TcpServerConfig
: virtual public TcpServerConfigImplement, public TcpServerConfigExtend {
public:
    typedef TcpServerConfigImplement Implements;
    typedef TcpServerConfigExtend Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    TcpServerConfig
    (const String& documentRoot, const String& listenHost, unsigned listenPort,
     int listenIpVersion = XOS_INET_HTTP_SERVER_MEDUSA_TCPSERVERCONFIG_LISTEN_IP_VERSION)
    : Extends(documentRoot), m_listenHost(listenHost),
      m_listenPort(listenPort), m_listenIpVersion(listenIpVersion) {
    }
    TcpServerConfig
    (const String& listenHost, unsigned listenPort,
     int listenIpVersion = XOS_INET_HTTP_SERVER_MEDUSA_TCPSERVERCONFIG_LISTEN_IP_VERSION)
    : m_listenHost(listenHost), m_listenPort(listenPort), m_listenIpVersion(listenIpVersion) {
    }
    TcpServerConfig()
    : m_listenHost(XOS_INET_HTTP_SERVER_MEDUSA_TCPSERVERCONFIG_LISTEN_HOST),
      m_listenPort(XOS_INET_HTTP_SERVER_MEDUSA_TCPSERVERCONFIG_LISTEN_PORT),
      m_listenIpVersion(XOS_INET_HTTP_SERVER_MEDUSA_TCPSERVERCONFIG_LISTEN_IP_VERSION) {
    }
    virtual ~TcpServerConfig() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const String& SetListenHost(const String& to) {
        m_listenHost = (to);
        return m_listenHost;
    }
    virtual const String& ListenHost() const {
        return m_listenHost;
    }
    virtual String& listenHost() const {
        return ((String&)m_listenHost);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual unsigned SetListenPort(unsigned to) {
        m_listenPort = (to);
        return m_listenPort;
    }
    virtual unsigned ListenPort() const {
        return m_listenPort;
    }
    virtual unsigned& listenPort() const {
        return ((unsigned&)m_listenPort);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int SetListenIpVersion(int to) {
        m_listenIpVersion = (to);
        return m_listenIpVersion;
    }
    virtual int ListenIpVersion() const {
        return m_listenIpVersion;
    }
    virtual int& listenIpVersion() const {
        return ((int&)m_listenIpVersion);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    String m_listenHost;
    unsigned m_listenPort;
    int m_listenIpVersion;
};

} // namespace medusa 
} // namespace server 
} // namespace http 
} // namespace xos 

#endif // _XOS_INET_HTTP_SERVER_MEDUSA_TCPSERVERCONFIG_HPP 
