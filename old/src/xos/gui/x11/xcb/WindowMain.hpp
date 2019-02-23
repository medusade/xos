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
///   Date: 3/18/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_X11_XCB_WINDOWMAIN_HPP
#define _XOS_GUI_X11_XCB_WINDOWMAIN_HPP

#include "xos/gui/x11/xcb/Main.hpp"
#include "xos/gui/x11/xcb/Window.hpp"
#include "xos/gui/x11/xcb/EventTarget.hpp"

#define XOS_GUI_X11_XCB_WINDOWMAIN_DEFAULT_MAINWINDOW_X 0
#define XOS_GUI_X11_XCB_WINDOWMAIN_DEFAULT_MAINWINDOW_Y 0
#define XOS_GUI_X11_XCB_WINDOWMAIN_DEFAULT_MAINWINDOW_WIDTH 128
#define XOS_GUI_X11_XCB_WINDOWMAIN_DEFAULT_MAINWINDOW_HEIGHT 128
#define XOS_GUI_X11_XCB_WINDOWMAIN_DEFAULT_MAINWINDOW_BORDER_WIDTH 0

namespace xos {
namespace x11 {
namespace xcb {

typedef MainImplement WindowMainImplementImplement;
///////////////////////////////////////////////////////////////////////
///  Class: WindowMainImplement
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS WindowMainImplement
: virtual public EventTarget, virtual public WindowMainImplementImplement {
public:
    typedef WindowMainImplementImplement Implements;
};
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
    : m_mainWindowX(XOS_GUI_X11_XCB_WINDOWMAIN_DEFAULT_MAINWINDOW_X),
      m_mainWindowY(XOS_GUI_X11_XCB_WINDOWMAIN_DEFAULT_MAINWINDOW_Y),
      m_mainWindowWidth(XOS_GUI_X11_XCB_WINDOWMAIN_DEFAULT_MAINWINDOW_WIDTH),
      m_mainWindowHeight(XOS_GUI_X11_XCB_WINDOWMAIN_DEFAULT_MAINWINDOW_HEIGHT),
      m_mainWindowBorderWidth(XOS_GUI_X11_XCB_WINDOWMAIN_DEFAULT_MAINWINDOW_BORDER_WIDTH),
      m_mainWindow(0) {
    }
    virtual ~WindowMain() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int Run(int argc, char** argv, char** env) {
        int err = 0;
        int err2;
        if (!(err = BeforeCreateMainWindow(argc, argv, env))) {
            if ((m_mainWindow = CreateMainWindow(argc, argv, env))) {

                EventTargets::Instance().Insert(m_mainWindow->AttachedTo(), m_mainWindow);

                if (!(err = AfterCreateMainWindow(*m_mainWindow, argc, argv, env))) {
                    if (!(err = MapMainWindow(*m_mainWindow, argc, argv, env))) {
                        err = ProcessEvents(*m_mainWindow, argc, argv, env);
                    }
                }

                if ((err2 = BeforeDestroyMainWindow(*m_mainWindow, argc, argv, env)))
                if (!(err))err = err2;

                EventTargets::Instance().Delete(m_mainWindow->AttachedTo());

                if ((err2 = DestroyMainWindow(m_mainWindow, argc, argv, env)))
                if (!(err))err = err2;

                m_mainWindow = 0;
            }
        }
        return err;
    }
    virtual int ProcessEvents
    (Window& mainWindow, int argc, char** argv, char** env) {
        int err = 0;
        bool done = false;
        xcb_connection_t* xcbConnection;
        xcb_generic_event_t* xcbEvent;
        if ((xcbConnection = GetConnection().AttachedTo())) {
            while (!(done)) {
                if ((xcbEvent = xcb_wait_for_event(xcbConnection))) {
                    done = ProcessEvent(*xcbEvent);
                    free(xcbEvent);
                } else {
                    break;
                }
            }
        }
        return err;
    }
    virtual bool ProcessEvent(const xcb_generic_event_t& xcbEvent) {
        bool isDone = false;
        isDone = OnEvent(xcbEvent);
        return isDone;
    }
    virtual bool OnEvent(const xcb_generic_event_t& xcbEvent) {
        EventTargets& targets = EventTargets::Instance();
        bool isDone = false;
        EventTarget* target;

        if ((target = targets.Find(xcbEvent.pad[0])))
            isDone = target->OnEvent(xcbEvent);

        if ((EventTarget::OnEvent(xcbEvent)))
        if (!(isDone))
            isDone = true;
        return isDone;
    }
    virtual bool OnEventDefault(const xcb_generic_event_t& xcbEvent) {
        bool isDone = false;
        return isDone;
    }
    virtual int MapMainWindow
    (Window& mainWindow, int argc, char** argv, char** env) {
        int err = 0;
        if (!(mainWindow.Map()))
            err = 1;
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int BeforeCreateMainWindow(int argc, char** argv, char** env) {
        int err = 0;
        return err;
    }
    virtual int AfterCreateMainWindow
    (Window& mainWindow, int argc, char** argv, char** env) {
        int err = 0;
        return err;
    }
    virtual int BeforeDestroyMainWindow
    (Window& mainWindow, int argc, char** argv, char** env) {
        int err = 0;
        return err;
    }
    virtual int AfterDestroyMainWindow(int argc, char** argv, char** env) {
        int err = 0;
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual Window* CreateMainWindow
    (int argc, char** argv, char** env) {
        Connection& connection = GetConnection();
        Setup& setup = GetSetup();
        Screen& screen = GetScreen();
        if ((m_defaultMainWindow.Create
            (connection.AttachedTo(), screen.RootDepth(), screen.RootWindowId(), 
             m_mainWindowX,m_mainWindowY, m_mainWindowWidth,m_mainWindowHeight, 
             m_mainWindowBorderWidth, screen.WhitePixel(), screen.RootVisualId()))) {
            return &m_defaultMainWindow;
        }
        return 0;
    }
    virtual bool DestroyMainWindow
    (Window* mainWindow, int argc, char** argv, char** env) {
        return false;
    }

    virtual EventTargets& GetEventTargets() const {
        return (EventTargets&)(m_eventTargets);
    }
protected:
    int16_t m_mainWindowX, m_mainWindowY;
    uint16_t m_mainWindowWidth, m_mainWindowHeight, m_mainWindowBorderWidth;
    Window* m_mainWindow;
    Window m_defaultMainWindow;
    EventTargets m_eventTargets;
};


} // namespace xcb 
} // namespace x11 
} // namespace xos 


#endif // _XOS_GUI_X11_XCB_WINDOWMAIN_HPP 
        

