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
#ifndef _XOS_GUI_GTK_MAIN_HPP
#define _XOS_GUI_GTK_MAIN_HPP

#include "xos/gui/gtk/Gtk.hpp"
#include "xos/gui/Main.hpp"

namespace xos {
namespace gtk {

typedef gui::MainImplements MainImplements;
typedef gui::Main MainExtends;
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
    virtual int EventLoop(int argc, char** argv, char** env) {
        int err = 0;
        XOS_LOG_MESSAGE_DEBUG("gtk_main()...");
        gtk_main();
        XOS_LOG_MESSAGE_DEBUG("...gtk_main()");
        return err;
    }
    virtual int BeforeEventLoop(int argc, char** argv, char** env) {
        int err = 0;
        int* pargc = 0;
        char*** pargv = 0;
        XOS_LOG_MESSAGE_DEBUG("gtk_init_check()...");
        if (TRUE != (gtk_init_check(pargc ,pargv))) {
            XOS_LOG_ERROR("...failed on gtk_init_check()");
            err = 1;
        } else {
            XOS_LOG_MESSAGE_DEBUG("...gtk_init_check()");
        }
        return err;
    }
    virtual int AfterEventLoop(int argc, char** argv, char** env) {
        int err = 0;
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace gtk 
} // namespace xos 

#endif // _XOS_GUI_GTK_MAIN_HPP 
