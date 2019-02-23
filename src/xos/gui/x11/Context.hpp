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
///   File: Context.hpp
///
/// Author: $author$
///   Date: 3/24/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_X11_CONTEXT_HPP
#define _XOS_GUI_X11_CONTEXT_HPP

#include "xos/gui/x11/Created.hpp"
#include "xos/gui/x11/Attached.hpp"

namespace xos {
namespace x11 {

typedef InterfaceBase ContextImplement;
typedef Attached<XContext, int, 0> ContextAttached;
typedef xos::Created<XContext, int, 0, ContextAttached> ContextCreated;
typedef Created<XContext, int, 0, ContextCreated> ContextExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Context
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Context
: virtual public ContextImplement, public ContextExtend {
public:
    typedef ContextImplement Implements;
    typedef ContextExtend Extends;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: Context
    ///////////////////////////////////////////////////////////////////////
    Context(XDisplay* xDisplay=0, XContext detached=0, bool isCreated=false)
    : Extends(xDisplay, detached, isCreated) {
    }
    virtual ~Context() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Create(XDisplay& xDisplay) {
        if ((Destroyed())) {
            XContext detached;
            detached = XUniqueContext();
            AttachCreated(&xDisplay, detached);
            return true;
        }
        return false;
    }
    virtual bool Destroy() {
        bool isSuccess = false;
        bool isCreated = false;
        XDisplay* xDisplay = 0;
        XContext detached = Detach(xDisplay, isCreated);
        if ((xDisplay))
            isSuccess = true;
        return isSuccess;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Save(XDisplay& xDisplay, XID xID, XPointer data) {
        bool isSuccess = true;
        XSaveContext(&xDisplay, xID, m_attachedTo, data);
        return isSuccess;
    }
    virtual bool Delete(XDisplay& xDisplay, XID xID) {
        bool isSuccess = true;
        XDeleteContext(&xDisplay, xID, m_attachedTo);
        return isSuccess;
    }
    virtual XPointer Find(XDisplay& xDisplay, XID xID) {
        XPointer found = 0;
        XFindContext(&xDisplay, xID, m_attachedTo, &found);
        return found;
    }
};

} // namespace x11 
} // namespace xos 

#endif // _XOS_GUI_X11_CONTEXT_HPP 
