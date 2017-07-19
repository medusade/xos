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
///   File: GLVideoView.hpp
///
/// Author: $author$
///   Date: 8/1/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_APP_WEBRTC_CLIENT_GUI_QT_GLVIDEOVIEW_HPP
#define _XOS_APP_WEBRTC_CLIENT_GUI_QT_GLVIDEOVIEW_HPP

#include "app/webrtc/client/gui/qt/VideoView.hpp"
#include "app/webrtc/client/PluginInterface.hpp"
#include "xos/gui/opengl/ImageRenderer.hpp"

namespace xos {
namespace app {
namespace webrtc {
namespace client {
namespace gui {
namespace qt {

typedef VideoWidgetT
<PluginInterface::Image, 
 PluginInterface::ImageFormat,
 xos::gui::opengl::ImageRenderer,  
 PluginInterface, QGLWidget> GLVideoWidgetExtend;
///////////////////////////////////////////////////////////////////////
///  Class: GLVideoWidget
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS GLVideoWidget: public GLVideoWidgetExtend {
public:
    typedef GLVideoWidgetExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: GLVideoWidget
    ///////////////////////////////////////////////////////////////////////
    GLVideoWidget(PluginInterface& plugin, QWidget* parent)
    : Extends(plugin, parent) {
    }
    virtual ~GLVideoWidget() {
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void initializeGL() {
        m_renderer.Prepare();
    }
    virtual void resizeGL(int width, int height) {
        m_renderer.Reshape(width, height);
    }
    virtual void paintGL() {
        m_painter.PaintRenderer(m_renderer);
    }
};
/*
typedef GLVideoWidget GLVideoView;
*/
typedef VideoViewT<PluginInterface, GLVideoWidget, QWidget> GLVideoViewExtend;
///////////////////////////////////////////////////////////////////////
///  Class: GLVideoView
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS GLVideoView: public GLVideoViewExtend {
Q_OBJECT
public:
    typedef GLVideoViewExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: GLVideoView
    ///////////////////////////////////////////////////////////////////////
    GLVideoView(Plugin& plugin, QWidget* parent)
    : Extends(plugin, parent) {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Init() {
        if ((Extends::Init())) {
            connect(m_disconnectButton, SIGNAL(released()), this, SLOT(disconnectButtonReleased()));
            return true;
        }
        return false;
    }
protected slots:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void disconnectButtonReleased() {
        m_plugin.DisconnectFromPeer();
    }
};

} // namespace qt 
} // namespace gui 
} // namespace client 
} // namespace webrtc 
} // namespace app 
} // namespace xos 

#endif // _XOS_APP_WEBRTC_CLIENT_GUI_QT_GLVIDEOVIEW_HPP 
