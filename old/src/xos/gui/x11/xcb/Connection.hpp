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
///   File: Connection.hpp
///
/// Author: $author$
///   Date: 3/16/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_X11_XCB_CONNECTION_HPP
#define _XOS_GUI_X11_XCB_CONNECTION_HPP

#include "xos/base/Opened.hpp"
#include "xos/os/Logger.hpp"
#include <xcb/xcb.h>

namespace xos {
namespace x11 {
namespace xcb {

typedef InterfaceBase ConnectionImplement;
typedef Attached<xcb_connection_t*, int, 0> ConnectionAttached;
typedef Opened<xcb_connection_t*, int, 0, ConnectionAttached> ConnectionExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Connection
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Connection
: virtual public ConnectionImplement, public ConnectionExtend {
public:
    typedef ConnectionImplement Implements;
    typedef ConnectionExtend Extends;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: Connection
    ///////////////////////////////////////////////////////////////////////
    Connection(AttachedT detached = 0, bool isOpen = false)
    : Extends(detached, isOpen) {
    }
    virtual ~Connection() {
    }

    virtual bool Open(const char* display, int* screen) {
        AttachedT detached;
        XOS_LOG_DEBUG("xcb_connect()...");
        if ((detached = xcb_connect(display, screen))) {
            if ((xcb_connection_has_error(detached))) {
                XOS_LOG_ERROR("failed xcb_connection_has_error() on xcb_connect()");
                xcb_disconnect(detached);
                return false;
            }
            XOS_LOG_DEBUG("...xcb_connect()");
            AttachOpened(detached);
            return true;
        } else {
            XOS_LOG_ERROR("failed on xcb_connect()");
        }
        return false;
    }
    virtual bool Close() {
        AttachedT detached;
        bool isCreated;
        if ((detached = Detach(isCreated))) {
            XOS_LOG_DEBUG("xcb_disconnect()...");
            xcb_disconnect(detached);
            if ((xcb_connection_has_error(detached))) {
                XOS_LOG_ERROR("failed xcb_connection_has_error() on xcb_disconnect()");
                return false;
            }
            XOS_LOG_DEBUG("...xcb_disconnect()");
            return true;
        }
        return false;
    }

    virtual const xcb_setup_t* GetSetup() const {
        const xcb_setup_t* setup = 0;
        AttachedT detached;
        if ((detached = AttachedTo())) {
            XOS_LOG_DEBUG("xcb_get_setup()...");
            if ((setup = xcb_get_setup(detached))) {
                XOS_LOG_DEBUG("...xcb_get_setup()");
            } else {
                XOS_LOG_ERROR("failed on xcb_get_setup()");
            }
        }
        return setup;
    }
};

} // namespace xcb 
} // namespace x11 
} // namespace xos 

#endif // _XOS_GUI_X11_XCB_CONNECTION_HPP 
