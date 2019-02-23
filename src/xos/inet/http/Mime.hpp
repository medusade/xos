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
///   File: Mime.hpp
///
/// Author: $author$
///   Date: 6/13/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_INET_HTTP_MIME_HPP
#define _XOS_INET_HTTP_MIME_HPP

#include "xos/base/String.hpp"

namespace xos {
namespace http {

typedef InterfaceBase MimeImplement;
typedef ExportBase MimeExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Mime
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Mime: virtual public MimeImplement,public MimeExtend {
public:
    typedef MimeImplement Implements;
    typedef MimeExtend Extends;

    typedef InterfaceBase TypeImplement;
    typedef ExportBase TypeExtend;
    ///////////////////////////////////////////////////////////////////////
    ///  Class: Type
    ///////////////////////////////////////////////////////////////////////
    class _EXPORT_CLASS Type: virtual public TypeImplement,public TypeExtend {
    public:
        typedef TypeImplement Implements;
        typedef TypeExtend Extends;

        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        Type() {
        }
        virtual ~Type() {
        }
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        virtual bool GetNameOfExtension(String& name, const String& of) const {
            return false;
        }
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        static Type& GetTheInstance();
    };

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Mime() {
    }
    virtual ~Mime() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace http 
} // namespace xos 

#endif // _XOS_INET_HTTP_MIME_HPP 
