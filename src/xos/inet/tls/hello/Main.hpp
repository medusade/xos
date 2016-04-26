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
///   File: Main.hpp
///
/// Author: $author$
///   Date: 4/23/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_TLS_HELLO_MAIN_HPP
#define _XOS_TLS_HELLO_MAIN_HPP

#include "xos/inet/tls/hello/MainOpt.hpp"
#include "xos/inet/tls/v12/ClientHello.hpp"
#include "xos/inet/tls/ServerHello.hpp"
#include "xos/inet/tls/ClientHello.hpp"
#include "xos/inet/tls/Client.hpp"
#include "xos/inet/tls/HeartbeatMessage.hpp"
#include "xos/network/SocketWriter.hpp"
#include "xos/network/SocketReader.hpp"
#include "xos/network/Sockets.hpp"
#include "xos/io/socket/Reader.hpp"
#include "xos/io/socket/Writer.hpp"
#include "xos/io/Reader.hpp"
#include "xos/io/Writer.hpp"
#include "xos/os/unix/Time.hpp"
#include "xos/base/Attacher.hpp"

namespace xos {
namespace tls {
namespace hello {

typedef xos::MainImplement MainImplement;
typedef xos::Main MainExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Main
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Main: virtual public MainImplement, public MainExtend {
public:
    typedef MainImplement Implements;
    typedef MainExtend Extends;
    typedef Main Derives;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Main()
    : m_runner(0),
      m_clientRunner(0),
      m_transport(XOS_TLS_HELLO_DEFAULT_TRANSPORT),
      m_family(XOS_TLS_HELLO_DEFAULT_FAMILY),
      m_host(XOS_TLS_HELLO_DEFAULT_HOST),
      m_port(XOS_TLS_HELLO_DEFAULT_PORT),
      m_portNo(XOS_TLS_HELLO_DEFAULT_PORTNO) {
    }
    virtual ~Main() {
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int Run(int argc, char** argv, char** env) {
        int err = 0;
        if ((m_runner)) {
            (this->*m_runner)(argc, argv, env);
        } else {
            Usage(argc, argv, env);
            err = 1;
        }
        return err;
    }
    virtual int BeforeRun(int argc, char** argv, char** env) {
        int err = 0;
        if (!(network::Sockets::Startup())) {
            err = 1;
        }
        return err;
    }
    virtual int AfterRun(int argc, char** argv, char** env) {
        int err = 0;
        if (!(network::Sockets::Cleanup())) {
            err = 1;
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int TcpClientRun(int argc, char** argv, char** env) {
        int err = 0;
        if ((m_clientRunner)) {
            network::Endpoint* ep = ClientEndpoint(m_host.c_str(), m_portNo);
            network::Socket* s = 0;

            if (s = (network::Socket::New(ep->GetFamily(), network::ip::tcp::Transport::Type, network::ip::tcp::Transport::Protocol))) {
                network::SocketReader r(s);
                network::SocketWriter w(s);

                XOS_LOG_MESSAGE_DEBUG("connecting " << m_host << ":" << m_portNo << "...");
                if ((s->Connect(ep->SocketAddress(), ep->SocketAddressLen()))) {
                    XOS_LOG_MESSAGE_DEBUG("...connected " << m_host << ":" << m_portNo << "");

                    s->SetNoDelayOpt();
                    s->SetDontLingerOpt();

                    err = (this->*m_clientRunner)(w, r, argc, argv, env);

                    XOS_LOG_MESSAGE_DEBUG("closing " << m_host << ":" << m_portNo << "...");
                    if ((s->Close())) {
                        XOS_LOG_MESSAGE_DEBUG("...closed " << m_host << ":" << m_portNo << "");
                    }
                }
                network::Socket::Delete(s);
            }
            delete ep;
        } else {
            Usage(argc, argv, env);
            err = 1;
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int TlsV10ClientRun
    (io::Writer& writer, io::Reader& reader, int argc, char** argv, char** env) {
        ProtocolVersion version;
        ClientHello hello
        (version, GmtUnixTime(), Random(), SessionID(), CipherSuite());

        return TlsClientRun
        (writer, reader, version, hello, argc, argv, env);
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int TlsV11ClientRun
    (io::Writer& writer, io::Reader& reader, int argc, char** argv, char** env) {
        ProtocolVersion version;
        ClientHello hello
        (version, GmtUnixTime(), Random(), SessionID(), CipherSuite());

        return TlsClientRun
        (writer, reader, version, hello, argc, argv, env);
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int TlsV12ClientRun
    (io::Writer& writer, io::Reader& reader, int argc, char** argv, char** env) {
        tls::v12::ProtocolVersion version;
        tls::v12::ClientHello hello
        (version, GmtUnixTime(), Random(), SessionID(), CipherSuite());

        return TlsClientRun
        (writer, reader, version, hello, argc, argv, env);
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int TlsV12HeartbeatClientRun
    (io::Writer& writer, io::Reader& reader, int argc, char** argv, char** env) {
        tls::v12::ProtocolVersion version;
        tls::HeartbeatMessage heartbeat(0x96, 96);
        Plaintext plain(CONTENT_TYPE_HEARTBEAT, version);

        XOS_LOG_MESSAGE_DEBUG("sending heartbeat...");
        if (0 < (plain.Write(writer, heartbeat))) {
            XOS_LOG_MESSAGE_DEBUG("...sent heartbeat");

            XOS_LOG_MESSAGE_DEBUG("receiving...")
            if (0 < (plain.Read(reader))) {
                XOS_LOG_MESSAGE_DEBUG("...received");
            }
        }
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int TlsClientRun
    (io::Writer& writer, io::Reader& reader,
     ProtocolVersion& version, ClientHello& hello,
     int argc, char** argv, char** env) {
        Handshake handshake(HANDSHAKE_TYPE_CLIENT_HELLO, hello);
        Plaintext plain(CONTENT_TYPE_HANDSHAKE, version);

        XOS_LOG_MESSAGE_DEBUG("sending hello...");
        if (0 < (plain.Write(writer, handshake))) {
            XOS_LOG_MESSAGE_DEBUG("...sent hello");

            XOS_LOG_MESSAGE_DEBUG("receiving...")
            if (0 < (plain.Read(reader))) {
                XOS_LOG_MESSAGE_DEBUG("...received");
                switch(plain.type()) {
                case CONTENT_TYPE_HANDSHAKE:
                    if (0 < (handshake.ReadMsgType(plain.fragment_reader()))) {
                        if (0 < (handshake.ReadLength(plain.fragment_reader()))) {
                            switch(handshake.msg_type()) {
                            case HANDSHAKE_TYPE_SERVER_HELLO: {
                                ServerHello server_hello;
                                server_hello.Read(plain.fragment_reader());
                                break; }
                            default:
                                break;
                            }
                        }
                    }
                    break;
                default:
                    break;
                }
            }
        }
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual tls::GmtUnixTime GmtUnixTime() {
        return current::GmtUnixTime();
    }
    virtual tls::Random Random() {
        return tls::Random(0x28);
    }
    virtual tls::SessionID SessionID() {
        return tls::SessionID(0x38);
    }
    virtual tls::CipherSuite CipherSuite() {
        return RSA_WITH_3DES_EDE_CBC_SHA;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual network::Endpoint* ClientEndpoint(const char* host, u_short port) {
        network::Endpoint* ep = 0;
        if ((m_clientEndpoint))
            ep = (this->*m_clientEndpoint)(host, port);
        else ep = ClientIpv4Endpoint(host, port);
        return ep;
    }
    virtual network::Endpoint* ServerEndpoint(const char* host, u_short port) {
        network::Endpoint* ep = 0;
        if ((m_serverEndpoint))
            ep = (this->*m_serverEndpoint)(host, port);
        else ep = ServerIpv4Endpoint(host, port);
        return ep;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual network::Endpoint* LocalEndpoint(const char* host, u_short port) {
        std::stringstream ss;
        ss << host;
        ss << port;
        network::Endpoint* ep = new network::local::Endpoint(ss.str().c_str());
        return ep;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual network::Endpoint* ClientIpv4Endpoint(const char* host, u_short port) {
        network::Endpoint* ep = new network::ip::v4::Endpoint(host, port);
        return ep;
    }
    virtual network::Endpoint* ServerIpv4Endpoint(const char* host, u_short port) {
        network::Endpoint* ep = new network::ip::v4::Endpoint(port);
        return ep;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual network::Endpoint* ClientIpv6Endpoint(const char* host, u_short port) {
        network::Endpoint* ep = new network::ip::v6::Endpoint(host, port);
        return ep;
    }
    virtual network::Endpoint* ServerIpv6Endpoint(const char* host, u_short port) {
        network::Endpoint* ep = new network::ip::v6::Endpoint(port);
        return ep;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int OnClientOption
    (int optval, const char* optarg,
     const char* optname, int optind,
     int argc, char**argv, char**env) {
        int err = 0;
        m_runner = &Derives::TcpClientRun;
        m_clientRunner = &Derives::TlsV10ClientRun;
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int OnTls10Option
    (int optval, const char* optarg,
     const char* optname, int optind,
     int argc, char**argv, char**env) {
        int err = 0;
        m_clientRunner = &Derives::TlsV10ClientRun;
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int OnTls11Option
    (int optval, const char* optarg,
     const char* optname, int optind,
     int argc, char**argv, char**env) {
        int err = 0;
        m_clientRunner = &Derives::TlsV11ClientRun;
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int OnTls12Option
    (int optval, const char* optarg,
     const char* optname, int optind,
     int argc, char**argv, char**env) {
        int err = 0;
        m_clientRunner = &Derives::TlsV12ClientRun;
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int OnTls12HeartbeatOption
    (int optval, const char* optarg,
     const char* optname, int optind,
     int argc, char**argv, char**env) {
        int err = 0;
        m_clientRunner = &Derives::TlsV12HeartbeatClientRun;
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int OnHostOption
    (int optval, const char* optarg,
     const char* optname, int optind,
     int argc, char**argv, char**env) {
        int err = 0;
        m_host.assign(optarg);
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int OnPortOption
    (int optval, const char* optarg,
     const char* optname, int optind,
     int argc, char**argv, char**env) {
        int err = 0;
        std::stringstream ss(optarg);
        ss >> m_portNo;
        m_port.assign(optarg);
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int OnIpV4FamilyOption
    (int optval, const char* optarg,
     const char* optname, int optind,
     int argc, char**argv, char**env) {
        int err = 0;
        m_family.assign(XOS_TLS_HELLO_FAMILY_OPTARG_IPV4_S);
        m_clientEndpoint = &Derives::ClientIpv4Endpoint;
        m_serverEndpoint = &Derives::ServerIpv4Endpoint;
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int OnIpV6FamilyOption
    (int optval, const char* optarg,
     const char* optname, int optind,
     int argc, char**argv, char**env) {
        int err = 0;
        m_family.assign(XOS_TLS_HELLO_FAMILY_OPTARG_IPV6_S);
        m_clientEndpoint = &Derives::ClientIpv6Endpoint;
        m_serverEndpoint = &Derives::ServerIpv6Endpoint;
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int OnLocalFamilyOption
    (int optval, const char* optarg,
     const char* optname, int optind,
     int argc, char**argv, char**env) {
        int err = 0;
        m_family.assign(XOS_TLS_HELLO_FAMILY_OPTARG_LOCAL_S);
        m_clientEndpoint = &Derives::LocalEndpoint;
        m_serverEndpoint = &Derives::LocalEndpoint;
        return err;
    }

#include "xos/inet/tls/hello/MainOpt.cpp"

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    typedef int (Derives::*Runner)(int argc, char** argv, char** env);
    typedef int (Derives::*ClientRunner)
    (io::Writer& writer, io::Reader& reader, int argc, char** argv, char** env);
    typedef network::Endpoint* (Derives::*Endpoint)(const char* host, u_short port);

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    Runner m_runner;
    ClientRunner m_clientRunner;
    Endpoint m_clientEndpoint, m_serverEndpoint;
    std::string m_transport, m_family, m_host, m_port;
    u_short m_portNo;
    char m_buf[4096];
};

} // namespace hello
} // namespace tls
} // namespace xos

#endif // _XOS_TLS_HELLO_MAIN_HPP
