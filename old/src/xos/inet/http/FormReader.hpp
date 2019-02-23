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
///   File: FormReader.hpp
///
/// Author: $author$
///   Date: 11/25/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_INET_HTTP_FORMREADER_HPP
#define _XOS_INET_HTTP_FORMREADER_HPP

#include "xos/inet/http/UrlEncodedReader.hpp"
#include "xos/base/String.hpp"
#include "xos/os/Logger.hpp"

namespace xos {
namespace http {

typedef InterfaceBase FormReaderImplement;
typedef Base FormReaderExtend;
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS FormReader
: virtual public FormReaderImplement, public FormReaderExtend {
public:
    typedef FormReaderImplement Implements;
    typedef FormReaderExtend Extends;

    typedef InterfaceBase ObserverImplement;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    class _EXPORT_CLASS Observer: virtual public ObserverImplement {
    public:
        typedef ObserverImplement Implements;
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        virtual ~Observer() {
        }
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        virtual void OnRead(const String& name,const String& value) {            
            XOS_LOG_TRACE("name = \"" << name << "\", value = \"" << value << "\"");
        }
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
    };
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    FormReader() {
    }
    virtual ~FormReader() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

typedef FormReaderImplement UrlEncodedFormReaderImplement;
typedef FormReader UrlEncodedFormReaderExtend;
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS UrlEncodedFormReader
: virtual public UrlEncodedFormReaderImplement, public UrlEncodedFormReaderExtend {
public:
    typedef UrlEncodedFormReaderImplement Implements;
    typedef UrlEncodedFormReaderExtend Extends;
    typedef CharStream Reader;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    UrlEncodedFormReader(Reader& reader, Observer& observer) {
        Read(reader, observer);
    }
    UrlEncodedFormReader() {
    }
    virtual ~UrlEncodedFormReader() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void Read(Reader& reader, Observer& observer) {
        UrlEncodedReader urlReader(reader);
        String name;
        String value;
        String* text = &name;
        char c;
        while (0 < (urlReader.Read(&c, 1))) {
            switch(c) {
            case '=':
                text = &value;
                break;
            case '&':
                if ((name.length())) {
                    XOS_LOG_TRACE("observer.OnRead(name = \"" << name << "\", value = \"" << value << "\")");
                    observer.OnRead(name, value);
                }
                name.clear();
                value.clear();
                text = &name;
                break;
            default:
                text->append(&c, 1);
            }
        }
        if ((name.length()) && (&value == text)) {
            XOS_LOG_TRACE("observer.OnRead(name = \"" << name << "\", value = \"" << value << "\")");
            observer.OnRead(name, value);
        }
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace http
} // namespace xos 

#endif // _XOS_INET_HTTP_FORMREADER_HPP 
