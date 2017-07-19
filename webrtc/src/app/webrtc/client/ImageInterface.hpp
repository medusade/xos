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
///   File: ImageInterface.hpp
///
/// Author: $author$
///   Date: 8/2/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_APP_WEBRTC_CLIENT_IMAGEINTERFACE_HPP
#define _XOS_APP_WEBRTC_CLIENT_IMAGEINTERFACE_HPP

#include "xos/base/Base.hpp"

namespace xos {
namespace app {
namespace webrtc {
namespace client {

typedef InterfaceBase ImageObserverInterfaceImplement;
///////////////////////////////////////////////////////////////////////
///  Class: ImageObserverInterface
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS ImageObserverInterface
: virtual public ImageObserverInterfaceImplement {
public:
    typedef ImageObserverInterfaceImplement Implements;

    ///////////////////////////////////////////////////////////////////////
    // Updated Remote/Local images
    ///////////////////////////////////////////////////////////////////////
    virtual bool UpdatedRemoteImage()  { 
        ImageObserverInterface* delegated;
        if ((delegated = ImageObserverInterfaceDelegated()))
            delegated->UpdatedRemoteImage();
        return true; 
    }
    virtual bool UpdatedLocalImage()  { 
        ImageObserverInterface* delegated;
        if ((delegated = ImageObserverInterfaceDelegated()))
            delegated->UpdatedLocalImage();
        return true; 
    }
    virtual bool UpdatedImages()  { 
        ImageObserverInterface* delegated;
        if ((delegated = ImageObserverInterfaceDelegated()))
            delegated->UpdatedImages();
        return true; 
    }

    ///////////////////////////////////////////////////////////////////////
    // delegated
    ///////////////////////////////////////////////////////////////////////
    virtual ImageObserverInterface* ImageObserverInterfaceDelegated() const {
        return 0;
    }
};

typedef InterfaceBase ImageInterfaceImplement;
///////////////////////////////////////////////////////////////////////
///  Class: ImageInterface
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS ImageInterface
: virtual public ImageInterfaceImplement {
public:
    typedef ImageInterfaceImplement Implements;

    typedef void Image;
    typedef int Format;
    enum {
        FORMAT_NONE = 0,
        FORMAT_GL_BGRA,
        FORMAY_GL_RGBA
    };

    ///////////////////////////////////////////////////////////////////////
    // Acquire/Release RemoteImage
    ///////////////////////////////////////////////////////////////////////
    virtual void* AcquireRemoteImage(int& width, int& height, Format& format) {
        void* image = 0;
        ImageInterface* imageInterface;
        if ((imageInterface = ImageInterfaceDelegated()))
            image = imageInterface->AcquireRemoteImage(width, height, format);
        return image;
    }
    virtual bool ReleaseRemoteImage(void* image) {
        bool success = false;
        ImageInterface* imageInterface;
        if ((imageInterface = ImageInterfaceDelegated()))
            success = imageInterface->ReleaseRemoteImage(image);
        return success;
    }

    ///////////////////////////////////////////////////////////////////////
    // Acquire/Release LocalImage
    ///////////////////////////////////////////////////////////////////////
    virtual void* AcquireLocalImage(int& width, int& height, Format& format) {
        void* image = 0;
        ImageInterface* imageInterface;
        if ((imageInterface = ImageInterfaceDelegated()))
            image = imageInterface->AcquireLocalImage(width, height, format);
        return image;
    }
    virtual bool ReleaseLocalImage(void* image) {
        bool success = false;
        ImageInterface* imageInterface;
        if ((imageInterface = ImageInterfaceDelegated()))
            success = imageInterface->ReleaseLocalImage(image);
        return success;
    }

    ///////////////////////////////////////////////////////////////////////
    // Register/Unregister ImageObserver
    ///////////////////////////////////////////////////////////////////////
    virtual void RegisterImageObserver(ImageObserverInterface* observer) {
        ImageInterface* imageInterface;
        if ((imageInterface = ImageInterfaceDelegated()))
            imageInterface->RegisterImageObserver(observer);
    }
    virtual void UnregisterImageObserver(ImageObserverInterface* observer) {
        ImageInterface* imageInterface;
        if ((imageInterface = ImageInterfaceDelegated()))
            imageInterface->UnregisterImageObserver(observer);
    }

    ///////////////////////////////////////////////////////////////////////
    // delegated
    ///////////////////////////////////////////////////////////////////////
    virtual ImageInterface* ImageInterfaceDelegated() const {
        return 0;
    }
};

} // namespace client 
} // namespace webrtc 
} // namespace app 
} // namespace xos 

#endif // _XOS_APP_WEBRTC_CLIENT_IMAGEINTERFACE_HPP 
