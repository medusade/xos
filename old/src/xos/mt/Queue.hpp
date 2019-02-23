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
///   File: Queue.hpp
///
/// Author: $author$
///   Date: 5/25/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_MT_QUEUE_HPP
#define _XOS_MT_QUEUE_HPP

#include "xos/mt/os/Semaphore.hpp"
#include "xos/mt/os/Mutex.hpp"
#include "xos/base/Base.hpp"
#include <deque>

namespace xos {
namespace mt {

typedef Locker QueueLocker;
typedef Waiter QueueWaiter;
///////////////////////////////////////////////////////////////////////
///  Class: QueueImplement
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS QueueImplement
: virtual public QueueLocker, virtual public QueueWaiter {};

typedef ExportBase QueueExtend;
///////////////////////////////////////////////////////////////////////
///  Class: QueueT
///////////////////////////////////////////////////////////////////////
template
<typename TWhat, class TImplement = QueueImplement, class TExtend = QueueExtend>

class _EXPORT_CLASS QueueT: virtual public TImplement, public TExtend {
public:
    typedef TImplement Implements;
    typedef TExtend Extends;
    enum Exception { Empty };
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    QueueT() {
    }
    virtual ~QueueT() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void Add(const TWhat& item) {
        try {
            volatile Locked lock(*this);
            AddLocked(item);
        } catch (const wait::Status& status) {
            if (wait::Failed != (status)) {
                XOS_LOG_TRACE("wait failed " << status);
            } else {
                XOS_LOG_ERROR("wait failed " << status);
            }
            throw (status);
        }
    }
    virtual void Push(const TWhat& item) {
        try {
            volatile Locked lock(*this);
            PushLocked(item);
        } catch (const wait::Status& status) {
            if (wait::Failed != (status)) {
                XOS_LOG_TRACE("wait failed " << status);
            } else {
                XOS_LOG_ERROR("wait failed " << status);
            }
            throw (status);
        }
    }
    virtual TWhat Pop() {
        try {
            volatile mt::Wait wait(*this);
            try {
                volatile Locked lock(*this);
                return PopLocked();
            } catch (const wait::Status& status) {
                if (wait::Failed != (status)) {
                    XOS_LOG_TRACE("wait failed " << status);
                } else {
                    XOS_LOG_ERROR("wait failed " << status);
                }
                throw (status);
            }
        } catch(const Exception& e) {
            XOS_LOG_ERROR("caught Exception = " << e);
            throw (e);
        }
    }
    virtual TWhat Pull() {
        try {
            volatile mt::Wait wait(*this);
            try {
                volatile Locked lock(*this);
                return PullLocked();
            } catch (const wait::Status& status) {
                if (wait::Failed != (status)) {
                    XOS_LOG_TRACE("wait failed " << status);
                } else {
                    XOS_LOG_ERROR("wait failed " << status);
                }
                throw (status);
            }
        } catch(const Exception& e) {
            XOS_LOG_ERROR("caught Exception = " << e);
            throw (e);
        }
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void AddLocked(const TWhat& item) {
        m_deque.push_back(item);
        Continue();
    }
    virtual void PushLocked(const TWhat& item) {
        m_deque.push_front(item);
        Continue();
    }
    virtual TWhat PopLocked() {
        if (!(m_deque.empty())) {
            TWhat item = m_deque.front();
            m_deque.pop_front();
            return item;
        }
        throw (Empty);
    }
    virtual TWhat PullLocked() {
        if (!(m_deque.empty())) {
            TWhat item = m_deque.back();
            m_deque.pop_back();
            return item;
        }
        throw (Empty);
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Stop() {
        return m_sem.Destroy();
    }
    virtual bool Continue() {
        return m_sem.Release();
    }
    virtual bool Wait() {
        return m_sem.Acquire();
    }
    virtual wait::Status TryWait() {
        return m_sem.TryAcquire();
    }
    virtual wait::Status TimedWait(mseconds_t waitMilliSeconds) {
        return m_sem.TimedAcquire(waitMilliSeconds);
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Lock() {
        return m_mtx.Lock();
    }
    virtual bool Unlock() {
        return m_mtx.Unlock();
    }
    virtual wait::Status TryLock() {
        return m_mtx.TryLock();
    }
    virtual wait::Status TimedLock(mseconds_t waitMilliseconds) {
        return m_mtx.TimedLock(waitMilliseconds);
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    std::deque<TWhat> m_deque;
    os::Mutex m_mtx;
    os::Semaphore m_sem;
};

} // namespace mt 
} // namespace xos 

#endif // _XOS_MT_QUEUE_HPP 
