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
///   File: ApplicationShell.hpp
///
/// Author: $author$
///   Date: 4/25/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_X11_XT_APPLICATIONSHELL_HPP
#define _XOS_GUI_X11_XT_APPLICATIONSHELL_HPP

#include "xos/gui/x11/xt/WMShell.hpp"
#include <X11/Shell.h>

#define XOS_GUI_X11_XT_APPLICATIONSHELL_WIDGET_NAME "xos::x11::xt::ApplicationShell"
#define XOS_GUI_X11_XT_APPLICATIONSHELL_WIDGET_CLASS_NAME XOS_GUI_X11_XT_APPLICATIONSHELL_WIDGET_NAME
#define XOS_GUI_X11_XT_APPLICATIONSHELL_WIDGET_CLASS applicationShellWidgetClass

namespace xos {
namespace x11 {
namespace xt {

typedef WMShellImplement ApplicationShellImplement;
typedef WMShell ApplicationShellExtend;
///////////////////////////////////////////////////////////////////////
///  Class: ApplicationShell
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS ApplicationShell
: virtual public ApplicationShellImplement, public ApplicationShellExtend {
public:
    typedef ApplicationShellImplement Implements;
    typedef ApplicationShellExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: ApplicationShell
    ///////////////////////////////////////////////////////////////////////
    ApplicationShell
    (XDisplay* xDisplay = 0, XtWidget xtWidget = 0, 
     XtWidgetClass xtWidgetClass = XOS_GUI_X11_XT_APPLICATIONSHELL_WIDGET_CLASS, 
     const XtChar* widgetName = XOS_GUI_X11_XT_APPLICATIONSHELL_WIDGET_NAME, 
     const XtChar* widgetClassName = XOS_GUI_X11_XT_APPLICATIONSHELL_WIDGET_CLASS_NAME, 
     bool isCreated = false)
    : Extends(xDisplay, xtWidget, xtWidgetClass, widgetName, widgetClassName, isCreated)
    {
    }
    virtual ~ApplicationShell()
    {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Create
    (XDisplay* xDisplay, XtWidgetClass xtWidgetClass, 
     const XtChar* widgetName, const XtChar* widgetClassName,
     XtArgList xtArgList, Cardinal argCount) {
        XtWidget detached;
        if ((detached = CreateAttached
            (xDisplay, xtWidgetClass, widgetName, widgetClassName, xtArgList, argCount))) {
             return true;
        }
        return false;
    }
    virtual XtWidget CreateAttached
    (XDisplay* xDisplay, XtArgList xtArgList, Cardinal argCount) {
        XtWidget detached = 0;
        XtWidgetClass xtWidgetClass;
        const XtChar* widgetName;
        const XtChar* widgetClassName;
        if ((xtWidgetClass = m_widgetClass.AttachedTo()))
        if ((widgetName = m_widgetName.Chars()))
        if ((widgetClassName = m_widgetClassName.Chars()))
            detached = CreateAttached
            (xDisplay, xtWidgetClass, widgetName, widgetClassName, xtArgList, argCount);
        return detached;
    }
    virtual XtWidget CreateAttached
    (XDisplay* xDisplay, const XtChar* widgetName, const XtChar* widgetClassName,
     XtArgList xtArgList, Cardinal argCount) {
        XtWidget detached = 0;
        XtWidgetClass xtWidgetClass;
        if ((xtWidgetClass = m_widgetClass.AttachedTo()))
            detached = CreateAttached
            (xDisplay, xtWidgetClass, widgetName, widgetClassName, xtArgList, argCount);
        return detached;
    }
    virtual XtWidget CreateAttached
    (XDisplay* xDisplay, XtWidgetClass xtWidgetClass, 
     const XtChar* widgetName, const XtChar* widgetClassName,
     XtArgList xtArgList, Cardinal argCount) {
        XtWidget detached = 0;
        if ((Destroyed()))
        if ((detached = CreateDetached
            (xDisplay, xtWidgetClass, widgetName, widgetClassName, xtArgList, argCount))) {
            AttachCreated(xDisplay, detached);
        }
        return detached;
    }
    virtual XtWidget CreateDetached
    (XDisplay* xDisplay, XtWidgetClass xtWidgetClass, 
     const XtChar* widgetName, const XtChar* widgetClassName,
     XtArgList xtArgList, Cardinal argCount) const {
        XtWidget detached = 0;
        if ((xDisplay) && (xtWidgetClass) && (widgetName) && (widgetClassName) && (xtArgList)) {
            if (!(detached = XtAppCreateShell
                (widgetName, widgetClassName, xtWidgetClass, xDisplay, xtArgList, argCount))) {
                XOS_LOG_ERROR("failed on XtAppCreateShell()");
            }
        }
        return detached;
    }
};

} // namespace xt 
} // namespace x11 
} // namespace xos 

#endif // _XOS_GUI_X11_XT_APPLICATIONSHELL_HPP 
