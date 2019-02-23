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
///   File: Thread.hpp
///
/// Author: $author$
///   Date: 4/15/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_MT_UNIX_THREAD_HPP
#define _XOS_MT_UNIX_THREAD_HPP

#include "xos/mt/Thread.hpp"
#include "xos/base/Creator.hpp"
#include "xos/base/Attacher.hpp"
#include "xos/os/Logger.hpp"

#include <pthread.h>
#include <time.h>
#include <errno.h>

#if defined(_POSIX_TIMEOUTS) && (_POSIX_TIMEOUTS >=0 )
#if !defined(PTHREAD_HAS_TRYJOIN)
#define PTHREAD_HAS_TRYJOIN
#endif // !defined(PTHREAD_HAS_TRYJOIN)
#if !defined(PTHREAD_HAS_TIMEDJOIN)
#define PTHREAD_HAS_TIMEDJOIN
#endif // !defined(PTHREAD_HAS_TIMEDJOIN)
#endif // defined(_POSIX_TIMEOUTS) && (_POSIX_TIMEOUTS >=0 )

namespace xos {
namespace mt {
namespace unix {

typedef CreatorImplementT<mt::Thread> ThreadAttacherImplement;
typedef ExportBase ThreadAttachedExtend;
typedef pthread_t* ThreadAttachedT;
typedef AttacherT<pthread_t*, int, 0, ThreadAttacherImplement> ThreadAttacher;
typedef AttachedT<pthread_t*, int, 0, ThreadAttacher, ThreadAttachedExtend> ThreadAttached;
typedef CreatedT<pthread_t*, int, 0, ThreadAttacher, ThreadAttached> ThreadCreated;
typedef ThreadAttacher ThreadImplements;
typedef ThreadCreated ThreadExtends;
///////////////////////////////////////////////////////////////////////
///  Class: ThreadT
///////////////////////////////////////////////////////////////////////
template
<class TAttached = ThreadAttachedT,
 class TExtend = ThreadExtends,
 class TImplement = ThreadImplements>

class _EXPORT_CLASS ThreadT: virtual public TImplement, public TExtend {
public:
    typedef TImplement Implements;
    typedef TExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    ThreadT(ThreadAttachedT attachedTo, bool isCreated)
    : Extends(attachedTo, isCreated), m_run(*this), m_forked(isCreated) {
    }
    ThreadT(ThreadAttachedT attachedTo)
    : Extends(attachedTo), m_run(*this), m_forked(false) {
    }
    ThreadT(Run& run, bool initiallySuspended): m_run(run), m_forked(false) {
        if (!(Create(initiallySuspended))) {
            Creator::Exception e = Creator::FailedToCreate;
            throw (e);
        }
    }
    ThreadT(bool initiallySuspended): m_run(*this), m_forked(false) {
        if (!(Create(initiallySuspended))) {
            Creator::Exception e = Creator::FailedToCreate;
            throw (e);
        }
    }
    ThreadT(Run& run): m_run(run), m_forked(false) {
        if (!(Create())) {
            Creator::Exception e = Creator::FailedToCreate;
            throw (e);
        }
    }
    ThreadT(): m_run(*this), m_forked(false) {
        if (!(Create())) {
            Creator::Exception e = Creator::FailedToCreate;
            throw (e);
        }
    }
    virtual ~ThreadT() {
        if (!(this->Destroyed())) {
            Creator::Exception e = Creator::FailedToDestroy;
            throw (e);
        }
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Create(bool initiallySuspended) {
        if (!(initiallySuspended))
            return this->Create();
        return false;
    }
    virtual bool Create() {
        if ((this->Destroyed())) {
            int err = 0;
            if (!(err = pthread_attr_init(&m_attr))) {
                if (!(err = pthread_create(&m_thread, &m_attr, StartRoutine, (void*)(this)))) {
                    this->AttachCreated(&m_thread, m_forked = true);
                    if ((err = pthread_attr_destroy(&m_attr))) {
                        XOS_LOG_ERROR("failed " << err << " on pthread_attr_destroy()");
                    }
                    return true;
                } else {
                    XOS_LOG_ERROR("failed " << err << " on pthread_create()");
                }
                if ((err = pthread_attr_destroy(&m_attr))) {
                    XOS_LOG_ERROR("failed " << err << " on pthread_attr_destroy()");
                }
            } else {
                XOS_LOG_ERROR("failed " << err << " on pthread_attr_init()");
            }
        }
        return false;
    }
    virtual bool Destroy() {
        if ((Joined())) {
            pthread_t* thread = 0;
            bool isCreated = false;
            if ((thread = this->DetachCreated(isCreated))) {
                return true;
            }
        }
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Resume() { return false ; }
    virtual bool Suspend() { return false; }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Joined() {
        if ((m_forked))
            return Join();
        return true;
    }
    virtual bool Join() {
        pthread_t* thread = 0;
        if ((thread = this->m_attachedTo)) {
            void* value = 0;
            int err = 0;
            if (!(err =  pthread_join(*thread, &value))) {
                return true;
            } else {
                XOS_LOG_ERROR("failed " << err << " on pthread_join()");
            }
        }
        return false;
    }
    virtual wait::Status TryJoin() {
#if defined(PTHREAD_HAS_TRYJOIN)
        pthread_t* thread = 0;
        if ((thread = this->m_attachedTo)) {
            void* value = 0;
            int err = 0;
            if ((err =  pthread_tryjoin_np(*thread, &value))) {
                switch(err) {
                case ETIMEDOUT:
                    XOS_LOG_TRACE("timedout " << err << " on pthread_tryjoin_np()");
                    return wait::Busy;
                case EINTR:
                    XOS_LOG_ERROR("interrupted " << err << " on pthread_tryjoin_np()");
                    return wait::Interrupted;
                default:
                    XOS_LOG_ERROR("failed " << err << " on pthread_tryjoin_np()");
                }
            } else {
                return wait::Success;
            }
        }
        return wait::Failed;
#else // defined(PTHREAD_HAS_TRYJOIN)
        XOS_LOG_ERROR("failed invalid on pthread_tryjoin()");
        return wait::Invalid;
#endif // defined(PTHREAD_HAS_TRYJOIN)
    }
    virtual wait::Status TimedJoin(mseconds_t waitMilliseconds) {
        pthread_t* thread = 0;
        void* value = 0;
        int err = 0;
        if ((thread = this->m_attachedTo)) {
            if (0 < waitMilliseconds) {
#if defined(PTHREAD_HAS_TIMEDJOIN)
                struct timespec untilTime;
                clock_gettime(CLOCK_REALTIME, &untilTime);
                untilTime.tv_sec +=  waitMilliseconds/1000;
                untilTime.tv_nsec +=  (waitMilliseconds%1000)*1000;
                if ((err =  pthread_timedjoin_np(*thread, &value, &untilTime))) {
                    switch(err) {
                    case ETIMEDOUT:
                        XOS_LOG_TRACE("timedout " << err << " on pthread_timedjoin_np()");
                        return wait::Busy;
                    case EINTR:
                        XOS_LOG_ERROR("interrupted " << err << " on pthread_timedjoin_np()");
                        return wait::Interrupted;
                    default:
                        XOS_LOG_ERROR("failed " << err << " on pthread_timedjoin_np()");
                    }
                } else {
                    return wait::Success;
                }
#else // defined(PTHREAD_HAS_TIMEDJOIN)
                XOS_LOG_ERROR("failed invalid on pthread_timedjoin()");
                return wait::Invalid;
#endif // defined(PTHREAD_HAS_TIMEDJOIN)
            } else {
                if (0 == waitMilliseconds) {
#if defined(PTHREAD_HAS_TRYJOIN)
                    if ((err =  pthread_tryjoin_np(*thread, &value))) {
                        switch(err) {
                        case ETIMEDOUT:
                            XOS_LOG_TRACE("timedout " << err << " on pthread_tryjoin_np()");
                            return wait::Busy;
                        case EINTR:
                            XOS_LOG_ERROR("interrupted " << err << " on pthread_tryjoin_np()");
                            return wait::Interrupted;
                        default:
                            XOS_LOG_ERROR("failed " << err << " on pthread_tryjoin_np()");
                        }
                    } else {
                        return wait::Success;
                    }
#else // defined(PTHREAD_HAS_TRYJOIN)
                    XOS_LOG_ERROR("failed invalid on pthread_tryjoin()");
                    return wait::Invalid;
#endif // defined(PTHREAD_HAS_TRYJOIN)
                } else {
                    if ((err =  pthread_join(*thread, &value))) {
                        XOS_LOG_ERROR("failed " << err << " on pthread_join()");
                    } else {
                        return wait::Success;
                    }
                }
            }
        }
        return wait::Failed;
    }
protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void operator()() {}
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    static void* StartRoutine(void* param) {
        void* result = 0;
        ThreadT* t = 0;
        XOS_LOG_TRACE("in...");
        if ((t = (ThreadT*)(param))) {
            XOS_LOG_TRACE("t->m_run()...");
            t->m_run();
            XOS_LOG_TRACE("...t->m_run()");
        } else {
            XOS_LOG_ERROR("void* param == 0");
        }
        XOS_LOG_TRACE("...out");
        return result;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    Run& m_run;
    bool m_forked;
    pthread_t m_thread;
    pthread_attr_t m_attr;
};
typedef ThreadT<> Thread;

} // namespace unix 
} // namespace mt 
} // namespace xos 

#endif // _XOS_MT_UNIX_THREAD_HPP 
