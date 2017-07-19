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
///   Date: 8/1/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_APP_WEBRTC_CLIENT_GUI_QT_MAINWINDOW_HPP
#define _XOS_APP_WEBRTC_CLIENT_GUI_QT_MAINWINDOW_HPP

#include "app/webrtc/client/gui/qt/ServerView.hpp"
#include "app/webrtc/client/gui/qt/PeerView.hpp"
#include "app/webrtc/client/gui/qt/VideoView.hpp"
#include "app/webrtc/client/gui/qt/GLVideoView.hpp"
#include "app/webrtc/client/PluginInterface.hpp"

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
namespace app {
namespace webrtc {
namespace client {
namespace gui {
namespace qt {

///////////////////////////////////////////////////////////////////////
///  Class: MainWindowImplement
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS MainWindowImplement
: virtual public ImageObserverInterface,
  virtual public EventObserverInterface {
public:
};
typedef QMainWindow MainWindowExtend;
///////////////////////////////////////////////////////////////////////
///  Class: MainWindow
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS MainWindow
: virtual public MainWindowImplement, public MainWindowExtend {
public:
    typedef MainWindowImplement Implements;
    typedef MainWindowExtend Extends;
    typedef MainWindow Derives;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: MainWindow
    ///////////////////////////////////////////////////////////////////////
    MainWindow(bool useOpenGL = false, bool useWindow = false)
    : m_plugin(0),
      m_errorMessage(0),
      m_paint(0),
      m_painter(0),
      m_renderer(0),
      m_view(0), 
      m_serverView(0),
      m_peerView(0),
      m_videoView(0), 
      m_glVideoView(0),
      m_useOpenGL(useOpenGL),
      m_useWindow(useWindow),
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
      m_bgColor(m_bgColorUnconnected) {
    }
    virtual ~MainWindow() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Init() {
        if ((AcquirePlugin())) {
            if ((m_view = (m_serverView = new ServerView(*m_plugin, this)))) {
                if ((m_serverView->Init())) {
                    m_serverView->Show(width(), height());

                    if (((m_peerView = new PeerView(*m_plugin, this)))) {
                        if ((m_peerView->Init())) {
                            m_peerView->hide();

                            if ((m_useWindow))
                            if ((m_renderer = new VideoRenderer(this))) {
                                if ((m_painter = new VideoPainter(*m_plugin))) {
                                    return true;
                                } else {
                                    delete m_renderer;
                                    m_renderer = 0;
                                }
                            }
                            if ((m_useOpenGL))
                            if (((m_glVideoView = new GLVideoView(*m_plugin, this)))) {
                                if ((m_glVideoView->Init())) {
                                    m_glVideoView->hide();
                                    return true;
                                } else {
                                    delete m_glVideoView;
                                    m_glVideoView = 0;
                                }
                            }
                            if (((m_videoView = new VideoView(*m_plugin, this)))) {
                                if ((m_videoView->Init())) {
                                    m_videoView->hide();
                                    return true;
                                } else {
                                    delete m_videoView;
                                    m_videoView = 0;
                                }
                            }
                        } else {
                            delete m_peerView;
                            m_peerView = 0;
                        }
                    }
                } else {
                    delete m_serverView;
                    m_serverView = 0;
                    m_view = 0;
                }
            }
            ReleasePlugin();
        }
        return false;
    }
    virtual bool Finish() {
        bool isSuccess = true;
        m_view = 0;
        if ((m_painter)) {
             delete m_painter;
             m_painter = 0;
        }
        if ((m_renderer)) {
             delete m_renderer;
             m_renderer = 0;
        }
        if ((m_glVideoView)) {
             delete m_glVideoView;
             m_glVideoView = 0;
        }
        if ((m_peerView)) {
             delete m_peerView;
             m_peerView = 0;
        }
        if ((m_serverView)) {
             delete m_serverView;
             m_serverView = 0;
        }
        if (!(ReleasePlugin()))
            isSuccess = false;
        return isSuccess;
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    // Image Observer
    ///////////////////////////////////////////////////////////////////////
    virtual bool UpdatedImages()  { 
        QApplication::postEvent(this, new UpdateImagesQEvent());
        return true; 
    }

    ///////////////////////////////////////////////////////////////////////
    // Event Observer
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    // Change State
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
    // Peer Connection
    ///////////////////////////////////////////////////////////////////////
    virtual void OnPeerConnectedToServer(int id, const std::string& name) {
        QApplication::postEvent(this, new PeerConnectedQEvent(PeerConnected, id, name));
    }
    virtual void OnPeerDisconnectedFromServer(int id) {
        QApplication::postEvent(this, new PeerConnectedQEvent(PeerDisconnected, id));
    }
    virtual void OnDisconnectedFromPeer(int id) {
        QApplication::postEvent(this, new PeerConnectedQEvent(DisconnectedFromPeer, id));
    }

    ///////////////////////////////////////////////////////////////////////
    // Events
    ///////////////////////////////////////////////////////////////////////
    virtual void OnLButtonUp() {
        if ((m_plugin))
            m_plugin->OnLButtonUp();
    }
    virtual void OnRButtonUp() {
        if ((m_plugin))
            m_plugin->OnRButtonUp();
    }
    virtual void OnFailedConnect(const std::string& server) {
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
    }
    virtual void OnConnect() {
        SwitchBgColor(m_bgColorUnconnected);
        if ((SwitchView(m_serverView)))
            m_serverView->Show(width(), height());
    }
    virtual void OnListPeers() {
        SwitchBgColor(m_bgColorConnected);
        if ((SwitchView(m_peerView)))
            m_peerView->Show(width(), height());
    }
    virtual void OnStreaming() {
        SwitchBgColor(m_bgColorStreaming);
        if ((m_renderer) && (m_painter)) {
            if ((m_view))
                m_view->hide();
            m_renderer->Reshape(width(), height());
            m_paint = &Derives::PaintImage;
        }
        else
        if ((SwitchView(m_glVideoView)))
            m_glVideoView->Show(width(), height());
        else
        if ((SwitchView(m_videoView)))
            m_videoView->Show(width(), height());
    }
    virtual void OnUpdateImages() {
        if ((m_renderer) && (m_painter))
            update();
        else
        if ((m_view) && (m_view == m_glVideoView))
            m_glVideoView->Update();
        else
        if ((m_view) && (m_view == m_videoView))
            m_videoView->Update();
    }
    virtual void OnPeerConnected(const std::string& name, int id) {
        if ((m_peerView) && (m_view == m_peerView))
            m_peerView->AddPeer(name);
    }
    virtual void OnPeerDisconnected(int id) {
    }
    virtual void OnDisconnectedPeer(int id) {
    }

    ///////////////////////////////////////////////////////////////////////
    // Qt events
    ///////////////////////////////////////////////////////////////////////
    virtual void customEvent(QEvent* event) {
        switch((event->type())) {
        case FailedConnectServer:
            OnFailedConnect(((FailedConnectServerQEvent*)event)->server());
            break;

        case ConnectServer:
            OnConnect();
            break;

        case ListPeers:
            OnListPeers();
            break;

        case Streaming:
            OnStreaming();
            break;

        case UpdateImages:
            OnUpdateImages();
            break;

        case PeerConnected:
            OnPeerConnected
            (((PeerConnectedQEvent*)event)->name(), 
             ((PeerConnectedQEvent*)event)->id());
            break;

        case PeerDisconnected:
            OnPeerDisconnected(((PeerConnectedQEvent*)event)->id());
            break;

        case DisconnectedFromPeer:
            OnDisconnectedPeer(((PeerConnectedQEvent*)event)->id());
            break;
        }
    }
    virtual void resizeEvent(QResizeEvent *event) {
        ResizeView();
    }
    virtual void mouseReleaseEvent(QMouseEvent *event) {
        switch((event->button())) {
        case Qt::LeftButton:
            OnLButtonUp();
            break;
        case Qt::RightButton:
            OnRButtonUp();
            break;
        }
    }
    virtual void paintEvent(QPaintEvent *event) {
        if ((m_paint))
            (this->*m_paint)(event);
        else
        PaintBackground(event);
    }
    virtual void PaintBackground(QPaintEvent *event) {
        QPainter qp(this);
        QRect rc(0,0, width(), height());
        qp.fillRect(rc, m_bgColor);
    }
    virtual void PaintImage(QPaintEvent *event) {
        if ((m_renderer) && (m_painter))
            m_painter->PaintRenderer(*m_renderer);
        else
        PaintBackground(event);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void SwitchBgColor(QColor& bgColor) {
        m_bgColor = bgColor;
        update();
    }
    virtual QWidget* SwitchView(QWidget* view = 0) {
        m_paint = 0;
        if ((m_view))
            m_view->hide();
        return m_view = view;
    }
    virtual void ResizeView() {
        if ((m_renderer))
            m_renderer->Reshape(width(), height());
        if ((m_view))
            m_view->resize(width(), height());
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual PluginInterface* AcquirePlugin() {
        if ((m_plugin = PluginInterface::AcquireInstance())) {
            m_plugin->RegisterImageObserver(this);
            m_plugin->RegisterEventObserver(this);
            if ((m_plugin->AttachUserInterface()))
                return m_plugin;
            PluginInterface::ReleaseInstance(m_plugin);
            m_plugin = 0;
        }
        return m_plugin;
    }
    virtual bool ReleasePlugin() {
        bool isSuccess = false;
        if ((m_plugin)) {
            isSuccess = m_plugin->DetachUserInterface();
            m_plugin->UnregisterEventObserver(this);
            m_plugin->UnregisterImageObserver(this);
            isSuccess = PluginInterface::ReleaseInstance(m_plugin);
            m_plugin = 0;
        }
        return isSuccess;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    enum  { 
        FailedConnectServer = QEvent::User+1,
        ConnectServer,
        ListPeers,
        Streaming,
        UpdateImages,
        PeerConnected,
        PeerDisconnected,
        DisconnectedFromPeer
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
    class UpdateImagesQEvent: public QEvent {
    public:
        UpdateImagesQEvent(): QEvent((Type)(UpdateImages)) {}
    };
    class PeerConnectedQEvent: public QEvent {
    public:
        PeerConnectedQEvent(int type, int id, const std::string& name)
        : QEvent((Type)(type)), m_id(id), m_name(name) {}
        PeerConnectedQEvent(int type, int id)
        : QEvent((Type)(type)), m_id(id) {}
        int id() const { return m_id; }
        const std::string& name() const { return m_name; }
    protected:
        int m_id;
        std::string m_name;
    };

    typedef void (Derives::*MPaint)(QPaintEvent* event);

    typedef xos::gui::qt::ImageRenderer VideoRenderer;

    typedef VideoPainterT
    <PluginInterface::Image, PluginInterface::ImageFormat,
     VideoRenderer, PluginInterface> VideoPainter;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    PluginInterface* m_plugin;
    QErrorMessage* m_errorMessage;
    MPaint m_paint;
    VideoPainter* m_painter;
    VideoRenderer* m_renderer;
    QWidget* m_view;
    ServerView* m_serverView;
    PeerView* m_peerView;
    VideoView* m_videoView;
    GLVideoView* m_glVideoView;
    bool m_useOpenGL;
    bool m_useWindow;
    QColor m_bgColorUnconnected;
    QColor m_bgColorConnected;
    QColor m_bgColorStreaming;
    QColor m_bgColor;
};

} // namespace qt 
} // namespace gui 
} // namespace client 
} // namespace webrtc 
} // namespace app 
} // namespace xos 

#endif // _XOS_APP_WEBRTC_CLIENT_GUI_QT_MAINWINDOW_HPP 
