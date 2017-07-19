///////////////////////////////////////////////////////////////////////
/// Copyright 2012, Google Inc.
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
///   File: MainWindowPeer.hpp
///
/// Author: $author$
///   Date: 12/25/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOWS_MAINWINDOWPEER_HPP
#define _XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOWS_MAINWINDOWPEER_HPP

#include "xos/webrtc/peerconnection/client/MainWindow.hpp"
#include "xos/webrtc/peerconnection/client/windows/ConnectToServerWindow.hpp"
#include "xos/webrtc/peerconnection/client/windows/ConnectToPeerWindow.hpp"
#include "xos/webrtc/peerconnection/client/windows/OpenGL.hpp"
#include "xos/webrtc/peerconnection/client/windows/GCRenderer.hpp"
#include "xos/gui/windows/MainWindow.hpp"

namespace xos {
namespace webrtc {
namespace peerconnection {
namespace client {

typedef MainWindow PeerMainWindow;
///////////////////////////////////////////////////////////////////////
///  Class: MainWindowPeerImplement
///
/// Author: $author$
///   Date: 1/14/2013
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS MainWindowPeerImplement
: virtual public ImageObserverInterface,
  virtual public UserInterfaceStateObserverImplement {
public:
};
typedef xos::windows::MainWindow MainWindowPeerExtend;
///////////////////////////////////////////////////////////////////////
///  Class: MainWindow::WindowPeer
///
/// Author: $author$
///   Date: 1/14/2013
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS MainWindow::WindowPeer
: virtual public MainWindowPeerImplement, public MainWindowPeerExtend {
public:
    typedef MainWindowPeerExtend Extends;

    WindowPeer
    (PeerMainWindow& mainWindow, 
     bool useOpenGLRenderer=true, 
     bool autoConnectToServer=false)
    : m_mainWindow(mainWindow), 
      m_autoConnectToServer(autoConnectToServer),
      m_useOpenGLRenderer(useOpenGLRenderer),
      m_cantUseOpenGLRenderer(false),

      m_backgroundColor(RGB
      (XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOW_DEFAULT_BACKGROUND_RED,
       XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOW_DEFAULT_BACKGROUND_GREEN,
       XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOW_DEFAULT_BACKGROUND_BLUE)),

      m_connectToServerColor(RGB
      (XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOW_DEFAULT_CONNECT_TO_SERVER_RED,
       XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOW_DEFAULT_CONNECT_TO_SERVER_GREEN,
       XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOW_DEFAULT_CONNECT_TO_SERVER_BLUE)),

      m_connectToPeerColor(RGB
      (XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOW_DEFAULT_CONNECT_TO_PEER_RED,
       XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOW_DEFAULT_CONNECT_TO_PEER_GREEN,
       XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOW_DEFAULT_CONNECT_TO_PEER_BLUE)),

      m_connectingColor(RGB
      (XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOW_DEFAULT_CONNECTING_RED,
       XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOW_DEFAULT_CONNECTING_GREEN,
       XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOW_DEFAULT_CONNECTING_BLUE)),

      m_connectToServerBefore(XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOW_DEFAULT_CONNECT_TO_SERVER_BEFORE),
      m_connectToServerAfter(XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOW_DEFAULT_CONNECT_TO_SERVER_AFTER),
      m_connectToPeerBefore(XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOW_DEFAULT_CONNECT_TO_PEER_BEFORE),
      m_connectToPeerAfter(XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOW_DEFAULT_CONNECT_TO_PEER_AFTER),

      m_connectToServerWindow(mainWindow),
      m_connectToPeerWindow(mainWindow)
    {
    }
    virtual ~WindowPeer() {
    }

    ///////////////////////////////////////////////////////////////////////
    // window messages
    ///////////////////////////////////////////////////////////////////////
    virtual LRESULT On_WM_CREATE_WindowMessage
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        LRESULT lResult = 0;
        lResult = OnWindowMessageDefault(hWnd,msg,wParam,lParam);
        m_connectToPeerWindow.Create(*this);
        m_connectToServerWindow.Create(*this);
        m_mainWindow.RegisterStateObserver(this);
        m_mainWindow.RegisterImageObserver(this);
        if ((m_cantUseOpenGLRenderer = !(m_glRenderer.Init(hWnd))))
            m_useOpenGLRenderer = false;
        m_gcRenderer.Init(hWnd);
        if ((m_mainWindow.Attached())) {
            if ((m_autoConnectToServer))
                m_mainWindow.ConnectToServer();
        }
        return lResult;
    }
    virtual LRESULT On_WM_DESTROY_WindowMessage
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        LRESULT lResult = 0;
        m_mainWindow.Detached();
        m_gcRenderer.Finish(hWnd);
        m_glRenderer.Finish(hWnd);
        m_mainWindow.UnregisterImageObserver(this);
        m_mainWindow.UnregisterStateObserver(this);
        m_connectToServerWindow.Destroy();
        m_connectToPeerWindow.Destroy();
        lResult = OnWindowMessageDefault(hWnd,msg,wParam,lParam);
        return lResult;
    }

    virtual LRESULT On_WM_LBUTTONUP_WindowMessage
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        LRESULT lResult = 0;
        m_mainWindow.OnLButtonUp();
        lResult = OnWindowMessageDefault(hWnd,msg,wParam,lParam);
        return lResult;
    }
    virtual LRESULT On_WM_RBUTTONUP_WindowMessage
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        LRESULT lResult = 0;
        m_mainWindow.OnRButtonUp();
        lResult = OnWindowMessageDefault(hWnd,msg,wParam,lParam);
        return lResult;
    }
    virtual LRESULT On_WM_MBUTTONUP_WindowMessage
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        LRESULT lResult = 0;
        if ((UserInterface::STREAMING == m_mainWindow.current_ui())) {
            if (!(m_cantUseOpenGLRenderer)) {
                m_useOpenGLRenderer = !m_useOpenGLRenderer;
                InvalidateRect(hWnd, NULL, TRUE);
            }
        }
        lResult = OnWindowMessageDefault(hWnd,msg,wParam,lParam);
        return lResult;
    }

    virtual LRESULT On_WM_ERASEBKGND_WindowMessage
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        LRESULT lResult = 0;
        return lResult;
    }
    virtual LRESULT On_WM_SIZE_WindowMessage
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        LRESULT lResult = 0;
        RECT rect;
        if ((GetClientRect(hWnd, &rect))) {
            if (!(m_cantUseOpenGLRenderer))
                m_glRenderer.Reshape(rect.right-rect.left, rect.bottom-rect.top);
        }
        InvalidateRect(hWnd, NULL, TRUE);
        lResult = OnWindowMessageDefault(hWnd,msg,wParam,lParam);
        m_connectToPeerWindow.OnSize(*this);
        m_connectToServerWindow.OnSize(*this);
        return lResult;
    }
    virtual LRESULT On_WM_PAINT_WindowMessage
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        LRESULT lResult = 0;
        uint8_t* localImage; int localImageWidth, localImageHeight, localImageFormat;
        uint8_t* remoteImage; int remoteImageWidth, remoteImageHeight, remoteImageFormat;

        if ((UserInterface::STREAMING == m_mainWindow.current_ui())) {
            if ((remoteImage = m_mainWindow.AcquireRemoteImage(remoteImageWidth, remoteImageHeight, remoteImageFormat))) {
                if ((localImage = m_mainWindow.AcquireLocalImage(localImageWidth, localImageHeight, localImageFormat))) {
                    OnPaintImage
                    (hWnd, remoteImage, remoteImageWidth, remoteImageHeight,
                     localImage, localImageWidth, localImageHeight);
                    m_mainWindow.ReleaseLocalImage(localImage);
                } else {
                    OnPaintImage
                    (hWnd, remoteImage, remoteImageWidth, remoteImageHeight);
                }
                m_mainWindow.ReleaseRemoteImage(remoteImage);
            } else {
                if ((localImage = m_mainWindow.AcquireLocalImage(localImageWidth, localImageHeight, localImageFormat))) {
                    OnPaintImage
                    (hWnd, localImage, localImageWidth, localImageHeight);
                     m_mainWindow.ReleaseLocalImage(localImage);
                } else {
                    OnPaintBlank(hWnd);
                }
            }
        } else {
            OnPaintBlank(hWnd);
        }
        return lResult;
    }

    virtual void OnPaintImage
    (HWND hWnd, uint8_t* remoteImage, int remoteImageWidth, int remoteImageHeight,
     uint8_t* localImage, int localImageWidth, int localImageHeight) {
        if ((m_useOpenGLRenderer)) {
            ValidateRect(hWnd, NULL);
            m_glRenderer.Render
            (remoteImage, remoteImageWidth, remoteImageHeight,
             localImage, localImageWidth, localImageHeight);
            m_glRenderer.SwapBuffers();
        } else {
            m_gcRenderer.Render
            (remoteImage, remoteImageWidth, remoteImageHeight,
             localImage, localImageWidth, localImageHeight);
        }
    }
    virtual void OnPaintImage
    (HWND hWnd, uint8_t* remoteImage, int remoteImageWidth, int remoteImageHeight) {
        if ((m_useOpenGLRenderer)) {
            ValidateRect(hWnd, NULL);
            m_glRenderer.Render
            (remoteImage, remoteImageWidth, remoteImageHeight);
            m_glRenderer.SwapBuffers();
        } else {
            m_gcRenderer.Render
            (remoteImage, remoteImageWidth, remoteImageHeight);
        }
    }

    virtual void OnPaintBlank(HWND hWnd) {
        HDC hDC;
        PAINTSTRUCT ps;
        if ((hDC = BeginPaint(hWnd, &ps))) {
            RECT rc;
            if ((GetClientRect(hWnd, &rc))) {
                HBRUSH hBrush;
                switch (m_mainWindow.current_ui()) {
                case UserInterface::CONNECT_TO_SERVER:
                    if ((hBrush = CreateSolidBrush(m_connectToServerColor))) {
                        FillRect(hDC, &rc, hBrush);
                        DeleteObject(hBrush);

                        std::string text(m_connectToServerBefore.c_str());
                        text += m_mainWindow.GetServerName();
                        text += m_connectToServerAfter.c_str();

                        DrawWhiteText
                        (hDC, rc, text.c_str(),
                         DT_SINGLELINE | DT_CENTER | DT_VCENTER);
                    }
                    break;
                case UserInterface::LIST_PEERS:
                    if ((hBrush = CreateSolidBrush(m_connectToPeerColor))) {
                        FillRect(hDC, &ps.rcPaint, hBrush);
                        DeleteObject(hBrush);

                        std::string text(m_connectToPeerBefore.c_str());
                        text += m_mainWindow.GetConnectToPeerName();
                        text += m_connectToPeerAfter.c_str();

                        DrawWhiteText
                        (hDC, rc, text.c_str(),
                         DT_SINGLELINE | DT_CENTER | DT_VCENTER);
                    }
                    break;
                case UserInterface::STREAMING:
                    if ((hBrush = CreateSolidBrush(m_connectingColor))) {
                        FillRect(hDC, &ps.rcPaint, hBrush);
                        DeleteObject(hBrush);
                    }
                    break;
                default:
                    if ((hBrush = CreateSolidBrush(m_backgroundColor))) {
                        FillRect(hDC, &ps.rcPaint, hBrush);
                        DeleteObject(hBrush);
                    }
                }
            }
            EndPaint(hWnd, &ps);
        }
    }
    virtual void DrawWhiteText
    (HDC dc, RECT& rect, const char* text, int flags)
    {
        HGDIOBJ oldFont = SelectObject(dc, GetDefaultFont());
        SetTextColor(dc, RGB(0xff, 0xff, 0xff));
        SetBkMode(dc, TRANSPARENT);
        DrawTextA(dc, text, -1, &rect, flags);
        SelectObject(dc, oldFont);
    }
    virtual HFONT GetDefaultFont()
    {
        HFONT font = (HFONT)(GetStockObject(DEFAULT_GUI_FONT));
        return font;
    }

    ///////////////////////////////////////////////////////////////////////
    // ui state observer
    ///////////////////////////////////////////////////////////////////////
    virtual void OnChangeStateToConnectToServer() {
        m_connectToPeerWindow.Hide();
        m_connectToServerWindow.Show();
        Invalidate();
    }
    virtual void OnChangeStateToListPeers() {
        m_connectToServerWindow.Hide();
        m_connectToPeerWindow.Show();
        Invalidate();
    }
    virtual void OnChangeStateToStreaming() {
        m_connectToServerWindow.Hide();
        m_connectToPeerWindow.Hide();
    }
    virtual void OnChangeState(const std::string& toState) {}

    ///////////////////////////////////////////////////////////////////////
    // image observer
    ///////////////////////////////////////////////////////////////////////
    virtual bool InvalidateWindow(bool eraseBackground = true) { 
        ImageObserverInterface* imageObserverInterface;
        if ((imageObserverInterface = ImageObserverInterfaceDelegated()))
            return imageObserverInterface->InvalidateWindow(eraseBackground);
        else {
            if ((UserInterface::STREAMING == m_mainWindow.current_ui()))
                Invalidate(eraseBackground);
        }
        return false; 
    }
    virtual bool ValidateWindow() { 
        ImageObserverInterface* imageObserverInterface;
        if ((imageObserverInterface = ImageObserverInterfaceDelegated()))
            return imageObserverInterface->ValidateWindow();
        else {
            if ((UserInterface::STREAMING == m_mainWindow.current_ui()))
                Validate();
        }
        return false; 
    }
    virtual bool IsWindow() const { 
        ImageObserverInterface* imageObserverInterface;
        if ((imageObserverInterface = ImageObserverInterfaceDelegated()))
            return imageObserverInterface->IsWindow();
        return true; 
    }
    virtual ImageObserverInterface* ImageObserverInterfaceDelegated() const  {
        return 0;
    }

protected:
    PeerMainWindow& m_mainWindow;
    bool m_autoConnectToServer;
    bool m_useOpenGLRenderer;
    bool m_cantUseOpenGLRenderer;
    COLORREF m_backgroundColor;
    COLORREF m_connectToServerColor;
    COLORREF m_connectToPeerColor;
    COLORREF m_connectingColor;
    std::string m_connectToServerBefore;
    std::string m_connectToServerAfter;
    std::string m_connectToPeerBefore;
    std::string m_connectToPeerAfter;
    windows::OpenGLRenderer m_glRenderer;
    windows::GCRenderer m_gcRenderer;
    windows::ConnectToServerWindow m_connectToServerWindow;
    windows::ConnectToPeerWindow m_connectToPeerWindow;
};

namespace windows {

typedef MainWindow::WindowPeer MainWindowPeer;

} // namespace windows 
} // namespace client 
} // namespace peerconnection 
} // namespace webrtc 
} // namespace xos 

#endif // _XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOWS_MAINWINDOWPEER_HPP 
