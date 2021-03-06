///////////////////////////////////////////////////////////////////////
/// Copyright 2012, Google Inc.
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
///   Date: 10/19/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_WEBRTC_CLIENT_CONSOLE_MAIN_HPP
#define _XOS_WEBRTC_CLIENT_CONSOLE_MAIN_HPP

#include "xos/webrtc/client/os/SocketServer.hpp"
#include "xos/webrtc/client/console/WindowPeer.hpp"
#include "xos/webrtc/client/console/Window.hpp"
#include "xos/webrtc/client/Window.hpp"
#include "xos/webrtc/client/Conductor.hpp"
#include "xos/webrtc/client/Connection.hpp"
#include "xos/webrtc/client/VideoCodec.hpp"
#include "xos/webrtc/client/Trace.hpp"
#include "app/console/Hello/Hello.hpp"

#define XOS_WEBRTC_CLIENT_MAIN_DEFAULT_SERVER_NAME "localhost"
#define XOS_WEBRTC_CLIENT_MAIN_DEFAULT_SERVER_PORT 8888

#define XOS_WEBRTC_CLIENT_MAIN_DEFAULT_USE_NUMERIC_SERVER_ADDRESSES false

#define XOS_WEBRTC_CLIENT_MAIN_DEFAULT_WEBRTC_CLIENT_TRACE_LEVELS \
    XOS_WEBRTC_CLIENT_TRACE_LEVELS_TRACE

#define XOS_WEBRTC_CLIENT_MAIN_DEFAULT_WEBRTC_CLIENT_VIDEO_CODEC_MODE \
    XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_VGA

namespace xos {
namespace webrtc {
namespace client {
namespace console {

typedef Window PeerWindow;
typedef Window::WindowPeer WindowPeer;
typedef client::os::SocketServer SocketServer;

typedef xos::HelloImplement MainImplement;
typedef xos::Hello MainExtend;

class _EXPORT_CLASS Main: virtual public MainImplement, public MainExtend {
public:
    typedef MainImplement Implements;
    typedef MainExtend Extends;
    typedef Main Derives;

    typedef int (Derives::*Runner)(int argc, char** argv, char** env);

    typedef Extends::ServiceTcp ServiceTcpExtends;

    class _EXPORT_CLASS ServiceTcp: public Extends::ServiceTcp {
    public:
        typedef ServiceTcpExtends Extends;

        ServiceTcp
        (WindowPeer& windowPeer, TcpConnections& cn, network::Socket& s, bool isRepeated = false)
        : Extends(cn, s, isRepeated), m_windowPeer(windowPeer) {
        }
        virtual void OnRecvdBye() { 
            m_windowPeer.OnQuit();
        }
    protected:
        WindowPeer& m_windowPeer;
    };

    Runner m_runner;

    std::string m_serverName;
    int m_serverPort;

    bool m_showConnectionState;
    bool m_handleButtonEvents;
    bool m_autoConnectToPeerOn;
    bool m_autoConnectToPeerAfterOn;

    VideoCodec::Mode m_videoCodecMode;
    std::string m_webrtcTraceFileName;
    std::string m_webrtcTraceFileDir;
    std::string m_webrtcTraceFileEnv;

    std::string m_videoModeName;
    std::string m_videoDeviceName;

    Main() 
    : m_runner(0),
      
      m_serverName(XOS_WEBRTC_CLIENT_MAIN_DEFAULT_SERVER_NAME),
      m_serverPort(XOS_WEBRTC_CLIENT_MAIN_DEFAULT_SERVER_PORT),

      m_showConnectionState(true),
      m_handleButtonEvents(true),
      m_autoConnectToPeerOn(true),
      m_autoConnectToPeerAfterOn(true),

      m_videoCodecMode
      (XOS_WEBRTC_CLIENT_MAIN_DEFAULT_WEBRTC_CLIENT_VIDEO_CODEC_MODE),

      m_webrtcTraceFileName
      (XOS_WEBRTC_CLIENT_TRACE_DEFAULT_TRACE_FILENAME),

      m_webrtcTraceFileDir
      (XOS_WEBRTC_CLIENT_TRACE_DEFAULT_TRACE_FILEDIR),

      m_webrtcTraceFileEnv
      (XOS_WEBRTC_CLIENT_TRACE_DEFAULT_TRACE_FILEENV)
    {
    }
    virtual ~Main()
    {
    }

    virtual int Run(int argc, char** argv, char** env) {
        if ((Extends::m_runner)) {
            return (this->*Extends::m_runner)(argc, argv, env);
        } else {
            if ((m_runner)) {
                return (this->*m_runner)(argc, argv, env);
            } else {
            }
        }
        return Extends::Run(argc, argv, env);
    }
    virtual int RunClient(int argc, char** argv, char** env) {

        std::string serverName = m_serverName;
        int serverPort = m_serverPort;

        if (optind < (argc)) {
            serverName = argv[optind];
        }
        if (optind+1 < (argc)) {
            std::stringstream ss(argv[optind+1]);
            ss >> serverPort;
        }

        PeerWindow peerWindow
        (serverName.c_str(), serverPort, 
         m_showConnectionState, m_handleButtonEvents, 
         m_autoConnectToPeerOn, m_autoConnectToPeerAfterOn);
        WindowPeer windowPeer(peerWindow);

        SocketServer socketServer(peerWindow);

        std::string webrtcTraceFileName
        (peerWindow.GenerateWebRtcTraceFileName
         (m_webrtcTraceFileEnv, 
          m_webrtcTraceFileDir, 
          m_webrtcTraceFileName));

        Trace::Level webrtcTraceLevels
        = XOS_WEBRTC_CLIENT_MAIN_DEFAULT_WEBRTC_CLIENT_TRACE_LEVELS;

        if ((windowPeer.Open()))
        {
            VideoCodec videoCodec(m_videoCodecMode);

            Trace webrtcTrace
            (webrtcTraceFileName, webrtcTraceLevels);

            Connection connection;

            Conductor conductor
            (videoCodec, webrtcTrace, 
             &connection, &peerWindow, 
             XOS_WEBRTC_CLIENT_MAIN_DEFAULT_USE_NUMERIC_SERVER_ADDRESSES);

            if (0 < (m_videoModeName.length())) {
                conductor.SetVideoCodecModeName(m_videoModeName);
            }
            if (0 < (m_videoDeviceName.length())) {
                conductor.SetVideoCaptureDevice(m_videoDeviceName);
            }

            if (0 < (m_threadsNo)) {
                network::Endpoint* ep = ServerEndpoint(m_host.c_str(), m_portNo);
                network::Socket* s = 0;
                if (s = (network::Socket::New(ep->GetFamily(), network::ip::tcp::Transport::Type, network::ip::tcp::Transport::Protocol))) {
                    if ((s->Bind(ep->SocketAddress(), ep->SocketAddressLen()))) {
                        if ((s->Listen())) {
                            //
                            // Threaded service
                            //
                            TcpConnections cn(*s);
                            ServiceTcp service(windowPeer, cn, *s, true);
                            AcceptTcp accept(cn, service, *ep, *s);
                            std::deque<xos::os::Thread*> tq;
                            xos::os::Thread* ct;

                            //
                            // Start service threads
                            //
                            for (int tNo = 0; tNo < m_threadsNo; tNo++) {
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
                                // Run webrtc client
                                // 
                                peerWindow.ConnectToServer();

                                XOS_LOG_DEBUG("socketServer.Run()...");
                                socketServer.Run();
                                XOS_LOG_DEBUG("...socketServer.Run()");

                                windowPeer.Close();
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
            } else {
                peerWindow.ConnectToServer();

                XOS_LOG_DEBUG("socketServer.Run()...");
                socketServer.Run();
                XOS_LOG_DEBUG("...socketServer.Run()");

                windowPeer.Close();
            }
        }
        return 0;
    }

    virtual int OnOption
    (int optval, const char* optarg,
     const char* optname, int optind,
     int argc, char**argv, char**env)
    {
        int err = 0;
        switch(optval)
        {
        case 'n':
            m_threadsNo = 1;
            m_runner = &Derives::RunClient;
            break;
        case 'd':
            if ((optarg))
            if ((optarg[0]))
            m_videoDeviceName = optarg;
            break;
        case 'v':
            if ((optarg))
            if ((optarg[0]))
            m_videoModeName = optarg;
            break;
        default:
            err = Extends::OnOption(optval, optarg, optname, optind, argc, argv, env);
        }
        return err;
    }
    virtual const char* OptionUsage
    (const char*& optarg, const struct option* longopt)
    {
        const char* chars = "";
        switch(longopt->val)
        {
        case 'n':
            chars = "Connect Server";
            break;
        case 'd':
            optarg = "name";
            chars = "Video Device";
            break;
        case 'v':
            optarg = "name";
            chars = "Video Mode";
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
        static const char* chars = "nd:v:" XOS_HELLO_OPTIONS_CHARS;
        static struct option optstruct[]= {
            {"connect-server", MAIN_OPT_ARGUMENT_NONE, 0, 'n'},
            {"video-device", MAIN_OPT_ARGUMENT_REQUIRED, 0, 'd'},
            {"video-mode", MAIN_OPT_ARGUMENT_REQUIRED, 0, 'v'},
            XOS_HELLO_OPTIONS_OPTIONS
            {0, 0, 0, 0}};
        longopts = optstruct;
        return chars;
    }
    virtual const char* Arguments(const char**& args) {
        static const char* arg[] = {
            "[host] Peer Connection Server Host (Name or IP (ddd.ddd.ddd.ddd))",
            "[port] Peer Connection Server Port (0..65535)",
            0};
        args = arg;
        return "[host [port]]";
    }
};

} // namespace console 
} // namespace client 
} // namespace webrtc 
} // namespace xos 

#endif // _XOS_WEBRTC_CLIENT_CONSOLE_MAIN_HPP 
