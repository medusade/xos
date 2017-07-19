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

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: MainWindow
    ///////////////////////////////////////////////////////////////////////
    MainWindow(PluginInterface* plugin)
    : m_plugin(plugin),
      m_acquiredPlugin(false),
      m_view(0), 
      m_serverView(0), 
      m_peerView(0),
      m_videoView(0), 
      m_glVideoView(0),
      m_useOpenGL(0) {
    }
    virtual ~MainWindow() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Init(bool useOpenGL = false) {
        bool isSuccess = false;
        if (!(m_plugin)) {
            if (!(AcquirePlugin()))
                return false;
        }
        if ((m_useOpenGL = useOpenGL)) {
            if ((m_view = (m_glVideoView = new GLVideoView(*m_plugin, this)))) {
                if ((m_glVideoView->Init())) {
                    m_glVideoView->hide();
                    //m_glVideoView->Show(width(), height());
                    //return true;
                } else {
                delete m_glVideoView;
                m_glVideoView = 0;
                m_view = 0;
                }
            }
        }
        if ((m_view = (m_videoView = new VideoView(*m_plugin, this)))) {
            if ((m_videoView->Init())) {
                m_videoView->hide();
                //m_videoView->Show(width(), height());
                //return true;
            } else {
            delete m_videoView;
            m_videoView = 0;
            m_view = 0;
            }
        }
        if ((m_view = (m_peerView = new PeerView(*m_plugin, this)))) {
            if ((m_peerView->Init())) {
                m_peerView->hide();
                //m_peerView->Show(width(), height());
                //return true;
            } else {
            delete m_serverView;
            m_serverView = 0;
            m_view = 0;
            }
        }
        if ((m_view = (m_serverView = new ServerView(*m_plugin, this)))) {
            if ((m_serverView->Init())) {
                m_serverView->Show(width(), height());
                return true;
            } else {
            delete m_serverView;
            m_serverView = 0;
            m_view = 0;
            }
        }
        return isSuccess;
    }
    virtual bool Finish() {
        bool isSuccess = true;
        if ((m_acquiredPlugin))
            isSuccess = ReleasePlugin();
        return isSuccess;
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
    // Image Observer
    ///////////////////////////////////////////////////////////////////////
    virtual bool UpdatedImages()  { 
        if ((m_view) && ((m_view == m_glVideoView) || (m_view == m_videoView)))
            QApplication::postEvent(this, new UpdateImageQEvent());
        return true; 
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void customEvent(QEvent* event) {
        switch((event->type())) {
        case FailedConnectServer:
            {   FailedConnectServerQEvent* serverEvent = ((FailedConnectServerQEvent*)event);
            }
            break;

        case ConnectServer:
            if ((m_view))
                m_view->hide();
            if ((m_view = m_serverView))
                m_serverView->Show(width(), height());
            break;

        case ListPeers:
            if ((m_view))
                m_view->hide();
            if ((m_view = m_peerView))
                m_peerView->Show(width(), height());
            break;

        case Streaming:
            if ((m_view))
                m_view->hide();
            if ((m_useOpenGL) && (m_view = m_glVideoView))
                m_glVideoView->Show(width(), height());
            else 
            if ((m_view = m_videoView))
                m_videoView->Show(width(), height());
            break;

        case UpdateImage:
            if ((m_view) && (m_view == m_glVideoView))
                m_glVideoView->update();
            else 
            if ((m_view) && (m_view == m_videoView))
                m_videoView->update();
            break;

        case PeerConnected:
            {   PeerConnectedQEvent* peerEvent = ((PeerConnectedQEvent*)event);
                if ((m_peerView) && (m_view == m_peerView))
                    m_peerView->AddPeer(peerEvent->name());
            }
            break;

        case PeerDisconnected:
            {   PeerConnectedQEvent* peerEvent = ((PeerConnectedQEvent*)event);
            }
            break;

        case DisconnectedFromPeer:
            {   PeerConnectedQEvent* peerEvent = ((PeerConnectedQEvent*)event);
            }
            break;
        }
    }
    virtual void resizeEvent(QResizeEvent *event) {
        Extends::resizeEvent(event);
        if ((m_view))
            m_view->resize(width(), height());
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual PluginInterface* AcquirePlugin() {
        if ((m_acquiredPlugin = (m_plugin = PluginInterface::AcquireInstance()))) {
            m_plugin->RegisterImageObserver(this);
            m_plugin->RegisterEventObserver(this);
        }
        return m_plugin;
    }
    virtual bool ReleasePlugin() {
        bool isSuccess = false;
        if ((m_acquiredPlugin) && (m_plugin)) {
            m_plugin->UnregisterEventObserver(this);
            m_plugin->UnregisterImageObserver(this);
            isSuccess = PluginInterface::ReleaseInstance(m_plugin);
            m_plugin = 0;
            m_acquiredPlugin = false;
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
        UpdateImage,
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
    class UpdateImageQEvent: public QEvent {
    public:
        UpdateImageQEvent(): QEvent((Type)(UpdateImage)) {}
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
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    PluginInterface* m_plugin;
    bool m_acquiredPlugin;
    QWidget* m_view;
    ServerView* m_serverView;
    PeerView* m_peerView;
    VideoView* m_videoView;
    GLVideoView* m_glVideoView;
    bool m_useOpenGL;
};

} // namespace qt 
} // namespace gui 
} // namespace client 
} // namespace webrtc 
} // namespace app 
} // namespace xos 

#endif // _XOS_APP_WEBRTC_CLIENT_GUI_QT_MAINWINDOW_HPP 
