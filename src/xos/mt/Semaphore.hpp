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
#ifndef _XOS_MT_SEMAPHORE_HPP
#define _XOS_MT_SEMAPHORE_HPP

#include "xos/mt/Acquirer.hpp"
#include "xos/mt/Waiter.hpp"
#include "xos/base/Creator.hpp"

namespace xos {
namespace mt {

///////////////////////////////////////////////////////////////////////
///  Class: SemaphoreImplements
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS SemaphoreImplements
: virtual public Waiter, virtual public Acquirer, virtual public Creator {
public:
};
///////////////////////////////////////////////////////////////////////
///  Class: SemaphoreT
///////////////////////////////////////////////////////////////////////
template <class TImplement = SemaphoreImplements >
class _EXPORT_CLASS SemaphoreT: virtual public TImplement {
public:
    typedef TImplement Implements;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Create(size_t initialCount) = 0;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Wait() {
        return this->Acquire();
    }
    virtual wait::Status TryWait() {
        return this->TryAcquire();
    }
    virtual wait::Status TimedWait(mseconds_t waitMilliSeconds) {
        return this->TimedAcquire(waitMilliSeconds);
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool InitiallyCreated() const { return true; }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef SemaphoreT<> Semaphore;

} // namespace mt 
} // namespace xos 

#endif // _XOS_MT_SEMAPHORE_HPP 
