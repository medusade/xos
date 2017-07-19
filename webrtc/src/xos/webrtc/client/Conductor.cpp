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
///   File: Conductor.cpp
///
/// Author: $author$
///   Date: 10/18/2012
///////////////////////////////////////////////////////////////////////
#include "xos/webrtc/client/Conductor.hpp"
#include "xos/network/ip/v4/AddressString.hpp"

#include "talk/base/common.h"
#include "talk/base/logging.h"
#include "talk/p2p/client/basicportallocator.h"
#include "talk/session/phone/videorendererfactory.h"

namespace xos {
namespace webrtc {
namespace client {

///////////////////////////////////////////////////////////////////////
///  Class: Conductor
///////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
///  Struct: Conductor::StreamInfo
///////////////////////////////////////////////////////////////////////
struct Conductor::StreamInfo {
  StreamInfo(const std::string& id, bool video) : id_(id), video_(video) {}
  std::string id_;
  bool video_;
};

///////////////////////////////////////////////////////////////////////
///  Class: Conductor::ServerSocketAddress
///////////////////////////////////////////////////////////////////////
class Conductor::ServerSocketAddress: public talk_base::SocketAddress
{
public:
    typedef talk_base::SocketAddress Extends;

    ServerSocketAddress
    (const ServerAddress& addr, bool useNumericAddress = false)
    {
      if (!(addr.isNil()))
      {
          xos::network::ip::v4::AddressString ipAddrString(addr.host_);
          uint32_t ipAddr;
          if ((useNumericAddress) && (0 < (ipAddr = (uint32_t)(ipAddrString))))
              SetIP(ipAddr);
          else
          SetIP(addr.host_);
          SetPort(addr.port_);
      }
    }
};

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
Conductor::Conductor
(VideoCodec& videoCodec,
 Trace& clientTrace,
 Connection* client, 
 UserInterface* main_wnd,
 bool useNumericServerAddresses) 
 : videoCodec_(videoCodec),
   clientTrace_(clientTrace),

   stun_server_
   (XOS_WEBRTC_CLIENT_CONDUCTOR_DEFAULT_STUN_SERVER_HOST, 
    XOS_WEBRTC_CLIENT_CONDUCTOR_DEFAULT_STUN_SERVER_PORT),

   relay_server_udp_
   (XOS_WEBRTC_CLIENT_CONDUCTOR_DEFAULT_RELAY_SERVER_UDP_HOST, 
    XOS_WEBRTC_CLIENT_CONDUCTOR_DEFAULT_RELAY_SERVER_UDP_PORT),

   relay_server_tcp_
   (XOS_WEBRTC_CLIENT_CONDUCTOR_DEFAULT_RELAY_SERVER_TCP_HOST, 
    XOS_WEBRTC_CLIENT_CONDUCTOR_DEFAULT_RELAY_SERVER_TCP_PORT),

   relay_server_ssl_
   (XOS_WEBRTC_CLIENT_CONDUCTOR_DEFAULT_RELAY_SERVER_SSL_HOST, 
    XOS_WEBRTC_CLIENT_CONDUCTOR_DEFAULT_RELAY_SERVER_SSL_PORT),

   useNumericServerAddresses_(useNumericServerAddresses),

   audioDeviceOptions_
   (XOS_WEBRTC_CLIENT_CONDUCTOR_DEFAULT_AUDIO_DEVICE_OPTIONS),

   videoCaptureDevice_
   (XOS_WEBRTC_CLIENT_CONDUCTOR_DEFAULT_VIDEO_CAPTURE_DEVICE),

   videoLabel_(XOS_WEBRTC_CLIENT_CONDUCTOR_VIDEO_LABEL),
   audioLabel_(XOS_WEBRTC_CLIENT_CONDUCTOR_AUDIO_LABEL),

   peer_id_(-1),
   client_(client),
   main_wnd_(main_wnd)
{
    client_->RegisterObserver(this);
    main_wnd->RegisterObserver(this);
}
Conductor::~Conductor() {
    main_wnd_->UnRegisterObserver();
    ASSERT(peer_connection_.get() == NULL);
}

void Conductor::Close() {
    client_->SignOut(true);
    DeletePeerConnection();
}
bool Conductor::connection_active() const {
    return (peer_connection_.get() != NULL);
}

//
// PortServer settings.
//
static PortServer::Options portServerOptions_;

void Conductor::SetUseRelayServer(bool val) {
    portServerOptions_.SetUseRelayServer(val);
}
bool Conductor::GetUseRelayServer() const {
    bool val = portServerOptions_.GetUseRelayServer();
    return val;
}

//
// Video settings.
//
void Conductor::SetVideoCodecOptions
(int codecWidth, int codecHeight, int frameRate, int minBitrate) {
    videoCodec_.SetDefaultOptions
    (codecWidth, codecHeight, frameRate, minBitrate);
}
void Conductor::GetVideoCodecOptions
(int& codecWidth, int& codecHeight, int& frameRate, int& minBitrate) const {
    videoCodec_.GetDefaultOptions
    (codecWidth, codecHeight, frameRate, minBitrate);
}

VideoCodec::Mode Conductor::SetVideoCodecModeByName(const std::string& toModeName) {
    VideoCodec::Mode toMode;
    if (0 < (toMode = videoCodec_.StringToMode(toModeName)))
        videoCodec_.SetDefaultMode(toMode);
    return toMode;
}
void Conductor::SetVideoCodecModeName(const std::string& toModeName) {
    VideoCodec::Mode toMode;
    if (0 < (toMode = videoCodec_.StringToMode(toModeName)))
        videoCodec_.SetDefaultMode(toMode);
}
std::string Conductor::GetVideoCodecModeName() const {
    std::string modeName;
    VideoCodec::Mode mode;
    if (0 < (mode = videoCodec_.GetDefaultMode()))
        modeName = videoCodec_.ModeToString(mode);
    return modeName;
}

VideoCodec::Mode Conductor::SetVideoCodecMode(VideoCodec::Mode toMode) {
    VideoCodec::Mode mode = videoCodec_.SetDefaultMode(toMode);
    return mode;
}
VideoCodec::Mode Conductor::GetVideoCodecMode() const {
    VideoCodec::Mode mode = videoCodec_.GetDefaultMode();
    return mode;
}

//
// Audio settings.
// 
void Conductor::SetAudioDeviceOptions
(bool echoCancelation, bool noiseSupression, bool autoGainControl) {
    Audio::DeviceOptions options = 0;
    options |= (echoCancelation)?(XOS_WEBRTC_CLIENT_AUDIO_DEVICE_OPTION_ECHO_CANCELLATION):(0);
    options |= (noiseSupression)?(XOS_WEBRTC_CLIENT_AUDIO_DEVICE_OPTION_NOISE_SUPPRESSION):(0);
    options |= (autoGainControl)?(XOS_WEBRTC_CLIENT_AUDIO_DEVICE_OPTION_AUTO_GAIN_CONTROL):(0);
    SetAudioDeviceOptions(options);
}
void Conductor::GetAudioDeviceOptions
(bool& echoCancelation, bool& noiseSupression, bool& autoGainControl) const {
    Audio::DeviceOptions options = 0;
    options = GetAudioDeviceOptions();
    echoCancelation = (0 != (XOS_WEBRTC_CLIENT_AUDIO_DEVICE_OPTION_ECHO_CANCELLATION & options));
    noiseSupression = (0 != (XOS_WEBRTC_CLIENT_AUDIO_DEVICE_OPTION_NOISE_SUPPRESSION & options));
    autoGainControl = (0 != (XOS_WEBRTC_CLIENT_AUDIO_DEVICE_OPTION_AUTO_GAIN_CONTROL & options));
}

Audio::DeviceOptions Conductor::SetAudioDeviceOptions(Audio::DeviceOptions toOptions) {
    Audio::DeviceOptions option = 0;
    audioDeviceOptions_ = 0;
    for (option = XOS_WEBRTC_CLIENT_AUDIO_DEVICE_OPTION_FIRST; 
         option < XOS_WEBRTC_CLIENT_AUDIO_DEVICE_OPTION_NEXT; option <<= 1)
    {
        if ((option & toOptions))
        switch (option)
        {
        case XOS_WEBRTC_CLIENT_AUDIO_DEVICE_OPTION_ECHO_CANCELLATION:
            audioDeviceOptions_ |= cricket::MediaEngineInterface::ECHO_CANCELLATION;
            break;

        case XOS_WEBRTC_CLIENT_AUDIO_DEVICE_OPTION_NOISE_SUPPRESSION:
            audioDeviceOptions_ |= cricket::MediaEngineInterface::NOISE_SUPPRESSION;
            break;

        case XOS_WEBRTC_CLIENT_AUDIO_DEVICE_OPTION_AUTO_GAIN_CONTROL:
            audioDeviceOptions_ |= cricket::MediaEngineInterface::AUTO_GAIN_CONTROL;
            break;
        }
    }
    return toOptions;
}
Audio::DeviceOptions Conductor::GetAudioDeviceOptions() const {
    Audio::DeviceOptions options = 0;

    if ((audioDeviceOptions_ & cricket::MediaEngineInterface::ECHO_CANCELLATION))
        options |= XOS_WEBRTC_CLIENT_AUDIO_DEVICE_OPTION_ECHO_CANCELLATION;

    if ((audioDeviceOptions_ & cricket::MediaEngineInterface::NOISE_SUPPRESSION))
        options |= XOS_WEBRTC_CLIENT_AUDIO_DEVICE_OPTION_NOISE_SUPPRESSION;

    if ((audioDeviceOptions_ & cricket::MediaEngineInterface::AUTO_GAIN_CONTROL))
        options |= XOS_WEBRTC_CLIENT_AUDIO_DEVICE_OPTION_AUTO_GAIN_CONTROL;

    return options;
}

//
// Connection
//
bool Conductor::InitializePeerConnection() {
    ASSERT(peer_connection_factory_.get() == NULL);
    ASSERT(peer_connection_.get() == NULL);
    ASSERT(worker_thread_.get() == NULL);

    worker_thread_.reset(new talk_base::Thread());
    if (!worker_thread_->SetName("ConductorWT", this) ||
        !worker_thread_->Start()) {
      LOG(LS_ERROR) << "Failed to start libjingle worker thread";
      worker_thread_.reset();
      return false;
    }

#if (WEBRTC_REVISION < WEBRTC_GEN_2_REVISION)
//  WebRtc < WEBRTC_GEN_2_REVISION 
// ...
    cricket::PortAllocator* port_allocator =
        new cricket::BasicPortAllocator(
            new talk_base::BasicNetworkManager(),
            ServerSocketAddress((stun_server_),useNumericServerAddresses_),
            ServerSocketAddress((relay_server_udp_),useNumericServerAddresses_),
            ServerSocketAddress((relay_server_tcp_),useNumericServerAddresses_),
            ServerSocketAddress((relay_server_ssl_),useNumericServerAddresses_));
            /*
            talk_base::SocketAddress("stun.l.google.com", 19302),
            talk_base::SocketAddress(),
            talk_base::SocketAddress(),
            talk_base::SocketAddress());
            */
// ...
//  WebRtc < WEBRTC_GEN_2_REVISION
#else // (WEBRTC_REVISION < WEBRTC_GEN_2_REVISION) 
#endif // (WEBRTC_REVISION < WEBRTC_GEN_2_REVISION) 

#if (WEBRTC_REVISION < WEBRTC_GEN_2_REVISION)
//  WebRtc < WEBRTC_GEN_2_REVISION 
// ...
    peer_connection_factory_.reset(
        new ::webrtc::PeerConnectionFactory(port_allocator,
                                          worker_thread_.get()));
    if (!peer_connection_factory_->Initialize()) {
      main_wnd_->MessageBox("Error",
          "Failed to initialize PeerConnectionFactory", true);
      DeletePeerConnection();
      return false;
    }
// ...
//  WebRtc < WEBRTC_GEN_2_REVISION
#else // (WEBRTC_REVISION < WEBRTC_GEN_2_REVISION) 
//  WebRtc >= WEBRTC_GEN_2_REVISION 
// ...
    peer_connection_factory_.reset(
        new ::webrtc::PeerConnectionFactory(worker_thread_.get()));
    if (!peer_connection_factory_->Initialize()) {
      main_wnd_->MessageBox("Error",
          "Failed to initialize PeerConnectionFactory", true);
      DeletePeerConnection();
      return false;
    }
// ...
//  WebRtc >= WEBRTC_GEN_2_REVISION
#endif // (WEBRTC_REVISION < WEBRTC_GEN_2_REVISION) 

#if (WEBRTC_REVISION < WEBRTC_GEN_2_REVISION)
#else // (WEBRTC_REVISION < WEBRTC_GEN_2_REVISION) 
//  WebRtc >= WEBRTC_GEN_2_REVISION 
// ...
    port_allocator_.reset(new cricket::BasicPortAllocator(
        new talk_base::BasicNetworkManager(),
            ServerSocketAddress((stun_server_),useNumericServerAddresses_),
            ServerSocketAddress((relay_server_udp_),useNumericServerAddresses_),
            ServerSocketAddress((relay_server_tcp_),useNumericServerAddresses_),
            ServerSocketAddress((relay_server_ssl_),useNumericServerAddresses_)));
        /*
        talk_base::SocketAddress("stun.l.google.com", 19302),
        talk_base::SocketAddress(),
        talk_base::SocketAddress(),
        talk_base::SocketAddress()));
        */
// ...
//  WebRtc >= WEBRTC_GEN_2_REVISION
#endif // (WEBRTC_REVISION < WEBRTC_GEN_2_REVISION) 

#if (WEBRTC_REVISION < WEBRTC_GEN_2_REVISION)
//  WebRtc < WEBRTC_GEN_2_REVISION 
// ...
    // Since we only ever use a single PeerConnection instance, we share
    // the worker thread between the factory and the PC instance.
    peer_connection_.reset(peer_connection_factory_->CreatePeerConnection(
        worker_thread_.get()));
    if (!peer_connection_.get()) {
      main_wnd_->MessageBox("Error",
          "CreatePeerConnection failed", true);
      DeletePeerConnection();
    } else {
      peer_connection_->RegisterObserver(this);
      bool audio = peer_connection_->SetAudioDevice("", "", audioDeviceOptions_);
      LOG(INFO) << "SetAudioDevice " << (audio ? "succeeded." : "failed.");
    }
// ...
//  WebRtc < WEBRTC_GEN_2_REVISION
#else // (WEBRTC_REVISION < WEBRTC_GEN_2_REVISION) 
//  WebRtc >= WEBRTC_GEN_2_REVISION 
// ...
    // Since we only ever use a single PeerConnection instance, we share
    // the worker thread between the factory and the PC instance.
    peer_connection_.reset(peer_connection_factory_->CreatePeerConnection(
        port_allocator_.get(), worker_thread_.get()));
    if (!peer_connection_.get()) {
      main_wnd_->MessageBox("Error",
          "CreatePeerConnection failed", true);
      DeletePeerConnection();
    } else {
      peer_connection_->RegisterObserver(this);
      bool audio = peer_connection_->SetAudioDevice("", "", audioDeviceOptions_);
      LOG(INFO) << "SetAudioDevice " << (audio ? "succeeded." : "failed.");
    }
// ...
//  WebRtc >= WEBRTC_GEN_2_REVISION
#endif // (WEBRTC_REVISION < WEBRTC_GEN_2_REVISION) 
    return (peer_connection_.get() != NULL);
}
void Conductor::DeletePeerConnection() {
#if (WEBRTC_REVISION < WEBRTC_GEN_2_REVISION)
//  WebRtc < WEBRTC_GEN_2_REVISION 
// ...
    peer_connection_.reset();
    worker_thread_.reset();
    active_streams_.clear();
    peer_connection_factory_.reset();
    peer_id_ = -1;
// ...
//  WebRtc < WEBRTC_GEN_2_REVISION
#else // (WEBRTC_REVISION < WEBRTC_GEN_2_REVISION) 
//  WebRtc >= WEBRTC_GEN_2_REVISION 
// ...
    peer_connection_.reset();
    active_streams_.clear();
    port_allocator_.reset();
    peer_connection_factory_.reset();
    worker_thread_.reset();
    peer_id_ = -1;
// ...
//  WebRtc >= WEBRTC_GEN_2_REVISION
#endif // (WEBRTC_REVISION < WEBRTC_GEN_2_REVISION) 
}
void Conductor::SwitchToStreamingUi() {
    ASSERT(peer_connection_.get() != NULL);
    if (main_wnd_->IsWindow()) {
      if (main_wnd_->current_ui() != UserInterface::STREAMING)
        main_wnd_->SwitchToStreamingUI();

      LOG(INFO) << "Video capture device: " << videoCaptureDevice_;
      if (peer_connection_->SetVideoCapture(videoCaptureDevice_)) {
        peer_connection_->SetLocalVideoRenderer(main_wnd_->local_renderer());
      }
    }
}
bool Conductor::AddStream(const std::string& id, bool video) {
    // NOTE: Must be called from the UI thread.
    if (active_streams_.find(id) != active_streams_.end())
      return false;  // Already added.

    active_streams_.insert(id);
    bool ret = peer_connection_->AddStream(id, video);
    if (!ret) {
      active_streams_.erase(id);
    } else if (video) {
      LOG(INFO) << "Setting video renderer for stream: " << id;
      bool ok = peer_connection_->SetVideoRenderer(id,
          main_wnd_->remote_renderer());
      ASSERT(ok);
      UNUSED(ok);
    }
    return ret;
}
void Conductor::AddStreams() {
    int streams = 0;
    if (AddStream(videoLabel_.c_str(), true))
      ++streams;

    if (AddStream(audioLabel_.c_str(), false))
      ++streams;

    // At the initiator of the call, after adding streams we need
    // kick start the ICE candidates discovery process, which
    // is done by the Connect method. Earlier this was done after
    // getting the OnLocalStreamInitialized callback which is removed
    // now. Connect will trigger OnSignalingMessage callback when
    // ICE candidates are available.
    if (streams)
      peer_connection_->Connect();
}

//
// PeerConnectionObserver implementation.
//
void Conductor::OnError() { 
    LOG(LS_ERROR) << __FUNCTION__;
    main_wnd_->QueueUIThreadCallback(PEER_CONNECTION_ERROR, NULL);
}
void Conductor::OnSignalingMessage(const std::string& msg) { 
    LOG(INFO) << __FUNCTION__;

    if ((main_wnd_))
    if ((main_wnd_->OnSignalingMessageToPeer(peer_id_, msg)))
        return;

    std::string* msg_copy = new std::string(msg);
    main_wnd_->QueueUIThreadCallback(SEND_MESSAGE_TO_PEER, msg_copy);
}
void Conductor::OnAddStream(const std::string& stream_id, bool video) { 
    LOG(INFO) << __FUNCTION__ << " " << stream_id;

    if (!(main_wnd_->OnAddStream(stream_id, video)))
       main_wnd_->QueueUIThreadCallback
       (NEW_STREAM_ADDED, new StreamInfo(stream_id, video));
}
void Conductor::OnRemoveStream(const std::string& stream_id, bool video) { 
    LOG(INFO) << __FUNCTION__ << (video ? " video: " : " audio: ") << stream_id;

    if (!(main_wnd_->OnRemoveStream(stream_id, video)))
       main_wnd_->QueueUIThreadCallback
       (STREAM_REMOVED, new StreamInfo(stream_id, video));
}

//
// ClientObserver implementation.
//
void Conductor::OnSignedIn() {
    LOG(INFO) << __FUNCTION__;
    if (!(main_wnd_->OnSignedIn(client_->peers())))
        main_wnd_->SwitchToPeerList(client_->peers());
}
void Conductor::OnDisconnected() {
    LOG(INFO) << __FUNCTION__;

    DeletePeerConnection();

    if (!(main_wnd_->OnDisconnected()))
    if (main_wnd_->IsWindow())
        main_wnd_->SwitchToConnectUI();
}
void Conductor::OnFailedToConnect() {
    LOG(INFO) << __FUNCTION__;

    main_wnd_->MessageBox
    ("Error", ("Failed to connect to server "
     + connecting_to_server_).c_str(), true);

    main_wnd_->OnFailedToConnectToServer(connecting_to_server_);
}
void Conductor::OnPeerConnected(int id, const std::string& name) {
    LOG(INFO) << __FUNCTION__;
    // Refresh the list if we're showing it.
    if (!(main_wnd_->OnPeerConnected(id, name)))
    if (main_wnd_->current_ui() == UserInterface::LIST_PEERS)
      main_wnd_->SwitchToPeerList(client_->peers());
}
void Conductor::OnPeerDisconnected(int id) {
    LOG(INFO) << __FUNCTION__;
    if (id == peer_id_) {
      LOG(INFO) << "Our peer disconnected";
      if (!(main_wnd_->OnPeerConnectionClosed(id)))
          main_wnd_->QueueUIThreadCallback(PEER_CONNECTION_CLOSED, NULL);
    } else {
      // Refresh the list if we're showing it.
      if (!(main_wnd_->OnPeerDisconnected(id)))
      if (main_wnd_->current_ui() == UserInterface::LIST_PEERS)
        main_wnd_->SwitchToPeerList(client_->peers());
    }
}
void Conductor::OnMessageFromPeer(int peer_id, const std::string& message) {
    if (!((peer_id_ == peer_id) || (peer_id_ == -1)))
    if ((main_wnd_->OnUnexpectedMessageFromPeer(peer_id, message)))
        return;
    ASSERT(peer_id_ == peer_id || peer_id_ == -1);

    if ((message.empty()))
    if ((main_wnd_->OnEmptyMessageFromPeer(peer_id, message)))
        return;
    ASSERT(!message.empty());

    if ((main_wnd_))
    if ((main_wnd_->OnMessageFromPeer(peer_id, message)))
        return;

    if (!peer_connection_.get()) {
      ASSERT(peer_id_ == -1);
      peer_id_ = peer_id;

      if ((main_wnd_))
      if ((main_wnd_->OnSignalingMessageFromUnconnectedPeer(peer_id, message)))
          return;

      // Got an offer.  Give it to the PeerConnection instance.
      // Once processed, we will get a callback to OnSignalingMessage with
      // our 'answer' which we'll send to the peer.
      LOG(INFO) << "Got an offer from our peer: " << peer_id;
      if (!InitializePeerConnection()) {
        LOG(LS_ERROR) << "Failed to initialize our PeerConnection instance";
        client_->SignOut();
        return;
      }
    } else if (peer_id != peer_id_) {
      ASSERT(peer_id_ != -1);
      LOG(WARNING) << "Received an offer from a peer while already in a "
                      "conversation with a different peer.";
      main_wnd_->OnUnexpectedMessageFromPeer(peer_id, message);
      return;
    }

    if ((main_wnd_))
    if ((main_wnd_->OnSignalingMessageFromPeer(peer_id, message)))
        return;

    peer_connection_->SignalingMessage(message);
}
void Conductor::OnMessageSent(int err) {
    // Process the next pending message if any.
    if (!(main_wnd_->OnMessageSentToPeer(err)))
        main_wnd_->QueueUIThreadCallback(SEND_MESSAGE_TO_PEER, NULL);
}

//
// UserInterfaceCallback implementation.
//
std::string Conductor::GetPeerName() {
    std::string peerName = GetDefaultPeerName();
    if ((main_wnd_))
    {
        std::string uiName = main_wnd_->GetThisPeerName();
        if ((uiName.length()))
            peerName = uiName;
        else main_wnd_->SetThisPeerName(peerName);
    }
    return peerName;
}
bool Conductor::StartLogin(const std::string& server, int port) {
    if (client_->is_connected())
      return false;

    if (!(client_->is_not_connected()))
      return false;

    connecting_to_server_ = server;

    if (!client_->Connect(server, port, GetPeerName())) {
      main_wnd_->MessageBox
      ("Error", ("Failed to connect to " + server).c_str(), true);
      main_wnd_->OnFailedToConnectToServer(connecting_to_server_);
      return false;
    }
    return true;
}
void Conductor::DisconnectFromServer(bool doClose) {
    LOG(INFO) << __FUNCTION__;

    if ((doClose) && (peer_connection_.get())) {
      client_->SendHangUp(peer_id_, doClose);
      DeletePeerConnection();
    }

    if (client_->is_connected())
      client_->SignOut(doClose);
}
void Conductor::ConnectToPeer(int peer_id) {
    ASSERT(peer_id_ == -1);
    ASSERT(peer_id != -1);

    if (peer_connection_.get()) {
      main_wnd_->MessageBox("Error",
          "We only support connecting to one peer at a time", true);
      return;
    }

    if (InitializePeerConnection()) {
      peer_id_ = peer_id;
      main_wnd_->SwitchToStreamingUI();
      SwitchToStreamingUi();
      AddStreams();
    } else {
      main_wnd_->MessageBox("Error", "Failed to initialize PeerConnection", true);
    }
}
void Conductor::DisconnectFromCurrentPeer() {
    LOG(INFO) << __FUNCTION__;

    if (peer_connection_.get()) {
      client_->SendHangUp(peer_id_);
      DeletePeerConnection();
    }

    if (main_wnd_->IsWindow())
      main_wnd_->SwitchToPeerList(client_->peers());
}
void Conductor::UIThreadCallback(int msg_id, void* data) {
    switch (msg_id) {
      case PEER_CONNECTION_CLOSED:
        LOG(INFO) << "PEER_CONNECTION_CLOSED";
        DeletePeerConnection();

        ASSERT(active_streams_.empty());

        if (main_wnd_->IsWindow()) {
          if (client_->is_connected()) {
            main_wnd_->SwitchToPeerList(client_->peers());
          } else {
            main_wnd_->SwitchToConnectUI();
          }
        } else {
          DisconnectFromServer();
        }
        break;

      case SEND_MESSAGE_TO_PEER: {
        LOG(INFO) << "SEND_MESSAGE_TO_PEER";
        std::string* msg = reinterpret_cast<std::string*>(data);
        if (msg) {
          // For convenience, we always run the message through the queue.
          // This way we can be sure that messages are sent to the server
          // in the same order they were signaled without much hassle.
          pending_messages_.push_back(msg);
        }

        if (!pending_messages_.empty() && !client_->IsSendingMessage()) {
          msg = pending_messages_.front();
          pending_messages_.pop_front();

          if (!client_->SendToPeer(peer_id_, *msg) && peer_id_ != -1) {
            LOG(LS_ERROR) << "SendToPeer failed";
            DisconnectFromServer();
          }

          delete msg;
        }

        if (!peer_connection_.get())
          peer_id_ = -1;
        break;
      }

      case PEER_CONNECTION_ADDSTREAMS:
        AddStreams();
        break;

      case PEER_CONNECTION_ERROR:
        main_wnd_->MessageBox("Error", "an unknown error occurred", true);
        break;

      case NEW_STREAM_ADDED: {
        talk_base::scoped_ptr<StreamInfo> info(
            reinterpret_cast<StreamInfo*>(data));
        if (info->video_) {
          LOG(INFO) << "Setting video renderer for stream: " << info->id_;
          bool ok = peer_connection_->SetVideoRenderer(info->id_,
              main_wnd_->remote_renderer());
          ASSERT(ok);
          if (!ok)
            LOG(LS_ERROR) << "SetVideoRenderer failed for : " << info->id_;

          // TODO(tommi): For the initiator, we shouldn't have to make this call
          // here (which is actually the second time this is called for the
          // initiator).  Look into why this is needed.
          SwitchToStreamingUi();
        }

        // If we haven't shared any streams with this peer (we're the receiver)
        // then do so now.
        if (active_streams_.empty())
          AddStreams();
        break;
      }

      case STREAM_REMOVED: {
        talk_base::scoped_ptr<StreamInfo> info(
            reinterpret_cast<StreamInfo*>(data));
        active_streams_.erase(info->id_);
        if (active_streams_.empty()) {
          LOG(INFO) << "All streams have been closed.";
          main_wnd_->QueueUIThreadCallback(PEER_CONNECTION_CLOSED, NULL);
        }
        break;
      }

      default:
        ASSERT(false);
        break;
    }
}
bool Conductor::SendMessageToPeer(const std::string& messageEnvelope) {
    bool handled = false;
    std::string* msgData;

    if ((main_wnd_))
    if ((msgData = new std::string(messageEnvelope)))
    {
        //
        // tell MainWnd to queue the message to be sent to the peer.
        // The string will be deleted when the message is sent.
        //
        main_wnd_->QueueUIThreadCallback(SEND_MESSAGE_TO_PEER, msgData);
        handled = true;
    }
    return handled;
}

//
// Utility
//
std::string Conductor::GetEnvVarOrDefault(const char* env_var_name, const char* default_value) {
    std::string value;
    const char* env_var = getenv(env_var_name);
    if (env_var)
      value = env_var;

    if (value.empty())
      value = default_value;

    return value;
}
std::string Conductor::GetWebRtcVideoString() {
    return GetEnvVarOrDefault("WEBRTC_CONNECT", "STUN stun.l.google.com:19302");
}
std::string Conductor::GetDefaultServerName() {
    return GetEnvVarOrDefault("WEBRTC_SERVER", "localhost");
}
std::string Conductor::GetDefaultPeerName() {
    char computer_name[256];
    if (gethostname(computer_name, ARRAY_SIZE(computer_name)) != 0)
      strcpy(computer_name, "host");
    std::string ret(GetEnvVarOrDefault("USERNAME", "user"));
    ret += '@';
    ret += computer_name;
    return ret;
}

} // namespace client 
} // namespace webrtc 
} // namespace xos 
