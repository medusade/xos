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
///   File: Semaphore.hpp
///
/// Author: $author$
///   Date: 4/14/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_MT_MACOSX_SEMAPHORE_HPP
#define _XOS_MT_MACOSX_SEMAPHORE_HPP

#include "xos/mt/Semaphore.hpp"
#include "xos/base/Creator.hpp"
#include "xos/base/Attacher.hpp"
#include "xos/os/Logger.hpp"

#include <mach/task.h>
#include <mach/mach.h>
#include <mach/semaphore.h>

namespace xos {
namespace mt {
namespace macosx {

typedef CreatorImplementT<mt::Semaphore> SemaphoreAttacherImplement;
typedef ExportBase SemaphoreAttachedExtend;
typedef semaphore_t* SemaphoreAttachedT;
typedef AttacherT<semaphore_t*, int, 0, SemaphoreAttacherImplement> SemaphoreAttacher;
typedef AttachedT<semaphore_t*, int, 0, SemaphoreAttacher, SemaphoreAttachedExtend> SemaphoreAttached;
typedef CreatedT<semaphore_t*, int, 0, SemaphoreAttacher, SemaphoreAttached> SemaphoreCreated;
typedef SemaphoreAttacher SemaphoreImplements;
typedef SemaphoreCreated SemaphoreExtends;
///////////////////////////////////////////////////////////////////////
///  Class: SemaphoreT
///////////////////////////////////////////////////////////////////////
template
<class TExtend = SemaphoreExtends,
 class TImplement = SemaphoreImplements>

class _EXPORT_CLASS SemaphoreT: virtual public TImplement, public TExtend {
public:
    typedef TImplement Implements;
    typedef TExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    SemaphoreT
    (semaphore_t* attachedTo, bool isCreated)
    : Extends(attachedTo, isCreated) {
    }
    SemaphoreT
    (semaphore_t* attachedTo)
    : Extends(attachedTo) {
    }
    SemaphoreT(size_t initialCount) {
        if (!(this->Create(initialCount))) {
            Creator::Exception e = Creator::FailedToCreate;
            throw (e);
        }
    }
    SemaphoreT() {
        if (!(this->Create())) {
            Creator::Exception e = Creator::FailedToCreate;
            throw (e);
        }
    }
    virtual ~SemaphoreT() {
        if (!(this->Destroyed())) {
            Creator::Exception e = Creator::FailedToDestroy;
            throw (e);
        }
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Create() {
        return Create(0);
    }
    virtual bool Create(size_t initialCount) {
        if ((this->Destroyed())) {
            task_t task = mach_task_self();
            sync_policy_t syncPolicy = SYNC_POLICY_FIFO;
            bool isCreated = false;
            int err;
            if (isCreated = (KERN_SUCCESS == (err = semaphore_create(task, &m_sem, syncPolicy, initialCount)))) {
                this->AttachCreated(&m_sem);
                return true;
            } else {
                XOS_LOG_ERROR("failed " << err << " on semaphore_create()");
            }
        }
        return false;
    }
    virtual bool Destroy() {
        task_t task = mach_task_self();
        semaphore_t* sem = 0;
        if ((sem = this->Detach())) {
            int err = 0;
            if (KERN_SUCCESS == (err = semaphore_destroy(task, *sem))) {
                return true;
            } else {
                XOS_LOG_ERROR("failed " << err << " on semaphore_destroy()");
            }
        }
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Acquire() {
        semaphore_t* sem = 0;
        if ((sem = this->m_attachedTo)) {
            int err = 0;
            XOS_LOG_TRACE("wait on semaphore_wait()...");
            if (KERN_SUCCESS == (err = semaphore_wait(*sem))) {
                XOS_LOG_TRACE("...waited on semaphore_wait()");
                return true;
            } else {
                XOS_LOG_ERROR("...failed " << err << " on semaphore_wait()");
            }
        }
        return false;
    }
    virtual bool Release() {
        semaphore_t* sem = 0;
        if ((sem = this->m_attachedTo)) {
            int err = 0;
            if (KERN_SUCCESS == (err = semaphore_signal(*sem))) {
                return true;
            } else {
                XOS_LOG_ERROR("failed " << err << " on semaphore_signal()");
            }
        }
        return false;
    }
    virtual wait::Status TryAcquire() {
        return TimedAcquire(0);
    }
    virtual wait::Status TimedAcquire(mseconds_t waitMilliseconds) {
        semaphore_t* sem = 0;
        if ((sem = this->m_attachedTo)) {
            int err = 0;
            if (0 <= (waitMilliseconds)) {
                mach_timespec_t waitTime;
                waitTime.tv_sec = waitMilliseconds/1000;
                waitTime.tv_nsec = (waitMilliseconds%1000)*1000;
                XOS_LOG_TRACE("wait on semaphore_timedwait()...");
                if (KERN_SUCCESS == (err = semaphore_timedwait(*sem, waitTime))) {
                    XOS_LOG_TRACE("...waited on semaphore_timedwait()");
                    return wait::Success;
                } else {
                    if (KERN_OPERATION_TIMED_OUT == (err)) {
                        XOS_LOG_TRACE("...KERN_OPERATION_TIMED_OUT on semaphore_timedwait()");
                        return wait::Busy;
                    } else {
                        if (KERN_ABORTED == (err)) {
                            XOS_LOG_TRACE("...KERN_ABORTED on semaphore_timedwait()");
                            return wait::Interrupted;
                        } else {
                            XOS_LOG_TRACE("...failed " << err << " on semaphore_timedwait()");
                        }
                    }
                }
            } else {
                XOS_LOG_TRACE("wait on semaphore_wait()...");
                if (KERN_SUCCESS == (err = semaphore_wait(*sem))) {
                    XOS_LOG_TRACE("...waited on semaphore_wait()");
                    return wait::Success;
                } else {
                    XOS_LOG_ERROR("...failed " << err << " on semaphore_wait()");
                }
            }
        }
        return wait::Failed;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    semaphore_t m_sem;
};
typedef SemaphoreT<> Semaphore;

} // namespace macosx 
} // namespace mt 
} // namespace xos 

#endif // _XOS_MT_MACOSX_SEMAPHORE_HPP 
