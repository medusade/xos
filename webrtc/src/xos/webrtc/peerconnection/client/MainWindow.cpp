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
///   File: MainWindow.cpp
///
/// Author: $author$
///   Date: 12/25/2012
///////////////////////////////////////////////////////////////////////
#include "xos/webrtc/peerconnection/client/MainWindow.hpp"

namespace xos {
namespace webrtc {
namespace peerconnection {
namespace client {

///////////////////////////////////////////////////////////////////////
///  Class: MainWindow
///
/// Author: $author$
///   Date: 12/25/2012
///////////////////////////////////////////////////////////////////////

MainWindow::MainWindow
(const char* serverName, int serverPort,
 bool autoConnectToPeerOn, bool autoConnectToPeerAfterOn,
 bool showConnectionState,bool handleButtonEvents, bool postButtonEventUIMessages,
 bool useUIMessageQueue, bool useOpenGLRenderer)
: m_showConnectionState(showConnectionState),
  m_handleButtonEvents(handleButtonEvents),
  m_postButtonEventUIMessages(postButtonEventUIMessages),
  m_peerMessageHeader(XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOW_DEFAULT_PEER_MESSAGE_HEADER),
  m_serverName(XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOW_DEFAULT_SERVER_NAME),
  m_serverPort(XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOW_DEFAULT_SERVER_PORT),
  m_peerName(""),
  m_peerId(-1),
  m_connectToPeerName(""),
  m_connectToPeerId(-1),

  m_autoConnectToPeer(false),
  m_autoConnectToPeerOn(autoConnectToPeerOn),
  m_autoConnectToPeerAfter(false),
  m_autoConnectToPeerAfterOn(m_autoConnectToPeerAfterOn),

  m_useOpenGLRendererOff(false),
  m_useOpenGLRenderer(useOpenGLRenderer),
  m_useCallbackInAPI(false),
  m_useUIMessageQueue(useUIMessageQueue),

  ui_(CONNECT_TO_SERVER), 
  ui_thread_id_(0),
  callback_(0),
  gl_renderer_(0),

  m_connectToServerStateName
  (XOS_WEBRTC_PEERCONNECTION_CLIENT_USER_INTERFACE_DEFAULT_STATE_CONNECT_TO_SERVER_NAME),
  m_listPeersStateName
  (XOS_WEBRTC_PEERCONNECTION_CLIENT_USER_INTERFACE_DEFAULT_STATE_LIST_PEERS_NAME),
  m_streamingStateName
  (XOS_WEBRTC_PEERCONNECTION_CLIENT_USER_INTERFACE_DEFAULT_STATE_STREAMING_NAME),

  m_ConnectToServerBefore
  (XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOW_DEFAULT_CONNECT_TO_SERVER_BEFORE),
  m_ConnectToServerAfter
  (XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOW_DEFAULT_CONNECT_TO_SERVER_AFTER),
  m_ConnectToPeerBefore
  (XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOW_DEFAULT_CONNECT_TO_PEER_BEFORE),
  m_ConnectToPeerAfter
  (XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOW_DEFAULT_CONNECT_TO_PEER_AFTER),
  m_Connecting
  (XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOW_DEFAULT_CONNECTING),
  m_NoVideoStreams
  (XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOW_DEFAULT_NO_VIDEO_STREAMS),
  m_NoIncomingVideoStream
  (XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOW_DEFAULT_NO_INCOMMING_VIDEO_STREAM),

  m_attachedWindowPeer(0),
  m_imageObserver(0),
  m_imageDelegated(0),
  m_stateObserver(0)
{
    if ((serverName)) m_serverName = serverName;
    if (0 < (serverPort)) m_serverPort = serverPort;
}
MainWindow::~MainWindow()
{
    VideoRenderer* renderer;
    if ((renderer = remote_video_.release())) ReleaseVideoRenderer(renderer);
    if ((renderer = local_video_.release())) ReleaseVideoRenderer(renderer);
}

bool MainWindow::UpdateWindow() {
    bool isSuccess = true;
    if ((gl_renderer_))
    if (!(gl_renderer_->GetDontUse()))
        gl_renderer_->SwapBuffers();
    return isSuccess;
}
::webrtc::VideoRendererInterface* MainWindow::local_renderer() 
{
    VideoRenderer* renderer;
    return local_video_.get();
}
::webrtc::VideoRendererInterface* MainWindow::remote_renderer() 
{
    VideoRenderer* renderer;
    return remote_video_.get();
}
void MainWindow::StartLocalRenderer(::webrtc::VideoTrackInterface* local_video)
{
    VideoRenderer* renderer;
    if (!(local_video_.get()))
    if ((renderer = AcquireVideoRenderer(local_video, 1, 1, false)))
        local_video_.reset(renderer);
}
void MainWindow::StopLocalRenderer()
{
    VideoRenderer* renderer;
    if ((renderer = local_video_.release()))
        ReleaseVideoRenderer(renderer);
}
void MainWindow::StartRemoteRenderer(::webrtc::VideoTrackInterface* remote_video)
{
    VideoRenderer* renderer;
    if (!(remote_video_.get()))
    if ((renderer = AcquireVideoRenderer(remote_video, 1, 1, true)))
        remote_video_.reset(renderer);
}
void MainWindow::StopRemoteRenderer()
{
    VideoRenderer* renderer;
    if ((renderer = remote_video_.release()))
        ReleaseVideoRenderer(renderer);
}

void MainWindow::SwitchToConnectUI() 
{
    switch(ui_)
    {
    case STREAMING:
        if ((callback_))
            callback_->DisconnectFromServer(true);
        break;

    case LIST_PEERS:
        if ((callback_))
            callback_->DisconnectFromServer(true);
        break;
    }

    m_connectToPeerId = -1;
    m_connectToPeerName = "";

    m_peerId = -1;
    m_peerName = "";

    UI ui = ui_;
    OnChangeUI(ui, ui_ = CONNECT_TO_SERVER);
    OnChangeStateToConnectToServer();
    InvalidateWindow();
}
void MainWindow::SwitchToPeerList(const Peers& peers) 
{
    VideoRenderer* renderer;
    Peers::const_iterator i;
    std::string peerName;
    int peerId;

    if ((renderer = remote_video_.release())) ReleaseVideoRenderer(renderer);
    if ((renderer = local_video_.release())) ReleaseVideoRenderer(renderer);

    m_connectToPeerId = -1;
    m_connectToPeerName = "";

    m_peerId = -1;
    m_peerName = "";
    m_peerList.clear();

    for (i = peers.begin(); i != peers.end(); ++i)
    {
        peerName = i->second;
        peerId = i->first;

        if (0 < (peerName.length()))
        if (0 <= (peerId))
        {
            PeerItem peerItem(peerName, peerId);
            m_peerList.push_back(peerItem);
        }
    }

    for (i = peers.begin(); i != peers.end(); ++i)
    {
        peerName = i->second;
        peerId = i->first;

        if ((token_.CheckIsValid(peerName)))
        {
            m_connectToPeerName = peerName;
            m_connectToPeerId = peerId;
            if ((m_autoConnectToPeer))
            {
                m_autoConnectToPeer = m_autoConnectToPeerAfter;
                m_autoConnectToPeerAfter = (m_autoConnectToPeerAfterOn && m_autoConnectToPeerOn);
                if (!(m_useCallbackInAPI) || !(callback_))
                    PostUIThreadMessage(ui_thread_id_, UI_CONNECT_TO_PEER, 0,0);
                else
                {
                    m_peerName = m_connectToPeerName;
                    m_peerId = m_connectToPeerId;
                    callback_->ConnectToPeer(m_peerId);
                }
            }
            break;
        }
    }

    UI ui = ui_;
    OnChangeUI(ui, ui_ = LIST_PEERS);
    OnChangeStateToListPeers();
    InvalidateWindow();
}
void MainWindow::SwitchToStreamingUI() 
{
    UI ui = ui_;
    OnChangeUI(ui, ui_ = STREAMING);
    OnChangeStateToStreaming();
    ReshapeOpenGLRenderer(gl_renderer_);
    InvalidateWindow();
}

bool MainWindow::SendMessageToPeer(const std::string& message)
{
    bool handled = false;
    if ((callback_))
    {
        std::string messageEnvelope = m_peerMessageHeader;
        messageEnvelope += message;
        handled = callback_->SendMessageToPeer(messageEnvelope);
    }
    return handled;
}

bool MainWindow::OnMessageFromPeer(int peer_id, const std::string& messageEnvelope)
{
    bool handled = false;
    size_t messageHeaderCharsLength;
    const char* messageHeaderChars;
    const char* messageEnvelopeChars;
    const char* messageChars;

    if ((messageEnvelopeChars = messageEnvelope.c_str()))
    if ((messageHeaderChars = m_peerMessageHeader.c_str()))
    if (0 < (messageHeaderCharsLength = m_peerMessageHeader.length()))
    if ((messageChars = strstr(messageEnvelopeChars, messageHeaderChars)))
    {
        std::string message(messageChars+messageHeaderCharsLength);
        OnReceiveMessageFromPeer(message);
        handled = true;
    }
    return handled;
}

void MainWindow::OnOpen()
{
    if ((m_useOpenGLRenderer))
    if ((gl_renderer_ = AcquireOpenGLRenderer()))
    if ((GetUseOpenGLRendererOn()))
        gl_renderer_->Use();
    else
    gl_renderer_->DontUse();
    ui_thread_id_ = GetUIMessageThreadId();
    SwitchToConnectUI();
}
void MainWindow::OnClose()
{
      if (callback_)
        callback_->Close();
      if ((gl_renderer_))
      {
          ReleaseOpenGLRenderer(gl_renderer_);
          gl_renderer_ = 0;
      }
}
void MainWindow::OnSize() 
{
    if ((gl_renderer_))
        ReshapeOpenGLRenderer(gl_renderer_);
}

void MainWindow::OnPaint() 
{
    if ((ui_ == STREAMING) 
        && (remote_video_.get()) 
        && (local_video_.get()))
    {
        AutoLock<VideoRenderer> local_lock(local_video_.get());
        AutoLock<VideoRenderer> remote_lock(remote_video_.get());
        const uint8* local_image;
        const uint8* remote_image;

        // if we have a remote stream
        if ((remote_image = remote_video_->image()))  
        {
            //Get dimensions
            int remote_width  = remote_video_->image_width();
            int remote_height = remote_video_->image_height();

            // if we have a local stream
            if ((local_image = local_video_->image()))
            {
                //Get dimensions
                int local_width  = local_video_->image_width();
                int local_height = local_video_->image_height();

                if ((OnPaintImage
                    (remote_image, remote_width, remote_height,
                     local_image, local_width, local_height)))
                    return;
            }
            else
            if ((OnPaintImage
                (remote_image, remote_width, remote_height, false)))
                return;
        }
        else
        // if we have a local stream
        if ((local_image = local_video_->image()))  
        {
            //Get dimensions
            int local_width  = local_video_->image_width();
            int local_height = local_video_->image_height();

            if ((OnPaintImage
                (local_image, local_width, local_height, true)))
                return;
        }
    }
    OnPaintBlank();
}
bool MainWindow::OnPaintImage
(const uint8* remote_image, int remote_width, int remote_height,
 const uint8* local_image, int local_width, int local_height) 
{
    if ((gl_renderer_))
    if (!(gl_renderer_->GetDontUse()))
    {
        ValidateWindow();
        gl_renderer_->Render
        (remote_image, remote_width, remote_height,
         local_image, local_width, local_height);
        UpdateWindow();
        return true;
    }
    if ((OnRenderImage
        (remote_image, remote_width, remote_height,
         local_image, local_width, local_height)))
        return true;
    return false;
}
bool MainWindow::OnPaintImage
(const uint8* image, int width, int height, bool is_local) 
{
    if ((gl_renderer_))
    if (!(gl_renderer_->GetDontUse()))
    {
        ValidateWindow();
        gl_renderer_->Render(image, width, height);
        UpdateWindow();
        return true;
    }
    if ((OnRenderImage(image, width, height, 0,0,0, is_local)))
        return true;
    return false;
}

void MainWindow::OnDefaultAction(int msg_id, int id, void* data)
{
    if ((callback_))
    switch(msg_id)
    {
    case UI_THREAD_CALLBACK:
        callback_->UIThreadCallback((id), (data));
        break;

    case UI_CONNECT_TO_SERVER:
        switch(ui_)
        {
        case CONNECT_TO_SERVER:
            callback_->StartLogin(m_serverName, m_serverPort);
            break;
        }
        break;

    case UI_DISCONNECT_SERVER:
        switch(ui_)
        {
        case STREAMING:
            callback_->DisconnectFromServer();
            break;

        case LIST_PEERS:
            callback_->DisconnectFromServer();
            break;
        }
        break;

    case UI_CONNECT_TO_PEER:
        switch(ui_)
        {
        case LIST_PEERS:
            if (0 > (m_peerId))
            {
                m_peerId = m_connectToPeerId;
                m_peerName = m_connectToPeerName;
                callback_->ConnectToPeer(m_peerId);
            }
            break;
        }
        break;

    case UI_DISCONNECT_PEER:
        switch(ui_)
        {
        case STREAMING:
            m_autoConnectToPeer = false;
            callback_->DisconnectFromCurrentPeer();
            break;
        }
        break;

    case UI_LBUTTON_UP:
        if ((m_handleButtonEvents))
        switch(ui_)
        {
        case CONNECT_TO_SERVER:
            m_autoConnectToPeer = m_autoConnectToPeerOn;
            m_autoConnectToPeerAfter = (m_autoConnectToPeerAfterOn && m_autoConnectToPeerOn);
            callback_->StartLogin(m_serverName, m_serverPort);
            break;

        case LIST_PEERS:
            if (0 <= (m_connectToPeerId))
            {
                m_peerId = m_connectToPeerId;
                m_peerName = m_connectToPeerName;
                callback_->ConnectToPeer(m_peerId);
            }
            else
            callback_->DisconnectFromServer();
            break;

        case STREAMING:
            m_autoConnectToPeer = false;
            callback_->DisconnectFromCurrentPeer();
            break;
        }
        break;

    case UI_RBUTTON_UP:
        if ((m_handleButtonEvents))
        switch(ui_)
        {
        case CONNECT_TO_SERVER:
            m_autoConnectToPeer = m_autoConnectToPeerOn;
            m_autoConnectToPeerAfter = (m_autoConnectToPeerAfterOn && m_autoConnectToPeerOn);
            callback_->StartLogin(m_serverName, m_serverPort);
            break;

        case LIST_PEERS:
            callback_->DisconnectFromServer();
            break;

        case STREAMING:
            m_autoConnectToPeer = false;
            callback_->DisconnectFromServer();
            break;
        }
        break;
    }
}

} // namespace client 
} // namespace peerconnection 
} // namespace webrtc 
} // namespace xos 
