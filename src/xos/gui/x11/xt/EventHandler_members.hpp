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
///   File: EventHandler_members.hpp
///
/// Author: $author$
///   Date: 7/1/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_X11_XT_EVENTHANDLER_MEMBERS_HPP
#define _XOS_GUI_X11_XT_EVENTHANDLER_MEMBERS_HPP

    virtual bool OnHandle_KeyPress_XtEvent
    (XtWidget xtWidget, XtPointer xtPointer, XEvent& xEvent, Boolean& continueToDispatch) {
        bool isHandled = false;
        isHandled = OnHandleXtEventDefault(xtWidget, xtPointer, xEvent, continueToDispatch);
        return isHandled;
    }
    virtual bool OnHandle_KeyRelease_XtEvent
    (XtWidget xtWidget, XtPointer xtPointer, XEvent& xEvent, Boolean& continueToDispatch) {
        bool isHandled = false;
        isHandled = OnHandleXtEventDefault(xtWidget, xtPointer, xEvent, continueToDispatch);
        return isHandled;
    }
    virtual bool OnHandle_ButtonPress_XtEvent
    (XtWidget xtWidget, XtPointer xtPointer, XEvent& xEvent, Boolean& continueToDispatch) {
        bool isHandled = false;
        isHandled = OnHandleXtEventDefault(xtWidget, xtPointer, xEvent, continueToDispatch);
        return isHandled;
    }
    virtual bool OnHandle_ButtonRelease_XtEvent
    (XtWidget xtWidget, XtPointer xtPointer, XEvent& xEvent, Boolean& continueToDispatch) {
        bool isHandled = false;
        isHandled = OnHandleXtEventDefault(xtWidget, xtPointer, xEvent, continueToDispatch);
        return isHandled;
    }
    virtual bool OnHandle_MotionNotify_XtEvent
    (XtWidget xtWidget, XtPointer xtPointer, XEvent& xEvent, Boolean& continueToDispatch) {
        bool isHandled = false;
        isHandled = OnHandleXtEventDefault(xtWidget, xtPointer, xEvent, continueToDispatch);
        return isHandled;
    }
    virtual bool OnHandle_EnterNotify_XtEvent
    (XtWidget xtWidget, XtPointer xtPointer, XEvent& xEvent, Boolean& continueToDispatch) {
        bool isHandled = false;
        isHandled = OnHandleXtEventDefault(xtWidget, xtPointer, xEvent, continueToDispatch);
        return isHandled;
    }
    virtual bool OnHandle_LeaveNotify_XtEvent
    (XtWidget xtWidget, XtPointer xtPointer, XEvent& xEvent, Boolean& continueToDispatch) {
        bool isHandled = false;
        isHandled = OnHandleXtEventDefault(xtWidget, xtPointer, xEvent, continueToDispatch);
        return isHandled;
    }
    virtual bool OnHandle_FocusIn_XtEvent
    (XtWidget xtWidget, XtPointer xtPointer, XEvent& xEvent, Boolean& continueToDispatch) {
        bool isHandled = false;
        isHandled = OnHandleXtEventDefault(xtWidget, xtPointer, xEvent, continueToDispatch);
        return isHandled;
    }
    virtual bool OnHandle_FocusOut_XtEvent
    (XtWidget xtWidget, XtPointer xtPointer, XEvent& xEvent, Boolean& continueToDispatch) {
        bool isHandled = false;
        isHandled = OnHandleXtEventDefault(xtWidget, xtPointer, xEvent, continueToDispatch);
        return isHandled;
    }
    virtual bool OnHandle_KeymapNotify_XtEvent
    (XtWidget xtWidget, XtPointer xtPointer, XEvent& xEvent, Boolean& continueToDispatch) {
        bool isHandled = false;
        isHandled = OnHandleXtEventDefault(xtWidget, xtPointer, xEvent, continueToDispatch);
        return isHandled;
    }
    virtual bool OnHandle_Expose_XtEvent
    (XtWidget xtWidget, XtPointer xtPointer, XEvent& xEvent, Boolean& continueToDispatch) {
        bool isHandled = false;
        isHandled = OnHandleXtEventDefault(xtWidget, xtPointer, xEvent, continueToDispatch);
        return isHandled;
    }
    virtual bool OnHandle_GraphicsExpose_XtEvent
    (XtWidget xtWidget, XtPointer xtPointer, XEvent& xEvent, Boolean& continueToDispatch) {
        bool isHandled = false;
        isHandled = OnHandleXtEventDefault(xtWidget, xtPointer, xEvent, continueToDispatch);
        return isHandled;
    }
    virtual bool OnHandle_NoExpose_XtEvent
    (XtWidget xtWidget, XtPointer xtPointer, XEvent& xEvent, Boolean& continueToDispatch) {
        bool isHandled = false;
        isHandled = OnHandleXtEventDefault(xtWidget, xtPointer, xEvent, continueToDispatch);
        return isHandled;
    }
    virtual bool OnHandle_VisibilityNotify_XtEvent
    (XtWidget xtWidget, XtPointer xtPointer, XEvent& xEvent, Boolean& continueToDispatch) {
        bool isHandled = false;
        isHandled = OnHandleXtEventDefault(xtWidget, xtPointer, xEvent, continueToDispatch);
        return isHandled;
    }
    virtual bool OnHandle_CreateNotify_XtEvent
    (XtWidget xtWidget, XtPointer xtPointer, XEvent& xEvent, Boolean& continueToDispatch) {
        bool isHandled = false;
        isHandled = OnHandleXtEventDefault(xtWidget, xtPointer, xEvent, continueToDispatch);
        return isHandled;
    }
    virtual bool OnHandle_DestroyNotify_XtEvent
    (XtWidget xtWidget, XtPointer xtPointer, XEvent& xEvent, Boolean& continueToDispatch) {
        bool isHandled = false;
        isHandled = OnHandleXtEventDefault(xtWidget, xtPointer, xEvent, continueToDispatch);
        return isHandled;
    }
    virtual bool OnHandle_UnmapNotify_XtEvent
    (XtWidget xtWidget, XtPointer xtPointer, XEvent& xEvent, Boolean& continueToDispatch) {
        bool isHandled = false;
        isHandled = OnHandleXtEventDefault(xtWidget, xtPointer, xEvent, continueToDispatch);
        return isHandled;
    }
    virtual bool OnHandle_MapNotify_XtEvent
    (XtWidget xtWidget, XtPointer xtPointer, XEvent& xEvent, Boolean& continueToDispatch) {
        bool isHandled = false;
        isHandled = OnHandleXtEventDefault(xtWidget, xtPointer, xEvent, continueToDispatch);
        return isHandled;
    }
    virtual bool OnHandle_MapRequest_XtEvent
    (XtWidget xtWidget, XtPointer xtPointer, XEvent& xEvent, Boolean& continueToDispatch) {
        bool isHandled = false;
        isHandled = OnHandleXtEventDefault(xtWidget, xtPointer, xEvent, continueToDispatch);
        return isHandled;
    }
    virtual bool OnHandle_ReparentNotify_XtEvent
    (XtWidget xtWidget, XtPointer xtPointer, XEvent& xEvent, Boolean& continueToDispatch) {
        bool isHandled = false;
        isHandled = OnHandleXtEventDefault(xtWidget, xtPointer, xEvent, continueToDispatch);
        return isHandled;
    }
    virtual bool OnHandle_ConfigureNotify_XtEvent
    (XtWidget xtWidget, XtPointer xtPointer, XEvent& xEvent, Boolean& continueToDispatch) {
        bool isHandled = false;
        isHandled = OnHandleXtEventDefault(xtWidget, xtPointer, xEvent, continueToDispatch);
        return isHandled;
    }
    virtual bool OnHandle_ConfigureRequest_XtEvent
    (XtWidget xtWidget, XtPointer xtPointer, XEvent& xEvent, Boolean& continueToDispatch) {
        bool isHandled = false;
        isHandled = OnHandleXtEventDefault(xtWidget, xtPointer, xEvent, continueToDispatch);
        return isHandled;
    }
    virtual bool OnHandle_GravityNotify_XtEvent
    (XtWidget xtWidget, XtPointer xtPointer, XEvent& xEvent, Boolean& continueToDispatch) {
        bool isHandled = false;
        isHandled = OnHandleXtEventDefault(xtWidget, xtPointer, xEvent, continueToDispatch);
        return isHandled;
    }
    virtual bool OnHandle_ResizeRequest_XtEvent
    (XtWidget xtWidget, XtPointer xtPointer, XEvent& xEvent, Boolean& continueToDispatch) {
        bool isHandled = false;
        isHandled = OnHandleXtEventDefault(xtWidget, xtPointer, xEvent, continueToDispatch);
        return isHandled;
    }
    virtual bool OnHandle_CirculateNotify_XtEvent
    (XtWidget xtWidget, XtPointer xtPointer, XEvent& xEvent, Boolean& continueToDispatch) {
        bool isHandled = false;
        isHandled = OnHandleXtEventDefault(xtWidget, xtPointer, xEvent, continueToDispatch);
        return isHandled;
    }
    virtual bool OnHandle_CirculateRequest_XtEvent
    (XtWidget xtWidget, XtPointer xtPointer, XEvent& xEvent, Boolean& continueToDispatch) {
        bool isHandled = false;
        isHandled = OnHandleXtEventDefault(xtWidget, xtPointer, xEvent, continueToDispatch);
        return isHandled;
    }
    virtual bool OnHandle_PropertyNotify_XtEvent
    (XtWidget xtWidget, XtPointer xtPointer, XEvent& xEvent, Boolean& continueToDispatch) {
        bool isHandled = false;
        isHandled = OnHandleXtEventDefault(xtWidget, xtPointer, xEvent, continueToDispatch);
        return isHandled;
    }
    virtual bool OnHandle_SelectionClear_XtEvent
    (XtWidget xtWidget, XtPointer xtPointer, XEvent& xEvent, Boolean& continueToDispatch) {
        bool isHandled = false;
        isHandled = OnHandleXtEventDefault(xtWidget, xtPointer, xEvent, continueToDispatch);
        return isHandled;
    }
    virtual bool OnHandle_SelectionRequest_XtEvent
    (XtWidget xtWidget, XtPointer xtPointer, XEvent& xEvent, Boolean& continueToDispatch) {
        bool isHandled = false;
        isHandled = OnHandleXtEventDefault(xtWidget, xtPointer, xEvent, continueToDispatch);
        return isHandled;
    }
    virtual bool OnHandle_SelectionNotify_XtEvent
    (XtWidget xtWidget, XtPointer xtPointer, XEvent& xEvent, Boolean& continueToDispatch) {
        bool isHandled = false;
        isHandled = OnHandleXtEventDefault(xtWidget, xtPointer, xEvent, continueToDispatch);
        return isHandled;
    }
    virtual bool OnHandle_ColormapNotify_XtEvent
    (XtWidget xtWidget, XtPointer xtPointer, XEvent& xEvent, Boolean& continueToDispatch) {
        bool isHandled = false;
        isHandled = OnHandleXtEventDefault(xtWidget, xtPointer, xEvent, continueToDispatch);
        return isHandled;
    }
    virtual bool OnHandle_ClientMessage_XtEvent
    (XtWidget xtWidget, XtPointer xtPointer, XEvent& xEvent, Boolean& continueToDispatch) {
        bool isHandled = false;
        isHandled = OnHandleXtEventDefault(xtWidget, xtPointer, xEvent, continueToDispatch);
        return isHandled;
    }
    virtual bool OnHandle_MappingNotify_XtEvent
    (XtWidget xtWidget, XtPointer xtPointer, XEvent& xEvent, Boolean& continueToDispatch) {
        bool isHandled = false;
        isHandled = OnHandleXtEventDefault(xtWidget, xtPointer, xEvent, continueToDispatch);
        return isHandled;
    }
    virtual bool OnHandleXtEventDefault
    (XtWidget xtWidget, XtPointer xtPointer, XEvent& xEvent, Boolean& continueToDispatch) {
        bool isHandled = false;
        //isHandled = DefaultXtEventHandler(xtWidget, xtPointer, xEvent, continueToDispatch);
        return isHandled;
    }
        
#endif // _XOS_GUI_X11_XT_EVENTHANDLER_MEMBERS_HPP 
