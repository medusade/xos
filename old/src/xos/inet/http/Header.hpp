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
///   File: Header.hpp
///
/// Author: $author$
///   Date: 3/9/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_HTTP_HEADER_HPP
#define _XOS_HTTP_HEADER_HPP

#include "xos/base/Named.hpp"
#include "xos/base/Types.hpp"

#define XOS_HTTP_HEADER_NAME_CONTENT_TYPE "Content-Type"
#define XOS_HTTP_HEADER_NAME_CONTENT_LENGTH "Content-Length"
#define XOS_HTTP_HEADER_NAME_CONTENT_ENCODING "Content-Encoding"

#define XOS_HTTP_HEADER_NAME_TRANSFER_ENCODING "Transfer-Encoding"
#define XOS_HTTP_TRANSFER_ENCODING_CHUNKED_NAME "chunked"

#define XOS_HTTP_HEADER_NAMES \
    XOS_HTTP_HEADER_NAME_CONTENT_TYPE, \
    XOS_HTTP_HEADER_NAME_CONTENT_LENGTH, \
    XOS_HTTP_HEADER_NAME_CONTENT_ENCODING

#define XOS_HTTP_HEADER_NAME_VALUE_SEPARATOR ":"
#define XOS_HTTP_HEADER_END "\r\n"

namespace xos {
namespace http {

typedef Named Header;
typedef NamedVector HeadersExtend;
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Headers: public HeadersExtend {
public:
    typedef HeadersExtend Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    typedef int Which;
    enum {
        None = 0,
        ContentType, ContentLength, ContentEncoding,
        Next, First = (None + 1), Last = (Next - 1),
        Count = (Last - First + 1)
    };

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Headers(const Headers& copy): Extends(copy) {
    }
    Headers() {
    }
    virtual ~Headers() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Combine(String& value) {
        if ((size())) {
            const_iterator b = begin();
            const_iterator e = end();
            for (const_iterator i = b; i != e; ++i) {
                const Header& h = *i;
                value.Append(h.name());
                value.Append(":");
                value.Append(h.value());
                value.Append("\r\n");
            }
        }
        value.Append("\r\n");
        return true;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual bool Separate(const String& value) {
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual String SetContentEncoding(const String& to) {
        String value;
        const Header* h;
        if ((h = Set(XOS_HTTP_HEADER_NAME_CONTENT_ENCODING, to))) {
            value = h->GetValue();
        }
        return value;
    }
    virtual String GetContentEncoding() const {
        String value;
        const Header* h;
        if ((h = Get(XOS_HTTP_HEADER_NAME_CONTENT_ENCODING))) {
            value = h->GetValue();
        }
        return value;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual String SetContentType(const String& to) {
        String value;
        const Header* h;
        if ((h = Set(XOS_HTTP_HEADER_NAME_CONTENT_TYPE, to))) {
            value = h->GetValue();
        }
        return value;
    }
    virtual String GetContentType() const {
        String value;
        const Header* h;
        if ((h = Get(XOS_HTTP_HEADER_NAME_CONTENT_TYPE))) {
            value = h->GetValue();
        }
        return value;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual String SetContentLength(const String& to) {
        String value;
        const Header* h;
        if ((h = Set(XOS_HTTP_HEADER_NAME_CONTENT_LENGTH, to))) {
            value = h->GetValue();
        }
        return value;
    }
    virtual String GetContentLength() const {
        String value;
        const Header* h;
        if ((h = Get(XOS_HTTP_HEADER_NAME_CONTENT_LENGTH))) {
            value = h->GetValue();
        }
        return value;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t SetContentLengthNo(ssize_t to) {
        String value((int)(to));
        const Header* h;
        if ((h = Set(XOS_HTTP_HEADER_NAME_CONTENT_LENGTH, value))) {
            value = h->GetValue();
            to = value.ToInt();
        }
        return to;
    }
    virtual ssize_t GetContentLengthNo() const {
        ssize_t length = -1;
        String value;
        const Header* h;
        if ((h = Get(XOS_HTTP_HEADER_NAME_CONTENT_LENGTH))) {
            value = h->GetValue();
            length = value.ToInt();
        }
        return length;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual String SetTransferEncoding(const String& to) {
        String value;
        const Header* h;
        if ((h = Set(XOS_HTTP_HEADER_NAME_TRANSFER_ENCODING, to))) {
            value = h->GetValue();
        }
        return value;
    }
    virtual String GetTransferEncoding() const {
        String value;
        const Header* h;
        if ((h = Get(XOS_HTTP_HEADER_NAME_TRANSFER_ENCODING))) {
            value = h->GetValue();
        }
        return value;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const Header* Set(const String& name,const String& value) {
        const Header* header = 0;
        if (!(header = Get(name))) {
            push_back(Header(name, value));
            return Get(name);
        } else {
            iterator b = begin();
            iterator e = end();
            iterator i;
            for (i = b; i != e; ++i) {
                Header& h = *i;
                if (!(name.compare(h.GetName()))) {
                    h.SetValue(value);
                    return &h;
                }
            }
        }
        return 0;
    }
    virtual const Header* Get(const String& name) const {
        const_iterator b = begin();
        const_iterator e = end();
        const_iterator i;
        for (i = b; i != e; ++i) {
            const Header& h = *i;
            if (!(name.compare(h.GetName()))) {
                return &h;
            }
        }
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void Add(const String& name, const String& value) {
        push_back(Header(name, value));
    }
    virtual void Add(const Header& header) {
        push_back(header);
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    static Which WhichOf(const Header& of) {
        return WhichOf(of.name());
    }
    static Which WhichOf(const String& of) {
        return WhichOf(of.Chars());
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
    static const char* OfWhich(Which which) {
        static const char* of[Count] = {
            XOS_HTTP_HEADER_NAMES
        };
        if ((which >= First) && (which <= Last))
            return of[which - First];
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace http
} // namespace xos 

#endif // _XOS_HTTP_HEADER_HPP 
