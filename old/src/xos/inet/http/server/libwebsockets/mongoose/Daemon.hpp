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
///   Date: 12/8/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_HTTP_SERVER_LIBWEBSOCKETS_MONGOOSE_DAEMON_HPP
#define _XOS_HTTP_SERVER_LIBWEBSOCKETS_MONGOOSE_DAEMON_HPP

#include "xos/inet/http/server/libwebsockets/Daemon.hpp"
#include "xos/inet/http/server/mongoose/Daemon.hpp"

#define XOS_HTTP_SERVER_LIBWEBSOCKETS_MONGOOSE_DAEMON_LISTEN_PORT_INCREMENT 1

namespace xos {
namespace http {
namespace server {
namespace libwebsockets {
namespace mongoose {

typedef server::mongoose::DaemonImplement DaemonImplement;
typedef libwebsockets::DaemonT
<server::mongoose::Daemon, DaemonImplement> DaemonExtend;
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
    : Extends(delegatedToProcessor),
      m_lwsListenPortIncrement
      (XOS_HTTP_SERVER_LIBWEBSOCKETS_MONGOOSE_DAEMON_LISTEN_PORT_INCREMENT) {
    }
    virtual ~Daemon() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int BeforeRunLwsServer(int argc, char** argv, char** env) {
        int err = 0;
        if ((err = BeforeRunMgServer(argc, argv, env))) {
            XOS_LOG_ERROR("failed on BeforeRunMgServer()");
        }
        return err;
    }
    virtual int AfterRunLwsServer(int argc, char** argv, char** env) {
        int err = 0;
        if ((err = AfterRunMgServer(argc, argv, env))) {
            XOS_LOG_ERROR("failed on AfterRunMgServer()");
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

} // namespace mongoose 
} // namespace libwebsockets 
} // namespace server 
} // namespace http 
} // namespace xos 

#endif // _XOS_HTTP_SERVER_LIBWEBSOCKETS_MONGOOSE_DAEMON_HPP 
