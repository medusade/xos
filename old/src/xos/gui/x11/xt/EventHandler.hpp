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
///   File: EventHandler.hpp
///
/// Author: $author$
///   Date: 7/1/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_X11_XT_EVENTHANDLER_HPP
#define _XOS_GUI_X11_XT_EVENTHANDLER_HPP

#include "xos/gui/x11/Intrinsic.hpp"

namespace xos {
namespace x11 {
namespace xt {

///////////////////////////////////////////////////////////////////////
///  Class: EventHandlerInterface
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS EventHandlerInterface {
public:
#include "EventHandler_members.hpp"
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool OnHandleXtEvent
    (XtWidget xtWidget, XtPointer xtPointer, XEvent& xEvent, Boolean& continueToDispatch) {
        bool isHandled = false;
        continueToDispatch = True;
        switch (xEvent.type) {
#include "EventHandler_cases.hpp"
        }
        return isHandled;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    static void HandleXtEvent
    (XtWidget xtWidget, XtPointer xtPointer, 
     XEvent* xEvent, Boolean* continueToDispatch) {
        EventHandlerInterface* handler;
        *continueToDispatch = True;
        if ((handler = (EventHandlerInterface*)(xtPointer)))
            handler->OnHandleXtEvent(xtWidget, xtPointer, *xEvent, *continueToDispatch);
    }
};
typedef EventHandlerInterface EventHandlerImplement;

} // namespace xt 
} // namespace x11 
} // namespace xos 

#endif // _XOS_GUI_X11_XT_EVENTHANDLER_HPP 
