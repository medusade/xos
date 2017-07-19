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
///   File: EventInterface.hpp
///
/// Author: $author$
///   Date: 2/24/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_WEBRTC_CLIENT_EVENTINTERFACE_HPP
#define _XOS_WEBRTC_CLIENT_EVENTINTERFACE_HPP

#include "xos/base/String.hpp"
#include "xos/base/Base.hpp"

namespace xos {
namespace webrtc {
namespace client {

typedef InterfaceBase EventObserverInterfaceImplement;
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS EventObserverInterface
: virtual public EventObserverInterfaceImplement {
public:
    typedef EventObserverInterfaceImplement Implements;

    ///////////////////////////////////////////////////////////////////////
    // Change State
    ///////////////////////////////////////////////////////////////////////
    virtual void OnChangeStateToConnectToServer() { 
        EventObserverInterface* delegated;
        if ((delegated = EventObserverInterfaceDelegated()))
            delegated->OnChangeStateToConnectToServer();
        else
        OnChangeState("ConnectToServer"); 
    }
    virtual void OnChangeStateToListPeers() { 
        EventObserverInterface* delegated;
        if ((delegated = EventObserverInterfaceDelegated()))
            delegated->OnChangeStateToListPeers();
        else
        OnChangeState("ListPeers"); 
    }
    virtual void OnChangeStateToStreaming() { 
        EventObserverInterface* delegated;
        if ((delegated = EventObserverInterfaceDelegated()))
            delegated->OnChangeStateToStreaming();
        else
        OnChangeState("Streaming"); 
    }
    virtual void OnChangeState(const std::string& toStateName) { 
        EventObserverInterface* delegated;
        if ((delegated = EventObserverInterfaceDelegated()))
            delegated->OnChangeState(toStateName);
        else {
        std::string eventName = "ChangeState to ";
        eventName += toStateName;
        OnEvent(eventName); 
        }
    }
    ///////////////////////////////////////////////////////////////////////
    // Server Connection
    ///////////////////////////////////////////////////////////////////////
    virtual void OnFailedToConnectToServer(const std::string& server) {
        EventObserverInterface* delegated;
        if ((delegated = EventObserverInterfaceDelegated()))
            delegated->OnFailedToConnectToServer(server);
        else
        OnEvent("FailedToConnectToServer"); 
    }
    virtual void OnConnectedToServer(int id, const std::string& name) {
        EventObserverInterface* delegated;
        if ((delegated = EventObserverInterfaceDelegated()))
            delegated->OnConnectedToServer(id, name);
        else
        OnEvent("ConnectedToServer"); 
    }
    virtual void OnDisconnectedFromServer() {
        EventObserverInterface* delegated;
        if ((delegated = EventObserverInterfaceDelegated()))
            delegated->OnDisconnectedFromServer();
        else
        OnEvent("DisconnectedFromServer"); 
    }
    ///////////////////////////////////////////////////////////////////////
    // Peer Connection
    ///////////////////////////////////////////////////////////////////////
    virtual void OnPeerConnectedToServer(int id, const std::string& name) {
        EventObserverInterface* delegated;
        if ((delegated = EventObserverInterfaceDelegated()))
            delegated->OnPeerConnectedToServer(id, name);
        else
        OnEvent("PeerConnectedToServer"); 
    }
    virtual void OnPeerDisconnectedFromServer(int id) {
        EventObserverInterface* delegated;
        if ((delegated = EventObserverInterfaceDelegated()))
            delegated->OnPeerDisconnectedFromServer(id);
        else
        OnEvent("PeerDisconnectedFromServer"); 
    }
    virtual void OnDisconnectedFromPeer(int id) {
        EventObserverInterface* delegated;
        if ((delegated = EventObserverInterfaceDelegated()))
            delegated->OnDisconnectedFromPeer(id);
        else
        OnEvent("DisconnectedFromPeer"); 
    }
    ///////////////////////////////////////////////////////////////////////
    // Event
    ///////////////////////////////////////////////////////////////////////
    virtual void OnEvent(const std::string& eventName) {
        EventObserverInterface* delegated;
        if ((delegated = EventObserverInterfaceDelegated()))
            delegated->OnEvent(eventName);
    }
    virtual void OnPeerListItem(const std::string& peerName, int peerId) {
        EventObserverInterface* delegated;
        if ((delegated = EventObserverInterfaceDelegated()))
            delegated->OnPeerListItem(peerName, peerId);
    }
    ///////////////////////////////////////////////////////////////////////
    // delegated
    ///////////////////////////////////////////////////////////////////////
    virtual EventObserverInterface* EventObserverInterfaceDelegated() const {
        return 0;
    }
};

typedef InterfaceBase EventInterfaceImplement;
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS EventInterface
: virtual public EventInterfaceImplement {
public:
    typedef EventInterfaceImplement Implements;

    ///////////////////////////////////////////////////////////////////////
    // Button Events
    ///////////////////////////////////////////////////////////////////////
    virtual void OnLButtonUp() {
        EventInterface* delegated;
        if ((delegated = EventInterfaceDelegated()))
            delegated->OnLButtonUp();
    }
    virtual void OnRButtonUp() {
        EventInterface* delegated;
        if ((delegated = EventInterfaceDelegated()))
            delegated->OnRButtonUp();
    }
    ///////////////////////////////////////////////////////////////////////
    // Register/Unregister Observer
    ///////////////////////////////////////////////////////////////////////
    virtual void RegisterEventObserver
    (EventObserverInterface* observer) {
        EventInterface* delegated;
        if ((delegated = EventInterfaceDelegated()))
            delegated->RegisterEventObserver(observer);
    }
    virtual void UnregisterEventObserver
    (EventObserverInterface* observer) {
        EventInterface* delegated;
        if ((delegated = EventInterfaceDelegated()))
            delegated->UnregisterEventObserver(observer);
    }
    ///////////////////////////////////////////////////////////////////////
    // delegated
    ///////////////////////////////////////////////////////////////////////
    virtual EventInterface* EventInterfaceDelegated() const {
        return 0;
    }
};

} // namespace client 
} // namespace webrtc 
} // namespace xos 

#endif // _XOS_WEBRTC_CLIENT_EVENTINTERFACE_HPP 
