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
///   File: Command.hpp
///
/// Author: $author$
///   Date: 7/3/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_X11_XAW_COMMAND_HPP
#define _XOS_GUI_X11_XAW_COMMAND_HPP

#include "xos/gui/x11/xaw/Label.hpp"
#include <X11/Xaw/Command.h>

#define XOS_GUI_X11_XAW_COMMAND_CLASS commandWidgetClass
#define XOS_GUI_X11_XAW_COMMAND_NAME "xos::x11::xaw::Command"

namespace xos {
namespace x11 {
namespace xaw {

typedef LabelImplement CommandImplement;
typedef Label CommandExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Command
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Command
: virtual public CommandImplement, public CommandExtend {
public:
    typedef CommandImplement Implements;
    typedef CommandExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: Command
    ///////////////////////////////////////////////////////////////////////
    Command
    (XDisplay* xDisplay = 0, XtWidget xtWidget = 0, 
     XtWidgetClass xtWidgetClass = XOS_GUI_X11_XAW_COMMAND_CLASS, 
     const XtChar* widgetName = XOS_GUI_X11_XAW_COMMAND_NAME, 
     bool isCreated = false)
    : Extends(xDisplay, xtWidget, xtWidgetClass, widgetName, isCreated) {
    }
    virtual ~Command()
    {
    }
};

} // namespace xaw 
} // namespace x11 
} // namespace xos 

#endif // _XOS_GUI_X11_XAW_COMMAND_HPP 
