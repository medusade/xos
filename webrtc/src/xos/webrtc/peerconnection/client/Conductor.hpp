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
///   File: Conductor.hpp
///
/// Author: $author$
///   Date: 12/25/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_WEBRTC_PEERCONNECTION_CLIENT_CONDUCTOR_HPP
#define _XOS_WEBRTC_PEERCONNECTION_CLIENT_CONDUCTOR_HPP

#include "xos/webrtc/peerconnection/client/ConductorInterface.hpp"
#include "xos/webrtc/peerconnection/client/UserInterface.hpp"
#include "xos/webrtc/peerconnection/client/Connection.hpp"
#include "xos/base/Base.hpp"
#include "talk/app/webrtc/mediastreaminterface.h"
#include "talk/app/webrtc/peerconnectioninterface.h"
#include "talk/base/scoped_ptr.h"

namespace xos {
namespace webrtc {
namespace peerconnection {
namespace client {

typedef ::webrtc::MediaStreamInterface MediaStreamInterface;
typedef ::webrtc::IceCandidateInterface IceCandidateInterface;
typedef ::webrtc::SessionDescriptionInterface SessionDescriptionInterface;
typedef ::webrtc::PeerConnectionInterface PeerConnectionInterface;
typedef ::webrtc::PeerConnectionFactoryInterface PeerConnectionFactoryInterface;
typedef ::webrtc::PeerConnectionObserver PeerConnectionObserverInterface;
typedef ::webrtc::CreateSessionDescriptionObserver CreateSessionDescriptionObserver;

///////////////////////////////////////////////////////////////////////
///  Class: ConductorImplements
///
/// Author: $author$
///   Date: 1/5/2013
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS ConductorImplements
: virtual public ConductorImplement,
  virtual public ConnectionObserverInterface,
  virtual public PeerConnectionObserverInterface,
  virtual public CreateSessionDescriptionObserver
{
public:
    typedef ConductorInterface Implements;
    virtual int AddRef(){ return 0; }
    virtual int Release(){ return 0; }
};

typedef ExportBase ConductorExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Conductor
///
/// Author: $author$
///   Date: 12/25/2012
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Conductor
: virtual public ConductorImplements, public ConductorExtend {
public:
    typedef ConductorImplements Implements;
    typedef ConductorExtend Extends;

    enum CallbackID 
    {
        MEDIA_CHANNELS_INITIALIZED = 1,
        PEER_CONNECTION_CLOSED,
        SEND_MESSAGE_TO_PEER,
        PEER_CONNECTION_ERROR,
        NEW_STREAM_ADDED,
        STREAM_REMOVED,
    };

    Conductor
    (Connection* client, 
     UserInterface* main_wnd);
    virtual ~Conductor();

    virtual void Close();
    bool connection_active() const;

protected:
    //
    // Connection
    //
    virtual bool InitializePeerConnection();
    virtual void DeletePeerConnection();
    virtual void EnsureStreamingUI();
    virtual void AddStreams();
    virtual cricket::VideoCapturer* OpenVideoCaptureDevice();

    //
    // PeerConnectionObserver implementation.
    //
    virtual void OnError();
    virtual void OnStateChange(PeerConnectionObserver::StateType state_changed) {}
    virtual void OnAddStream(MediaStreamInterface* stream);
    virtual void OnRemoveStream(MediaStreamInterface* stream);
    virtual void OnRenegotiationNeeded() {}
    virtual void OnIceChange() {}
    virtual void OnIceCandidate(const IceCandidateInterface* candidate);

    //
    // ClientObserver implementation.
    //
    virtual void OnSignedIn();
    virtual void OnDisconnected();
    virtual void OnPeerConnected(int id, const std::string& name);
    virtual void OnPeerDisconnected(int id);
    virtual void OnMessageFromPeer(int peer_id, const std::string& message);
    virtual void OnMessageSent(int err);
    virtual void OnServerConnectionFailure();

    //
    // UserInterfaceCallback implementation.
    //
    virtual std::string GetPeerName();
    virtual bool StartLogin(const std::string& server, int port);
    virtual void DisconnectFromServer(bool doClose=false);
    virtual void ConnectToPeer(int peer_id);
    virtual void DisconnectFromCurrentPeer();
    virtual void UIThreadCallback(int msg_id, void* data);
    virtual bool SendMessage(const std::string& messageEnvelope);

    //
    // CreateSessionDescriptionObserver implementation.
    //
    virtual void OnSuccess(SessionDescriptionInterface* desc);
    virtual void OnFailure(const std::string& error);

    //
    // Utility
    //
    static std::string GetEnvVarOrDefault(const char* env_var_name, const char* default_value);
    static std::string GetPeerConnectionString();
    static std::string GetDefaultServerName();
    static std::string GetDefaultPeerName();

protected:
    int peer_id_;
    talk_base::scoped_refptr<PeerConnectionInterface> peer_connection_;
    talk_base::scoped_refptr<PeerConnectionFactoryInterface> peer_connection_factory_;
    Connection* client_;
    UserInterface* main_wnd_;
    std::deque<std::string*> pending_messages_;
    std::map<std::string, talk_base::scoped_refptr<MediaStreamInterface> > active_streams_;
    std::string server_;
};

} // namespace client 
} // namespace peerconnection 
} // namespace webrtc 
} // namespace xos 

#endif // _XOS_WEBRTC_PEERCONNECTION_CLIENT_CONDUCTOR_HPP 
