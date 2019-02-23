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
///   File: TcpService.hpp
///
/// Author: $author$
///   Date: 5/26/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_INET_HTTP_SERVER_MEDUSA_TCPSERVICE_HPP
#define _XOS_INET_HTTP_SERVER_MEDUSA_TCPSERVICE_HPP

#include "xos/inet/http/server/medusa/TcpServerConfig.hpp"
#include "xos/inet/http/server/medusa/TcpConnection.hpp"
#include "xos/inet/http/server/medusa/Service.hpp"
#include "xos/inet/http/server/medusa/Response.hpp"
#include "xos/inet/http/server/medusa/Request.hpp"
#include "xos/inet/http/server/Processor.hpp"
#include "xos/network/Sockets.hpp"
#include "xos/mt/os/Thread.hpp"
#include "xos/io/Reader2Reader.hpp"

namespace xos {
namespace http {
namespace server {
namespace medusa {

typedef ServiceImplement TcpServiceImplement;
typedef Service TcpServiceExtend;
///////////////////////////////////////////////////////////////////////
///  Class: TcpService
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS TcpService
: virtual public TcpServiceImplement, public TcpServiceExtend {
public:
    typedef TcpServiceImplement Implements;
    typedef TcpServiceExtend Extends;
    using Extends::Process;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    TcpService
    (Processor& processor,
     TcpConnections& connections, const TcpServerConfig& serverConfig)
    : Extends(processor, serverConfig),
      m_serverConfig(serverConfig), m_connections(connections), m_done(false) {
    }
    virtual ~TcpService() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Process
    (TcpConnection& connection, const TcpServerConfig& serverConfig) {
        CharReader2Reader reader2Reader(connection);
        Request request(reader2Reader, serverConfig);
        Response response(request);

        XOS_LOG_DEBUG("read request...");
        if ((Read(request, connection))) {
            XOS_LOG_DEBUG("...read request");

            XOS_LOG_DEBUG("process request...");
            if ((Process(response, request))) {
                XOS_LOG_DEBUG("...processed request");

                XOS_LOG_DEBUG("write response...");
                if ((Write(response, connection))) {
                    XOS_LOG_DEBUG("...wrote response");
                    return true;
                } else {
                    XOS_LOG_DEBUG("failed to write response");
                }
            } else {
                XOS_LOG_DEBUG("...failed to process request");
            }
        } else {
            XOS_LOG_DEBUG("...failed to read request");
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void operator()(){
        XOS_LOG_DEBUG("in...");
        do {
            XOS_LOG_DEBUG("pull connection...");
            try {
                TcpConnection connection = m_connections.Pull();
                XOS_LOG_DEBUG("...pulled connection");

                XOS_LOG_DEBUG("process connection...");
                if ((Process(connection, m_serverConfig))) {
                    XOS_LOG_DEBUG("...processed connection");
                } else {
                    XOS_LOG_DEBUG("...failed to process connection");
                }
            } catch (const mt::wait::Status& s) {
                XOS_LOG_DEBUG("...caught wait status = " << s);
                break;
            } catch (const TcpConnections::Exception& e) {
                XOS_LOG_DEBUG("...caught exception = " << e);
                break;
            }
        } while (!(Done()));
        XOS_LOG_DEBUG("...out");
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Stop() {
        SetDone();
        return m_connections.Stop();
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool SetDone(bool isTrue = true) {
        m_done = isTrue;
        return m_done;
    }
    virtual bool Done() {
        return m_done;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    static void Delete(TcpService* instance) {
        delete instance;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    const TcpServerConfig& m_serverConfig;
    TcpConnections& m_connections;
    bool m_done;
};

} // namespace medusa
} // namespace server 
} // namespace http 
} // namespace xos 

#endif // _XOS_INET_HTTP_SERVER_MEDUSA_TCPSERVICE_HPP 
