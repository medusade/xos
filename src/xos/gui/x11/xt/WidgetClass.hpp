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
///   File: WidgetClass.hpp
///
/// Author: $author$
///   Date: 4/3/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_X11_XT_WIDGETCLASS_HPP
#define _XOS_GUI_X11_XT_WIDGETCLASS_HPP

#include "xos/gui/x11/Intrinsic.hpp"
#include "xos/gui/x11/StringDefs.hpp"
#include "xos/base/Created.hpp"
#include "xos/base/Attached.hpp"

namespace xos {
namespace x11 {
namespace xt {

typedef xos::InterfaceBase WidgetClassImplement;
typedef xos::Attached<XtWidgetClass, int, 0> WidgetClassExtend;
///////////////////////////////////////////////////////////////////////
///  Class: WidgetClass
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS WidgetClass
: virtual public WidgetClassImplement, public WidgetClassExtend {
public:
    typedef WidgetClassImplement Implements;
    typedef WidgetClassExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: WidgetClass
    ///////////////////////////////////////////////////////////////////////
    WidgetClass(XtWidgetClass detached = 0): Extends(detached) {
    }
    virtual ~WidgetClass() {
    }
};

} // namespace xt 
} // namespace x11 
} // namespace xos 

#endif // _XOS_GUI_X11_XT_WIDGETCLASS_HPP 
