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
///   File: Enumeration.hpp
///
/// Author: $author$
///   Date: 2/25/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_JAVA_UTIL_ENUMERATION_HPP
#define _XOS_JAVA_UTIL_ENUMERATION_HPP

#include "xos/jdk/java/Types.hpp"
#include <list>

namespace xos {
namespace java {
namespace util {

///////////////////////////////////////////////////////////////////////
///  Class: Enumeration
///////////////////////////////////////////////////////////////////////
template
<typename TElement, class TExtend = ExportBase, class TImplement = InterfaceBase>

class _EXPORT_CLASS Enumeration: virtual public TImplement, public TExtend {
protected:
    typedef std::list<TElement> List;
    typedef typename List::iterator List_iterator;
    typedef typename List::const_iterator List_const_iterator;
public:
    typedef TImplement Implements;
    typedef TExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Enumeration(const Enumeration& copy)
    : m_list(copy.m_list), m_next(m_list.begin()) {
    }
    Enumeration(): m_next(m_list.begin()) {
    }
    virtual ~Enumeration() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual TElement nextElement() {
        TElement e;
        if (m_next != m_list.end()) {
            return *(m_next++);
        }
        return e;
    }
    virtual boolean_t hasMoreElements() const {
        if (m_next != m_list.end())
            return true;
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    List m_list;
    List_const_iterator m_next;
};

} // namespace util 
} // namespace java 
} // namespace xos 

#endif // _XOS_JAVA_UTIL_ENUMERATION_HPP 
