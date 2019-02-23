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
///   File: EventHandler_cases.hpp
///
/// Author: $author$
///   Date: 7/1/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_X11_XT_EVENTHANDLER_CASES_HPP
#define _XOS_GUI_X11_XT_EVENTHANDLER_CASES_HPP

#if defined(XOS_GUI_X11_XT_EVENTHANDLER_MEMBER_CASES_SWITCH)
        switch(xEvent.type) {
#endif // defined(XOS_GUI_X11_XT_EVENTHANDLER_MEMBER_CASES_SWITCH) 

           case KeyPress:
                isHandled = OnHandle_KeyPress_XtEvent
                (xtWidget, xtPointer, xEvent, continueToDispatch);
                break;

           case KeyRelease:
                isHandled = OnHandle_KeyRelease_XtEvent
                (xtWidget, xtPointer, xEvent, continueToDispatch);
                break;

           case ButtonPress:
                isHandled = OnHandle_ButtonPress_XtEvent
                (xtWidget, xtPointer, xEvent, continueToDispatch);
                break;

           case ButtonRelease:
                isHandled = OnHandle_ButtonRelease_XtEvent
                (xtWidget, xtPointer, xEvent, continueToDispatch);
                break;

           case MotionNotify:
                isHandled = OnHandle_MotionNotify_XtEvent
                (xtWidget, xtPointer, xEvent, continueToDispatch);
                break;

           case EnterNotify:
                isHandled = OnHandle_EnterNotify_XtEvent
                (xtWidget, xtPointer, xEvent, continueToDispatch);
                break;

           case LeaveNotify:
                isHandled = OnHandle_LeaveNotify_XtEvent
                (xtWidget, xtPointer, xEvent, continueToDispatch);
                break;

           case FocusIn:
                isHandled = OnHandle_FocusIn_XtEvent
                (xtWidget, xtPointer, xEvent, continueToDispatch);
                break;

           case FocusOut:
                isHandled = OnHandle_FocusOut_XtEvent
                (xtWidget, xtPointer, xEvent, continueToDispatch);
                break;

           case KeymapNotify:
                isHandled = OnHandle_KeymapNotify_XtEvent
                (xtWidget, xtPointer, xEvent, continueToDispatch);
                break;

           case Expose:
                isHandled = OnHandle_Expose_XtEvent
                (xtWidget, xtPointer, xEvent, continueToDispatch);
                break;

           case GraphicsExpose:
                isHandled = OnHandle_GraphicsExpose_XtEvent
                (xtWidget, xtPointer, xEvent, continueToDispatch);
                break;

           case NoExpose:
                isHandled = OnHandle_NoExpose_XtEvent
                (xtWidget, xtPointer, xEvent, continueToDispatch);
                break;

           case VisibilityNotify:
                isHandled = OnHandle_VisibilityNotify_XtEvent
                (xtWidget, xtPointer, xEvent, continueToDispatch);
                break;

           case CreateNotify:
                isHandled = OnHandle_CreateNotify_XtEvent
                (xtWidget, xtPointer, xEvent, continueToDispatch);
                break;

           case DestroyNotify:
                isHandled = OnHandle_DestroyNotify_XtEvent
                (xtWidget, xtPointer, xEvent, continueToDispatch);
                break;

           case UnmapNotify:
                isHandled = OnHandle_UnmapNotify_XtEvent
                (xtWidget, xtPointer, xEvent, continueToDispatch);
                break;

           case MapNotify:
                isHandled = OnHandle_MapNotify_XtEvent
                (xtWidget, xtPointer, xEvent, continueToDispatch);
                break;

           case MapRequest:
                isHandled = OnHandle_MapRequest_XtEvent
                (xtWidget, xtPointer, xEvent, continueToDispatch);
                break;

           case ReparentNotify:
                isHandled = OnHandle_ReparentNotify_XtEvent
                (xtWidget, xtPointer, xEvent, continueToDispatch);
                break;

           case ConfigureNotify:
                isHandled = OnHandle_ConfigureNotify_XtEvent
                (xtWidget, xtPointer, xEvent, continueToDispatch);
                break;

           case ConfigureRequest:
                isHandled = OnHandle_ConfigureRequest_XtEvent
                (xtWidget, xtPointer, xEvent, continueToDispatch);
                break;

           case GravityNotify:
                isHandled = OnHandle_GravityNotify_XtEvent
                (xtWidget, xtPointer, xEvent, continueToDispatch);
                break;

           case ResizeRequest:
                isHandled = OnHandle_ResizeRequest_XtEvent
                (xtWidget, xtPointer, xEvent, continueToDispatch);
                break;

           case CirculateNotify:
                isHandled = OnHandle_CirculateNotify_XtEvent
                (xtWidget, xtPointer, xEvent, continueToDispatch);
                break;

           case CirculateRequest:
                isHandled = OnHandle_CirculateRequest_XtEvent
                (xtWidget, xtPointer, xEvent, continueToDispatch);
                break;

           case PropertyNotify:
                isHandled = OnHandle_PropertyNotify_XtEvent
                (xtWidget, xtPointer, xEvent, continueToDispatch);
                break;

           case SelectionClear:
                isHandled = OnHandle_SelectionClear_XtEvent
                (xtWidget, xtPointer, xEvent, continueToDispatch);
                break;

           case SelectionRequest:
                isHandled = OnHandle_SelectionRequest_XtEvent
                (xtWidget, xtPointer, xEvent, continueToDispatch);
                break;

           case SelectionNotify:
                isHandled = OnHandle_SelectionNotify_XtEvent
                (xtWidget, xtPointer, xEvent, continueToDispatch);
                break;

           case ColormapNotify:
                isHandled = OnHandle_ColormapNotify_XtEvent
                (xtWidget, xtPointer, xEvent, continueToDispatch);
                break;

           case ClientMessage:
                isHandled = OnHandle_ClientMessage_XtEvent
                (xtWidget, xtPointer, xEvent, continueToDispatch);
                break;

           case MappingNotify:
                isHandled = OnHandle_MappingNotify_XtEvent
                (xtWidget, xtPointer, xEvent, continueToDispatch);
                break;

           default:
                isHandled = OnHandleXtEventDefault
                (xtWidget, xtPointer, xEvent, continueToDispatch);
                break;

#if defined(XOS_GUI_X11_XT_EVENTHANDLER_MEMBER_CASES_SWITCH)
        }
#endif // defined(XOS_GUI_X11_XT_EVENTHANDLER_MEMBER_CASES_SWITCH) 

#endif // _XOS_GUI_X11_XT_EVENTHANDLER_CASES_HPP 
