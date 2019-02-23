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
///   File: DispatcherType.hpp
///
/// Author: $author$
///   Date: 2/26/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_JAVAX_SERVLET_DISPATCHERTYPE_HPP
#define _XOS_JAVAX_SERVLET_DISPATCHERTYPE_HPP

#include "xos/jdk/java/lang/Enum.hpp"

namespace xos {
namespace javax {
namespace servlet {

class _EXPORT_CLASS DispatcherType;
typedef InterfaceBase DispatcherTypeImplement;
typedef java::lang::Enum<DispatcherType> DispatcherTypeExtend;
///////////////////////////////////////////////////////////////////////
///  Class: DispatcherType
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS DispatcherType
: virtual public DispatcherTypeImplement, public DispatcherTypeExtend {
public:
    typedef DispatcherTypeImplement Implements;
    typedef DispatcherTypeExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    DispatcherType() {
    }
    virtual ~DispatcherType() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int_t compareTo(const DispatcherType& to) const {
        return 1;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

///////////////////////////////////////////////////////////////////////
///  Class: NullDispatcherType
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS NullDispatcherType
: virtual public DispatcherTypeImplement, public DispatcherType {
public:
    typedef DispatcherTypeImplement Implements;
    typedef DispatcherType Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    NullDispatcherType() {
    }
    virtual ~NullDispatcherType() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace servlet
} // namespace javax 
} // namespace xos 

#endif // _XOS_JAVAX_SERVLET_DISPATCHERTYPE_HPP 
