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
///   File: OpenGL.hh
///
/// Author: $author$
///   Date: 12/26/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_WEBRTC_PEERCONNECTION_CLIENT_COCOA_OPENGL_HH
#define _XOS_WEBRTC_PEERCONNECTION_CLIENT_COCOA_OPENGL_HH

#include "xos/webrtc/peerconnection/client/OpenGL.hpp"
#include "xos/gui/opengl/cocoa/Context.hh"

namespace xos {
namespace webrtc {
namespace peerconnection {
namespace client {
namespace cocoa {

///////////////////////////////////////////////////////////////////////
///  Class: OpenGL
///
/// Author: $author$
///   Date: 12/26/2012
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS OpenGL {
public:

///////////////////////////////////////////////////////////////////////
///  Class: VideoRenderer
///
/// Author: $author$
///   Date: 12/26/2012
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS VideoRenderer: public client::OpenGL::VideoRenderer {
public:
    typedef client::OpenGL::VideoRenderer Extends;

    xos::gui::opengl::cocoa::Context m_context;

    VideoRenderer() {}
    virtual ~VideoRenderer() {}

    virtual bool Init(xos::gui::opengl::ContextImplemented& impl) { 
        return m_context.Init(impl); 
    }
    virtual bool Finish(xos::gui::opengl::ContextImplemented& impl) { 
        return m_context.Finish(impl); 
    }

    virtual void SwapBuffers() {
#if defined(OBJC) 
        NSOpenGLContext* glContext;
        if ((glContext = m_context.GetContext())) {
            [glContext flushBuffer];
        }
#else // defined(OBJC) 
#endif // defined(OBJC) 
    }
};

};

} // namespace cocoa 
} // namespace client 
} // namespace peerconnection 
} // namespace webrtc 
} // namespace xos 


#endif // _XOS_WEBRTC_PEERCONNECTION_CLIENT_COCOA_OPENGL_HH 
        

