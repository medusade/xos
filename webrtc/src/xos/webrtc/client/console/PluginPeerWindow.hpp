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
///   File: PluginPeerWindow.hpp
///
/// Author: $author$
///   Date: 2/25/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_WEBRTC_CLIENT_CONSOLE_PLUGINPEERWINDOW_HPP
#define _XOS_WEBRTC_CLIENT_CONSOLE_PLUGINPEERWINDOW_HPP

#include "xos/webrtc/client/console/PeerWindow.hpp"
#include "xos/webrtc/client/firebreath/PluginWindow.hpp"
#include "xos/webrtc/client/ImageInterface.hpp"
#include "xos/webrtc/client/EventInterface.hpp"

namespace xos {
namespace webrtc {
namespace client {
namespace console {

typedef PeerWindowImplement PluginPeerWindowImplementImplement;
typedef ImageInterface PluginPeerWindowImageImplement;
typedef EventInterface PluginPeerWindowEventImplement;
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS PluginPeerWindowImplement
: virtual public PluginPeerWindowImplementImplement,
  virtual public PluginPeerWindowImageImplement,
  virtual public PluginPeerWindowEventImplement
{
public:
    typedef PluginPeerWindowImplementImplement Implements;
    typedef PluginPeerWindowImageImplement ImageImplements;
    typedef PluginPeerWindowEventImplement EventImplements;
};

typedef firebreath::PluginInterface PluginInterface;
typedef firebreath::PluginWindowT<PeerWindow> PluginPeerWindowExtend;
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS PluginPeerWindow
: virtual public PluginPeerWindowImplement,
  public PluginPeerWindowExtend
{
public:
    typedef PluginPeerWindowImplement Implements;
    typedef PluginPeerWindowExtend Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    PluginPeerWindow
    (PluginInterface& plugin,
     const char* serverName=0, int serverPort=0,
     bool showConnectionState = XOS_WEBRTC_CLIENT_WINDOW_DEFAULT_SHOW_CONNECTION_STATE,
     bool handleButtonEvents = XOS_WEBRTC_CLIENT_WINDOW_DEFAULT_HANDLE_BUTTON_EVENTS,
     bool autoConnectToPeerOn = true, bool autoConnectToPeerAfterOn = true)
    : Extends(plugin, serverName, serverPort, showConnectionState, handleButtonEvents),
      m_imageObserver(0),
      m_eventObserver(0),
      m_localVideo(0),
      m_remoteVideo(0)
    {
        m_autoConnectToPeerOn = autoConnectToPeerOn;
        m_autoConnectToPeerAfterOn = autoConnectToPeerAfterOn;
        m_localRendererLock.Create();
        m_remoteRendererLock.Create();
    }
    virtual ~PluginPeerWindow() {
        m_remoteRendererLock.Destroy();
        m_localRendererLock.Destroy();
    }

    ///////////////////////////////////////////////////////////////////////
    // Event Observer
    ///////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////
    // Change State
    ////////////////////////////////////////////////////////////////////////
    virtual void OnChangeStateToConnectToServer() { 
        if ((m_eventObserver))
            m_eventObserver->OnChangeStateToConnectToServer();
        else
        Extends::OnChangeStateToConnectToServer();
    }
    virtual void OnChangeStateToListPeers() {
        if ((m_eventObserver))
            m_eventObserver->OnChangeStateToListPeers();
        else
        Extends::OnChangeStateToListPeers();
    }
    virtual void OnChangeStateToStreaming() { 
        if ((m_eventObserver))
            m_eventObserver->OnChangeStateToStreaming();
        else
        Extends::OnChangeStateToStreaming();
    }
    virtual void OnChangeState(const std::string& toStateName) { 
        if ((m_eventObserver))
            m_eventObserver->OnChangeState(toStateName);
        else
        Extends::OnChangeState(toStateName);
    }
    virtual void OnPeerListItem(const std::string& peerName, int peerId) {
        if ((m_eventObserver))
            m_eventObserver->OnPeerListItem(peerName, peerId);
        else
        Extends::OnPeerListItem(peerName, peerId);
    }
    ////////////////////////////////////////////////////////////////////////
    // Server
    ////////////////////////////////////////////////////////////////////////
    virtual void OnFailedToConnectToServer(const std::string& server) {
        if ((m_eventObserver))
            m_eventObserver->OnFailedToConnectToServer(server);
        else
        Extends::OnFailedToConnectToServer(server);
    }
    ////////////////////////////////////////////////////////////////////////
    // Peer
    ////////////////////////////////////////////////////////////////////////
    virtual bool OnPeerConnected(int id, const std::string& name) {
        if ((m_eventObserver)) {
            m_eventObserver->OnPeerConnectedToServer(id, name);
            return false;
        }
        return Extends::OnPeerConnected(id, name);
    }
    virtual bool OnPeerDisconnected(int id) {
        if ((m_eventObserver)) {
            m_eventObserver->OnPeerDisconnectedFromServer(id);
            return false;
        }
        return Extends::OnPeerDisconnected(id);
    }
    ///////////////////////////////////////////////////////////////////////
    // Event Interface
    ///////////////////////////////////////////////////////////////////////
    virtual void OnLButtonUp() {
        Extends::OnLButtonUp();
    }
    virtual void OnRButtonUp() {
        Extends::OnRButtonUp();
    }
    virtual void RegisterEventObserver(EventObserverInterface* observer) {
        if ((observer))
            m_eventObserver = observer;
    }
    virtual void UnregisterEventObserver(EventObserverInterface* observer) {
        if ((observer == m_eventObserver))
            m_eventObserver = 0;
    }

    ///////////////////////////////////////////////////////////////////////
    // Image Observer
    ///////////////////////////////////////////////////////////////////////
    virtual bool InvalidateWindow(bool eraseBackground = true) { 
        if ((m_imageObserver))
            m_imageObserver->InvalidateWindow(eraseBackground);
        return true; 
    }
    virtual bool ValidateWindow() { 
        if ((m_imageObserver))
            m_imageObserver->ValidateWindow();
        return true; 
    }
    ///////////////////////////////////////////////////////////////////////
    // Image Interface
    ///////////////////////////////////////////////////////////////////////
    virtual void RegisterImageObserver
    (ImageObserverInterface* imageObserver) {
        if ((imageObserver))
            m_imageObserver = imageObserver;
    }
    virtual void UnregisterImageObserver
    (ImageObserverInterface* imageObserver) {
        if (imageObserver == m_imageObserver)
            m_imageObserver = 0;
    }

    virtual uint8_t* AcquireRemoteImage
    (int& width, int& height, Format& format) {
        uint8_t* image = 0;
        client::VideoRenderer* video;

        if ((LockRemoteRenderer())) {
            if ((video = remote_video_.get())) {
                video->Lock();
                if (!(image = video->d_image())) {
                    video->Unlock();
                    UnlockRemoteRenderer();
                } else {
                    m_remoteVideo = video;
                    width = video->image_width();
                    height = video->image_height();
                    format = RenderImageFormat(video->RenderImageFormat());
                }
            } else {
                UnlockRemoteRenderer();
            }
        }
        return image;
    }
    virtual bool ReleaseRemoteImage(uint8_t* image) {
        bool success = false;
        client::VideoRenderer* video;

        if ((video = m_remoteVideo)) {
            if (!(image != video->d_image())) {
                video->Unlock();
                m_remoteVideo = 0;
                UnlockRemoteRenderer();
                success = true;
            }
        }
        return success;
    }

    virtual uint8_t* AcquireLocalImage
    (int& width, int& height, Format& format) {
        uint8_t* image = 0;
        client::VideoRenderer* video;

        if ((LockLocalRenderer())) {
            if ((video = local_video_.get())) {
                video->Lock();
                if (!(image = video->d_image())) {
                    video->Unlock();
                    UnlockLocalRenderer();
                } else {
                    m_localVideo = video;
                    width = video->image_width();
                    height = video->image_height();
                    format = (video->RenderImageFormat());
                }
            } else {
                UnlockLocalRenderer();
            }
        }
        return image;
    }
    virtual bool ReleaseLocalImage(uint8_t* image) {
        bool success = false;
        client::VideoRenderer* video;

        if ((video = m_localVideo)) {
            if (!(image != video->d_image())) {
                video->Unlock();
                m_localVideo = 0;
                UnlockLocalRenderer();
                success = true;
            }
        }
        return success;
    }

    virtual Format RenderImageFormat(cricket::FourCC fourCC) const {
        Format format = FORMAT_NONE;
        switch(fourCC) {
        case cricket::FOURCC_ARGB:
            format = FORMAT_GL_BGRA;
            break;
        }
        return format;
    }

    virtual bool LockLocalRenderer() { 
        return m_localRendererLock.Lock();
    }
    virtual bool UnlockLocalRenderer() { 
        return m_localRendererLock.Unlock(); 
    }

    virtual bool LockRemoteRenderer() {
        return m_remoteRendererLock.Lock();
    }
    virtual bool UnlockRemoteRenderer() { 
        return m_remoteRendererLock.Unlock(); 
    }

protected:
    ImageObserverInterface* m_imageObserver;
    EventObserverInterface* m_eventObserver;
    client::VideoRenderer* m_localVideo;
    client::VideoRenderer* m_remoteVideo;
    xos::os::Mutex m_localRendererLock;
    xos::os::Mutex m_remoteRendererLock;
};

} // namespace console 
} // namespace client 
} // namespace webrtc 
} // namespace xos 

#endif // _XOS_WEBRTC_CLIENT_CONSOLE_PLUGINPEERWINDOW_HPP 
