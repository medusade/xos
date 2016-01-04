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
#ifndef _XOS_SERVER_DAEMON_HPP
#define _XOS_SERVER_DAEMON_HPP

#include "xos/os/Daemon.hpp"

namespace xos {
namespace server {

typedef xos::DaemonImplement DaemonImplement;
typedef xos::Daemon DaemonExtend;
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Daemon: virtual public DaemonImplement, public DaemonExtend {
public:
    typedef DaemonImplement Implements;
    typedef DaemonExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Daemon() {
    }
    virtual ~Daemon() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int RunDaemon(int argc, char** argv, char** env) {
        int err = 0, err2 = 0;
        if (!(err = BeforeRunServer(argc, argv,env))) {
            if ((err = RunServer(argc, argv, env))) {
                XOS_LOG_ERROR("failed on RunServer()");
            }
            if ((err2 = AfterRunServer(argc, argv, env))) {
                XOS_LOG_ERROR("failed on AfterRunServer()");
                if (!(err)) err = err2;
            }
        } else {
            XOS_LOG_ERROR("failed on BeforeRunServer()");
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int RunServer(int argc, char** argv, char** env) {
        int err = 0;
        return err;
    }
    virtual int BeforeRunServer(int argc, char** argv, char** env) {
        int err = 0;
        return err;
    }
    virtual int AfterRunServer(int argc, char** argv, char** env) {
        int err = 0;
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace server 
} // namespace xos 

#endif // _XOS_SERVER_DAEMON_HPP 
