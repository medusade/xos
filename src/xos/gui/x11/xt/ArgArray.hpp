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
///   File: ArgArray.hpp
///
/// Author: $author$
///   Date: 4/1/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_X11_XT_ARGARRAY_HPP
#define _XOS_GUI_X11_XT_ARGARRAY_HPP

#include "xos/gui/x11/xt/Arg.hpp"
#include "xos/gui/x11/Intrinsic.hpp"
#include "xos/base/Array.hpp"

namespace xos {
namespace x11 {
namespace xt {

typedef XtArg ArgElementExtend;
///////////////////////////////////////////////////////////////////////
///  Struct: ArgElement
///////////////////////////////////////////////////////////////////////
struct _EXPORT_CLASS ArgElement: ArgElementExtend {
    typedef ArgElementExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: ArgElement
    ///////////////////////////////////////////////////////////////////////
    ArgElement(XtString p_name = 0, XtArgVal p_value = 0) {
        name = p_name;
        value = p_value;
    }
};

typedef InterfaceBase ArgArrayImplement;
typedef Array<ArgElement> ArgArrayExtend;
///////////////////////////////////////////////////////////////////////
///  Class: ArgArray
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS ArgArray
: virtual public ArgArrayImplement, public ArgArrayExtend {
public:
    typedef ArgArrayImplement Implements;
    typedef ArgArrayExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: ArgArray
    ///////////////////////////////////////////////////////////////////////
    ArgArray() {
    }
    virtual ~ArgArray() {
    }
    virtual operator XtArgList() const {
        return Elements();
    }
};

} // namespace xt 
} // namespace x11 
} // namespace xos 

#endif // _XOS_GUI_X11_XT_ARGARRAY_HPP 
