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
///   File: Content.hpp
///
/// Author: $author$
///   Date: 4/4/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_INET_HTTP_CGI_CONTENT_HPP
#define _XOS_INET_HTTP_CGI_CONTENT_HPP

#include "xos/inet/http/Content.hpp"
#include "xos/os/FILEReader.hpp"

namespace xos {
namespace http {
namespace cgi {

typedef FILEReaderImplement ContentImplement;
typedef FILEReader ContentExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Content
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Content: virtual public ContentImplement, public ContentExtend {
public:
    typedef ContentImplement Implements;
    typedef ContentExtend Extends;
    typedef http::Content::Type Type;
    typedef http::Content::Reader Reader;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Content(FILE* detached = 0): Extends(detached) {
    }
    virtual ~Content() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace cgi 
} // namespace http 
} // namespace xos 


#endif // _XOS_INET_HTTP_CGI_CONTENT_HPP 
        

