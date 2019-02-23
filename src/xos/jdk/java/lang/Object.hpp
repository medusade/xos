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
///   File: Object.hpp
///
/// Author: $author$
///   Date: 2/23/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_JAVA_LANG_OBJECT_HPP
#define _XOS_JAVA_LANG_OBJECT_HPP

#include "xos/jdk/java/Types.hpp"

namespace xos {
namespace java {
namespace lang {

typedef InterfaceBase ObjectImplement;
typedef ExportBase ObjectExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Object
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Object: virtual public ObjectImplement, public ObjectExtend {
public:
    typedef ObjectImplement Implements;
    typedef ObjectExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Object() {
    }
    virtual ~Object() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

///////////////////////////////////////////////////////////////////////
///  Class: NullObject
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS NullObject: virtual public ObjectImplement, public Object {
public:
    typedef ObjectImplement Implements;
    typedef Object Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    NullObject() {
    }
    virtual ~NullObject() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace lang
} // namespace java 
} // namespace xos 

#endif // _XOS_JAVA_LANG_OBJECT_HPP 
