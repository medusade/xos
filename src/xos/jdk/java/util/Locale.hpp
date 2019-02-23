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
///   File: Locale.hpp
///
/// Author: $author$
///   Date: 2/26/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_JAVA_UTIL_LOCALE_HPP
#define _XOS_JAVA_UTIL_LOCALE_HPP

#include "xos/jdk/java/lang/Object.hpp"

namespace xos {
namespace java {
namespace util {

typedef java::lang::ObjectImplement LocaleImplement;
typedef java::lang::Object LocaleExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Locale
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Locale: virtual public LocaleImplement,public LocaleExtend {
public:
    typedef LocaleImplement Implements;
    typedef LocaleExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Locale() {
    }
    virtual ~Locale() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

///////////////////////////////////////////////////////////////////////
///  Class: NullLocale
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS NullLocale: virtual public LocaleImplement, public Locale {
public:
    typedef LocaleImplement Implements;
    typedef Locale Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    NullLocale() {
    }
    virtual ~NullLocale() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace util
} // namespace java 
} // namespace xos 

#endif // _XOS_JAVA_UTIL_LOCALE_HPP 
