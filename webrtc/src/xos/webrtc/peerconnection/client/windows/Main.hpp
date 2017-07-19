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
///   File: Main.hpp
///
/// Author: $author$
///   Date: 1/12/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOWS_MAIN_HPP
#define _XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOWS_MAIN_HPP

#include "xos/webrtc/peerconnection/client/console/PluginWindow.hpp"
#include "xos/webrtc/peerconnection/client/windows/MainWindowPeer.hpp"
#include "xos/gui/windows/WindowMain.hpp"

#define XOS_WEBRTC_PEERCONNECTION_CLIENT_MAIN_DEFAULT_SERVER_NAME "localhost"
#define XOS_WEBRTC_PEERCONNECTION_CLIENT_MAIN_DEFAULT_SERVER_PORT 8888

namespace xos {
namespace webrtc {
namespace peerconnection {
namespace client {
namespace windows {

typedef console::PluginWindow PeerMainWindow;
typedef xos::windows::WindowMainImplement MainImplement;
typedef xos::windows::WindowMain MainExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Main
///
/// Author: $author$
///   Date: 1/12/2013
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Main
: virtual public MainImplement,
  public MainExtend
{
public:
    typedef MainImplement Implements;
    typedef MainExtend Extends;

    Main()
    : m_serverName(XOS_WEBRTC_PEERCONNECTION_CLIENT_MAIN_DEFAULT_SERVER_NAME),
      m_serverPort(XOS_WEBRTC_PEERCONNECTION_CLIENT_MAIN_DEFAULT_SERVER_PORT),
      m_showConnectionState(true),
      m_handleButtonEvents(true),
      m_postButtonEventUIMessages(true),
      m_autoConnectToPeerOn(false),
      m_autoConnectToPeerAfterOn(false),
      m_useUIMessageQueue(true),
      m_useOpenGLRenderer(false),
      m_mainWindow
      (m_serverName.c_str(), m_serverPort, 
       m_autoConnectToPeerOn, m_autoConnectToPeerAfterOn,
       m_showConnectionState, m_handleButtonEvents, m_postButtonEventUIMessages, 
       m_useUIMessageQueue, m_useOpenGLRenderer),
      m_mainWindowPeer(m_mainWindow) {
    }
    virtual ~Main() {
    }

    virtual xos::windows::MainWindow* CreateMainWinow
    (xos::windows::WindowClass& mainWindowClass,
     HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int cmdShow) {
        LPCTSTR className;
        if ((className = mainWindowClass.GetWindowClassName()))
            if ((m_mainWindowPeer.Create(hInstance, className, className)))
                return &m_mainWindowPeer;
        return 0;
    }
    virtual bool DestroyMainWindow
    (xos::windows::MainWindow* mainWindow,
     HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int cmdShow) {
        if ((&m_mainWindowPeer == mainWindow))
            return m_mainWindowPeer.Destroy();
        return false;
    }
    virtual xos::windows::MainWindow* GetMainWindow() const {
        return (xos::windows::MainWindow*)(&m_mainWindowPeer);
    }

protected:
    std::string m_serverName;
    int m_serverPort;
    bool m_showConnectionState;
    bool m_handleButtonEvents;
    bool m_postButtonEventUIMessages;
    bool m_autoConnectToPeerOn;
    bool m_autoConnectToPeerAfterOn;
    bool m_useUIMessageQueue;
    bool m_useOpenGLRenderer;
    PeerMainWindow m_mainWindow;
    MainWindowPeer m_mainWindowPeer;
};

} // namespace windows 
} // namespace client 
} // namespace peerconnection 
} // namespace webrtc 
} // namespace xos 

#endif // _XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOWS_MAIN_HPP 
