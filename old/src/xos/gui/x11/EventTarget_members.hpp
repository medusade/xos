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
///   File: EventTarget_members.hpp
///
/// Author: $author$
///   Date: 3/23/2013
///////////////////////////////////////////////////////////////////////

#if defined(XOS_GUI_X11_EVENTTARGET_MEMBERS_CLASS)
typedef InterfaceBase EventTargetImplement;
///////////////////////////////////////////////////////////////////////
//  Class: EventTarget
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS EventTarget: virtual public EventTargetImplement {
public:
    typedef EventTargetImplement Implements;
#endif // XOS_GUI_X11_EVENTTARGET_MEMBERS_CLASS

    virtual bool OnKeyPressXEvent(const XEvent& xEvent) {
        bool isHandled = false;
        isHandled = OnXEventDefault(xEvent);
        return isHandled;
    }
    virtual bool OnKeyReleaseXEvent(const XEvent& xEvent) {
        bool isHandled = false;
        isHandled = OnXEventDefault(xEvent);
        return isHandled;
    }
    virtual bool OnButtonPressXEvent(const XEvent& xEvent) {
        bool isHandled = false;
        isHandled = OnXEventDefault(xEvent);
        return isHandled;
    }
    virtual bool OnButtonReleaseXEvent(const XEvent& xEvent) {
        bool isHandled = false;
        isHandled = OnXEventDefault(xEvent);
        return isHandled;
    }
    virtual bool OnMotionNotifyXEvent(const XEvent& xEvent) {
        bool isHandled = false;
        isHandled = OnXEventDefault(xEvent);
        return isHandled;
    }
    virtual bool OnEnterNotifyXEvent(const XEvent& xEvent) {
        bool isHandled = false;
        isHandled = OnXEventDefault(xEvent);
        return isHandled;
    }
    virtual bool OnLeaveNotifyXEvent(const XEvent& xEvent) {
        bool isHandled = false;
        isHandled = OnXEventDefault(xEvent);
        return isHandled;
    }
    virtual bool OnFocusInXEvent(const XEvent& xEvent) {
        bool isHandled = false;
        isHandled = OnXEventDefault(xEvent);
        return isHandled;
    }
    virtual bool OnFocusOutXEvent(const XEvent& xEvent) {
        bool isHandled = false;
        isHandled = OnXEventDefault(xEvent);
        return isHandled;
    }
    virtual bool OnKeymapNotifyXEvent(const XEvent& xEvent) {
        bool isHandled = false;
        isHandled = OnXEventDefault(xEvent);
        return isHandled;
    }
    virtual bool OnExposeXEvent(const XEvent& xEvent) {
        bool isHandled = false;
        isHandled = OnXEventDefault(xEvent);
        return isHandled;
    }
    virtual bool OnGraphicsExposeXEvent(const XEvent& xEvent) {
        bool isHandled = false;
        isHandled = OnXEventDefault(xEvent);
        return isHandled;
    }
    virtual bool OnNoExposeXEvent(const XEvent& xEvent) {
        bool isHandled = false;
        isHandled = OnXEventDefault(xEvent);
        return isHandled;
    }
    virtual bool OnVisibilityNotifyXEvent(const XEvent& xEvent) {
        bool isHandled = false;
        isHandled = OnXEventDefault(xEvent);
        return isHandled;
    }
    virtual bool OnCreateNotifyXEvent(const XEvent& xEvent) {
        bool isHandled = false;
        isHandled = OnXEventDefault(xEvent);
        return isHandled;
    }
    virtual bool OnDestroyNotifyXEvent(const XEvent& xEvent) {
        bool isHandled = false;
        isHandled = OnXEventDefault(xEvent);
        return isHandled;
    }
    virtual bool OnUnmapNotifyXEvent(const XEvent& xEvent) {
        bool isHandled = false;
        isHandled = OnXEventDefault(xEvent);
        return isHandled;
    }
    virtual bool OnMapNotifyXEvent(const XEvent& xEvent) {
        bool isHandled = false;
        isHandled = OnXEventDefault(xEvent);
        return isHandled;
    }
    virtual bool OnMapRequestXEvent(const XEvent& xEvent) {
        bool isHandled = false;
        isHandled = OnXEventDefault(xEvent);
        return isHandled;
    }
    virtual bool OnReparentNotifyXEvent(const XEvent& xEvent) {
        bool isHandled = false;
        isHandled = OnXEventDefault(xEvent);
        return isHandled;
    }
    virtual bool OnConfigureNotifyXEvent(const XEvent& xEvent) {
        bool isHandled = false;
        isHandled = OnXEventDefault(xEvent);
        return isHandled;
    }
    virtual bool OnConfigureRequestXEvent(const XEvent& xEvent) {
        bool isHandled = false;
        isHandled = OnXEventDefault(xEvent);
        return isHandled;
    }
    virtual bool OnGravityNotifyXEvent(const XEvent& xEvent) {
        bool isHandled = false;
        isHandled = OnXEventDefault(xEvent);
        return isHandled;
    }
    virtual bool OnResizeRequestXEvent(const XEvent& xEvent) {
        bool isHandled = false;
        isHandled = OnXEventDefault(xEvent);
        return isHandled;
    }
    virtual bool OnCirculateNotifyXEvent(const XEvent& xEvent) {
        bool isHandled = false;
        isHandled = OnXEventDefault(xEvent);
        return isHandled;
    }
    virtual bool OnCirculateRequestXEvent(const XEvent& xEvent) {
        bool isHandled = false;
        isHandled = OnXEventDefault(xEvent);
        return isHandled;
    }
    virtual bool OnPropertyNotifyXEvent(const XEvent& xEvent) {
        bool isHandled = false;
        isHandled = OnXEventDefault(xEvent);
        return isHandled;
    }
    virtual bool OnSelectionClearXEvent(const XEvent& xEvent) {
        bool isHandled = false;
        isHandled = OnXEventDefault(xEvent);
        return isHandled;
    }
    virtual bool OnSelectionRequestXEvent(const XEvent& xEvent) {
        bool isHandled = false;
        isHandled = OnXEventDefault(xEvent);
        return isHandled;
    }
    virtual bool OnSelectionNotifyXEvent(const XEvent& xEvent) {
        bool isHandled = false;
        isHandled = OnXEventDefault(xEvent);
        return isHandled;
    }
    virtual bool OnColormapNotifyXEvent(const XEvent& xEvent) {
        bool isHandled = false;
        isHandled = OnXEventDefault(xEvent);
        return isHandled;
    }
    virtual bool OnClientMessageXEvent(const XEvent& xEvent) {
        bool isHandled = false;
        isHandled = OnXEventDefault(xEvent);
        return isHandled;
    }
    virtual bool OnMappingNotifyXEvent(const XEvent& xEvent) {
        bool isHandled = false;
        isHandled = OnXEventDefault(xEvent);
        return isHandled;
    }
    virtual bool OnXEventDefault(const XEvent& xEvent) {
        bool isHandled = false;
        isHandled = DefaultXEventHandler(xEvent);
        return isHandled;
    }
    static bool DefaultXEventHandler(const XEvent& xEvent);

#if defined(XOS_GUI_X11_EVENTTARGET_MEMBERS_CLASS)
};
#endif // XOS_GUI_X11_EVENTTARGET_MEMBERS_CLASS
