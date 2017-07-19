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
///   File: OpenGL.hpp
///
/// Author: $author$
///   Date: 1/14/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOWS_OPENGL_HPP
#define _XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOWS_OPENGL_HPP

#include "xos/webrtc/peerconnection/client/OpenGL.hpp"
#include "xos/gui/opengl/windows/Context.hpp"

namespace xos {
namespace webrtc {
namespace peerconnection {
namespace client {
namespace windows {

typedef gui::opengl::windows::Context OpenGLContext;
typedef client::OpenGLRenderer OpenGLRendererExtend;
///////////////////////////////////////////////////////////////////////
///  Class: OpenGLRenderer
///
/// Author: $author$
///   Date: 1/14/2013
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS OpenGLRenderer: public OpenGLRendererExtend {
public:
    typedef OpenGLRendererExtend Extends;

    OpenGLRenderer() {
    }
    virtual ~OpenGLRenderer() {
    }

    virtual bool Init(HWND hWnd) {
        xos::gui::opengl::ContextImplemented impl(hWnd);
        if ((Init(impl))) {
            return true;
        }
        return false; 
    }
    virtual bool Finish(HWND hWnd) {
        xos::gui::opengl::ContextImplemented impl(hWnd);
        if ((Finish(impl))) {
            return true;
        }
        return false; 
    }

    virtual bool Init(xos::gui::opengl::ContextImplemented& impl) { 
        if ((m_context.Init(impl))) {
            Prepare();
            return true;
        }
        return false; 
    }
    virtual bool Finish(xos::gui::opengl::ContextImplemented& impl) { 
        if ((m_context.Finish(impl))) {
            return true;
        }
        return false; 
    }

    virtual void SwapBuffers() {
        m_context.SwapBuffers();
    }

protected:
    OpenGLContext m_context;
};

} // namespace windows 
} // namespace client 
} // namespace peerconnection 
} // namespace webrtc 
} // namespace xos 

#endif // _XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOWS_OPENGL_HPP 
        

