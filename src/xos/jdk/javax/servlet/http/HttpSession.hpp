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
///   File: HttpSession.hpp
///
/// Author: $author$
///   Date: 2/27/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_JAVAX_SERVLET_HTTP_HTTPSESSION_HPP
#define _XOS_JAVAX_SERVLET_HTTP_HTTPSESSION_HPP

#include "xos/jdk/java/lang/Object.hpp"

namespace xos {
namespace javax {
namespace servlet {
namespace http {

typedef InterfaceBase HttpSessionImplement;
///////////////////////////////////////////////////////////////////////
///  Class: HttpSession
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS HttpSession: virtual public HttpSessionImplement {
public:
    typedef HttpSessionImplement Implements;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

///////////////////////////////////////////////////////////////////////
///  Class: NullHttpSession
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS NullHttpSession: virtual public HttpSession, public ExportBase {
public:
    typedef HttpSession Implements;
    typedef ExportBase Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    NullHttpSession() {
    }
    virtual ~NullHttpSession() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace http
} // namespace servlet 
} // namespace javax 
} // namespace xos 

#endif // _XOS_JAVAX_SERVLET_HTTP_HTTPSESSION_HPP 
