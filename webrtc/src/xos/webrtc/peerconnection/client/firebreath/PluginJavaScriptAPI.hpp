////////////////////////////////////////////////////////////////////////
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
///   File: PluginJavaScriptAPI.hpp
///
/// Author: $author$
///   Date: 1/17/2013
////////////////////////////////////////////////////////////////////////
#if !defined(_XOS_WEBRTC_PEERCONNECTION_CLIENT_FIREBREATH_PLUGINJAVASCRIPTAPI_HPP) || defined(XOS_WEBRTC_PEERCONNECTION_CLIENT_FIREBREATH_PLUGINJAVASCRIPTAPI_MEMBERS_ONLY)
#if !defined(_XOS_WEBRTC_PEERCONNECTION_CLIENT_FIREBREATH_PLUGINJAVASCRIPTAPI_HPP) && !defined(XOS_WEBRTC_PEERCONNECTION_CLIENT_FIREBREATH_PLUGINJAVASCRIPTAPI_MEMBERS_ONLY)
#define _XOS_WEBRTC_PEERCONNECTION_CLIENT_FIREBREATH_PLUGINJAVASCRIPTAPI_HPP
#endif // !defined(_XOS_WEBRTC_PEERCONNECTION_CLIENT_FIREBREATH_PLUGINJAVASCRIPTAPI_HPP) && !defined(XOS_WEBRTC_PEERCONNECTION_CLIENT_FIREBREATH_PLUGINJAVASCRIPTAPI_MEMBERS_ONLY)

#if !defined(XOS_WEBRTC_PEERCONNECTION_CLIENT_FIREBREATH_PLUGINJAVASCRIPTAPI_MEMBERS_ONLY)
#include "xos/base/Base.hpp"
#include <string>

namespace xos {
namespace webrtc {
namespace peerconnection {
namespace client {
namespace firebreath {

////////////////////////////////////////////////////////////////////////
///  Class: PluginJavaScriptAPI
///
/// Author: $author$
///   Date: 1/17/2013
////////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS PluginJavaScriptAPI
{
public:
    typedef PluginJavaScriptAPI Implements;
    typedef PluginJavaScriptAPI Derives;
#else // !defined(XOS_WEBRTC_PEERCONNECTION_CLIENT_FIREBREATH_PLUGINJAVASCRIPTAPI_MEMBERS_ONLY)
#endif // !defined(XOS_WEBRTC_PEERCONNECTION_CLIENT_FIREBREATH_PLUGINJAVASCRIPTAPI_MEMBERS_ONLY)

    //
    // read/write properties
    //

    // autoConnectToPeerOn
    //
    bool get_autoConnectToPeerOn()
    { bool val = false;
      Implements* delegated;
      if ((delegated = Delegated()))
          val = delegated->get_autoConnectToPeerOn();
      return val; }
    void set_autoConnectToPeerOn(bool val)
    { Implements* delegated;
      if ((delegated = Delegated()))
          delegated->set_autoConnectToPeerOn(val); }

    // autoConnectToPeerAfterOn
    //
    bool get_autoConnectToPeerAfterOn()
    { bool val = false;
      Implements* delegated;
      if ((delegated = Delegated()))
          val = delegated->get_autoConnectToPeerAfterOn();
      return val; }
    void set_autoConnectToPeerAfterOn(bool val)
    { Implements* delegated;
      if ((delegated = Delegated()))
          delegated->set_autoConnectToPeerAfterOn(val); }

    // openGLRenderingOn
    //
    bool get_openGLRenderingOn()
    { bool val = false;
      Implements* delegated;
      if ((delegated = Delegated()))
          val = delegated->get_openGLRenderingOn();
      return val; }
    void set_openGLRenderingOn(bool val)
    { Implements* delegated;
      if ((delegated = Delegated()))
          delegated->set_openGLRenderingOn(val); }

    // openGLRenderingMode
    //
    std::string get_openGLRenderingMode()
    { std::string val;
      Implements* delegated;
      if ((delegated = Delegated()))
          val = delegated->get_openGLRenderingMode();
      return val; }
    void set_openGLRenderingMode(const std::string& val)
    { Implements* delegated;
      if ((delegated = Delegated()))
          delegated->set_openGLRenderingMode(val); }

    // audioEchoCancellationOn
    //
    bool get_audioEchoCancellationOn()
    { bool val = false;
      Implements* delegated;
      if ((delegated = Delegated()))
          val = delegated->get_audioEchoCancellationOn();
      return val; }
    void set_audioEchoCancellationOn(bool val)
    { Implements* delegated;
      if ((delegated = Delegated()))
          delegated->set_audioEchoCancellationOn(val); }

    // audioNoiseSupressionOn
    //
    bool get_audioNoiseSupressionOn()
    { bool val = false;
      Implements* delegated;
      if ((delegated = Delegated()))
          val = delegated->get_audioNoiseSupressionOn();
      return val; }
    void set_audioNoiseSupressionOn(bool val)
    { Implements* delegated;
      if ((delegated = Delegated()))
          delegated->set_audioNoiseSupressionOn(val); }

    // audioAutoGainControlOn
    //
    bool get_audioAutoGainControlOn()
    { bool val = false;
      Implements* delegated;
      if ((delegated = Delegated()))
          val = delegated->get_audioAutoGainControlOn();
      return val; }
    void set_audioAutoGainControlOn(bool val)
    { Implements* delegated;
      if ((delegated = Delegated()))
          delegated->set_audioAutoGainControlOn(val); }

    // videoCodecMode
    //
    std::string get_videoCodecMode()
    { std::string val;
      Implements* delegated;
      if ((delegated = Delegated()))
          val = delegated->get_videoCodecMode();
      return val; }
    void set_videoCodecMode(const std::string& val)
    { Implements* delegated;
      if ((delegated = Delegated()))
          delegated->set_videoCodecMode(val); }

    // videoCodecWidth
    //
    int get_videoCodecWidth()
    { int val = -1;
      Implements* delegated;
      if ((delegated = Delegated()))
          val = delegated->get_videoCodecWidth();
      return val; }
    void set_videoCodecWidth(int val)
    { Implements* delegated;
      if ((delegated = Delegated()))
          delegated->set_videoCodecWidth(val); }

    // videoCodecHeight
    //
    int get_videoCodecHeight()
    { int val = -1;
      Implements* delegated;
      if ((delegated = Delegated()))
          val = delegated->get_videoCodecHeight();
      return val; }
    void set_videoCodecHeight(int val)
    { Implements* delegated;
      if ((delegated = Delegated()))
          delegated->set_videoCodecHeight(val); }

    // videoCodecFrameRate
    //
    int get_videoCodecFrameRate()
    { int val = -1;
      Implements* delegated;
      if ((delegated = Delegated()))
          val = delegated->get_videoCodecFrameRate();
      return val; }
    void set_videoCodecFrameRate(int val)
    { Implements* delegated;
      if ((delegated = Delegated()))
          delegated->set_videoCodecFrameRate(val); }

    // videoCodecMinBitrate
    //
    int get_videoCodecMinBitrate()
    { int val = -1;
      Implements* delegated;
      if ((delegated = Delegated()))
          val = delegated->get_videoCodecMinBitrate();
      return val; }
    void set_videoCodecMinBitrate(int val)
    { Implements* delegated;
      if ((delegated = Delegated()))
          delegated->set_videoCodecMinBitrate(val); }

    // stunServerHost
    //
    std::string get_stunServerHost()
    { std::string val;
      Implements* delegated;
      if ((delegated = Delegated()))
          val = delegated->get_stunServerHost();
      return val; }
    void set_stunServerHost(const std::string& val)
    { Implements* delegated;
      if ((delegated = Delegated()))
          delegated->set_stunServerHost(val); }

    // stunServerPort
    //
    int get_stunServerPort()
    { int val = -1;
      Implements* delegated;
      if ((delegated = Delegated()))
          val = delegated->get_stunServerPort();
      return val; }
    void set_stunServerPort(int val)
    { Implements* delegated;
      if ((delegated = Delegated()))
          delegated->set_stunServerPort(val); }

    // relayUDPServerHost
    //
    std::string get_relayUDPServerHost()
    { std::string val;
      Implements* delegated;
      if ((delegated = Delegated()))
          val = delegated->get_relayUDPServerHost();
      return val; }
    void set_relayUDPServerHost(const std::string& val)
    { Implements* delegated;
      if ((delegated = Delegated()))
          delegated->set_relayUDPServerHost(val); }

    // relayUDPServerPort
    //
    int get_relayUDPServerPort()
    { int val = -1;
      Implements* delegated;
      if ((delegated = Delegated()))
          val = delegated->get_relayUDPServerPort();
      return val; }
    void set_relayUDPServerPort(int val)
    { Implements* delegated;
      if ((delegated = Delegated()))
          delegated->set_relayUDPServerPort(val); }

    // relayTCPServerHost
    //
    std::string get_relayTCPServerHost()
    { std::string val;
      Implements* delegated;
      if ((delegated = Delegated()))
          val = delegated->get_relayTCPServerHost();
      return val; }
    void set_relayTCPServerHost(const std::string& val)
    { Implements* delegated;
      if ((delegated = Delegated()))
          delegated->set_relayTCPServerHost(val); }

    // relayTCPServerPort
    //
    int get_relayTCPServerPort()
    { int val = -1;
      Implements* delegated;
      if ((delegated = Delegated()))
          val = delegated->get_relayTCPServerPort();
      return val; }
    void set_relayTCPServerPort(int val)
    { Implements* delegated;
      if ((delegated = Delegated()))
          delegated->set_relayTCPServerPort(val); }

    // relaySSLServerHost
    //
    std::string get_relaySSLServerHost()
    { std::string val;
      Implements* delegated;
      if ((delegated = Delegated()))
          val = delegated->get_relaySSLServerHost();
      return val; }
    void set_relaySSLServerHost(const std::string& val)
    { Implements* delegated;
      if ((delegated = Delegated()))
          delegated->set_relaySSLServerHost(val); }

    // relaySSLServerPort
    //
    int get_relaySSLServerPort()
    { int val = -1;
      Implements* delegated;
      if ((delegated = Delegated()))
          val = delegated->get_relaySSLServerPort();
      return val; }
    void set_relaySSLServerPort(int val)
    { Implements* delegated;
      if ((delegated = Delegated()))
          delegated->set_relaySSLServerPort(val); }

    //
    // read only properties
    //

    // version
    //
    std::string get_version()
    { std::string val;
      Implements* delegated;
      if ((delegated = Delegated()))
          val = delegated->get_version();
      return val; }

    // state
    //
    std::string get_state()
    { std::string val;
      Implements* delegated;
      if ((delegated = Delegated()))
          val = delegated->get_state();
      return val; }

    // availablePeers
    //
    std::string get_availablePeers()
    { std::string val;
      Implements* delegated;
      if ((delegated = Delegated()))
          val = delegated->get_availablePeers();
      return val; }

    // connectedPeer
    //
    std::string get_connectedPeer()
    { std::string val;
      Implements* delegated;
      if ((delegated = Delegated()))
          val = delegated->get_connectedPeer();
      return val; }

    // connectedPeerId
    //
    int get_connectedPeerId()
    { int val = -1;
      Implements* delegated;
      if ((delegated = Delegated()))
          val = delegated->get_connectedPeerId();
      return val; }

    class _EXPORT_CLASS EventsInterface;
    ////////////////////////////////////////////////////////////////////////
    ///  Function: Delegate
    ///
    ///    Author: $author$
    ///      Date: 1/17/2013
    ////////////////////////////////////////////////////////////////////////
    virtual Implements* Delegate(EventsInterface* events=0)
    { return ((Implements*)(this)); }
    ////////////////////////////////////////////////////////////////////////
    ///  Function: Delegated
    ///
    ///    Author: $author$
    ///      Date: 1/17/2013
    ////////////////////////////////////////////////////////////////////////
    virtual Implements* Delegated()
#if !defined(XOS_WEBRTC_PEERCONNECTION_CLIENT_FIREBREATH_PLUGINJAVASCRIPTAPI_MEMBERS_ONLY)
    { return 0; }
#else // !defined(XOS_WEBRTC_PEERCONNECTION_CLIENT_FIREBREATH_PLUGINJAVASCRIPTAPI_MEMBERS_ONLY)
    ;
#endif // !defined(XOS_WEBRTC_PEERCONNECTION_CLIENT_FIREBREATH_PLUGINJAVASCRIPTAPI_MEMBERS_ONLY)


#if !defined(XOS_WEBRTC_PEERCONNECTION_CLIENT_FIREBREATH_PLUGINJAVASCRIPTAPI_MEMBERS_ONLY)
#else // !defined(XOS_WEBRTC_PEERCONNECTION_CLIENT_FIREBREATH_PLUGINJAVASCRIPTAPI_MEMBERS_ONLY)
    ////////////////////////////////////////////////////////////////////////
    ///  Function: RegisterProperties
    ///
    ///    Author: $author$
    ///      Date: 1/17/2013
    ////////////////////////////////////////////////////////////////////////
    virtual void RegisterProperties()
    {
        //
        // read/write properties
        //

        // autoConnectToPeerOn
        //
        registerProperty
        ("autoConnectToPeerOn", make_property(this,
         &Derives::get_autoConnectToPeerOn, &Derives::set_autoConnectToPeerOn));
    
        // autoConnectToPeerAfterOn
        //
        registerProperty
        ("autoConnectToPeerAfterOn", make_property(this,
         &Derives::get_autoConnectToPeerAfterOn, &Derives::set_autoConnectToPeerAfterOn));
    
        // openGLRenderingOn
        //
        registerProperty
        ("openGLRenderingOn", make_property(this,
         &Derives::get_openGLRenderingOn, &Derives::set_openGLRenderingOn));
    
        // openGLRenderingMode
        //
        registerProperty
        ("openGLRenderingMode", make_property(this,
         &Derives::get_openGLRenderingMode, &Derives::set_openGLRenderingMode));
    
        // audioEchoCancellationOn
        //
        registerProperty
        ("audioEchoCancellationOn", make_property(this,
         &Derives::get_audioEchoCancellationOn, &Derives::set_audioEchoCancellationOn));
    
        // audioNoiseSupressionOn
        //
        registerProperty
        ("audioNoiseSupressionOn", make_property(this,
         &Derives::get_audioNoiseSupressionOn, &Derives::set_audioNoiseSupressionOn));
    
        // audioAutoGainControlOn
        //
        registerProperty
        ("audioAutoGainControlOn", make_property(this,
         &Derives::get_audioAutoGainControlOn, &Derives::set_audioAutoGainControlOn));
    
        // videoCodecMode
        //
        registerProperty
        ("videoCodecMode", make_property(this,
         &Derives::get_videoCodecMode, &Derives::set_videoCodecMode));
    
        // videoCodecWidth
        //
        registerProperty
        ("videoCodecWidth", make_property(this,
         &Derives::get_videoCodecWidth, &Derives::set_videoCodecWidth));
    
        // videoCodecHeight
        //
        registerProperty
        ("videoCodecHeight", make_property(this,
         &Derives::get_videoCodecHeight, &Derives::set_videoCodecHeight));
    
        // videoCodecFrameRate
        //
        registerProperty
        ("videoCodecFrameRate", make_property(this,
         &Derives::get_videoCodecFrameRate, &Derives::set_videoCodecFrameRate));
    
        // videoCodecMinBitrate
        //
        registerProperty
        ("videoCodecMinBitrate", make_property(this,
         &Derives::get_videoCodecMinBitrate, &Derives::set_videoCodecMinBitrate));
    
        // stunServerHost
        //
        registerProperty
        ("stunServerHost", make_property(this,
         &Derives::get_stunServerHost, &Derives::set_stunServerHost));
    
        // stunServerPort
        //
        registerProperty
        ("stunServerPort", make_property(this,
         &Derives::get_stunServerPort, &Derives::set_stunServerPort));
    
        // relayUDPServerHost
        //
        registerProperty
        ("relayUDPServerHost", make_property(this,
         &Derives::get_relayUDPServerHost, &Derives::set_relayUDPServerHost));
    
        // relayUDPServerPort
        //
        registerProperty
        ("relayUDPServerPort", make_property(this,
         &Derives::get_relayUDPServerPort, &Derives::set_relayUDPServerPort));
    
        // relayTCPServerHost
        //
        registerProperty
        ("relayTCPServerHost", make_property(this,
         &Derives::get_relayTCPServerHost, &Derives::set_relayTCPServerHost));
    
        // relayTCPServerPort
        //
        registerProperty
        ("relayTCPServerPort", make_property(this,
         &Derives::get_relayTCPServerPort, &Derives::set_relayTCPServerPort));
    
        // relaySSLServerHost
        //
        registerProperty
        ("relaySSLServerHost", make_property(this,
         &Derives::get_relaySSLServerHost, &Derives::set_relaySSLServerHost));
    
        // relaySSLServerPort
        //
        registerProperty
        ("relaySSLServerPort", make_property(this,
         &Derives::get_relaySSLServerPort, &Derives::set_relaySSLServerPort));
    
        //
        // read only properties
        //

        // version
        //
        registerProperty
        ("version", make_property(this,
         &Derives::get_version));
    
        // state
        //
        registerProperty
        ("state", make_property(this,
         &Derives::get_state));
    
        // availablePeers
        //
        registerProperty
        ("availablePeers", make_property(this,
         &Derives::get_availablePeers));
    
        // connectedPeer
        //
        registerProperty
        ("connectedPeer", make_property(this,
         &Derives::get_connectedPeer));
    
        // connectedPeerId
        //
        registerProperty
        ("connectedPeerId", make_property(this,
         &Derives::get_connectedPeerId));
    
    }
#endif // !defined(XOS_WEBRTC_PEERCONNECTION_CLIENT_FIREBREATH_PLUGINJAVASCRIPTAPI_MEMBERS_ONLY)

    //
    // methods
    //

    // Start
    //
    virtual void Start(const std::string& mediaType)
    { Implements* delegated;
      if ((delegated = Delegated()))
          delegated->Start(mediaType); }
        
    // Signin
    //
    virtual void Signin
    (const std::string& serverName, const std::string& serverIP, int serverPort)
    { Implements* delegated;
      if ((delegated = Delegated()))
          delegated->Signin
          (serverName, serverIP, serverPort); }
        
    // Signout
    //
    virtual void Signout()
    { Implements* delegated;
      if ((delegated = Delegated()))
          delegated->Signout(); }
        
    // Call
    //
    virtual void Call(const std::string& peerName)
    { Implements* delegated;
      if ((delegated = Delegated()))
          delegated->Call(peerName); }
        
    // Hangup
    //
    virtual void Hangup(const std::string& peerName)
    { Implements* delegated;
      if ((delegated = Delegated()))
          delegated->Hangup(peerName); }
        

#if !defined(XOS_WEBRTC_PEERCONNECTION_CLIENT_FIREBREATH_PLUGINJAVASCRIPTAPI_MEMBERS_ONLY)
#else // !defined(XOS_WEBRTC_PEERCONNECTION_CLIENT_FIREBREATH_PLUGINJAVASCRIPTAPI_MEMBERS_ONLY)
    ////////////////////////////////////////////////////////////////////////
    ///  Function: RegisterMethods
    ///
    ///    Author: $author$
    ///      Date: 1/17/2013
    ////////////////////////////////////////////////////////////////////////
    virtual void RegisterMethods()
    {

        // Start
        //
        registerMethod
        ("Start", make_method
         (this, &Derives::Start));

        // Signin
        //
        registerMethod
        ("Signin", make_method
         (this, &Derives::Signin));

        // Signout
        //
        registerMethod
        ("Signout", make_method
         (this, &Derives::Signout));

        // Call
        //
        registerMethod
        ("Call", make_method
         (this, &Derives::Call));

        // Hangup
        //
        registerMethod
        ("Hangup", make_method
         (this, &Derives::Hangup));
    }
#endif // !defined(XOS_WEBRTC_PEERCONNECTION_CLIENT_FIREBREATH_PLUGINJAVASCRIPTAPI_MEMBERS_ONLY)


#if !defined(XOS_WEBRTC_PEERCONNECTION_CLIENT_FIREBREATH_PLUGINJAVASCRIPTAPI_MEMBERS_ONLY)
    ////////////////////////////////////////////////////////////////////////
    ///  Class: EventsInterface
    ///
    /// Author: $author$
    ///   Date: 1/17/2013
    ////////////////////////////////////////////////////////////////////////
    class _EXPORT_CLASS EventsInterface
    {
    public:

        // onSignedIn
        //
        virtual void onSignedIn(const std::string& eventData)
        { }

        // onSignedOut
        //
        virtual void onSignedOut(const std::string& eventData)
        { }

        // onPeerOnline
        //
        virtual void onPeerOnline(const std::string& eventData)
        { }

        // onPeerOffline
        //
        virtual void onPeerOffline(const std::string& eventData)
        { }

        // onRemotePeerCall
        //
        virtual void onRemotePeerCall(const std::string& eventData)
        { }

        // onRemotePeerHangup
        //
        virtual void onRemotePeerHangup(const std::string& eventData)
        { }

        // onRendererAdd
        //
        virtual void onRendererAdd(const std::string& eventData)
        { }

        // onRendererRemove
        //
        virtual void onRendererRemove(const std::string& eventData)
        { }

        // onFailedToConnectToServer
        //
        virtual void onFailedToConnectToServer(const std::string& server)
        { }

        // onMessageFromPeer
        //
        virtual void onMessageFromPeer(const std::string& message)
        { }

        // onChangeState
        //
        virtual void onChangeState(const std::string& toState)
        { }

        // onEvent
        //
        virtual void onEvent(const std::string& eventName)
        { }
    };
#else // !defined(XOS_WEBRTC_PEERCONNECTION_CLIENT_FIREBREATH_PLUGINJAVASCRIPTAPI_MEMBERS_ONLY)
    //
    // event helpers
    //

    // onSignedIn
    //
    FB_JSAPI_EVENT(SignedIn, 1, (const std::string&));

    // onSignedOut
    //
    FB_JSAPI_EVENT(SignedOut, 1, (const std::string&));

    // onPeerOnline
    //
    FB_JSAPI_EVENT(PeerOnline, 1, (const std::string&));

    // onPeerOffline
    //
    FB_JSAPI_EVENT(PeerOffline, 1, (const std::string&));

    // onRemotePeerCall
    //
    FB_JSAPI_EVENT(RemotePeerCall, 1, (const std::string&));

    // onRemotePeerHangup
    //
    FB_JSAPI_EVENT(RemotePeerHangup, 1, (const std::string&));

    // onRendererAdd
    //
    FB_JSAPI_EVENT(RendererAdd, 1, (const std::string&));

    // onRendererRemove
    //
    FB_JSAPI_EVENT(RendererRemove, 1, (const std::string&));

    // onFailedToConnectToServer
    //
    FB_JSAPI_EVENT(FailedToConnectToServer, 1, (const std::string&));

    // onMessageFromPeer
    //
    FB_JSAPI_EVENT(MessageFromPeer, 1, (const std::string&));

    // onChangeState
    //
    FB_JSAPI_EVENT(ChangeState, 1, (const std::string&));

    // onEvent
    //
    FB_JSAPI_EVENT(Event, 1, (const std::string&));

    //
    // event fires
    //

    // onSignedIn
    //
    virtual void onSignedIn(const std::string& eventData)
    { fire_SignedIn(eventData); }

    // onSignedOut
    //
    virtual void onSignedOut(const std::string& eventData)
    { fire_SignedOut(eventData); }

    // onPeerOnline
    //
    virtual void onPeerOnline(const std::string& eventData)
    { fire_PeerOnline(eventData); }

    // onPeerOffline
    //
    virtual void onPeerOffline(const std::string& eventData)
    { fire_PeerOffline(eventData); }

    // onRemotePeerCall
    //
    virtual void onRemotePeerCall(const std::string& eventData)
    { fire_RemotePeerCall(eventData); }

    // onRemotePeerHangup
    //
    virtual void onRemotePeerHangup(const std::string& eventData)
    { fire_RemotePeerHangup(eventData); }

    // onRendererAdd
    //
    virtual void onRendererAdd(const std::string& eventData)
    { fire_RendererAdd(eventData); }

    // onRendererRemove
    //
    virtual void onRendererRemove(const std::string& eventData)
    { fire_RendererRemove(eventData); }

    // onFailedToConnectToServer
    //
    virtual void onFailedToConnectToServer(const std::string& server)
    { fire_FailedToConnectToServer(server); }

    // onMessageFromPeer
    //
    virtual void onMessageFromPeer(const std::string& message)
    { fire_MessageFromPeer(message); }

    // onChangeState
    //
    virtual void onChangeState(const std::string& toState)
    { fire_ChangeState(toState); }

    // onEvent
    //
    virtual void onEvent(const std::string& eventName)
    { fire_Event(eventName); }
#endif // !defined(XOS_WEBRTC_PEERCONNECTION_CLIENT_FIREBREATH_PLUGINJAVASCRIPTAPI_MEMBERS_ONLY)

#if !defined(XOS_WEBRTC_PEERCONNECTION_CLIENT_FIREBREATH_PLUGINJAVASCRIPTAPI_MEMBERS_ONLY)
};

} // namespace firebreath 
} // namespace client 
} // namespace peerconnection 
} // namespace webrtc 
} // namespace xos 

#else // !defined(XOS_WEBRTC_PEERCONNECTION_CLIENT_FIREBREATH_PLUGINJAVASCRIPTAPI_MEMBERS_ONLY)
#endif // !defined(XOS_WEBRTC_PEERCONNECTION_CLIENT_FIREBREATH_PLUGINJAVASCRIPTAPI_MEMBERS_ONLY)

#endif // !defined(_XOS_WEBRTC_PEERCONNECTION_CLIENT_FIREBREATH_PLUGINJAVASCRIPTAPI_HPP) || defined(XOS_WEBRTC_PEERCONNECTION_CLIENT_FIREBREATH_PLUGINJAVASCRIPTAPI_MEMBERS_ONLY)
