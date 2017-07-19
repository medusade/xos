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
///   File: PluginInterface.hpp
///
/// Author: $author$
///   Date: 8/2/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_APP_WEBRTC_CLIENT_PLUGININTERFACE_HPP
#define _XOS_APP_WEBRTC_CLIENT_PLUGININTERFACE_HPP

#include "app/webrtc/client/firebreath/JavaScriptAPI.hpp"
#include "app/webrtc/client/ImageInterface.hpp"
#include "app/webrtc/client/EventInterface.hpp"

namespace xos {
namespace app {
namespace webrtc {
namespace client {

typedef firebreath::JavaScriptAPI PluginInterfaceImplement;
typedef ImageInterface PluginImageInterfaceImplement;
typedef EventInterface PluginEventInterfaceImplement;
///////////////////////////////////////////////////////////////////////
///  Class: PluginInterface
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS PluginInterface
: virtual public PluginInterfaceImplement,
  virtual public PluginImageInterfaceImplement,
  virtual public PluginEventInterfaceImplement {
public:
    typedef PluginInterfaceImplement Implements;
    typedef PluginImageInterfaceImplement ImageImplements;
    typedef PluginEventInterfaceImplement EventImplements;

    typedef PluginImageInterfaceImplement::Image Image;
    typedef PluginImageInterfaceImplement::Format ImageFormat;

    ///////////////////////////////////////////////////////////////////////
    ///  Class: UserInterface
    ///////////////////////////////////////////////////////////////////////
    class _EXPORT_CLASS UserInterface: virtual public InterfaceBase {
    public:
    };
    virtual bool AttachUserInterface(UserInterface* userInterface = 0) {
        return false;
    }
    virtual bool DetachUserInterface(UserInterface* userInterface = 0) {
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    // connection to server
    ///////////////////////////////////////////////////////////////////////
    virtual bool ConnectToServer(const std::string& serverName, int serverPort) {
        return false;
    }
    virtual bool ConnectToServer(const std::string& serverName) {
        return false;
    }
    virtual bool ConnectToServer() {
        return false;
    }
    virtual bool DisconnectFromServer() { 
        return false; 
    }
    virtual void SetServerName(const std::string& serverName) { 
    }
    virtual void SetServerPort(int serverPort) {
    }

    ///////////////////////////////////////////////////////////////////////
    // connection to peer
    ///////////////////////////////////////////////////////////////////////
    virtual bool ConnectToPeer(const std::string& peerName) {
        return false;
    }
    virtual bool ConnectToPeer(int peerId) {
        return false;
    }
    virtual bool ConnectToPeer() {
        return false;
    }
    virtual bool DisconnectFromPeer() { 
        return false; 
    }
    virtual void SetAutoConnectToPeerOn(bool isTrue=true) {
    }
    virtual bool GetAutoConnectToPeerOn() const {
        return false; 
    }
    virtual void SetAutoConnectToPeerAfterOn(bool isTrue=true) {
    }
    virtual bool GetAutoConnectToPeerAfterOn() const {
        return false; 
    }

    ///////////////////////////////////////////////////////////////////////
    // Acquire/Release instance
    ///////////////////////////////////////////////////////////////////////
    static PluginInterface* AcquireInstance();
    static bool ReleaseInstance(PluginInterface* plugin);
};

} // namespace client 
} // namespace webrtc 
} // namespace app 
} // namespace xos 

#endif // _XOS_APP_WEBRTC_CLIENT_PLUGININTERFACE_HPP 
