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
///   File: AppContext.hpp
///
/// Author: $author$
///   Date: 7/1/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_X11_XT_APPCONTEXT_HPP
#define _XOS_GUI_X11_XT_APPCONTEXT_HPP

#include "xos/gui/x11/Intrinsic.hpp"
#include "xos/gui/x11/Created.hpp"
#include "xos/gui/x11/Attached.hpp"

namespace xos {
namespace x11 {
namespace xt {

///////////////////////////////////////////////////////////////////////
///  Class: AppContextInterface
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS AppContextInterface
: virtual public InterfaceBase {
public:
};
typedef AppContextInterface AppContextImplement;
typedef Attached<XtAppContext, int, 0> AppContextAttached;
typedef xos::Created<XtAppContext, int, 0, AppContextAttached> AppContextCreated;
typedef Created<XtAppContext, int, 0, AppContextCreated> AppContextExtend;
///////////////////////////////////////////////////////////////////////
///  Class: AppContext
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS AppContext
: virtual public AppContextImplement, public AppContextExtend {
public:
    typedef AppContextImplement Implements;
    typedef AppContextExtend Extends;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: AppContext
    ///////////////////////////////////////////////////////////////////////
    AppContext
    (XDisplay* xDisplay = 0, XtAppContext xtAppContext = 0, bool isCreated = false)
    : Extends(xDisplay, xtAppContext, isCreated) {
    }
    virtual ~AppContext() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Create(XDisplay* display=0) {
        bool isSuccess = false;
        XtAppContext detached;
        if ((Destroyed())) {
            if ((detached = CreateDetached())) {
                AttachCreated(display, detached);
                return true;
            }
        }
        return isSuccess;
    }
    virtual bool Destroy() {
        bool isSuccess = false;
        bool isCreated = false;
        XDisplay* display = 0;
        XtAppContext detached;
        if ((detached = Detach(display, isCreated))) {
            isSuccess = DestroyDetached(detached);
        }
        return isSuccess;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual XtAppContext CreateDetached() const {
        XtAppContext xtAppContext = XtCreateApplicationContext();
        return xtAppContext;
    }
    virtual bool DestroyDetached(XtAppContext xtAppContext) const {
        bool isSuccess = false;
        if ((isSuccess = (xtAppContext !=0)))
            XtDestroyApplicationContext(xtAppContext);
        return isSuccess;
    }
};

} // namespace xt 
} // namespace x11 
} // namespace xos 

#endif // _XOS_GUI_X11_XT_APPCONTEXT_HPP 
