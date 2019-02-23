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
///   Date: 4/18/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_IO_LOCKER_HPP
#define _XOS_IO_LOCKER_HPP

#include "xos/mt/Locker.hpp"

namespace xos {
namespace io {

///////////////////////////////////////////////////////////////////////
///  Class: LockerT
///////////////////////////////////////////////////////////////////////
template <class TImplement = mt::Locker>
class _EXPORT_CLASS LockerT: virtual public TImplement {
public:
    typedef TImplement Implements;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Lock() {
        LockerT* locker;
        if ((locker = DelegatedToLocker()))
            return locker->Lock();
        return true; }
    virtual bool Unlock() {
        LockerT* locker;
        if ((locker = DelegatedToLocker()))
            return locker->Unlock();
        return true; }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual mt::wait::Status TryLock() {
        LockerT* locker;
        if ((locker = DelegatedToLocker()))
            return locker->TryLock();
        return mt::wait::Success; }
    virtual mt::wait::Status TimedLock(mseconds_t waitMilliseconds) {
        LockerT* locker;
        if ((locker = DelegatedToLocker()))
            return locker->TimedLock(waitMilliseconds);
        return mt::wait::Success; }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual LockerT* DelegateToLocker(LockerT* locker) { return 0; }
    virtual LockerT* DelegatedToLocker() const { return 0; }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef LockerT<> Locker;

} // namespace io 
} // namespace xos 

#endif // _XOS_IO_LOCKER_HPP 
