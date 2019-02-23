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
///   File: Event.hpp
///
/// Author: $author$
///   Date: 3/24/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_X11_EVENT_HPP
#define _XOS_GUI_X11_EVENT_HPP

#include "xos/gui/x11/Xlib.hpp"
#include "xos/base/Wrapped.hpp"
#include "xos/os/Logger.hpp"

namespace xos {
namespace x11 {

typedef InterfaceBase EventImplement;
typedef Wrapped<XEvent> EventExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Event
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Event: virtual public EventImplement, public EventExtend {
public:
    typedef EventImplement Implements;
    typedef EventExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: Event
    ///////////////////////////////////////////////////////////////////////
    Event
    (XDisplay* xDisplay, XWindow xWindow, XEventType type, 
     bool sent=false, unsigned long serial=0) {
        wrapped().xany.display = xDisplay;
        wrapped().xany.window = xWindow;
        wrapped().xany.send_event = (Bool)((sent)?(True):(False));
        wrapped().xany.serial = serial;
        wrapped().xany.type = type;
    }
    Event(XEvent& xEvent): Extends(xEvent) {
    }
    Event(const Event& copy): Extends(copy) {
    }
    Event() {
    }
    virtual ~Event() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Send(bool propigate=false, XEventMask mask=0) {
        XDisplay* xDisplay = wrapped().xany.display;
        XWindow xWindow = wrapped().xany.window;
        if ((xDisplay) && (xWindow)) {
            Bool bPropigate = (Bool)((propigate)?(True):(False));
            XOS_LOG_DEBUG("XSendEvent()...");
            if ((XSendEvent(xDisplay, xWindow, bPropigate, mask, &wrapped()))) {
                return true;
            } else {
                XOS_LOG_ERROR("failed on XSendEvent()");
            }
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual operator XEvent& () const {
        return wrapped();
    }
    virtual operator XEvent* () const {
        return &wrapped();
    }
};

///////////////////////////////////////////////////////////////////////
///  Class: ExposeEvent
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS ExposeEvent: public Event {
public:
    typedef Event Extends;
    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: Event
    ///////////////////////////////////////////////////////////////////////
    ExposeEvent
    (XDisplay* xDisplay, XWindow xWindow, 
     int x,int y, int width,int height, int count=0,
     XEventType type=Expose, bool sent=false, unsigned long serial=0)
    : Extends(xDisplay, xWindow, type, sent, serial) {
        wrapped().xexpose.x = x;
        wrapped().xexpose.y = y;
        wrapped().xexpose.width = width;
        wrapped().xexpose.height = height;
        wrapped().xexpose.count = count;
    }
};

} // namespace x11 
} // namespace xos 

#endif // _XOS_GUI_X11_EVENT_HPP 
