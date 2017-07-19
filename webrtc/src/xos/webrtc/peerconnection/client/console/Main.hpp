///////////////////////////////////////////////////////////////////////
/// Copyright 2013, Google Inc.
///
/// Redistribution and use in source and binary forms, with or without
/// modification, are permitted provided that the following conditions are met:
/// 
///  1. Redistributions of source code must retain the above copyright notice,
///     this list of conditions and the following disclaimer.
///  2. Redistributions in binary form must reproduce the above copyright notice,
///     this list of conditions and the following disclaimer in the documentation
///     and/or other materials provided with the distribution.
///  3. The name of the author may not be used to endorse or promote products
///     derived from this software without specific prior written permission.
/// 
/// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
/// WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
/// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
/// EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
/// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
/// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
/// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
/// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
/// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
/// ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
///
///   File: Main.hpp
///
/// Author: $author$
///   Date: 1/6/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_WEBRTC_PEERCONNECTION_CLIENT_CONSOLE_MAIN_HPP
#define _XOS_WEBRTC_PEERCONNECTION_CLIENT_CONSOLE_MAIN_HPP

#include "xos/webrtc/peerconnection/client/os/SocketServer.hpp"
#include "xos/webrtc/peerconnection/client/console/MainWindow.hpp"
#include "xos/webrtc/peerconnection/client/MainWindow.hpp"
#include "xos/webrtc/peerconnection/client/Conductor.hpp"
#include "xos/webrtc/peerconnection/client/Connection.hpp"
#include "xos/webrtc/peerconnection/client/Trace.hpp"
#include "xos/network/service/tcp/Main.hpp"
#include "xos/os/Main.hpp"

#define XOS_WEBRTC_PEERCONNECTION_CLIENT_MAIN_DEFAULT_SERVER_NAME "localhost"
#define XOS_WEBRTC_PEERCONNECTION_CLIENT_MAIN_DEFAULT_SERVER_PORT 8888

#define XOS_WEBRTC_PEERCONNECTION_CLIENT_MAIN_DEFAULT_WEBRTC_PEERCONNECTION_CLIENT_TRACE_LEVELS \
    XOS_WEBRTC_PEERCONNECTION_CLIENT_TRACE_LEVELS_TRACE

#define XOS_WEBRTC_PEERCONNECTION_CLIENT_MAIN_DEFAULT_SERVICE_SIGNIN "Signin"
#define XOS_WEBRTC_PEERCONNECTION_CLIENT_MAIN_DEFAULT_SERVICE_SIGNOUT "Signout"

#define XOS_WEBRTC_PEERCONNECTION_CLIENT_MAIN_RUN_THREAD_OPT "run-thread"
#define XOS_WEBRTC_PEERCONNECTION_CLIENT_MAIN_RUN_THREAD_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_NONE
#define XOS_WEBRTC_PEERCONNECTION_CLIENT_MAIN_RUN_THREAD_OPTARG ""
#define XOS_WEBRTC_PEERCONNECTION_CLIENT_MAIN_RUN_THREAD_OPTUSE "Run in Thread"
#define XOS_WEBRTC_PEERCONNECTION_CLIENT_MAIN_RUN_THREAD_OPTVAL_S "r"
#define XOS_WEBRTC_PEERCONNECTION_CLIENT_MAIN_RUN_THREAD_OPTVAL_C 'r'

#define XOS_WEBRTC_PEERCONNECTION_CLIENT_MAIN_OPTIONS_CHARS \
    XOS_WEBRTC_PEERCONNECTION_CLIENT_MAIN_RUN_THREAD_OPTVAL_S \
    XOS_NETWORK_SERVICE_MAIN_OPTIONS_CHARS

#define XOS_WEBRTC_PEERCONNECTION_CLIENT_MAIN_OPTIONS_OPTIONS \
            {XOS_WEBRTC_PEERCONNECTION_CLIENT_MAIN_RUN_THREAD_OPT,\
             XOS_WEBRTC_PEERCONNECTION_CLIENT_MAIN_RUN_THREAD_OPTARG_REQUIRED, 0,\
             XOS_WEBRTC_PEERCONNECTION_CLIENT_MAIN_RUN_THREAD_OPTVAL_C},\
            XOS_NETWORK_SERVICE_MAIN_OPTIONS_OPTIONS

namespace xos {
namespace webrtc {
namespace peerconnection {
namespace client {
namespace console {

typedef MainWindow MainWindow;
typedef client::os::SocketServer SocketServer;

typedef xos::network::service::tcp::MainImplement MainImplement;
typedef xos::network::service::tcp::Main MainExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Main
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Main
: virtual public MainImplement,
  virtual public ImageObserverInterface,
  public MainExtend
{
public:
    typedef MainImplement Implements;
    typedef MainExtend Extends;
    typedef Main Derives;

    typedef int (Derives::*Runner)(int argc, char** argv, char** env);

    ///////////////////////////////////////////////////////////////////////
    /// Class: MessageProcessor
    ///////////////////////////////////////////////////////////////////////
    class _EXPORT_CLASS MessageProcessor {
    public:
        MessageProcessor() {}
        virtual ~MessageProcessor() {}
        virtual void Run() {}
    };

    ///////////////////////////////////////////////////////////////////////
    /// Class: SocketServerMessageProcessor
    ///////////////////////////////////////////////////////////////////////
    class _EXPORT_CLASS SocketServerMessageProcessor: public MessageProcessor {
    public:
        typedef MessageProcessor Extends;
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        SocketServerMessageProcessor(SocketServer& socketServer)
        : m_socketServer(socketServer) {}
        virtual void Run() {
            XOS_LOG_DEBUG("socketServer.Run()...");
            m_socketServer.Run();
            XOS_LOG_DEBUG("...socketServer.Run()");
        }
    protected:
        SocketServer& m_socketServer;
    };

    typedef Extends::ServiceTcp ServiceTcpExtend;
    ///////////////////////////////////////////////////////////////////////
    ///  Class: ServiceTcp
    ///////////////////////////////////////////////////////////////////////
    class _EXPORT_CLASS ServiceTcp: public ServiceTcpExtend {
    public:
        typedef ServiceTcpExtend Extends;
        ///////////////////////////////////////////////////////////////////////
        ///  Constructor: ServiceTcp
        ///////////////////////////////////////////////////////////////////////
        ServiceTcp
        (MainWindow& window, const std::string& serverName, int serverPort,
         TcpConnections& cn, network::Socket& s, bool isRepeated = false)
        : Extends(cn, s, isRepeated), m_window(window), 
          m_serverName(serverName), m_serverPort(serverPort),
          m_signIn(XOS_WEBRTC_PEERCONNECTION_CLIENT_MAIN_DEFAULT_SERVICE_SIGNIN),
          m_signOut(XOS_WEBRTC_PEERCONNECTION_CLIENT_MAIN_DEFAULT_SERVICE_SIGNOUT)
        {
        }
        virtual void OnRecvd(char* buf = 0, ssize_t count = -1) { 
            if ((buf == (strstr(buf, m_signIn.c_str())))) {
                OnRecvdSignIn(buf, count);
            } else {
                if ((buf == (strstr(buf, m_signOut.c_str())))) {
                    OnRecvdSignOut(buf, count);
                } else {
                }
            }
        }
        virtual void OnRecvdSignIn(char* buf = 0, ssize_t count = -1) { 
            m_window.PostUIMessage(MainWindow::UI_CONNECT_TO_SERVER, 0,0);
        }
        virtual void OnRecvdSignOut(char* buf = 0, ssize_t count = -1) { 
            m_window.PostUIMessage(MainWindow::UI_DISCONNECT_SERVER, 0,0);
        }
        virtual void OnRecvdBye(char* buf = 0, ssize_t count = -1) { 
            m_window.PostUIMessage(MainWindow::UI_THREAD_QUIT, 0,0);
        }
    protected:
        MainWindow& m_window;
        std::string m_serverName;
        int m_serverPort;
        std::string m_signIn;
        std::string m_signOut;
    };

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: Main
    ///////////////////////////////////////////////////////////////////////
    Main() 
    : m_serverName(XOS_WEBRTC_PEERCONNECTION_CLIENT_MAIN_DEFAULT_SERVER_NAME),
      m_serverPort(XOS_WEBRTC_PEERCONNECTION_CLIENT_MAIN_DEFAULT_SERVER_PORT),

      m_webrtcTraceFileName
      (XOS_WEBRTC_PEERCONNECTION_CLIENT_TRACE_DEFAULT_TRACE_FILENAME),

      m_webrtcTraceFileDir
      (XOS_WEBRTC_PEERCONNECTION_CLIENT_TRACE_DEFAULT_TRACE_FILEDIR),

      m_webrtcTraceFileEnv
      (XOS_WEBRTC_PEERCONNECTION_CLIENT_TRACE_DEFAULT_TRACE_FILEENV),

      m_webrtcTraceLevels
      (XOS_WEBRTC_PEERCONNECTION_CLIENT_MAIN_DEFAULT_WEBRTC_PEERCONNECTION_CLIENT_TRACE_LEVELS),

      m_autoConnectToPeerOn(true),
      m_autoConnectToPeerAfterOn(true),
      m_showConnectionState(true),
      m_handleButtonEvents(true),
      m_useUIMessageQueue(true),
      m_postButtonEventUIMessages(true),

      m_runThread(false),
      m_runner(0),
      m_mainWindow(0)
    {
    }
    virtual ~Main() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int Run(int argc, char** argv, char** env) {
        int err = 0;
        if ((m_runner))
            err = (this->*m_runner)(argc, argv, env);
        else
        err = RunDerives(argc, argv, env);
        return err;
    }
    virtual int RunExtends(int argc, char** argv, char** env) {
        int err = Extends::Run(argc, argv, env);
        return err;
    }
    virtual int RunDerives(int argc, char** argv, char** env) {
        int err = 0;

        if (optind < (argc)) {
            m_serverName = argv[optind];
        }
        if (optind+1 < (argc)) {
            std::stringstream ss(argv[optind+1]);
            ss >> m_serverPort;
        }

        MainWindow mainWindow
        (m_serverName.c_str(), m_serverPort, 
         m_autoConnectToPeerOn, m_autoConnectToPeerAfterOn,
         m_showConnectionState, m_handleButtonEvents, 
         m_postButtonEventUIMessages, m_useUIMessageQueue);

        m_mainWindow = &mainWindow;
        mainWindow.RegisterImageObserver(this);

        if ((m_runThread)) {
            err = RunThread(mainWindow, argc, argv, env);
        } else {
            err = RunMain(mainWindow, argc, argv, env);
        }

        mainWindow.UnregisterImageObserver(this);
        m_mainWindow = 0;
        return err;
    }
    virtual int RunMain(MainWindow& mainWindow, int argc, char** argv, char** env) {
        int err = 0;
        SocketServer socketServer(mainWindow);
        SocketServerMessageProcessor messageProcessor(socketServer);

        std::string webrtcTraceFileName
        (mainWindow.GenerateWebRtcTraceFileName
         (m_webrtcTraceFileEnv, m_webrtcTraceFileDir, m_webrtcTraceFileName));

        if ((mainWindow.Opened())) {

            Trace webrtcTrace
            (webrtcTraceFileName, m_webrtcTraceLevels);
            Connection connection;
            Conductor conductor(&connection, &mainWindow);

            mainWindow.ConnectToServer();
            RunMessageProcessor(messageProcessor, mainWindow, argc, argv, env);
            mainWindow.Closed();
        }
        return err;
    }
    virtual int RunThread(MainWindow& mainWindow, int argc, char** argv, char** env) {
        int err = 0;
        if ((mainWindow.Attached())) {
            mainWindow.ConnectToServer();
#if defined(WINDOWS)
            {
                MSG msg;
                while ((GetMessage(&msg, NULL, 0,0))) {
                    TranslateMessage(&msg);
                    DispatchMessage(&msg);
                }
            }
#else // defined(WINDOWS)
#endif // defined(WINDOWS)
            mainWindow.Detached();
        }
        return err;
    }
    virtual int RunMessageProcessor
    (MessageProcessor& messageProcessor, 
     MainWindow& mainWindow, int argc, char** argv, char** env) {
        int err = 0;
        if (1 > (m_serviceThreadsNo)) {
            messageProcessor.Run();
        } else {
            network::Endpoint* ep = ServerEndpoint(m_serviceHost.c_str(), m_servicePortNo);
            network::Socket* s = 0;
            if (s = (network::Socket::New
                (ep->GetFamily(), network::ip::tcp::Transport::Type, 
                 network::ip::tcp::Transport::Protocol))) {
                if ((s->Bind(ep->SocketAddress(), ep->SocketAddressLen()))) {
                    if ((s->Listen())) {
                        //
                        // Threaded service
                        //
                        TcpConnections cn(*s);
                        ServiceTcp service(mainWindow, m_serverName, m_serverPort, cn, *s, true);
                        AcceptTcp accept(cn, service, *ep, *s);
                        std::deque<xos::os::Thread*> tq;
                        xos::os::Thread* ct;
                        //
                        // Start service threads
                        //
                        for (int tNo = 0; tNo < m_serviceThreadsNo; tNo++) {
                            xos::os::Thread* t = 0;
                            if ((t = new xos::os::Thread(service))) {
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
                        if ((ct = new xos::os::Thread(accept))) {
                            //
                            // Run message processor
                            // 
                            messageProcessor.Run();
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
                            xos::os::Thread* t = 0;
                            if ((t = tq.back())) {
                                tq.pop_back();
                                t->Join();
                                delete t;
                            }
                        }
                    }
                }
            }
        }
        return err;
    }

    virtual bool InvalidateWindow(bool eraseBackground = true) { 
        ImageObserverInterface* imageObserverInterface;
        if ((imageObserverInterface = ImageObserverInterfaceDelegated()))
            return imageObserverInterface->InvalidateWindow(eraseBackground );
        else 
        if ((m_mainWindow)) {
            MainWindow& mainWindow = *m_mainWindow;
            uint8_t *remoteImage; int remoteImageWidth, remoteImageHeight, remoteImageFormat;
            uint8_t *localImage; int localImageWidth, localImageHeight, localImageFormat;

            if ((remoteImage = mainWindow.AcquireRemoteImage
                (remoteImageWidth, remoteImageHeight, remoteImageFormat))) 
            {
                if ((localImage = mainWindow.AcquireLocalImage
                    (localImageWidth, localImageHeight, localImageFormat))) 
                {
                    mainWindow.ReleaseLocalImage(localImage);
                }
                mainWindow.ReleaseRemoteImage(remoteImage);
            } else {
                if ((localImage = mainWindow.AcquireLocalImage
                    (localImageWidth, localImageHeight, localImageFormat))) 
                {
                    mainWindow.ReleaseLocalImage(localImage);
                }
            }
        }
        return true; 
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
        case XOS_WEBRTC_PEERCONNECTION_CLIENT_MAIN_RUN_THREAD_OPTVAL_C:
            m_runThread = true;
            break;
        case XOS_NETWORK_SERVICE_MAIN_SERVICE_CLIENT_OPTVAL_C:
        case XOS_NETWORK_SERVICE_MAIN_SERVICE_SERVER_OPTVAL_C:
            m_runner = &Derives::RunExtends;
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
        case XOS_WEBRTC_PEERCONNECTION_CLIENT_MAIN_RUN_THREAD_OPTVAL_C:
            optarg = XOS_WEBRTC_PEERCONNECTION_CLIENT_MAIN_RUN_THREAD_OPTARG;
            chars = XOS_WEBRTC_PEERCONNECTION_CLIENT_MAIN_RUN_THREAD_OPTUSE;
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
        static const char* chars = XOS_WEBRTC_PEERCONNECTION_CLIENT_MAIN_OPTIONS_CHARS;
        static struct option optstruct[]= {
            XOS_WEBRTC_PEERCONNECTION_CLIENT_MAIN_OPTIONS_OPTIONS
            {0, 0, 0, 0}};
        longopts = optstruct;
        return chars;
    }

protected:
    std::string m_serverName;
    int m_serverPort;

    std::string m_webrtcTraceFileName;
    std::string m_webrtcTraceFileDir;
    std::string m_webrtcTraceFileEnv;
    Trace::Level m_webrtcTraceLevels;

    bool m_autoConnectToPeerOn;
    bool m_autoConnectToPeerAfterOn;
    bool m_showConnectionState;
    bool m_handleButtonEvents;
    bool m_useUIMessageQueue;
    bool m_postButtonEventUIMessages;

    bool m_runThread;
    Runner m_runner;
    MainWindow* m_mainWindow;
};

} // namespace console 
} // namespace client 
} // namespace peerconnection 
} // namespace webrtc 
} // namespace xos 

#endif // _XOS_WEBRTC_PEERCONNECTION_CLIENT_CONSOLE_MAIN_HPP 
