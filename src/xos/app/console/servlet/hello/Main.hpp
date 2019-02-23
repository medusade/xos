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
///   Date: 10/5/2016
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_APP_CONSOLE_SERVLET_HELLO_MAIN_HPP
#define _XOS_APP_CONSOLE_SERVLET_HELLO_MAIN_HPP

#include "xos/os/Main.hpp"
#include "xos/os/os/DLibrary.hpp"

#define XOS_APP_CONSOLE_SERVLET_HELLO_LIBRARY_NAME "libXosHelloServlet"

namespace xos {
namespace app {
namespace console {
namespace servlet {
namespace hello {

typedef xos::MainImplement MainImplements;
typedef xos::Main MainExtends;
///////////////////////////////////////////////////////////////////////
///  Class: Main
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Main: virtual public MainImplements, public MainExtends {
public:
    typedef MainImplements Implements;
    typedef MainExtends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Main(): m_libraryName(XOS_APP_CONSOLE_SERVLET_HELLO_LIBRARY_NAME) {
    }
    virtual ~Main() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    int Run(int argc, char **argv, char **env) {
        int err = 0;
        os::DLibrary dl;
        if ((dl.Open(m_libraryName.Chars()))) {
            dl.Close();
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    String m_libraryName;
};

} // namespace hello 
} // namespace servlet 
} // namespace console 
} // namespace app 
} // namespace xos 

#endif // _XOS_APP_CONSOLE_SERVLET_HELLO_MAIN_HPP 
        

