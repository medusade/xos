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
///   File: Gc.hpp
///
/// Author: $author$
///   Date: 3/19/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_X11_XCB_GC_HPP
#define _XOS_GUI_X11_XCB_GC_HPP

#include "xos/gui/x11/xcb/Created.hpp"
#include "xos/os/Logger.hpp"

namespace xos {
namespace x11 {
namespace xcb {

typedef InterfaceBase GcImplement;
typedef Attached<xcb_gcontext_t, int, 0> GcAttached;
typedef xos::Created<xcb_gcontext_t, int, 0, GcAttached> GcCreated;
typedef Created<xcb_gcontext_t, int, 0, GcCreated> GcExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Gc
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Gc
: virtual public GcImplement, public GcExtend {
public:
    typedef GcImplement Implements;
    typedef GcExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: Gc
    ///////////////////////////////////////////////////////////////////////
    Gc(xcb_connection_t* connection=0, AttachedT detached=0, bool isCreated=false)
    : Extends(connection, detached, isCreated) {
    }
    virtual ~Gc() {
        if (!(Destroyed()))
        {   XOS_LOG_ERROR("failed on Destroyed()"); }
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Create
    (xcb_connection_t* connection, xcb_gcontext_t gcId, 
     xcb_drawable_t drawableId, uint32_t valueMask, const uint32_t* valueList) {
        xcb_generic_error_t* error;
        if (!(error = xcb_request_check(connection, xcb_create_gc_checked
            (connection, gcId, drawableId, valueMask, valueList)))) {
            AttachCreated(connection, gcId);
            return true;
        } else {
            XOS_LOG_ERROR("failed " << error->error_code << " on xcb_create_gc_checked()");
            free(error);
        }
        return false;
    }
    virtual bool Destroy() {
        bool isSuccess = false;
        xcb_connection_t* connection = 0;
        xcb_gcontext_t gcId = 0;
        bool isCreated = false;
        if ((gcId = Detach(connection, isCreated))) {
            xcb_generic_error_t* error;
            if (!(isSuccess = !(error = xcb_request_check(connection, 
                xcb_free_gc_checked(connection, gcId))))) {
                XOS_LOG_ERROR("failed " << error->error_code << " on xcb_free_gc_checked()");
                free(error);
            }
        }
        return isSuccess;
    }
};

} // namespace xcb 
} // namespace x11 
} // namespace xos 

#endif // _XOS_GUI_X11_XCB_GC_HPP 
