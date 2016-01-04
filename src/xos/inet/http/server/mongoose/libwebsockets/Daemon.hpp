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
///   Date: 12/23/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_HTTP_SERVER_MONGOOSE_LIBWEBSOCKETS_DAEMON_HPP
#define _XOS_HTTP_SERVER_MONGOOSE_LIBWEBSOCKETS_DAEMON_HPP

#include "xos/inet/http/server/libwebsockets/Daemon.hpp"
#include "xos/inet/http/server/mongoose/Daemon.hpp"

#define XOS_HTTP_SERVER_MONGOOSE_LIBWEBSOCKETS_DAEMON_LISTEN_PORT_INCREMENT 1

namespace xos {
namespace http {
namespace server {
namespace mongoose {
namespace libwebsockets {

typedef server::libwebsockets::DaemonImplement DaemonImplement;
typedef mongoose::DaemonT
<server::libwebsockets::Daemon, DaemonImplement> DaemonExtend;
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
      (XOS_HTTP_SERVER_MONGOOSE_LIBWEBSOCKETS_DAEMON_LISTEN_PORT_INCREMENT) {
    }
    virtual ~Daemon() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int RunMgServer(int argc, char** argv, char** env) {
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
    virtual int LwsListenPort() const {
        return this->m_listenPortNo + m_lwsListenPortIncrement;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    int m_lwsListenPortIncrement;
};

} // namespace libwebsockets 
} // namespace mongoose 
} // namespace server 
} // namespace http 
} // namespace xos 

#endif // _XOS_HTTP_SERVER_MONGOOSE_LIBWEBSOCKETS_DAEMON_HPP
