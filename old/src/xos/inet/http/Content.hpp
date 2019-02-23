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
///   Date: 3/9/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_HTTP_CONTENT_HPP
#define _XOS_HTTP_CONTENT_HPP

#include "xos/inet/http/Header.hpp"
#include "xos/base/Reader.hpp"
#include "xos/base/Types.hpp"

#define XOS_HTTP_CONTENT_TYPE_NAME XOS_HTTP_HEADER_NAME_CONTENT_TYPE
#define XOS_HTTP_CONTENT_LENGTH_NAME XOS_HTTP_HEADER_NAME_CONTENT_LENGTH
#define XOS_HTTP_CONTENT_ENCODING_NAME XOS_HTTP_HEADER_NAME_CONTENT_ENCODING

#define XOS_HTTP_CONTENT_TYPE_PARAMETER_SEPARATOR_CHAR ';'

#define XOS_HTTP_CONTENT_TYPE_NAME_TEXT "text/plain"
#define XOS_HTTP_CONTENT_TYPE_NAME_HTML "text/html"
#define XOS_HTTP_CONTENT_TYPE_NAME_XML "text/xml"
#define XOS_HTTP_CONTENT_TYPE_NAME_URLENCODED_FORM_DATA "application/x-www-form-urlencoded"
#define XOS_HTTP_CONTENT_TYPE_NAME_MULTIPART_FORM_DATA "multipart/form-data"
#define XOS_HTTP_CONTENT_TYPE_NAME_UNKNOWN "application/octet-stream"

#define XOS_HTTP_CONTENT_TYPE_NAMES \
    XOS_HTTP_CONTENT_TYPE_NAME_TEXT, \
    XOS_HTTP_CONTENT_TYPE_NAME_HTML, \
    XOS_HTTP_CONTENT_TYPE_NAME_XML, \
    XOS_HTTP_CONTENT_TYPE_NAME_URLENCODED_FORM_DATA, \
    XOS_HTTP_CONTENT_TYPE_NAME_MULTIPART_FORM_DATA

namespace xos {
namespace http {

typedef InterfaceBase ContentImplement;
typedef ExportBase ContentExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Content
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Content: virtual public ContentImplement, public ContentExtend {
public:
    typedef ContentImplement Implements;
    typedef ContentExtend Extends;

    typedef StringImplement TypeImplement;
    typedef String TypeExtend;
    ///////////////////////////////////////////////////////////////////////
    ///  Class: Type
    ///////////////////////////////////////////////////////////////////////
    class _EXPORT_CLASS Type: virtual public TypeImplement, public TypeExtend {
    public:
        typedef TypeImplement Implements;
        typedef TypeExtend Extends;

        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        typedef int Which;
        enum {
            None = 0,
            Text, Html, Xml,
            UrlEncodedFormData, MultipartFormData,
            Next, First = (None + 1), Last = (Next - 1),
            Count = ((Last - First) + 1)
        };

        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        Type(const char* chars, ssize_t length = -1) {
            Parse(chars, length);
        }
        Type(const String& value) {
            Parse(value);
        }
        Type(const Type& copy): Extends(copy) {
        }
        Type() {
        }
        virtual ~Type() {
        }
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        virtual Type& Parse(const String& value) {
            Parse(value.Chars(), value.Length());
            return *this;
        }
        virtual Type& Parse(const char* chars, ssize_t length = -1) {
            Extends::Assign(chars, length);
            if ((chars)) {
                const char* separator;
                if ((separator = xos::Chars::Find
                     (chars, XOS_HTTP_CONTENT_TYPE_PARAMETER_SEPARATOR_CHAR, length))) {
                    if (0 < (length = (separator - chars)))
                        Extends::Assign(chars, length);
                    else Extends::Clear();
                }
            }
            return *this;
        }
        virtual Which ToWhich() const {
            return WhichOf(Chars());
        }
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        static const char* OfWhich(Which which) {
            static const char* of[Count] = {
                XOS_HTTP_CONTENT_TYPE_NAMES
            };
            if ((which >= First) && (which <= Last))
                return of[which - First];
            return 0;
        }
        static Which WhichOf(const char* of) {
            if ((of)) {
                const char* toOf;
                for (Which which = First; which <= Last; ++which) {
                    if ((toOf = OfWhich(which))) {
                        if (!(xos::Chars::CompareCase(of, toOf)))
                            return which;
                    }
                }
            }
            return None;
        }
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
    };

    typedef CharReader ReaderImplement;
    typedef ExportBase ReaderExtend;
    ///////////////////////////////////////////////////////////////////////
    ///  Class: Reader
    ///////////////////////////////////////////////////////////////////////
    class _EXPORT_CLASS Reader: virtual public ReaderImplement, public ReaderExtend {
    public:
        typedef ReaderImplement Implements;
        typedef ReaderExtend Extends;
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        Reader(xos::Reader& reader, ssize_t length)
        : m_reader(reader), m_length(length), m_tell(0) {
        }
        virtual ~Reader() {
        }
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        virtual ssize_t Read(WhatT* what, size_t size) {
            ssize_t count = -1;
            if (0 <= (m_length)) {
                if (m_length < (m_tell + size))
                    size = m_length - m_tell;
            }
            if (0 < (count = size)) {
                if (0 < (count = m_reader.Read(what, size)))
                    m_tell += (count);
            }
            return count;
        }
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
    protected:
        xos::Reader& m_reader;
        ssize_t m_length;
        size_t m_tell;
    };

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Content() {
    }
    virtual ~Content() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace http
} // namespace xos 

#endif // _XOS_HTTP_CONTENT_HPP 
