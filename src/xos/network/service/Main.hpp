///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2013 $organization$
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
///   Date: 2/16/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_NETWORK_SERVICE_MAIN_HPP
#define _XOS_NETWORK_SERVICE_MAIN_HPP

#include "xos/os/Main.hpp"
#include "xos/os/os/Mutexes.hpp"
#include "xos/os/os/Semaphores.hpp"
#include "xos/os/os/Threads.hpp"
#include "xos/os/os/Process.hpp"
#include "xos/network/Sockets.hpp"
#include "xos/base/Locker.hpp"
#include <sstream>
#include <deque>
#include <queue>

#define XOS_NETWORK_SERVICE_2STRING_(value) #value
#define XOS_NETWORK_SERVICE_2STRING(value) XOS_NETWORK_SERVICE_2STRING_(value)

#define XOS_NETWORK_SERVICE_DEFAULT_HELLO "Hello"
#define XOS_NETWORK_SERVICE_DEFAULT_BYE "Bye"

#define XOS_NETWORK_SERVICE_DEFAULT_PORTNO 7000
#define XOS_NETWORK_SERVICE_DEFAULT_PORT "" XOS_NETWORK_SERVICE_2STRING(XOS_NETWORK_SERVICE_DEFAULT_PORTNO) ""
#define XOS_NETWORK_SERVICE_DEFAULT_HOST "localhost"

#define XOS_NETWORK_SERVICE_DEFAULT_THREADSNO 0
#define XOS_NETWORK_SERVICE_DEFAULT_THREADS "" XOS_NETWORK_SERVICE_2STRING(XOS_NETWORK_SERVICE_DEFAULT_THREADSNO) ""

#define XOS_NETWORK_SERVICE_DEFAULT_TRANSPORT "t"
#define XOS_NETWORK_SERVICE_DEFAULT_FAMILY "4"

#define XOS_NETWORK_SERVICE_OPTIONS_CHARS "m:c:s:r:wat:o:p:f:" XOS_MAIN_OPTIONS_CHARS
#define XOS_NETWORK_SERVICE_OPTIONS_OPTIONS \
            {"service-message", MAIN_OPT_ARGUMENT_REQUIRED, 0, 'm'},\
            {"service-client", MAIN_OPT_ARGUMENT_REQUIRED, 0, 'c'},\
            {"service-server", MAIN_OPT_ARGUMENT_REQUIRED, 0, 's'},\
            {"start-service-process", MAIN_OPT_ARGUMENT_REQUIRED, 0, 'r'},\
            {"wait-service-process", MAIN_OPT_ARGUMENT_NONE, 0, 'w'},\
            {"native-service-process", MAIN_OPT_ARGUMENT_NONE, 0, 'n'},\
            {"service-threads", MAIN_OPT_ARGUMENT_REQUIRED, 0, 't'},\
            {"service-host", MAIN_OPT_ARGUMENT_REQUIRED, 0, 'o'},\
            {"service-port", MAIN_OPT_ARGUMENT_REQUIRED, 0, 'p'},\
            {"service-address-family", MAIN_OPT_ARGUMENT_REQUIRED, 0, 'f'},\
            XOS_MAIN_OPTIONS_OPTIONS

#define XOS_NETWORK_SERVICE_DEFAULT_DATA_BUFFER_SIZE 4096

namespace xos {
namespace network {
namespace service {

typedef MainImplement MainImplement;
typedef Main MainExtend;

class _EXPORT_CLASS Main: virtual public MainImplement, public MainExtend {
public:
    typedef MainImplement Implements;
    typedef MainExtend Extends;
    typedef Main Derives;

    typedef int (Derives::*Runner)(int argc, char** argv, char** env);
    typedef network::Endpoint* (Derives::*Endpoint)(const char* host, u_short port);

    class _EXPORT_CLASS TcpConnections {
    public:
        TcpConnections(network::Socket& s, network::Socket* c): m_s(s), m_cleared(false) {
            Queue(c);
        }
        TcpConnections(network::Socket& s): m_s(s), m_cleared(false) {}
        virtual ~TcpConnections() {
            void Clear();
        }

        void Clear() {
            Locker<Mutex> l(m_lock);
            while (0 < (m_queue.size())) {
                network::Socket* c = 0;
                if ((c = m_queue.front())) {
                    c->Shutdown();
                    network::Socket::Delete(c);
                }
                m_queue.pop();
            }
            m_cleared = true;
            m_s.Shutdown();
            m_s.Close();
            m_signal.Continue();
        }
        void Queue(network::Socket* c) {
            Locker<Mutex> l(m_lock);
            m_queue.push(c);
            XOS_LOG_TRACE("queued socket...");
            m_signal.Continue();
        }
        network::Socket* Dequeue() {
            network::Socket* c = 0;
            XOS_LOG_TRACE("wait signal...");
            if ((m_signal.Wait())) {
                Locker<Mutex> l(m_lock);
                if (0 < (m_queue.size())) {
                    c = m_queue.front();
                    m_queue.pop();
                    XOS_LOG_TRACE("...dequeued socket");
                } else {
                    XOS_LOG_TRACE("...queue empty");
                    if ((m_cleared)) {
                        m_signal.Continue();
                    }
                }
            } else {
                XOS_LOG_TRACE("...failed on wait signal");
            }
            return c;
        }
    protected:
        network::Socket& m_s;
        bool m_cleared;
        os::Mutex m_lock;
        os::Semaphore m_signal;
        std::queue<network::Socket*> m_queue;
    };

    class _EXPORT_CLASS ServiceTcp: public Thread::Run {
    public:
        ServiceTcp
        (TcpConnections& cn, network::Socket& s, bool isRepeated = false)
        : m_cn(cn),
          m_s(s),
          m_isRepeated(isRepeated),
          m_recvdBye(false), 
          m_serviceBye(XOS_NETWORK_SERVICE_DEFAULT_BYE), 
          m_serviceHello(XOS_NETWORK_SERVICE_DEFAULT_HELLO) {
        }
        virtual bool SetRecvdBye(bool recvdBye = true) { 
            if ((m_recvdBye = recvdBye)) {
                m_cn.Clear();
            }
            return m_recvdBye; }
        virtual bool RecvdBye() const { return m_recvdBye; }
        virtual void OnRecvdBye(char* buf = 0, ssize_t count = -1) {}
        virtual void OnRecvdHello(char* buf = 0, ssize_t count = -1) {}
        virtual void OnRecvd(char* buf = 0, ssize_t count = -1) {}
        virtual bool IsRepeated() const { return m_isRepeated; }
        virtual void operator()() {
            network::Socket* c = 0;
            bool recvdBye = false;
            char buf[XOS_NETWORK_SERVICE_DEFAULT_DATA_BUFFER_SIZE];

            XOS_LOG_DEBUG("in...");
            do {
                XOS_LOG_TRACE("dequeue socket...");
                if ((c = m_cn.Dequeue())) {
                    ssize_t count = 0;
                    XOS_LOG_TRACE("...dequeued socket");
                    if (0 < (count = c->Recv(buf, sizeof(buf)-1, 0))) {
                        buf[count] = 0;
                        printf("--->\n%s\n<---\n", buf);
                        if (recvdBye = (buf == (strstr(buf, m_serviceBye.c_str())))) {
                            XOS_LOG_INFO("...received \"" << m_serviceBye << "\"");
                            SetRecvdBye();
                            OnRecvdBye(buf, count);
                        } else {
                            if ((buf == (strstr(buf, m_serviceHello.c_str())))) {
                                XOS_LOG_INFO("...received \"" << m_serviceHello << "\"");
                                OnRecvdHello(buf, count);
                            } else {
                                OnRecvd(buf, count);
                            }
                        }
                    }
                    c->Shutdown();
                    network::Socket::Delete(c);
                } else {
                    XOS_LOG_TRACE("...failed on dequeue socket");
                }
            } while (IsRepeated() && !RecvdBye());
            XOS_LOG_DEBUG("...out");
        }
    protected:
        TcpConnections& m_cn;
        network::Socket& m_s;
        bool m_isRepeated;
        bool m_recvdBye;
        std::string m_serviceBye;
        std::string m_serviceHello;
    };

    class _EXPORT_CLASS AcceptTcp: public Thread::Run {
    public:
        AcceptTcp
        (TcpConnections& cn, ServiceTcp& service,
         network::Endpoint& ep, network::Socket& s)
        : m_cn(cn), m_service(service), m_ep(ep), m_s(s) {
        }
        virtual void operator()() {
            network::Socket* c = 0;
            XOS_LOG_DEBUG("in...");
            do {
                XOS_LOG_TRACE("accept socket...");
                if ((c = m_s.Accept(m_ep.SocketAddress(), &m_ep.SocketAddressLen()))) {
                    XOS_LOG_TRACE("...accepted socket");
                    m_cn.Queue(c);
                } else {
                    XOS_LOG_TRACE("...failed on accept socket");
                    break;
                }
            } while (!(m_service.RecvdBye()));
            XOS_LOG_DEBUG("...out");
        }
    protected:
        TcpConnections& m_cn;
        ServiceTcp& m_service;
        network::Endpoint& m_ep;
        network::Socket& m_s;
    };

    Main()
    : m_serviceRunner(0),
      m_serviceWaitIsTrue(false),
      m_serviceProcessIsNative(false),
      m_serviceThreadsNo(XOS_NETWORK_SERVICE_DEFAULT_THREADSNO),
      m_serviceThreads(XOS_NETWORK_SERVICE_DEFAULT_THREADS),
      m_serviceTransport(XOS_NETWORK_SERVICE_DEFAULT_TRANSPORT),
      m_serviceAddressFamily(XOS_NETWORK_SERVICE_DEFAULT_FAMILY),
      m_serviceHello(XOS_NETWORK_SERVICE_DEFAULT_HELLO),
      m_serviceBye(XOS_NETWORK_SERVICE_DEFAULT_BYE),
      m_serviceHost(XOS_NETWORK_SERVICE_DEFAULT_HOST), 
      m_servicePort(XOS_NETWORK_SERVICE_DEFAULT_PORT),
      m_servicePortNo(XOS_NETWORK_SERVICE_DEFAULT_PORTNO) {
    }
    virtual ~Main() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int Run(int argc, char** argv, char** env) { 
        printf("%s %s\n", m_serviceHello.c_str(), (optind<argc)?(argv[optind]):(""));
        if ((m_serviceRunner)) {
            (this->*m_serviceRunner)(argc, argv, env);
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

    //
    // Start
    //
    virtual int RunStart(int argc, char** argv, char** env) { 
        char* argV[] = {
            argv[0],
            "-o",
            (char*)(m_serviceHost.c_str()),
            "-p",
            (char*)(m_servicePort.c_str()),
            "-t",
            (char*)(m_serviceThreads.c_str()),
            "-s",
            (char*)(m_serviceTransport.c_str()),
            "-a",
            (char*)(m_serviceAddressFamily.c_str()),
            argv[optind],
            0};
            if ((m_serviceProcessIsNative)) {
                os::Process p(argv[0], argV);
                if (!(m_serviceWaitIsTrue)) {
                    p.Separate(); }
            } else {
                os::crt::Process p(argv[0], argV);
                if (!(m_serviceWaitIsTrue)) {
                    p.Separate(); }
            }
        return 0; 
    }

    //
    // TCP
    //
    virtual int RunTcpClient(int argc, char** argv, char** env) { 
        network::Endpoint* ep = ClientEndpoint(m_serviceHost.c_str(), m_servicePortNo);
        network::Socket* s = 0;
        if (s = (network::Socket::New(ep->GetFamily(), network::ip::tcp::Transport::Type, network::ip::tcp::Transport::Protocol))) {
            if ((s->Connect(ep->SocketAddress(), ep->SocketAddressLen()))) {
                std::string message(m_serviceHello + " ");
                message.append((optind<argc)?(argv[optind]):(""));
                message.append("\n");
                XOS_LOG_INFO("Sending \"" << message << "\"...");
                if (0 < (s->Send((const void*)(message.c_str()), message.length(), 0))) {
                    XOS_LOG_INFO("...Sent \"" << message << "\"...");
                }
            }
            network::Socket::Delete(s);
        }
        delete ep;
        return 0; 
    }
    virtual int RunTcpServer(int argc, char** argv, char** env) { 
        network::Endpoint* ep = ServerEndpoint(m_serviceHost.c_str(), m_servicePortNo);
        network::Socket* s = 0;
        if (s = (network::Socket::New(ep->GetFamily(), network::ip::tcp::Transport::Type, network::ip::tcp::Transport::Protocol))) {
            if ((s->Bind(ep->SocketAddress(), ep->SocketAddressLen()))) {
                if ((s->Listen())) {
                    if (0 < (m_serviceThreadsNo)) {
                        //
                        // Threaded service
                        //
                        TcpConnections cn(*s);
                        ServiceTcp service(cn, *s, true);
                        AcceptTcp accept(cn, service, *ep, *s);
                        std::deque<os::Thread*> tq;
                        os::Thread* ct;

                        //
                        // Start service threads
                        //
                        for (int tNo = 0; tNo < m_serviceThreadsNo; tNo++) {
                            os::Thread* t = 0;
                            if ((t = new os::Thread(service))) {
                                tq.push_back(t);
                            } else {
                                service.SetRecvdBye();
                                //
                                // Join service threads already created
                                //
                                while (0 < (tq.size())) {
                                    if ((t = tq.back())) {
                                        tq.pop_back();
                                        t->Join();
                                        delete t;
                                    }
                                }
                                break;
                            }
                        }
                        //
                        // Start connection thread
                        //
                        if ((ct = new os::Thread(accept))) {
                            //
                            // Join connection thread
                            //
                            ct->Join();
                            delete ct;
                        }
                        //
                        // Join service threads
                        //
                        while (0 < (tq.size())) {
                            os::Thread* t = 0;
                            if ((t = tq.back())) {
                                tq.pop_back();
                                t->Join();
                                delete t;
                            }
                        }
                    } else {
                        //
                        // Non threaded service
                        //
                        network::Socket* c = 0;
                        while ((c = s->Accept(ep->SocketAddress(), &ep->SocketAddressLen()))) {
                            TcpConnections cn(*s, c);
                            ServiceTcp service(cn, *s);
                            service();
                            if ((service.RecvdBye())) {
                                break;
                            }
                        }
                    }
                }
            }
            network::Socket::Delete(s);
        }
        delete ep;
        return 0; 
    }

    //
    // UDP
    //
    virtual int RunUdpClient(int argc, char** argv, char** env) { 
        network::Endpoint* ep = ClientEndpoint(m_serviceHost.c_str(), m_servicePortNo);
        network::Socket* s = 0;
        if (s = (network::Socket::New(ep->GetFamily(), network::ip::udp::Transport::Type, network::ip::udp::Transport::Protocol))) {
             std::string message(m_serviceHello + " ");
             message.append((optind<argc)?(argv[optind]):(""));
             message.append("\n");
             XOS_LOG_INFO("Sending \"" << message << "\"...");
             if (0 < (s->SendTo((const void*)(message.c_str()), message.length(), 0, ep->SocketAddress(), ep->SocketAddressLen()))) {
                 XOS_LOG_INFO("...Sent \"" << message << "\"...");
             }
            network::Socket::Delete(s);
        }
        delete ep;
        return 0; 
    }
    virtual int RunUdpServer(int argc, char** argv, char** env) { 
        network::Endpoint* ep = ServerEndpoint(m_serviceHost.c_str(), m_servicePortNo);
        network::Socket* s = 0;
        if (s = (network::Socket::New(ep->GetFamily(), network::ip::udp::Transport::Type, network::ip::udp::Transport::Protocol))) {
            if ((s->Bind(ep->SocketAddress(), ep->SocketAddressLen()))) {
                ssize_t count = 0;
                while (0 < (count = s->RecvFrom(m_serviceDataBuffer, sizeof(m_serviceDataBuffer)-1, 0, ep->SocketAddress(), &ep->SocketAddressLen()))) {
                    m_serviceDataBuffer[count] = 0;
                    printf("--->\n%s\n<---\n", m_serviceDataBuffer);
                    if (m_serviceDataBuffer == (strstr(m_serviceDataBuffer, m_serviceBye.c_str()))) {
                        break;
                    }
                }
            }
            network::Socket::Delete(s);
        }
        delete ep;
        return 0; 
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual network::Endpoint* ClientEndpoint(const char* host, u_short port) {
        network::Endpoint* ep = 0;
        if ((m_serviceClientEndpoint))
            ep = (this->*m_serviceClientEndpoint)(host, port);
        else ep = ClientIpv4Endpoint(host, port);
        return ep;
    }
    virtual network::Endpoint* ServerEndpoint(const char* host, u_short port) {
        network::Endpoint* ep = 0;
        if ((m_serviceServerEndpoint))
            ep = (this->*m_serviceServerEndpoint)(host, port);
        else ep = ServerIpv4Endpoint(host, port);
        return ep;
    }

    virtual network::Endpoint* LocalEndpoint(const char* host, u_short port) {
        std::stringstream ss;
        ss << host;
        ss << port;
        network::Endpoint* ep = new network::local::Endpoint(ss.str().c_str());
        return ep;
    }

    virtual network::Endpoint* ClientIpv4Endpoint(const char* host, u_short port) {
        network::Endpoint* ep = new network::ip::v4::Endpoint(host, port);
        return ep;
    }
    virtual network::Endpoint* ServerIpv4Endpoint(const char* host, u_short port) {
        network::Endpoint* ep = new network::ip::v4::Endpoint(port);
        return ep;
    }

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
     int argc, char**argv, char**env)
    {
        int err = 0;
        switch(optval)
        {
        case 'c':
            if ('u' != (tolower(optarg[0]))) {
                m_serviceTransport.assign("t");
                m_serviceRunner = &Derives::RunTcpClient;
            } else {
                m_serviceTransport.assign("u");
                m_serviceRunner = &Derives::RunUdpClient;
            }
            break;
        case 's':
            if ('u' != (tolower(optarg[0]))) {
                m_serviceTransport.assign("t");
                m_serviceRunner = &Derives::RunTcpServer;
            } else {
                m_serviceTransport.assign("u");
                m_serviceRunner = &Derives::RunUdpServer;
            }
            break;
        case 'r':
            if ('u' != (tolower(optarg[0]))) {
                m_serviceTransport.assign("t");
                m_serviceRunner = &Derives::RunStart;
            } else {
                m_serviceTransport.assign("u");
                m_serviceRunner = &Derives::RunStart;
            }
            break;
        case 'w':
            m_serviceWaitIsTrue = true;
            break;
        case 'n':
            m_serviceProcessIsNative = true;
            break;
        case 'm':
            m_serviceHello.assign(optarg);
            break;
        case 't':
            {
                std::stringstream ss(optarg);
                ss >> m_serviceThreadsNo;
                m_serviceThreads.assign(optarg);
            }
            break;
        case 'o':
            m_serviceHost.assign(optarg);
            break;
        case 'p':
            {
                std::stringstream ss(optarg);
                ss >> m_servicePortNo;
                m_servicePort.assign(optarg);
            }
            break;
        case 'f':
            switch(tolower(optarg[0])) {
            case '4':
                m_serviceAddressFamily.assign("4");
                m_serviceClientEndpoint = &Derives::ClientIpv4Endpoint;
                m_serviceServerEndpoint = &Derives::ServerIpv4Endpoint;
                break;
            case '6':
                m_serviceAddressFamily.assign("6");
                m_serviceClientEndpoint = &Derives::ClientIpv6Endpoint;
                m_serviceServerEndpoint = &Derives::ServerIpv6Endpoint;
                break;
            case 'l':
                m_serviceAddressFamily.assign("l");
                m_serviceClientEndpoint = &Derives::LocalEndpoint;
                m_serviceServerEndpoint = &Derives::LocalEndpoint;
                break;
            }
            break;
        default:
            err = Extends::OnOption
            (optval, optarg, optname, optind, argc, argv, env);
        }
        return err;
    }
    virtual const char* OptionUsage
    (const char*& optarg, const struct option* longopt)
    {
        const char* chars = "";
        switch(longopt->val)
        {
        case 'm':
            optarg = "message";
            chars = "Service Message";
            break;
        case 'c':
        case 'r':
        case 's':
            optarg = "{(t)Tcp | (u)Udp}";
            chars = ('s'!=(longopt->val))?(('r'!=(longopt->val))?("Service Client"):("Start Service")):("Service Server");
            break;
        case 'w':
            chars = "Wait Service Process";
            break;
        case 'n':
            chars = "Native Service Process";
            break;
        case 't':
            optarg = "number";
            chars = "Service Threads";
            break;
        case 'o':
            optarg = "name";
            chars = "Service Host Name";
            break;
        case 'p':
            optarg = "number";
            chars = "Service Port Number";
            break;
        case 'f':
            optarg = "{(4)ipv4 | (6)ipv6 | (l)local}";
            chars = "Service Address Family";
            break;
        default:
            chars = Extends::OptionUsage(optarg, longopt);
        }
        return chars;
    }
    virtual const char* Options
    (const struct option*& longopts)
    {
        int err = 0;
        static const char* chars = XOS_NETWORK_SERVICE_OPTIONS_CHARS;
        static struct option optstruct[]= {
            XOS_NETWORK_SERVICE_OPTIONS_OPTIONS
            {0, 0, 0, 0}};
        longopts = optstruct;
        return chars;
    }

protected:
    Runner m_serviceRunner;
    Endpoint m_serviceClientEndpoint;
    Endpoint m_serviceServerEndpoint;
    bool m_serviceWaitIsTrue;
    bool m_serviceProcessIsNative;
    unsigned m_serviceThreadsNo;
    std::string m_serviceThreads;
    std::string m_serviceTransport;
    std::string m_serviceAddressFamily;
    std::string m_serviceHello;
    std::string m_serviceBye;
    std::string m_serviceHost;
    std::string m_servicePort;
    u_short m_servicePortNo;
    char m_serviceDataBuffer[XOS_NETWORK_SERVICE_DEFAULT_DATA_BUFFER_SIZE];
};

} // namespace service 
} // namespace network 
} // namespace xos 

#endif // _XOS_NETWORK_SERVICE_MAIN_HPP 
