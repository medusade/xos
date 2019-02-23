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
///   File: Request.hpp
///
/// Author: $author$
///   Date: 11/23/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_HTTP_REQUEST_HPP
#define _XOS_HTTP_REQUEST_HPP

#include "xos/inet/http/Version.hpp"
#include "xos/inet/http/Header.hpp"
#include "xos/inet/http/Message.hpp"
#include "xos/inet/http/Form.hpp"
#include "xos/base/Named.hpp"
#include "xos/base/Types.hpp"

#define XOS_HTTP_STATUS_OK_NO 200
#define XOS_HTTP_STATUS_OK XOS_STRING(XOS_HTTP_STATUS_OK_NO)
#define XOS_HTTP_STATUS_OK_REASON "OK"

#define XOS_HTTP_STATUS_BAD_REQUEST_NO 400
#define XOS_HTTP_STATUS_BAD_REQUEST XOS_STRING(XOS_HTTP_STATUS_BAD_REQUEST_NO)
#define XOS_HTTP_STATUS_BAD_REQUEST_REASON "Bad Request"

#define XOS_HTTP_STATUS_NOT_FOUND_NO 404
#define XOS_HTTP_STATUS_NOT_FOUND XOS_STRING(XOS_HTTP_STATUS_NOT_FOUND_NO)
#define XOS_HTTP_STATUS_NOT_FOUND_REASON "Not Found"

#define XOS_HTTP_URI_QUERY_SEPARATOR "?"
#define XOS_HTTP_URI_FRAGMENT_SEPARATOR "#"

#define XOS_HTTP_REQUEST_METHOD_NAME_GET "GET"
#define XOS_HTTP_REQUEST_METHOD_NAME_POST "POST"
#define XOS_HTTP_REQUEST_METHOD_NAME_PUT "PUT"
#define XOS_HTTP_REQUEST_METHOD_NAME_DELETE "DELETE"
#define XOS_HTTP_REQUEST_METHOD_NAME_TRACE "TRACE"
#define XOS_HTTP_REQUEST_METHOD_NAME_CONNECT "CONNECT"
#define XOS_HTTP_REQUEST_METHOD_NAME_OPTIONS "OPTIONS"
#define XOS_HTTP_REQUEST_METHOD_NAME_HEAD "HEAD"

#define XOS_HTTP_REQUEST_METHOD_NAMES \
    XOS_HTTP_REQUEST_METHOD_NAME_GET, \
    XOS_HTTP_REQUEST_METHOD_NAME_POST, \
    XOS_HTTP_REQUEST_METHOD_NAME_PUT, \
    XOS_HTTP_REQUEST_METHOD_NAME_DELETE, \
    XOS_HTTP_REQUEST_METHOD_NAME_TRACE, \
    XOS_HTTP_REQUEST_METHOD_NAME_CONNECT, \
    XOS_HTTP_REQUEST_METHOD_NAME_OPTIONS

namespace xos {
namespace http {

typedef InterfaceBase RequestImplement;
typedef Base RequestExtend;
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Request: virtual public RequestImplement, public RequestExtend {
public:
    typedef RequestImplement Implements;
    typedef RequestExtend Extends;

    typedef String::Implements MethodImplement;
    typedef String MethodExtend;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    class _EXPORT_CLASS Method: virtual public MethodImplement, public MethodExtend {
    public:
        typedef MethodImplement Implements;
        typedef MethodExtend Extends;

        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        typedef int Which;
        enum {
            None = 0,
            GET, POST, PUT, DELETE, TRACE, CONNECT, OPTIONS, HEAD,
            Next, First = (None + 1), Last = (Next - 1),
            Count = ((Last - First) + 1)
        };
        enum {
            none = 0,
            Get, Post, Put, Delete, Trace, Connect, Options, Head,
            next, first = (none + 1), last  = (next - 1),
            count = ((last - first) + 1)
        };

        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        Method(const String& value): Extends(value) {
        }
        Method() {
        }
        virtual ~Method() {
        }
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        virtual Which ToWhich() const {
            return WhichOf(Chars());
        }
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        static const char* OfWhich(Which which) {
            static const char* of[Count] = {
                XOS_HTTP_REQUEST_METHOD_NAMES
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
                        if (!(xos::Chars::Compare(of, toOf)))
                            return which;
                    }
                }
            }
            return None;
        }
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
    };

    typedef String::Implements UriImplement;
    typedef String UriExtend;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    class _EXPORT_CLASS Uri: virtual public UriImplement, public UriExtend {
    public:
        typedef UriImplement Implements;
        typedef UriExtend Extends;
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        Uri(const String& path, const String& query, const String& fragment)
        : m_path(path), m_query(query), m_fragment(fragment) {
            Combine();
        }
        Uri(const String& combined)
        : Extends(combined) {
            Separate();
        }
        Uri(const char* combined, ssize_t length)
        : Extends(combined, length) {
            Separate();
        }
        Uri(const Uri& copy)
        : Extends(copy), m_path(copy.m_path), m_query(copy.m_query), m_fragment(copy.m_fragment) {
        }
        Uri() {
        }
        virtual ~Uri() {
        }
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        virtual const String& Set(const String& to) {
            Assign(to);
            Separate();
            return *this;
        }
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        virtual bool Combine() {
            return false;
        }
        virtual bool Separate() {
            size_t query, fragment;
            m_path.Clear();
            m_query.Clear();
            m_fragment.Clear();
            if ((0 < (query = find(XOS_HTTP_URI_QUERY_SEPARATOR))) && (query < Length())) {
                m_path.Assign(c_str(), query);
                if ((query < (fragment = find(XOS_HTTP_URI_FRAGMENT_SEPARATOR))) && (fragment < Length())) {
                    m_query.Assign(c_str()+query+1, fragment-query);
                    m_fragment.Assign(c_str()+fragment+1);
                } else {
                    m_query.Assign(c_str()+query+1);
                }
            } else {
                if ((0 < (fragment = find(XOS_HTTP_URI_FRAGMENT_SEPARATOR))) && (fragment < Length())) {
                    m_path.Assign(c_str(), fragment);
                    m_fragment.Assign(c_str()+fragment+1);
                } else {
                    m_path.Assign(c_str(), length());
                }
            }
            return true;
        }
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        virtual const String& SetPath(const String& to) {
            m_path = to;
            return m_path;
        }
        virtual const String& GetPath() const {
            return m_path;
        }
        ///////////////////////////////////////////////////////////////////////
        virtual const String& SetQuery(const String& to) {
            m_query = to;
            return m_query;
        }
        virtual const String& GetQuery() const {
            return m_query;
        }
        ///////////////////////////////////////////////////////////////////////
        virtual const String& SetFragment(const String& to) {
            m_fragment = to;
            return m_fragment;
        }
        virtual const String& GetFragment() const {
            return m_fragment;
        }
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
    protected:
        String m_path, m_query, m_fragment;
    };

    typedef String::Implements LineImplement;
    typedef String LineExtend;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    class _EXPORT_CLASS Line: virtual public LineImplement, public LineExtend {
    public:
        typedef LineImplement Implements;
        typedef LineExtend Extends;
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        Line(const Method& method, const Uri& uri, const Version& version)
        : m_method(method), m_uri(uri), m_version(version) {
        }
        Line(const Method& method, const Uri& uri)
        : m_method(method), m_uri(uri) {
        }
        Line() {
        }
        virtual ~Line() {
        }

        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        virtual const String& SetMethod(const String& to) {
            m_method = to;
            return m_method;
        }
        virtual const String& GetMethod() const {
            return m_method;
        }
        virtual Method::Which GetMethodWhich() const {
            return m_method.ToWhich();
        }

        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        virtual const String& SetUri(const String& to) {
            m_uri.Set(to);
            return m_uri;
        }
        virtual const String& GetUri() const {
            return m_uri;
        }
        ///////////////////////////////////////////////////////////////////////
        virtual const String& SetPath(const String& to) {
            m_uri.SetPath(to);
            return m_uri.GetPath();
        }
        virtual const String& GetPath() const {
            return m_uri.GetPath();
        }
        ///////////////////////////////////////////////////////////////////////
        virtual const String& SetQuery(const String& to) {
            m_uri.SetQuery(to);
            return m_uri.GetQuery();
        }
        virtual const String& GetQuery() const {
            return m_uri.GetQuery();
        }
        ///////////////////////////////////////////////////////////////////////
        virtual const String& SetFragment(const String& to) {
            m_uri.SetFragment(to);
            return m_uri.GetFragment();
        }
        virtual const String& GetFragment() const {
            return m_uri.GetFragment();
        }

        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        virtual const Version& SetVersion(const Version& to) {
            m_version.Set(to);
            return m_version;
        }
        virtual const Version& GetVersion() const {
            return m_version;
        }

        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        virtual const String& SetProtocol(const String& to) {
            m_version.SetProtocol(to);
            return m_version.GetProtocol();
        }
        virtual const String& GetProtocol() const {
            return m_version.GetProtocol();
        }
        ///////////////////////////////////////////////////////////////////////
        virtual const String& SetProtocolVersionMajor(const String& to) {
            m_version.SetMajor(to);
            return m_version.GetMajor();
        }
        virtual const String& GetProtocolVersionMajor() const {
            return m_version.GetMajor();
        }
        ///////////////////////////////////////////////////////////////////////
        virtual const String& SetProtocolVersionMinor(const String& to) {
            m_version.SetMinor(to);
            return m_version.GetMinor();
        }
        virtual const String& GetProtocolVersionMinor() const {
            return m_version.GetMinor();
        }

        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
    protected:
        Method m_method;
        Uri m_uri;
        Version m_version;
    };

    typedef InterfaceBase ContextImplement;
    typedef ExportBase ContextExtend;
    ///////////////////////////////////////////////////////////////////////
    ///  Class: Context
    ///////////////////////////////////////////////////////////////////////
    class _EXPORT_CLASS Context: virtual public ContextImplement, public ContextExtend {
    public:
        typedef ContextImplement Implements;
        typedef ContextExtend Extends;
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        Context(const String& pathTranslated): m_pathTranslated(pathTranslated) {
        }
        Context(const Context& copy): m_pathTranslated(copy.m_pathTranslated) {
        }
        Context() {
        }
        virtual ~Context() {
        }
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        virtual const String& SetPathTranslated
        (const String& root, const String& path, char directorySeparator = '/') {
            m_pathTranslated.Assign(root);
            m_pathTranslated.Append(&directorySeparator,1);
            m_pathTranslated.Append(path);
            return m_pathTranslated;
        }
        virtual const String& SetPathTranslated(const String& to) {
            m_pathTranslated.Assign(to);
            return m_pathTranslated;
        }
        virtual const String& GetPathTranslated() const {
            return m_pathTranslated;
        }
        virtual String& pathTranslated() const {
            return (String&)(m_pathTranslated);
        }
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
    protected:
        String m_pathTranslated;
    };

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Request
    (const Line& line, const Headers& headers,
     const Message& message, const Context& context)
    : m_line(line), m_headers(headers), m_message(message), m_context(context) {
    }
    Request(const Line& line, const Headers& headers, const Message& message)
    : m_line(line), m_headers(headers), m_message(message) {
    }
    Request(const Method& method, const Uri& uri, const Version& version)
    : m_line(method, uri, version) {
    }
    Request(const Method& method, const Uri& uri)
    : m_line(method, uri) {
    }
    Request(const Request& copy)
    : m_line(copy.m_line), m_headers(copy.m_headers),
      m_message(copy.m_message), m_context(copy.m_context) {
    }
    Request(CharReader& messageReader): m_message(messageReader) {
    }
    Request() {
    }
    virtual ~Request() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual Line& SetLine(const Line& to) {
        m_line = to;
        return m_line;
    }
    virtual const Line& GetLine() const {
        return m_line;
    }
    virtual Line& line() const {
        return (Line&)(m_line);
    }
    ///////////////////////////////////////////////////////////////////////
    virtual const String& SetMethod(const String& to) {
        m_line.SetMethod(to);
        return m_line.GetMethod();
    }
    virtual const String& GetMethod() const {
        return m_line.GetMethod();
    }
    virtual Method::Which GetMethodWhich() const {
        return m_line.GetMethodWhich();
    }
    ///////////////////////////////////////////////////////////////////////
    virtual const String& SetPath(const String& to) {
        m_line.SetPath(to);
        return m_line.GetPath();
    }
    virtual const String& GetPath() const {
        return m_line.GetPath();
    }
    ///////////////////////////////////////////////////////////////////////
    virtual const String& SetQuery(const String& to) {
        m_line.SetQuery(to);
        return m_line.GetQuery();
    }
    virtual const String& GetQuery() const {
        return m_line.GetQuery();
    }
    ///////////////////////////////////////////////////////////////////////
    virtual const String& SetFragment(const String& to) {
        m_line.SetFragment(to);
        return m_line.GetFragment();
    }
    virtual const String& GetFragment() const {
        return m_line.GetFragment();
    }
    ///////////////////////////////////////////////////////////////////////
    virtual Headers& SetHeaders(const Headers& to) {
        m_headers = to;
        return m_headers;
    }
    virtual const Headers& GetHeaders() const {
        return m_headers;
    }
    virtual Headers& headers() const {
        return (Headers&)(m_headers);
    }
    ///////////////////////////////////////////////////////////////////////
    virtual String SetTransferEncoding(const String& to) {
        return m_headers.SetTransferEncoding(to);
    }
    virtual String GetTransferEncoding() const {
        return m_headers.GetTransferEncoding();
    }
    ///////////////////////////////////////////////////////////////////////
    virtual String SetContentEncoding(const String& to) {
        return m_headers.SetContentEncoding(to);
    }
    virtual String GetContentEncoding() const {
        return m_headers.GetContentEncoding();
    }
    ///////////////////////////////////////////////////////////////////////
    virtual String SetContentType(const String& to) {
        return m_headers.SetContentType(to);
    }
    virtual String GetContentType() const {
        return m_headers.GetContentType();
    }
    ///////////////////////////////////////////////////////////////////////
    virtual String SetContentLength(const String& to) {
        return m_headers.SetContentLength(to);
    }
    virtual String GetContentLength() const {
        return m_headers.GetContentLength();
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int SetContentLengthNo(int toValue) {
        String to(toValue);
        to = SetContentLength(to);
        if ((to.Length()))
            return (to >> toValue);
        return -1;
    }
    virtual int GetContentLengthNo() const {
        String to = GetContentLength();
        int toValue;
        if ((to.Length()))
            return (to >> toValue);
        return -1;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int SetContent(const String& value) {
        int length = -1;
        return length;
    }
    virtual int GetContent(String& value) const {
        int length = -1;
        return length;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual Form& SetForm(const Form& to) {
        m_form = to;
        return m_form;
    }
    virtual const Form& GetForm() const {
        return m_form;
    }
    virtual Form& form() const {
        return (Form&)(m_form);
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const String& SetPathTranslated
    (const String& root, const String& path, char directorySeparator = '/') {
        m_context.pathTranslated().Assign(root);
        m_context.pathTranslated().Append(&directorySeparator,1);
        m_context.pathTranslated().Append(path);
        return m_context.pathTranslated();
    }
    virtual const String& SetPathTranslated(const String& to) {
        m_context.pathTranslated().Assign(to);
        return m_context.pathTranslated();
    }
    virtual const String& GetPathTranslated() const {
        return m_context.pathTranslated();
    }
    virtual String& pathTranslated() const {
        return (String&)(m_context.pathTranslated());
    }
    ///////////////////////////////////////////////////////////////////////
    virtual Context& SetContext(const Context& to) {
        m_context = to;
        return m_context;
    }
    virtual const Context& GetContext() const {
        return m_context;
    }
    virtual Context& context() const {
        return (Context&)(m_context);
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual CharReader& GetMessageReader() const {
        return m_message.GetReader();
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    Line m_line;
    Headers m_headers;
    Message m_message;
    Form m_form;
    Context m_context;
};

} // namespace http 
} // namespace xos 

#endif // _XOS_HTTP_REQUEST_HPP 
