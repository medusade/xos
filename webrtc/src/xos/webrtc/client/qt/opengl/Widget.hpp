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
///   File: Widget.hpp
///
/// Author: $author$
///   Date: 2/23/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_WEBRTC_CLIENT_QT_OPENGL_WIDGET_HPP
#define _XOS_WEBRTC_CLIENT_QT_OPENGL_WIDGET_HPP

#include "xos/gui/qt/Gui.hpp"
#include "xos/gui/opengl/ImageRenderer.hpp"
#include "xos/webrtc/client/PluginInterface.hpp"

namespace xos {
namespace webrtc {
namespace client {
namespace qt {
namespace opengl {

typedef QGLWidget WidgetExtend;
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Widget: public WidgetExtend {
public:
    typedef WidgetExtend Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Widget
    (PluginInterface* plugin, QWidget* parent, const QColor& bgColor)
    : Extends(parent), m_plugin(plugin), m_bgColor(bgColor) {
    }
    virtual ~Widget() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void Invalidate() {
        int width = this->width();
        int height = this->height();
        update(0,0, width,height);
    }
    virtual void Resize() {
        int width = this->width();
        int height = this->height();
        resizeGL(width, height);
        update(0,0, width,height);
    }
    virtual void Show() {
        int width = this->width();
        int height = this->height();
        resizeGL(width, height);
        show();
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void initializeGL() {
        m_openglRenderer.Prepare();
    }
    virtual void resizeGL(int w, int h) {
        m_openglRenderer.Reshape(w, h);
    }
    virtual void paintGL() {
        if ((m_plugin)) {
            uint8_t *remoteImage, *localImage;
            int remoteImageFormat, localImageFormat;
            int remoteImageWidth, remoteImageHeight;
            int localImageWidth, localImageHeight;

            if ((remoteImage = m_plugin->AcquireRemoteImage
                (remoteImageWidth, remoteImageHeight, remoteImageFormat))) 
            {
                if ((localImage = m_plugin->AcquireLocalImage
                    (localImageWidth, localImageHeight, localImageFormat))) 
                {
                    m_openglRenderer.Render
                    (remoteImage, remoteImageWidth, remoteImageHeight,
                     localImage, localImageWidth, localImageHeight);
                    m_plugin->ReleaseLocalImage(localImage);
                } else {
                    m_openglRenderer.Render
                    (remoteImage, remoteImageWidth, remoteImageHeight);
                }
                m_plugin->ReleaseRemoteImage(remoteImage);
                m_openglRenderer.SwapBuffers();
            } else {
                if ((localImage = m_plugin->AcquireLocalImage
                    (localImageWidth, localImageHeight, localImageFormat))) 
                {
                    m_openglRenderer.Render
                    (localImage, localImageWidth, localImageHeight);
                    m_plugin->ReleaseLocalImage(localImage);
                    m_openglRenderer.SwapBuffers();
                } else {
                    PaintBackground();
                }
            }
        } else {
            PaintBackground();
        }
    }
    virtual void PaintBackground() {
        int width = this->width();
        int height = this->height();
        QPainter qp(this);
        QRect rc(0,0, width, height);
        qp.fillRect(rc, m_bgColor);
    }

protected:
    PluginInterface* m_plugin;
    QColor m_bgColor;
    gui::opengl::ImageRenderer m_openglRenderer;
};

} // namespace opengl 
} // namespace qt 
} // namespace client 
} // namespace webrtc 
} // namespace xos 

#endif // _XOS_WEBRTC_CLIENT_QT_OPENGL_WIDGET_HPP 
