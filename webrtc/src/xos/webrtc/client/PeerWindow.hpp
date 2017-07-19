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
///   File: PeerWindow.hpp
///
/// Author: $author$
///   Date: 2/16/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_WEBRTC_CLIENT_PEERWINDOW_HPP
#define _XOS_WEBRTC_CLIENT_PEERWINDOW_HPP

#include "xos/webrtc/client/Window.hpp"
#include "xos/webrtc/client/ConnectorPair.hpp"
#include "xos/webrtc/client/os/UIMessage.hpp"
#include "xos/webrtc/client/os/SocketServer.hpp"

namespace xos {
namespace webrtc {
namespace client {

typedef WindowImplement PeerWindowImplement;
typedef Window PeerWindowExtend;

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS PeerWindow: virtual public PeerWindowImplement, public PeerWindowExtend {
public:
    typedef PeerWindowImplement Implements;
    typedef PeerWindowExtend Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    PeerWindow
    (const char* serverName, int serverPort,
     bool showConnectionState=XOS_WEBRTC_CLIENT_WINDOW_DEFAULT_SHOW_CONNECTION_STATE,
     bool handleButtonEvents=XOS_WEBRTC_CLIENT_WINDOW_DEFAULT_HANDLE_BUTTON_EVENTS) 
    : Extends(serverName, serverPort, showConnectionState, handleButtonEvents),
      m_traceFileName(XOS_WEBRTC_CLIENT_TRACE_DEFAULT_TRACE_FILENAME),
      m_traceFileDir(XOS_WEBRTC_CLIENT_TRACE_DEFAULT_TRACE_FILEDIR),
      m_traceFileEnv(XOS_WEBRTC_CLIENT_TRACE_DEFAULT_TRACE_FILEENV),
      m_traceLevels(XOS_WEBRTC_CLIENT_TRACE_DEFAULT_TRACE_LEVELS),
      m_videoCodecMode(XOS_WEBRTC_CLIENT_VIDEO_CODEC_DEFAULT_VIDEO_CODEC_MODE),
      m_windowPeer(0),
      m_socketServer(0),
      m_connectorPair(0)
    {
    }
    virtual ~PeerWindow() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool OnWindowOpened(WindowPeer* windowPeer) {
        bool isSuccess = false;
        if ((isSuccess = InitUIMessageThread())) {
            m_windowPeer = windowPeer;
            OnOpen();
        }
        return isSuccess;
    }
    virtual bool OnWindowClosed(WindowPeer* windowPeer) {
        bool isSuccess = false;
        OnClose();
        m_windowPeer = 0;
        isSuccess = FinishUIMessageThread();
        return isSuccess;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool OnWindowAttached(WindowPeer* windowPeer) {
        bool isSuccess = false;

        XOS_LOG_DEBUG("...");

        std::string traceFileName
        (GenerateWebRtcTraceFileName
         (m_traceFileEnv, m_traceFileDir, m_traceFileName));

        if ((isSuccess = CreateConnectorPair(traceFileName))) {
            if ((isSuccess = InitUIMessageThread())) {
                m_windowPeer = windowPeer;
                OnOpen();
                if ((isSuccess = CreateUIMessageThread()))
                    return isSuccess;
                FinishUIMessageThread();
                OnClose();
                m_windowPeer = 0;
            }
            DestroyConnectorPair();
        }
        return isSuccess;
    }
    virtual bool OnWindowDetached(WindowPeer* windowPeer) {
        bool isSuccess = DestroyUIMessageThread();
        OnClose();
        m_windowPeer = 0;
        if (!(FinishUIMessageThread()))
            isSuccess = false;
        if (!(DestroyConnectorPair()))
            isSuccess = false;
        return isSuccess;
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool CreateConnectorPair(const std::string& traceFileName) {
        bool isSuccess = false;
        XOS_LOG_DEBUG("...");
        if ((isSuccess = CreateSocketServer(*this))) {
            if ((isSuccess = (0 != (m_connectorPair = new ConnectorPair
                (*this, traceFileName, m_traceLevels, m_videoCodecMode)))))
                return isSuccess;
            DestroySocketServer();
        }
        return isSuccess;
    }
    virtual bool DestroyConnectorPair() {
        bool isSuccess = false;
        if ((isSuccess = (0 != (m_connectorPair)))) {
            delete m_connectorPair;
            m_connectorPair = 0;
        }
        if (!(DestroySocketServer()))
            isSuccess = false;
        return isSuccess;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool CreateSocketServer(Window& peerWindow) {
        bool isSuccess = false;
        XOS_LOG_DEBUG("...");
        if ((isSuccess = (0 != (m_socketServer = new SocketServer(peerWindow)))))
            Connection::SetSocketServer(m_socketServer);
        return isSuccess;
    }
    virtual bool DestroySocketServer() {
        bool isSuccess = false;
        if ((isSuccess = (0 != (m_socketServer))))
        {
            Connection::SetSocketServer(0);
            delete m_socketServer;
            m_socketServer = 0;
        }
        return isSuccess;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool CreateUIMessageThread() {
        bool isSuccess = false;
        XOS_LOG_DEBUG("...");
        isSuccess = m_msgThread.CreateMessageThread(this, m_socketServer);
        return isSuccess;
    }
    virtual bool DestroyUIMessageThread() {
        bool isSuccess = m_msgThread.DestroyMessageThread();
        return isSuccess;
    }
    virtual UIMessage::ThreadId GetUIMessageThreadId() {
        return &m_msgThread;
    }

protected:
    std::string m_traceFileName;
    std::string m_traceFileDir;
    std::string m_traceFileEnv;
    Trace::Level m_traceLevels;
    VideoCodec::Mode m_videoCodecMode;
    WindowPeer* m_windowPeer;
    SocketServer* m_socketServer;
    ConnectorPair* m_connectorPair;
    os::UIMessage::Thread m_msgThread;
};

} // namespace client 
} // namespace webrtc 
} // namespace xos 

#endif // _XOS_WEBRTC_CLIENT_PEERWINDOW_HPP 
