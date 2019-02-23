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
///   File: WindowObject.hpp
///
/// Author: $author$
///   Date: 4/6/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_X11_XT_WINDOWOBJECT_HPP
#define _XOS_GUI_X11_XT_WINDOWOBJECT_HPP

#include "xos/gui/x11/xt/RectObject.hpp"

namespace xos {
namespace x11 {
namespace xt {

typedef RectObjectImplement WindowObjectImplement;
typedef RectObject WindowObjectExtend;
///////////////////////////////////////////////////////////////////////
///  Class: WindowObject
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS WindowObject
: virtual public WindowObjectImplement, public WindowObjectExtend {
public:
    typedef WindowObjectImplement Implements;
    typedef WindowObjectExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: WindowObject
    ///////////////////////////////////////////////////////////////////////
    WindowObject
    (XDisplay* xDisplay = 0, XtWidget xtWidget = 0, 
     XtWidgetClass xtWidgetClass = 0, 
     const XtChar* widgetName = XOS_GUI_X11_XT_WIDGET_NAME, 
     bool isCreated = false)
    : Extends(xDisplay, xtWidget, xtWidgetClass, widgetName, isCreated) {
    }
    virtual ~WindowObject() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Realize() {
        XtWidget xtWidget;
        if ((xtWidget = m_attachedTo)) {
            XtRealizeWidget(xtWidget);
            return true;
        }
        return false;
    }
    virtual bool Unrealize() {
        XtWidget xtWidget;
        if ((xtWidget = m_attachedTo)) {
            XtUnrealizeWidget(xtWidget);
            return true;
        }
        return false;
    }
    virtual XWindow WindowAttachedTo() const {
        XtWidget xtWidget;
        if ((xtWidget = m_attachedTo)) {
            return XtWindow(xtWidget);
        }
        return 0;
    }
};


} // namespace xt 
} // namespace x11 
} // namespace xos 


#endif // _XOS_GUI_X11_XT_WINDOWOBJECT_HPP 
        

