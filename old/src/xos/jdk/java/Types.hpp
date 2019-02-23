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
///   File: Types.hpp
///
/// Author: $author$
///   Date: 2/24/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_JAVA_TYPES_HPP
#define _XOS_JAVA_TYPES_HPP

#include "xos/base/String.hpp"
#include "xos/base/Base.hpp"

namespace xos {
namespace java {

typedef int8_t byte_t;
typedef int16_t short_t;
typedef int32_t int_t;
typedef int64_t long_t;
typedef float float_t;
typedef double double_t;
typedef bool boolean_t;
typedef wchar_t char_t;
typedef StringT<char_t> string_t;
typedef StringT<char> cstring_t;
typedef StringT<tchar_t> tstring_t;
typedef StringT<wchar_t> wstring_t;

} // namespace java
namespace javax {

typedef java::byte_t byte_t;
typedef java::short_t short_t;
typedef java::int_t int_t;
typedef java::long_t long_t;
typedef java::float_t float_t;
typedef java::double_t double_t;
typedef java::boolean_t boolean_t;
typedef java::char_t char_t;
typedef java::string_t string_t;
typedef java::cstring_t cstring_t;
typedef java::tstring_t tstring_t;
typedef java::wstring_t wstring_t;

} // namespace javax
} // namespace xos

#endif // _XOS_JAVA_TYPES_HPP 
