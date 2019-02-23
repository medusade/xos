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
///   File: Daemon.hpp
///
/// Author: $author$
///   Date: 5/25/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_INET_HTTP_SERVER_MEDUSA_DAEMON_HPP
#define _XOS_INET_HTTP_SERVER_MEDUSA_DAEMON_HPP

#include "xos/inet/http/server/medusa/method/GetProcessor.hpp"
#include "xos/inet/http/server/medusa/method/Processor.hpp"
#include "xos/inet/http/server/medusa/TcpServer.hpp"
#include "xos/inet/http/server/medusa/TcpConnection.hpp"
#include "xos/inet/http/server/medusa/Processor.hpp"
#include "xos/inet/http/server/Daemon.hpp"
#include "xos/inet/http/FormReader.hpp"
#include "xos/inet/http/Response.hpp"
#include "xos/inet/http/Request.hpp"

namespace xos {
namespace http {
namespace server {
namespace medusa {

///////////////////////////////////////////////////////////////////////
///  Class: DaemonImplement
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS DaemonImplement
: virtual public server::DaemonImplement, virtual public medusa::Processor {
};
typedef server::Daemon DaemonExtend;
///////////////////////////////////////////////////////////////////////
///  Class: DaemonT
///////////////////////////////////////////////////////////////////////
template
<class TExtend = DaemonExtend,
 class TImplement = DaemonImplement>

class _EXPORT_CLASS DaemonT: virtual public TImplement, public TExtend {
public:
    typedef TImplement Implements;
    typedef TExtend Extends;
    typedef xos::Daemon::Locker Locker;
    using Extends::Process;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    DaemonT(server::Processor& delegatedToProcessor): Extends(delegatedToProcessor) {
    }
    DaemonT() {
    }
    virtual ~DaemonT() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int RunServer(int argc, char** argv, char** env) {
        int err = 0;
        if (!(err = BeforeRunMedusaServer(argc, argv, env))) {
            int err2;

            err = RunMedusaServer(argc, argv, env);

            if ((err2 = AfterRunMedusaServer(argc, argv, env))) {
                if (!err)
                    err = err2;
            }
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int RunMedusaServer(int argc, char** argv, char** env) {
        int err = 0;
        return err;
    }
    virtual int BeforeRunMedusaServer(int argc, char** argv, char** env) {
        int err = 1;
        TcpServerConfig* tcpServerConfig;

        if ((tcpServerConfig = new TcpServerConfig
            (this->m_documentRoot, this->m_listenHost, this->m_listenPortNo))) {
            TcpServer* tcpServer;

            if ((tcpServer = new TcpServer(*this, *tcpServerConfig))) {

                XOS_LOG_DEBUG("tcpServer->Start()...");
                if ((tcpServer->Start())) {

                    XOS_LOG_DEBUG("...tcpServer->Start()");
                    m_tcpServerConfigs.push_back(tcpServerConfig);
                    m_tcpServers.push_back(tcpServer);
                    return 0;
                } else {
                    XOS_LOG_ERROR("...failed on tcpServer->Start()");
                }
                delete tcpServer;
            }
            delete tcpServerConfig;
        }
        return err;
    }
    virtual int AfterRunMedusaServer(int argc, char** argv, char** env) {
        int err = 0;
        TcpServer* tcpServer;

        while ((tcpServer = BackTcpServer())) {
            XOS_LOG_DEBUG("tcpServer->Finish()...");
            if (tcpServer->Finish()) {
                XOS_LOG_DEBUG("...tcpServer->Finish()");
            } else {
                XOS_LOG_ERROR("...failed on tcpServer->Finish()");
            }
            if ((tcpServer = PullTcpServer())) {
                delete tcpServer;
            }
        }

        while (m_tcpServerConfigs.begin() != m_tcpServerConfigs.end()) {
            TcpServerConfig* tcpServerConfig = m_tcpServerConfigs.back();
            m_tcpServerConfigs.pop_back();
            delete tcpServerConfig;
        }
        return err;
    }
    virtual TcpServer* BackTcpServer() {
        try {
            volatile Locker lockr(*this);
            if (m_tcpServers.begin() != m_tcpServers.end()) {
                return m_tcpServers.back();
            }
        } catch (const Error& error) {
            XOS_LOG_ERROR("caught error " << error << " on  Locker(*this)");
        }
        return 0;
    }
    virtual TcpServer* PullTcpServer() {
        try {
            volatile Locker lockr(*this);
            if (m_tcpServers.begin() != m_tcpServers.end()) {
                TcpServer* tcpServer = m_tcpServers.back();
                m_tcpServers.pop_back();
                return tcpServer;
            }
        } catch (const Error& error) {
            XOS_LOG_ERROR("caught error " << error << " on  Locker(*this)");
        }
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Process(Response& response, const Request& request) {
        bool processed = false;
        server::Processor* delegatedToProcessor;
        if ((delegatedToProcessor = this->DelegatedToProcessor()))
            processed = delegatedToProcessor->Process(response, request);
        if (!(processed))
            processed = OnProcess(response, request);
        return processed;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool OnProcess(Response& response, const Request& request) {
        http::Request::Method::Which method = request.GetMethodWhich();
        bool processed = false;
        server::Processor* processor;

        XOS_LOG_DEBUG("in...");

        if ((processor = this->DelegatedToProcessor())) {
            if ((processed = processor->Process(response, request))) {
                return true;
            }
        }
        switch(method) {
        case http::Request::Method::Get:
            processed = OnProcessGet(response, request);
            break;
        case http::Request::Method::Post:
            processed = OnProcessPost(response, request);
            break;
        case http::Request::Method::Put:
            processed = OnProcessPut(response, request);
            break;
        case http::Request::Method::Delete:
            processed = OnProcessDelete(response, request);
            break;
        case http::Request::Method::Trace:
            processed = OnProcessTrace(response, request);
            break;
        case http::Request::Method::Connect:
            processed = OnProcessConnect(response, request);
            break;
        case http::Request::Method::Options:
            processed = OnProcessOptions(response, request);
            break;
        case http::Request::Method::Head:
            processed = OnProcessHead(response, request);
            break;
        default:
            processed = OnProcessNone(response, request);
        }
        XOS_LOG_DEBUG("...out");
        return processed;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool OnProcessGet(Response& response, const Request& request) {
        method::Processor& get = method::GetProcessor::GetTheInstance();
        bool processed = false;
        XOS_LOG_DEBUG("in...");
        if (!(processed = get.Process(response, request)))
            processed = OnProcessAny(response, request);
        XOS_LOG_DEBUG("...out");
        return processed;
    }
    virtual bool OnProcessPost(Response& response, const Request& request) {
        bool processed = false;
        XOS_LOG_DEBUG("in...");
        processed = OnProcessAny(response, request);
        XOS_LOG_DEBUG("...out");
        return processed;
    }
    virtual bool OnProcessPut(Response& response, const Request& request) {
        bool processed = false;
        XOS_LOG_DEBUG("in...");
        processed = OnProcessAny(response, request);
        XOS_LOG_DEBUG("...out");
        return processed;
    }
    virtual bool OnProcessDelete(Response& response, const Request& request) {
        bool processed = false;
        XOS_LOG_DEBUG("in...");
        processed = OnProcessAny(response, request);
        XOS_LOG_DEBUG("...out");
        return processed;
    }
    virtual bool OnProcessTrace(Response& response, const Request& request) {
        bool processed = false;
        XOS_LOG_DEBUG("in...");
        processed = OnProcessAny(response, request);
        XOS_LOG_DEBUG("...out");
        return processed;
    }
    virtual bool OnProcessConnect(Response& response, const Request& request) {
        bool processed = false;
        XOS_LOG_DEBUG("in...");
        processed = OnProcessAny(response, request);
        XOS_LOG_DEBUG("...out");
        return processed;
    }
    virtual bool OnProcessOptions(Response& response, const Request& request) {
        bool processed = false;
        XOS_LOG_DEBUG("in...");
        processed = OnProcessAny(response, request);
        XOS_LOG_DEBUG("...out");
        return processed;
    }
    virtual bool OnProcessHead(Response& response, const Request& request) {
        bool processed = false;
        XOS_LOG_DEBUG("in...");
        processed = OnProcessAny(response, request);
        XOS_LOG_DEBUG("...out");
        return processed;
    }
    virtual bool OnProcessAny(Response& response, const Request& request) {
        bool processed = false;
        XOS_LOG_DEBUG("in...");
        processed = OnProcessNone(response, request);
        XOS_LOG_DEBUG("...out");
        return processed;
    }
    virtual bool OnProcessNone(Response& response, const Request& request) {
        bool processed = true;
        XOS_LOG_DEBUG("in...");
        response.line().Set(XOS_HTTP_STATUS_BAD_REQUEST, XOS_HTTP_STATUS_BAD_REQUEST_REASON);
        XOS_LOG_DEBUG("...out");
        return processed;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool OnStop() {
        TcpServers::iterator i;
        TcpServer* s;
        XOS_LOG_DEBUG("stopping severs...");
        for (i = m_tcpServers.begin(); i != m_tcpServers.end(); ++i) {
            if ((s = (*i))) {
                s->Stop();
            }
        }
        return true;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    typedef std::deque<TcpServerConfig*> TcpServerConfigs;
    typedef std::deque<TcpServer*> TcpServers;
protected:
    TcpServerConfigs m_tcpServerConfigs;
    TcpServers m_tcpServers;
};

typedef DaemonT<> Daemon;

} // namespace medusa 
} // namespace server 
} // namespace http 
} // namespace xos 

#endif // _XOS_INET_HTTP_SERVER_MEDUSA_DAEMON_HPP 
