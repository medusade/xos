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
///   File: Colormap.hpp
///
/// Author: $author$
///   Date: 3/25/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_X11_COLORMAP_HPP
#define _XOS_GUI_X11_COLORMAP_HPP

#include "xos/gui/x11/Created.hpp"
#include "xos/gui/x11/Attached.hpp"
#include "xos/os/Logger.hpp"

namespace xos {
namespace x11 {

typedef InterfaceBase ColormapImplement;
typedef Attached<XColormap, int, 0> ColormapAttached;
typedef xos::Created<XColormap, int, 0, ColormapAttached> ColormapCreated;
typedef Created<XColormap, int, 0, ColormapCreated> ColormapExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Colormap
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Colormap: virtual public ColormapImplement, public ColormapExtend {
public:
    typedef ColormapImplement Implements;
    typedef ColormapExtend Extends;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: Colormap
    ///////////////////////////////////////////////////////////////////////
    Colormap(XDisplay* xDisplay=0, XColormap detached=0, bool isCreated=false)
    : Extends(xDisplay, detached, isCreated) {
    }
    virtual ~Colormap() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Create
    (XDisplay& xDisplay, XWindow xWindow, 
     XVisual& xVisual, int allocEntries = AllocAll) {
        bool isSuccess = false;
        if ((Destroyed())) {
            XColormap detached;
            if ((detached = XCreateColormap
                (&xDisplay, xWindow, &xVisual, allocEntries))) {
                Attach(&xDisplay, detached);
                isSuccess = true;
            } else {
                XOS_LOG_ERROR("failed on XCreateColormap()");
            }
        }
        return isSuccess;
    }
    virtual bool Destroy() {
        bool isSuccess = false;
        bool isCreated = false;
        XDisplay* xDisplay = 0;
        XColormap detached = Detach(xDisplay, isCreated);
        if ((detached)) {
            XFreeColormap(xDisplay, detached);
            isSuccess = true;
        }
        return isSuccess;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual XColormap AttachDefault(XDisplay& xDisplay) {
        unsigned int screenNumber = XDefaultScreen(&xDisplay);
        XColormap detached = AttachDefaultOfScreen(xDisplay, screenNumber);
        return detached;
    }
    virtual XColormap AttachDefaultOfScreen
    (XDisplay& xDisplay, unsigned int screenNumber) {
        XScreen* xScreen = XScreenOfDisplay(&xDisplay, screenNumber);
        XColormap detached = 0;
        if ((xScreen)) {
            detached = AttachDefaultOfScreen(xDisplay, *xScreen);
        } else {
            XOS_LOG_ERROR("failed on XScreenOfDisplay()");
        }
        return detached;
    }
    virtual XColormap AttachDefaultOfScreen
    (XDisplay& xDisplay, XScreen& xScreen) {
        XColormap detached = 0;
        if ((Destroyed())) {
            if ((detached = XDefaultColormapOfScreen(&xScreen))) {
                Attach(&xDisplay, detached);
            }
        }
        return detached;
    }
};

} // namespace x11 
} // namespace xos 

#endif // _XOS_GUI_X11_COLORMAP_HPP 
