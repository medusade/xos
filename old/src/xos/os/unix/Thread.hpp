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
///   File: Thread.hpp
///
/// Author: $author$
///   Date: 10/11/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_OS_UNIX_THREAD_HPP
#define _XOS_OS_UNIX_THREAD_HPP

#include "xos/os/unix/Pthread.hpp"
#include "xos/os/Thread.hpp"
#include "xos/os/Logger.hpp"
#include "xos/base/Created.hpp"

namespace xos {
namespace unix {

typedef xos::Thread ThreadImplement;
typedef ThreadImplement::Status ThreadStatus;
typedef Attached<pthread_t*, int, 0, ExportBase, ThreadImplement> ThreadAttached;
typedef Created<pthread_t*, int, 0, ThreadAttached, ThreadImplement> ThreadExtend;

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Thread: virtual public ThreadImplement, public ThreadExtend {
public:
    typedef ThreadImplement Implements;
    typedef ThreadExtend Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Thread(Run& run): m_run(run), m_isForked(false), m_attrAttachedTo(0) {
        if (!(Create())) {
            XOS_LOG_ERROR("failed on Create()");
            throw (Error(Error::Failed));
        }
    }
    Thread(pthread_t* thread = 0, pthread_attr_t* attr = 0, bool isCreated = false)
    : Extends(thread, isCreated), m_run(NullRun()), m_isForked(false), m_attrAttachedTo(0) {
        if (!(Create())) {
            XOS_LOG_ERROR("failed on Create()");
            throw (Error(Error::Failed));
        }
    }
    virtual ~Thread() {
        if (!(Destroyed())) {
            XOS_LOG_ERROR("failed on Destroyed()");
        }
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Create() {
        if ((Destroyed())) {
            int err = 0;
            if (!(err = pthread_attr_init(&m_attr))) {
                if (!(err = pthread_create(&m_thread, &m_attr, StartRoutine, (void*)(this)))) {
                    Attach(&m_thread, &m_attr, true);
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
            pthread_attr_t* attr = 0;
            bool isCreated = false;
            int err;
            if ((thread = Detach(attr, isCreated))) {
                if (!(err = pthread_attr_destroy(attr))) {
                    return true;
                } else {
                    XOS_LOG_ERROR("failed " << err << " on pthread_attr_destroy()");
                }
            }
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual pthread_t* Attach(pthread_t* thread, pthread_attr_t* attr, bool isCreated) {
        m_attrAttachedTo = attr;
        m_isForked = isCreated;
        return Extends::Attach(thread, isCreated);
    }
    virtual pthread_t* Detach(pthread_attr_t*& attr, bool& isCreated) {
        attr = m_attrAttachedTo;
        m_attrAttachedTo = 0;
        m_isForked = false;
        return Extends::Detach(isCreated);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Joined() {
        if ((m_isForked))
            return Join();
        return true;
    }
    virtual bool Join() {
        pthread_t* thread = 0;
        if ((thread = m_attachedTo)) {
            void* value = 0;
            int err = 0;
            if (!(err =  pthread_join(*thread, &value))) {
                m_isForked = false;
                return true;
            } else {
                XOS_LOG_ERROR("failed " << err << " on pthread_join()");
            }
        }
        return false; 
    }
    virtual Status TryJoin() {
#if defined(PTHREAD_HAS_TRYJOIN)
        pthread_t* thread = 0;
        if ((thread = m_attachedTo)) {
            void* value = 0;
            int err = 0;
            if (!(err =  pthread_tryjoin_np(*thread, &value))) {
                m_isForked = false;
                return Success;
            } else {
                switch(err) {
                case ETIMEDOUT:
                    XOS_LOG_TRACE("timedout " << err << " on pthread_tryjoin_np()");
                    return Busy;
                case EINTR:
                    XOS_LOG_ERROR("interrupted " << err << " on pthread_tryjoin_np()");
                    return Interrupted;
                default:
                    XOS_LOG_ERROR("failed " << err << " on pthread_tryjoin_np()");
                }
            }
        }
        return Failed; 
#else // defined(PTHREAD_HAS_TRYJOIN)
        return Invalid;
#endif // defined(PTHREAD_HAS_TRYJOIN)
    }
    virtual Status TimedJoin(mseconds_t waitMilliseconds) {
        pthread_t* thread = 0;
        void* value = 0;
        int err = 0;
        if ((thread = m_attachedTo)) {
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
                        return Busy;
                    case EINTR:
                        XOS_LOG_ERROR("interrupted " << err << " on pthread_timedjoin_np()");
                        return Interrupted;
                    default:
                        XOS_LOG_ERROR("failed " << err << " on pthread_timedjoin_np()");
                    }
                } else {
                    m_isForked = false;
                    return Success;
                }
#else // defined(PTHREAD_HAS_TIMEDJOIN)
                return Invalid;
#endif // defined(PTHREAD_HAS_TIMEDJOIN)
            } else {
                if (0 == waitMilliseconds) {
#if defined(PTHREAD_HAS_TRYJOIN)
                    if ((err =  pthread_tryjoin_np(*thread, &value))) {
                        switch(err) {
                        case ETIMEDOUT:
                            XOS_LOG_TRACE("timedout " << err << " on pthread_tryjoin_np()");
                            return Busy;
                        case EINTR:
                            XOS_LOG_ERROR("interrupted " << err << " on pthread_tryjoin_np()");
                            return Interrupted;
                        default:
                            XOS_LOG_ERROR("failed " << err << " on pthread_tryjoin_np()");
                        }
                    } else {
                        m_isForked = false;
                        return Success;
                    }
#else // defined(PTHREAD_HAS_TRYJOIN)
                    return Invalid;
#endif // defined(PTHREAD_HAS_TRYJOIN)
                } else {
                    if ((err =  pthread_join(*thread, &value))) {
                        XOS_LOG_ERROR("failed " << err << " on pthread_join()");
                    } else {
                        m_isForked = false;
                        return Success;
                    }
                }
            }
        }
        return Failed; 
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    static void* StartRoutine(void* param) {
        void* result = 0;
        Thread* t = 0;
        XOS_LOG_TRACE("in...");
        if ((t = (Thread*)(param))) {
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
    bool m_isForked;
    pthread_attr_t* m_attrAttachedTo;
    pthread_attr_t m_attr;
    pthread_t m_thread;
};

} // namespace unix 
} // namespace xos 

#endif // _XOS_OS_UNIX_THREAD_HPP 
