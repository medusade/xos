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
///   File: Setup.hpp
///
/// Author: $author$
///   Date: 3/16/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_X11_XCB_SETUP_HPP
#define _XOS_GUI_X11_XCB_SETUP_HPP

#include "xos/gui/x11/xcb/Connection.hpp"
#include "xos/base/Attached.hpp"
#include "xos/os/Logger.hpp"

namespace xos {
namespace x11 {
namespace xcb {

typedef InterfaceBase SetupImplement;
typedef Attached<const xcb_setup_t*, int, 0> SetupExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Setup
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Setup
: virtual public SetupImplement, public SetupExtend {
public:
    typedef SetupImplement Implements;
    typedef SetupExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: Setup
    ///////////////////////////////////////////////////////////////////////
    Setup(AttachedT detached = 0): Extends(detached) {
    }
    virtual ~Setup() {
    }

    virtual xcb_screen_iterator_t* Screens() {
        xcb_screen_iterator_t* xcbScreenIterator = 0;
        AttachedT detached = 0;
        if ((detached = AttachedTo())) {
            m_xcbScreenIterator = xcb_setup_roots_iterator(detached);
            xcbScreenIterator = &m_xcbScreenIterator;
        }
        return xcbScreenIterator;
    }
protected:
    xcb_screen_iterator_t m_xcbScreenIterator;
};

} // namespace xcb 
} // namespace x11 
} // namespace xos 

#endif // _XOS_GUI_X11_XCB_SETUP_HPP 
