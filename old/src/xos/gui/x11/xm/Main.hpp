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
///   File: Main.hpp
///
/// Author: $author$
///   Date: 7/3/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_X11_XM_MAIN_HPP
#define _XOS_GUI_X11_XM_MAIN_HPP

#include "xos/gui/x11/xt/Main.hpp"

#define XOS_GUI_X11_XM_MAIN_APP_NAME "xos::x11::xm::Main"
#define XOS_GUI_X11_XM_MAIN_APP_CLASS_NAME XOS_GUI_X11_XM_MAIN_APP_NAME

namespace xos {
namespace x11 {
namespace xm {

typedef xt::MainImplement MainImplement;
typedef xt::Main MainExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Main
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Main
: virtual public MainImplement, public MainExtend {
public:
    typedef MainImplement Implements;
    typedef MainExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: Main
    ///////////////////////////////////////////////////////////////////////
    Main
    (const XtChar* appName = XOS_GUI_X11_XM_MAIN_APP_NAME,
     const XtChar* appClassName = XOS_GUI_X11_XM_MAIN_APP_CLASS_NAME)
    : Extends(appName, appClassName) {
    }
    virtual ~Main() {
    }
};

} // namespace xm 
} // namespace x11 
} // namespace xos 

#endif // _XOS_GUI_X11_XM_MAIN_HPP 
