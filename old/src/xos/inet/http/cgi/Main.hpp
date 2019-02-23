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
///   Date: 3/5/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_INET_HTTP_CGI_MAIN_HPP
#define _XOS_INET_HTTP_CGI_MAIN_HPP

#include "xos/inet/http/cgi/Content.hpp"
#include "xos/inet/http/cgi/Environment.hpp"
#include "xos/inet/http/cgi/Arguments.hpp"
#include "xos/inet/http/cgi/Catch.hpp"
#include "xos/inet/http/Request.hpp"
#include "xos/inet/http/Header.hpp"
#include "xos/inet/http/Content.hpp"
#include "xos/inet/http/FormReader.hpp"
#include "xos/os/Main.hpp"
#include "xos/os/os/Mutex.cpp"
#include "xos/base/StringReader.hpp"
#include "xos/base/FormattedStream.hpp"
#include "xos/base/StreamStream.hpp"

#define XOS_HTTP_CGI_CONTENT_TYPE_NAME \
    XOS_HTTP_CONTENT_TYPE_NAME_TEXT

#define XOS_HTTP_CGI_MAIN_ENV_FILENAME \
    XOS_HTTP_CGI_CATCH_ENV_FILENAME

#define XOS_HTTP_CGI_MAIN_ARGV_FILENAME \
    XOS_HTTP_CGI_CATCH_ARGV_FILENAME

#define XOS_HTTP_CGI_MAIN_STDIN_FILENAME \
    XOS_HTTP_CGI_CATCH_STDIN_FILENAME

namespace xos {
namespace http {
namespace cgi {

typedef xos::Main MainExtend;
///////////////////////////////////////////////////////////////////////
///  Class: MainImplement
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS MainImplement
: virtual public FormattedStream,
  virtual public xos::MainImplement {
public:
};
///////////////////////////////////////////////////////////////////////
///  Class: Main
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Main: virtual public MainImplement, public MainExtend {
public:
    typedef MainImplement Implements;
    typedef MainExtend Extends;
    typedef cgi::Arguments Arguments;
    typedef cgi::Environment Environment;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Main()
    : m_envFileName(XOS_HTTP_CGI_MAIN_ENV_FILENAME),
      m_argvFileName(XOS_HTTP_CGI_MAIN_ARGV_FILENAME),
      m_stdinFileName(XOS_HTTP_CGI_MAIN_STDIN_FILENAME),
      m_outContentHeaders(false),
      m_outContentLength(-1),
      m_outContentType(0),
      m_inContentLength(-1),
      m_inContentType(0),
      m_contentLength(-1),
      m_contentType(XOS_HTTP_CGI_CONTENT_TYPE_NAME),
      m_envReader(m_env),
      m_argReader(m_arg),
      m_mainArgReader(m_mainArg) {
    }
    virtual ~Main() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int RunCgi(int argc, char** argv, char** env) {
        int err = 0;
        OutContentFlush();
        return err;
    }
    virtual int BeforeRunCgi(int argc, char** argv, char** env) {
        int err = 0;
        return err;
    }
    virtual int AfterRunCgi(int argc, char** argv, char** env) {
        int err = 0;
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int CgiRun(int argc, char** argv, char** env) {
        int err = 0;
        if (!(err = BeforeRunCgi(argc, argv, env))) {
            int err2;
            err = RunCgi(argc, argv, env);
            if ((err2 = AfterRunCgi(argc, argv, env)) && (!err))
                err = err2;
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int CgiMain(int argc, char** argv, char** env) {
        int err = 0;
        m_env.Get();
        m_arg.Get(argc, argv, env);
        SetStdInIsBinary();
        m_inContent.Attach(StdIn());
        err = CgiRun(argc, argv, env);
        return err;
    }
    virtual int ConsoleMain(int argc, char** argv, char** env) {
        int err = 0;
        FILE* inFile;
        char c;
        m_envReader.Read(m_envFileName);
        if ((inFile = m_stdinFile.OpenAttached(m_stdinFileName.Chars(), XOS_FILE_MODE_READ_BINARY))) {
            m_inContent.Attach(inFile);
            // skip first line containing content length
            while (0 < (fread(&c, 1,1, inFile))) {
                if ('\n' == c)
                    break;
            }
        }
        err = CgiRun(argc, argv, env);
        if ((inFile)) {
            m_inContent.Detach();
            m_stdinFile.Close();
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int Run(int argc, char** argv, char** env) {
        int err = 0;
        Environment::Variable::Value e;
        if (0 < (e.Get(Environment::Variable::GATEWAY_INTERFACE).Length())) {
            XOS_LOG_TRACE("running as CGI");
            err = CgiMain(argc, argv, env);
        }
        else {
            XOS_LOG_TRACE("running on console");
            err = ConsoleMain(argc, argv, env);
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
   virtual int operator()(int argc, char** argv, char** env) {
        xos::os::Mutex locker;
        xos::StreamStream loggerStream(*this, &locker, true);
        xos::Main::Logger logger(&loggerStream);

        XOS_SET_LOGGING_LEVELS_TO_DEFAULT_LOGGING_LEVELS_ID();

        if (0 < (m_argReader.NameValueRead(m_argvFileName))) {
            int ac = 0; char** av = 0;

            if ((0 < (ac = m_arg.c())) && (0 != (av = m_arg.v()))) {
                m_mainArg.Get(argc, argv, env);
                argc = ac; argv = av;
            }
        }
        return Extends::operator()(argc, argv, env);
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool GetMethodFormData(const Environment& env) {
        const Environment::Variable& variable = env[Environment::Variable::REQUEST_METHOD];
        const Environment::Variable::Value& value = variable.value();
        const char* chars;
        ssize_t length;
        if ((chars = value.wrapped()) && (0 < (length = value.Length()))) {
            const String method(chars, length);

            XOS_LOG_TRACE("method = \"" << method << "\"");

            switch(Request::Method::WhichOf(method.Chars())) {
            case Request::Method::POST:
                return GetContentFormData(env);
            }
        }
        return false;
    }
    virtual bool GetContentFormData(const Environment& env) {
        const Environment::Variable& variable = env[Environment::Variable::CONTENT_TYPE];
        const Environment::Variable::Value& value = variable.value();
        const char* chars;
        ssize_t length;
        if ((chars = value.wrapped()) && (0 < (length = value.Length()))) {
            const Content::Type type(chars, length);

            XOS_LOG_TRACE("content type = \"" << type << "\"");

            switch(type.ToWhich()) {
            case Content::Type::UrlEncodedFormData:
                return GetUrlEncodedFormData(env);

            case Content::Type::MultipartFormData:
                return GetMultipartFormData(env);
            }
        }
        return false;
    }
    virtual bool GetUrlEncodedFormData(const Environment& env) {
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

            return GetUrlEncodedFormData(reader);
        }
        return false;
    }
    virtual bool GetMultipartFormData(const Environment& env) {
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool GetQueryFormData(const Environment& env) {
        const Environment::Variable& variable = env[Environment::Variable::QUERY_STRING];
        const Environment::Variable::Value& value = variable.value();
        const char* chars;
        ssize_t length;
        if ((chars = value.wrapped()) && (0 < (length = value.Length()))) {
            const String query(chars, length);

            XOS_LOG_TRACE("query = \"" << query << "\"");

            return GetQueryFormData(query);
        }
        return false;
    }
    virtual bool GetQueryFormData(const String& query) {
        if (0 < (query.Length())) {
            StringReader reader(query);

            XOS_LOG_TRACE("reading form from query...");

            return GetUrlEncodedFormData(reader);
        }
        return false;
    }
    virtual bool GetUrlEncodedFormData(CharReader& reader) {
        UrlEncodedReader uReader(reader);
        return GetUrlEncodedFormData(uReader);
    }
    virtual bool GetUrlEncodedFormData(UrlEncodedReader& reader) {
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OutContentFormatted(const char* format, ...) {
        ssize_t count = 0;
        va_list va;
        va_start(va, format);
        count = OutContentFormattedV(format, va);
        va_end(va);
        return count;
    }
    virtual ssize_t OutContentFormattedV(const char* format, va_list va) {
        ssize_t count = 0;
        ssize_t count2;
        if (0 > (count = OutContentHeaders()))
            return count;
        if (0 > (count2 = Extends::OutFormattedV(format, va)))
            return count2;
        count += count2;
        return count;
    }
    virtual ssize_t OutContentL(const char* what, ...) {
        ssize_t count = 0;
        va_list va;
        va_start(va, what);
        count = OutContentV(what, va);
        va_end(va);
        return count;
    }
    virtual ssize_t OutContentV(const char* what, va_list va) {
        ssize_t count = 0;
        ssize_t length = 0;
        for (count = 0; what; count += length) {
            if (0 > (length = OutContent(what)))
                return count;
            what = va_arg(va, const char*);
        }
        return count;
    }
    virtual ssize_t OutContent(const char* chars, ssize_t length = -1) {
        ssize_t count = 0;
        ssize_t count2;
        if (0 > (count = OutContentHeaders()))
            return count;
        if (0 > (count2 = Extends::Out(chars, length)))
            return count2;
        count += count2;
        return count;
    }
    virtual ssize_t OutContentFlush() {
        ssize_t count = OutContentHeaders();
        ssize_t count2;
        if (0 > (count2 = Extends::OutFlush()))
            return count2;
        count += count2;
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OutContentHeaders() {
        ssize_t count = 0;
        if (!(m_outContentHeaders)) {
            if (0 > (count = OutContentType()))
                return count;
            if (0 > (count = OutContentLength()))
                return count;
            m_outContentHeaders = true;
        }
        return count;
    }
    virtual ssize_t OutContentType(const char* chars = 0, ssize_t length =- 1) {
        ssize_t count = 0;
        if (!(m_outContentHeaders) && !(m_outContentType)) {
            if (!(chars)) {
                chars = m_contentType.Chars();
                length = m_contentType.Length();
            }
            if ((chars) && (length)) {
                if (count = Extends::OutL
                    (XOS_HTTP_HEADER_NAME_CONTENT_TYPE,
                     XOS_HTTP_HEADER_NAME_VALUE_SEPARATOR,
                     chars, XOS_HTTP_HEADER_END,
                     XOS_HTTP_HEADER_END, (const char*)(0))) {
                    m_outContentType = chars;
                }
            }
        }
        return count;
    }
    virtual ssize_t OutContentLength(int contentLength =- 1) {
        ssize_t count = 0;
        if (!(m_outContentHeaders) && (0 > (m_outContentLength))) {
            if (0 > (contentLength)) {
                contentLength = m_contentLength;
            }
            if (0 <= (contentLength)) {
                String s(contentLength);
                ssize_t length = s.Length();
                const char* chars = s.Chars();

                if ((chars) && (length)) {
                    if (count = Extends::OutL
                        (XOS_HTTP_HEADER_NAME_CONTENT_LENGTH,
                         XOS_HTTP_HEADER_NAME_VALUE_SEPARATOR,
                         chars, XOS_HTTP_HEADER_END,
                         XOS_HTTP_HEADER_END, (const char*)(0))) {
                        m_outContentLength = contentLength;
                    }
                }
            }
        }
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const char* SetContentType(const String& to) {
        return SetContentType(to.Chars());
    }
    virtual const char* SetContentType(const char* to) {
        if ((to)) {
            if ((to[0])) {
                m_contentType.Assign(to);
                return m_contentType.Chars();
            }
        }
        return 0;
    }
    virtual const char* GetContentType() const {
        return m_contentType.Chars();
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OutFormattedV(const char* format, va_list va) {
        ssize_t count = 0;
        OutContentHeaders();
        count = Extends::OutFormattedV(format, va);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Write(const char* what, ssize_t length = -1) {
        return OutContent((const char*)(what), length);
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    String m_envFileName;
    String m_argvFileName;
    String m_stdinFileName;
    FileOpened m_stdinFile;
    bool m_outContentHeaders;
    int m_outContentLength;
    const char* m_outContentType;
    int m_inContentLength;
    const char* m_inContentType;
    Content m_inContent;
    int m_contentLength;
    String m_contentType;
    Environment m_env;
    Environment::Reader m_envReader;
    Arguments m_arg;
    Arguments::Reader m_argReader;
    Arguments m_mainArg;
    Arguments::Reader m_mainArgReader;
};

} // namespace cgi 
} // namespace http 
} // namespace xos 

#endif // _XOS_INET_HTTP_CGI_MAIN_HPP 
