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
///   File: Daemon.hpp
///
/// Author: $author$
///   Date: 11/23/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_HTTP_SERVER_DAEMON_HPP
#define _XOS_HTTP_SERVER_DAEMON_HPP

#include "xos/os/server/Daemon.hpp"
#include "xos/inet/http/server/Processor.hpp"
#include "xos/inet/http/FormReader.hpp"
#include "xos/base/StringReader.hpp"

#define XOS_HTTP_SERVER_DAEMON_NUM_THREADSNO 1
#define XOS_HTTP_SERVER_DAEMON_NUM_THREADS XOS_STRING(XOS_HTTP_SERVER_DAEMON_NUM_THREADSNO)
#define XOS_HTTP_SERVER_DAEMON_LISTEN_PORTNO 8080
#define XOS_HTTP_SERVER_DAEMON_LISTEN_PORT XOS_STRING(XOS_HTTP_SERVER_DAEMON_LISTEN_PORTNO)
#define XOS_HTTP_SERVER_DAEMON_LISTEN_HOST "localhost"
#define XOS_HTTP_SERVER_DAEMON_DOCUMENT_ROOT "."
#define XOS_HTTP_SERVER_DAEMON_CGI_PATTERN ""
#define XOS_HTTP_SERVER_DAEMON_CGI_EXECUTABLE ""
#define XOS_HTTP_SERVER_DAEMON_DEFAULT_CONTENT_FILE "hello.html"
#define XOS_HTTP_SERVER_DAEMON_DEFAULT_CONTENT_TYPE "text/html"

#define XOS_HTTP_SERVER_DAEMON_LISTEN_PORT_OPT "listen-port"
#define XOS_HTTP_SERVER_DAEMON_LISTEN_PORT_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_REQUIRED
#define XOS_HTTP_SERVER_DAEMON_LISTEN_PORT_OPTARG "number"
#define XOS_HTTP_SERVER_DAEMON_LISTEN_PORT_OPTUSE "Listening port number"
#define XOS_HTTP_SERVER_DAEMON_LISTEN_PORT_OPTVAL_S "p:"
#define XOS_HTTP_SERVER_DAEMON_LISTEN_PORT_OPTVAL_C 'p'

#define XOS_HTTP_SERVER_DAEMON_DOCUMENT_ROOT_OPT "document-root"
#define XOS_HTTP_SERVER_DAEMON_DOCUMENT_ROOT_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_REQUIRED
#define XOS_HTTP_SERVER_DAEMON_DOCUMENT_ROOT_OPTARG "path"
#define XOS_HTTP_SERVER_DAEMON_DOCUMENT_ROOT_OPTUSE "Document root path"
#define XOS_HTTP_SERVER_DAEMON_DOCUMENT_ROOT_OPTVAL_S "d:"
#define XOS_HTTP_SERVER_DAEMON_DOCUMENT_ROOT_OPTVAL_C 'd'

#define XOS_HTTP_SERVER_DAEMON_CONTENT_FILE_OPT "content-file"
#define XOS_HTTP_SERVER_DAEMON_CONTENT_FILE_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_REQUIRED
#define XOS_HTTP_SERVER_DAEMON_CONTENT_FILE_OPTARG "file"
#define XOS_HTTP_SERVER_DAEMON_CONTENT_FILE_OPTUSE "Default content file"
#define XOS_HTTP_SERVER_DAEMON_CONTENT_FILE_OPTVAL_S "f:"
#define XOS_HTTP_SERVER_DAEMON_CONTENT_FILE_OPTVAL_C 'f'

#define XOS_HTTP_SERVER_DAEMON_CONTENT_TYPE_OPT "content-type"
#define XOS_HTTP_SERVER_DAEMON_CONTENT_TYPE_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_REQUIRED
#define XOS_HTTP_SERVER_DAEMON_CONTENT_TYPE_OPTARG "string"
#define XOS_HTTP_SERVER_DAEMON_CONTENT_TYPE_OPTUSE "Default content type"
#define XOS_HTTP_SERVER_DAEMON_CONTENT_TYPE_OPTVAL_S "y:"
#define XOS_HTTP_SERVER_DAEMON_CONTENT_TYPE_OPTVAL_C 'y'

#define XOS_HTTP_SERVER_DAEMON_OPTIONS_CHARS_BEGIN \
   XOS_HTTP_SERVER_DAEMON_LISTEN_PORT_OPTVAL_S \
   XOS_HTTP_SERVER_DAEMON_DOCUMENT_ROOT_OPTVAL_S \
   XOS_HTTP_SERVER_DAEMON_CONTENT_FILE_OPTVAL_S \
   XOS_HTTP_SERVER_DAEMON_CONTENT_TYPE_OPTVAL_S

#define XOS_HTTP_SERVER_DAEMON_OPTIONS_CHARS_END \
   XOS_MAIN_OPTIONS_CHARS

#define XOS_HTTP_SERVER_DAEMON_OPTIONS_CHARS \
   XOS_HTTP_SERVER_DAEMON_OPTIONS_CHARS_BEGIN \
   XOS_HTTP_SERVER_DAEMON_OPTIONS_CHARS_END

#define XOS_HTTP_SERVER_DAEMON_OPTIONS_OPTIONS_BEGIN \
   {XOS_HTTP_SERVER_DAEMON_LISTEN_PORT_OPT, \
    XOS_HTTP_SERVER_DAEMON_LISTEN_PORT_OPTARG_REQUIRED, 0, \
    XOS_HTTP_SERVER_DAEMON_LISTEN_PORT_OPTVAL_C}, \
   {XOS_HTTP_SERVER_DAEMON_DOCUMENT_ROOT_OPT, \
    XOS_HTTP_SERVER_DAEMON_DOCUMENT_ROOT_OPTARG_REQUIRED, 0, \
    XOS_HTTP_SERVER_DAEMON_DOCUMENT_ROOT_OPTVAL_C}, \
   {XOS_HTTP_SERVER_DAEMON_CONTENT_FILE_OPT, \
    XOS_HTTP_SERVER_DAEMON_CONTENT_FILE_OPTARG_REQUIRED, 0, \
    XOS_HTTP_SERVER_DAEMON_CONTENT_FILE_OPTVAL_C}, \
   {XOS_HTTP_SERVER_DAEMON_CONTENT_TYPE_OPT, \
    XOS_HTTP_SERVER_DAEMON_CONTENT_TYPE_OPTARG_REQUIRED, 0, \
    XOS_HTTP_SERVER_DAEMON_CONTENT_TYPE_OPTVAL_C},

#define XOS_HTTP_SERVER_DAEMON_OPTIONS_OPTIONS_END \
   XOS_MAIN_OPTIONS_OPTIONS

#define XOS_HTTP_SERVER_DAEMON_OPTIONS_OPTIONS \
    XOS_HTTP_SERVER_DAEMON_OPTIONS_OPTIONS_BEGIN \
    XOS_HTTP_SERVER_DAEMON_OPTIONS_OPTIONS_END

namespace xos {
namespace http {
namespace server {

typedef xos::server::DaemonImplement DaemonImplementImplement;
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS DaemonImplement
: virtual public Processor, virtual public DaemonImplementImplement {
public:
    typedef DaemonImplementImplement Implements;
};
typedef xos::server::Daemon DaemonExtend;
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Daemon
: virtual public DaemonImplement, public DaemonExtend {
public:
    typedef DaemonImplement Implements;
    typedef DaemonExtend Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Daemon(Processor& delegatedToProcessor)
    : m_delegatedToProcessor(&delegatedToProcessor),
      m_numThreadsNo(XOS_HTTP_SERVER_DAEMON_NUM_THREADSNO),
      m_numThreads(XOS_HTTP_SERVER_DAEMON_NUM_THREADS),
      m_listenPortNo(XOS_HTTP_SERVER_DAEMON_LISTEN_PORTNO),
      m_listenPort(XOS_HTTP_SERVER_DAEMON_LISTEN_PORT),
      m_listenHost(XOS_HTTP_SERVER_DAEMON_LISTEN_HOST),
      m_documentRoot(XOS_HTTP_SERVER_DAEMON_DOCUMENT_ROOT),
      m_cgiPattern(XOS_HTTP_SERVER_DAEMON_CGI_PATTERN),
      m_cgiExecutable(XOS_HTTP_SERVER_DAEMON_CGI_EXECUTABLE),
      m_defaultContentFile(XOS_HTTP_SERVER_DAEMON_DEFAULT_CONTENT_FILE),
      m_defaultContentType(XOS_HTTP_SERVER_DAEMON_DEFAULT_CONTENT_TYPE) {
    }
    Daemon()
    : m_delegatedToProcessor(0),
      m_numThreadsNo(XOS_HTTP_SERVER_DAEMON_NUM_THREADSNO),
      m_numThreads(XOS_HTTP_SERVER_DAEMON_NUM_THREADS),
      m_listenPortNo(XOS_HTTP_SERVER_DAEMON_LISTEN_PORTNO),
      m_listenPort(XOS_HTTP_SERVER_DAEMON_LISTEN_PORT),
      m_listenHost(XOS_HTTP_SERVER_DAEMON_LISTEN_HOST),
      m_documentRoot(XOS_HTTP_SERVER_DAEMON_DOCUMENT_ROOT),
      m_cgiPattern(XOS_HTTP_SERVER_DAEMON_CGI_PATTERN),
      m_cgiExecutable(XOS_HTTP_SERVER_DAEMON_CGI_EXECUTABLE) {
    }
    virtual ~Daemon() {
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool GetQueryFormData(Request& request) {
        const String& query = request.GetQuery();
        if (0 < (query.Length())) {
            StringReader reader(query);
            Form& form = request.form();
            UrlEncodedFormReader uReader;

            XOS_LOG_TRACE("reading form from query...");
            uReader.Read(reader, form);
            return true;
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ushort SetListenPortNo(const String& to) {
        ushort listenPortNo;
        m_listenPort = to;
        if (0 < (listenPortNo = m_listenPort.ToUnsignedInt()))
            m_listenPortNo = listenPortNo;
        return m_listenPortNo;
    }
    virtual ushort SetListenPortNo(ushort to) {
        m_listenPortNo = to;
        return m_listenPortNo;
    }
    virtual ushort ListenPortNo() const {
        return m_listenPortNo;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual String& SetListenPort(ushort to) {
        m_listenPort.Assign(m_listenPortNo = to);
        return m_listenPort;
    }
    virtual String& SetListenPort(const String& to) {
        m_listenPort = to;
        return m_listenPort;
    }
    virtual const String& ListenPort() const {
        return m_listenPort;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual String& SetDocumentRoot(const String& to) {
        m_documentRoot = to;
        return m_documentRoot;
    }
    virtual const String& DocumentRoot() const  {
        return m_documentRoot;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual String& SetCgiPattern(const String& to) {
        m_cgiPattern = to;
        return m_cgiPattern;
    }
    virtual const String& CgiPattern() const {
        return m_cgiPattern;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual String& SetCgiExecutable(const String& to) {
        m_cgiExecutable = to;
        return m_cgiExecutable;
    }
    virtual const String& CgiExecutable() const {
        return m_cgiExecutable;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int OnOption
    (int optval, const char* optarg,
     const char* optname, int optind,
     int argc, char**argv, char**env) {
        int err = 0;
        switch(optval) {
        case XOS_HTTP_SERVER_DAEMON_LISTEN_PORT_OPTVAL_C:
            if ((optarg)) {
                SetListenPortNo(optarg);
                XOS_LOG_TRACE("m_listenPort = \"" << m_listenPort << "\"");
            }
            break;
        case XOS_HTTP_SERVER_DAEMON_DOCUMENT_ROOT_OPTVAL_C:
            if ((optarg)) {
                SetDocumentRoot(optarg);
                XOS_LOG_TRACE("m_documentRoot = \"" << m_documentRoot << "\"");
            }
            break;
        case XOS_HTTP_SERVER_DAEMON_CONTENT_FILE_OPTVAL_C:
            if ((optarg)) {
                m_defaultContentFile = (optarg);
                XOS_LOG_TRACE("m_defaultContentFile = \"" << m_defaultContentFile << "\"");
            }
            break;
        case XOS_HTTP_SERVER_DAEMON_CONTENT_TYPE_OPTVAL_C:
            if ((optarg)) {
                m_defaultContentType = (optarg);
                XOS_LOG_TRACE("m_defaultContentType = \"" << m_defaultContentType << "\"");
            }
            break;
        default:
            err = Extends::OnOption
            (optval, optarg, optname, optind, argc, argv, env);
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual const char* OptionUsage
    (const char*& optarg, const struct option* longopt) {
        const char* chars = "";
        switch(longopt->val) {
        case XOS_HTTP_SERVER_DAEMON_LISTEN_PORT_OPTVAL_C:
            optarg = XOS_HTTP_SERVER_DAEMON_LISTEN_PORT_OPTARG;
            chars = XOS_HTTP_SERVER_DAEMON_LISTEN_PORT_OPTUSE;
            break;

        case XOS_HTTP_SERVER_DAEMON_DOCUMENT_ROOT_OPTVAL_C:
            optarg = XOS_HTTP_SERVER_DAEMON_DOCUMENT_ROOT_OPTARG;
            chars = XOS_HTTP_SERVER_DAEMON_DOCUMENT_ROOT_OPTUSE;
            break;

        case XOS_HTTP_SERVER_DAEMON_CONTENT_FILE_OPTVAL_C:
            optarg = XOS_HTTP_SERVER_DAEMON_CONTENT_FILE_OPTARG;
            chars = XOS_HTTP_SERVER_DAEMON_CONTENT_FILE_OPTUSE;
            break;

        case XOS_HTTP_SERVER_DAEMON_CONTENT_TYPE_OPTVAL_C:
            optarg = XOS_HTTP_SERVER_DAEMON_CONTENT_TYPE_OPTARG;
            chars = XOS_HTTP_SERVER_DAEMON_CONTENT_TYPE_OPTUSE;
            break;

        default:
            chars = Extends::OptionUsage(optarg, longopt);
        }
        return chars;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual const char* Options(const struct option*& longopts) {
        static const char* chars = XOS_HTTP_SERVER_DAEMON_OPTIONS_CHARS;
        static struct option optstruct[]= {
            XOS_HTTP_SERVER_DAEMON_OPTIONS_OPTIONS
            {0, 0, 0, 0}};
        longopts = optstruct;
        return chars;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool OnProcess(Response& response, const Request& request) {
        bool processed = false;
        return processed;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual bool Process(Response& response, const Request& request) {
        bool processed = false;
        Processor* delegatedToProcessor;
        if ((delegatedToProcessor = DelegatedToProcessor()))
            processed = delegatedToProcessor->Process(response, request);
        else processed = OnProcess(response, request);
        return processed;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual Processor* DelegateToProcessor(Processor* delegatedToProcessor) {
        return m_delegatedToProcessor = delegatedToProcessor;
    }
    virtual Processor* DelegatedToProcessor() const {
        return m_delegatedToProcessor;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    Processor* m_delegatedToProcessor;
    ushort m_numThreadsNo;
    String m_numThreads;
    ushort m_listenPortNo;
    String m_listenPort;
    String m_listenHost;
    String m_documentRoot, m_cgiPattern, m_cgiExecutable;
    String m_defaultContentFile, m_defaultContentType;
};

} // namespace server 
} // namespace http 
} // namespace xos 

#endif // _XOS_HTTP_SERVER_DAEMON_HPP 
