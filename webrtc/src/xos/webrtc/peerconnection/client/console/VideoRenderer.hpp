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
///   File: VideoRenderer.hpp
///
/// Author: $author$
///   Date: 1/9/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_WEBRTC_PEERCONNECTION_CLIENT_CONSOLE_VIDEORENDERER_HPP
#define _XOS_WEBRTC_PEERCONNECTION_CLIENT_CONSOLE_VIDEORENDERER_HPP

#include "xos/webrtc/peerconnection/client/MainWindow.hpp"
#include "xos/webrtc/peerconnection/client/VideoRenderer.hpp"
#include "xos/os/Mutex.hpp"

namespace xos {
namespace webrtc {
namespace peerconnection {
namespace client {
namespace console {

typedef client::VideoRenderer VideoRendererExtend;
///////////////////////////////////////////////////////////////////////
///  Class: VideoRenderer
///
/// Author: $author$
///   Date: 1/9/2013
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS VideoRenderer: public VideoRendererExtend {
public:
    typedef VideoRendererExtend Extends;

    MainWindow& m_window;
    xos::os::Mutex buffer_lock_;

    VideoRenderer
    (MainWindow& window, webrtc::VideoTrackInterface* track_to_render, 
     size_t width=0, size_t height=0, bool isRemote=false)
    : Extends(track_to_render, width, height, isRemote),
      m_window(window)
    {
        buffer_lock_.Create();
    }
    virtual ~VideoRenderer()
    {
        buffer_lock_.Destroy();
    }
    virtual void UpdateVisibleFrame() 
    { 
        m_window.InvalidateWindow(false); 
    }
    virtual void Lock() { buffer_lock_.Lock(); }
    virtual void Unlock() { buffer_lock_.Unlock(); }
};

} // namespace console 

///////////////////////////////////////////////////////////////////////
///  Class: VideoRendererDerived
///
/// Author: $author$
///   Date: 1/10/2013
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS VideoRendererDerived: public console::VideoRenderer {
public:
    typedef console::VideoRenderer Extends;

    VideoRendererDerived
    (MainWindow& window, webrtc::VideoTrackInterface* track_to_render, 
     size_t width=0, size_t height=0, bool isRemote=false)
    : Extends(window, track_to_render, width, height, isRemote)
    {}
    virtual VideoRendererDerived* RendererDerived() const
    { return (VideoRendererDerived*)(this); }
};

} // namespace client 
} // namespace peerconnection 
} // namespace webrtc 
} // namespace xos 

#endif // _XOS_WEBRTC_PEERCONNECTION_CLIENT_CONSOLE_VIDEORENDERER_HPP 
