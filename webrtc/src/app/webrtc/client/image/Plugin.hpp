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
///   File: Plugin.hpp
///
/// Author: $author$
///   Date: 8/2/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_APP_WEBRTC_CLIENT_IMAGE_PLUGIN_HPP
#define _XOS_APP_WEBRTC_CLIENT_IMAGE_PLUGIN_HPP

#include "app/webrtc/client/PluginInterface.hpp"
#include "app/gui/hello/Image.hpp"

namespace xos {
namespace app {
namespace webrtc {
namespace client {
namespace image {

typedef PluginInterface PluginImplementImplement;
///////////////////////////////////////////////////////////////////////
///  Class: PluginImplement
///////////////////////////////////////////////////////////////////////
class c_EXPORT_CLASS PluginImplement
: virtual public PluginImplementImplement,
  virtual public ImageObserverInterface,
  virtual public EventObserverInterface {
public:
    typedef PluginImplementImplement Implements;
};
typedef gui::hello::ImageT<PluginImplement, ExportBase> PluginExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Plugin
///////////////////////////////////////////////////////////////////////
class c_EXPORT_CLASS Plugin
: virtual public PluginImplement, public PluginExtend {
public:
    typedef PluginImplement Implements;
    typedef PluginExtend cExtends;
    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: Plugin
    ///////////////////////////////////////////////////////////////////////
    Plugin(): m_imageObserver(0), m_eventObserver(0) {
    }
    virtual ~Plugin() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool AttachUserInterface(UserInterface* userInterface = 0) {
        return true;
    }
    virtual bool DetachUserInterface(UserInterface* userInterface = 0) {
        return true;
    }

    ///////////////////////////////////////////////////////////////////////
    // Register/Unregister and Delegated ImageObserver
    ///////////////////////////////////////////////////////////////////////
    virtual void RegisterImageObserver(ImageObserverInterface* observer) {
        ImageInterface* imageInterface;
        if ((imageInterface = ImageInterfaceDelegated()))
            imageInterface->RegisterImageObserver(observer);
        else {
            m_imageObserver = observer;
        }
    }
    virtual void UnregisterImageObserver(ImageObserverInterface* observer) {
        ImageInterface* imageInterface;
        if ((imageInterface = ImageInterfaceDelegated()))
            imageInterface->UnregisterImageObserver(observer);
        else if ((observer) && (m_imageObserver == observer)) {
            m_imageObserver = 0;
        }
    }
    virtual ImageObserverInterface* ImageObserverInterfaceDelegated() const {
        return m_imageObserver;
    }

    ///////////////////////////////////////////////////////////////////////
    // Register/Unregister and Delegated EventObserver
    ///////////////////////////////////////////////////////////////////////
    virtual void RegisterEventObserver
    (EventObserverInterface* observer) {
        EventInterface* delegated;
        if ((delegated = EventInterfaceDelegated()))
            delegated->RegisterEventObserver(observer);
        else {
            m_eventObserver = observer;
        }
    }
    virtual void UnregisterEventObserver
    (EventObserverInterface* observer) {
        EventInterface* delegated;
        if ((delegated = EventInterfaceDelegated()))
            delegated->UnregisterEventObserver(observer);
        else if ((observer) && (m_eventObserver == observer)) {
            m_eventObserver = 0;
        }
    }
    virtual EventObserverInterface* EventObserverInterfaceDelegated() const {
        return m_eventObserver;
    }

    ///////////////////////////////////////////////////////////////////////
    // connection to server
    ///////////////////////////////////////////////////////////////////////
    virtual bool ConnectToServer(const std::string& serverName, int serverPort) {
        if ((0 < (serverName.length())) && (0 < (serverPort))) {
            return ConnectToServer();
        }
        return false;
    }
    virtual bool ConnectToServer(const std::string& serverName) {
        if ((0 < (serverName.length()))) {
            return ConnectToServer();
        }
        return false;
    }
    virtual bool ConnectToServer() {
        if ((ChangeStateToListPeers()))
            return true;
        return false;
    }
    virtual bool DisconnectFromServer() { 
        OnChangeStateToConnectToServer();
        return false; 
    }

    ///////////////////////////////////////////////////////////////////////
    // connection to peer
    ///////////////////////////////////////////////////////////////////////
    virtual bool ConnectToPeer(const std::string& peerName) {
        if ((LoadImageFile(peerName))) {
            OnChangeStateToStreaming();
            return true;
        }
        return false;
    }
    virtual bool ConnectToPeer(int peerId) {
        if (1 == (peerId))
            return ConnectToPeer();
        return false;
    }
    virtual bool ConnectToPeer() {
        if ((LoadImageFile())) {
            OnChangeStateToStreaming();
            return true;
        }
        return false;
    }
    virtual bool DisconnectFromPeer() { 
        if ((ChangeStateToListPeers()))
            return true;
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
    ///////////////////////////////////////////////////////////////////////
    virtual void* AcquireRemoteImage(int& width, int& height, Format& format) {
        void* image = 0;
        if ((image = ImageLodaed())) {
            width = m_imageWidth;
            height = m_imageHeight;
            format = FORMAT_GL_BGRA;
        }
        return image;
    }
    virtual bool ReleaseRemoteImage(void* image) {
        bool success = (image && (image == m_image));
        return success;
    }
    virtual void* AcquireLocalImage(int& width, int& height, Format& format) {
        void* image = AcquireRemoteImage(width, height, format);
        return image;
    }
    virtual bool ReleaseLocalImage(void* image) {
        bool success = ReleaseRemoteImage(image);
        return success;
    }
    virtual void* ImageLodaed() {
        void* image;
        if (!(image = Image()))
            image = LoadImageFile();
        return image;
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool ChangeStateToListPeers() {
        const char* imageFile;

        OnChangeStateToListPeers();

        if ((imageFile = ImageFile())) {
            std::string fileName(imageFile);

            if (0 < (fileName.length()))
                OnPeerConnectedToServer(1, fileName);
            return true;
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    ImageObserverInterface* m_imageObserver;
    EventObserverInterface* m_eventObserver;
};

} // namespace image 
} // namespace client 
} // namespace webrtc 
} // namespace app 
} // namespace xos 

#endif // _XOS_APP_WEBRTC_CLIENT_IMAGE_PLUGIN_HPP 
