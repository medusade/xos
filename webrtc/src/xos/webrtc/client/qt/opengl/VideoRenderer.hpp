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
///   Date: 2/23/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_WEBRTC_CLIENT_QT_OPENGL_VIDEORENDERER_HPP
#define _XOS_WEBRTC_CLIENT_QT_OPENGL_VIDEORENDERER_HPP

#include "xos/webrtc/client/OpenGL.hpp"
#include <QtOpenGL>

namespace xos {
namespace webrtc {
namespace client {
namespace qt {
namespace opengl {

typedef client::opengl::VideoRendererImplement VideoRendererImplement;
typedef client::opengl::VideoRenderer VideoRendererExtend;
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS VideoRenderer
: virtual public VideoRendererImplement, public VideoRendererExtend {
public:
    typedef VideoRendererImplement Implements;
    typedef VideoRendererExtend Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    VideoRenderer(): m_widget(0), m_glContext(0) {
    }
    virtual ~VideoRenderer() {
    }

    virtual bool Init(QWidget* widget) {
        if ((m_widget = widget)) {
            QGLFormat glFormat
            (QGL::DoubleBuffer | QGL::Rgba | QGL::NoOverlay 
             | QGL::NoAccumBuffer | QGL::NoStencilBuffer 
             | QGL::NoStereoBuffers | QGL::NoSampleBuffers);
            if ((m_glContext = new QGLContext(glFormat, widget))) {
                if ((m_glContext->create())) {
                    m_glContext->makeCurrent();
                    Prepare();
                    return true;
                }
                delete m_glContext;
                m_glContext = 0;
            }
            m_widget = 0;
        }
        return false;
    }
    virtual bool Finish() {
        if ((m_widget)) {
            if ((m_glContext)) {
                m_glContext->doneCurrent();
                delete m_glContext;
                m_glContext = 0;
            }
            m_widget = 0;
        }
        return false;
    }
    virtual void SwapBuffers() {
        if ((m_glContext)) {
            m_glContext->swapBuffers();
        }
    }
    using Extends::Reshape;
    virtual void Reshape() {
        if ((m_widget) && (m_glContext)) {
            int width = m_widget->width();
            int height = m_widget->height();
            Reshape(width, height);
        }
    }

protected:
    QWidget* m_widget;
    QGLContext* m_glContext;
};

} // namespace opengl 
} // namespace qt 
} // namespace client 
} // namespace webrtc 
} // namespace xos 

#endif // _XOS_WEBRTC_CLIENT_QT_OPENGL_VIDEORENDERER_HPP 
