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
///   File: UserInterface.hpp
///
/// Author: $author$
///   Date: 12/25/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_WEBRTC_PEERCONNECTION_CLIENT_USERINTERFACE_HPP
#define _XOS_WEBRTC_PEERCONNECTION_CLIENT_USERINTERFACE_HPP

#include "xos/webrtc/peerconnection/client/ConductorInterface.hpp"
#include "xos/webrtc/peerconnection/client/ConnectionInterface.hpp"
#include "talk/app/webrtc/mediastreaminterface.h"

namespace xos {
namespace webrtc {

typedef ::webrtc::VideoTrackInterface VideoTrackInterface;
typedef ::webrtc::VideoRendererInterface VideoRendererInterface;

namespace peerconnection {
namespace client {

///////////////////////////////////////////////////////////////////////
///  Class: UserInterfaceStateObserver
///
/// Author: $author$
///   Date: 1/16/2013
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS UserInterfaceStateObserver: virtual public InterfaceBase {
public:
    typedef InterfaceBase Implements;

    virtual void OnChangeStateToConnectToServer() = 0;
    virtual void OnChangeStateToListPeers() = 0;
    virtual void OnChangeStateToStreaming() = 0;
    virtual void OnChangeState(const std::string& toState) = 0;
};
///////////////////////////////////////////////////////////////////////
///  Class: UserInterfaceStateObserverImplement
///
/// Author: $author$
///   Date: 1/16/2013
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS UserInterfaceStateObserverImplement
: virtual public UserInterfaceStateObserver {
public:
    typedef UserInterfaceStateObserver Implements;

    virtual void OnChangeStateToConnectToServer() {}
    virtual void OnChangeStateToListPeers() {}
    virtual void OnChangeStateToStreaming() {}
    virtual void OnChangeState(const std::string& toState) {}
};

typedef UserInterfaceStateObserver UserInterfaceBase;
///////////////////////////////////////////////////////////////////////
///  Class: UserInterface
///
/// Author: $author$
///   Date: 12/25/2012
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS UserInterface: virtual public UserInterfaceBase {
public:
    typedef UserInterfaceBase Implements;
    typedef ConnectionInterface::Peers Peers;

    enum UI {
        CONNECT_TO_SERVER,
        LIST_PEERS,
        STREAMING,
    };

    virtual void RegisterObserver
    (ConductorInterface* callback) = 0;
    virtual void UnRegisterObserver() = 0;

    virtual bool IsWindow() = 0;
    virtual void MessageBox
    (const char* caption, const char* text, bool is_error) = 0;

    virtual UI current_ui() = 0;

    virtual void SwitchToConnectUI() = 0;
    virtual void SwitchToPeerList(const Peers& peers) = 0;
    virtual void SwitchToStreamingUI() = 0;

    virtual void StartLocalRenderer(webrtc::VideoTrackInterface* local_video) = 0;
    virtual void StopLocalRenderer() = 0;
    virtual void StartRemoteRenderer(webrtc::VideoTrackInterface* remote_video) = 0;
    virtual void StopRemoteRenderer() = 0;

    virtual webrtc::VideoRendererInterface* local_renderer() = 0;
    virtual webrtc::VideoRendererInterface* remote_renderer() = 0;

    virtual void QueueUIThreadCallback(int msg_id, void* data) = 0;

    virtual const std::string GetThisPeerName() = 0;
    virtual void SetThisPeerName(const std::string& peerName) = 0;

    virtual bool OnMessageFromPeer(int peer_id, const std::string& messageEnvelope) = 0;
    virtual void OnFailedToConnectToServer(const std::string& server) = 0;

    ///////////////////////////////////////////////////////////////////////
    // state observer
    ///////////////////////////////////////////////////////////////////////
    virtual bool RegisterStateObserver(UserInterfaceStateObserver* stateObserver) = 0;
    virtual bool UnregisterStateObserver(UserInterfaceStateObserver* stateObserver) = 0;
    virtual UserInterfaceStateObserver* StateObserver() const = 0;
    virtual void OnChangeStateToConnectToServer() = 0;
    virtual void OnChangeStateToListPeers() = 0;
    virtual void OnChangeStateToStreaming() = 0;
    virtual void OnChangeState(const std::string& toState) = 0;

    virtual void OnEvent(const std::string& eventName) = 0;

    virtual bool OnSignedIn(const Peers& peers) = 0;
    virtual bool OnDisconnected() = 0;

    virtual bool OnPeerConnected(int id, const std::string& name) = 0;
    virtual bool OnPeerDisconnected(int id) = 0;
    virtual bool OnPeerConnectionClosed(int id) = 0;

    virtual bool OnUnexpectedMessageFromPeer(int peer_id, const std::string& message) = 0;
    virtual bool OnUnknownMessageFromPeer(int peer_id, const std::string& message) = 0;
    virtual bool OnInvalidMessageFromPeer(int peer_id, const std::string& message) = 0;
    virtual bool OnEmptyMessageFromPeer(int peer_id, const std::string& message) = 0;

    virtual bool OnSignalingMessageFromPeer(int peer_id, const std::string& message) = 0;
    virtual bool OnSignalingMessageFromUnconnectedPeer(int peer_id, const std::string& message) = 0;
    virtual bool OnSignalingMessageToPeer(int peer_id, const std::string& message) = 0;

    virtual bool OnSendMessageToPeer(const std::string* message) = 0;
    virtual bool OnMessageSentToPeer(int err) = 0;

    virtual bool OnAddStream(const std::string& stream_id, bool video) = 0;
    virtual bool OnRemoveStream(const std::string& stream_id, bool video) = 0;

    virtual bool OnFailure(const std::string& error) = 0;
};
///////////////////////////////////////////////////////////////////////
///  Class: UserInterfaceImplement
///
/// Author: $author$
///   Date: 12/25/2012
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS UserInterfaceImplement: virtual public UserInterface {
public:
    typedef UserInterface Implements;

    virtual void RegisterObserver
    (ConductorInterface* callback) {}
    virtual void UnRegisterObserver() {}

    virtual bool IsWindow() { return false; }
    virtual void MessageBox
    (const char* caption, const char* text, bool is_error) {}

    virtual UI current_ui() = 0;

    virtual void SwitchToConnectUI() {}
    virtual void SwitchToPeerList(const Peers& peers) {}
    virtual void SwitchToStreamingUI() {}

    virtual void StartLocalRenderer(webrtc::VideoTrackInterface* local_video) {}
    virtual void StopLocalRenderer() {}
    virtual void StartRemoteRenderer(webrtc::VideoTrackInterface* remote_video) {}
    virtual void StopRemoteRenderer() {}

    virtual webrtc::VideoRendererInterface* local_renderer() { return 0; }
    virtual webrtc::VideoRendererInterface* remote_renderer() { return 0; }

    virtual void QueueUIThreadCallback(int msg_id, void* data) {}

    virtual const std::string GetThisPeerName() { std::string name; return name; }
    virtual void SetThisPeerName(const std::string& name) { }

    virtual bool OnMessageFromPeer
    (int peer_id, const std::string& messageEnvelope) { return false; }
    virtual void OnFailedToConnectToServer(const std::string& server) {}

    ///////////////////////////////////////////////////////////////////////
    // state observer
    ///////////////////////////////////////////////////////////////////////
    virtual bool RegisterStateObserver(UserInterfaceStateObserver* stateObserver) { return false; }
    virtual bool UnregisterStateObserver(UserInterfaceStateObserver* stateObserver) { return false; }
    virtual UserInterfaceStateObserver* StateObserver() const { return 0; }
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

    virtual void OnEvent(const std::string& eventName) {}

    virtual bool OnSignedIn(const Peers& peers) { OnEvent("SignedIn"); return false; }
    virtual bool OnDisconnected() { OnEvent("Disconnected"); return false; }

    virtual bool OnPeerConnected(int id, const std::string& name) { OnEvent("PeerConnected"); return false; }
    virtual bool OnPeerDisconnected(int id) { OnEvent("PeerDisconnected"); return false; }
    virtual bool OnPeerConnectionClosed(int id) { OnEvent("PeerConnectionClosed"); return false; }

    virtual bool OnUnexpectedMessageFromPeer
    (int peer_id, const std::string& message) { OnEvent("UnexpectedMessageFromPeer"); return false; }
    virtual bool OnUnknownMessageFromPeer
    (int peer_id, const std::string& message) { OnEvent("UnknownMessageFromPeer"); return false; }
    virtual bool OnInvalidMessageFromPeer
    (int peer_id, const std::string& message) { OnEvent("InvalidMessageFromPeer"); return false; }
    virtual bool OnEmptyMessageFromPeer
    (int peer_id, const std::string& message) { OnEvent("EmptyMessageFromPeer"); return false; }

    virtual bool OnSignalingMessageFromPeer
    (int peer_id, const std::string& message) { OnEvent("SignalingMessageFromPeer"); return false; }
    virtual bool OnSignalingMessageFromUnconnectedPeer
    (int peer_id, const std::string& message) { OnEvent("SignalingMessageFromUnconnectedPeer"); return false; }
    virtual bool OnSignalingMessageToPeer
    (int peer_id, const std::string& message) { OnEvent("SignalingMessage"); return false; }

    virtual bool OnSendMessageToPeer(const std::string* message) { OnEvent("SendMessageToPeer"); return false; }
    virtual bool OnMessageSentToPeer(int err) { OnEvent("MessageSentToPeer"); return false; }

    virtual bool OnAddStream(const std::string& stream_id, bool video) { OnEvent("AddStream"); return false; }
    virtual bool OnRemoveStream(const std::string& stream_id, bool video) { OnEvent("RemoveStream"); return false; }

    virtual bool OnFailure(const std::string& error) { OnEvent("Failure"); return false; }
};

} // namespace client 
} // namespace peerconnection 
} // namespace webrtc 
} // namespace xos 


#endif // _XOS_WEBRTC_PEERCONNECTION_CLIENT_USERINTERFACE_HPP 
        

