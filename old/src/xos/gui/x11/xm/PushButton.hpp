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
///   File: PushButton.hpp
///
/// Author: $author$
///   Date: 7/4/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_X11_XM_PUSHBUTTON_HPP
#define _XOS_GUI_X11_XM_PUSHBUTTON_HPP

#include "xos/gui/x11/xm/Label.hpp"
#include <Xm/PushB.h>

#define XOS_GUI_X11_XM_PUSHBUTTON_WIDGET_CLASS xmPushButtonWidgetClass
#define XOS_GUI_X11_XM_PUSHBUTTON_WIDGET_NAME "xos::x11::xm::PushButton"

namespace xos {
namespace x11 {
namespace xm {

typedef LabelImplement PushButtonImplement;
typedef Label PushButtonExtend;
///////////////////////////////////////////////////////////////////////
///  Class: PushButton
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS PushButton
: virtual public PushButtonImplement, public PushButtonExtend {
public:
    typedef PushButtonImplement Implements;
    typedef PushButtonExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: PushButton
    ///////////////////////////////////////////////////////////////////////
    PushButton
    (XDisplay* xDisplay = 0, XtWidget xtWidget = 0, 
     XtWidgetClass xtWidgetClass = XOS_GUI_X11_XM_PUSHBUTTON_WIDGET_CLASS, 
     const XtChar* widgetName = XOS_GUI_X11_XM_PUSHBUTTON_WIDGET_NAME, 
     bool isCreated = false)
    : Extends(xDisplay, xtWidget, xtWidgetClass, widgetName, isCreated) {
    }
    virtual ~PushButton() {
    }
};

} // namespace xm 
} // namespace x11 
} // namespace xos 

#endif // _XOS_GUI_X11_XM_PUSHBUTTON_HPP 
