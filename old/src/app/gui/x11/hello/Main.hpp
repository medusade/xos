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
///   File: Main.hpp
///
/// Author: $author$
///   Date: 3/24/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_X11_HELLO_MAIN_HPP
#define _XOS_GUI_X11_HELLO_MAIN_HPP

#include "app/gui/x11/opengl/hello/Main.hpp"
#include "xos/gui/x11/WindowMain.hpp"
#include "xos/gui/x11/MainWindow.hpp"

namespace xos {
namespace x11 {
namespace hello {

typedef x11::MainWindowImplement MainWindowImplement;
typedef x11::MainWindow MainWindowExtendExtend;
typedef x11::opengl::hello::MainT
<MainWindowImplement, MainWindowExtendExtend> MainWindowExtend;
///////////////////////////////////////////////////////////////////////
///  Class: MainWindow
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS MainWindow
: virtual public MainWindowImplement, public MainWindowExtend {
public:
    typedef MainWindowImplement Implements;
    typedef MainWindowExtend Extends;
    typedef MainWindow Derives;

    typedef bool (Derives::*MOnButtonReleaseXEvent)(const XEvent& xEvent);

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: MainWindow
    ///////////////////////////////////////////////////////////////////////
    MainWindow(WindowMain& main)
    : m_main(main), m_onButtonReleaseXEvent(0) {
    }
    virtual ~MainWindow() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int OnCreate(int argc, char** argv, char** env) {
        XDisplay* xDisplay;
        XWindow xWindow;
        if ((xDisplay = m_display) && (xWindow = m_attachedTo)) {

            StoreName("Hello");

            if ((optind < argc))
                m_imageFile = argv[optind];

            if ((LoadImageFile(m_imageFile))) {
                if ((m_glRenderer.Init(xDisplay, xWindow))) {
                    m_glRenderer.Prepare();
                } else {
                    XOS_LOG_ERROR("failed on m_glRenderer.Init()");
                    FreeImage();
                    ChangeBackground(m_main.RedColor());
                }
            } else {
                ChangeBackground(m_main.RedColor());
            }
        }
        return 0;
    }
    virtual int OnDestroy(int argc, char** argv, char** env) {
        if (!(m_glRenderer.Finish())) {
            XOS_LOG_ERROR("failed on m_glRenderer.Finish()");
        }
        FreeImage();
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool OnConfigureNotifyXEvent(const XEvent& xEvent) {
        const XConfigureEvent& xConfigureEvent = (const XConfigureEvent&)(xEvent);
        bool isHandled = false;
        if ((m_image)) {
            m_glRenderer.Reshape(xConfigureEvent.width, xConfigureEvent.height);
            Invalidate();
        }
        isHandled = OnXEventDefault(xEvent);
        return isHandled;
    }
    virtual bool OnExposeXEvent(const XEvent& xEvent) {
        bool isHandled = false;
        if ((m_render))
            (this->*m_render)();
        else
        RenderRaw();
        isHandled = OnXEventDefault(xEvent);
        return isHandled;
    }
    virtual bool OnButtonPressXEvent(const XEvent& xEvent) {
        bool isHandled = false;
        XOS_LOG_DEBUG("...");
        isHandled = OnXEventDefault(xEvent);
        return isHandled;
    }
    virtual bool OnButtonReleaseXEvent(const XEvent& xEvent) {
        bool isHandled = false;
        XOS_LOG_DEBUG("...");
        if ((m_onButtonReleaseXEvent))
            isHandled = (this->*m_onButtonReleaseXEvent)(xEvent);
        else {
            isHandled = OnRenderRawButtonReleaseXEvent(xEvent);
        }
        return isHandled;
    }
    virtual bool OnRenderRawButtonReleaseXEvent(const XEvent& xEvent) {
        bool isHandled = false;
        m_onButtonReleaseXEvent = &Derives::OnRenderButtonReleaseXEvent;
        m_render = &Derives::Render;
        Invalidate();
        return isHandled;
    }
    virtual bool OnRenderButtonReleaseXEvent(const XEvent& xEvent) {
        bool isHandled = false;
        m_onButtonReleaseXEvent = &Derives::OnRenderInButtonReleaseXEvent;
        m_render = &Derives::RenderIn;
        Invalidate();
        return isHandled;
    }
    virtual bool OnRenderInButtonReleaseXEvent(const XEvent& xEvent) {
        bool isHandled = false;
        m_onButtonReleaseXEvent = &Derives::OnRenderRawButtonReleaseXEvent;
        m_render = &Derives::RenderRaw;
        Invalidate();
        return isHandled;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    WindowMain& m_main;
    MOnButtonReleaseXEvent m_onButtonReleaseXEvent;
};

typedef WindowMainImplement MainImplement;
typedef WindowMain MainExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Main
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Main: virtual public MainImplement, public MainExtend {
public:
    typedef MainImplement Implements;
    typedef MainExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: Main
    ///////////////////////////////////////////////////////////////////////
    Main(): m_mainWindow(*this) {
    }
    virtual ~Main() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual MainWindow& defaultMainWindow() const {
        return (MainWindow&)(m_mainWindow);
    }
protected:
    MainWindow m_mainWindow;
};

} // namespace hello 
} // namespace x11 
} // namespace xos 

#endif // _XOS_GUI_X11_HELLO_MAIN_HPP 
