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
///   File: Enum.hpp
///
/// Author: $author$
///   Date: 2/26/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_JAVA_LANG_ENUM_HPP
#define _XOS_JAVA_LANG_ENUM_HPP

#include "xos/jdk/java/io/Serializable.hpp"
#include "xos/jdk/java/lang/Comparable.hpp"
#include "xos/jdk/java/lang/Object.hpp"
#include "xos/jdk/java/Types.hpp"

namespace xos {
namespace java {
namespace lang {

///////////////////////////////////////////////////////////////////////
///  Class: EnumImplement
///////////////////////////////////////////////////////////////////////
template <typename TEnum>

class _EXPORT_CLASS EnumImplement
: virtual public Comparable<TEnum>,
  virtual public io::Serializable {
public:
};

///////////////////////////////////////////////////////////////////////
///  Class: Enum
///////////////////////////////////////////////////////////////////////
template
<typename TEnum,
 class TImplement = EnumImplement<TEnum>,
 class TExtend = Object>

class _EXPORT_CLASS Enum: virtual public TImplement, public TExtend {
public:
    typedef TImplement Implements;
    typedef TExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Enum() {
    }
    virtual ~Enum() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int_t compareTo(const TEnum& to) const = 0;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace lang 
} // namespace java 
} // namespace xos 

#endif // _XOS_JAVA_LANG_ENUM_HPP 
