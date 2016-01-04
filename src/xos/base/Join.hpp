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
///   File: Join.hpp
///
/// Author: $author$
///   Date: 10/7/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_JOIN_HPP
#define _XOS_JOIN_HPP

#include "xos/base/Wait.hpp"

namespace xos {

typedef WaitInterface JoinInterfaceImplement;

class _EXPORT_CLASS JoinInterface: virtual public JoinInterfaceImplement {
public:
    typedef JoinInterfaceImplement Implements;

    virtual bool Join() = 0;
    virtual bool Separate() = 0;

    virtual Status TryJoin() = 0;
    virtual Status TimedJoin(mseconds_t waitMilliSeconds) = 0;

    virtual bool Wait() { return Join(); }
    virtual bool Continue() { return Separate(); }

    virtual Status TryWait() { return TryJoin(); }
    virtual Status TimedWait(mseconds_t waitMilliSeconds) 
    { return TimedJoin(waitMilliSeconds); }
};

} // namespace xos 

#endif // _XOS_JOIN_HPP 
