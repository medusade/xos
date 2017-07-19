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
///   File: PlugoutWindowPeer.hpp
///
/// Author: $author$
///   Date: 3/10/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_WEBRTC_CLIENT_CONSOLE_PLUGOUTWINDOWPEER_HPP
#define _XOS_WEBRTC_CLIENT_CONSOLE_PLUGOUTWINDOWPEER_HPP

#include "xos/webrtc/client/PluginInterface.hpp"

namespace xos {
namespace webrtc {
namespace client {

typedef InterfaceBase PluginInterfaceWindowImplement;
typedef ExportBase PluginInterfaceWindowExtend;
///////////////////////////////////////////////////////////////////////
///  Class: PluginInterface::Window
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS PluginInterface::Window
: virtual public PluginInterfaceWindowImplement, public PluginInterfaceWindowExtend {
public:
    typedef PluginInterfaceWindowImplement Implements;
    typedef PluginInterfaceWindowExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: Window
    ///////////////////////////////////////////////////////////////////////
    Window() {}
    virtual ~Window() {}
};

namespace console {

typedef ImageInterface PlugoutWindowPeerImplement;
typedef PluginInterface::Window PlugoutWindowPeerExtend;
///////////////////////////////////////////////////////////////////////
///  Class: PlugoutWindowPeer
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS PlugoutWindowPeer
: virtual public PlugoutWindowPeerImplement, public PlugoutWindowPeerExtend {
public:
    typedef PlugoutWindowPeerImplement Implements;
    typedef PlugoutWindowPeerExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: PlugoutWindowPeer
    ///////////////////////////////////////////////////////////////////////
    PlugoutWindowPeer(): m_plugin(0), m_imageObserver(0) {
    }
    virtual ~PlugoutWindowPeer() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Open() {
        bool success = false;
        if (!(m_plugin))
        if ((success = (0 != (m_plugin = LoadPlugin(m_imageObserver)))))
            m_plugin->AttachWindow(this);
        return success;
    }
    virtual bool Close() {
        bool success = false;
        if ((m_plugin)) {
            m_plugin->DetachWindow(this);
            success = UnloadPlugin(m_plugin);
            m_plugin = 0;
        }
        return success;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool ConnectToServer(const std::string& serverName, int serverPort) {
        bool success = false;
        if ((m_plugin))
            success = m_plugin->ConnectToServer(serverName, serverPort);
        return success;
    }
    virtual bool ConnectToServer() {
        bool success = false;
        if ((m_plugin))
            success = m_plugin->ConnectToServer();
        return success;
    }
    virtual bool DisconnectFromServer() {
        bool success = false;
        if ((m_plugin))
            success = m_plugin->DisconnectFromServer();
        return success;
    }
    virtual void SetAutoConnectToPeerOn(bool isTrue=true) {
        if ((m_plugin)) {
            m_plugin->SetAutoConnectToPeerOn(isTrue);
            m_plugin->SetAutoConnectToPeerAfterOn(isTrue);
        }
    }
    virtual void SetAutoConnectToPeerAfterOn(bool isTrue=true) {
        if ((m_plugin)) {
            m_plugin->SetAutoConnectToPeerAfterOn(isTrue);
        }
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void RegisterImageObserver(ImageObserverInterface* imageObserver) {
        if ((m_plugin)) {
            m_plugin->RegisterImageObserver(imageObserver);
        } else {
            m_imageObserver = imageObserver;
        }
    }
    virtual void UnregisterImageObserver(ImageObserverInterface* imageObserver) {
        if ((m_plugin)) {
            m_plugin->UnregisterImageObserver(imageObserver);
        } else {
            m_imageObserver = 0;
        }
    }
    virtual ImageInterface* ImageInterfaceDelegated() const {
        if ((m_plugin))
            return (ImageInterface*)(m_plugin);
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual PluginInterface* LoadPlugin(ImageObserverInterface* imageObserver = 0) {
        PluginInterface* plugin = 0;
        if ((plugin = PluginInterface::AcquireInstance())) {
            if ((imageObserver))
                plugin->RegisterImageObserver(imageObserver);
        }
        return plugin;
    }
    virtual bool UnloadPlugin
    (PluginInterface* plugin, ImageObserverInterface* imageObserver = 0) {
        bool isSuccess = false;
        if ((plugin)) {
            if ((imageObserver))
                plugin->UnregisterImageObserver(imageObserver);
            isSuccess = PluginInterface::ReleaseInstance(plugin);
        }
        return isSuccess;
    }
protected:
    PluginInterface* m_plugin;
    ImageObserverInterface* m_imageObserver;
};

} // namespace console 
} // namespace client 
} // namespace webrtc 
} // namespace xos 

#endif // _XOS_WEBRTC_CLIENT_CONSOLE_PLUGOUTWINDOWPEER_HPP 
