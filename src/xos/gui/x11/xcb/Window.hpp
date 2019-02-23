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
///   File: Window.hpp
///
/// Author: $author$
///   Date: 3/17/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_X11_XCB_WINDOW_HPP
#define _XOS_GUI_X11_XCB_WINDOW_HPP

#include "xos/gui/x11/xcb/EventTarget.hpp"
#include "xos/gui/x11/xcb/Created.hpp"
#include "xos/os/Logger.hpp"

#define XOS_GUI_X11_XCB_WINDOW_DEFAULT_WINDOW_CLASS \
    XCB_WINDOW_CLASS_INPUT_OUTPUT

#define XOS_GUI_X11_XCB_WINDOW_DEFAULT_EVENT_MASK \
    XCB_EVENT_MASK_KEY_PRESS | \
    XCB_EVENT_MASK_KEY_RELEASE | \
    XCB_EVENT_MASK_BUTTON_PRESS | \
    XCB_EVENT_MASK_BUTTON_RELEASE | \
    XCB_EVENT_MASK_ENTER_WINDOW | \
    XCB_EVENT_MASK_LEAVE_WINDOW | \
    XCB_EVENT_MASK_POINTER_MOTION | \
    XCB_EVENT_MASK_POINTER_MOTION_HINT | \
    XCB_EVENT_MASK_BUTTON_1_MOTION | \
    XCB_EVENT_MASK_BUTTON_2_MOTION | \
    XCB_EVENT_MASK_BUTTON_3_MOTION | \
    XCB_EVENT_MASK_BUTTON_4_MOTION | \
    XCB_EVENT_MASK_BUTTON_5_MOTION | \
    XCB_EVENT_MASK_BUTTON_MOTION | \
    XCB_EVENT_MASK_KEYMAP_STATE | \
    XCB_EVENT_MASK_EXPOSURE | \
    XCB_EVENT_MASK_VISIBILITY_CHANGE | \
    XCB_EVENT_MASK_STRUCTURE_NOTIFY | \
    XCB_EVENT_MASK_RESIZE_REDIRECT | \
    XCB_EVENT_MASK_SUBSTRUCTURE_NOTIFY | \
    XCB_EVENT_MASK_SUBSTRUCTURE_REDIRECT | \
    XCB_EVENT_MASK_FOCUS_CHANGE | \
    XCB_EVENT_MASK_PROPERTY_CHANGE | \
    XCB_EVENT_MASK_COLOR_MAP_CHANGE | \
    XCB_EVENT_MASK_OWNER_GRAB_BUTTON

namespace xos {
namespace x11 {
namespace xcb {

typedef InterfaceBase WindowImplement;
typedef Attached<xcb_window_t, int, 0> WindowAttached;
typedef xos::Created<xcb_window_t, int, 0, WindowAttached> WindowCreated;
typedef Created<xcb_window_t, int, 0, WindowCreated> WindowExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Window
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Window
: virtual public EventTarget, virtual public WindowImplement, public WindowExtend {
public:
    typedef WindowImplement Implements;
    typedef WindowExtend Extends;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: Window
    ///////////////////////////////////////////////////////////////////////
    Window(xcb_connection_t* connection=0, AttachedT detached=0, bool isCreated=false)
    : Extends(connection, detached, isCreated) {
    }
    virtual ~Window() {
        if (!(Destroyed()))
        {   XOS_LOG_ERROR("failed on Destroyed()"); }
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool On_XCB_EXPOSE_Event(const xcb_generic_event_t& xcbEvent) {
        const xcb_expose_event_t& x = (const xcb_expose_event_t&)(xcbEvent);
        const xcb_rectangle_t r = {x.x,x.y, x.width,x.height};
        bool isDone = false;
        XOS_LOG_DEBUG("XCB_EXPOSE(" << x.x << "," << x.y << ", " << x.width << "," << x.height << ")");
        return isDone;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Create
    (xcb_connection_t* connection, 
     uint8_t depth, xcb_window_t parentId, 
     int16_t x,int16_t y, uint16_t width,uint16_t height, 
     uint16_t borderWidth, uint32_t backPixel, xcb_visualid_t visualId) {
        xcb_window_t windowId = 0;
        uint16_t windowClass = XOS_GUI_X11_XCB_WINDOW_DEFAULT_WINDOW_CLASS;
        uint32_t valueMask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
        const uint32_t valueList[] = { backPixel, XOS_GUI_X11_XCB_WINDOW_DEFAULT_EVENT_MASK };
        if ((connection)) {
            if ((windowId = xcb_generate_id(connection))) {
                if ((Create
                    (connection, depth, windowId, parentId, 
                     x,y, width,height, borderWidth, windowClass, 
                     visualId, valueMask, valueList))) {
                    return true;
                }
            } else {
                XOS_LOG_ERROR("faied on xcb_generate_id()");
            }
        }
        return false;
    }
    virtual bool Create
    (xcb_connection_t* connection, 
     uint8_t depth, xcb_window_t windowId, xcb_window_t parentId, 
     int16_t x,int16_t y, uint16_t width,uint16_t height, uint16_t borderWidth,
     uint16_t windowClass, xcb_visualid_t visualId, uint32_t valueMask, const uint32_t* valueList) {
        xcb_generic_error_t* error;
        if (!(error = xcb_request_check(connection, xcb_create_window_checked
            (connection, depth, windowId, parentId, x,y, width,height, borderWidth, 
             windowClass, visualId, valueMask, valueList)))) {
             AttachCreated(connection, windowId);
             return true;
        } else {
            XOS_LOG_ERROR("failed " << error->error_code << " on xcb_create_window_checked()");
            free(error);
        }
        return false;
    }
    virtual bool Destroy() {
        bool isCreated = false;
        xcb_connection_t* connection = 0;
        AttachedT detached = Detach(connection, isCreated);
        if ((connection) && (detached)) {
            xcb_generic_error_t* error;
            if (!(error = xcb_request_check
                (connection, xcb_destroy_window_checked(connection, detached)))) {
                return true;
            } else {
                XOS_LOG_ERROR("failed " << error->error_code << " on xcb_destroy_window_checked()");
                free(error);
            }
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Map() {
        xcb_connection_t* connection = 0;
        AttachedT detached = 0;
        if ((connection = m_connection) && (detached = m_attachedTo)) {
            xcb_generic_error_t* error;
            if (!(error = xcb_request_check
                (connection, xcb_map_window_checked(connection, detached)))) {
                return true;
            } else {
                XOS_LOG_ERROR("failed " << error->error_code << " on xcb_map_window_checked()");
                free(error);
            }
        }
        return false;
    }
    virtual bool Unmap() {
        xcb_connection_t* connection = 0;
        AttachedT detached = 0;
        if ((connection = m_connection) && (detached = m_attachedTo)) {
            xcb_generic_error_t* error;
            if (!(error = xcb_request_check
                (connection, xcb_unmap_window_checked(connection, detached)))) {
                return true;
            } else {
                XOS_LOG_ERROR("failed " << error->error_code << " on xcb_unmap_window_checked()");
                free(error);
            }
        }
        return false;
    }
};

} // namespace xcb 
} // namespace x11 
} // namespace xos 

#endif // _XOS_GUI_X11_XCB_WINDOW_HPP 
