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
///   Date: 1/17/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_WEBRTC_PEERCONNECTION_CLIENT_FIREBREATH_PLUGINWINDOW_HPP
#define _XOS_WEBRTC_PEERCONNECTION_CLIENT_FIREBREATH_PLUGINWINDOW_HPP

#include "xos/webrtc/peerconnection/client/MainWindow.hpp"
#include "xos/webrtc/peerconnection/client/VideoCodec.hpp"
#include "xos/webrtc/peerconnection/client/firebreath/PluginJavaScriptAPI.hpp"

namespace xos {
namespace webrtc {
namespace peerconnection {
namespace client {
namespace firebreath {

#undef CDB_CLASS
#define CDB_CLASS "PluginWindow"
///////////////////////////////////////////////////////////////////////
///  Class: PluginWindow
///
/// Author: $author$
///   Date: 1/17/2013
///////////////////////////////////////////////////////////////////////
template 
<class TExtend = client::MainWindow>

class _EXPORT_CLASS PluginWindow: virtual public PluginJavaScriptAPI, public TExtend {
public:
    typedef PluginJavaScriptAPI Implements;
    typedef TExtend Extends;
    typedef Implements::EventsInterface EventsInterface;
    typedef std::map<int, std::string> Peers;

    PluginWindow
    (const char* serverName, int serverPort,
     bool autoConnectToPeerOn=XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOW_DEFAULT_AUTO_CONNECT_TO_PEER_ON, 
     bool autoConnectToPeerAfterOn=XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOW_DEFAULT_AUTO_CONNECT_TO_PEER_AFTER_ON,
     bool showConnectionState=XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOW_DEFAULT_SHOW_CONNECTION_STATE,
     bool handleButtonEvents=XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOW_DEFAULT_HANDLE_BUTTON_EVENTS,
     bool postButtonEventUIMessages=XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOW_DEFAULT_POST_BUTTON_EVENT_UI_MESSAGES,
     bool useUIMessageQueue=XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOW_DEFAULT_USE_UI_MESSAGE_QUEUE,
     bool useOpenGLRenderer=XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOW_DEFAULT_USE_OPENGL_RENDERER)
    : Extends
      (serverName, serverPort, 
       autoConnectToPeerOn, autoConnectToPeerAfterOn, 
       showConnectionState, handleButtonEvents, postButtonEventUIMessages,
       useUIMessageQueue, useOpenGLRenderer),
      m_jsapiEvents(0) {
    }
    virtual ~PluginWindow() {
    }

    ////////////////////////////////////////////////////////////////////////
    // sign in/out
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
    virtual bool OnDisconnected() {
        std::string eventData;
        if ((CTHIS m_jsapiEvents))
            CTHIS m_jsapiEvents->onSignedOut(eventData);
        return false;
    }

    ////////////////////////////////////////////////////////////////////////
    // call/hangup
    ////////////////////////////////////////////////////////////////////////
    virtual void Call(const std::string& peerName) {
        CTHIS ConnectToPeer(peerName);
    }
    virtual void Hangup(const std::string& peerName) {
        CTHIS DisconnectFromPeer();
    }
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
    // streams
    ////////////////////////////////////////////////////////////////////////
    virtual bool OnAddStream
    (const std::string& stream_id, bool video) {
        int codecWidth = 0;
        int codecHeight = 0;
        int frameRate = 0;
        int minBitrate = 0;
        String eventData;
        if ((video))
        {
            eventData << XOS_WEBRTC_PEERCONNECTION_CLIENT_DEFAULT_VIDEO_CODEC_MODE_WIDTH;
            eventData << ":";
            eventData << XOS_WEBRTC_PEERCONNECTION_CLIENT_DEFAULT_VIDEO_CODEC_MODE_HEIGHT;

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
    // video codec mode
    ////////////////////////////////////////////////////////////////////////
    virtual std::string get_videoCodecMode() { 
        std::string val = CTHIS GetVideoCodecModeName();
        return val; 
    }
    virtual void set_videoCodecMode(const std::string& val) { 
        CTHIS SetVideoCodecModeName(val); 
    }

    ////////////////////////////////////////////////////////////////////////
    // jsapi event delegation
    ////////////////////////////////////////////////////////////////////////
    virtual Implements* Delegate(EventsInterface* events=0) { 
        CTHIS m_jsapiEvents = events;
        return ((Implements*)(this)); 
    }

protected:
    EventsInterface* m_jsapiEvents;
    Peers m_peers;
};
#undef CDB_CLASS

} // namespace firebreath 
} // namespace client 
} // namespace peerconnection 
} // namespace webrtc 
} // namespace xos 

#endif // _XOS_WEBRTC_PEERCONNECTION_CLIENT_FIREBREATH_PLUGINWINDOW_HPP 
