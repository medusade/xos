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
///   File: Main.hpp
///
/// Author: $author$
///   Date: 3/17/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_X11_XCB_HELLO_MAIN_HPP
#define _XOS_GUI_X11_XCB_HELLO_MAIN_HPP

#include "xos/gui/x11/xcb/WindowMain.hpp"

namespace xos {
namespace x11 {
namespace xcb {
namespace hello {

typedef xcb::WindowMainImplement MainImplement;
typedef xcb::WindowMain MainExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Main
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Main
: virtual public MainImplement, public MainExtend {
public:
    typedef MainImplement Implements;
    typedef MainExtend Extends;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: Main
    ///////////////////////////////////////////////////////////////////////
    Main() {
    }
    virtual ~Main() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool On_XCB_EXPOSE_Event(const xcb_generic_event_t& xcbEvent) {
        bool isDone = false;
        return isDone;
    }
    virtual bool On_XCB_BUTTON_PRESS_Event(const xcb_generic_event_t& xcbEvent) {
        const xcb_button_press_event_t& xcbButtonEvent = (const xcb_button_press_event_t&)(xcbEvent);
        bool isDone = false;
        XOS_LOG_INFO("XCB_BUTTON_PRESS " << xcbButtonEvent.detail);
        return isDone;
    }
    virtual bool On_XCB_BUTTON_RELEASE_Event(const xcb_generic_event_t& xcbEvent) {
        const xcb_button_press_event_t& xcbButtonEvent = (const xcb_button_press_event_t&)(xcbEvent);
        bool isDone = false;
        XOS_LOG_INFO("XCB_BUTTON_RELEASE " << xcbButtonEvent.detail);
        return isDone;
    }
};

} // namespace hello 
} // namespace xcb 
} // namespace x11 
} // namespace xos 

#endif // _XOS_GUI_X11_XCB_HELLO_MAIN_HPP 
