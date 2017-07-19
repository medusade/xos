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
///   File: VideoView.hpp
///
/// Author: $author$
///   Date: 8/1/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_APP_WEBRTC_CLIENT_GUI_QT_VIDEOVIEW_HPP
#define _XOS_APP_WEBRTC_CLIENT_GUI_QT_VIDEOVIEW_HPP

#include "xos/gui/qt/ImageRenderer.hpp"
#include "app/webrtc/client/PluginInterface.hpp"

namespace xos {
namespace app {
namespace webrtc {
namespace client {
namespace gui {
namespace qt {

///////////////////////////////////////////////////////////////////////
///  Class: VideoPainterT
///////////////////////////////////////////////////////////////////////
template 
<class TImage, class TImageFormat, class TImageRenderer, 
 class TPlugin, class TExtend = ExportBase>

class _EXPORT_CLASS VideoPainterT: public TExtend {
public:
    typedef TExtend Extends;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: VideoPainterT
    ///////////////////////////////////////////////////////////////////////
    VideoPainterT(TPlugin& plugin)
    : m_plugin(plugin) {
    }
    virtual ~VideoPainterT() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void PaintRenderer(TImageRenderer& m_renderer) {
        TImage* remoteImage; int remoteImageWidth, remoteImageHeight; TImageFormat remoteImageFormat;
        TImage* localImage; int localImageWidth, localImageHeight; TImageFormat localImageFormat;;
        if ((remoteImage = m_plugin.AcquireRemoteImage
            (remoteImageWidth, remoteImageHeight, remoteImageFormat))) {
            if ((localImage = m_plugin.AcquireLocalImage
                (localImageWidth, localImageHeight, localImageFormat))) {
                    m_renderer.Render
                    (remoteImage, remoteImageWidth, remoteImageHeight,
                     localImage, localImageWidth, localImageHeight);
                    m_plugin.ReleaseLocalImage(localImage);
            } else {
                m_renderer.Render
                (remoteImage, remoteImageWidth, remoteImageHeight);
            }
             m_plugin.ReleaseRemoteImage(remoteImage);
        } else {
            if ((localImage = m_plugin.AcquireLocalImage
                (localImageWidth, localImageHeight, localImageFormat))) {
                    m_renderer.Render
                    (remoteImage, remoteImageWidth, remoteImageHeight);
                     m_plugin.ReleaseLocalImage(localImage);
            } else {
            }
        }
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    TPlugin& m_plugin;
};

///////////////////////////////////////////////////////////////////////
///  Class: VideoWidgetT
///////////////////////////////////////////////////////////////////////
template 
<class TImage, class TImageFormat, class TImageRenderer, 
 class TPlugin, class TExtend = QWidget>

class _EXPORT_CLASS VideoWidgetT: public TExtend {
public:
    typedef TExtend Extends;
    typedef TPlugin Plugin;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: VideoWidgetT
    ///////////////////////////////////////////////////////////////////////
    VideoWidgetT(TPlugin& plugin, QWidget* parent)
    : Extends(parent), 
      m_plugin(plugin),
      m_painter(m_plugin) {
    }
    virtual ~VideoWidgetT() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Init() {
        return true;
    }
    virtual bool Finish() {
        return true;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Show(int width, int height) {
        this->show();
        this->resize(width, height);
        this->update();
        return true;
    }
    virtual bool Show() {
        m_renderer.Reshape(this->width(), this->height());
        this->show();
        this->update();
        return true;
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void resizeEvent(QResizeEvent *event) {
        m_renderer.Reshape(this->width(), this->height());
    }
    virtual void mouseReleaseEvent(QMouseEvent *event) {
        Qt::MouseButton button = Qt::NoButton;
        switch((button = event->button())) {
        case Qt::LeftButton:
            m_plugin.OnLButtonUp();
            break;
        case Qt::RightButton:
            m_plugin.OnRButtonUp();
            break;
        }
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    TPlugin& m_plugin;
    TImageRenderer m_renderer;
    VideoPainterT<TImage, TImageFormat, TImageRenderer, TPlugin> m_painter;
};

typedef VideoWidgetT
<PluginInterface::Image, PluginInterface::ImageFormat,
 xos::gui::qt::ImageRenderer,  PluginInterface, QWidget>
VideoWidgetExtend;
///////////////////////////////////////////////////////////////////////
///  Class: VideoWidget
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS VideoWidget: public VideoWidgetExtend {
public:
    typedef VideoWidgetExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: VideoWidget
    ///////////////////////////////////////////////////////////////////////
    VideoWidget(PluginInterface& plugin, QWidget* parent)
    : Extends(plugin, parent) {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Init() {
        return m_renderer.Init(this);
    }
    virtual bool Finish() {
        return m_renderer.Finish();
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void paintEvent(QPaintEvent *event) {
        m_painter.PaintRenderer(m_renderer);
    }
};

///////////////////////////////////////////////////////////////////////
///  Class: VideoViewT
///////////////////////////////////////////////////////////////////////
template <class TPlugin, class TVideoWidget, class TExtend = QWidget>

class _EXPORT_CLASS VideoViewT: public TExtend {
public:
    typedef TExtend Extends;
    typedef TPlugin Plugin;
    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: VideoViewT
    ///////////////////////////////////////////////////////////////////////
    VideoViewT(TPlugin& plugin, QWidget* parent)
    : Extends(parent), m_plugin(plugin), m_video(0), m_disconnectButton(0) {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Init() {
        this->setAutoFillBackground(true);
        this->setAttribute(Qt::WA_NoMousePropagation);

        if ((m_video = new TVideoWidget(m_plugin, this))) {

            if ((m_video->Init())) {

                if ((m_disconnectButton = new QPushButton("Disconnect", this))) {
                    Resize();
                    return true;

                    delete m_disconnectButton;
                    m_disconnectButton = 0;
                }
            }
            delete m_video;
            m_video = 0;
        }
        return false;
    }
    virtual bool Finish() {
        bool success = false;
        return success;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Show(int width, int height) {
        this->resize(width, height);
        this->show();
        return true;
    }
    virtual bool Update() {
        if ((m_video))
            m_video->update();
        return true;
    }
protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void resizeEvent(QResizeEvent *event) {
        Resize();
    }
    virtual void Resize() {
        if ((m_disconnectButton) && (m_video)) {
            int buttonWidth = m_disconnectButton->width();
            int buttonHeight = m_disconnectButton->height();
             m_video->resize
             (this->width(), ((buttonHeight) < this->height())?(this->height()-(buttonHeight)):(0));
            m_disconnectButton->move
            ((buttonWidth < this->width())?((this->width()-buttonWidth)/2):(0), m_video->height());
        }
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    TPlugin& m_plugin;
    TVideoWidget* m_video;
    QPushButton* m_disconnectButton;
};

typedef VideoViewT<PluginInterface, VideoWidget, QWidget> VideoViewExtend;
///////////////////////////////////////////////////////////////////////
///  Class: VideoView
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS VideoView: public VideoViewExtend {
Q_OBJECT
public:
    typedef VideoViewExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: VideoView
    ///////////////////////////////////////////////////////////////////////
    VideoView(Plugin& plugin, QWidget* parent)
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

#endif // _XOS_APP_WEBRTC_CLIENT_GUI_QT_VIDEOVIEW_HPP 
