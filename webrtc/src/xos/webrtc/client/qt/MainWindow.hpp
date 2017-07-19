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
///   File: MainWindow.hpp
///
/// Author: $author$
///   Date: 2/23/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_WEBRTC_CLIENT_QT_MAINWINDOW_HPP
#define _XOS_WEBRTC_CLIENT_QT_MAINWINDOW_HPP

#include "xos/webrtc/client/qt/opengl/Widget.hpp"
#include "xos/webrtc/client/qt/Widget.hpp"
#include "xos/webrtc/client/PluginInterface.hpp"
#include "xos/gui/qt/ImageRenderer.hpp"
#include "xos/base/String.hpp"

#define XOS_WEBRTC_CLIENT_DEFAULT_SERVER_NAME "localhost"
#define XOS_WEBRTC_CLIENT_DEFAULT_SERVER_PORT 8888

#define XOS_WEBRTC_CLIENT_DEFAULT_BACKGROUND_RED   0
#define XOS_WEBRTC_CLIENT_DEFAULT_BACKGROUND_GREEN 0
#define XOS_WEBRTC_CLIENT_DEFAULT_BACKGROUND_BLUE  0

#define XOS_WEBRTC_CLIENT_DEFAULT_CONNECT_TO_PEER_RED   0
#define XOS_WEBRTC_CLIENT_DEFAULT_CONNECT_TO_PEER_GREEN 128
#define XOS_WEBRTC_CLIENT_DEFAULT_CONNECT_TO_PEER_BLUE  0

#define XOS_WEBRTC_CLIENT_DEFAULT_CONNECT_TO_SERVER_RED 0
#define XOS_WEBRTC_CLIENT_DEFAULT_CONNECT_TO_SERVER_GREEN 0
#define XOS_WEBRTC_CLIENT_DEFAULT_CONNECT_TO_SERVER_BLUE 128

namespace xos {
namespace webrtc {
namespace client {

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS PluginInterface::Window: public QMainWindow {
public:
    typedef QMainWindow Extends;
    virtual ~Window() {}
};

namespace qt {

typedef InterfaceBase MainWindowImplementImplement;
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS MainWindowImplement
: virtual public MainWindowImplementImplement,
  virtual public ImageObserverInterface,
  virtual public EventObserverInterface {
public:
    typedef MainWindowImplementImplement Implements;
    typedef ImageObserverInterface ImageImplements;
    typedef EventObserverInterface EventImplements;
};

typedef PluginInterface::Window MainWindowExtend;
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS MainWindow
: virtual public MainWindowImplement, public MainWindowExtend {
public:
    typedef MainWindowImplement Implements;
    typedef MainWindowExtend Extends;
    typedef MainWindow Derives;
    typedef void (Derives::*MPaint)(QPaintEvent* event);

    ///////////////////////////////////////////////////////////////////////
    // constructor/destructor
    ///////////////////////////////////////////////////////////////////////
    MainWindow(bool useOpenGLRenderer=false, bool useWindowRenderer=false)
    : m_renderer(this),
      m_paint(0),
      m_plugin(0),
      m_widget(0),
      m_openglWidget(0),
      m_useWindowRenderer(useWindowRenderer),
      m_useOpenGLRenderer(useOpenGLRenderer),
      m_autoConnectToPeerOn(false),
      m_serverName(XOS_WEBRTC_CLIENT_DEFAULT_SERVER_NAME),
      m_serverPort(XOS_WEBRTC_CLIENT_DEFAULT_SERVER_PORT),
      m_bgColorUnconnected
      (XOS_WEBRTC_CLIENT_DEFAULT_CONNECT_TO_SERVER_RED,
       XOS_WEBRTC_CLIENT_DEFAULT_CONNECT_TO_SERVER_GREEN,
       XOS_WEBRTC_CLIENT_DEFAULT_CONNECT_TO_SERVER_BLUE),
      m_bgColorConnected
      (XOS_WEBRTC_CLIENT_DEFAULT_CONNECT_TO_PEER_RED,
       XOS_WEBRTC_CLIENT_DEFAULT_CONNECT_TO_PEER_GREEN,
       XOS_WEBRTC_CLIENT_DEFAULT_CONNECT_TO_PEER_BLUE),
      m_bgColorStreaming
      (XOS_WEBRTC_CLIENT_DEFAULT_BACKGROUND_RED,
       XOS_WEBRTC_CLIENT_DEFAULT_BACKGROUND_GREEN,
       XOS_WEBRTC_CLIENT_DEFAULT_BACKGROUND_BLUE),
      m_bgColor(m_bgColorUnconnected),
      m_errorMessage(0)
    {
    }
    virtual ~MainWindow()
    {
    }

    ///////////////////////////////////////////////////////////////////////
    // On Window Open/Close
    ///////////////////////////////////////////////////////////////////////
    virtual bool OnWindowOpen()
    {
        bool success = false;
        if (!(m_plugin)) {
            if ((success = (0 != (m_plugin = LoadPlugin())))) {

                m_plugin->SetAutoConnectToPeerOn(m_autoConnectToPeerOn);
                m_plugin->SetServerName(m_serverName);
                m_plugin->SetServerPort(m_serverPort);
                m_plugin->RegisterImageObserver(this);
                m_plugin->RegisterEventObserver(this);

                if (!(m_useWindowRenderer)) {
                    if (!(m_useOpenGLRenderer)) {
                        if ((m_widget = new Widget
                            (m_plugin, this, m_bgColorStreaming))) {
                            if ((!m_openglWidget) || (m_openglWidget != centralWidget())) {
                                setCentralWidget(m_widget);
                            }
                        }
                    }
                    if ((m_useOpenGLRenderer)) {
                        if ((m_openglWidget = new opengl::Widget
                            (m_plugin, this, m_bgColorStreaming))) {
                            if ((!m_widget) || (m_widget != centralWidget())) {
                                setCentralWidget(m_openglWidget);
                            }
                        }
                    }
                }
                if ((success = m_plugin->AttachWindow(this))) {
                    return success;
                }
                if ((m_openglWidget)) {
                    if (m_openglWidget == (centralWidget()))
                        setCentralWidget(0);
                    else
                    delete m_openglWidget;
                    m_openglWidget = 0;
                }
                if ((m_widget)) {
                    if (m_widget == (centralWidget()))
                        setCentralWidget(0);
                    else
                    delete m_widget;
                    m_widget = 0;
                }
                m_plugin->UnregisterEventObserver(this);
                m_plugin->UnregisterImageObserver(this);
                UnloadPlugin(m_plugin);
                m_plugin = 0;
            }
        }
        return success;
    }
    virtual bool OnWindowClose()
    {
        bool success = false;
        if ((m_plugin)) {
            success = m_plugin->DetachWindow(this);
            if ((m_openglWidget)) {
                if (m_openglWidget == (centralWidget()))
                    setCentralWidget(0);
                else
                delete m_openglWidget;
                m_openglWidget = 0;
            }
            if ((m_widget)) {
                if (m_widget == (centralWidget()))
                    setCentralWidget(0);
                else
                delete m_widget;
                m_widget = 0;
            }
            m_plugin->UnregisterEventObserver(this);
            m_plugin->UnregisterImageObserver(this);
            if (!(UnloadPlugin(m_plugin)))
                success = false;
            m_plugin = 0;
        }
        return success;
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    // Image Observer
    ///////////////////////////////////////////////////////////////////////
    virtual bool InvalidateWindow(bool eraseBackground = true) 
    { 
        QApplication::postEvent(this, new InvalidateQEvent());
        return true; 
    }

    ///////////////////////////////////////////////////////////////////////
    // Event Observer
    ///////////////////////////////////////////////////////////////////////
    virtual void OnChangeStateToConnectToServer() { 
        QApplication::postEvent(this, new ChangeStateQEvent(ConnectServer));
    }
    virtual void OnChangeStateToListPeers() { 
        QApplication::postEvent(this, new ChangeStateQEvent(ListPeers));
    }
    virtual void OnChangeStateToStreaming() {
        QApplication::postEvent(this, new ChangeStateQEvent(Streaming));
    }
    virtual void OnFailedToConnectToServer(const std::string& server) {
        QApplication::postEvent(this, new FailedConnectServerQEvent(server));
    }

    ///////////////////////////////////////////////////////////////////////
    // Message Events
    ///////////////////////////////////////////////////////////////////////
    virtual void OnResize() 
    { 
        int width = this->width();
        int height = this->height();
        m_renderer.Reshape(width,height);
        if ((m_widget))
            m_widget->Resize();
        if ((m_openglWidget))
            m_openglWidget->Resize();
        update(0,0, width,height);
    }
    virtual void OnInvalidate() 
    { 
        int width = this->width();
        int height = this->height();
        update(0,0, width,height);
        if ((m_openglWidget) && (m_openglWidget == centralWidget()))
            m_openglWidget->Invalidate();
    }
    virtual void OnConnectServer() { 
        m_paint = 0;
        if ((m_widget))
            m_widget->hide();
        if ((m_openglWidget))
            m_openglWidget->hide();
        m_bgColor = m_bgColorUnconnected;
        OnResize();
        EventImplements::OnChangeStateToConnectToServer();
    }
    virtual void OnListPeers() { 
        m_paint = 0;
        if ((m_widget))
            m_widget->hide();
        if ((m_openglWidget))
            m_openglWidget->hide();
        m_bgColor = m_bgColorConnected;
        OnResize();
        EventImplements::OnChangeStateToListPeers();
    }
    virtual void OnStreaming() {
        if ((m_widget) && (m_widget == centralWidget()))
            m_widget->Show();
        else
        if ((m_openglWidget) && (m_openglWidget == centralWidget()))
            m_openglWidget->Show();
        else  {
            m_renderer.Reshape(width(),height());
            m_paint = &Derives::PaintImage;
        }
        m_bgColor = m_bgColorStreaming;
        OnResize();
        EventImplements::OnChangeStateToStreaming();
    }
    virtual void OnFailedConnectServer(const std::string& server) {
        if ((m_errorMessage)) {
            delete m_errorMessage;
            m_errorMessage = 0;
        }
        if ((m_errorMessage = new QErrorMessage(this))) {
            QString message("Failed to connect to server \"");
            message.append(server.c_str());
            message.append("\"");
            m_errorMessage->showMessage(message);
        }
        EventImplements::OnFailedToConnectToServer(server);
    }

    ///////////////////////////////////////////////////////////////////////
    // Button Events
    ///////////////////////////////////////////////////////////////////////
    virtual void OnLButtonUp() {
        if ((m_plugin))
            m_plugin->OnLButtonUp();
    }
    virtual void OnRButtonUp() {
        if ((m_plugin))
            m_plugin->OnRButtonUp();
    }

    ///////////////////////////////////////////////////////////////////////
    // Qt events
    ///////////////////////////////////////////////////////////////////////
    virtual void customEvent(QEvent* event) 
    {
        switch((event->type()))
        {
        case FailedConnectServer:
            OnFailedConnectServer(((FailedConnectServerQEvent*)(event))->server());
            break;
        case ConnectServer:
            OnConnectServer();
            break;
        case ListPeers:
            OnListPeers();
            break;
        case Streaming:
            OnStreaming();
            break;
        case Invalidate:
            OnInvalidate();
            break;
        }
    }
    virtual void mouseReleaseEvent(QMouseEvent *event)
    {
        switch((event->button()))
        {
        case Qt::LeftButton:
            OnLButtonUp();
            break;
        case Qt::RightButton:
        default:
            OnRButtonUp();
            break;
        }
        Extends::mouseReleaseEvent(event);
    }
    virtual void resizeEvent(QResizeEvent *event) 
    {
        OnResize();
    }
    virtual void paintEvent(QPaintEvent *event) 
    {
        if ((m_paint)) {
            (this->*m_paint)(event);
        } else {
            PaintBackground(event);
        }
    }
    virtual void PaintBackground(QPaintEvent *event) {
        int width = this->width();
        int height = this->height();
        QPainter qp(this);
        QRect rc(0,0, width, height);
        qp.fillRect(rc, m_bgColor);
    }
    virtual void PaintImage(QPaintEvent *event) {
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
                    m_renderer.Render
                    (remoteImage, remoteImageWidth, remoteImageHeight,
                     localImage, localImageWidth, localImageHeight);
                    m_plugin->ReleaseLocalImage(localImage);
                } else {
                    m_renderer.Render
                    (remoteImage, remoteImageWidth, remoteImageHeight);
                }
                m_plugin->ReleaseRemoteImage(remoteImage);
            } else {
                if ((localImage = m_plugin->AcquireLocalImage
                    (localImageWidth, localImageHeight, localImageFormat))) 
                {
                    m_renderer.Render
                    (localImage, localImageWidth, localImageHeight);
                    m_plugin->ReleaseLocalImage(localImage);
                } else {
                    PaintBackground(event);
                }
            }
        } else {
            PaintBackground(event);
        }
    }

    ///////////////////////////////////////////////////////////////////////
    // Load/Unload Plugin
    ///////////////////////////////////////////////////////////////////////
    virtual PluginInterface* LoadPlugin() {
        PluginInterface* plugin = PluginInterface::AcquireInstance();
        return plugin;
    }
    virtual bool UnloadPlugin(PluginInterface* plugin) {
        bool isTrue = PluginInterface::ReleaseInstance(plugin);
        return isTrue;
    }

protected:
    enum  { 
        FailedConnectServer = QEvent::User+1,
        ConnectServer,
        ListPeers,
        Streaming,
        Invalidate
    };
    class FailedConnectServerQEvent: public QEvent {
    public:
        FailedConnectServerQEvent(const std::string& server)
        : QEvent((Type)(FailedConnectServer)), m_server(server) {}
        const std::string& server() const { return m_server; }
    protected:
        std::string m_server;
    };
    class ChangeStateQEvent: public QEvent {
    public:
        ChangeStateQEvent(int type): QEvent((Type)(type)) {}
    };
    class InvalidateQEvent: public QEvent {
    public:
        InvalidateQEvent(): QEvent((Type)(Invalidate)) {}
    };

protected:
    gui::qt::ImageRenderer m_renderer;
    MPaint m_paint;
    PluginInterface* m_plugin;
    Widget* m_widget;
    opengl::Widget* m_openglWidget;
    String m_serverName;
    int m_serverPort;
    bool m_useWindowRenderer;
    bool m_useOpenGLRenderer;
    bool m_autoConnectToPeerOn;
    QColor m_bgColorUnconnected;
    QColor m_bgColorConnected;
    QColor m_bgColorStreaming;
    QColor m_bgColor;
    QErrorMessage* m_errorMessage;
};

} // namespace qt 
} // namespace client 
} // namespace webrtc 
} // namespace xos 

#endif // _XOS_WEBRTC_CLIENT_QT_MAINWINDOW_HPP 
