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
///   Date: 12/5/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_HTTP_SERVER_LIBWEBSOCKETS_DAEMON_HPP
#define _XOS_HTTP_SERVER_LIBWEBSOCKETS_DAEMON_HPP

#include "xos/inet/http/server/libwebsockets/Libwebsockets.hpp"
#include "xos/inet/http/server/Daemon.hpp"
#include "xos/inet/http/FormReader.hpp"
#include "xos/inet/http/Response.hpp"
#include "xos/inet/http/Request.hpp"
#include "xos/base/StringReader.hpp"
#include "xos/base/Array.hpp"
#include "xos/base/Attached.hpp"
#include "xos/base/Wrapped.hpp"

#define XOS_HTTP_SERVER_LIBWEBSOCKETS_DAEMON_LWS_DEBUG_LEVEL 7
#define XOS_HTTP_SERVER_LIBWEBSOCKETS_DAEMON_LWS_TIMEOUT_MS 50

#define XOS_HTTP_SERVER_LIBWEBSOCKETS_DAEMON_LWS_ENTER_NOTICE "lwsXosHttpd server"
#define XOS_HTTP_SERVER_LIBWEBSOCKETS_DAEMON_LWS_EXIT_NOTICE \
    XOS_HTTP_SERVER_LIBWEBSOCKETS_DAEMON_LWS_ENTER_NOTICE " exited cleanly"

#define XOS_HTTP_SERVER_LIBWEBSOCKETS_DAEMON_SEND_BUFFER_DATA_SIZE 4096
#define XOS_HTTP_SERVER_LIBWEBSOCKETS_DAEMON_SEND_BUFFER_SIZE \
    XOS_HTTP_SERVER_LIBWEBSOCKETS_DAEMON_SEND_BUFFER_DATA_SIZE \
    + LWS_SEND_BUFFER_PRE_PADDING \
    + LWS_SEND_BUFFER_POST_PADDING

#define XOS_HTTP_SERVER_LIBWEBSOCKETS_DAEMON_LWS_PROTOCOL_HTTP_NAME "http-only"
#define XOS_HTTP_SERVER_LIBWEBSOCKETS_DAEMON_LWS_PROTOCOL_HTTP_RX_BUFFER_SIZE 0
#define XOS_HTTP_SERVER_LIBWEBSOCKETS_DAEMON_LWS_PROTOCOL_HTTP_CALLBACK LwsCallbackHttp
#define XOS_HTTP_SERVER_LIBWEBSOCKETS_DAEMON_LWS_PROTOCOL_HTTP_SESSION_DATA_SIZE sizeof(HttpSessionData)

#define XOS_HTTP_SERVER_LIBWEBSOCKETS_DAEMON_LWS_PROTOCOL_HTTP \
{ XOS_HTTP_SERVER_LIBWEBSOCKETS_DAEMON_LWS_PROTOCOL_HTTP_NAME,\
  XOS_HTTP_SERVER_LIBWEBSOCKETS_DAEMON_LWS_PROTOCOL_HTTP_CALLBACK,\
  XOS_HTTP_SERVER_LIBWEBSOCKETS_DAEMON_LWS_PROTOCOL_HTTP_SESSION_DATA_SIZE,\
  XOS_HTTP_SERVER_LIBWEBSOCKETS_DAEMON_LWS_PROTOCOL_HTTP_RX_BUFFER_SIZE},

#define XOS_HTTP_SERVER_LIBWEBSOCKETS_DAEMON_LWS_PROTOCOLS_COUNT 1

#define XOS_HTTP_SERVER_LIBWEBSOCKETS_DAEMON_LWS_PROTOCOLS \
    XOS_HTTP_SERVER_LIBWEBSOCKETS_DAEMON_LWS_PROTOCOL_HTTP

#define XOS_HTTP_SERVER_LIBWEBSOCKETS_DAEMON_LWS_PROTOCOL_NULL \
    { NULL, NULL, 0, 0 }

#define XOS_HTTP_SERVER_LIBWEBSOCKETS_DAEMON_LWS_PROTOCOLS_END \
    XOS_HTTP_SERVER_LIBWEBSOCKETS_DAEMON_LWS_PROTOCOL_NULL

namespace xos {
namespace http {
namespace server {
namespace libwebsockets {

typedef InterfaceBase SendBufferImplement;
typedef Array
<unsigned char, XOS_HTTP_SERVER_LIBWEBSOCKETS_DAEMON_SEND_BUFFER_SIZE,
 ExportBase, InterfaceBase> SendBufferExtend;
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS SendBuffer
: virtual public SendBufferImplement, public SendBufferExtend {
public:
    typedef SendBufferImplement Implements;
    typedef SendBufferExtend Extends;
};

typedef InterfaceBase ContextImplement;
typedef Attached
<struct libwebsocket_context*, int,0,
 ExportBase, ContextImplement> ContextExtend;
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Context
: virtual public ContextImplement, public ContextExtend {
public:
    typedef ContextImplement Implements;
    typedef ContextExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Context(AttachedT attachedTo = 0): Extends(attachedTo) {
    }
};

typedef InterfaceBase ContextCreationInfoImplement;
typedef Wrapped
<struct lws_context_creation_info, int,
 ExportBase, ContextCreationInfoImplement> ContextCreationInfoExtend;
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS ContextCreationInfo
: virtual public ContextCreationInfoImplement, public ContextCreationInfoExtend {
public:
    typedef ContextCreationInfoImplement Implements;
    typedef ContextCreationInfoExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    ContextCreationInfo(InitializedT initialized = 0): Extends(initialized) {
    }
};

typedef server::Daemon DaemonExtend;
typedef server::DaemonImplement DaemonImplement;
template
<class TExtend = DaemonExtend,
 class TImplement = DaemonImplement>
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS DaemonT
: virtual public TImplement, public TExtend {
public:
    typedef TImplement Implements;
    typedef TExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    DaemonT(Processor& delegatedToProcessor)
    : Extends(delegatedToProcessor),
      m_lwsDebugLevel(XOS_HTTP_SERVER_LIBWEBSOCKETS_DAEMON_LWS_DEBUG_LEVEL),
      m_lwsTimeoutMs(XOS_HTTP_SERVER_LIBWEBSOCKETS_DAEMON_LWS_TIMEOUT_MS),
      m_lwsEnterNotice(XOS_HTTP_SERVER_LIBWEBSOCKETS_DAEMON_LWS_ENTER_NOTICE),
      m_lwsExitNotice(XOS_HTTP_SERVER_LIBWEBSOCKETS_DAEMON_LWS_EXIT_NOTICE),
      m_lwsUid(-1),
      m_lwsGid(-1),
      m_lwsContext(0),
      m_lwsCreationInfo(0) {
    }
    virtual ~DaemonT() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int RunServer(int argc, char** argv, char** env) {
        int err = 0;
        if (!(err = BeforeRunLwsServer(argc, argv, env))) {
            int err2;

            err = RunLwsServer(argc, argv, env);

            if ((err2 = AfterRunLwsServer(argc, argv, env))) {
                if (!err) err = err2;
            }
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int RunLwsServer(int argc, char** argv, char** env) {
        struct libwebsocket_context*& lwsContext = m_lwsContext.attachedTo();
        struct lws_context_creation_info& lwsCreationInfo = m_lwsCreationInfo.wrapped();
        int err = 0;
        lws_set_log_level(m_lwsDebugLevel, lwsl_emit_syslog);
        lwsl_notice(m_lwsEnterNotice.c_str());

        lwsCreationInfo.port = LwsListenPort();
        lwsCreationInfo.protocols = LwsProtocols();
        lwsCreationInfo.extensions = LwsExtensions();
        lwsCreationInfo.gid = m_lwsUid;
        lwsCreationInfo.uid = m_lwsGid;
        lwsCreationInfo.user = this;

        XOS_LOG_DEBUG("libwebsocket_create_context()...");

        if ((lwsContext = libwebsocket_create_context(&lwsCreationInfo))) {

            XOS_LOG_DEBUG("...libwebsocket_create_context()");

            while (LwsServiced(lwsContext, m_lwsTimeoutMs)) {
                if (this->GetStop()) {
                    XOS_LOG_DEBUG("...GetStop() is true");
                    break;
                }
            }

            XOS_LOG_DEBUG("libwebsocket_context_destory()...");

            libwebsocket_context_destroy(lwsContext);
            lwsContext = 0;

            lwsl_notice(m_lwsExitNotice.c_str());
        } else  {
            XOS_LOG_ERROR("...failed on libwebsocket_create_context()");
        }
        return err;
    }
    virtual int BeforeRunLwsServer(int argc, char** argv, char** env) {
        int err = 0;
        return err;
    }
    virtual int AfterRunLwsServer(int argc, char** argv, char** env) {
        int err = 0;
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool LwsServiced
    (struct libwebsocket_context *context, int timeout_ms) {
        return (0 <= libwebsocket_service(context, timeout_ms));
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int OnLwsCallbackHttp_LWS_CALLBACK_HTTP
    (struct libwebsocket_context *context, struct libwebsocket *wsi,
     enum libwebsocket_callback_reasons reason, void *user, void *in, size_t len) {
        int result = -1;

        XOS_LOG_DEBUG("in...");

        if ((in) && (0 < len)) {
            Request::Method method(XOS_HTTP_REQUEST_METHOD_NAME_GET);
            Request::Uri uri((const char*)(in), len);
            Request request(method, uri);
            Response response;

            XOS_LOG_DEBUG("uri = \"" << uri << "\" path = \"" << uri.GetPath() << "\" query = \"" << uri.GetQuery() << "\" fragment = \"" << uri.GetFragment() << "\"");

            this->GetQueryFormData(request);

            XOS_LOG_DEBUG("processing request...");

            if ((this->Process(response, request))) {

                XOS_LOG_DEBUG("...processed request");

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

                        XOS_LOG_DEBUG("response = \"" << responseData << "\"");

                        if ((wsi)) {
                            libwebsocket_write_protocol lwsWrite = LWS_WRITE_HTTP;
                            unsigned char* lwsBuf;
                            size_t lwsLen;
                            if ((lwsBuf = (unsigned char*)(responseData.Chars()))
                                && (lwsLen = responseData.Length())) {
                            }

                            XOS_LOG_DEBUG("libwebsocket_write()...");

                            if (0 < (libwebsocket_write(wsi, lwsBuf, lwsLen, lwsWrite))) {
                                XOS_LOG_DEBUG("...libwebsocket_write()");
                                return 1;
                            } else {
                                XOS_LOG_ERROR("failed on libwebsocket_write()");
                            }
                        }
                    }
                }
            }
        }
        if ((this->m_defaultContentFile.Length())
            && (this->m_defaultContentType.Length())) {
            int err;
            if (!(err = libwebsockets_serve_http_file
                (context, wsi, this->m_defaultContentFile.c_str(), this->m_defaultContentType.c_str()))) {
                result = 1;
            } else {
                XOS_LOG_ERROR("failed on libwebsockets_serve_http_file(\"" << this->m_defaultContentFile << "\", \"" << this->m_defaultContentType << "\")");
            }
        }
        XOS_LOG_DEBUG("...out");
        return result;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int OnLwsCallbackHttp_LWS_CALLBACK_HTTP_WRITEABLE
    (struct libwebsocket_context *context, struct libwebsocket *wsi,
     enum libwebsocket_callback_reasons reason, void *user, void *in, size_t len) {
        int result = 0;
        return result;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int OnLwsCallbackHttp_LWS_CALLBACK_HTTP_FILE_COMPLETION
    (struct libwebsocket_context *context, struct libwebsocket *wsi,
     enum libwebsocket_callback_reasons reason, void *user, void *in, size_t len) {
        int result = 0;
        return result;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int OnLwsCallbackHttp_LWS_CALLBACK_CLOSED_HTTP
    (struct libwebsocket_context *context, struct libwebsocket *wsi,
     enum libwebsocket_callback_reasons reason, void *user, void *in, size_t len) {
        int result = 0;
        return result;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int OnLwsCallbackHttp_LWS_CALLBACK_FILTER_PROTOCOL_CONNECTION
    (struct libwebsocket_context *context, struct libwebsocket *wsi,
     enum libwebsocket_callback_reasons reason, void *user, void *in, size_t len) {
        int result = 0;
        return result;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int OnLwsCallbackHttp_LWS_CALLBACK_FILTER_NETWORK_CONNECTION
    (struct libwebsocket_context *context, struct libwebsocket *wsi,
     enum libwebsocket_callback_reasons reason, void *user, void *in, size_t len) {
        int result = 0;
        return result;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int OnLwsCallbackHttp_LWS_CALLBACK_CLIENT_CONNECTION_ERROR
    (struct libwebsocket_context *context, struct libwebsocket *wsi,
     enum libwebsocket_callback_reasons reason, void *user, void *in, size_t len) {
        int result = 0;
        return result;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int OnLwsCallbackHttp_LWS_CALLBACK_CLIENT_FILTER_PRE_ESTABLISH
    (struct libwebsocket_context *context, struct libwebsocket *wsi,
     enum libwebsocket_callback_reasons reason, void *user, void *in, size_t len) {
        int result = 0;
        return result;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int OnLwsCallbackHttp_LWS_CALLBACK_CLIENT_ESTABLISHED
    (struct libwebsocket_context *context, struct libwebsocket *wsi,
     enum libwebsocket_callback_reasons reason, void *user, void *in, size_t len) {
        int result = 0;
        return result;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int OnLwsCallbackHttp_LWS_CALLBACK_ESTABLISHED
    (struct libwebsocket_context *context, struct libwebsocket *wsi,
     enum libwebsocket_callback_reasons reason, void *user, void *in, size_t len) {
        int result = 0;
        return result;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int OnLwsCallbackHttp_LWS_CALLBACK_CLOSED
    (struct libwebsocket_context *context, struct libwebsocket *wsi,
     enum libwebsocket_callback_reasons reason, void *user, void *in, size_t len) {
        int result = 0;
        return result;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int OnLwsCallbackHttp_LWS_CALLBACK_RECEIVE
    (struct libwebsocket_context *context, struct libwebsocket *wsi,
     enum libwebsocket_callback_reasons reason, void *user, void *in, size_t len) {
        int result = 0;
        const char* chars;
        if ((chars = ((const char*)in)) && (0 < len)) {
            String message(chars, len);
            XOS_LOG_DEBUG("...received \"" << message << "\"");
        }
        return result;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int OnLwsCallbackHttp
    (struct libwebsocket_context *context, struct libwebsocket *wsi,
     enum libwebsocket_callback_reasons reason, void *user, void *in, size_t len) {
        int result = 0;
        switch (reason) {
        //
        // Http
        //
        case LWS_CALLBACK_HTTP:
            XOS_LOG_DEBUG("LWS_CALLBACK_HTTP...");
            result = OnLwsCallbackHttp_LWS_CALLBACK_HTTP(context, wsi, reason, user, in, len);
            break;

        case LWS_CALLBACK_HTTP_WRITEABLE:
            XOS_LOG_DEBUG("LWS_CALLBACK_HTTP_WRITEABLE...");
            result = OnLwsCallbackHttp_LWS_CALLBACK_HTTP_WRITEABLE(context, wsi, reason, user, in, len);
            break;

        case LWS_CALLBACK_HTTP_FILE_COMPLETION:
            XOS_LOG_DEBUG("LWS_CALLBACK_HTTP_FILE_COMPLETION...");
            result = OnLwsCallbackHttp_LWS_CALLBACK_HTTP_FILE_COMPLETION(context, wsi, reason, user, in, len);
            break;

        case LWS_CALLBACK_CLOSED_HTTP:
            XOS_LOG_DEBUG("LWS_CALLBACK_CLOSED_HTTP...");
            result = OnLwsCallbackHttp_LWS_CALLBACK_CLOSED_HTTP(context, wsi, reason, user, in, len);
            break;

        //
        // Filter
        //
        case LWS_CALLBACK_FILTER_PROTOCOL_CONNECTION:
            XOS_LOG_DEBUG("LWS_CALLBACK_FILTER_PROTOCOL_CONNECTION...");
            result = OnLwsCallbackHttp_LWS_CALLBACK_FILTER_PROTOCOL_CONNECTION(context, wsi, reason, user, in, len);
            break;

        case LWS_CALLBACK_FILTER_NETWORK_CONNECTION:
            XOS_LOG_DEBUG("LWS_CALLBACK_FILTER_NETWORK_CONNECTION...");
            result = OnLwsCallbackHttp_LWS_CALLBACK_FILTER_NETWORK_CONNECTION(context, wsi, reason, user, in, len);
            break;

        //
        // Client
        //
        case LWS_CALLBACK_CLIENT_CONNECTION_ERROR:
            XOS_LOG_DEBUG("LWS_CALLBACK_CLIENT_CONNECTION_ERROR...");
            result = OnLwsCallbackHttp_LWS_CALLBACK_CLIENT_CONNECTION_ERROR(context, wsi, reason, user, in, len);
            break;

        case LWS_CALLBACK_CLIENT_FILTER_PRE_ESTABLISH:
            XOS_LOG_DEBUG("LWS_CALLBACK_CLIENT_FILTER_PRE_ESTABLISH...");
            result = OnLwsCallbackHttp_LWS_CALLBACK_CLIENT_FILTER_PRE_ESTABLISH(context, wsi, reason, user, in, len);
            break;

        case LWS_CALLBACK_CLIENT_ESTABLISHED:
            XOS_LOG_DEBUG("LWS_CALLBACK_CLIENT_ESTABLISHED...");
            result = OnLwsCallbackHttp_LWS_CALLBACK_CLIENT_ESTABLISHED(context, wsi, reason, user, in, len);
            break;

        //
        // Other
        //
        case LWS_CALLBACK_ESTABLISHED:
            XOS_LOG_DEBUG("LWS_CALLBACK_ESTABLISHED...");
            result = OnLwsCallbackHttp_LWS_CALLBACK_ESTABLISHED(context, wsi, reason, user, in, len);
            break;

        case LWS_CALLBACK_CLOSED:
            XOS_LOG_DEBUG("LWS_CALLBACK_CLOSED...");
            result = OnLwsCallbackHttp_LWS_CALLBACK_CLOSED(context, wsi, reason, user, in, len);
            break;

        case LWS_CALLBACK_RECEIVE:
            XOS_LOG_DEBUG("LWS_CALLBACK_RECEIVE...");
            result = OnLwsCallbackHttp_LWS_CALLBACK_RECEIVE(context, wsi, reason, user, in, len);
            break;

        }
        return result;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    static int LwsCallbackHttp
    (struct libwebsocket_context *context, struct libwebsocket *wsi,
     enum libwebsocket_callback_reasons reason, void *user, void *in, size_t len) {
        int result = -1;
        DaemonT* daemon = 0;
        if ((daemon = (DaemonT*)(libwebsocket_context_user(context))))
            result = daemon->OnLwsCallbackHttp(context, wsi, reason, user, in, len);
        return result;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int LwsListenPort() const {
        return this->m_listenPortNo;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual struct libwebsocket_protocols* LwsProtocols() const {
        static struct libwebsocket_protocols lwsProtocols[] = {
            XOS_HTTP_SERVER_LIBWEBSOCKETS_DAEMON_LWS_PROTOCOLS
            XOS_HTTP_SERVER_LIBWEBSOCKETS_DAEMON_LWS_PROTOCOLS_END
        };
        return lwsProtocols;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual struct libwebsocket_extension* LwsExtensions() const {
        struct libwebsocket_extension* lwsExtensions = libwebsocket_get_internal_extensions();
        return lwsExtensions;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    struct HttpSessionData {
        void* data;
    };
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    int m_lwsDebugLevel;
    int m_lwsTimeoutMs;
    String m_lwsEnterNotice;
    String m_lwsExitNotice;
    int m_lwsUid;
    int m_lwsGid;
    Context m_lwsContext;
    ContextCreationInfo m_lwsCreationInfo;
    SendBuffer m_lwsSendBuffer;
};

typedef DaemonT<> Daemon;

} // namespace libwebsockets 
} // namespace server 
} // namespace http 
} // namespace xos 

#endif // _XOS_HTTP_SERVER_LIBWEBSOCKETS_DAEMON_HPP
