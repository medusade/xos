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
///   File: Screen.hpp
///
/// Author: $author$
///   Date: 3/16/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_X11_XCB_SCREEN_HPP
#define _XOS_GUI_X11_XCB_SCREEN_HPP

#include "xos/base/Attached.hpp"
#include "xos/base/Wrapped.hpp"
#include "xos/os/Logger.hpp"
#include <xcb/xcb.h>

namespace xos {
namespace x11 {
namespace xcb {

typedef InterfaceBase ScreenImplement;
typedef Attached<xcb_screen_t*, int, 0> ScreenExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Screen
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Screen
: virtual public ScreenImplement, public ScreenExtend {
public:
    typedef ScreenImplement Implements;
    typedef ScreenExtend Extends;
    class _EXPORT_CLASS iterator;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: Screen
    ///////////////////////////////////////////////////////////////////////
    Screen(AttachedT detached = 0): Extends(detached) {
    }
    virtual ~Screen() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual xcb_colormap_t DefaultColormapId() const {
        if ((m_attachedTo))
            return m_attachedTo->default_colormap;
        return 0;
    }

    virtual xcb_visualid_t RootVisualId() const {
        if ((m_attachedTo))
            return m_attachedTo->root_visual;
        return 0;
    }
    virtual xcb_window_t RootWindowId() const {
        if ((m_attachedTo))
            return m_attachedTo->root;
        return 0;
    }
    virtual uint8_t RootDepth() const {
        if ((m_attachedTo))
            return m_attachedTo->root_depth;
        return 0;
    }

    virtual uint32_t BlackPixel() const {
        if ((m_attachedTo))
            return m_attachedTo->black_pixel;
        return 0;
    }
    virtual uint32_t WhitePixel() const {
        if ((m_attachedTo))
            return m_attachedTo->white_pixel;
        return 0;
    }
};

typedef InterfaceBase ScreenIteratorImplement;
typedef Wrapped
<xcb_screen_iterator_t, int, ExportBase, ScreenIteratorImplement> 
ScreenIteratorExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Screen::iterator
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Screen::iterator
: virtual public ScreenIteratorImplement, public ScreenIteratorExtend {
public:
    typedef ScreenIteratorImplement Implements;
    typedef ScreenIteratorExtend Extends;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: iterator
    ///////////////////////////////////////////////////////////////////////
    iterator(const xcb_screen_iterator_t& xcbScreenIterator) {
        Copy(xcbScreenIterator);
    }
    iterator(const iterator& copy): Extends(copy) {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual xcb_screen_t* operator * () {
        return wrapped().data;
    }
};

} // namespace xcb 
} // namespace x11 
} // namespace xos 

#endif // _XOS_GUI_X11_XCB_SCREEN_HPP 
