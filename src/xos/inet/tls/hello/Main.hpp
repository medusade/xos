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
#ifndef _XOS_TLS_MAIN_HPP
#define _XOS_TLS_MAIN_HPP

#include "xos/os/Main.hpp"
#include "xos/os/unix/Time.hpp"
#include "xos/network/Sockets.hpp"
#include "xos/io/socket/Reader.hpp"
#include "xos/io/socket/Writer.hpp"
#include "xos/io/Reader.hpp"
#include "xos/io/Writer.hpp"
#include "xos/base/Attacher.hpp"
#include "xos/inet/tls/Client.hpp"

#define XOS_HELLO_2STRING_(value) #value
#define XOS_HELLO_2STRING(value) XOS_HELLO_2STRING_(value)

#define XOS_HELLO_DEFAULT_PORTNO 443
#define XOS_HELLO_DEFAULT_PORT "" XOS_HELLO_2STRING(XOS_HELLO_DEFAULT_PORTNO) ""
#define XOS_HELLO_DEFAULT_HOST "localhost"

#define XOS_HELLO_DEFAULT_TRANSPORT "t"
#define XOS_HELLO_DEFAULT_FAMILY "4"

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
#define XOS_HELLO_CLIENT_OPT "client"
#define XOS_HELLO_CLIENT_OPTARG_REQUIRED XOS_MAIN_OPT_ARGUMENT_NONE
#define XOS_HELLO_CLIENT_OPTARG ""
#define XOS_HELLO_CLIENT_OPTUSE ""
#define XOS_HELLO_CLIENT_OPTVAL_S "c"
#define XOS_HELLO_CLIENT_OPTVAL_C 'c'

#define XOS_HELLO_CLIENT_OPTIONS_OPTION \
   {XOS_HELLO_CLIENT_OPT, \
    XOS_HELLO_CLIENT_OPTARG_REQUIRED, 0, \
    XOS_HELLO_CLIENT_OPTVAL_C},

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
#define XOS_HELLO_HOST_OPT "host"
#define XOS_HELLO_HOST_OPTARG_REQUIRED XOS_MAIN_OPT_ARGUMENT_REQUIRED
#define XOS_HELLO_HOST_OPTARG "name"
#define XOS_HELLO_HOST_OPTUSE "Host Name or Address"
#define XOS_HELLO_HOST_OPTVAL_S "o:"
#define XOS_HELLO_HOST_OPTVAL_C 'o'

#define XOS_HELLO_HOST_OPTIONS_OPTION \
   {XOS_HELLO_HOST_OPT, \
    XOS_HELLO_HOST_OPTARG_REQUIRED, 0, \
    XOS_HELLO_HOST_OPTVAL_C},

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
#define XOS_HELLO_PORT_OPT "port"
#define XOS_HELLO_PORT_OPTARG_REQUIRED XOS_MAIN_OPT_ARGUMENT_REQUIRED
#define XOS_HELLO_PORT_OPTARG "number"
#define XOS_HELLO_PORT_OPTUSE "Port Number"
#define XOS_HELLO_PORT_OPTVAL_S "p:"
#define XOS_HELLO_PORT_OPTVAL_C 'p'

#define XOS_HELLO_PORT_OPTIONS_OPTION \
   {XOS_HELLO_PORT_OPT, \
    XOS_HELLO_PORT_OPTARG_REQUIRED, 0, \
    XOS_HELLO_PORT_OPTVAL_C},

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
#define XOS_HELLO_FAMILY_OPT "address-family"
#define XOS_HELLO_FAMILY_OPTARG_REQUIRED XOS_MAIN_OPT_ARGUMENT_REQUIRED
#define XOS_HELLO_FAMILY_OPTARG_IPV4_S "4"
#define XOS_HELLO_FAMILY_OPTARG_IPV4_C '4'
#define XOS_HELLO_FAMILY_OPTARG_IPV6_S "6"
#define XOS_HELLO_FAMILY_OPTARG_IPV6_C '6'
#define XOS_HELLO_FAMILY_OPTARG_LOCAL_S "l"
#define XOS_HELLO_FAMILY_OPTARG_LOCAL_C 'l'
#define XOS_HELLO_FAMILY_OPTARG "{(4)ipv4 | (6)ipv6 | (l)local}"
#define XOS_HELLO_FAMILY_OPTUSE "Address Family"
#define XOS_HELLO_FAMILY_OPTVAL_S "f:"
#define XOS_HELLO_FAMILY_OPTVAL_C 'f'

#define XOS_HELLO_FAMILY_OPTIONS_OPTION \
   {XOS_HELLO_FAMILY_OPT, \
    XOS_HELLO_FAMILY_OPTARG_REQUIRED, 0, \
    XOS_HELLO_FAMILY_OPTVAL_C},

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
#define XOS_HELLO_OPTIONS_CHARS \
    XOS_HELLO_CLIENT_OPTVAL_S \
    XOS_HELLO_HOST_OPTVAL_S \
    XOS_HELLO_PORT_OPTVAL_S \
    XOS_HELLO_FAMILY_OPTVAL_S \
    XOS_MAIN_OPTIONS_CHARS

#define XOS_HELLO_OPTIONS_OPTIONS \
    XOS_HELLO_CLIENT_OPTIONS_OPTION \
    XOS_HELLO_HOST_OPTIONS_OPTION \
    XOS_HELLO_PORT_OPTIONS_OPTION \
    XOS_HELLO_FAMILY_OPTIONS_OPTION \
    XOS_MAIN_OPTIONS_OPTIONS

namespace xos {
namespace network {

typedef AttachedT<network::Socket*, int, 0, io::socket::Reader> SocketReader;
typedef AttachedT<network::Socket*, int, 0, io::socket::Writer> SocketWriter;

} // namespace network
namespace tls {
namespace hello {

typedef MainImplement MainImplement;
typedef Main MainExtend;
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
      m_transport(XOS_HELLO_DEFAULT_TRANSPORT),
      m_family(XOS_HELLO_DEFAULT_FAMILY),
      m_host(XOS_HELLO_DEFAULT_HOST),
      m_port(XOS_HELLO_DEFAULT_PORT),
      m_portNo(XOS_HELLO_DEFAULT_PORTNO) {
    }
    virtual ~Main() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    //
    // TCP
    //
    virtual int RunTcpClient(int argc, char** argv, char** env) {
        network::Endpoint* ep = ClientEndpoint(m_host.c_str(), m_portNo);
        network::Socket* s = 0;
        if (s = (network::Socket::New(ep->GetFamily(), network::ip::tcp::Transport::Type, network::ip::tcp::Transport::Protocol))) {
            network::SocketReader r(s);
            network::SocketWriter w(s);
            XOS_LOG_DEBUG("connecting " << m_host << ":" << m_portNo << "...");
            if ((s->Connect(ep->SocketAddress(), ep->SocketAddressLen()))) {
                //s->SetNoDelayOpt();
                //s->SetLingerOpt();
                XOS_LOG_DEBUG("...connected " << m_host << ":" << m_portNo << "");

                RunTlsClient(w, r, argc, argv, env);

                XOS_LOG_DEBUG("closing " << m_host << ":" << m_portNo << "...");
                if ((s->Close())) {
                    XOS_LOG_DEBUG("...closed " << m_host << ":" << m_portNo << "");
                }
            }
            network::Socket::Delete(s);
        }
        delete ep;
        return 0;
    }
    virtual int RunTlsClient
    (io::Writer& writer, io::Reader& reader, int argc, char** argv, char** env) {
        ContentType content_type = CONTENT_TYPE_HANDSHAKE;
        ProtocolVersion protocol_version;
        uint32_t gmt_unix_time = (unix::Time::Uint32GmtCurrent)(unix::Time());
        opaque random_byte = 0x42;
        opaque session_id = 0x38;
        uint16_t cipher_suite = RSA_WITH_3DES_EDE_CBC_SHA;
        ClientHello hello(gmt_unix_time, random_byte, session_id, cipher_suite);
        Handshake helloHandshake(HANDSHAKE_TYPE_CLIENT_HELLO, hello);
        Plaintext plain(content_type, protocol_version);

        XOS_LOG_DEBUG("sending hello...");
        if (0 < (plain.Write(writer, helloHandshake))) {
            XOS_LOG_DEBUG("...sent hello");

            XOS_LOG_DEBUG("receiving...")
            if (0 < (plain.Read(reader))) {
                XOS_LOG_DEBUG("...received");
            }
        }
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int Run(int argc, char** argv, char** env) {
        if ((m_runner)) {
            (this->*m_runner)(argc, argv, env);
        }
        return 0;
    }
    virtual int BeforeRun(int argc, char** argv, char** env) {
        network::Sockets::Startup();
        return 0;
    }
    virtual int AfterRun(int argc, char** argv, char** env) {
        network::Sockets::Cleanup();
        return 0;
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
    virtual int OnOption
    (int optval, const char* optarg,
     const char* optname, int optind,
     int argc, char**argv, char**env) {
        int err = 0;
        switch(optval) {
        case XOS_HELLO_CLIENT_OPTVAL_C:
            m_runner = &Derives::RunTcpClient;
            break;
        case XOS_HELLO_HOST_OPTVAL_C:
            m_host.assign(optarg);
            break;
        case XOS_HELLO_PORT_OPTVAL_C:
            {
                std::stringstream ss(optarg);
                ss >> m_portNo;
                m_port.assign(optarg);
            }
            break;
        case XOS_HELLO_FAMILY_OPTVAL_C:
            switch(tolower(optarg[0])) {
            case XOS_HELLO_FAMILY_OPTARG_IPV4_C:
                m_family.assign(XOS_HELLO_FAMILY_OPTARG_IPV4_S);
                m_clientEndpoint = &Derives::ClientIpv4Endpoint;
                m_serverEndpoint = &Derives::ServerIpv4Endpoint;
                break;

            case XOS_HELLO_FAMILY_OPTARG_IPV6_C:
                m_family.assign(XOS_HELLO_FAMILY_OPTARG_IPV6_S);
                m_clientEndpoint = &Derives::ClientIpv6Endpoint;
                m_serverEndpoint = &Derives::ServerIpv6Endpoint;
                break;

            case XOS_HELLO_FAMILY_OPTARG_LOCAL_C:
                m_family.assign(XOS_HELLO_FAMILY_OPTARG_LOCAL_S);
                m_clientEndpoint = &Derives::LocalEndpoint;
                m_serverEndpoint = &Derives::LocalEndpoint;
                break;
            }
            break;
        default:
            err = Extends::OnOption(optval, optarg, optname, optind, argc, argv, env);
        }
        return err;
    }
    virtual const char* OptionUsage
    (const char*& optarg, const struct option* longopt) {
        const char* chars = "";
        switch(longopt->val) {
        case XOS_HELLO_CLIENT_OPTVAL_C:
            optarg = XOS_HELLO_CLIENT_OPTARG;
            chars = XOS_HELLO_CLIENT_OPTUSE;
            break;

        case XOS_HELLO_HOST_OPTVAL_C:
            optarg = XOS_HELLO_HOST_OPTARG;
            chars = XOS_HELLO_HOST_OPTUSE;
            break;

        case XOS_HELLO_PORT_OPTVAL_C:
            optarg = XOS_HELLO_PORT_OPTARG;
            chars = XOS_HELLO_PORT_OPTUSE;
            break;

        case XOS_HELLO_FAMILY_OPTVAL_C:
            optarg = XOS_HELLO_FAMILY_OPTARG;
            chars = XOS_HELLO_FAMILY_OPTUSE;
            break;
        default:
            chars = Extends::OptionUsage(optarg, longopt);
        }
        return chars;
    }
    virtual const char* Options(const struct option*& longopts) {
        static const char* chars = XOS_HELLO_OPTIONS_CHARS;
        static struct option optstruct[]= {
            XOS_HELLO_OPTIONS_OPTIONS
            {0, 0, 0, 0}};
        longopts = optstruct;
        return chars;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    typedef int (Derives::*Runner)(int argc, char** argv, char** env);
    typedef network::Endpoint* (Derives::*Endpoint)(const char* host, u_short port);

protected:
    Runner m_runner;
    Endpoint m_clientEndpoint;
    Endpoint m_serverEndpoint;
    std::string m_transport;
    std::string m_family;
    std::string m_host;
    std::string m_port;
    u_short m_portNo;
    char m_buf[4096];
};

} // namespace hello
} // namespace tls
} // namespace xos

#endif // _XOS_TLS_MAIN_HPP 
