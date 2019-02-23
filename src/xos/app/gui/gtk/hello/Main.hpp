///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2016 $organization$
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
///   Date: 4/29/2016
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_APP_GUI_GTK_HELLO_MAIN_HPP
#define _XOS_APP_GUI_GTK_HELLO_MAIN_HPP

#include "xos/gui/gtk/application/WindowMain.hpp"

namespace xos {
namespace app {
namespace gui {
namespace gtk {
namespace hello {

typedef xos::gtk::application::WindowMainImplements MainImplements;
typedef xos::gtk::application::WindowMain MainExtends;
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Main: virtual public MainImplements, public MainExtends {
public:
    typedef MainImplements Implements;
    typedef MainExtends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Main() {
    }
    virtual ~Main() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace hello 
} // namespace gtk 
} // namespace gui 
} // namespace app 
} // namespace xos 

#endif // _XOS_APP_GUI_GTK_HELLO_MAIN_HPP 
