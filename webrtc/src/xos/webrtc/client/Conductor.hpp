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
///   Date: 10/18/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_WEBRTC_CLIENT_CONDUCTOR_HPP
#define _XOS_WEBRTC_CLIENT_CONDUCTOR_HPP

#include "xos/webrtc/client/ConductorInterface.hpp"
#include "xos/webrtc/client/Connection.hpp"
#include "xos/webrtc/client/UserInterface.hpp"
#include "xos/webrtc/client/PortServer.hpp"
#include "xos/webrtc/client/VideoCodec.hpp"
#include "xos/webrtc/client/Trace.hpp"
#include "talk/base/scoped_ptr.h"
#include "talk/app/webrtc/peerconnection.h"
#include "talk/app/webrtc/peerconnectionfactory.h"
#include "talk/session/phone/mediaengine.h"

#define XOS_WEBRTC_CLIENT_CONDUCTOR_USE_GOOGLE_STUN_SERVER
#define XOS_WEBRTC_CLIENT_CONDUCTOR_NO_USE_NUMERIC_SERVER_ADDRESSES

#if !defined(XOS_WEBRTC_CLIENT_CONDUCTOR_DEFAULT_USE_NUMERIC_SERVER_ADDRESSES) 
#if defined(XOS_WEBRTC_CLIENT_CONDUCTOR_USE_NUMERIC_SERVER_ADDRESSES)
// Numeric server addresses
#define XOS_WEBRTC_CLIENT_CONDUCTOR_DEFAULT_USE_NUMERIC_SERVER_ADDRESSES true
#else // defined(XOS_WEBRTC_CLIENT_CONDUCTOR_USE_NUMERIC_SERVER_ADDRESSES)
// String server addresses
#define XOS_WEBRTC_CLIENT_CONDUCTOR_DEFAULT_USE_NUMERIC_SERVER_ADDRESSES false
#endif // defined(XOS_WEBRTC_CLIENT_CONDUCTOR_USE_NUMERIC_SERVER_ADDRESSES)
#endif // !defined(XOS_WEBRTC_CLIENT_CONDUCTOR_DEFAULT_USE_NUMERIC_SERVER_ADDRESSES) 

//
// Google address
//
#define XOS_WEBRTC_CLIENT_CONDUCTOR_DEFAULT_GOOGLE_STUN_SERVER_HOST_NAME "stun.l.google.com"
#define XOS_WEBRTC_CLIENT_CONDUCTOR_DEFAULT_GOOGLE_STUN_SERVER_HOST_ADDRESS "72.215.255.9"
#define XOS_WEBRTC_CLIENT_CONDUCTOR_DEFAULT_GOOGLE_STUN_SERVER_PORT 19302

#if defined(XOS_WEBRTC_CLIENT_CONDUCTOR_USE_NUMERIC_SERVER_ADDRESSES) 
// Use numeric addresses 
#define XOS_WEBRTC_CLIENT_CONDUCTOR_DEFAULT_GOOGLE_STUN_SERVER_HOST \
    XOS_WEBRTC_CLIENT_CONDUCTOR_DEFAULT_GOOGLE_STUN_SERVER_HOST_ADDRESS
#else // defined(XOS_WEBRTC_CLIENT_CONDUCTOR_USE_NUMERIC_SERVER_ADDRESSES) 
// Use hostnames 
#define XOS_WEBRTC_CLIENT_CONDUCTOR_DEFAULT_GOOGLE_STUN_SERVER_HOST \
    XOS_WEBRTC_CLIENT_CONDUCTOR_DEFAULT_GOOGLE_STUN_SERVER_HOST_NAME
#endif // defined(XOS_WEBRTC_CLIENT_CONDUCTOR_USE_NUMERIC_SERVER_ADDRESSES) 

//
// Relay address
//
#define XOS_WEBRTC_CLIENT_CONDUCTOR_DEFAULT_RELAY_SERVER_HOST_NAME "localhost"
#define XOS_WEBRTC_CLIENT_CONDUCTOR_DEFAULT_RELAY_SERVER_HOST_ADDRESS "127.0.0.1"

#if defined(XOS_WEBRTC_CLIENT_CONDUCTOR_USE_NUMERIC_SERVER_ADDRESSES) 
// Use numeric addresses 
#define XOS_WEBRTC_CLIENT_CONDUCTOR_DEFAULT_RELAY_SERVER_HOST \
    XOS_WEBRTC_CLIENT_CONDUCTOR_DEFAULT_RELAY_SERVER_HOST_ADDRESS
#else // defined(XOS_WEBRTC_CLIENT_CONDUCTOR_USE_NUMERIC_SERVER_ADDRESSES) 
// Use hostnames 
#define XOS_WEBRTC_CLIENT_CONDUCTOR_DEFAULT_RELAY_SERVER_HOST \
    XOS_WEBRTC_CLIENT_CONDUCTOR_DEFAULT_RELAY_SERVER_HOST_NAME
#endif // defined(XOS_WEBRTC_CLIENT_CONDUCTOR_USE_NUMERIC_SERVER_ADDRESSES) 

//
// local address
//
#define XOS_WEBRTC_CLIENT_CONDUCTOR_DEFAULT_LOCAL_SERVER_HOST_NAME "localhost"
#define XOS_WEBRTC_CLIENT_CONDUCTOR_DEFAULT_LOCAL_SERVER_HOST_ADDRESS "127.0.0.1"

#if defined(XOS_WEBRTC_CLIENT_CONDUCTOR_USE_NUMERIC_SERVER_ADDRESSES) 
// Use numeric addresses 
#define XOS_WEBRTC_CLIENT_CONDUCTOR_DEFAULT_LOCAL_SERVER_HOST \
    XOS_WEBRTC_CLIENT_CONDUCTOR_DEFAULT_LOCAL_SERVER_HOST_ADDRESS
#else // defined(XOS_WEBRTC_CLIENT_CONDUCTOR_USE_NUMERIC_SERVER_ADDRESSES) 
// Use hostnames 
#define XOS_WEBRTC_CLIENT_CONDUCTOR_DEFAULT_LOCAL_SERVER_HOST \
    XOS_WEBRTC_CLIENT_CONDUCTOR_DEFAULT_LOCAL_SERVER_HOST_NAME
#endif // defined(XOS_WEBRTC_CLIENT_CONDUCTOR_USE_NUMERIC_SERVER_ADDRESSES) 

//
// XOS default server addresses
//
#if defined(XOS_WEBRTC_CLIENT_CONDUCTOR_USE_GOOGLE_STUN_SERVER)
//
// Use Google stun server
//
#define XOS_WEBRTC_CLIENT_CONDUCTOR_DEFAULT_STUN_SERVER_HOST XOS_WEBRTC_CLIENT_CONDUCTOR_DEFAULT_GOOGLE_STUN_SERVER_HOST
#define XOS_WEBRTC_CLIENT_CONDUCTOR_DEFAULT_STUN_SERVER_PORT XOS_WEBRTC_CLIENT_CONDUCTOR_DEFAULT_GOOGLE_STUN_SERVER_PORT

#define XOS_WEBRTC_CLIENT_CONDUCTOR_DEFAULT_RELAY_SERVER_UDP_HOST ""
#define XOS_WEBRTC_CLIENT_CONDUCTOR_DEFAULT_RELAY_SERVER_UDP_PORT -1

#define XOS_WEBRTC_CLIENT_CONDUCTOR_DEFAULT_RELAY_SERVER_TCP_HOST ""
#define XOS_WEBRTC_CLIENT_CONDUCTOR_DEFAULT_RELAY_SERVER_TCP_PORT -1

#define XOS_WEBRTC_CLIENT_CONDUCTOR_DEFAULT_RELAY_SERVER_SSL_HOST ""
#define XOS_WEBRTC_CLIENT_CONDUCTOR_DEFAULT_RELAY_SERVER_SSL_PORT -1
#else // XOS_WEBRTC_CLIENT_CONDUCTOR_USE_GOOGLE_STUN_SERVER
//
// Use relay stun server
//
#define XOS_WEBRTC_CLIENT_CONDUCTOR_DEFAULT_STUN_SERVER_HOST XOS_WEBRTC_CLIENT_CONDUCTOR_DEFAULT_RELAY_SERVER_HOST
#define XOS_WEBRTC_CLIENT_CONDUCTOR_DEFAULT_STUN_SERVER_PORT 7000

#define XOS_WEBRTC_CLIENT_CONDUCTOR_DEFAULT_RELAY_SERVER_UDP_HOST XOS_WEBRTC_CLIENT_CONDUCTOR_DEFAULT_RELAY_SERVER_HOST
#define XOS_WEBRTC_CLIENT_CONDUCTOR_DEFAULT_RELAY_SERVER_UDP_PORT 5000

#define XOS_WEBRTC_CLIENT_CONDUCTOR_DEFAULT_RELAY_SERVER_TCP_HOST XOS_WEBRTC_CLIENT_CONDUCTOR_DEFAULT_RELAY_SERVER_HOST
#define XOS_WEBRTC_CLIENT_CONDUCTOR_DEFAULT_RELAY_SERVER_TCP_PORT 5000

//#define XOS_WEBRTC_CLIENT_CONDUCTOR_DEFAULT_RELAY_SERVER_SSL_HOST XOS_WEBRTC_CLIENT_CONDUCTOR_DEFAULT_RELAY_SERVER_HOST
//#define XOS_WEBRTC_CLIENT_CONDUCTOR_DEFAULT_RELAY_SERVER_SSL_PORT 5000
#define XOS_WEBRTC_CLIENT_CONDUCTOR_DEFAULT_RELAY_SERVER_SSL_HOST ""
#define XOS_WEBRTC_CLIENT_CONDUCTOR_DEFAULT_RELAY_SERVER_SSL_PORT -1
#endif // XOS_WEBRTC_CLIENT_CONDUCTOR_USE_GOOGLE_STUN_SERVER

//
// Default video device
//
#define XOS_WEBRTC_CLIENT_CONDUCTOR_DEFAULT_VIDEO_CAPTURE_DEVICE ""

//
// Default audio device options
//
#define XOS_WEBRTC_CLIENT_CONDUCTOR_DEFAULT_AUDIO_DEVICE_OPTIONS \
    cricket::MediaEngineInterface::ECHO_CANCELLATION \
    | cricket::MediaEngineInterface::NOISE_SUPPRESSION \
    | cricket::MediaEngineInterface::AUTO_GAIN_CONTROL

#define XOS_WEBRTC_CLIENT_CONDUCTOR_VIDEO_LABEL "video_label"
#define XOS_WEBRTC_CLIENT_CONDUCTOR_AUDIO_LABEL "audio_label"

namespace cricket {
class VideoRenderer;
#if (WEBRTC_REVISION < WEBRTC_GEN_2_REVISION)
#else // (WEBRTC_REVISION < WEBRTC_GEN_2_REVISION) 
class PortAllocator;
#endif // (WEBRTC_REVISION < WEBRTC_GEN_2_REVISION) 
}  // namespace cricket

namespace xos {
namespace webrtc {
namespace client {

typedef ::webrtc::PeerConnection PeerConnection;
typedef ::webrtc::PeerConnectionFactory PeerConnectionFactory;
typedef ::webrtc::PeerConnectionObserver PeerConnectionObserverInterface;

class _EXPORT_CLASS ConductorImplements
: virtual public ConductorImplement,
  virtual public ConnectionObserverInterface,
  virtual public PeerConnectionObserverInterface
{
public:
    typedef ConductorInterface Implements;
};

typedef ExportBase ConductorExtends;

class _EXPORT_CLASS Conductor: virtual public ConductorImplements, public ConductorExtends {
public:
    typedef ConductorImplements Implements;
    typedef ConductorExtends Extends;

    Conductor
    (VideoCodec& videoCodec,
     Trace& clientTrace,
     Connection* client, 
     UserInterface* main_wnd,
     bool useNumericServerAddresses = XOS_WEBRTC_CLIENT_CONDUCTOR_DEFAULT_USE_NUMERIC_SERVER_ADDRESSES);
    virtual ~Conductor();

    virtual void Close();
    bool connection_active() const;

public:
    //
    // PortServer settings.
    //
    virtual void SetPortServerHost(const std::string& val)
    { stun_server_.host_ = val;
      relay_server_udp_.host_ = val; 
      relay_server_tcp_.host_ = val; 
      relay_server_ssl_.host_ = val; }
    virtual std::string GetPortServerHost() const
    { return stun_server_.host_;}

    virtual void SetStunServerHost(const std::string& val)
    { stun_server_.host_ = val; }
    virtual std::string GetStunServerHost() const
    { return stun_server_.host_;}

    virtual void SetStunServerPort(int val)
    { stun_server_.port_ = val; }
    virtual int GetStunServerPort() const
    { return stun_server_.port_;}

    virtual void SetRelayServerHost(const std::string& val)
    { relay_server_udp_.host_ = val; 
      relay_server_tcp_.host_ = val; 
      relay_server_ssl_.host_ = val; }
    virtual std::string GetRelayServerHost() const
    { return relay_server_udp_.host_;}

    virtual void SetRelayServerPort(int val)
    { relay_server_udp_.port_ = val; 
      relay_server_tcp_.port_ = val; 
      relay_server_ssl_.port_ = val; }
    virtual int GetRelayServerPort() const
    { return relay_server_udp_.port_;}

    virtual void SetRelayUDPServerHost(const std::string& val)
    { relay_server_udp_.host_ = val; }
    virtual std::string GetRelayUDPServerHost() const
    { return relay_server_udp_.host_;}

    virtual void SetRelayUDPServerPort(int val)
    { relay_server_udp_.port_ = val; }
    virtual int GetRelayUDPServerPort() const
    { return relay_server_udp_.port_;}

    virtual void SetRelayTCPServerHost(const std::string& val)
    { relay_server_tcp_.host_ = val; }
    virtual std::string GetRelayTCPServerHost() const
    { return relay_server_tcp_.host_;}

    virtual void SetRelayTCPServerPort(int val)
    { relay_server_tcp_.port_ = val; }
    virtual int GetRelayTCPServerPort() const
    { return relay_server_tcp_.port_;}

    virtual void SetRelaySSLServerHost(const std::string& val)
    { relay_server_ssl_.host_ = val; }
    virtual std::string GetRelaySSLServerHost() const
    { return relay_server_ssl_.host_;}

    virtual void SetRelaySSLServerPort(int val)
    { relay_server_ssl_.port_ = val; }
    virtual int GetRelaySSLServerPort() const
    { return relay_server_ssl_.port_;}

    virtual void SetUseNumericServerAddresses(bool val = true)
    { useNumericServerAddresses_ = val; }
    virtual bool GetUseNumericServerAddresses() const
    { return useNumericServerAddresses_; }

    virtual void SetUseRelayServer(bool val = true);
    virtual bool GetUseRelayServer() const;

    //
    // Video settings.
    //
    virtual void SetVideoCaptureDevice(const std::string& val)
    { videoCaptureDevice_ = val; }
    virtual std::string GetVideoCaptureDevice() const
    { return videoCaptureDevice_; }

    virtual void SetVideoCodecOptions
    (int codecWidth, int codecHeight, int frameRate, int minBitrate);
    virtual void GetVideoCodecOptions
    (int& codecWidth, int& codecHeight, int& frameRate, int& minBitrate) const;

    virtual VideoCodec::Mode SetVideoCodecModeByName(const std::string& toModeName);
    virtual void SetVideoCodecModeName(const std::string& toModeName);
    virtual std::string GetVideoCodecModeName() const;

    virtual VideoCodec::Mode SetVideoCodecMode(VideoCodec::Mode toMode);
    virtual VideoCodec::Mode GetVideoCodecMode() const;

    //
    // Audio settings.
    // 
    virtual void SetAudioDeviceOptions
    (bool echoCancelation, bool noiseSupression, bool autoGainControl);
    virtual void GetAudioDeviceOptions
    (bool& echoCancelation, bool& noiseSupression, bool& autoGainControl) const;

    virtual Audio::DeviceOptions SetAudioDeviceOptions(Audio::DeviceOptions toOptions);
    virtual Audio::DeviceOptions GetAudioDeviceOptions() const;

protected:
    //
    // Connection
    //
    virtual bool InitializePeerConnection();
    virtual void DeletePeerConnection();
    virtual void SwitchToStreamingUi();
    virtual bool AddStream(const std::string& id, bool video);
    virtual void AddStreams();

    //
    // PeerConnectionObserver implementation.
    //
    virtual void OnError();
    virtual void OnSignalingMessage(const std::string& msg);
    virtual void OnAddStream(const std::string& stream_id, bool video);
    virtual void OnRemoveStream(const std::string& stream_id, bool video);

    //
    // ClientObserver implementation.
    //
    virtual void OnSignedIn();
    virtual void OnDisconnected();
    virtual void OnFailedToConnect();
    virtual void OnPeerConnected(int id, const std::string& name);
    virtual void OnPeerDisconnected(int id);
    virtual void OnMessageFromPeer(int peer_id, const std::string& message);
    virtual void OnMessageSent(int err);

    //
    // UserInterfaceCallback implementation.
    //
    virtual std::string GetPeerName();
    virtual bool StartLogin(const std::string& server, int port);
    virtual void DisconnectFromServer(bool doClose=false);
    virtual void ConnectToPeer(int peer_id);
    virtual void DisconnectFromCurrentPeer();
    virtual void UIThreadCallback(int msg_id, void* data);
    virtual bool SendMessageToPeer(const std::string& messageEnvelope);

    //
    // Utility
    //
    static std::string GetEnvVarOrDefault(const char* env_var_name, const char* default_value);
    static std::string GetWebRtcVideoString();
    static std::string GetDefaultServerName();
    static std::string GetDefaultPeerName();

protected:
    enum CallbackID 
    {
        MEDIA_CHANNELS_INITIALIZED = 1,
        PEER_CONNECTION_CLOSED,
        SEND_MESSAGE_TO_PEER,
        PEER_CONNECTION_ADDSTREAMS,
        PEER_CONNECTION_ERROR,
        NEW_STREAM_ADDED,
        STREAM_REMOVED,
    };
    class ServerAddress
    {
    public:
        std::string host_;
        int port_;
        ServerAddress(const std::string& host, int port)
        : host_(host), port_(port){}
        bool isNil() const 
        {return ((0 >= host_.length())||(0 > port_));};
    };
    class ServerSocketAddress;
    struct StreamInfo;

protected:
    VideoCodec& videoCodec_;
    Trace& clientTrace_;

    ServerAddress stun_server_;
    ServerAddress relay_server_udp_;
    ServerAddress relay_server_tcp_;
    ServerAddress relay_server_ssl_;
    bool useNumericServerAddresses_;
    int audioDeviceOptions_;
    std::string videoCaptureDevice_;
    std::string videoLabel_;
    std::string audioLabel_;
    int peer_id_;
    talk_base::scoped_ptr<PeerConnection> peer_connection_;
    talk_base::scoped_ptr<PeerConnectionFactory> peer_connection_factory_;
    talk_base::scoped_ptr<talk_base::Thread> worker_thread_;
    Connection* client_;
    UserInterface* main_wnd_;
    std::deque<std::string*> pending_messages_;
    std::set<std::string> active_streams_;
#if (WEBRTC_REVISION < WEBRTC_GEN_2_REVISION)
#else // (WEBRTC_REVISION < WEBRTC_GEN_2_REVISION) 
    talk_base::scoped_ptr<cricket::PortAllocator> port_allocator_;
#endif // (WEBRTC_REVISION < WEBRTC_GEN_2_REVISION) 
    std::string connecting_to_server_;
};

} // namespace client 
} // namespace webrtc 
} // namespace xos 

#endif // _XOS_WEBRTC_CLIENT_CONDUCTOR_HPP 
