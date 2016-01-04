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
///   File: Arg.hpp
///
/// Author: $author$
///   Date: 3/30/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_X11_XT_ARG_HPP
#define _XOS_GUI_X11_XT_ARG_HPP

#include "xos/gui/x11/xt/String.hpp"
#include "xos/gui/x11/Intrinsic.hpp"
#include "xos/base/Wrapped.hpp"

namespace xos {
namespace x11 {
namespace xt {

typedef InterfaceBase ArgImplement;
typedef Wrapped<XtArg> ArgExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Arg
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Arg: virtual public ArgImplement, public ArgExtend {
public:
    typedef ArgImplement Implements;
    typedef ArgExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: Arg
    ///////////////////////////////////////////////////////////////////////
    Arg(XtArg& xtArg, const Char* argName=0, XtArgVal argVal=0): Extends(xtArg) {
        if ((argName)) {
            m_argName.Assign(argName);
            m_wrapped.name = m_argName.str();
            m_wrapped.value = argVal;
        }
    }
    virtual ~Arg() {
        m_wrapped.value = 0;
        m_wrapped.name = 0;
    }
protected:
    String m_argName;
};

} // namespace xt 
} // namespace x11 
} // namespace xos 

#endif // _XOS_GUI_X11_XT_ARG_HPP 
