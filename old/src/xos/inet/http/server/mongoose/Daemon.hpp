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
#ifndef _XOS_HTTP_SERVER_MONGOOSE_DAEMON_HPP
#define _XOS_HTTP_SERVER_MONGOOSE_DAEMON_HPP

#include "xos/inet/http/server/Daemon.hpp"
#include "xos/inet/http/FormReader.hpp"
#include "xos/inet/http/Response.hpp"
#include "xos/inet/http/Request.hpp"
#include "xos/os/os/Thread.hpp"
#include "xos/os/os/Semaphore.hpp"
#include "xos/os/os/Mutex.hpp"
#include "xos/base/StringReader.hpp"
#include "xos/base/Wrapped.hpp"
#include <mongoose.h>
#include <unistd.h>

#define XOS_HTTP_SERVER_MONGOOSE_DAEMON_SLEEP_MSECONDS 100

#define XOS_HTTP_SERVER_MONGOOSE_DAEMON_OPTION_DOCUMENT_ROOT "document_root"
#define XOS_HTTP_SERVER_MONGOOSE_DAEMON_OPTION_LISTENGING_PORTS "listening_ports"
#define XOS_HTTP_SERVER_MONGOOSE_DAEMON_OPTION_NUM_THREADS "num_threads"
#define XOS_HTTP_SERVER_MONGOOSE_DAEMON_OPTION_CGI_PATTERN "cgi_pattern"
#define XOS_HTTP_SERVER_MONGOOSE_DAEMON_OPTION_CGI_INTREPRETER "cgi_interpreter"

#define XOS_HTTP_SERVER_MONGOOSE_DAEMON_CGI_PATTERN_OPT "cgi-pattern"
#define XOS_HTTP_SERVER_MONGOOSE_DAEMON_CGI_PATTERN_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_REQUIRED
#define XOS_HTTP_SERVER_MONGOOSE_DAEMON_CGI_PATTERN_OPTARG "pattern (**.ex1$|**.ex2$|...)"
#define XOS_HTTP_SERVER_MONGOOSE_DAEMON_CGI_PATTERN_OPTUSE "File pattern for CGI processing"
#define XOS_HTTP_SERVER_MONGOOSE_DAEMON_CGI_PATTERN_OPTVAL_S "c:"
#define XOS_HTTP_SERVER_MONGOOSE_DAEMON_CGI_PATTERN_OPTVAL_C 'c'

#define XOS_HTTP_SERVER_MONGOOSE_DAEMON_CGI_EXECUTABLE_OPT "cgi-executable"
#define XOS_HTTP_SERVER_MONGOOSE_DAEMON_CGI_EXECUTABLE_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_REQUIRED
#define XOS_HTTP_SERVER_MONGOOSE_DAEMON_CGI_EXECUTABLE_OPTARG "filename"
#define XOS_HTTP_SERVER_MONGOOSE_DAEMON_CGI_EXECUTABLE_OPTUSE "Filename of CGI executable"
#define XOS_HTTP_SERVER_MONGOOSE_DAEMON_CGI_EXECUTABLE_OPTVAL_S "g:"
#define XOS_HTTP_SERVER_MONGOOSE_DAEMON_CGI_EXECUTABLE_OPTVAL_C 'g'

#define XOS_HTTP_SERVER_MONGOOSE_DAEMON_OPTIONS_CHARS \
    XOS_HTTP_SERVER_DAEMON_OPTIONS_CHARS_BEGIN \
    XOS_HTTP_SERVER_MONGOOSE_DAEMON_CGI_PATTERN_OPTVAL_S \
    XOS_HTTP_SERVER_MONGOOSE_DAEMON_CGI_EXECUTABLE_OPTVAL_S \
    XOS_HTTP_SERVER_DAEMON_OPTIONS_CHARS_END

#define XOS_HTTP_SERVER_MONGOOSE_DAEMON_OPTIONS_OPTIONS \
    XOS_HTTP_SERVER_DAEMON_OPTIONS_OPTIONS_BEGIN \
    {XOS_HTTP_SERVER_MONGOOSE_DAEMON_CGI_PATTERN_OPT, \
     XOS_HTTP_SERVER_MONGOOSE_DAEMON_CGI_PATTERN_OPTARG_REQUIRED, 0, \
     XOS_HTTP_SERVER_MONGOOSE_DAEMON_CGI_PATTERN_OPTVAL_C}, \
    {XOS_HTTP_SERVER_MONGOOSE_DAEMON_CGI_EXECUTABLE_OPT, \
     XOS_HTTP_SERVER_MONGOOSE_DAEMON_CGI_EXECUTABLE_OPTARG_REQUIRED, 0, \
     XOS_HTTP_SERVER_MONGOOSE_DAEMON_CGI_EXECUTABLE_OPTVAL_C}, \
    XOS_HTTP_SERVER_DAEMON_OPTIONS_OPTIONS_END

namespace xos {
namespace http {
namespace server {
namespace mongoose {

typedef CharReader ContentReaderImplement;
typedef Base ContentReaderExtend;
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS ContentReader
: virtual public ContentReaderImplement, public ContentReaderExtend {
public:
    typedef ContentReaderImplement Implements;
    typedef ContentReaderExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    ContentReader
    (struct mg_connection& mgConnection, int contentLength = -1)
    : m_mgConnection(mgConnection),
      m_contentLength(contentLength),
      m_contentTell(0) {
    }
    virtual ~ContentReader() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Read(WhatT* what, size_t size) {
        ssize_t count = -1;
        if (0 < (m_contentLength)) {
            if (m_contentLength < (m_contentTell + size))
                size = m_contentLength - m_contentTell;
            if (0 < (size)) {
                if (0 < (count = mg_read(&m_mgConnection, what, size))) {
                    m_contentTell += count;
                    m_contentRead.Append((const char*)(what), count);
                }
            }
        } else {
            for (count = 0; count < size; ++count, ++what) {
                if (0 >= (mg_read(&m_mgConnection, what, 1))) {
                    break;
                } else {
                    m_contentRead.Append((const char*)(what), 1);
                }
            }
        }
        return count;
    }
    virtual const String& GetContentRead() const {
        return m_contentRead;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    struct mg_connection& m_mgConnection;
    int m_contentLength;
    size_t m_contentTell;
    String m_contentRead;
};

typedef server::Daemon DaemonTExtend;
typedef server::DaemonImplement DaemonTImplement;
template
<class TExtend = DaemonTExtend,
 class TImplement = DaemonTImplement>
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS DaemonT: virtual public TImplement, public TExtend {
public:
    typedef TImplement Implements;
    typedef TExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    DaemonT(Processor& delegatedToProcessor)
    : Extends(delegatedToProcessor),
      m_mgSleepMilliseconds(XOS_HTTP_SERVER_MONGOOSE_DAEMON_SLEEP_MSECONDS),
      m_mgCallBacks(MgBeginRequestHandler, 0),
      m_mgServerThreadRun(*this),
      m_mgServerThread(0) {
    }
    DaemonT()
    : m_mgSleepMilliseconds(XOS_HTTP_SERVER_MONGOOSE_DAEMON_SLEEP_MSECONDS),
      m_mgCallBacks(MgBeginRequestHandler, 0),
      m_mgServerThreadRun(*this),
      m_mgServerThread(0) {
    }
    virtual ~DaemonT() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int RunServer(int argc, char** argv, char** env) {
        int err = 0;
        if (!(err = BeforeRunMgServer(argc, argv, env))) {
            int err2;

            err = RunMgServer(argc, argv, env);

            if ((err2 = AfterRunMgServer(argc, argv, env))) {
                if (!err)
                    err = err2;
            }
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int RunMgServer(int argc, char** argv, char** env) {
        int err = 0;
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int BeforeRunMgServer(int argc, char** argv, char** env) {
        int err = 1;

        if ((m_mgStopSemaphore.Create())) {

            XOS_LOG_TRACE("creating server thread...");

            if ((m_mgServerThread = new MgServerThread(m_mgServerThreadRun))) {
                XOS_LOG_TRACE("...created server thread");
                err = 0;
                return err;
            } else {
                XOS_LOG_ERROR("failed create server thread");
            }
            if (!(m_mgStopSemaphore.Destroy())) {
                XOS_LOG_ERROR("faile to destroy stop semaphore");
            }
        } else {
            XOS_LOG_ERROR("failed to create stop semaphore");
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int AfterRunMgServer(int argc, char** argv, char** env) {
        int err = 0;

        if ((m_mgServerThread)) {
            XOS_LOG_TRACE("joining server thread...");

            m_mgServerThread->Join();

            XOS_LOG_TRACE("...joined server");
            delete m_mgServerThread;
            m_mgServerThread = 0;
        } else {
            XOS_LOG_ERROR("server thread not created");
            err = 1;
        }
        if (!(m_mgStopSemaphore.Destroy())) {
            XOS_LOG_ERROR("faile to destroy stop semaphore");
            err = 1;
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int OnMgBeginRequest(struct mg_connection *mgConnection) {
        const struct mg_request_info* mgRequestInfo = 0;
        int processed = 0;
        XOS_LOG_TRACE("in...");

        if ((mgConnection)) {
            if ((mgRequestInfo = mg_get_request_info(mgConnection))) {
                http::Request request;
                http::Response response;
                const char* chars;

                if ((chars = mgRequestInfo->request_method)) {
                    request.SetMethod(chars);
                    XOS_LOG_TRACE("method = \"" << request.GetMethod() << "\"");
                }

                if ((chars = mgRequestInfo->uri)) {
                    const String& path = request.SetPath(chars);
                    XOS_LOG_TRACE("path = \"" << path << "\"");
                    if ((0 < (this->m_documentRoot.Length())) && (0 < (path.Length()))) {
                        const String& pathTranslated = request.SetPathTranslated(this->m_documentRoot, path);
                        XOS_LOG_TRACE("path translated = \"" << pathTranslated << "\"");
                    }
                }

                if ((chars = mgRequestInfo->query_string)) {
                    request.SetQuery(chars);
                    XOS_LOG_TRACE("query = \"" << request.GetQuery() << "\"");
                }

                if ((chars = mg_get_header(mgConnection, XOS_HTTP_HEADER_NAME_CONTENT_TYPE))) {
                    request.SetContentType(chars);
                    XOS_LOG_TRACE("content-type = \"" << request.GetContentType() << "\"");
                }

                if ((chars = mg_get_header(mgConnection, XOS_HTTP_HEADER_NAME_CONTENT_LENGTH))) {
                    request.SetContentLength(chars);
                    XOS_LOG_TRACE("content-length = \"" << request.GetContentLength() << "\"");
                }

                //
                // Get query form data
                //
                this->GetQueryFormData(request);

                //
                // Get url encoded content form data
                //
                if (!(request.GetContentType().compare(XOS_INET_HTTP_URL_ENCODED_FORM_CONTENT_TYPE_NAME))) {
                    int contentLength = request.GetContentLengthNo();
                    ContentReader reader(*mgConnection, contentLength);
                    const String& contentRead = reader.GetContentRead();
                    Form& form = request.form();
                    UrlEncodedFormReader uReader;
                    uReader.Read(reader, form);
                    XOS_LOG_TRACE("content read = \"" << contentRead << "\"");
                }

                if ((this->Process(response, request))) {
                    if (!(response.line().version().Length())) {
                        response.line().version().protocol().Assign(XOS_HTTP_VERSION_PROTOCOL);
                        response.line().version().major().Assign(XOS_HTTP_VERSION_MAJOR);
                        response.line().version().minor().Assign(XOS_HTTP_VERSION_MINOR);
                        response.line().version().Combine();
                    }
                    if (!(response.line().status().Length())) {
                        response.line().status().Assign(XOS_HTTP_STATUS_OK);
                        response.line().reason().Assign(XOS_HTTP_STATUS_OK_REASON);
                        response.line().Combine();
                    }
                    if ((response.line().Length())) {
                        String responseData(response.line());
                        if ((response.headers().Combine(responseData))) {
                            if ((response.message().Length())) {
                                responseData.Append(response.message());
                            }
                            XOS_LOG_TRACE("response = \"" << responseData << "\"");
                            if (0 < (mg_write(mgConnection, responseData.Chars(), responseData.Length()))) {
                                processed = 1;
                            } else {
                                XOS_LOG_ERROR("failed on mg_write()");
                            }
                        }
                    }
                }
            }
        }
        XOS_LOG_TRACE("...out");
        return processed;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void RunMgServerThread() {
        const char** mgOptions = MgOptions();
        struct mg_callbacks* mgCallbacks = MgCallbacks();
        struct mg_context *mgCtx;

        XOS_LOG_TRACE("in...");

        for (const char** o = mgOptions; *o; o += 2) {
            XOS_LOG_TRACE("\"" << *o << "\" = \"" << *(o+1) << "\"");
        }

        if ((mgCtx = mg_start(mgCallbacks, (void*)(this), mgOptions))) {
            if ((false)) {
            } else {
                XOS_LOG_TRACE("waiting on stop semaphore...");

                if ((m_mgStopSemaphore.Wait())) {
                    XOS_LOG_TRACE("...waited on stop semaphore");
                } else {
                    XOS_LOG_ERROR("...failed to waiting on stop semaphore");

                    for (bool done = false; !done; done = false) {
                        usleep(m_mgSleepMilliseconds*1000);
                    }
                }
            }
            mg_stop(mgCtx);
        } else {
            XOS_LOG_ERROR("failed on mg_start()");
        }
        XOS_LOG_TRACE("...out");
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const char** MgOptions() const {
        static const char* cgiExecutable = MgGgiExecutable();
        static const char* cgiPattern = MgCgiPattern();

        static const char* mgOptions[] = {
            XOS_HTTP_SERVER_MONGOOSE_DAEMON_OPTION_DOCUMENT_ROOT, MgDocumentRoot(),
            XOS_HTTP_SERVER_MONGOOSE_DAEMON_OPTION_LISTENGING_PORTS, MgListenPorts(),
            XOS_HTTP_SERVER_MONGOOSE_DAEMON_OPTION_NUM_THREADS, MgNumThreads(),
            (cgiPattern)?(XOS_HTTP_SERVER_MONGOOSE_DAEMON_OPTION_CGI_PATTERN):(0), cgiPattern,
            (cgiExecutable)?(XOS_HTTP_SERVER_MONGOOSE_DAEMON_OPTION_CGI_INTREPRETER):(0), cgiExecutable,
            0,0
        };
        return mgOptions;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual struct mg_callbacks* MgCallbacks() const {
        struct mg_callbacks& mgCallbacks = m_mgCallBacks.wrapped();
        return &mgCallbacks;
    }
    ///////////////////////////////////////////////////////////////////////
    static int MgBeginRequestHandler(struct mg_connection *mgConnection) {
        int processed = 0;
        const struct mg_request_info* mgRequestInfo;
        DaemonT* daemon;

        XOS_LOG_TRACE("in...");

        if ((mgConnection)) {
            if ((mgRequestInfo = mg_get_request_info(mgConnection))) {
                if ((daemon = (DaemonT*)(mgRequestInfo->user_data))) {
                    processed = daemon->OnMgBeginRequest(mgConnection);
                }
            }
        }
        XOS_LOG_TRACE("..out");
        return processed;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const char* MgDocumentRoot() const {
        return this->m_documentRoot.c_str();
    }
    virtual const char* MgListenPorts() const {
        return this->m_listenPort.c_str();
    }
    virtual const char* MgNumThreads() const {
        return this->m_numThreads.c_str();
    }
    virtual const char* MgGgiExecutable() const {
        return (0 < this->m_cgiExecutable.length())?(this->m_cgiExecutable.c_str()):(0);
    }
    virtual const char* MgCgiPattern() const {
        return (0 < this->m_cgiPattern.length())?(this->m_cgiPattern.c_str()):(0);
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Stop() {
        this->SetStop();
        return m_mgStopSemaphore.Release();
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    typedef InterfaceBase MgCallBacksImplement;
    typedef Wrapped
    <struct mg_callbacks, int,
     ExportBase, MgCallBacksImplement> MgCallBacksExtend;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    class _EXPORT_CLASS MgCallBacks
    : virtual public MgCallBacksImplement, public MgCallBacksExtend
    {
    public:
        typedef MgCallBacksImplement Implements;
        typedef MgCallBacksExtend Extends;
        typedef int (*BeginRequestHandler)(struct mg_connection *mgConnection);
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        MgCallBacks
        (BeginRequestHandler beginRequestHandler = 0,
         InitializedT initialized = 0): Extends(initialized) {
            m_wrapped.begin_request = beginRequestHandler;
        }
    };
    typedef os::Semaphore MgStopSemaphore;
    typedef os::Thread MgServerThread;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    class _EXPORT_CLASS MgServerThreadRun: public Thread::Run {
    public:
        typedef Thread::Run Extends;
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        MgServerThreadRun(DaemonT& daemon): m_daemon(daemon) {
        }
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        virtual void operator()() {
            m_daemon.RunMgServerThread();
        }
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
    protected:
        DaemonT& m_daemon;
    };
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    u_long m_mgSleepMilliseconds;
    MgCallBacks m_mgCallBacks;
    MgServerThreadRun m_mgServerThreadRun;
    MgServerThread* m_mgServerThread;
    MgStopSemaphore m_mgStopSemaphore;
};

typedef DaemonTImplement DaemonImplement;
typedef DaemonT<DaemonTExtend, DaemonImplement> DaemonExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Daemon
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Daemon: virtual public DaemonImplement,public DaemonExtend {
public:
    typedef DaemonImplement Implements;
    typedef DaemonExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Daemon(Processor& delegatedToProcessor): Extends(delegatedToProcessor) {
    }
    Daemon() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int OnOption
    (int optval, const char* optarg,
     const char* optname, int optind,
     int argc, char**argv, char**env) {
        int err = 0;
        switch(optval) {
        case XOS_HTTP_SERVER_MONGOOSE_DAEMON_CGI_EXECUTABLE_OPTVAL_C:
            if ((optarg)) {
                if ((optarg[0])) {
                    SetCgiExecutable(optarg);
                }
            }
            break;
        case XOS_HTTP_SERVER_MONGOOSE_DAEMON_CGI_PATTERN_OPTVAL_C:
            if ((optarg)) {
                if ((optarg[0])) {
                    SetCgiPattern(optarg);
                }
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
        case XOS_HTTP_SERVER_MONGOOSE_DAEMON_CGI_PATTERN_OPTVAL_C:
            optarg = XOS_HTTP_SERVER_MONGOOSE_DAEMON_CGI_PATTERN_OPTARG;
            chars = XOS_HTTP_SERVER_MONGOOSE_DAEMON_CGI_PATTERN_OPTUSE;
            break;
        case XOS_HTTP_SERVER_MONGOOSE_DAEMON_CGI_EXECUTABLE_OPTVAL_C:
            optarg = XOS_HTTP_SERVER_MONGOOSE_DAEMON_CGI_EXECUTABLE_OPTARG;
            chars = XOS_HTTP_SERVER_MONGOOSE_DAEMON_CGI_EXECUTABLE_OPTUSE;
            break;
        default:
            chars = Extends::OptionUsage(optarg, longopt);
        }
        return chars;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual const char* Options(const struct option*& longopts) {
        static const char* chars = XOS_HTTP_SERVER_MONGOOSE_DAEMON_OPTIONS_CHARS;
        static struct option optstruct[]= {
            XOS_HTTP_SERVER_MONGOOSE_DAEMON_OPTIONS_OPTIONS
            {0, 0, 0, 0}};
        longopts = optstruct;
        return chars;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace mongoose 
} // namespace server 
} // namespace http 
} // namespace xos 

#endif // _XOS_HTTP_SERVER_MONGOOSE_DAEMON_HPP 
