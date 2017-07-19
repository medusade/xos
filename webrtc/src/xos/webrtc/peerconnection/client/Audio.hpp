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
///   File: Audio.hpp
///
/// Author: $author$
///   Date: 1/18/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_WEBRTC_PEERCONNECTION_CLIENT_AUDIO_HPP
#define _XOS_WEBRTC_PEERCONNECTION_CLIENT_AUDIO_HPP

#include "xos/base/String.hpp"

enum {
    XOS_WEBRTC_PEERCONNECTION_CLIENT_AUDIO_DEVICE_OPTION_ECHO_CANCELLATION = 1,
    XOS_WEBRTC_PEERCONNECTION_CLIENT_AUDIO_DEVICE_OPTION_NOISE_SUPPRESSION = (1 << 1),
    XOS_WEBRTC_PEERCONNECTION_CLIENT_AUDIO_DEVICE_OPTION_AUTO_GAIN_CONTROL = (1 << 2),

    XOS_WEBRTC_PEERCONNECTION_CLIENT_AUDIO_DEVICE_OPTION_FIRST = 1,
    XOS_WEBRTC_PEERCONNECTION_CLIENT_AUDIO_DEVICE_OPTION_NEXT = (1 << 3),
};

namespace xos {
namespace webrtc {
namespace peerconnection {
namespace client {

class _EXPORT_CLASS Audio {
public:
typedef int DeviceOptions;
typedef InterfaceBase OptionsInterfaceImplement;

class _EXPORT_CLASS OptionsInterface: virtual public OptionsInterfaceImplement {
public:
    virtual void SetAudioDeviceOptions
    (bool echoCancellation, bool noiseSupression, bool autoGainControl) = 0;
    virtual void GetAudioDeviceOptions
    (bool& echoCancellation, bool& noiseSupression, bool& autoGainControl) const = 0;
};

class _EXPORT_CLASS OptionsImplement: virtual public OptionsInterface {
public:
    virtual void SetAudioDeviceOptions
    (bool echoCancellation, bool noiseSupression, bool autoGainControl) {
        OptionsInterface* delegated = 0;
        if ((delegated = DelegatedAudioOptions())) {
            delegated->SetAudioDeviceOptions(echoCancellation, noiseSupression, autoGainControl);
        }
    }
    virtual void GetAudioDeviceOptions
    (bool& echoCancellation, bool& noiseSupression, bool& autoGainControl) const {
        OptionsInterface* delegated = 0;
        if ((delegated = DelegatedAudioOptions())) {
            delegated->GetAudioDeviceOptions(echoCancellation, noiseSupression, autoGainControl);
        }
    }

    virtual OptionsInterface* DelegateAudioOptions(OptionsInterface* delegated) {
        return 0; }
    virtual OptionsInterface* DelegatedAudioOptions() const {
        return 0; }
};

};

} // namespace client 
} // namespace peerconnection 
} // namespace webrtc 
} // namespace xos 

#endif // _XOS_WEBRTC_PEERCONNECTION_CLIENT_AUDIO_HPP 
