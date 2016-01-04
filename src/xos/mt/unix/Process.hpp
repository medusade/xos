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
///   File: Process.hpp
///
/// Author: $author$
///   Date: 9/21/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_MT_UNIX_PROCESS_HPP
#define _XOS_MT_UNIX_PROCESS_HPP

#include "xos/mt/Process.hpp"
#include "xos/base/Creator.hpp"
#include "xos/base/Attacher.hpp"
#include "xos/os/Logger.hpp"
#include "thirdparty/gnu/glibc/posix/execvpe.h"

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

namespace xos {
namespace mt {
namespace unix {

typedef CreatorImplementT<mt::Process> ProcessAttacherImplement;
typedef ExportBase ProcessAttachedExtend;
typedef pid_t ProcessAttachedT;
typedef AttacherT<pid_t, int, -1, ProcessAttacherImplement> ProcessAttacher;
typedef AttachedT<pid_t, int, -1, ProcessAttacher,ProcessAttachedExtend> ProcessAttached;
typedef CreatedT<pid_t, int, -1, ProcessAttacher,ProcessAttached> ProcessCreated;
typedef ProcessAttacher ProcessImplements;
typedef ProcessCreated ProcessExtends;
///////////////////////////////////////////////////////////////////////
///  Class: ProcessT
///////////////////////////////////////////////////////////////////////
template
<typename TChar = char, typename TEnd = TChar, TEnd VEnd = 0,
 class TImplement = ProcessImplements, class TExtend = ProcessExtends>

class _EXPORT_CLASS ProcessT: virtual public TImplement, public TExtend {
public:
    typedef TImplement Implements;
    typedef TExtend Extends;

    typedef TChar CharT;
    typedef TEnd EndT;
    enum { End = VEnd };

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    ProcessT
    (const CharT* path, CharT** argv, CharT** env,
     int* fdup, int** pdup, bool isDetached = false)
    : m_isForked(false) {
        if (!(this->Create(path, argv, env, fdup, pdup, isDetached))) {
            XOS_LOG_ERROR("...throwing Creator::FailedToCreate");
            Creator::Exception e = Creator::FailedToCreate;
            throw (e);
        }
    }
    ProcessT(pid_t pid, bool isCreated = false)
    : Extends(pid, isCreated), m_isForked(isCreated)  {
    }
    ProcessT(): m_isForked(false) {
    }
    virtual ~ProcessT() {
        if (!(this->Destroyed())) {
            XOS_LOG_ERROR("...throwing Creator::FailedToDestroy");
            Creator::Exception e = Creator::FailedToDestroy;
            throw (e);
        }
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Create
    (const CharT* path, CharT** argv, CharT** env,
     int* fdup, int** pdup, bool isDetached = false) {
        if ((this->Destroyed())) {
            pid_t pid = -1;
            if (0 < (pid = this->Fork(path, argv, env, fdup, pdup, isDetached))) {
                this->AttachCreated(pid);
                return true;
            }
        }
        return false;
    }
    virtual bool Destroy() {
        if ((this->Joined())) {
            this->Detach();
            return true;
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual pid_t Fork
    (const CharT* path, CharT** argv, CharT** env,
     int* fdup, int** pdup, bool isDetached = false) {
        pid_t pid = (pid_t)(-1);

        XOS_LOG_TRACE("fork()...");
        if (0 < (pid = fork())) {
            XOS_LOG_TRACE("...fork() pid = " << pid << "");
        } else {
            if (0 > (pid)) {
                XOS_LOG_TRACE("...failed " << errno << "on fork()");
            } else {
                XOS_LOG_TRACE("...fork() in child process...");
                this->Exec(path, argv, env, fdup, pdup, isDetached);
                XOS_LOG_ERROR("...child process exit(1)");
                exit(1);
            }
        }
        return pid;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Exec
    (const CharT* path, CharT** argv, CharT** env,
     int* fdup, int** pdup, bool isDetached = false) {
        if ((path) && (argv)) {
            int err = 0;
            if ((env)) {
                XOS_LOG_TRACE("execvpe(\"" << path << "\", ...)...");
                if ((err = execvpe(path, argv, env))) {
                    XOS_LOG_ERROR("...failed " << errno << "on execvpe(\"" << path << "\",...)");
                }
            } else {
                XOS_LOG_TRACE("execvp(\"" << path << "\", ...)...");
                if ((err = execvp(path, argv))) {
                    XOS_LOG_ERROR("...failed " << errno << "on execvp(\"" << path << "\",...)");
                }
            }
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Joined() {
        if ((this->IsForked())) {
            return Join();
        }
        return true;
    }
    virtual bool Join() {
        return this->Wait();
    }
    virtual wait::Status TryJoin() {
        return this->TryWait();
    }
    virtual wait::Status TimedJoin(mseconds_t waitMilliseconds) {
        return this->TimedWait(waitMilliseconds);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Wait() {
        pid_t pid = (pid_t)(-1);

        if (0 < (pid = this->AttachedTo())) {
            int options = 0;
            int status = 0;

            this->SetIsForked(false);
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
    virtual wait::Status TryWait() {
        pid_t pid = (pid_t)(-1);

        if (0 < (pid = this->AttachedTo())) {
            int options = WNOHANG;
            int status = 0;

            XOS_LOG_TRACE("wait on waitpid()...");
            if (!(pid != waitpid(pid, &status, options))) {
                XOS_LOG_TRACE("...waited on waitpid()");
                this->SetIsForked(false);
                return wait::Success;
            } else {
                if (EBUSY != (errno)) {
                    XOS_LOG_ERROR("...failed " << errno << " on waitpid()");
                    this->SetIsForked(false);
                } else {
                    XOS_LOG_TRACE("...busy " << errno << " on waitpid()");
                    return wait::Busy;
                }
            }
        }
        return wait::Failed;
    }
    virtual wait::Status TimedWait(mseconds_t waitMilliSeconds) {
        XOS_LOG_ERROR("failed timed_waitpid(..., " << waitMilliSeconds << ") unavailable");
        return wait::Invalid;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual pid_t AttachCreated(pid_t detached, bool isCreated = true) {
        detached = Extends::AttachCreated(detached, isCreated);
        this->SetIsForked(isCreated);
        return detached;
    }
    virtual pid_t Attach(pid_t detached) {
        detached = Extends::Attach(detached);
        this->SetIsForked(false);
        return detached;
    }
    virtual pid_t Detach() {
        pid_t detached = Extends::Detach();
        this->SetIsForked(false);
        return detached;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool SetIsForked(bool isTrue = true) {
        m_isForked = isTrue;
        return m_isForked;
    }
    virtual bool IsForked() const {
        return m_isForked;
    }
    virtual bool IsJoined() const {
        return !m_isForked;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    bool m_isForked;
};
typedef ProcessT<> Process;

} // namespace unix 
} // namespace mt 
} // namespace xos 

#endif // _XOS_MT_UNIX_PROCESS_HPP 
