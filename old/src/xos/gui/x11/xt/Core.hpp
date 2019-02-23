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
///   File: Core.hpp
///
/// Author: $author$
///   Date: 7/2/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_X11_XT_CORE_HPP
#define _XOS_GUI_X11_XT_CORE_HPP

#include "xos/gui/x11/xt/WindowObject.hpp"

namespace xos {
namespace x11 {
namespace xt {

typedef WindowObjectImplement CoreImplement;
typedef WindowObject CoreExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Core
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Core
: virtual public CoreImplement, public CoreExtend {
public:
    typedef CoreImplement Implements;
    typedef CoreExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: Core
    ///////////////////////////////////////////////////////////////////////
    Core
    (XDisplay* xDisplay = 0, XtWidget xtWidget = 0, 
     XtWidgetClass xtWidgetClass = 0, 
     const XtChar* widgetName = XOS_GUI_X11_XT_WIDGET_NAME, 
     bool isCreated = false)
    : Extends(xDisplay, xtWidget, xtWidgetClass, widgetName, isCreated) {
    }
    virtual ~Core() {
    }
};

} // namespace xt 
} // namespace x11 
} // namespace xos 

#endif // _XOS_GUI_X11_XT_CORE_HPP 
