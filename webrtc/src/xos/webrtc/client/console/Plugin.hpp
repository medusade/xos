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
///   Date: 2/26/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_WEBRTC_CLIENT_CONSOLE_PLUGIN_HPP
#define _XOS_WEBRTC_CLIENT_CONSOLE_PLUGIN_HPP

#include "xos/webrtc/client/console/PluginWindowPeer.hpp"
#include "xos/webrtc/client/console/PluginPeerWindow.hpp"
#include "xos/webrtc/client/Plugin.hpp"

namespace xos {
namespace webrtc {
namespace client {
namespace console {

typedef client::PluginImplement PluginImplement;
typedef client::Plugin PluginExtend;
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Plugin
: virtual public PluginImplement, public PluginExtend {
public:
    typedef PluginImplement Implements;
    typedef PluginExtend Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Plugin
    (const char* serverName=XOS_WEBRTC_CLIENT_WINDOW_DEFAULT_SERVER_NAME, 
     int serverPort=XOS_WEBRTC_CLIENT_WINDOW_DEFAULT_SERVER_PORT,
     bool showConnectionState = XOS_WEBRTC_CLIENT_WINDOW_DEFAULT_SHOW_CONNECTION_STATE,
     bool handleButtonEvents = XOS_WEBRTC_CLIENT_WINDOW_DEFAULT_HANDLE_BUTTON_EVENTS,
     bool autoConnectToPeerOn = true, bool autoConnectToPeerAfterOn = true)
    : m_peerWindow(*this, serverName, serverPort, showConnectionState, handleButtonEvents),
      m_windowPeer(m_peerWindow),
      m_window(0) {
    }
    virtual ~Plugin() {
    }

    ///////////////////////////////////////////////////////////////////////
    // Attach/Detach window
    ///////////////////////////////////////////////////////////////////////
    virtual bool AttachWindow(Window* window) {
        if (!(m_window) && (window)) {
            if ((m_windowPeer.Attach())) {
                m_window = window;
                return true;
            }
        }
        return false;
    }
    virtual bool DetachWindow(Window* window) {
        if ((m_window) && (m_window == window)) {
            m_window = 0;
            if ((m_windowPeer.Detach())) {
                return true;
            }
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    // connection to server
    ///////////////////////////////////////////////////////////////////////
    virtual bool ConnectToServer(const std::string& serverName, int serverPort) {
        return m_peerWindow.ConnectToServer(serverName, serverPort); 
    }
    virtual bool ConnectToServer() {
        return m_peerWindow.ConnectToServer(); 
    }
    virtual bool DisconnectFromServer() { 
        return m_peerWindow.DisconnectFromServer(); 
    }
    virtual void SetServerName(const std::string& serverName) { 
         m_peerWindow.SetServerName(serverName);
    }
    virtual void SetServerPort(int serverPort) {
         m_peerWindow.SetServerPort(serverPort);
    }

    ///////////////////////////////////////////////////////////////////////
    // connection to peer
    ///////////////////////////////////////////////////////////////////////
    virtual bool ConnectToPeer(const std::string& peerName) {
        return m_peerWindow.ConnectToPeer(peerName); 
    }
    virtual bool ConnectToPeer(int peerId) {
        return m_peerWindow.ConnectToPeer(peerId); 
    }
    virtual bool ConnectToPeer() {
        return m_peerWindow.ConnectToPeer(); 
    }
    virtual bool DisconnectFromPeer() { 
        return m_peerWindow.DisconnectFromPeer(); 
    }
    virtual void SetAutoConnectToPeerOn(bool isTrue=true) {
         m_peerWindow.SetAutoConnectToPeerOn(isTrue);
    }
    virtual bool GetAutoConnectToPeerOn() const {
        return  m_peerWindow.GetAutoConnectToPeerOn(); 
    }
    virtual void SetAutoConnectToPeerAfterOn(bool isTrue=true) {
         m_peerWindow.SetAutoConnectToPeerAfterOn(isTrue);
    }
    virtual bool GetAutoConnectToPeerAfterOn() const {
        return  m_peerWindow.GetAutoConnectToPeerAfterOn(); 
    }

    ///////////////////////////////////////////////////////////////////////
    // Image/Event Interface delegated
    ///////////////////////////////////////////////////////////////////////
    virtual ImageInterface* ImageInterfaceDelegated() const {
        return (ImageInterface*)(&m_peerWindow);
    }
    virtual EventInterface* EventInterfaceDelegated() const {
        return (EventInterface*)(&m_peerWindow);
    }

protected:
    PluginPeerWindow m_peerWindow;
    PluginWindowPeer m_windowPeer;
    Window* m_window;
};

} // namespace console 
} // namespace client 
} // namespace webrtc 
} // namespace xos 

#endif // _XOS_WEBRTC_CLIENT_CONSOLE_PLUGIN_HPP 
