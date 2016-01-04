///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2013 $organization$
///
/// This software is provided by the author and contributors ``as is'' 
/// and any express or implied warranties, including, but not limited to, 
/// the implied warranties of merchantability and fitness for a particular 
/// purpose are disclaimed. In no event shall the author or contributors 
/// be liable for any direct, indirect, incidental, special, exemplary, 
/// or consequential damages (including, but not limited to, procurement 
/// of substitute goods or services; loss of use, data, or profits; or 
/// business interruption) however caused and on any theory of liability, 
/// whether in contract, strict liability, or tort (including negligence 
/// or otherwise) arising in any way out of the use of this software, 
/// even if advised of the possibility of such damage.
///
///   File: WindowMain.hpp
///
/// Author: $author$
///   Date: 3/24/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_X11_WINDOWMAIN_HPP
#define _XOS_GUI_X11_WINDOWMAIN_HPP

#include "xos/gui/x11/Main.hpp"
#include "xos/gui/x11/MainWindow.hpp"
#include "xos/gui/x11/Window.hpp"
#include "xos/gui/x11/Atom.hpp"

#define XOS_GUI_X11_WINDOWMAIN_DEFAULT_WINDOW_X 0
#define XOS_GUI_X11_WINDOWMAIN_DEFAULT_WINDOW_Y \
    XOS_GUI_X11_WINDOWMAIN_DEFAULT_WINDOW_X

#define XOS_GUI_X11_WINDOWMAIN_DEFAULT_WINDOW_WIDTH 100
#define XOS_GUI_X11_WINDOWMAIN_DEFAULT_WINDOW_HEIGHT \
    XOS_GUI_X11_WINDOWMAIN_DEFAULT_WINDOW_WIDTH

#define XOS_GUI_X11_WINDOWMAIN_DEFAULT_WINDOW_BORDER_WIDTH 0
#define XOS_GUI_X11_WINDOWMAIN_DEFAULT_WINDOW_BORDER_COLOR 0
#define XOS_GUI_X11_WINDOWMAIN_DEFAULT_WINDOW_BACKGROUND_COLOR 0

namespace xos {
namespace x11 {

typedef MainImplement WindowMainImplement;
typedef Main WindowMainExtend;
///////////////////////////////////////////////////////////////////////
///  Class: WindowMain
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS WindowMain
: virtual public WindowMainImplement, public WindowMainExtend {
public:
    typedef WindowMainImplement Implements;
    typedef WindowMainExtend Extends;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: WindowMain
    ///////////////////////////////////////////////////////////////////////
    WindowMain()
    : m_mainWindowX(XOS_GUI_X11_WINDOWMAIN_DEFAULT_WINDOW_X),
      m_mainWindowY(XOS_GUI_X11_WINDOWMAIN_DEFAULT_WINDOW_Y),
      m_mainWindowWidth(XOS_GUI_X11_WINDOWMAIN_DEFAULT_WINDOW_WIDTH),
      m_mainWindowHeight(XOS_GUI_X11_WINDOWMAIN_DEFAULT_WINDOW_HEIGHT),
      m_mainWindowBorderWidth(XOS_GUI_X11_WINDOWMAIN_DEFAULT_WINDOW_BORDER_WIDTH),
      m_mainWindowBorderColor(XOS_GUI_X11_WINDOWMAIN_DEFAULT_WINDOW_BORDER_COLOR),
      m_mainWindowBackgroundColor(XOS_GUI_X11_WINDOWMAIN_DEFAULT_WINDOW_BACKGROUND_COLOR),
      m_mainWindow(0) {
    }
    virtual ~WindowMain() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool OnClientMessageXEvent(const XEvent& xEvent) {
        bool isHandled = false;
        XOS_LOG_DEBUG("...");
        if (m_atom_WM_PROTOCOLS.AttachedTo() == xEvent.xclient.message_type)
        if ((isHandled = On_WM_PROTOCOLS_ClientMessageXEvent(xEvent)))
            return isHandled;
        isHandled = OnXEventDefault(xEvent);
        return isHandled;
    }
    virtual bool On_WM_PROTOCOLS_ClientMessageXEvent(const XEvent& xEvent) {
        bool isHandled = false;
        XOS_LOG_DEBUG("...");
        if (m_atom_WM_DELETE_WINDOW.AttachedTo() == (xEvent.xclient.data.l[0]))
            isHandled = On_WM_DELETE_WINDOW_ClientMessageXEvent(xEvent);
        return isHandled;
    }
    virtual bool On_WM_DELETE_WINDOW_ClientMessageXEvent(const XEvent& xEvent) {
        bool isHandled = false;
        XOS_LOG_DEBUG("...");
        SetDoneProcessingXEvents();
        return isHandled;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int AfterOpenDisplay
    (XDisplay& xDisplay, XScreen& xScreen, int argc, char** argv, char** env) {
        int err = 0;
        if (!(err = Extends::AfterOpenDisplay(xDisplay, xScreen, argc, argv, env))) {
            m_mainWindowBorderColor = GetMainWindowBorderColor();
            m_mainWindowBackgroundColor = GetMainWindowBackgroundColor();
        }
        return err;
    }
    virtual XPixel GetMainWindowBorderColor() const {
        return BlackColor();
    }
    virtual XPixel GetMainWindowBackgroundColor() const {
        return WhiteColor();
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int BeforeProcessXEvents(int argc, char** argv, char** env) {
        int err = 1;
        XDisplay* xDisplay;
        XWindow xWindow;
        XAtom xAtom;

        if ((xDisplay = m_display.AttachedTo()))
        if (None != (xWindow = m_display.RootWindowAttachedTo())) {
            m_rootWindow.Attach(xDisplay, xWindow);
            m_atom_WM_PROTOCOLS.AttachIntern(*xDisplay, XOS_GUI_X11_ATOM_NAME_WM_PROTOCOLS);
            m_atom_WM_DELETE_WINDOW.AttachIntern(*xDisplay, XOS_GUI_X11_ATOM_NAME_WM_DELETE_WINDOW);
            if (!(err = BeforeOpenMainWindow(argc, argv, env))) {
                if ((m_mainWindow = OpenMainWindow(argc, argv, env))) {
                    if ((xWindow = m_mainWindow->AttachedTo()) 
                        && (xAtom = m_atom_WM_DELETE_WINDOW.AttachedTo())) {
                        if (!(XSetWMProtocols(xDisplay, xWindow, &xAtom, 1)))
                        {   XOS_LOG_ERROR("failed on XSetWMProtocols()"); }
                    }
                    if (!(err = AfterOpenMainWindow(*m_mainWindow, argc, argv, env)))
                        return err;
                    CloseMainWindow(m_mainWindow, argc, argv, env);
                    m_mainWindow = 0;
                } else {
                    err = 1;
                }
            }
            m_rootWindow.Detach();
        }
        return err;
    }
    virtual int AfterProcessXEvents(int argc, char** argv, char** env) {
        int err = 1;
        if ((m_mainWindow)) {
            err = BeforeCloseMainWindow(*m_mainWindow, argc, argv, env);
            if (!(CloseMainWindow(m_mainWindow, argc, argv, env)))
            if (!(err)) err = 1;
            m_mainWindow = 0;
        }
        m_rootWindow.Detach();
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int BeforeOpenMainWindow(int argc, char** argv, char** env) {
        int err = 0;
        return err;
    }
    virtual int AfterOpenMainWindow
    (MainWindow& mainWindow, int argc, char** argv, char** env) {
        int err = 0;
        return err;
    }
    virtual int BeforeCloseMainWindow
    (MainWindow& mainWindow, int argc, char** argv, char** env) {
        int err = 0;
        return err;
    }
    virtual int AfterCloseMainWindow(int argc, char** argv, char** env) {
        int err = 0;
        return err;
    }
    virtual MainWindow* OpenMainWindow(int argc, char** argv, char** env) {
        MainWindow* mainWindow = 0;
        XDisplay* xDisplay;
        XWindow xWindow;
        int err;
        if ((xDisplay = m_display.AttachedTo())) {
            if ((mainWindow = CreateMainWindow(argc, argv, env))) {
                if (!(err = mainWindow->OnCreate(argc, argv, env))) {
                    EventTarget* eventTarget = mainWindow;
                    if (None != (xWindow = mainWindow->AttachedTo()))
                        m_context.Save(*xDisplay, xWindow, (XPointer)(eventTarget));
                    mainWindow->Map();
                } else {
                    DestroyMainWindow(mainWindow, argc, argv, env);
                    mainWindow = 0;
                }
            }
        }
        return mainWindow;
    }
    virtual bool CloseMainWindow
    (MainWindow* mainWindow, int argc, char** argv, char** env) {
        bool isSuccess = false;
        XDisplay* xDisplay;
        XWindow xWindow;
        int err;
        if ((isSuccess = ((xDisplay = m_display.AttachedTo()) && (mainWindow)))) {
            if (!(mainWindow->Unmap()))
                isSuccess = false;

            if (!(m_context.Delete(*xDisplay, xWindow = mainWindow->AttachedTo())))
                isSuccess = false;

            if ((err = mainWindow->OnDestroy(argc, argv, env)))
                isSuccess = false;

            if (!(DestroyMainWindow(mainWindow, argc, argv, env)))
                isSuccess = false;
        }
        return isSuccess;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual MainWindow* CreateMainWindow(int argc, char** argv, char** env) {
        MainWindow* mainWindow = 0;
        XDisplay* xDisplay = 0;
        XWindow xWindow = m_rootWindow.AttachedTo(xDisplay);
        if ((xDisplay) && (None != (xWindow))) {
            if ((mainWindow = CreateMainWindow(*xDisplay, xWindow, argc, argv, env))) {
                XEventMask xEventMask = Window::GetDefaultXEventMask();
                mainWindow->SelectInput(xEventMask);
            }
        }
        return mainWindow;
    }
    virtual MainWindow* CreateMainWindow
    (XDisplay& xDisplay, XWindow xWindow, int argc, char** argv, char** env) {
        MainWindow* mainWindow = 0;
        if ((defaultMainWindow().Create
            (xDisplay, xWindow, 
             m_mainWindowX,m_mainWindowY, m_mainWindowWidth,m_mainWindowHeight, 
             m_mainWindowBorderWidth, m_mainWindowBorderColor, m_mainWindowBackgroundColor)))
            mainWindow = &defaultMainWindow();
        return mainWindow;
    }
    virtual bool DestroyMainWindow
    (MainWindow* mainWindow, int argc, char** argv, char** env) {
        bool isSuccess = false;
        if ((&defaultMainWindow() == mainWindow)) {
            isSuccess = defaultMainWindow().Destroy();
        }
        return isSuccess;
    }
    virtual MainWindow& defaultMainWindow() const {
        return (MainWindow&)(m_defaultMainWindow);
    }

protected:
    int m_mainWindowX;
    int m_mainWindowY;
    unsigned m_mainWindowWidth;
    unsigned m_mainWindowHeight;
    unsigned m_mainWindowBorderWidth;
    XPixel m_mainWindowBorderColor;
    XPixel m_mainWindowBackgroundColor;
    MainWindow* m_mainWindow;
    MainWindow m_defaultMainWindow;
    Window m_rootWindow;
    Atom m_atom_WM_PROTOCOLS;
    Atom m_atom_WM_DELETE_WINDOW;
};

} // namespace x11 
} // namespace xos 

#endif // _XOS_GUI_X11_WINDOWMAIN_HPP 
