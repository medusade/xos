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
///   File: Plugin.hpp
///
/// Author: $author$
///   Date: 8/4/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_APP_WEBRTC_CLIENT_WEBRTC_GEN1125_PLUGIN_HPP
#define _XOS_APP_WEBRTC_CLIENT_WEBRTC_GEN1125_PLUGIN_HPP

#include "app/webrtc/client/PluginInterface.hpp"
#include "xos/webrtc/client/PluginInterface.hpp"
#include <vector>

#define XOS_WEBRTC_CLIENT_DEFAULT_SERVER_NAME "localhost"
#define XOS_WEBRTC_CLIENT_DEFAULT_SERVER_PORT 8888

namespace xos {
namespace webrtc {
namespace client {
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS PluginInterface::Window
: virtual public xos::app::webrtc::client::PluginInterface,
  public ExportBase {
public:
    typedef xos::app::webrtc::client::PluginInterface Implements;
    typedef ExportBase Extends;
};
} // namespace client 
} // namespace webrtc 
} // namespace xos 

namespace xos {
namespace app {
namespace webrtc {
namespace client {
namespace webrtc {
namespace gen1125 {

typedef PluginInterface PluginImplementImplement;
///////////////////////////////////////////////////////////////////////
///  Class: PluginImplement
///////////////////////////////////////////////////////////////////////
class c_EXPORT_CLASS PluginImplement
: virtual public PluginImplementImplement,
  virtual public xos::webrtc::client::ImageObserverInterface,
  virtual public xos::webrtc::client::EventObserverInterface {
public:
    typedef PluginImplementImplement Implements;
};
typedef xos::webrtc::client::PluginInterface::Window PluginExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Plugin
///
/// Author: $author$
///   Date: 8/4/2013
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Plugin
: virtual public PluginImplement, public PluginExtend {
public:
    typedef PluginImplement Implements;
    typedef PluginExtend Extends;
    typedef xos::app::webrtc::client::ImageObserverInterface ImageObserverInterface;
    typedef xos::app::webrtc::client::EventObserverInterface EventObserverInterface;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: Plugin
    ///////////////////////////////////////////////////////////////////////
    Plugin()
    : m_imageObserver(0), 
      m_eventObserver(0), 
      m_plugin(0),
      m_serverName(XOS_WEBRTC_CLIENT_DEFAULT_SERVER_NAME),
      m_serverPort(XOS_WEBRTC_CLIENT_DEFAULT_SERVER_PORT) {
    }
    virtual ~Plugin() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Init() {
        if ((LoadPlugin())) {
            m_loadedPlugin->SetAutoConnectToPeerOn(m_autoConnectToPeerOn);
            m_loadedPlugin->SetServerName(m_serverName);
            m_loadedPlugin->SetServerPort(m_serverPort);
            m_loadedPlugin->RegisterImageObserver(this);
            m_loadedPlugin->RegisterEventObserver(this);
            return true;
        }
        return false;
    }
    virtual bool Finish() {
        bool success = false;
        if ((m_loadedPlugin)) {
            m_loadedPlugin->UnregisterEventObserver(this);
            m_loadedPlugin->UnregisterImageObserver(this);
            if ((UnloadPlugin()))
                success = true;
        }
        return success;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool AttachUserInterface(UserInterface* userInterface = 0) {
        if ((m_loadedPlugin) && (!m_plugin)) {
            if ((m_loadedPlugin->AttachWindow(this))) {
                m_plugin = m_loadedPlugin;
                return true;
            }
        }
        return false;
    }
    virtual bool DetachUserInterface(UserInterface* userInterface = 0) {
        bool success = false;
        if ((m_plugin)) {
            success = m_plugin->DetachWindow(this);
            m_plugin = 0;
        }
        return success;
    }

    ///////////////////////////////////////////////////////////////////////
    // Register/Unregister ImageObserver
    ///////////////////////////////////////////////////////////////////////
    virtual void RegisterImageObserver(ImageObserverInterface* observer) {
        ImageInterface* imageInterface;
        if ((imageInterface = ImageInterfaceDelegated()))
            imageInterface->RegisterImageObserver(observer);
        else {
            m_imageObserver = observer;
        }
    }
    virtual void UnregisterImageObserver(ImageObserverInterface* observer) {
        ImageInterface* imageInterface;
        if ((imageInterface = ImageInterfaceDelegated()))
            imageInterface->UnregisterImageObserver(observer);
        else if ((observer) && (m_imageObserver == observer)) {
            m_imageObserver = 0;
        }
    }

    ///////////////////////////////////////////////////////////////////////
    // Register/Unregister EventObserver
    ///////////////////////////////////////////////////////////////////////
    virtual void RegisterEventObserver
    (EventObserverInterface* observer) {
        EventInterface* delegated;
        if ((delegated = EventInterfaceDelegated()))
            delegated->RegisterEventObserver(observer);
        else {
            m_eventObserver = observer;
        }
    }
    virtual void UnregisterEventObserver
    (EventObserverInterface* observer) {
        EventInterface* delegated;
        if ((delegated = EventInterfaceDelegated()))
            delegated->UnregisterEventObserver(observer);
        else if ((observer) && (m_eventObserver == observer)) {
            m_eventObserver = 0;
        }
    }

    ///////////////////////////////////////////////////////////////////////
    // button events
    ///////////////////////////////////////////////////////////////////////
    virtual void OnLButtonUp() {
        if ((m_plugin))
            m_plugin->OnLButtonUp();
    }
    virtual void OnRButtonUp() {
        if ((m_plugin))
            m_plugin->OnRButtonUp();
    }

    ///////////////////////////////////////////////////////////////////////
    // connection to server
    ///////////////////////////////////////////////////////////////////////
    virtual bool ConnectToServer(const std::string& serverName, int serverPort) {
        if ((m_plugin) && (0 < (serverName.length())) && (0 < (serverPort))) {
            return m_plugin->ConnectToServer(serverName, serverPort);
        }
        return false;
    }
    virtual bool ConnectToServer(const std::string& serverName) {
        if ((m_plugin) && (0 < (serverName.length()))) {
            return m_plugin->ConnectToServer();
        }
        return false;
    }
    virtual bool ConnectToServer() {
        if ((m_plugin))
            return m_plugin->ConnectToServer();
        return false;
    }
    virtual bool DisconnectFromServer() { 
        if ((m_plugin))
            return m_plugin->DisconnectFromServer();
        return false; 
    }

    ///////////////////////////////////////////////////////////////////////
    // connection to peer
    ///////////////////////////////////////////////////////////////////////
    virtual bool ConnectToPeer(const std::string& peerName) {
        if ((m_plugin))
            return m_plugin->ConnectToPeer(peerName);
        return false;
    }
    virtual bool ConnectToPeer(int peerId) {
        if ((m_plugin))
            return m_plugin->ConnectToPeer(peerId);
        return false;
    }
    virtual bool ConnectToPeer() {
        if ((m_plugin))
            return m_plugin->ConnectToPeer();
        return false;
    }
    virtual bool DisconnectFromPeer() { 
        if ((m_plugin))
            return m_plugin->DisconnectFromPeer();
        return false; 
    }
    virtual void SetAutoConnectToPeerOn(bool isTrue=true) {
        if ((m_plugin))
            m_plugin->SetAutoConnectToPeerOn(isTrue);
    }
    virtual bool GetAutoConnectToPeerOn() const {
        if ((m_plugin))
            return m_plugin->GetAutoConnectToPeerOn();
        return false; 
    }
    virtual void SetAutoConnectToPeerAfterOn(bool isTrue=true) {
        if ((m_plugin))
            m_plugin->SetAutoConnectToPeerAfterOn(isTrue);
    }
    virtual bool GetAutoConnectToPeerAfterOn() const {
        if ((m_plugin))
            return m_plugin->GetAutoConnectToPeerAfterOn();
        return false; 
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void* AcquireRemoteImage(int& width, int& height, Format& format) {
        void* image = 0;
        xos::webrtc::client::ImageInterface::Format iFormat;
        if ((m_plugin))
        if ((image = m_plugin->AcquireRemoteImage(width, height, iFormat)))
            format = FORMAT_GL_BGRA;
        return image;
    }
    virtual bool ReleaseRemoteImage(void* image) {
        bool success = false;
        if ((m_plugin))
            success = m_plugin->ReleaseRemoteImage((uint8_t*)(image));
        return success;
    }
    virtual void* AcquireLocalImage(int& width, int& height, Format& format) {
        void* image = 0;
        xos::webrtc::client::ImageInterface::Format iFormat;
        if ((m_plugin))
        if ((image = m_plugin->AcquireLocalImage(width, height, iFormat)))
            format = FORMAT_GL_BGRA;
        return image;
    }
    virtual bool ReleaseLocalImage(void* image) {
        bool success = false;
        if ((m_plugin))
            success = m_plugin->ReleaseLocalImage((uint8_t*)(image));
        return success;
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    // Image Observer
    ///////////////////////////////////////////////////////////////////////
    virtual bool InvalidateWindow(bool eraseBackground = true) { 
        if ((m_imageObserver))
            m_imageObserver->UpdatedImages();
        return true; 
    }

    ///////////////////////////////////////////////////////////////////////
    // Event Observer
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    // Change State
    ///////////////////////////////////////////////////////////////////////
    virtual void OnChangeStateToConnectToServer() { 
        m_peerList.clear();
        if ((m_eventObserver))
            m_eventObserver->OnChangeStateToConnectToServer();
    }
    virtual void OnChangeStateToListPeers() { 
        if ((m_eventObserver)) {
            m_eventObserver->OnChangeStateToListPeers();
            if (0 < (m_peerList.size())) {
                PeerList::const_iterator i;
                for (i = m_peerList.begin(); i != m_peerList.end(); ++i) {
                    if ((0 < i->m_name.length()) && (0 < i->m_id)) {
                        m_eventObserver->OnPeerConnectedToServer(i->m_id, i->m_name);
                    }
                }
            }
        }
        m_peerList.clear();
    }
    virtual void OnChangeStateToStreaming() {
        if ((m_eventObserver))
            m_eventObserver->OnChangeStateToStreaming();
    }
    ///////////////////////////////////////////////////////////////////////
    // Server Connection
    ///////////////////////////////////////////////////////////////////////
    virtual void OnFailedToConnectToServer(const std::string& server) {
        if ((m_eventObserver))
            m_eventObserver->OnFailedToConnectToServer(server);
    }
    virtual void OnConnectedToServer(int id, const std::string& name) {
        if ((m_eventObserver))
            m_eventObserver->OnConnectedToServer(id, name); 
    }
    virtual void OnDisconnectedFromServer() {
        if ((m_eventObserver))
            m_eventObserver->OnDisconnectedFromServer(); 
    }
    ///////////////////////////////////////////////////////////////////////
    // Peer Connection
    ///////////////////////////////////////////////////////////////////////
    virtual void OnPeerConnectedToServer(int id, const std::string& name) {
        if ((m_eventObserver))
            m_eventObserver->OnPeerConnectedToServer(id, name);
    }
    virtual void OnPeerListItem(const std::string& name, int id) {
        if ((0 < id) && (0 < name.length())) {
            PeerItem peerItem(name, id);
            m_peerList.push_back(peerItem);
        }
    }
    virtual void OnPeerDisconnectedFromServer(int id) {
        //if ((m_eventObserver))
        //    m_eventObserver->OnPeerDisconnectedFromServer(id); 
    }
    virtual void OnDisconnectedFromPeer(int id) {
        if ((m_eventObserver))
            m_eventObserver->OnDisconnectedFromPeer(id); 
    }
    ///////////////////////////////////////////////////////////////////////
    // Event
    ///////////////////////////////////////////////////////////////////////
    virtual void OnEvent(const std::string& eventName) {
        if ((m_eventObserver))
            m_eventObserver->OnEvent(eventName);
    }

    ///////////////////////////////////////////////////////////////////////
    // Load/Unload Plugin
    ///////////////////////////////////////////////////////////////////////
    virtual xos::webrtc::client::PluginInterface* LoadPlugin() {
        m_plugin = 0;
        m_loadedPlugin = xos::webrtc::client::PluginInterface::AcquireInstance();
        return m_loadedPlugin;
    }
    virtual bool UnloadPlugin() {
        bool isTrue = false;
        if ((m_loadedPlugin)) {
            isTrue = xos::webrtc::client::PluginInterface::ReleaseInstance(m_loadedPlugin);
            m_loadedPlugin = 0;
        }
        m_plugin = 0;
        return isTrue;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
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

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    ImageObserverInterface* m_imageObserver;
    EventObserverInterface* m_eventObserver;
    xos::webrtc::client::PluginInterface* m_plugin;
    xos::webrtc::client::PluginInterface* m_loadedPlugin;
    String m_serverName;
    int m_serverPort;
    bool m_autoConnectToPeerOn;
    PeerList m_peerList;
};

} // namespace gen1125 
} // namespace webrtc 
} // namespace client 
} // namespace webrtc 
} // namespace app 
} // namespace xos 

#endif // _XOS_APP_WEBRTC_CLIENT_WEBRTC_GEN1125_PLUGIN_HPP 
