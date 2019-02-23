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
///   File: Waiter.hpp
///
/// Author: $author$
///   Date: 4/14/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_MT_WAITER_HPP
#define _XOS_MT_WAITER_HPP

#include "xos/base/Base.hpp"

namespace xos {
namespace mt {
namespace wait {

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
typedef seconds_t Seconds;
typedef mseconds_t MSeconds;
typedef useconds_t USeconds;
enum {
    Forever = -1,
    Now = 0
};

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
typedef int Status;
enum {
    Success,
    Failed,
    Busy,
    Interrupted,
    Invalid
};

} // namespace wait

///////////////////////////////////////////////////////////////////////
///  Class: WaiterT
///////////////////////////////////////////////////////////////////////
template <class TImplement = InterfaceBase>

class _EXPORT_CLASS WaiterT: virtual public TImplement {
public:
    typedef TImplement Implements;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Wait() = 0;
    virtual wait::Status TryWait() = 0;
    virtual wait::Status TimedWait(mseconds_t waitMilliSeconds) = 0;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef WaiterT<> Waiter;

///////////////////////////////////////////////////////////////////////
///  Class: WaiterImplementT
///////////////////////////////////////////////////////////////////////
template <class TImplement = Waiter>

class _EXPORT_CLASS WaiterImplementT: virtual public TImplement {
public:
    typedef TImplement Implements;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Continue() { return true; }
    virtual bool Wait() { return true; }
    virtual wait::Status TryWait() { return wait::Success; }
    virtual wait::Status TimedWait(mseconds_t waitMilliSeconds) { return wait::Success; }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef WaiterImplementT<> WaiterImplement;

///////////////////////////////////////////////////////////////////////
///  Class: WaitT
///////////////////////////////////////////////////////////////////////
template <class TWaiter = Waiter, class TExtend = ExportBase, class TImplement = InterfaceBase>
class _EXPORT_CLASS WaitT: virtual public TImplement, public TExtend {
public:
    typedef TImplement Implements;
    typedef TExtend Extends;
    typedef TWaiter Waiter;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    WaitT(Waiter& waiter, mseconds_t waitMilliSeconds) {
        wait::Status status;
        if (wait::Success != (status = waiter.TimedWait(waitMilliSeconds))) {
            throw (status);
        }
    }
    WaitT(Waiter& waiter) {
        if (!(waiter.Wait())) {
            wait::Status status = wait::Failed;
            throw (status);
        }
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

typedef WaitT<> Wait;

} // namespace mt
} // namespace xos 

#endif // _XOS_MT_WAITER_HPP 
