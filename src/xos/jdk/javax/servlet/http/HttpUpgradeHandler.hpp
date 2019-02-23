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
///   File: HttpUpgradeHandler.hpp
///
/// Author: $author$
///   Date: 2/27/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_JAVAX_SERVLET_HTTP_HTTPUPGRADEHANDLER_HPP
#define _XOS_JAVAX_SERVLET_HTTP_HTTPUPGRADEHANDLER_HPP

#include "xos/jdk/java/lang/Object.hpp"

namespace xos {
namespace javax {
namespace servlet {
namespace http {

typedef InterfaceBase HttpUpgradeHandlerImplement;
///////////////////////////////////////////////////////////////////////
///  Class: HttpUpgradeHandler
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS HttpUpgradeHandler: virtual public HttpUpgradeHandlerImplement {
public:
    typedef HttpUpgradeHandlerImplement Implements;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

///////////////////////////////////////////////////////////////////////
///  Class: NullHttpUpgradeHandler
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS NullHttpUpgradeHandler
: virtual public HttpUpgradeHandler, public ExportBase {
public:
    typedef HttpUpgradeHandler Implements;
    typedef ExportBase Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    NullHttpUpgradeHandler() {
    }
    virtual ~NullHttpUpgradeHandler() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace http
} // namespace servlet 
} // namespace javax 
} // namespace xos 

#endif // _XOS_JAVAX_SERVLET_HTTP_HTTPUPGRADEHANDLER_HPP 
