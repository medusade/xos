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
///   File: Locker.hpp
///
/// Author: $author$
///   Date: Aug 15, 2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_LOCKER_HPP_
#define _XOS_LOCKER_HPP_

#include "xos/base/Base.hpp"

namespace xos {

template
<class TLocked,
 class TExtend = ExportBase,
 class TImplement = InterfaceBase>

class EXPORT_CLASS Locker: virtual public TImplement, public TExtend {
public:
    typedef TImplement Implements;
    typedef TExtend Extends;
    typedef TLocked LockedT;
    Locker(LockedT& locked, mseconds_t waitMilliseconds): m_locked(locked) {
        if (!(m_locked.TimedLock(waitMilliseconds))){
            Error error(Error::Failed);
            throw(error);
        }
    }
    Locker(LockedT& locked): m_locked(locked) {
        if (!(m_locked.Lock())){
            Error error(Error::Failed);
            throw(error);
        }
    }
    virtual ~Locker(){
        if (!(m_locked.Unlock())) {
            Error error(Error::Failed);
            throw(error);
        }
    }
protected:
    LockedT& m_locked;
};

} // namespace xos

#endif // _XOS_LOCKER_HPP_ 
