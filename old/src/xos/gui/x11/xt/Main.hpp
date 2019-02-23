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
///   Date: 7/1/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_X11_XT_MAIN_HPP
#define _XOS_GUI_X11_XT_MAIN_HPP

#include "xos/gui/x11/xt/EventHandler.hpp"
#include "xos/gui/x11/xt/Callback.hpp"
#include "xos/gui/x11/xt/AppContext.hpp"
#include "xos/gui/x11/xt/String.hpp"
#include "xos/gui/x11/Main.hpp"

#define XOS_GUI_X11_XT_MAIN_APP_NAME "xos::x11::xt::Main"
#define XOS_GUI_X11_XT_MAIN_APP_CLASS_NAME XOS_GUI_X11_XT_MAIN_APP_NAME

namespace xos {
namespace x11 {
namespace xt {

///////////////////////////////////////////////////////////////////////
///  Class: MainImplement
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS MainImplement
: virtual public x11::MainImplement, 
  virtual public EventHandlerImplement,
  virtual public CallbackImplement {
public:
};
typedef x11::Main MainExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Main
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Main
: virtual public MainImplement, public MainExtend {
public:
    typedef MainImplement Implements;
    typedef MainExtend Extends;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: Main
    ///////////////////////////////////////////////////////////////////////
    Main
    (const XtChar* appName = XOS_GUI_X11_XT_MAIN_APP_NAME,
     const XtChar* appClassName = XOS_GUI_X11_XT_MAIN_APP_CLASS_NAME)
    : m_appName(appName), m_appClassName(appClassName) {
    }
    virtual ~Main() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool ProcessXEvent(XEvent& xEvent, XDisplay& xDisplay) {
        bool isHandled = false;
        XtAppContext xtAppContext;
        if ((xtAppContext = m_appContext.AttachedTo())) {
            isHandled = (False != XtDispatchEvent(&xEvent));
        }
        return isHandled;
    }
    virtual bool NextXEvent(XEvent& xEvent, XDisplay& xDisplay) {
        XtAppContext xtAppContext;
        if ((xtAppContext = m_appContext.AttachedTo())) {
            XtAppNextEvent(xtAppContext, &xEvent);
            return true;
        }
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int BeforeOpenDisplay(int argc, char** argv, char** env) {
        int err = 0;
        XtToolkitInitialize();
        if (!(m_appContext.Create()))
            err = 1;
        return err;
    }
    virtual int AfterCloseDisplay(int argc, char** argv, char** env) {
        int err = 0;
        m_appContext.Destroy();
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual XDisplay* OpenDisplay
    (XScreen*& xScreen, int argc, char** argv, char** env) {
        const char* displayNameChars = m_displayNameChars;
        XDisplay* xDisplay = 0;
        XtAppContext xtAppContext;
        XtString xtAppClassName;
        XtString xtAppName;

        if ((displayNameChars))
        if ((xtAppName = m_appName.str()))
        if ((xtAppClassName = m_appClassName.str()))
        if ((xtAppContext = m_appContext.AttachedTo()))
        if ((xDisplay = XtOpenDisplay
            (xtAppContext, displayNameChars, 
             xtAppName, xtAppClassName, 0,0, &argc, argv))) {
             if ((xScreen = m_display.AttachWithScreenOf(xDisplay)))
                return xDisplay;
             XtCloseDisplay(xDisplay);
             xDisplay = 0;
        } else {   
            XOS_LOG_ERROR("failed on XtOpenDisplay(...," << displayNameChars << ",...)"); 
        }
        return xDisplay;
    }
    virtual bool CloseDisplay(int argc, char** argv, char** env) {
        bool isSuccess = false;
        XDisplay* xDisplay = 0;
        if ((xDisplay = m_display.Detach())) {
            XtCloseDisplay(xDisplay);
        }
        return isSuccess;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    String m_appName;
    String m_appClassName;
    AppContext m_appContext;
};

} // namespace xt 
} // namespace x11 
} // namespace xos 

#endif // _XOS_GUI_X11_XT_MAIN_HPP 
