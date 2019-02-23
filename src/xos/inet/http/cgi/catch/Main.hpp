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
///   Date: 3/9/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_INET_HTTP_CGI_CATCH_MAIN_HPP
#define _XOS_INET_HTTP_CGI_CATCH_MAIN_HPP

#include "xos/inet/http/cgi/Main.hpp"
#include "xos/inet/http/cgi/Environment.hpp"
#include "xos/inet/http/cgi/Arguments.hpp"
#include "xos/inet/http/cgi/Catch.hpp"
#include "xos/inet/http/Header.hpp"
#include "xos/inet/http/Content.hpp"
#include "xos/os/File.hpp"
#include "xos/os/Main.hpp"

namespace xos {
namespace http {
namespace cgi {
namespace Catch {

typedef cgi::MainImplement MainImplement;
typedef cgi::Main MainExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Main
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Main: virtual public MainImplement, public MainExtend {
public:
    typedef MainImplement Implements;
    typedef MainExtend Extends;
    using Extends::OutContent;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Main()
    : m_envFilePattern(XOS_HTTP_CGI_CATCH_ENV_FILE_PATTERN),
      m_argvFilePattern(XOS_HTTP_CGI_CATCH_ARGV_FILE_PATTERN),
      m_stdinFilePattern(XOS_HTTP_CGI_CATCH_STDIN_FILE_PATTERN) {
    }
    virtual ~Main() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void OutContent() {
        int argc = m_arg.c();
        char** argv = m_arg.v();
        const char* name;
        const char* value;

        OutContentL("Arguments: (file = \"", m_argvFileName.Chars(), "\")\n\n", (const char*)(0));
        for (int a = 0; a < argc; ++a) {
            String arg(a);
            OutContentL("argv[", arg.Chars(), "] = \"", argv[a], "\"\n", (const char*)(0));
        }
        OutContent("\n");

        OutContentL("Environment: (file = \"", m_envFileName.Chars(), "\")\n\n", (const char*)(0));
        for (Environment::Variable::Which which = Environment::Variable::First;
             which <= Environment::Variable::Last; ++which) {
            Environment::Variable& v = m_env[which];
            if ((name = v.name()) && (value = v.value())) {
                OutContentL("\"", name, "\" = \"", value, "\"\n", (const char*)(0));
            }
        }
        OutContent("\n");

        OutContentL("Input: (file = \"", m_stdinFileName.Chars(), "\")\n\n", (const char*)(0));
        OutContent("\n");

        OutContentFlush();
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int RunCgi(int argc, char** argv, char** env) {
        int err = 0;
        const char* r = XOS_FILE_MODE_READ_BINARY;
        const char* w = XOS_FILE_MODE_WRITE_BINARY;
        const char* name;
        const char* value;
        CharFileBase f;

        //
        // write arguments to file
        //
        if ((f.OpenSafe(m_argvFilePattern.Chars(), m_argvFileName.Chars(), w))) {
            int argc = m_arg.c();
            char** argv = m_arg.v();
            for (int a = 0; a < argc; ++a) {
                String arg(a);
                if (1 > (f.WriteL("argv[", arg.Chars(), "]=", argv[a], "\r\n", (const char*)(0))))
                    break;
            }
            f.Close();
        }

        //
        // write environment to file
        //
        if ((f.OpenSafe(m_envFilePattern.Chars(), m_envFileName.Chars(), w))) {
            const char* name;
            const char* value;
            for (Environment::Variable::Which which = Environment::Variable::First;
                 which <= Environment::Variable::Last; ++which) {
                Environment::Variable& v = m_env[which];
                if ((name = v.name()) && (value = v.value())) {
                    if (1 > (f.WriteL(name, "=", value, "\r\n", (const char*)(0))))
                        break;
                }
            }
            f.Close();
        }

        //
        // write input to file
        //
        if ((name = (m_env[Environment::Variable::CONTENT_LENGTH].name()))) {
            String contentLengthValue("-1");

            if ((value = (m_env[Environment::Variable::CONTENT_LENGTH].value()))) {
                if ((value[0]))
                    contentLengthValue.Assign(value);
                else value = contentLengthValue.Chars();
            }
            else value = contentLengthValue.Chars();

            if ((f.OpenSafe(m_stdinFilePattern.Chars(), m_stdinFileName.Chars(), w))) {
                if (0 < (f.WriteL(name, "=", value, "\r\n", (const char*)(0)))) {
                    ssize_t contentLength;

                    if ((contentLength = contentLengthValue.ToInt())) {
                        ssize_t n;
                        char c[1];
                        if (0 <= (contentLength)) {
                            for (ssize_t count = 0; count < contentLength; ++count) {
                                if (0 >= (n = In(c, 1)))
                                    break;
                                if (0 >= (f.Write(c, 1)))
                                    break;
                            }
                        }
                    }
                }
                f.Close();
            }
        }

        OutContent();
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int ConsoleMain(int argc, char** argv, char** env) {
        int err = 0;
        m_envReader.Read(m_envFileName);
        m_argReader.NameValueRead(m_argvFileName);
        OutContent();
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int operator()(int argc, char** argv, char** env) {
        xos::os::Mutex locker;
        xos::StreamStream loggerStream(*this, &locker, true);
        xos::Main::Logger logger(&loggerStream);
        XOS_SET_LOGGING_LEVELS_TO_DEFAULT_LOGGING_LEVELS_ID();
        return Extends::Extends::operator()(argc, argv, env);
     }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    String m_envFilePattern;
    String m_argvFilePattern;
    String m_stdinFilePattern;
};

} // namespace Catch
} // namespace cgi 
} // namespace http 
} // namespace xos 

#endif // _XOS_INET_HTTP_CGI_CATCH_MAIN_HPP 
        

