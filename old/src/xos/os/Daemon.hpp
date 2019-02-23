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
#ifndef _XOS_OS_DAEMON_HPP
#define _XOS_OS_DAEMON_HPP

#include "xos/os/Main.hpp"
#include "xos/base/Locker.hpp"
#include "xos/base/Locked.hpp"

namespace xos {

typedef MainImplement DaemonImplement;
typedef Main DaemonExtend;
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Daemon
: virtual public UnlockedImplement, virtual public DaemonImplement, public DaemonExtend {
public:
    typedef DaemonImplement Implements;
    typedef DaemonExtend Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Daemon(): m_restart(false), m_stop(false) {
    }
    virtual ~Daemon() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int Run(int argc, char** argv, char** env) {
        int err = 0, err2 = 0;
        do {
            SetStop(false);
            SetRestart(false);
            if (!(err = BeforeRunDaemon(argc, argv,env))) {
                if ((err = RunDaemon(argc, argv, env))) {
                    XOS_LOG_ERROR("failed on RunDaemon()");
                }
                if ((err2 = AfterRunDaemon(argc, argv, env))) {
                    XOS_LOG_ERROR("failed on AfterRunDaemon()");
                    if (!(err)) err = err2;
                }
            } else {
                XOS_LOG_ERROR("failed on BeforeRunDaemon()");
            }
        } while (GetRestart());
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int RunDaemon(int argc, char** argv, char** env) {
        int err = 0;
        return err;
    }
    virtual int BeforeRunDaemon(int argc, char** argv, char** env) {
        int err = 0;
        return err;
    }
    virtual int AfterRunDaemon(int argc, char** argv, char** env) {
        int err = 0;
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Stop() {
        try {
            volatile Locker lockr(*this);
            SetStop();
            return OnStop();
        } catch (const Error& error) {
            XOS_LOG_ERROR("caught error " << error << " on  Locker(*this)");
        }
        return false;
    }
    virtual bool Start() {
        XOS_LOG_ERROR("can't start (already running)");
        return false;
    }
    virtual bool Restart() {
        try {
            volatile Locker lockr(*this);
            SetRestart();
        } catch (const Error& error) {
            XOS_LOG_ERROR("caught error " << error << " on  Locker(*this)");
            return false;
        }
        if ((Stop())) {
            return OnRestart();
        } else {
            try {
                volatile Locker lockr(*this);
                SetRestart(false);
            } catch (const Error& error) {
                XOS_LOG_ERROR("caught error " << error << " on  Locker(*this)");
            }
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool OnStop() {
        return true;
    }
    virtual bool OnRestart() {
        return true;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool SetRestart(bool to = true) {
        m_restart = to;
        return m_restart;
    }
    virtual bool GetRestart() const {
        return m_restart;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual bool SetStop(bool to = true) {
        m_stop = to;
        return m_stop;
    }
    virtual bool GetStop() const {
        return m_stop;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    static Daemon& GetTheInstance();

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    typedef xos::Locker<UnlockedImplement> Locker;
protected:
    bool m_restart, m_stop;
};

} // namespace xos 

#endif // _XOS_OS_DAEMON_HPP 
