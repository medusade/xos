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
///   Date: 4/8/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_INET_HTTP_CGI_ECHO_MAIN_HPP
#define _XOS_INET_HTTP_CGI_ECHO_MAIN_HPP

#include "xos/inet/http/cgi/Main.hpp"

namespace xos {
namespace http {
namespace cgi {
namespace echo {

typedef cgi::MainImplement MainImplement;
typedef cgi::Main MainExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Main
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Main: virtual public MainImplement, public MainExtend {
public:
    typedef MainImplement Implements;
    typedef MainExtend Extends;

    typedef FormReader::Observer FormReaderObserverExtend;
    ///////////////////////////////////////////////////////////////////////
    ///  Class: FormReaderObserver
    ///////////////////////////////////////////////////////////////////////
    class _EXPORT_CLASS FormReaderObserver: public FormReaderObserverExtend {
    public:
        typedef FormReaderObserverExtend Extends;
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        FormReaderObserver(cgi::Main& cgi): m_cgi(cgi) {
        }
        virtual ~FormReaderObserver() {
        }
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        virtual void OnRead(const String& name,const String& value) {
            XOS_LOG_TRACE("name = \"" << name << "\", value = \"" << value << "\"");
            m_cgi.OutContentFormatted("form[\"%s\"] = \"%s\"\n", name.Chars(), value.Chars());
        }
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
    protected:
        cgi::Main& m_cgi;
    };

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Main() {
    }
    virtual ~Main() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int RunCgi(int argc, char** argv, char** env) {
        int err = 0;
        for (int arg = 0; arg < argc; ++arg) {
            OutContentFormatted("argv[%d] = \"%s\"\n", arg, argv[arg]);
        }
        OutContentFormatted("\n\n");

        for (Environment::Variable::Which e = Environment::Variable::First;
             e <= Environment::Variable::Last; ++e) {
            const char* name = m_env[e].name().wrapped();
            const char* value = m_env[e].value().wrapped();
            if ((name) && (value)) {
                OutContentFormatted("env[%s] = \"%s\"\n", name, value);
            }
        }
        OutContentFormatted("\n\n");

        if ((GetQueryFormData(m_env)))
            OutContentFormatted("\n\n");

        if ((GetMethodFormData(m_env)))
            OutContentFormatted("\n\n");

        OutContentFlush();
        return err;
    }
    virtual bool GetUrlEncodedFormData(UrlEncodedReader& reader) {
        FormReaderObserver observer(*this);
        UrlEncodedFormReader form(reader, observer);
        return true;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace echo 
} // namespace cgi 
} // namespace http 
} // namespace xos 

#endif // _XOS_INET_HTTP_CGI_ECHO_MAIN_HPP 
