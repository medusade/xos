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
///   Date: 3/24/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_X11_WINDOW_HPP
#define _XOS_GUI_X11_WINDOW_HPP

#include "xos/gui/x11/Created.hpp"
#include "xos/gui/x11/Attached.hpp"
#include "xos/gui/x11/EventTarget.hpp"
#include "xos/gui/x11/Event.hpp"
#include "xos/os/Logger.hpp"

#define XOS_GUI_X11_WINDOW_DEFAULT_XEVENT_MASK \
   ExposureMask|ColormapChangeMask|PropertyChangeMask|VisibilityChangeMask|\
   KeymapStateMask|EnterWindowMask|LeaveWindowMask|FocusChangeMask|\
   KeyPressMask|KeyReleaseMask|ButtonPressMask|ButtonReleaseMask|\
   PointerMotionMask|StructureNotifyMask|SubstructureNotifyMask|\
   SubstructureRedirectMask

#define XOS_GUI_X11_WINDOW_DEFAULT_XEVENT_GRAB_MASK \
   ButtonPressMask|ButtonReleaseMask|\
   PointerMotionMask|EnterWindowMask|LeaveWindowMask

namespace xos {
namespace x11 {

typedef EventTarget WindowImplement;
typedef Attached<XWindow, int, 0> WindowAttached;
typedef xos::Created<XWindow, int, 0, WindowAttached> WindowCreated;
typedef Created<XWindow, int, 0, WindowCreated> WindowExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Window
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Window: virtual public WindowImplement, public WindowExtend {
public:
    typedef WindowImplement Implements;
    typedef WindowExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: Window
    ///////////////////////////////////////////////////////////////////////
    Window(XDisplay* xDisplay=0, XWindow detached=0, bool isCreated=false)
    : Extends(xDisplay, detached, isCreated) {
    }
    virtual ~Window() {
        if (!(Destroyed()))
        {   XOS_LOG_ERROR("failed on Destroyed()"); }
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Create
    (XDisplay& xDisplay, XWindow parentXWindow, 
     int x,int y, unsigned int width,unsigned int height, 
     unsigned int borderWidth, XPixel border, XPixel background) {
        bool isSuccess = false;
        if ((isSuccess = Destroyed())) {
            XWindow xWindow;
            if ((isSuccess = (None != (xWindow = XCreateSimpleWindow
                (&xDisplay, parentXWindow, x,y, width,height, 
                 borderWidth, border, background))))) {
                AttachCreated(&xDisplay, xWindow);
            } else {
                XOS_LOG_ERROR("failed on XCreateSimpleWindow()");
            }
        }
        return isSuccess;
    }
    virtual bool Destroy() {
        bool isSuccess = false;
        bool isCreated = false;
        XDisplay* xDisplay = 0;
        XWindow xWindow = Detach(xDisplay, isCreated);
        if ((xDisplay) && (xWindow)) {
            XDestroyWindow(xDisplay, xWindow);
            isSuccess = true;
        }
        return isSuccess;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool SelectInput(XEventMask xEventMask) {
        XDisplay* xDisplay;
        XWindow xWindow;
        if ((xDisplay = m_display) && (None != (xWindow = m_attachedTo))) {
            XSelectInput(xDisplay, xWindow, xEventMask);
            return true;
        }
        return false;
    }
    static XEventMask GetDefaultXEventMask() {
        static XEventMask defaultXEventMask = XOS_GUI_X11_WINDOW_DEFAULT_XEVENT_MASK;
        return defaultXEventMask;
    }
    static XEventMask GetDefaultXEventGrabMask() {
        static XEventMask defaultXEventGrabMask = XOS_GUI_X11_WINDOW_DEFAULT_XEVENT_GRAB_MASK;
        return defaultXEventGrabMask;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Map() {
        XDisplay* xDisplay;
        XWindow xWindow;
        if ((xDisplay = m_display) && (None != (xWindow = m_attachedTo))) {
            XMapWindow(xDisplay, xWindow);
            return true;
        }
        return false;
    }
    virtual bool Unmap() {
        XDisplay* xDisplay;
        XWindow xWindow;
        if ((xDisplay = m_display) && (None != (xWindow = m_attachedTo))) {
            XUnmapWindow(xDisplay, xWindow);
            return true;
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Invalidate(bool eraseBackground=false) {
        XWindowAttributes xWindowAttributes;
        if ((GetWindowAttributes(xWindowAttributes))) {
            XOS_LOG_DEBUG("Invalidate(0,0, " << xWindowAttributes.width<< "," << xWindowAttributes.height<< ")...");
            return Invalidate(0,0, xWindowAttributes.width,xWindowAttributes.height, eraseBackground);
        }
        return false;
    }
    virtual bool Invalidate
    (int x,int y, int width,int height, bool eraseBackground=false) {
        XDisplay* xDisplay;
        XWindow xWindow;
        if ((xDisplay = m_display) && (None != (xWindow = m_attachedTo))) {
            if ((eraseBackground)) {
                XClearArea(xDisplay, xWindow, x,y, width,height, True);
                return true;
            } else {
                ExposeEvent xEvent(xDisplay, xWindow, x,y, width,height);
                if ((xEvent.Send()))
                    return true;
            }
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool ChangeBackground(XPixel background) {
        XSetWindowAttributesMask xSetWindowAttributesMask = CWBackPixel;
        XSetWindowAttributes xSetWindowAttributes; 
        xSetWindowAttributes.background_pixel = background;
        return ChangeWindowAttributes(xSetWindowAttributesMask, xSetWindowAttributes);
    }
    virtual bool ChangeWindowAttributes
    (XSetWindowAttributesMask xSetWindowAttributesMask,
     XSetWindowAttributes& xSetWindowAttributes) {
        XDisplay* xDisplay;
        XWindow xWindow;
        if ((xDisplay = m_display) && (None != (xWindow = m_attachedTo))) {
            XChangeWindowAttributes(xDisplay, xWindow, xSetWindowAttributesMask, &xSetWindowAttributes);
            return true;
        }
        return false;
    }
    virtual bool GetWindowAttributes
    (XWindowAttributes& xWindowAttributes) {
        XDisplay* xDisplay;
        XWindow xWindow;
        if ((xDisplay = m_display) && (None != (xWindow = m_attachedTo))) {
            XGetWindowAttributes(xDisplay, xWindow, &xWindowAttributes);
            return true;
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool StoreName(const char* chars) {
        XDisplay* xDisplay;
        XWindow xWindow;
        if ((chars) && (xDisplay = m_display) && (None != (xWindow = m_attachedTo))) {
            XStoreName(xDisplay, xWindow, chars);
            return true;
        }
        return false;
    }
};

} // namespace x11 
} // namespace xos 

#endif // _XOS_GUI_X11_WINDOW_HPP 
