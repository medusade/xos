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
///   Date: 3/4/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_NETWORK_SERVICE_TCP_MAIN_HPP
#define _XOS_NETWORK_SERVICE_TCP_MAIN_HPP

#include "xos/os/Main.hpp"
#include "xos/os/os/Mutexes.hpp"
#include "xos/os/os/Semaphores.hpp"
#include "xos/os/os/Threads.hpp"
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

#define XOS_NETWORK_SERVICE_DEFAULT_FAMILY "4"

#define XOS_NETWORK_SERVICE_DEFAULT_DATA_BUFFER_SIZE 4096

#define XOS_NETWORK_SERVICE_MAIN_SERVICE_CLIENT_OPT "service-client"
#define XOS_NETWORK_SERVICE_MAIN_SERVICE_CLIENT_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_NONE
#define XOS_NETWORK_SERVICE_MAIN_SERVICE_CLIENT_OPTARG ""
#define XOS_NETWORK_SERVICE_MAIN_SERVICE_CLIENT_OPTUSE "Service Client"
#define XOS_NETWORK_SERVICE_MAIN_SERVICE_CLIENT_OPTVAL_S "c"
#define XOS_NETWORK_SERVICE_MAIN_SERVICE_CLIENT_OPTVAL_C 'c'

#define XOS_NETWORK_SERVICE_MAIN_SERVICE_SERVER_OPT "service-server"
#define XOS_NETWORK_SERVICE_MAIN_SERVICE_SERVER_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_NONE
#define XOS_NETWORK_SERVICE_MAIN_SERVICE_SERVER_OPTARG ""
#define XOS_NETWORK_SERVICE_MAIN_SERVICE_SERVER_OPTUSE "Service Server"
#define XOS_NETWORK_SERVICE_MAIN_SERVICE_SERVER_OPTVAL_S "s"
#define XOS_NETWORK_SERVICE_MAIN_SERVICE_SERVER_OPTVAL_C 's'

#define XOS_NETWORK_SERVICE_MAIN_SERVICE_THREADS_OPT "service-threads"
#define XOS_NETWORK_SERVICE_MAIN_SERVICE_THREADS_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_NONE
#define XOS_NETWORK_SERVICE_MAIN_SERVICE_THREADS_OPTARG "number"
#define XOS_NETWORK_SERVICE_MAIN_SERVICE_THREADS_OPTUSE "Service Threads"
#define XOS_NETWORK_SERVICE_MAIN_SERVICE_THREADS_OPTVAL_S "t:"
#define XOS_NETWORK_SERVICE_MAIN_SERVICE_THREADS_OPTVAL_C 't'

#define XOS_NETWORK_SERVICE_MAIN_SERVICE_MESSAGE_OPT "service-message"
#define XOS_NETWORK_SERVICE_MAIN_SERVICE_MESSAGE_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_REQUIRED
#define XOS_NETWORK_SERVICE_MAIN_SERVICE_MESSAGE_OPTARG "string"
#define XOS_NETWORK_SERVICE_MAIN_SERVICE_MESSAGE_OPTUSE "Service Message"
#define XOS_NETWORK_SERVICE_MAIN_SERVICE_MESSAGE_OPTVAL_S "m:"
#define XOS_NETWORK_SERVICE_MAIN_SERVICE_MESSAGE_OPTVAL_C 'm'

#define XOS_NETWORK_SERVICE_MAIN_SERVICE_HOST_OPT "service-host"
#define XOS_NETWORK_SERVICE_MAIN_SERVICE_HOST_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_REQUIRED
#define XOS_NETWORK_SERVICE_MAIN_SERVICE_HOST_OPTARG "name"
#define XOS_NETWORK_SERVICE_MAIN_SERVICE_HOST_OPTUSE "Service Host"
#define XOS_NETWORK_SERVICE_MAIN_SERVICE_HOST_OPTVAL_S "o:"
#define XOS_NETWORK_SERVICE_MAIN_SERVICE_HOST_OPTVAL_C 'o'

#define XOS_NETWORK_SERVICE_MAIN_SERVICE_PORT_OPT "service-port"
#define XOS_NETWORK_SERVICE_MAIN_SERVICE_PORT_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_REQUIRED
#define XOS_NETWORK_SERVICE_MAIN_SERVICE_PORT_OPTARG "number"
#define XOS_NETWORK_SERVICE_MAIN_SERVICE_PORT_OPTUSE "Service Port"
#define XOS_NETWORK_SERVICE_MAIN_SERVICE_PORT_OPTVAL_S "p:"
#define XOS_NETWORK_SERVICE_MAIN_SERVICE_PORT_OPTVAL_C 'p'

#define XOS_NETWORK_SERVICE_MAIN_OPTIONS_CHARS \
    XOS_NETWORK_SERVICE_MAIN_SERVICE_CLIENT_OPTVAL_S \
    XOS_NETWORK_SERVICE_MAIN_SERVICE_SERVER_OPTVAL_S \
    XOS_NETWORK_SERVICE_MAIN_SERVICE_THREADS_OPTVAL_S \
    XOS_NETWORK_SERVICE_MAIN_SERVICE_MESSAGE_OPTVAL_S \
    XOS_NETWORK_SERVICE_MAIN_SERVICE_HOST_OPTVAL_S \
    XOS_NETWORK_SERVICE_MAIN_SERVICE_PORT_OPTVAL_S \
    XOS_MAIN_OPTIONS_CHARS

#define XOS_NETWORK_SERVICE_MAIN_OPTIONS_OPTIONS \
            {XOS_NETWORK_SERVICE_MAIN_SERVICE_CLIENT_OPT,\
             XOS_NETWORK_SERVICE_MAIN_SERVICE_CLIENT_OPTARG_REQUIRED, 0,\
             XOS_NETWORK_SERVICE_MAIN_SERVICE_CLIENT_OPTVAL_C},\
             \
            {XOS_NETWORK_SERVICE_MAIN_SERVICE_SERVER_OPT,\
             XOS_NETWORK_SERVICE_MAIN_SERVICE_SERVER_OPTARG_REQUIRED, 0,\
             XOS_NETWORK_SERVICE_MAIN_SERVICE_SERVER_OPTVAL_C},\
             \
            {XOS_NETWORK_SERVICE_MAIN_SERVICE_THREADS_OPT,\
             XOS_NETWORK_SERVICE_MAIN_SERVICE_THREADS_OPTARG_REQUIRED, 0,\
             XOS_NETWORK_SERVICE_MAIN_SERVICE_THREADS_OPTVAL_C},\
             \
            {XOS_NETWORK_SERVICE_MAIN_SERVICE_MESSAGE_OPT,\
             XOS_NETWORK_SERVICE_MAIN_SERVICE_MESSAGE_OPTARG_REQUIRED, 0,\
             XOS_NETWORK_SERVICE_MAIN_SERVICE_MESSAGE_OPTVAL_C},\
             \
            {XOS_NETWORK_SERVICE_MAIN_SERVICE_HOST_OPT,\
             XOS_NETWORK_SERVICE_MAIN_SERVICE_HOST_OPTARG_REQUIRED, 0,\
             XOS_NETWORK_SERVICE_MAIN_SERVICE_HOST_OPTVAL_C},\
             \
            {XOS_NETWORK_SERVICE_MAIN_SERVICE_PORT_OPT,\
             XOS_NETWORK_SERVICE_MAIN_SERVICE_PORT_OPTARG_REQUIRED, 0,\
             XOS_NETWORK_SERVICE_MAIN_SERVICE_PORT_OPTVAL_C},\
            XOS_MAIN_OPTIONS_OPTIONS

namespace xos {
namespace network {
namespace service {
namespace tcp {

typedef MainImplement MainImplement;
typedef Main MainExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Main
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Main
: virtual public MainImplement,
  public MainExtend
{
public:
    typedef MainImplement Implements;
    typedef MainExtend Extends;
    typedef Main Derives;

    typedef int (Derives::*Runner)(int argc, char** argv, char** env);
    typedef network::Endpoint* (Derives::*Endpoint)(const char* host, u_short port);

    ///////////////////////////////////////////////////////////////////////
    ///  Class: 
    ///////////////////////////////////////////////////////////////////////
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
    ///////////////////////////////////////////////////////////////////////
    ///  Class: 
    ///////////////////////////////////////////////////////////////////////
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
                        printf("\n--->%s\n", buf);
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
    ///////////////////////////////////////////////////////////////////////
    ///  Class: 
    ///////////////////////////////////////////////////////////////////////
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

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: Main
    ///////////////////////////////////////////////////////////////////////
    Main()
    : m_serviceRunner(0),
      m_serviceClientEndpoint(0),
      m_serviceServerEndpoint(0),
      m_serviceThreadsNo(XOS_NETWORK_SERVICE_DEFAULT_THREADSNO),
      m_serviceThreads(XOS_NETWORK_SERVICE_DEFAULT_THREADS),
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
    // Run
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
    // Client/Server
    ///////////////////////////////////////////////////////////////////////
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

    ///////////////////////////////////////////////////////////////////////
    // Client/Server Endpoint
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
    ///////////////////////////////////////////////////////////////////////
    // Client/Server IPv4 Endpoint
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
    // Client/Server IPv6 Endpoint
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
        switch(optval)
        {
        case XOS_NETWORK_SERVICE_MAIN_SERVICE_CLIENT_OPTVAL_C:
            m_serviceRunner = &Derives::RunTcpClient;
            break;
        case XOS_NETWORK_SERVICE_MAIN_SERVICE_SERVER_OPTVAL_C:
            m_serviceRunner = &Derives::RunTcpServer;
            break;
        case XOS_NETWORK_SERVICE_MAIN_SERVICE_THREADS_OPTVAL_C:
            {
                std::stringstream ss(optarg);
                ss >> m_serviceThreadsNo;
                m_serviceThreads.assign(optarg);
            }
            break;
        case XOS_NETWORK_SERVICE_MAIN_SERVICE_MESSAGE_OPTVAL_C:
            m_serviceHello.assign(optarg);
            break;
        case XOS_NETWORK_SERVICE_MAIN_SERVICE_HOST_OPTVAL_C:
            m_serviceHost.assign(optarg);
            break;
        case XOS_NETWORK_SERVICE_MAIN_SERVICE_PORT_OPTVAL_C:
            {
                std::stringstream ss(optarg);
                ss >> m_servicePortNo;
                m_servicePort.assign(optarg);
            }
            break;
        default:
            err = Extends::OnOption
            (optval, optarg, optname, optind, argc, argv, env);
        }
        return err;
    }
    virtual const char* OptionUsage
    (const char*& optarg, const struct option* longopt) {
        const char* chars = "";
        switch(longopt->val)
        {
        case XOS_NETWORK_SERVICE_MAIN_SERVICE_CLIENT_OPTVAL_C:
            optarg = XOS_NETWORK_SERVICE_MAIN_SERVICE_CLIENT_OPTARG;
            chars = XOS_NETWORK_SERVICE_MAIN_SERVICE_CLIENT_OPTUSE;
            break;
        case XOS_NETWORK_SERVICE_MAIN_SERVICE_SERVER_OPTVAL_C:
            optarg = XOS_NETWORK_SERVICE_MAIN_SERVICE_SERVER_OPTARG;
            chars = XOS_NETWORK_SERVICE_MAIN_SERVICE_SERVER_OPTUSE;
            break;
        case XOS_NETWORK_SERVICE_MAIN_SERVICE_THREADS_OPTVAL_C:
            optarg = XOS_NETWORK_SERVICE_MAIN_SERVICE_THREADS_OPTARG;
            chars = XOS_NETWORK_SERVICE_MAIN_SERVICE_THREADS_OPTUSE;
            break;
        case XOS_NETWORK_SERVICE_MAIN_SERVICE_MESSAGE_OPTVAL_C:
            optarg = XOS_NETWORK_SERVICE_MAIN_SERVICE_MESSAGE_OPTARG;
            chars = XOS_NETWORK_SERVICE_MAIN_SERVICE_MESSAGE_OPTUSE;
            break;
        case XOS_NETWORK_SERVICE_MAIN_SERVICE_HOST_OPTVAL_C:
            optarg = XOS_NETWORK_SERVICE_MAIN_SERVICE_HOST_OPTARG;
            chars = XOS_NETWORK_SERVICE_MAIN_SERVICE_HOST_OPTUSE;
            break;
        case XOS_NETWORK_SERVICE_MAIN_SERVICE_PORT_OPTVAL_C:
            optarg = XOS_NETWORK_SERVICE_MAIN_SERVICE_PORT_OPTARG;
            chars = XOS_NETWORK_SERVICE_MAIN_SERVICE_PORT_OPTUSE;
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
        static const char* chars = XOS_NETWORK_SERVICE_MAIN_OPTIONS_CHARS;
        static struct option optstruct[]= {
            XOS_NETWORK_SERVICE_MAIN_OPTIONS_OPTIONS
            {0, 0, 0, 0}};
        longopts = optstruct;
        return chars;
    }

protected:
    Runner m_serviceRunner;
    Endpoint m_serviceClientEndpoint;
    Endpoint m_serviceServerEndpoint;
    unsigned m_serviceThreadsNo;
    std::string m_serviceThreads;
    std::string m_serviceAddressFamily;
    std::string m_serviceHello;
    std::string m_serviceBye;
    std::string m_serviceHost;
    std::string m_servicePort;
    u_short m_servicePortNo;
    char m_serviceDataBuffer[XOS_NETWORK_SERVICE_DEFAULT_DATA_BUFFER_SIZE];
};

} // namespace tcp 
} // namespace service 
} // namespace network 
} // namespace xos 

#endif // _XOS_NETWORK_SERVICE_TCP_MAIN_HPP 
