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
///   File: AudioVideo.hpp
///
/// Author: $author$
///   Date: 10/16/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_WEBRTC_CLIENT_AUDIOVIDEO_HPP
#define _XOS_WEBRTC_CLIENT_AUDIOVIDEO_HPP

#include "xos/webrtc/client/Audio.hpp"
#include "xos/webrtc/client/Video.hpp"

namespace xos {
namespace webrtc {
namespace client {

class _EXPORT_CLASS AudioVideo {
public:

class _EXPORT_CLASS OptionsInterface
: virtual public Audio::OptionsInterface, 
  virtual public Video::OptionsInterface {
public:
    typedef Audio::OptionsInterface AudioImplements;
    typedef Video::OptionsInterface VideoImplements;
};

class _EXPORT_CLASS OptionsImplement
: virtual public Audio::OptionsImplement, 
  virtual public Video::OptionsImplement,
  virtual public OptionsInterface {
public:
    typedef Audio::OptionsImplement AudioImplements;
    typedef Video::OptionsImplement VideoImplements;
    typedef AudioVideo::OptionsInterface OptionsInterface;

    virtual OptionsInterface* DelegateAudioVideoOptions(OptionsInterface* delegated) {
        return 0; }
    virtual OptionsInterface* DelegatedAudioVideoOptions() const {
        return 0; }
};

typedef ExportBase OptionsExtend;

class _EXPORT_CLASS Options: virtual public OptionsImplement, public OptionsExtend {
public:
    typedef OptionsImplement Implements;
    typedef OptionsExtend Extends;

    Options(): m_delegated(0) {}

    virtual OptionsInterface* DelegateAudioVideoOptions(OptionsInterface* delegated) {
        return m_delegated = delegated; 
    }
    virtual OptionsInterface* DelegatedAudioVideoOptions() const {
       return (OptionsInterface*)(m_delegated); 
    }

    virtual Audio::OptionsInterface* DelegatedAudioOptions() const {
        return (Audio::OptionsInterface*)(m_delegated); 
    }
    virtual Video::OptionsInterface* DelegatedVideoOptions() const {
        return (Video::OptionsInterface*)(m_delegated); 
    }
protected:
    OptionsInterface* m_delegated;
};

};

} // namespace client 
} // namespace webrtc 
} // namespace xos 

#endif // _XOS_WEBRTC_CLIENT_AUDIOVIDEO_HPP 
