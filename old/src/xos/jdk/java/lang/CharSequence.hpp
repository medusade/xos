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
///   File: CharSequence.hpp
///
/// Author: $author$
///   Date: 2/24/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_JAVA_LANG_CHARSEQUENCE_HPP
#define _XOS_JAVA_LANG_CHARSEQUENCE_HPP

#include "xos/jdk/java/Types.hpp"

namespace xos {
namespace java {
namespace lang {

class _EXPORT_CLASS String;

typedef InterfaceBase CharSequenceImplement;
///////////////////////////////////////////////////////////////////////
///  Class: CharSequence
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS CharSequence: virtual public CharSequenceImplement {
public:
    typedef CharSequenceImplement Implements;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual char_t charAt(int_t index) const = 0;
    virtual int_t length() const = 0;
    virtual String subSequence(int_t start, int_t end) const = 0;
    virtual String toString() const = 0;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace lang 
} // namespace java 
} // namespace xos 

#endif // _XOS_JAVA_LANG_CHARSEQUENCE_HPP 
