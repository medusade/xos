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
///   Date: 8/18/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_APP_WEBRTC_CLIENT_IMAGE_LIB_LIBPNG_PLUGIN_HPP
#define _XOS_APP_WEBRTC_CLIENT_IMAGE_LIB_LIBPNG_PLUGIN_HPP

#include "app/webrtc/client/PluginInterface.hpp"
#include "xos/image/lib/libpng/Reader.hpp"
#include "app/gui/hello/Image.hpp"
#include "xos/fs/os/Directory.hpp"
#include "xos/fs/Path.hpp"

#define XOS_APP_WEBRTC_CLIENT_IMAGE_LIB_LIBPNG_IMAGE_FILENAME "video-frame.png"

namespace xos {
namespace app {
namespace webrtc {
namespace client {
namespace image {
namespace lib {
namespace libpng {

typedef PluginInterface PluginImplementImplement;
///////////////////////////////////////////////////////////////////////
///  Class: PluginImplement
///////////////////////////////////////////////////////////////////////
class c_EXPORT_CLASS PluginImplement
: virtual public PluginImplementImplement,
  virtual public ImageObserverInterface,
  virtual public EventObserverInterface,
  virtual public xos::image::libpng::ReaderEventsImplement {
public:
    typedef PluginImplementImplement Implements;
};
typedef gui::hello::ImageT
<PluginImplement, xos::image::libpng::ReaderEvents> PluginExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Plugin
///////////////////////////////////////////////////////////////////////
class c_EXPORT_CLASS Plugin
: virtual public PluginImplement, public PluginExtend {
using PluginExtend::LoadImageFile;
public:
    typedef PluginImplement Implements;
    typedef PluginExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: Plugin
    ///////////////////////////////////////////////////////////////////////
    Plugin(): m_pngReader(this), m_imageObserver(0), m_eventObserver(0) {
        SetImageFile(m_defaultImageFile = XOS_APP_WEBRTC_CLIENT_IMAGE_LIB_LIBPNG_IMAGE_FILENAME);
    }
    virtual ~Plugin() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool OnPNGPixel
    (Pixel& pixel,
     BYTE* colByte, TSIZE colBytes, TSIZE col, 
     TSIZE row, TSIZE height, TSIZE width, 
     TSIZE bitDepth, TSIZE colorChannels,
     UINT colorType, UINT filterType, 
     UINT interlaceType, UINT compressionType) {
         if ((m_imageByte)) {
             m_imageByte[3] = pixel.alpha();
             m_imageByte[2] = pixel.red();
             m_imageByte[1] = pixel.green();
             m_imageByte[0] = pixel.blue();
         }
         return true;
    }
    virtual bool OnEndPNGCol
    (BYTE* colByte, TSIZE colBytes, TSIZE col, 
     TSIZE row, TSIZE height, TSIZE width, 
     TSIZE bitDepth, TSIZE colorChannels,
     UINT colorType, UINT filterType, 
     UINT interlaceType, UINT compressionType) {
         if ((m_imageByte)) {
             m_imageByte += ImageDepth();
             m_imageCol++;
         }
         return true;
    }
    virtual bool OnEndPNGRow
    (BYTE* rowByte, TSIZE rowBytes, 
     TSIZE row, TSIZE height, TSIZE width, 
     TSIZE bitDepth, TSIZE colorChannels,
     UINT colorType, UINT filterType, 
     UINT interlaceType, UINT compressionType) {
         if ((m_imageByte)) {
             m_imageByte = (m_imageRowByte += (ImageWidth()*ImageDepth()));
             m_imageRow++;
         }
         return true;
    }
    virtual bool OnBeginPNGImage
    (TSIZE height, TSIZE width, 
     TSIZE bitDepth, TSIZE colorChannels,
     UINT colorType, UINT filterType, 
     UINT interlaceType, UINT compressionType) {
         if ((m_imageRowByte = (m_imageByte = (BYTE*)(AllocateImage(width, height, 4))))) {
             memset(m_imageByte, (BYTE)(-1), ImageSize());
             m_imageRow = 0;
             m_imageCol = 0;
         }
         return true;
    }
    virtual bool OnEndPNGImage
    (TSIZE height, TSIZE width, 
     TSIZE bitDepth, TSIZE colorChannels,
     UINT colorType, UINT filterType, 
     UINT interlaceType, UINT compressionType) {
         m_imageRowByte = 0;
         m_imageByte = 0;
         m_imageRow = 0;
         m_imageCol = 0;
         return true;
    }
    BYTE* m_imageRowByte;
    BYTE* m_imageByte;
    TSIZE m_imageRow;
    TSIZE m_imageCol;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void* LoadImageFile(const char* chars) {
        FreeImage();

        if ((chars) && (chars != m_imageFile))
            SetImageFile(chars);

        m_pngReader.Read(chars);
        return m_image;
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
        m_files.clear();
        if ((0 < (serverName.length())) && (0 < (serverPort))) {
            return ConnectToServer(serverName);
        }
        return false;
    }
    virtual bool ConnectToServer(const std::string& serverName) {
        m_files.clear();
        if ((0 < (serverName.length()))) {
            fs::os::Directory directory;
            if ((directory.Open(serverName))) {
                fs::Entry* entry;
                if ((entry = directory.GetFirst())) {
                    do {
                        if (fs::Entry::File == (entry->GetType())) {
                            String fileName(entry->GetName().c_str());
                            fs::Path filePath(fileName.c_str());
                            if ((filePath.Separate())) {
                                String fileExtension(filePath.GetFileExtension());
                                if (!(fileExtension.compare("png"))) {
                                    filePath.AssignDirectory(serverName.c_str());
                                    filePath.AppendDirectory(fileName.c_str());
                                    m_files.push_back(filePath);
                                }
                            }
                        }
                    } while ((entry = directory.GetNext()));
                }
                directory.Close();
            }
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

        if (0 < (m_files.size())) {
            int id;
            Files::const_iterator i;
            for (id = 1, i = m_files.begin(); i != m_files.end(); ++i, ++id) {
                std::string fileName(i->Chars());
                if (0 < (fileName.length()))
                    OnPeerConnectedToServer(id, fileName);
            }
        } else
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
    typedef std::vector<String> Files;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    xos::image::libpng::Reader m_pngReader;
    ImageObserverInterface* m_imageObserver;
    EventObserverInterface* m_eventObserver;
    Files m_files;
};

} // namespace libpng 
} // namespace lib 
} // namespace image 
} // namespace client 
} // namespace webrtc 
} // namespace app 
} // namespace xos 

#endif // _XOS_APP_WEBRTC_CLIENT_IMAGE_LIB_LIBPNG_PLUGIN_HPP 
