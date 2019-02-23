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
///   File: Wait.hpp
///
/// Author: $author$
///   Date: 10/5/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_WAIT_HPP
#define _XOS_WAIT_HPP

#include "xos/base/Base.hpp"

namespace xos {

typedef InterfaceBase WaitInterfaceImplement;

class _EXPORT_CLASS WaitInterface: virtual public WaitInterfaceImplement {
public:
    typedef WaitInterfaceImplement Implements;

    enum {
        Forever = -1
    };
    enum Status {
        Success,
        Failed,
        Busy,
        Interrupted,
        Invalid
    };

    virtual bool Wait() = 0;
    virtual bool Continue() = 0;

    virtual Status TryWait() = 0;
    virtual Status TimedWait(mseconds_t waitMilliSeconds) = 0;
};


} // namespace xos 


#endif // _XOS_WAIT_HPP 
        

