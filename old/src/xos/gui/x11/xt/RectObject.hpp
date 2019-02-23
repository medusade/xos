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
///   File: RectObject.hpp
///
/// Author: $author$
///   Date: 4/6/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_X11_XT_RECTOBJECT_HPP
#define _XOS_GUI_X11_XT_RECTOBJECT_HPP

#include "xos/gui/x11/xt/Object.hpp"

namespace xos {
namespace x11 {
namespace xt {

typedef ObjectImplement RectObjectImplement;
typedef Object RectObjectExtend;
///////////////////////////////////////////////////////////////////////
///  Class: RectObject
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS RectObject
: virtual public RectObjectImplement, public RectObjectExtend {
public:
    typedef RectObjectImplement Implements;
    typedef RectObjectExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: RectObject
    ///////////////////////////////////////////////////////////////////////
    RectObject
    (XDisplay* xDisplay = 0, XtWidget xtWidget = 0, 
     XtWidgetClass xtWidgetClass = 0, 
     const XtChar* widgetName = XOS_GUI_X11_XT_WIDGET_NAME, 
     bool isCreated = false)
    : Extends(xDisplay, xtWidget, xtWidgetClass, widgetName, isCreated) {
    }
    virtual ~RectObject() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool SetRectangle(XRectangle& rect) {
        XtArgVal argValX = rect.x;
        XtArgVal argValY = rect.y;
        XtArgVal argValWidth = rect.width;
        XtArgVal argValHeight = rect.height;

        if (4 <= (SetValuesL
            (XtNx, argValX, XtNy, argValY, 
             XtNwidth, argValWidth, XtNheight, argValHeight, 0))) {
            return true;
        }
        return false;
    }
    virtual bool GetRectangle(XRectangle& rect) {
        XtArgVal argValX = 0;
        XtArgVal argValY = 0;
        XtArgVal argValWidth = 0;
        XtArgVal argValHeight = 0;

        if (4 <= (GetValuesL
            (XtNx, &argValX, XtNy, &argValY, 
             XtNwidth, &argValWidth, XtNheight, &argValHeight, 0))) {
            rect.x = (XOffset)(argValX);
            rect.y = (XOffset)(argValY);
            rect.width = (XSize)(argValWidth);
            rect.height = (XSize)(argValHeight);
            return true;
        }
        return false;
    }
    virtual XOffset GetX() {
        XOffset value = 0;
        XtArgVal argVal = 0;
        if (1 <= (GetValuesL(XtNx, &argVal, 0)))
            value = (XOffset)(argVal);
        return value;
    }
    virtual XOffset GetY() {
        XOffset value = 0;
        XtArgVal argVal = 0;
        if (1 <= (GetValuesL(XtNy, &argVal, 0)))
            value = (XOffset)(argVal);
        return value;
    }
    virtual XSize GetWidth() {
        XSize value = 0;
        XtArgVal argVal = 0;
        if (1 <= (GetValuesL(XtNwidth, &argVal, 0)))
            value = (XSize)(argVal);
        return value;
    }
    virtual XSize GetHeight() {
        XSize value = 0;
        XtArgVal argVal = 0;
        if (1 <= (GetValuesL(XtNheight, &argVal, 0)))
            value = (XSize)(argVal);
        return value;
    }
};

} // namespace xt 
} // namespace x11 
} // namespace xos 

#endif // _XOS_GUI_X11_XT_RECTOBJECT_HPP 
