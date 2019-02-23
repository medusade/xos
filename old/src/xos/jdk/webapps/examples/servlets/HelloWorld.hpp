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
///   File: HelloWorld.hpp
///
/// Author: $author$
///   Date: 3/4/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_JDK_WEBAPPS_EXAMPLES_SERVLETS_HELLOWORLD_HPP
#define _XOS_JDK_WEBAPPS_EXAMPLES_SERVLETS_HELLOWORLD_HPP

#include "xos/jdk/javax/servlet/http/HttpServlet.hpp"

namespace xos {
namespace javax {
namespace servlet {
namespace http {
namespace examples {

using java::io::PrintWriter;

///////////////////////////////////////////////////////////////////////
///  Class: HelloWorld
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS HelloWorld: public HttpServlet {
public:
    typedef HttpServlet Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool doGet(const HttpServletRequest& request, HttpServletResponse& response) {
        response.setContentType("text/html");
        PrintWriter& out = response.getWriter();
        out.print("<html>");
        out.println("<head>");
        out.println("<title>Hello World!</title>");
        out.println("</head>");
        out.println("<body>");
        out.println("<h1>Hello World!</h1>");
        out.println("</body>");
        out.println("</html>");
        return true;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    static HelloWorld& getTheInstance();
};

} // namespace examples
} // namespace http
} // namespace servlet
} // namespace javax 
} // namespace xos 

#endif // _XOS_JDK_WEBAPPS_EXAMPLES_SERVLETS_HELLOWORLD_HPP 
