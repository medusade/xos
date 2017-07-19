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
///   Date: 2/28/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_WEBRTC_CLIENT_QT_VIDEORENDERER_HPP
#define _XOS_WEBRTC_CLIENT_QT_VIDEORENDERER_HPP

#include "xos/webrtc/client/LocalWindow.hpp"
#include "xos/gui/Rectangle.hpp"
#include "xos/base/Base.hpp"
#include <QtGui>

namespace xos {
namespace webrtc {
namespace client {
namespace qt {

typedef InterfaceBase VideoRendererImplement;
typedef ExportBase VideoRendererExtend;
///////////////////////////////////////////////////////////////////////
///  Class: VideoRenderer
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS VideoRenderer
: virtual public VideoRendererImplement, public VideoRendererExtend {
public:
    typedef VideoRendererImplement Implements;
    typedef VideoRendererExtend Extends;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: VideoRenderer
    ///////////////////////////////////////////////////////////////////////
    VideoRenderer(QWidget* widget=0)
    : m_localWindowMinimum(XOS_WEBRTC_CLIENT_LOCAL_WINDOW_MINIMUM),
      m_localWindowOffet(XOS_WEBRTC_CLIENT_LOCAL_WINDOW_OFFSET),
      m_localWindowRatio(XOS_WEBRTC_CLIENT_LOCAL_WINDOW_RATIO),
      m_widget(widget)
    {
    }
    virtual ~VideoRenderer()
    {
    }

    virtual bool Init(QWidget* widget) { 
        if ((m_widget = widget))
            return true;
        return false;
    }
    virtual bool Finish() {
        if ((m_widget)) {
            m_widget = 0;
            return true;
        }
        return false;
    }

    virtual void Reshape(int width, int height) {
        m_width = width;
        m_height = height;
    }

    virtual void Render
    (const void* remoteImage, int remoteImageWidth, int remoteImageHeight,
     const void* localImage, int localImageWidth, int localImageHeight) {
         Render(remoteImage, remoteImageWidth, remoteImageHeight);
    }

    virtual void Render
    (const void* remoteImage, int remoteImageWidth, int remoteImageHeight) {
        if ((m_widget)) {
            QImage qImage
            ((const unsigned char*)(remoteImage), 
             remoteImageWidth, remoteImageHeight, QImage::Format_ARGB32);
            QPainter qPainter(m_widget);
            gui::Size fromSize(remoteImageWidth, remoteImageHeight);
            gui::Size toSize(m_width, m_height);
            gui::Rectangle rect(fromSize, toSize);
            qPainter.drawImage
            (rect.origin.x,rect.origin.y, 
             qImage.scaled(m_width, m_height, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
    }

protected:
    int m_width;
    int m_height;
    int m_localWindowMinimum;
    int m_localWindowOffet;
    int m_localWindowRatio;
    QWidget* m_widget;
};

} // namespace qt 
} // namespace client 
} // namespace webrtc 
} // namespace xos 

#endif // _XOS_WEBRTC_CLIENT_QT_VIDEORENDERER_HPP 
