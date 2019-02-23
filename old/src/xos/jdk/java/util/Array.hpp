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
///   File: Array.hpp
///
/// Author: $author$
///   Date: 2/26/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_JAVA_UTIL_ARRAY_HPP
#define _XOS_JAVA_UTIL_ARRAY_HPP

#include "xos/jdk/java/lang/Object.hpp"
#include "xos/base/Array.hpp"

namespace xos {
namespace java {
namespace util {

///////////////////////////////////////////////////////////////////////
///  Class: Array
///////////////////////////////////////////////////////////////////////
template
<typename TElement,
 class TExtend = ExportBase, class TImplement = InterfaceBase>

class _EXPORT_CLASS Array: virtual public TImplement, public TExtend {
protected:
    typedef xos::Array<TElement> Elements;
public:
    typedef TImplement Implements;
    typedef TExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Array(int_t size): m_element(size) {
    }
    Array(const Array& copy): m_element(copy.m_element) {
    }
    Array() {
    }
    virtual ~Array() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int_t length() const {
        return m_element.Length();
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual TElement& operator[](int_t index) const {
        return (TElement&)(m_element[(0 > index)?(0):(index)]);
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    Elements m_element;
};

} // namespace util 
} // namespace java 
} // namespace xos 

#endif // _XOS_JAVA_UTIL_ARRAY_HPP 
