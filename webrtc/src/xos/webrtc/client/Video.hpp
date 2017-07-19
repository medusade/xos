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
///   File: Video.hpp
///
/// Author: $author$
///   Date: 10/16/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_WEBRTC_CLIENT_VIDEO_HPP
#define _XOS_WEBRTC_CLIENT_VIDEO_HPP

#include "xos/base/String.hpp"

namespace xos {
namespace webrtc {
namespace client {

class _EXPORT_CLASS Video {
public:
typedef InterfaceBase OptionsInterfaceImplement;

class _EXPORT_CLASS OptionsInterface: virtual public OptionsInterfaceImplement {
public:

    virtual void SetVideoCaptureDevice(const std::string& val) = 0;
    virtual std::string GetVideoCaptureDevice() const = 0;

    virtual void SetVideoCodecModeName(const std::string& toModeName) = 0;
    virtual std::string GetVideoCodecModeName() const = 0;

    virtual void SetVideoCodecOptions
    (int codecWidth, int codecHeight, int frameRate, int minBitrate) = 0;
    virtual void GetVideoCodecOptions
    (int& codecWidth, int& codecHeight, int& frameRate, int& minBitrate) const = 0;
};

class _EXPORT_CLASS OptionsImplement: virtual public OptionsInterface {
public:
    virtual void SetVideoCaptureDevice(const std::string& val) {
        OptionsInterface* delegated = 0;
        if ((delegated = DelegatedVideoOptions())) {
            delegated->SetVideoCaptureDevice(val);
        }
    }
    virtual std::string GetVideoCaptureDevice() const {
        std::string val;
        OptionsInterface* delegated = 0;
        if ((delegated = DelegatedVideoOptions())) {
            val = delegated->GetVideoCaptureDevice();
        }
        return val;
    }

    virtual void SetVideoCodecModeName(const std::string& toModeName) {
        OptionsInterface* delegated = 0;
        if ((delegated = DelegatedVideoOptions())) {
            delegated->SetVideoCodecModeName(toModeName);
        }
    }
    virtual std::string GetVideoCodecModeName() const {
        std::string val;
        OptionsInterface* delegated = 0;
        if ((delegated = DelegatedVideoOptions())) {
            val = delegated->GetVideoCodecModeName();
        }
        return val;
    }

    virtual void SetVideoCodecOptions
    (int codecWidth, int codecHeight, int frameRate, int minBitrate) {
        OptionsInterface* delegated = 0;
        if ((delegated = DelegatedVideoOptions())) {
            delegated->SetVideoCodecOptions(codecWidth, codecHeight, frameRate, minBitrate);
        }
    }
    virtual void GetVideoCodecOptions
    (int& codecWidth, int& codecHeight, int& frameRate, int& minBitrate) const {
        OptionsInterface* delegated = 0;
        if ((delegated = DelegatedVideoOptions())) {
            delegated->GetVideoCodecOptions(codecWidth, codecHeight, frameRate, minBitrate);
        }
    }

    virtual OptionsInterface* DelegateVideoOptions(OptionsInterface* delegated) {
        return 0; }
    virtual OptionsInterface* DelegatedVideoOptions() const {
        return 0; }
};

};

} // namespace client 
} // namespace webrtc 
} // namespace xos 

#endif // _XOS_WEBRTC_CLIENT_VIDEO_HPP 
