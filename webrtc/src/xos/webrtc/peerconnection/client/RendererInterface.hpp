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
///   File: RendererInterface.hpp
///
/// Author: $author$
///   Date: 1/9/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_WEBRTC_PEERCONNECTION_CLIENT_RENDERERINTERFACE_HPP
#define _XOS_WEBRTC_PEERCONNECTION_CLIENT_RENDERERINTERFACE_HPP

#include "xos/webrtc/peerconnection/client/UserInterface.hpp"

namespace xos {
namespace webrtc {
namespace peerconnection {
namespace client {

class _EXPORT_CLASS GCRenderer;
class _EXPORT_CLASS OpenGLRenderer;
class _EXPORT_CLASS VideoRenderer;
///////////////////////////////////////////////////////////////////////
///  Class: RendererInterface
///
/// Author: $author$
///   Date: 1/9/2013
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS RendererInterface
{
public:
    virtual VideoRenderer* AcquireVideoRenderer
    (webrtc::VideoTrackInterface* track_to_render,
     size_t width, size_t height, bool isRemote=false) {
        VideoRenderer* renderer = 0;
        RendererInterface* delegated;
        if ((delegated = RendererInterfaceDelegated()))
            return delegated->AcquireVideoRenderer
            (track_to_render, width, height, isRemote);
        return renderer;
    }
    virtual bool ReleaseVideoRenderer(VideoRenderer* renderer) {
        bool isSuccess = false;
        RendererInterface* delegated;
        if ((delegated = RendererInterfaceDelegated()))
            return delegated->ReleaseVideoRenderer(renderer);
        return isSuccess;
    }

    virtual OpenGLRenderer* AcquireOpenGLRenderer() {
        OpenGLRenderer* renderer = 0;
        RendererInterface* delegated;
        if ((delegated = RendererInterfaceDelegated()))
            return delegated->AcquireOpenGLRenderer();
        return renderer;
    }
    virtual bool ReleaseOpenGLRenderer(OpenGLRenderer* renderer) {
        bool isSuccess = false;
        RendererInterface* delegated;
        if ((delegated = RendererInterfaceDelegated()))
            return delegated->ReleaseOpenGLRenderer(renderer);
        return isSuccess;
    }

    virtual GCRenderer* AcquireGCRenderer() {
        GCRenderer* renderer = 0;
        RendererInterface* delegated;
        if ((delegated = RendererInterfaceDelegated()))
            return delegated->AcquireGCRenderer();
        return renderer;
    }
    virtual bool ReleaseGCRenderer(GCRenderer* renderer) {
        bool isSuccess = false;
        RendererInterface* delegated;
        if ((delegated = RendererInterfaceDelegated()))
            return delegated->ReleaseGCRenderer(renderer);
        return isSuccess;
    }

    virtual RendererInterface* RendererInterfaceDelegated() const {
        return 0;
    }
};

} // namespace client 
} // namespace peerconnection 
} // namespace webrtc 
} // namespace xos 

#endif // _XOS_WEBRTC_PEERCONNECTION_CLIENT_RENDERERINTERFACE_HPP 
