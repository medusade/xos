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
///   File: Form.hpp
///
/// Author: $author$
///   Date: 7/2/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_X11_XAW_FORM_HPP
#define _XOS_GUI_X11_XAW_FORM_HPP

#include "xos/gui/x11/xt/Constraint.hpp"
#include <X11/Xaw/Form.h>

#define XOS_GUI_X11_XAW_FORM_CLASS formWidgetClass
#define XOS_GUI_X11_XAW_FORM_NAME "xos::x11::xaw::Form"

namespace xos {
namespace x11 {
namespace xaw {

typedef xt::ConstraintImplement FormImplement;
typedef xt::Constraint FormExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Form
///
/// Author: $author$
///   Date: 7/2/2013
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Form
: virtual public FormImplement, public FormExtend {
public:
    typedef FormImplement Implements;
    typedef FormExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: Form
    ///
    ///       Author: $author$
    ///         Date: 7/2/2013
    ///////////////////////////////////////////////////////////////////////
    Form
    (XDisplay* xDisplay = 0, XtWidget xtWidget = 0, 
     XtWidgetClass xtWidgetClass = XOS_GUI_X11_XAW_FORM_CLASS, 
     const XtChar* widgetName = XOS_GUI_X11_XAW_FORM_NAME, 
     bool isCreated = false)
    : Extends(xDisplay, xtWidget, xtWidgetClass, widgetName, isCreated) {
    }
    virtual ~Form() {
    }
};

} // namespace xaw 
} // namespace x11 
} // namespace xos 

#endif // _XOS_GUI_X11_XAW_FORM_HPP 
