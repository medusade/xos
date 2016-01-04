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
///   File: Acquired.hpp
///
/// Author: $author$
///   Date: 10/6/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_ACQUIRED_HPP
#define _XOS_ACQUIRED_HPP

#include "xos/base/Wait.hpp"
#include "xos/base/Attached.hpp"

namespace xos {

typedef WaitInterface AcquiredInterfaceImplement;

class _EXPORT_CLASS AcquiredInterface: virtual public AcquiredInterfaceImplement {
public:
    virtual bool Acquire() = 0;
    virtual bool Release() = 0;
    virtual bool isAcquired() const = 0;

    virtual ssize_t Acquire(size_t amount) = 0;
    virtual ssize_t Release(size_t amount) = 0;
    virtual ssize_t AmountAcquired() const = 0;

    virtual Status TryAcquire() = 0;
    virtual Status TimedAcquire(mseconds_t waitMilliSeconds) = 0;

    virtual bool Wait() { return Acquire(); }
    virtual bool Continue() { return Release(); }

    virtual Status TryWait(){ return TryAcquire(); }
    virtual Status TimedWait(mseconds_t waitMilliSeconds) 
    { return TimedAcquire(waitMilliSeconds); }
};

} // namespace xos 

#endif // _XOS_ACQUIRED_HPP 
