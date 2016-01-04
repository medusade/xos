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
///   Date: 6/15/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_INET_HTTP_SERVER_LIBWEBSOCKETS_MEDUSA_DAEMON_HPP
#define _XOS_INET_HTTP_SERVER_LIBWEBSOCKETS_MEDUSA_DAEMON_HPP

#include "xos/inet/http/server/libwebsockets/Daemon.hpp"
#include "xos/inet/http/server/medusa/Daemon.hpp"

#define XOS_HTTP_SERVER_LIBWEBSOCKETS_MEDUSA_DAEMON_LISTEN_PORT_INCREMENT 1

namespace xos {
namespace http {
namespace server {
namespace libwebsockets {
namespace medusa {

typedef server::medusa::DaemonImplement DaemonImplement;
typedef libwebsockets::DaemonT
<server::medusa::Daemon, DaemonImplement> DaemonExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Daemon
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Daemon: virtual public DaemonImplement, public DaemonExtend {
public:
    typedef DaemonImplement Implements;
    typedef DaemonExtend Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Daemon(server::Processor& delegatedToProcessor)
    : Extends(delegatedToProcessor),
      m_lwsListenPortIncrement
      (XOS_HTTP_SERVER_LIBWEBSOCKETS_MEDUSA_DAEMON_LISTEN_PORT_INCREMENT) {
    }
    virtual ~Daemon() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int BeforeRunLwsServer(int argc, char** argv, char** env) {
        int err = 0;
        if ((err = BeforeRunMedusaServer(argc, argv, env))) {
            XOS_LOG_ERROR("failed on BeforeRunMedusaServer()");
        }
        return err;
    }
    virtual int AfterRunLwsServer(int argc, char** argv, char** env) {
        int err = 0;
        if ((err = AfterRunMedusaServer(argc, argv, env))) {
            XOS_LOG_ERROR("failed on AfterRunMedusaServer()");
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int LwsListenPort() const {
        return this->m_listenPortNo + m_lwsListenPortIncrement;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    int m_lwsListenPortIncrement;
};

} // namespace medusa 
} // namespace libwebsockets 
} // namespace server 
} // namespace http 
} // namespace xos 

#endif // _XOS_INET_HTTP_SERVER_LIBWEBSOCKETS_MEDUSA_DAEMON_HPP 
