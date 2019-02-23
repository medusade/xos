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
///   File: Callback.hpp
///
/// Author: $author$
///   Date: 4/2/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_X11_XT_CALLBACK_HPP
#define _XOS_GUI_X11_XT_CALLBACK_HPP

#include "xos/gui/x11/Intrinsic.hpp"
#include "xos/base/Base.hpp"

namespace xos {
namespace x11 {
namespace xt {

typedef InterfaceBase CallbackImplementImplement;
///////////////////////////////////////////////////////////////////////
///  Class: CallbackInterface
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS CallbackInterface: virtual public CallbackImplementImplement {
public:
    typedef CallbackImplementImplement Implements;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void OnXtCallback
    (XtWidget xtWidget, XtPointer clientData, XtPointer callData) {
    }
    static void XtCallback
    (XtWidget xtWidget, XtPointer clientData, XtPointer callData) {
        CallbackInterface* callback;
        if ((callback = (CallbackInterface*)(clientData)))
            callback->OnXtCallback(xtWidget, clientData, callData);
    }
};
typedef CallbackInterface CallbackImplement;
typedef ExportBase CallbackExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Callback
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Callback
: virtual public CallbackImplement, public CallbackExtend {
public:
    typedef CallbackImplement Implements;
    typedef CallbackExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: Callback
    ///////////////////////////////////////////////////////////////////////
    Callback() {
    }
    virtual ~Callback() {
    }
};

} // namespace xt 
} // namespace x11 
} // namespace xos 

#endif // _XOS_GUI_X11_XT_CALLBACK_HPP 
