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
///   File: WMShell.hpp
///
/// Author: $author$
///   Date: 4/6/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_X11_XT_WMSHELL_HPP
#define _XOS_GUI_X11_XT_WMSHELL_HPP

#include "xos/gui/x11/xt/WindowObject.hpp"
#include "xos/gui/x11/xm/WmHints.hpp"
#include "xos/gui/x11/xm/MwmUtil.hpp"

namespace xos {
namespace x11 {
namespace xt {

typedef WindowObjectImplement WMShellImplement;
typedef WindowObject WMShellExtend;
///////////////////////////////////////////////////////////////////////
///  Class: WMShell
///
/// Author: $author$
///   Date: 4/6/2013
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS WMShell
: virtual public WMShellImplement, public WMShellExtend {
public:
    typedef WMShellImplement Implements;
    typedef WMShellExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: WMShell
    ///////////////////////////////////////////////////////////////////////
    WMShell
    (XDisplay* xDisplay = 0, XtWidget xtWidget = 0, 
     XtWidgetClass xtWidgetClass = 0, 
     const XtChar* widgetName = XOS_GUI_X11_XT_WIDGET_NAME, 
     const XtChar* widgetClassName = XOS_GUI_X11_XT_WIDGET_CLASS_NAME, 
     bool isCreated = false)
    : Extends(xDisplay, xtWidget, xtWidgetClass, widgetName, isCreated),
      m_widgetClassName(widgetClassName) {
    }
    virtual ~WMShell() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool ChangeWMDecorations
    (xm::WmHints& mwmHints, CARD32 decorations) {
        return ChangeWMHints(mwmHints, MWM_HINTS_DECORATIONS, 0, decorations);
    }
    virtual bool ChangeWMHints
    (xm::WmHints& mwmHints,
     CARD32 flags = 0, CARD32 functions = 0, 
     CARD32 decorations = 0, INT32 inputMode = 0) {
        XDisplay* xDisplay;
        XWindow xWindow;
        if (((xDisplay = DisplayAttachedTo()) != 0) 
            && ((xWindow = WindowAttachedTo()) != None)) {

            if (MWM_HINTS_DECORATIONS == (flags & MWM_HINTS_DECORATIONS))
                XUnmapWindow(xDisplay, xWindow);

            bool isSuccess = mwmHints.Change
            (*xDisplay, xWindow, flags, functions, decorations, inputMode);

            if (MWM_HINTS_DECORATIONS == (flags & MWM_HINTS_DECORATIONS))
                XMapWindow(xDisplay, xWindow);
            return isSuccess;
        }
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    String m_widgetClassName;
};

} // namespace xt 
} // namespace x11 
} // namespace xos 

#endif // _XOS_GUI_X11_XT_WMSHELL_HPP 
