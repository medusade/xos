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
///   File: Composite.hpp
///
/// Author: $author$
///   Date: 7/2/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_X11_XT_COMPOSITE_HPP
#define _XOS_GUI_X11_XT_COMPOSITE_HPP

#include "xos/gui/x11/xt/Core.hpp"

#define XOS_GUI_X11_XT_COMPOSITE_WIDGET_CLASS compositeWidgetClass
#define XOS_GUI_X11_XT_COMPOSITE_WIDGET_NAME "xos::x11::xt::Composite"

namespace xos {
namespace x11 {
namespace xt {

typedef CoreImplement CompositeImplement;
typedef Core CompositeExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Composite
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Composite
: virtual public CompositeImplement,
  public CompositeExtend
{
public:
    typedef CompositeImplement Implements;
    typedef CompositeExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: Composite
    ///////////////////////////////////////////////////////////////////////
    Composite
    (XDisplay* xDisplay = 0, XtWidget xtWidget = 0, 
     XtWidgetClass xtWidgetClass = XOS_GUI_X11_XT_COMPOSITE_WIDGET_CLASS, 
     const XtChar* widgetName = XOS_GUI_X11_XT_COMPOSITE_WIDGET_NAME, 
     bool isCreated = false)
    : Extends(xDisplay, xtWidget, xtWidgetClass, widgetName, isCreated) {
    }
    virtual ~Composite() {
    }
};


} // namespace xt 
} // namespace x11 
} // namespace xos 


#endif // _XOS_GUI_X11_XT_COMPOSITE_HPP 
        

