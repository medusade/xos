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
///   File: Locked.hpp
///
/// Author: $author$
///   Date: Aug 15, 2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_LOCKED_HPP_
#define _XOS_LOCKED_HPP_

#include "xos/base/Attached.hpp"
#include "xos/base/Wait.hpp"

namespace xos {

typedef WaitInterface LockedImplement;
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class EXPORT_CLASS LockedInterface: virtual public LockedImplement {
public:
    typedef LockedImplement Implements;

    virtual bool Lock() = 0;
    virtual bool Unlock() = 0;

    virtual Status TryLock() = 0;
    virtual Status TimedLock(mseconds_t waitMilliseconds) = 0;

    virtual bool Wait() { return Lock(); }
    virtual bool Continue() { return Unlock(); }

    virtual Status TryWait() { return TryLock(); }
    virtual Status TimedWait(mseconds_t waitMilliSeconds) { return TimedLock(waitMilliSeconds); }
};

typedef LockedInterface LockedAttachedImplement;
typedef Attached<LockedInterface*, int, 0, ExportBase, LockedInterface> LockedAttachedExtend;
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class EXPORT_CLASS LockedAttached: virtual public LockedAttachedImplement, public LockedAttachedExtend {
public:
    typedef LockedAttachedExtend Extends;

    LockedAttached(LockedInterface* detached=0):Extends(detached){}

    virtual bool Lock()
    { return (m_attachedTo)?(m_attachedTo->Lock()):(true); }
    virtual bool Unlock()
    { return (m_attachedTo)?(m_attachedTo->Unlock()):(true); }

    virtual Status TryLock()
    { return (m_attachedTo)?(m_attachedTo->TryLock()):(Success); }
    virtual Status TimedLock(mseconds_t waitMilliseconds)
    { return (m_attachedTo)?(m_attachedTo->TimedLock(waitMilliseconds)):(Success); }
};

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class EXPORT_CLASS UnlockedImplement: virtual public LockedInterface {
public:
    typedef LockedInterface Implements;

    virtual bool Lock() { return true; }
    virtual bool Unlock() { return true; }

    virtual Status TryLock() { return Success; }
    virtual Status TimedLock(mseconds_t waitMilliseconds) { return Success; }

    virtual bool Wait() { return Lock(); }
    virtual bool Continue() { return Unlock(); }

    virtual Status TryWait() { return TryLock(); }
    virtual Status TimedWait(mseconds_t waitMilliSeconds) { return TimedLock(waitMilliSeconds); }
};

} // namespace xos

#endif // _XOS_LOCKED_HPP_ 
