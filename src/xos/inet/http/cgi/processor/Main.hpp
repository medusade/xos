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
///   File: Main.hpp
///
/// Author: $author$
///   Date: 4/3/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_INET_HTTP_CGI_PROCESSOR_MAIN_HPP
#define _XOS_INET_HTTP_CGI_PROCESSOR_MAIN_HPP

#include "xos/inet/http/cgi/Main.hpp"
#include "xos/inet/http/server/Processor.hpp"
#include "xos/inet/http/FormReader.hpp"
#include "xos/base/StringReader.hpp"

namespace xos {
namespace http {
namespace cgi {
namespace processor {

typedef cgi::MainImplement MainImplement;
typedef cgi::Main MainExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Main
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Main: virtual public MainImplement, public MainExtend {
public:
    typedef MainImplement Implements;
    typedef MainExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Main() {
    }
    virtual ~Main() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int RunCgi(int argc, char** argv, char** env) {
        http::server::Processor& processor = http::server::Processor::GetTheInstance();
        int err = 0;

        GetContext(m_request, m_env);
        GetQueryFormData(m_request, m_env);
        GetMethodFormData(m_request, m_env);

        if ((processor.Process(m_response, m_request))) {
            OutContentHeaders(m_response);
            OutContent(m_response);
        }
        OutContentFlush();
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool OutContentHeaders(Response& response) {
        Headers::const_iterator b = m_response.headers().begin();
        Headers::const_iterator e = m_response.headers().end();
        for (Headers::const_iterator i = b; i != e; ++i) {
            const Header& h = *i;
            const String& name = h.name();
            const String& value = h.value();

            XOS_LOG_TRACE("header \"" << name << "\" = \"" << value << "\"");

            switch (Headers::WhichOf(h)) {
            case Headers::ContentType:
                if ((value.Length())) {
                    XOS_LOG_TRACE("content type = \"" << value << "\"");
                    m_contentType = value;
                }
                break;
            case Headers::ContentLength:
                if ((value.Length())) {
                    int length;
                    if (0 < (length = value.ToInt())) {
                        XOS_LOG_TRACE("content length = " << length << "");
                        m_contentLength = length;
                    }
                }
                break;
            case Headers::ContentEncoding:
                if ((value.Length())) {
                    XOS_LOG_TRACE("content encoding = \"" << value << "\"");
                }
                break;
            }
        }
        if (0 < (Extends::OutContentHeaders()))
            return true;
        return false;
    }
    virtual bool OutContent(Response& response) {
        const char* chars;
        ssize_t length;
        if ((chars = response.message().Chars())
            && (0 < (length = response.message().Length()))) {
            if (0 < (Extends::OutContent(chars, length)))
                return true;
        }
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool GetContext(Request& request, const Environment& env) {
        GetPathTranslated(request, env);
        return true;
    }
    virtual bool GetPathTranslated(Request& request, const Environment& env) {
        const Environment::Variable& variable = env[Environment::Variable::PATH_TRANSLATED];
        const Environment::Variable::Value& value = variable.value();
        const char* chars;
        ssize_t length;
        if ((chars = value.wrapped()) && (0 < (length = value.Length()))) {
            const String path(chars, length);

            XOS_LOG_TRACE("path translated = \"" << path << "\"");
            request.SetPathTranslated(path);
            return true;
        }
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool GetMethodFormData(Request& request, const Environment& env) {
        const Environment::Variable& variable = env[Environment::Variable::REQUEST_METHOD];
        const Environment::Variable::Value& value = variable.value();
        const char* chars;
        ssize_t length;
        if ((chars = value.wrapped()) && (0 < (length = value.Length()))) {
            const String method(chars, length);

            XOS_LOG_TRACE("method = \"" << method << "\"");
            request.SetMethod(method);

            switch(Request::Method::WhichOf(method.Chars())) {
            case Request::Method::POST:
                return GetContentFormData(request, env);
            }
        }
        return false;
    }
    virtual bool GetContentFormData(Request& request, const Environment& env) {
        const Environment::Variable& variable = env[Environment::Variable::CONTENT_TYPE];
        const Environment::Variable::Value& value = variable.value();
        const char* chars;
        ssize_t length;
        if ((chars = value.wrapped()) && (0 < (length = value.Length()))) {
            const Content::Type type(chars, length);

            XOS_LOG_TRACE("content type = \"" << type << "\"");
            request.SetContentType(type);

            switch(type.ToWhich()) {
            case Content::Type::UrlEncodedFormData:
                return GetUrlEncodedFormData(request, env);

            case Content::Type::MultipartFormData:
                return GetMultipartFormData(request, env);
            }
        }
        return false;
    }
    virtual bool GetUrlEncodedFormData(Request& request, const Environment& env) {
        const Environment::Variable& variable = env[Environment::Variable::CONTENT_LENGTH];
        const Environment::Variable::Value& value = variable.value();
        const char* chars;
        ssize_t length;
        if ((chars = value.wrapped()) && (0 < (length = value.Length()))) {
            const String s(chars, length);
            length = s.ToInt();
        } else {
            length = 0;
        }
        if ((length)) {
            http::Content::Reader reader(m_inContent, length);
            XOS_LOG_TRACE("reading form from content...");
            return GetUrlEncodedFormData(request, reader);
        }
        return false;
    }
    virtual bool GetMultipartFormData(Request& request, const Environment& env) {
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool GetQueryFormData(Request& request, const Environment& env) {
        const Environment::Variable& variable = env[Environment::Variable::QUERY_STRING];
        const Environment::Variable::Value& value = variable.value();
        const char* chars;
        ssize_t length;
        if ((chars = value.wrapped()) && (0 < (length = value.Length()))) {
            const String query(chars, length);

            XOS_LOG_TRACE("query = \"" << query << "\"");
            request.SetQuery(query);
            return GetQueryFormData(request);
        }
        return false;
    }
    virtual bool GetQueryFormData(Request& request) {
        const String& query = request.GetQuery();
        if (0 < (query.Length())) {
            StringReader reader(query);
            XOS_LOG_TRACE("reading form from query...");
            return GetUrlEncodedFormData(request, reader);
        }
        return false;
    }
    virtual bool GetUrlEncodedFormData(Request& request, CharReader& reader) {
        Form& form = request.form();
        UrlEncodedFormReader uReader;
        uReader.Read(reader, form);
        return true;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    Request m_request;
    Response m_response;
};

} // namespace processor 
} // namespace cgi 
} // namespace http 
} // namespace xos 

#endif // _XOS_INET_HTTP_CGI_PROCESSOR_MAIN_HPP 
