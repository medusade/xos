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
///   File: EventTarget_cases.hpp
///
/// Author: $author$
///   Date: 3/18/2013
///////////////////////////////////////////////////////////////////////
#if defined(XOS_GUI_X11_XCB_EVENTTARGET_MEMBER_CASES_SWITCH)
        switch(xcbEvent.response_type) {
#endif // defined(XOS_GUI_X11_XCB_EVENTTARGET_MEMBER_CASES_SWITCH) 

           case XCB_KEY_PRESS:
                isDone = On_XCB_KEY_PRESS_Event(xcbEvent);
                break;

           case XCB_KEY_RELEASE:
                isDone = On_XCB_KEY_RELEASE_Event(xcbEvent);
                break;

           case XCB_BUTTON_PRESS:
                isDone = On_XCB_BUTTON_PRESS_Event(xcbEvent);
                break;

           case XCB_BUTTON_RELEASE:
                isDone = On_XCB_BUTTON_RELEASE_Event(xcbEvent);
                break;

           case XCB_MOTION_NOTIFY:
                isDone = On_XCB_MOTION_NOTIFY_Event(xcbEvent);
                break;

           case XCB_ENTER_NOTIFY:
                isDone = On_XCB_ENTER_NOTIFY_Event(xcbEvent);
                break;

           case XCB_LEAVE_NOTIFY:
                isDone = On_XCB_LEAVE_NOTIFY_Event(xcbEvent);
                break;

           case XCB_FOCUS_IN:
                isDone = On_XCB_FOCUS_IN_Event(xcbEvent);
                break;

           case XCB_FOCUS_OUT:
                isDone = On_XCB_FOCUS_OUT_Event(xcbEvent);
                break;

           case XCB_KEYMAP_NOTIFY:
                isDone = On_XCB_KEYMAP_NOTIFY_Event(xcbEvent);
                break;

           case XCB_EXPOSE:
                isDone = On_XCB_EXPOSE_Event(xcbEvent);
                break;

           case XCB_GRAPHICS_EXPOSURE:
                isDone = On_XCB_GRAPHICS_EXPOSURE_Event(xcbEvent);
                break;

           case XCB_NO_EXPOSURE:
                isDone = On_XCB_NO_EXPOSURE_Event(xcbEvent);
                break;

           case XCB_VISIBILITY_NOTIFY:
                isDone = On_XCB_VISIBILITY_NOTIFY_Event(xcbEvent);
                break;

           case XCB_CREATE_NOTIFY:
                isDone = On_XCB_CREATE_NOTIFY_Event(xcbEvent);
                break;

           case XCB_DESTROY_NOTIFY:
                isDone = On_XCB_DESTROY_NOTIFY_Event(xcbEvent);
                break;

           case XCB_UNMAP_NOTIFY:
                isDone = On_XCB_UNMAP_NOTIFY_Event(xcbEvent);
                break;

           case XCB_MAP_NOTIFY:
                isDone = On_XCB_MAP_NOTIFY_Event(xcbEvent);
                break;

           case XCB_MAP_REQUEST:
                isDone = On_XCB_MAP_REQUEST_Event(xcbEvent);
                break;

           case XCB_REPARENT_NOTIFY:
                isDone = On_XCB_REPARENT_NOTIFY_Event(xcbEvent);
                break;

           case XCB_CONFIGURE_NOTIFY:
                isDone = On_XCB_CONFIGURE_NOTIFY_Event(xcbEvent);
                break;

           case XCB_CONFIGURE_REQUEST:
                isDone = On_XCB_CONFIGURE_REQUEST_Event(xcbEvent);
                break;

           case XCB_GRAVITY_NOTIFY:
                isDone = On_XCB_GRAVITY_NOTIFY_Event(xcbEvent);
                break;

           case XCB_RESIZE_REQUEST:
                isDone = On_XCB_RESIZE_REQUEST_Event(xcbEvent);
                break;

           case XCB_CIRCULATE_NOTIFY:
                isDone = On_XCB_CIRCULATE_NOTIFY_Event(xcbEvent);
                break;

           case XCB_CIRCULATE_REQUEST:
                isDone = On_XCB_CIRCULATE_REQUEST_Event(xcbEvent);
                break;

           case XCB_PROPERTY_NOTIFY:
                isDone = On_XCB_PROPERTY_NOTIFY_Event(xcbEvent);
                break;

           case XCB_SELECTION_CLEAR:
                isDone = On_XCB_SELECTION_CLEAR_Event(xcbEvent);
                break;

           case XCB_SELECTION_REQUEST:
                isDone = On_XCB_SELECTION_REQUEST_Event(xcbEvent);
                break;

           case XCB_SELECTION_NOTIFY:
                isDone = On_XCB_SELECTION_NOTIFY_Event(xcbEvent);
                break;

           case XCB_COLORMAP_NOTIFY:
                isDone = On_XCB_COLORMAP_NOTIFY_Event(xcbEvent);
                break;

           case XCB_CLIENT_MESSAGE:
                isDone = On_XCB_CLIENT_MESSAGE_Event(xcbEvent);
                break;

           case XCB_MAPPING_NOTIFY:
                isDone = On_XCB_MAPPING_NOTIFY_Event(xcbEvent);
                break;

#if defined(XOS_GUI_X11_XCB_EVENTTARGET_MEMBER_CASES_SWITCH)
        }
#endif // defined(XOS_GUI_X11_XCB_EVENTTARGET_MEMBER_CASES_SWITCH) 
