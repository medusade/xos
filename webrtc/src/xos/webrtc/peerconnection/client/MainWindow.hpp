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
///   File: MainWindow.hpp
///
/// Author: $author$
///   Date: 12/25/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_WEBRTC_PEERCONNECTION_CLIENT_MAINWINDOW_HPP
#define _XOS_WEBRTC_PEERCONNECTION_CLIENT_MAINWINDOW_HPP

#include "xos/webrtc/peerconnection/client/UserInterface.hpp"
#include "xos/webrtc/peerconnection/client/RendererInterface.hpp"
#include "xos/webrtc/peerconnection/client/ImageInterface.hpp"
#include "xos/webrtc/peerconnection/client/Options.hpp"
#include "xos/webrtc/peerconnection/client/UIMessage.hpp"
#include "xos/webrtc/peerconnection/client/Token.hpp"
#include "xos/webrtc/peerconnection/client/VideoRenderer.hpp"
#include "xos/webrtc/peerconnection/client/OpenGL.hpp"
#include <string>
#include <vector>

#define XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOW_DEFAULT_SERVER_NAME "localhost"
#define XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOW_DEFAULT_SERVER_PORT 8888
#define XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOW_DEFAULT_AUTO_CONNECT_TO_PEER_ON false
#define XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOW_DEFAULT_AUTO_CONNECT_TO_PEER_AFTER_ON false

#define XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOW_DEFAULT_USE_OPENGL_RENDERER false
#define XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOW_DEFAULT_USE_UI_MESSAGE_QUEUE false
#define XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOW_DEFAULT_SHOW_CONNECTION_STATE true
#define XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOW_DEFAULT_HANDLE_BUTTON_EVENTS true
#define XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOW_DEFAULT_POST_BUTTON_EVENT_UI_MESSAGES false

#define XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOW_DEFAULT_WEBRTC_PEERCONNECTION_CLIENT_TRACE_LEVELS \
    XOS_WEBRTC_PEERCONNECTION_CLIENT_TRACE_LEVELS_TRACE

#define XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOW_DEFAULT_PEER_MESSAGE_HEADER \
    "SEND_MESSAGE_TO_PEER:"

#define XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOW_DEFAULT_CONNECT_TO_SERVER_BEFORE "Connect to Server \""
#define XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOW_DEFAULT_CONNECT_TO_SERVER_AFTER "\"..."
#define XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOW_DEFAULT_CONNECT_TO_PEER_BEFORE "Connect to Peer \""
#define XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOW_DEFAULT_CONNECT_TO_PEER_AFTER "\"..."
#define XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOW_DEFAULT_CONNECTING "Connecting... "
#define XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOW_DEFAULT_NO_VIDEO_STREAMS "(no video streams either way)"
#define XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOW_DEFAULT_NO_INCOMMING_VIDEO_STREAM "(no incoming video stream)"

#define XOS_WEBRTC_PEERCONNECTION_CLIENT_USER_INTERFACE_DEFAULT_STATE_CONNECT_TO_SERVER_NAME "ConnectToServer"
#define XOS_WEBRTC_PEERCONNECTION_CLIENT_USER_INTERFACE_DEFAULT_STATE_LIST_PEERS_NAME "ListPeers"
#define XOS_WEBRTC_PEERCONNECTION_CLIENT_USER_INTERFACE_DEFAULT_STATE_STREAMING_NAME "Streaming"

#define XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOW_DEFAULT_BACKGROUND_RED   0
#define XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOW_DEFAULT_BACKGROUND_GREEN 0
#define XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOW_DEFAULT_BACKGROUND_BLUE  0

#define XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOW_DEFAULT_CONNECT_TO_PEER_RED   0
#define XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOW_DEFAULT_CONNECT_TO_PEER_GREEN 128
#define XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOW_DEFAULT_CONNECT_TO_PEER_BLUE  0

#define XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOW_DEFAULT_CONNECT_TO_SERVER_RED 0
#define XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOW_DEFAULT_CONNECT_TO_SERVER_GREEN 0
#define XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOW_DEFAULT_CONNECT_TO_SERVER_BLUE 128

#define XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOW_DEFAULT_CONNECTING_RED 0
#define XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOW_DEFAULT_CONNECTING_GREEN 0
#define XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOW_DEFAULT_CONNECTING_BLUE 0

namespace xos {
namespace webrtc {
namespace peerconnection {
namespace client {

///////////////////////////////////////////////////////////////////////
///  Class: PeerItem
///
/// Author: $author$
///   Date: 12/25/2012
///////////////////////////////////////////////////////////////////////
class PeerItem {
public:
    std::string m_name;
    int m_id;

    PeerItem
    (const std::string& name, int id)
    : m_name(name), m_id(id){
    }
    PeerItem
    (const PeerItem& item)
    : m_name(item.m_name), m_id(item.m_id){
    }
};
typedef std::vector<PeerItem> PeerList;

typedef UserInterfaceImplement MainWindowImplementImplement;
///////////////////////////////////////////////////////////////////////
///  Class: MainWindowImplement
///
/// Author: $author$
///   Date: 1/8/2013
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS MainWindowImplement
: virtual public MainWindowImplementImplement,
  virtual public RendererInterface,
  virtual public ImageInterface
{
public:
    typedef MainWindowImplementImplement Implements;
    typedef ImageInterface ImageImplements;
};
typedef Options MainWindowExtend;
///////////////////////////////////////////////////////////////////////
///  Class: MainWindow
///
/// Author: $author$
///   Date: 12/25/2012
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS MainWindow
: virtual public MainWindowImplement,
  public MainWindowExtend
{
public:
    typedef MainWindowImplement Implements;
    typedef MainWindowExtend Extends;

    class _EXPORT_CLASS WindowPeer;

    enum UIMessages 
    {
        UI_THREAD_CALLBACK = 1,
        UI_CONNECT_TO_SERVER,
        UI_DISCONNECT_SERVER,
        UI_CONNECT_TO_PEER,
        UI_DISCONNECT_PEER,
        UI_LBUTTON_UP,
        UI_RBUTTON_UP,
        UI_THREAD_QUIT,
        UI_THREAD_WAKEUP
    };

    MainWindow
    (const char* serverName, int serverPort,
     bool autoConnectToPeerOn=XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOW_DEFAULT_AUTO_CONNECT_TO_PEER_ON, 
     bool autoConnectToPeerAfterOn=XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOW_DEFAULT_AUTO_CONNECT_TO_PEER_AFTER_ON,
     bool showConnectionState=XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOW_DEFAULT_SHOW_CONNECTION_STATE,
     bool handleButtonEvents=XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOW_DEFAULT_HANDLE_BUTTON_EVENTS,
     bool postButtonEventUIMessages=XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOW_DEFAULT_POST_BUTTON_EVENT_UI_MESSAGES,
     bool useUIMessageQueue=XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOW_DEFAULT_USE_UI_MESSAGE_QUEUE,
     bool useOpenGLRenderer=XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOW_DEFAULT_USE_OPENGL_RENDERER);
    virtual ~MainWindow();

    ///////////////////////////////////////////////////////////////////////
    // observer
    ///////////////////////////////////////////////////////////////////////
    virtual void RegisterObserver
    (ConductorInterface* callback) 
    { callback_ = callback; }
    virtual void UnRegisterObserver() 
    { callback_ = 0; }

    ///////////////////////////////////////////////////////////////////////
    // window
    ///////////////////////////////////////////////////////////////////////
    virtual bool UpdateWindow();
    virtual bool ValidateWindow() { 
        if ((m_imageObserver))
            return m_imageObserver->ValidateWindow();
        return false; 
    }
    virtual bool InvalidateWindow(bool eraseBackground = true) { 
        if ((m_imageObserver))
            return m_imageObserver->InvalidateWindow(eraseBackground);
        return false; 
    }
    virtual bool IsWindow() { 
        if ((m_imageObserver))
            return m_imageObserver->IsWindow();
        return true; 
    }
    virtual UI current_ui() { return ui_; }

    ///////////////////////////////////////////////////////////////////////
    // renderers
    ///////////////////////////////////////////////////////////////////////
    virtual OpenGL::VideoRenderer* AcquireOpenGLRenderer() { return 0; }
    virtual bool ReleaseOpenGLRenderer
    (OpenGL::VideoRenderer* renderer) { return false; }

    virtual bool ReshapeOpenGLRenderer
    (OpenGL::VideoRenderer* renderer) { return false; }

    virtual VideoRenderer* AcquireVideoRenderer
    (webrtc::VideoTrackInterface* track_to_render,
     size_t width, size_t height, bool isRemote=false) { return 0; }
    virtual bool ReleaseVideoRenderer
    (VideoRenderer* renderer) { return false; }

    virtual ::webrtc::VideoRendererInterface* local_renderer();
    virtual ::webrtc::VideoRendererInterface* remote_renderer();

    virtual void StartLocalRenderer(::webrtc::VideoTrackInterface* local_video);
    virtual void StopLocalRenderer();
    virtual void StartRemoteRenderer(::webrtc::VideoTrackInterface* remote_video);
    virtual void StopRemoteRenderer();

    ///////////////////////////////////////////////////////////////////////
    // images
    ///////////////////////////////////////////////////////////////////////
    virtual uint8_t* AcquireImage
    (VideoRenderer* video, int& width, int& height, Format& format) {
        uint8_t* image = 0;
        if ((video)) {
            video->Lock();
            if (!(image = video->d_image())) {
                video->Unlock();
            } else {
                width = video->image_width();
                height = video->image_height();
                switch(video->RenderImageFormat()) 
                {
                case cricket::FOURCC_ARGB:
                    format = FORMAT_GL_BGRA;
                    break;
                default:
                    format = FORMAT_NONE;
                }
            }
        }
        return image;
    }
    virtual bool ReleaseImage(VideoRenderer* video, uint8_t* image) {
        bool success = false;
        if ((video)) {
            if (!(image != video->d_image())) {
                video->Unlock();
                success = true;
            }
        }
        return success;
    }
    //
    // local
    //
    virtual uint8_t* AcquireLocalImage(int& width, int& height, Format& format) {
        uint8_t* image = 0;
        ImageInterface* imageInterface;
        if ((imageInterface = ImageInterfaceDelegated()))
            image = imageInterface->AcquireLocalImage(width, height, format);
        else
        image = AcquireImage(local_video_.get(), width, height, format);
        return image;
    }
    virtual bool ReleaseLocalImage(uint8_t* image) {
        bool success = false;
        ImageInterface* imageInterface;
        if ((imageInterface = ImageInterfaceDelegated()))
            success = imageInterface->ReleaseLocalImage(image);
        else
        success = ReleaseImage(local_video_.get(), image);
        return success;
    }
    //
    // remote
    //
    virtual uint8_t* AcquireRemoteImage(int& width, int& height, Format& format) {
        uint8_t* image = 0;
        ImageInterface* imageInterface;
        if ((imageInterface = ImageInterfaceDelegated()))
            image = imageInterface->AcquireRemoteImage(width, height, format);
        else
        image = AcquireImage(remote_video_.get(), width, height, format);
        return image;
    }
    virtual bool ReleaseRemoteImage(uint8_t* image) {
        bool success = false;
        ImageInterface* imageInterface;
        if ((imageInterface = ImageInterfaceDelegated()))
            success = imageInterface->ReleaseRemoteImage(image);
        else
        success = ReleaseImage(remote_video_.get(), image);
        return success;
    }
    //
    // observer
    //
    virtual void RegisterImageObserver(ImageObserverInterface* imageObserver) {
        ImageInterface* imageInterface;
        if ((imageInterface = ImageInterfaceDelegated()))
            imageInterface->RegisterImageObserver(imageObserver);
        else
        if ((imageObserver) && (!m_imageObserver))
            m_imageObserver = imageObserver;
    }
    virtual void UnregisterImageObserver(ImageObserverInterface* imageObserver) {
        ImageInterface* imageInterface;
        if ((imageInterface = ImageInterfaceDelegated()))
            imageInterface->UnregisterImageObserver(imageObserver);
        else
        if ((imageObserver) && (imageObserver == (m_imageObserver)))
            m_imageObserver = 0;
    }
    //
    // delegated
    //
    virtual ImageInterface* DelegateImageInterface(ImageInterface* imageDelegated) {
        if ((imageDelegated))
            return m_imageDelegated = imageDelegated;
        return 0;
    }
    virtual ImageInterface* DismissImageInterface(ImageInterface* imageDelegated) {
        if ((imageDelegated) && (imageDelegated == m_imageDelegated)) {
            m_imageDelegated = 0;
            return imageDelegated;
        }
        return 0;
    }
    virtual ImageInterface* ImageInterfaceDelegated() const  {
        return m_imageDelegated;
    }

    ///////////////////////////////////////////////////////////////////////
    // switch state
    ///////////////////////////////////////////////////////////////////////
    virtual void SwitchToConnectUI();
    virtual void SwitchToPeerList(const Peers& peers);
    virtual void SwitchToStreamingUI();

    virtual void MessageBox
    (const char* caption, const char* text, bool is_error) {}

    virtual void QueueUIThreadCallback(int msg_id, void* data) {
        PostUIThreadMessage(ui_thread_id_, UI_THREAD_CALLBACK, (msg_id), (data));
    }
    virtual const std::string GetThisPeerName() {
        std::string name;
        token_.Make(name);
        return name;
    }
    virtual void SetThisPeerName(const std::string& name) {
        token_.SetPeerName(name.c_str());
    }

    ///////////////////////////////////////////////////////////////////////
    // peer messages
    ///////////////////////////////////////////////////////////////////////
    virtual bool SendMessageToPeer(const std::string& message);
    virtual bool OnMessageFromPeer(int peer_id, const std::string& messageEnvelope);
    virtual bool OnReceiveMessageFromPeer(const std::string& message) {
        return false; }
    virtual void OnFailedToConnectToServer(const std::string& server) {}

    ///////////////////////////////////////////////////////////////////////
    // state change
    ///////////////////////////////////////////////////////////////////////
    virtual void OnChangeStateToConnectToServer() {
        UserInterfaceStateObserver* stateObserver;
        if ((stateObserver = StateObserver()))
            stateObserver->OnChangeStateToConnectToServer();
        OnChangeState("ConnectToServer");
    }
    virtual void OnChangeStateToListPeers() {
        UserInterfaceStateObserver* stateObserver;
        if ((stateObserver = StateObserver()))
            stateObserver->OnChangeStateToListPeers();
        OnChangeState("ListPeers");
    }
    virtual void OnChangeStateToStreaming() {
        UserInterfaceStateObserver* stateObserver;
        if ((stateObserver = StateObserver()))
            stateObserver->OnChangeStateToStreaming();
        OnChangeState("Streaming");
    }
    virtual void OnChangeState(const std::string& toStateName) {
        UserInterfaceStateObserver* stateObserver;
        if ((stateObserver = StateObserver()))
            stateObserver->OnChangeState(toStateName);
    }
    virtual void OnChangeUI(UI uiFrom, UI uiTo) {
    }
    ///////////////////////////////////////////////////////////////////////
    // state observer
    ///////////////////////////////////////////////////////////////////////
    virtual bool RegisterStateObserver(UserInterfaceStateObserver* stateObserver) { 
        if ((stateObserver)) {
            m_stateObserver = stateObserver;
            return true;
        }
        return false; 
    }
    virtual bool UnregisterStateObserver(UserInterfaceStateObserver* stateObserver) { 
        if ((stateObserver && (stateObserver == m_stateObserver))) {
            m_stateObserver = 0;
            return true;
        }
        return false; 
    }
    virtual UserInterfaceStateObserver* StateObserver() const { 
        return m_stateObserver; 
    }
    ///////////////////////////////////////////////////////////////////////
    // window attached
    ///////////////////////////////////////////////////////////////////////
    virtual bool WindowAttached(WindowPeer* windowPeer) {
        bool isSuccess;
        WindowPeer* attached;
        if ((attached = AttachedWindowPeer())) {
            if (!(WindowDetached(attached))) {
                return false;
            }
        }
        if ((isSuccess = CreateConnectorPair())) {
            if ((isSuccess = InitUIMessageThread())) {
                AttachWindowPeer(windowPeer);
                OnOpen();
                if ((isSuccess = CreateUIMessageThread()))
                    return isSuccess;
                OnClose();
                DetachWindowPeer();
                FinishUIMessageThread();
            }
            DestroyConnectorPair();
        }
        return isSuccess;
    }
    virtual bool WindowDetached(WindowPeer* windowPeer) {
        bool isSuccess;
        WindowPeer* attached;
        if (windowPeer != (attached = AttachedWindowPeer())) {
            return false;
        }
        isSuccess = DestroyUIMessageThread();
        OnClose();
        DetachWindowPeer();
        if (!(FinishUIMessageThread()))
            isSuccess = false;
        if (!(DestroyConnectorPair()))
            isSuccess = false;
        return isSuccess;
    }

    ///////////////////////////////////////////////////////////////////////
    // window opened
    ///////////////////////////////////////////////////////////////////////
    virtual bool WindowOpened(WindowPeer* windowPeer) {
        bool isSuccess;
        WindowPeer* attached;
        if ((attached = AttachedWindowPeer())) {
            if (!(WindowClosed(attached))) {
                return false;
            }
        }
        if ((isSuccess = InitUIMessageThread())) {
            AttachWindowPeer(windowPeer);
            OnOpen();
        }
        return isSuccess;
    }
    virtual bool WindowClosed(WindowPeer* windowPeer) {
        bool isSuccess;
        WindowPeer* attached;
        if (windowPeer != (attached = AttachedWindowPeer())) {
            return false;
        }
        OnClose();
        DetachWindowPeer();
        isSuccess = FinishUIMessageThread();
        return isSuccess;
    }

    ///////////////////////////////////////////////////////////////////////
    // attached
    ///////////////////////////////////////////////////////////////////////
    virtual bool Attached() {
        bool isSuccess;
        if ((isSuccess = CreateConnectorPair())) {
            if ((isSuccess = InitUIMessageThread())) {
                OnOpen();
                if ((isSuccess = CreateUIMessageThread()))
                    return isSuccess;
                OnClose();
                FinishUIMessageThread();
            }
            DestroyConnectorPair();
        }
        return isSuccess;
    }
    virtual bool Detached() {
        bool isSuccess;
        isSuccess = DestroyUIMessageThread();
        OnClose();
        if (!(FinishUIMessageThread()))
            isSuccess = false;
        if (!(DestroyConnectorPair()))
            isSuccess = false;
        return isSuccess;
    }

    ///////////////////////////////////////////////////////////////////////
    // opend
    ///////////////////////////////////////////////////////////////////////
    virtual bool Opened() {
        bool isSuccess;
        if ((isSuccess = InitUIMessageThread())) {
            OnOpen();
        }
        return isSuccess;
    }
    virtual bool Closed() {
        bool isSuccess;
        OnClose();
        isSuccess = FinishUIMessageThread();
        return isSuccess;
    }

protected:
    virtual void OnOpen();
    virtual void OnClose();
    virtual void OnSize();

    ///////////////////////////////////////////////////////////////////////
    // paint
    ///////////////////////////////////////////////////////////////////////
    virtual void OnPaint();
    virtual bool OnPaintImage
    (const uint8* remote_image, int remote_width, int remote_height,
     const uint8* local_image, int local_width, int local_height);
    virtual bool OnPaintImage
    (const uint8* image, int width, int height, bool is_local);
    virtual bool OnPaintBlank() {
        return false; }

    virtual bool OnRenderImage
    (const uint8* remote_image, int remote_width, int remote_height,
     const uint8* local_image, int local_width, int local_height, 
     bool is_local = false) { return false; }

    ///////////////////////////////////////////////////////////////////////
    // actions
    ///////////////////////////////////////////////////////////////////////
    virtual void OnLButtonUp()
    {
        if ((m_postButtonEventUIMessages))
            PostUIMessage(UI_LBUTTON_UP, 0,0);
        else
        OnUIMessage(UI_LBUTTON_UP, 0,0);
    }
    virtual void OnRButtonUp()
    {
        if ((m_postButtonEventUIMessages))
            PostUIMessage(UI_RBUTTON_UP, 0,0);
        else
        OnUIMessage(UI_RBUTTON_UP, 0,0);
    }
    virtual void OnDefaultAction
    (int msg_id, int id, void* data);

    ///////////////////////////////////////////////////////////////////////
    // UI message queue
    ///////////////////////////////////////////////////////////////////////
    virtual bool InitUIMessageQueue() {
        bool isSuccess = true;
        isSuccess = ui_message_queue_.Init();
        return isSuccess;
    }
    virtual bool FinishUIMessageQueue() {
        bool isSuccess = true;
        isSuccess = ui_message_queue_.Finish();
        return isSuccess;
    }

    ///////////////////////////////////////////////////////////////////////
    // UI message thread
    ///////////////////////////////////////////////////////////////////////
    virtual bool InitUIMessageThread() {
        bool isSuccess = true;
        if ((m_useUIMessageQueue))
            isSuccess = InitUIMessageQueue();
        return isSuccess;
    }
    virtual bool FinishUIMessageThread() {
        bool isSuccess = true;
        if ((m_useUIMessageQueue))
            isSuccess = FinishUIMessageQueue();
        return isSuccess;
    }
    virtual bool CreateUIMessageThread() { return false; }
    virtual bool DestroyUIMessageThread() { return false; }

    virtual bool CreateConnectorPair() { return false; }
    virtual bool DestroyConnectorPair() { return false; }

    virtual void PostUIThreadMessage
    (UIMessage::ThreadId tid, int msg_id, int id, void* data) {
        if ((m_useUIMessageQueue))
            ui_message_queue_.PostUIMessage(msg_id, id, data);
    }
    virtual UIMessage::ThreadId GetUIMessageThreadId() { return 0; }

public:
    ///////////////////////////////////////////////////////////////////////
    // UI messages
    ///////////////////////////////////////////////////////////////////////
    virtual bool PostUIMessage
    (int msg_id, int id, void* data)
    { 
        if ((m_useUIMessageQueue)) 
            return ui_message_queue_.PostUIMessage(msg_id, id, data);

        PostUIThreadMessage(ui_thread_id_, msg_id, id, data); 
        return true;
    }
    virtual bool GetUIMessage
    (int& msg_id, int& id, void*& data,
     int filterMin = -1, int filterMax = -1)
    { 
        if ((m_useUIMessageQueue)) 
            return ui_message_queue_.GetUIMessage
            (msg_id, id, data, filterMin, filterMax);
        return false; 
    }
    virtual bool PeekUIMessage
    (int& msg_id, int& id, void*& data,
     int filterMin = -1, int filterMax = -1, 
     bool dontRemove=false, int dontRemoveMin = -1, int dontRemoveMax = -1)
    { 
        if ((m_useUIMessageQueue)) 
            return ui_message_queue_.PeekUIMessage
            (msg_id, id, data, filterMin, filterMax, 
             dontRemove, dontRemoveMin, dontRemoveMax);
        return false; 
    }
    virtual bool OnUIMessage
    (int msg_id, int id, void* data)
    { 
        OnDefaultAction(msg_id, id, data);
        return true; 
    }

    ///////////////////////////////////////////////////////////////////////
    // connection to server
    ///////////////////////////////////////////////////////////////////////
    virtual bool ConnectToServer
    (const std::string& serverName, int serverPort)
    {
        std::string portSeparator = ":";
        std::string hostName = serverName;
        int hostPort = serverPort;
        size_t portPos;

        if ((portPos = serverName.find_last_of(portSeparator))
            != (serverName.npos))
        {
            std::string hostPortString(serverName.c_str()+portPos+portSeparator.length());
            std::stringstream hostPortStream(hostPortString);
            hostName.assign(serverName.c_str(), portPos);
            hostPortStream >> hostPort;
        }

        if ((0 < (hostName.length())))
            m_serverName = hostName;

        if ((0 < (hostPort)))
            m_serverPort = hostPort;

        return ConnectToServer();
    }
    virtual bool ConnectToServer()
    {
        m_autoConnectToPeer = m_autoConnectToPeerOn;
        m_autoConnectToPeerAfter = m_autoConnectToPeerAfterOn;

        SwitchToConnectUI();
        if (!(m_useCallbackInAPI) || !(callback_))
            PostUIThreadMessage(ui_thread_id_, UI_CONNECT_TO_SERVER, 0,0);
        else
        callback_->StartLogin(m_serverName, m_serverPort);
        return true;
    }
    virtual bool DisconnectFromServer()
    { 
        SwitchToConnectUI(); 
        return true; 
    }

    ///////////////////////////////////////////////////////////////////////
    // connection to peer
    ///////////////////////////////////////////////////////////////////////
    virtual bool ConnectToPeer(const std::string& peerName)
    {
        if (0 >= (peerName.length()))
            return ConnectToPeer();

        if ((LIST_PEERS == (ui_)) && (0 > m_peerId))
        {
            PeerList::const_iterator i;
            for (i = m_peerList.begin(); i != m_peerList.end(); i++)
            {
                PeerItem peerItem(*i);
                if ((peerItem.m_name != peerName))
                    continue;

                m_connectToPeerName = peerItem.m_name;
                return ConnectToPeer(peerItem.m_id);
            }
        }
        return false;
    }
    virtual bool ConnectToPeer(int peerId)
    {
        if (0 > (peerId))
            return ConnectToPeer();

        if ((LIST_PEERS == (ui_)) && (0 > m_peerId))
        {
            m_connectToPeerId = peerId;
            return ConnectToPeer();
        }
        return false;
    }
    virtual bool ConnectToPeer()
    { 
        if ((LIST_PEERS == (ui_)) && (0 <= (m_connectToPeerId)) && (0 > m_peerId))
        {
            if (!(m_useCallbackInAPI) || !(callback_))
                PostUIThreadMessage(ui_thread_id_, UI_CONNECT_TO_PEER, 0,0);
            else
            {
                m_peerName = m_connectToPeerName;
                m_peerId = m_connectToPeerId;
                callback_->ConnectToPeer(m_peerId);
            }
            return true;
        }
        return false; 
    }
    virtual bool DisconnectFromPeer()
    { 
        if (STREAMING == (ui_))
        {
            m_autoConnectToPeer = false;
            if (!(m_useCallbackInAPI) || !(callback_))
                PostUIThreadMessage(ui_thread_id_, UI_DISCONNECT_PEER, 0,0);
            else
            callback_->DisconnectFromCurrentPeer();
            return true;
        }
        return false; 
    }

    ///////////////////////////////////////////////////////////////////////
    // server
    ///////////////////////////////////////////////////////////////////////
    virtual void SetServerName(const std::string& toName)
    { m_serverName = toName; }
    virtual void SetServerName(const char* toChars)
    { m_serverName = toChars; }
    virtual const char* GetServerName() const
    { const char* val=m_serverName.c_str(); return val; }
    virtual void SetServerPort(int serverPort)
    { m_serverPort = serverPort; }
    virtual int GetServerPort() const
    { int val = m_serverPort; return val; }

    ///////////////////////////////////////////////////////////////////////
    // peer
    ///////////////////////////////////////////////////////////////////////
    virtual void SetConnectToPeerName(const std::string& toName)
    { m_connectToPeerName = toName; }
    virtual void SetConnectToPeerName(const char* toChars)
    { m_connectToPeerName = toChars; }
    virtual const char* GetConnectToPeerName() const
    { const char* val=m_connectToPeerName.c_str(); return val; }

    ///////////////////////////////////////////////////////////////////////
    // options
    ///////////////////////////////////////////////////////////////////////
    virtual void SetAutoConnectToPeerOn(bool isTrue=true)
    { m_autoConnectToPeerOn = isTrue; }
    virtual bool GetAutoConnectToPeerOn() const
    { bool val=m_autoConnectToPeerOn; return val; }

    virtual void SetAutoConnectToPeerAfterOn(bool isTrue=true)
    { m_autoConnectToPeerAfterOn = isTrue; }
    virtual bool GetAutoConnectToPeerAfterOn() const
    { bool val=m_autoConnectToPeerAfterOn; return val; }

    virtual void SetUseOpenGLRendererOn(bool isTrue=true)
    { m_useOpenGLRendererOff = !isTrue; }
    virtual bool GetUseOpenGLRendererOn() const
    { bool val=!m_useOpenGLRendererOff; return val; }

    virtual void UseOpenGLRenderer()
    { 
        SetUseOpenGLRendererOn(); 
        if ((gl_renderer_))
            gl_renderer_->Use();
    }
    virtual void DontUseOpenGLRenderer()
    { 
        SetUseOpenGLRendererOn(false); 
        if ((gl_renderer_))
            gl_renderer_->DontUse();
    }

    ///////////////////////////////////////////////////////////////////////
    // trace filenames
    ///////////////////////////////////////////////////////////////////////
    virtual std::string GenerateWebRtcTraceFileName
    (const std::string& p_webrtcTraceFileEnv,
     const std::string& p_webrtcTraceFileDir,
     const std::string& p_webrtcTraceFileName) const
    {
        std::string webrtcTraceFileDir(p_webrtcTraceFileDir);
        bool isAbsoluteDir = false;
        char dirSeparatorChar = '/';
        const char* separator = 0;
        const char* chars = 0;
        size_t length;

        if (0 < ( p_webrtcTraceFileEnv.length()))
        if ((chars =  p_webrtcTraceFileEnv.c_str()))
        if ((isAbsoluteDir = (chars = getenv(chars))))
        {
            webrtcTraceFileDir.assign(chars);
            if (0 < (p_webrtcTraceFileDir.length()))
            if (0 < (length = webrtcTraceFileDir.length()))
            if ((chars = webrtcTraceFileDir.c_str()))
            {
                if ('/' != (chars[length-1]))
                if ('\\' != (chars[length-1]))
                    webrtcTraceFileDir.append(&dirSeparatorChar, 1);
                webrtcTraceFileDir.append(p_webrtcTraceFileDir);
            }
        }
        return GenerateWebRtcTraceFileName
        (webrtcTraceFileDir, p_webrtcTraceFileName, isAbsoluteDir);
    }
    virtual std::string GenerateWebRtcTraceFileName
    (const std::string& p_webrtcTraceFileDir,
     const std::string& p_webrtcTraceFileName,
     bool isAbsoluteDir=false) const
    {
        std::string webrtcTraceFileName(p_webrtcTraceFileName);
        char dirSeparatorChar = 0;
        const char* separator = 0;
        const char* chars = 0;
        size_t length;

        if (0 < (length = p_webrtcTraceFileDir.length()))
        if ((chars = p_webrtcTraceFileDir.c_str()))
        if ('/' != (chars[length-1]))
        if ('\\' != (chars[length-1]))
            dirSeparatorChar = '/';
 
        if ((isAbsoluteDir))
        {
            if (0 < (p_webrtcTraceFileDir.length()))
            {
                webrtcTraceFileName.assign(p_webrtcTraceFileDir);
                if ((dirSeparatorChar))
                    webrtcTraceFileName.append(&dirSeparatorChar, 1);
                webrtcTraceFileName.append(p_webrtcTraceFileName);
            }
        }
        else
        {
            //
            // Make path relative to module file name
            //
            std::string webrtcTraceModuleFileName(GetThisModuleFileName());

            if ((chars = webrtcTraceModuleFileName.c_str()))
            {
                if (!(separator = strrchr(chars, '/')))
                    separator = strrchr(chars, '\\');
            }
            if ((separator))
            {
                webrtcTraceFileName.assign(chars, (separator-chars+1));
                if (0 < (p_webrtcTraceFileDir.length()))
                {
                    webrtcTraceFileName.append(p_webrtcTraceFileDir);
                    if ((dirSeparatorChar))
                        webrtcTraceFileName.append(separator, 1);
                }
                webrtcTraceFileName.append(p_webrtcTraceFileName);
            }
        }
        return webrtcTraceFileName;
    }
    virtual std::string GetThisModuleFileName() const
    {
        std::string moduleFileName;
        return moduleFileName;
    }

    ///////////////////////////////////////////////////////////////////////
    // window peer
    ///////////////////////////////////////////////////////////////////////
    virtual WindowPeer* AttachWindowPeer
    (WindowPeer* detached)
    {
        WindowPeer* attached = 0;
        attached = (m_attachedWindowPeer = detached);
        return attached;
    }
    virtual WindowPeer* DetachWindowPeer()
    {
        WindowPeer* detached = 0;
        detached = (m_attachedWindowPeer);
        m_attachedWindowPeer = 0;
        return detached;
    }
    virtual WindowPeer* AttachedWindowPeer() const
    {
        WindowPeer* attached = 0;
        attached = (m_attachedWindowPeer);
        return attached;
    }

protected:
    template <typename T>
    class AutoLock {
     public:
        explicit AutoLock(T* obj) : obj_(obj) { obj_->Lock(); }
        ~AutoLock() { obj_->Unlock(); }
     protected:
          T* obj_;
    };
    class _EXPORT_CLASS OpenGLVideoRenderer;

protected:
    bool m_showConnectionState;
    bool m_handleButtonEvents;
    bool m_postButtonEventUIMessages;
    std::string m_peerMessageHeader;
    std::string m_serverName;
    int m_serverPort;
    std::string m_peerName;
    int m_peerId;
    std::string m_connectToPeerName;
    int m_connectToPeerId;
    bool m_autoConnectToPeer;
    bool m_autoConnectToPeerOn;
    bool m_autoConnectToPeerAfter;
    bool m_autoConnectToPeerAfterOn;
    bool m_useOpenGLRendererOff;
    bool m_useOpenGLRenderer;
    PeerList m_peerList;
    bool m_useCallbackInAPI;
    bool m_useUIMessageQueue;

    talk_base::scoped_ptr<VideoRenderer> remote_video_;
    talk_base::scoped_ptr<VideoRenderer> local_video_;
    UI ui_;
    UIMessage::ThreadId ui_thread_id_;
    UIMessage::Queue ui_message_queue_;
    ConductorInterface* callback_;
    OpenGL::VideoRenderer* gl_renderer_;
    Token token_;

    std::string m_connectToServerStateName;
    std::string m_listPeersStateName;
    std::string m_streamingStateName;

    std::string m_ConnectToServerBefore;
    std::string m_ConnectToServerAfter;
    std::string m_ConnectToPeerBefore;
    std::string m_ConnectToPeerAfter;
    std::string m_Connecting;
    std::string m_NoVideoStreams;
    std::string m_NoIncomingVideoStream;

    WindowPeer* m_attachedWindowPeer;
    ImageObserverInterface* m_imageObserver;
    ImageInterface* m_imageDelegated;
    UserInterfaceStateObserver* m_stateObserver;
};

} // namespace client 
} // namespace peerconnection 
} // namespace webrtc 
} // namespace xos 

#endif // _XOS_WEBRTC_PEERCONNECTION_CLIENT_MAINWINDOW_HPP 
