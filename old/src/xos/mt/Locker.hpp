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
///   File: Locker.hpp
///
/// Author: $author$
///   Date: 4/14/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_MT_LOCKER_HPP
#define _XOS_MT_LOCKER_HPP

#include "xos/mt/Waiter.hpp"

namespace xos {
namespace mt {

///////////////////////////////////////////////////////////////////////
///  Class: LockerT
///////////////////////////////////////////////////////////////////////
template <class TImplement = InterfaceBase>

class _EXPORT_CLASS LockerT: virtual public TImplement {
public:
    typedef TImplement Implements;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Lock() = 0;
    virtual bool Unlock() = 0;
    virtual wait::Status TryLock() = 0;
    virtual wait::Status TimedLock(mseconds_t waitMilliseconds) = 0;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef LockerT<> Locker;

///////////////////////////////////////////////////////////////////////
///  Class: LockerImplementT
///////////////////////////////////////////////////////////////////////
template <class TImplement = Locker>

class _EXPORT_CLASS LockerImplementT: virtual public TImplement {
public:
    typedef TImplement Implements;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Lock() { return true; }
    virtual bool Unlock() { return true; }
    virtual wait::Status TryLock() { return wait::Success; }
    virtual wait::Status TimedLock(mseconds_t waitMilliseconds) { return wait::Success; }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef LockerImplementT<> LockerImplement;

///////////////////////////////////////////////////////////////////////
///  Class: LockedT
///////////////////////////////////////////////////////////////////////
template <class TLocker = Locker, class TExtend = ExportBase, class TImplement = InterfaceBase>
class _EXPORT_CLASS LockedT: virtual public TImplement, public TExtend {
public:
    typedef TImplement Implements;
    typedef TExtend Extends;
    typedef TLocker Locker;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    LockedT(Locker& locker, mseconds_t waitMilliSeconds): m_locker(locker) {
        wait::Status status;
        if (wait::Success != (status = m_locker.TimedLock(waitMilliSeconds))) {
            throw (status);
        }
    }
    LockedT(Locker& locker): m_locker(locker) {
        if (!(m_locker.Lock())) {
            wait::Status status = wait::Failed;
            throw (status);
        }
    }
    virtual ~LockedT() {
        if (!(m_locker.Unlock())) {
            wait::Status status = wait::Failed;
            throw (status);
        }
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    Locker& m_locker;
};
typedef LockedT<> Locked;

} // namespace mt
} // namespace xos 

#endif // _XOS_MT_LOCKER_HPP 
