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
///   File: StringBuffer.hpp
///
/// Author: $author$
///   Date: 2/28/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_JAVA_LANG_STRINGBUFFER_HPP
#define _XOS_JAVA_LANG_STRINGBUFFER_HPP

#include "xos/jdk/java/lang/Object.hpp"

namespace xos {
namespace java {
namespace lang {

typedef ObjectImplement StringBufferImplement;
typedef Object StringBufferExtend;
///////////////////////////////////////////////////////////////////////
///  Class: StringBuffer
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS StringBuffer
: virtual public StringBufferImplement, public StringBufferExtend {
public:
    typedef StringBufferImplement Implements;
    typedef StringBufferExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    StringBuffer() {
    }
    virtual ~StringBuffer() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace lang 
} // namespace java 
} // namespace xos 

#endif // _XOS_JAVA_LANG_STRINGBUFFER_HPP 
