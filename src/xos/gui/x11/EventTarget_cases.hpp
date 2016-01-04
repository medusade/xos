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
///   Date: 3/23/2013
///////////////////////////////////////////////////////////////////////

#if defined(XOS_GUI_X11_MEMBER_CASES_SWITCH)
        switch(xEvent.type) {
#endif // defined(XOS_GUI_X11_MEMBER_CASES_SWITCH) 

           case KeyPress:
                isHandled = OnKeyPressXEvent(xEvent);
                break;

           case KeyRelease:
                isHandled = OnKeyReleaseXEvent(xEvent);
                break;

           case ButtonPress:
                isHandled = OnButtonPressXEvent(xEvent);
                break;

           case ButtonRelease:
                isHandled = OnButtonReleaseXEvent(xEvent);
                break;

           case MotionNotify:
                isHandled = OnMotionNotifyXEvent(xEvent);
                break;

           case EnterNotify:
                isHandled = OnEnterNotifyXEvent(xEvent);
                break;

           case LeaveNotify:
                isHandled = OnLeaveNotifyXEvent(xEvent);
                break;

           case FocusIn:
                isHandled = OnFocusInXEvent(xEvent);
                break;

           case FocusOut:
                isHandled = OnFocusOutXEvent(xEvent);
                break;

           case KeymapNotify:
                isHandled = OnKeymapNotifyXEvent(xEvent);
                break;

           case Expose:
                isHandled = OnExposeXEvent(xEvent);
                break;

           case GraphicsExpose:
                isHandled = OnGraphicsExposeXEvent(xEvent);
                break;

           case NoExpose:
                isHandled = OnNoExposeXEvent(xEvent);
                break;

           case VisibilityNotify:
                isHandled = OnVisibilityNotifyXEvent(xEvent);
                break;

           case CreateNotify:
                isHandled = OnCreateNotifyXEvent(xEvent);
                break;

           case DestroyNotify:
                isHandled = OnDestroyNotifyXEvent(xEvent);
                break;

           case UnmapNotify:
                isHandled = OnUnmapNotifyXEvent(xEvent);
                break;

           case MapNotify:
                isHandled = OnMapNotifyXEvent(xEvent);
                break;

           case MapRequest:
                isHandled = OnMapRequestXEvent(xEvent);
                break;

           case ReparentNotify:
                isHandled = OnReparentNotifyXEvent(xEvent);
                break;

           case ConfigureNotify:
                isHandled = OnConfigureNotifyXEvent(xEvent);
                break;

           case ConfigureRequest:
                isHandled = OnConfigureRequestXEvent(xEvent);
                break;

           case GravityNotify:
                isHandled = OnGravityNotifyXEvent(xEvent);
                break;

           case ResizeRequest:
                isHandled = OnResizeRequestXEvent(xEvent);
                break;

           case CirculateNotify:
                isHandled = OnCirculateNotifyXEvent(xEvent);
                break;

           case CirculateRequest:
                isHandled = OnCirculateRequestXEvent(xEvent);
                break;

           case PropertyNotify:
                isHandled = OnPropertyNotifyXEvent(xEvent);
                break;

           case SelectionClear:
                isHandled = OnSelectionClearXEvent(xEvent);
                break;

           case SelectionRequest:
                isHandled = OnSelectionRequestXEvent(xEvent);
                break;

           case SelectionNotify:
                isHandled = OnSelectionNotifyXEvent(xEvent);
                break;

           case ColormapNotify:
                isHandled = OnColormapNotifyXEvent(xEvent);
                break;

           case ClientMessage:
                isHandled = OnClientMessageXEvent(xEvent);
                break;

           case MappingNotify:
                isHandled = OnMappingNotifyXEvent(xEvent);
                break;

           default:
                isHandled = OnXEventDefault(xEvent);
                break;

#if defined(XOS_GUI_X11_MEMBER_CASES_SWITCH)
        }
#endif // defined(XOS_GUI_X11_MEMBER_CASES_SWITCH) 

