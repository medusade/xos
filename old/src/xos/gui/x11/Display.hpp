///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2012 $organization$
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
///   File: Display.hpp
///
/// Author: $author$
///   Date: Aug 5, 2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_X11_DISPLAY_HPP_
#define _XOS_GUI_X11_DISPLAY_HPP_

#include "xos/gui/x11/Screen.hpp"
#include "xos/base/Opened.hpp"
#include "xos/os/Logger.hpp"

namespace xos {
namespace x11 {

typedef InterfaceBase DisplayImplement;
typedef xos::Attached<XDisplay*, int, 0> DisplayAttached;
typedef xos::Opened<XDisplay*, int, 0, DisplayAttached> DisplayExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Display
///////////////////////////////////////////////////////////////////////
class EXPORT_CLASS Display: virtual public DisplayImplement, public DisplayExtend {
public:
    typedef DisplayImplement Implements;
    typedef DisplayExtend Extends;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: Display
    ///////////////////////////////////////////////////////////////////////
    Display(XDisplay* attachedTo=0):Extends(attachedTo){}
    virtual ~Display(){}

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Open(const char* displayName){
        XDisplay* detached;
        if ((displayName)) {
            if ((detached = XOpenDisplay(displayName))){
                if ((m_screen.AttachDisplay(*detached))) {
                    AttachOpened(detached);
                    return true;
                }
                XCloseDisplay(detached);
            }
            XOS_LOG_ERROR("failed on XOpenDisplay(\"" << displayName << "\")");
        }
        return false;
    }
    virtual bool Close(){
        bool isSuccess = false;
        XDisplay* detached;
        if ((detached = Detach())){
            XCloseDisplay(detached);
            isSuccess = true;
        }
        m_screen.Detach();
        return isSuccess;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual XScreen* AttachWithScreenOf(XDisplay* detached, bool isOpen = false) {
        XScreen* xScreen = 0;
        if ((detached = Attach(detached, isOpen))) {
            if (!(xScreen = m_screen.AttachDisplay(*detached)))
                Detach();
        }
        return xScreen;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual XWindow RootWindowAttachedTo() const {
        XWindow xWindow = None;
        XScreen* xScreen = 0;
        if ((xScreen = ScreenAttachedTo()))
            xWindow = XRootWindowOfScreen(xScreen);
        return xWindow;
    }
    virtual XScreen* ScreenAttachedTo() const {
        XScreen* xScreen = m_screen.AttachedTo();
        return  xScreen;
    }

protected:
    Screen m_screen;
};

} // namespace x11
} // namespace xos

#endif // _XOS_GUI_X11_DISPLAY_HPP_
