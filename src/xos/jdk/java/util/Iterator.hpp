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
///   File: Iterator.hpp
///
/// Author: $author$
///   Date: 3/2/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_JAVA_UTIL_ITERATOR_HPP
#define _XOS_JAVA_UTIL_ITERATOR_HPP

#include "xos/jdk/java/Types.hpp"

namespace xos {
namespace java {
namespace util {

typedef InterfaceBase IteratorImplement;
///////////////////////////////////////////////////////////////////////
///  Class: Iterator
///////////////////////////////////////////////////////////////////////
template <typename TElement, class TImplement = IteratorImplement>

class _EXPORT_CLASS Iterator: virtual public TImplement {
public:
    typedef TImplement Implements;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual boolean_t hasNext() const = 0;
    virtual TElement& next() = 0;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace util 
} // namespace java 
} // namespace xos 

#endif // _XOS_JAVA_UTIL_ITERATOR_HPP 
