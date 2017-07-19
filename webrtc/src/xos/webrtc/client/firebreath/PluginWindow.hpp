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
///   File: PluginWindow.hpp
///
/// Author: $author$
///   Date: 2/25/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_WEBRTC_CLIENT_FIREBREATH_PLUGINWINDOW_HPP
#define _XOS_WEBRTC_CLIENT_FIREBREATH_PLUGINWINDOW_HPP

#include "xos/webrtc/client/firebreath/PluginInterface.hpp"
#include "xos/webrtc/client/firebreath/JavaScriptAPI.hpp"
#include "xos/webrtc/client/Window.hpp"

namespace xos {
namespace webrtc {
namespace client {
namespace firebreath {

typedef JavaScriptAPI PluginWindowImplement;

#undef CDB_CLASS
#define CDB_CLASS "PluginWindowT"

template <class TExtend>
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS PluginWindowT
: virtual public PluginWindowImplement,
  public TExtend
{
public:
    typedef PluginWindowImplement Implements;
    typedef TExtend Extends;
    typedef ConnectionInterface::Peers Peers;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    PluginWindowT
    (PluginInterface& plugin,
     const char* serverName, int serverPort,
     bool showConnectionState=XOS_WEBRTC_CLIENT_WINDOW_DEFAULT_SHOW_CONNECTION_STATE,
     bool handleButtonEvents=XOS_WEBRTC_CLIENT_WINDOW_DEFAULT_HANDLE_BUTTON_EVENTS)
    : Extends(serverName, serverPort, showConnectionState, handleButtonEvents),
      m_plugin(plugin), 
      m_jsapiEvents(0) {
    }
    virtual ~PluginWindowT() {
    }

    ////////////////////////////////////////////////////////////////////////
    // Signin
    ////////////////////////////////////////////////////////////////////////
    virtual void Signin
    (const std::string& userName, 
     const std::string& serverIP, int serverPort) {
        CTHIS SetThisPeerName(userName);
        CTHIS ConnectToServer(serverIP, serverPort);
    }
    virtual void Signout() {
        CTHIS DisconnectFromServer();
    }
    virtual void OnFailedToConnectToServer(const std::string& server) {
        if ((CTHIS m_jsapiEvents))
            CTHIS m_jsapiEvents->onFailedToConnectToServer(server);
    }
    virtual bool OnSignedIn(const Peers& peers) {
        Peers::const_iterator i;
        std::string eventData;
        std::string peerName;
        int peerId;

        for (i = peers.begin(); i != peers.end(); ++i)
        {
            peerName = i->second;
            peerId = i->first;
            if (0 < (peerName.length()))
            {
                eventData.append(peerName);
                eventData.append(":", 1);
            }
        }

        if ((CTHIS m_jsapiEvents))
            CTHIS m_jsapiEvents->onSignedIn(eventData);
        return false;
    }

    ////////////////////////////////////////////////////////////////////////
    // Call
    ////////////////////////////////////////////////////////////////////////
    virtual void Call(const std::string& peerName) {
        CTHIS ConnectToPeer(peerName);
    }
    virtual void Hangup(const std::string& peerName) {
        CTHIS DisconnectFromPeer();
    }

    ////////////////////////////////////////////////////////////////////////
    // Peer
    ////////////////////////////////////////////////////////////////////////
    virtual bool OnPeerConnected(int id, const std::string& name) {
        std::string eventData = name;
        CTHIS m_peers[id] = name;
        if ((CTHIS m_jsapiEvents))
            CTHIS m_jsapiEvents->onPeerOnline(eventData);
        return false;
    }
    virtual bool OnPeerDisconnected(int id) {
        std::string eventData = CTHIS m_peers[id];
        if ((CTHIS m_jsapiEvents))
            CTHIS m_jsapiEvents->onPeerOffline(eventData);
        CTHIS m_peers.erase(id);
        return false;
    }
    virtual bool OnSignalingMessageFromUnconnectedPeer
    (int peer_id, const std::string& message) {
        std::string eventData = CTHIS m_peers[peer_id];
        if ((0 > (CTHIS m_peerId)) && (0 < (eventData.length())))
        if ((CTHIS m_jsapiEvents))
            CTHIS m_jsapiEvents->onRemotePeerCall(eventData);
        return false;
    }
    virtual bool OnSignalingMessageToPeer
    (int peer_id, const std::string& message) {
        std::string eventData = CTHIS m_peerName;
        if ((0 < (CTHIS m_peerId)) && (peer_id == CTHIS m_peerId) && (0 < (eventData.length())))
        if ((CTHIS m_jsapiEvents))
            CTHIS m_jsapiEvents->onRemotePeerCall(eventData);
        return false;
    }
    virtual bool OnPeerConnectionClosed(int id) {
        std::string eventData = CTHIS m_peers[id];
        if ((CTHIS m_jsapiEvents))
            CTHIS m_jsapiEvents->onRemotePeerHangup(eventData);
        return false;
    }

    ////////////////////////////////////////////////////////////////////////
    // Stream
    ////////////////////////////////////////////////////////////////////////
    virtual bool OnAddStream
    (const std::string& stream_id, bool video) {
        int codecWidth = 0;
        int codecHeight = 0;
        int frameRate = 0;
        int minBitrate = 0;
        String eventData = "640:480";
        if ((video))
        {
            CTHIS GetVideoCodecOptions
            (codecWidth, codecHeight, frameRate, minBitrate);
            if ((0 < codecWidth) && (0 < codecHeight))
            {
                eventData.clear();
                eventData << codecWidth;
                eventData << ":";
                eventData << codecHeight;
            }
            if ((CTHIS m_jsapiEvents))
                CTHIS m_jsapiEvents->onRendererAdd(eventData);
        }
        return false;
    }
    virtual bool OnRemoveStream
    (const std::string& stream_id, bool video) {
        std::string eventData;
        if ((CTHIS m_jsapiEvents))
            CTHIS m_jsapiEvents->onRendererRemove(eventData);
        return false;
    }

    ////////////////////////////////////////////////////////////////////////
    // events
    ////////////////////////////////////////////////////////////////////////
    virtual void OnEvent(const std::string& eventName)  { 
        if ((CTHIS m_jsapiEvents))
            CTHIS m_jsapiEvents->onEvent(eventName);
    }

    ////////////////////////////////////////////////////////////////////////
    // videoCodecMode
    ////////////////////////////////////////////////////////////////////////
    virtual std::string get_videoCodecMode() { 
        std::string val = CTHIS GetVideoCodecModeName();
        return val; 
    }
    virtual void set_videoCodecMode(const std::string& val) { 
        CTHIS SetVideoCodecModeName(val); 
    }

    ////////////////////////////////////////////////////////////////////////
    // Delegate
    ////////////////////////////////////////////////////////////////////////
    virtual Implements* Delegate(EventsInterface* events=0) { 
        CTHIS m_jsapiEvents = events;
        return ((Implements*)(this)); 
    }

protected:
    PluginInterface& m_plugin;
    EventsInterface* m_jsapiEvents;
    Peers m_peers;
};
#undef CDB_CLASS

} // namespace firebreath 
} // namespace client 
} // namespace webrtc 
} // namespace xos 

#endif // _XOS_WEBRTC_CLIENT_FIREBREATH_PLUGINWINDOW_HPP 
