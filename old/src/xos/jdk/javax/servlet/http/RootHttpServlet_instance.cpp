///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2014 $organization$
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
///   File: RootHttpServlet_instance.cpp
///
/// Author: $author$
///   Date: 3/2/2014
///////////////////////////////////////////////////////////////////////
#include "xos/jdk/javax/servlet/http/RootHttpServlet.hpp"
#include "xos/jdk/webapps/examples/servlets/HelloWorld.hpp"

namespace xos {
namespace javax {
namespace servlet {
namespace http {

///////////////////////////////////////////////////////////////////////
///  Class: RootHttpServlet
///////////////////////////////////////////////////////////////////////

RootHttpServlet& RootHttpServlet::getTheInstance() {
    class _EXPORT_CLASS RootHttpServlet: public http::RootHttpServlet {
    protected:
        virtual HttpServlet* getServletToService
        (const HttpServletRequest& req, HttpServletResponse& resp) const {
            return &examples::HelloWorld::getTheInstance();
        }
    };
    static RootHttpServlet theInstance;
    return theInstance;
}

} // namespace http 
} // namespace servlet 
} // namespace javax 
} // namespace xos 


        

