///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2012 $organization$
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
///   File: Process.hpp
///
/// Author: $author$
///   Date: 10/11/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_OS_UNIX_PROCESS_HPP
#define _XOS_OS_UNIX_PROCESS_HPP

#include "xos/os/Process.hpp"
#include "xos/os/Logger.hpp"
#include "xos/base/Created.hpp"
#include "xos/base/Wrapped.hpp"
#include "xos/base/String.hpp"
#include "xos/base/Array.hpp"
#include "thirdparty/gnu/glibc/posix/execvpe.h"

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

namespace xos {
namespace unix {

typedef xos::Process ProcessImplement;
typedef ProcessImplement::Status ProcessStatus;
typedef Attached<pid_t, int, -1, ExportBase, ProcessImplement> ProcessAttached;
typedef Created<pid_t, int, -1, ProcessAttached, ProcessImplement> ProcessExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Process
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Process: virtual public ProcessImplement, public ProcessExtend {
public:
    typedef ProcessImplement Implements;
    typedef ProcessExtend Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Process(const char* path, char** argv, char** env, bool isDetached = false) {
        if (!(Create(path, argv, env, isDetached))) {
            XOS_LOG_ERROR("failed on Create()");
            throw(Error(Error::Failed));
        }
    }
    Process(const char* path, char** argv, bool isDetached = false) {
        if (!(Create(path, argv, isDetached))) {
            XOS_LOG_ERROR("failed on Create()");
            throw(Error(Error::Failed));
        }
    }
    Process(pid_t pid, bool isCreated = false)
    : Extends(pid, isCreated) {}
    virtual ~Process() {
        if (!(Destroyed())) {
            XOS_LOG_ERROR("failed on Destroyed()");
        }
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Create(const char* path, char** argv, char** env, bool isDetached = false) {
        if ((Destroyed())) {
            pid_t pid = (pid_t)(-1);
            bool isCreated = false;

            if ((isCreated = (0 < (pid = fork())))) {
                Attach(pid, isCreated);
                return true;
            } else {
                if (0 == (pid)) {
                    int err = 0;

                    XOS_LOG_TRACE("chlid process...");
                    if ((env)) {
                        if ((err = execvpe(path, argv, env))) {
                            XOS_LOG_ERROR("failed " << errno << "on execvpe(\"" << path << "\",...)");
                        }
                    } else {
                        if ((err = execvp(path, argv))) {
                            XOS_LOG_ERROR("failed " << errno << "on execvpe(\"" << path << "\",...)");
                        }
                    }
                    XOS_LOG_TRACE("...chlid process");
                    exit(err);
                } else {
                    XOS_LOG_ERROR("failed " << errno << "on fork()");
                }
            }
        }
        return false; 
    }
    virtual bool Create(const char* path, char** argv, bool isDetached = false) {
        return Create(path, argv, 0, isDetached); 
    }
    virtual bool Destroy() {
        if ((Join())) {
            Detach();
        }
        return false; 
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Join() {
        pid_t pid = (pid_t)(-1);

        if (0 < (pid = m_attachedTo)) {
            int options = 0;
            int status = 0;

            XOS_LOG_TRACE("wait on waitpid()...");
            if (!(pid != waitpid(pid, &status, options))) {
                XOS_LOG_TRACE("...waited on waitpid()");
                return true;
            } else {
                XOS_LOG_ERROR("...failed " << errno << " on waitpid()");
            }
        }
        return false; 
    }
    virtual Status TryJoin() {
        pid_t pid = (pid_t)(-1);

        if (0 < (pid = m_attachedTo)) {
            int options = WNOHANG;
            int status = 0;

            XOS_LOG_TRACE("wait on waitpid()...");
            if (!(pid != waitpid(pid, &status, options))) {
                XOS_LOG_TRACE("...waited on waitpid()");
                return Success;
            } else {
                XOS_LOG_ERROR("...failed " << errno << " on waitpid()");
            }
        }
        return Failed; 
    }
    virtual Status TimedJoin(mseconds_t waitMilliSeconds) {
        return Invalid; 
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Separate() {
        Detach();
        return true;
    }
};

} // namespace unix 
} // namespace xos 

#endif // _XOS_OS_UNIX_PROCESS_HPP 
