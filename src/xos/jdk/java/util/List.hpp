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
///   File: List.hpp
///
/// Author: $author$
///   Date: 3/2/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_JAVA_UTIL_LIST_HPP
#define _XOS_JAVA_UTIL_LIST_HPP

#include "xos/jdk/java/util/Iterator.hpp"
#include "xos/jdk/java/Types.hpp"
#include <list>

namespace xos {
namespace java {
namespace util {

typedef InterfaceBase ListImplement;
typedef ExportBase ListExtend;
///////////////////////////////////////////////////////////////////////
///  Class: List
///////////////////////////////////////////////////////////////////////
template
<typename TElement,
 class TExtend = ListExtend, class TImplement = ListImplement>

class _EXPORT_CLASS List: virtual public TImplement, public TExtend {
protected:
    typedef std::list<TElement> list;
    typedef typename list::iterator list_iterator;
    typedef typename list::const_iterator list_const_iterator;
public:
    typedef TImplement Implements;
    typedef TExtend Extends;

    typedef util::Iterator<TElement> IteratorImplement;
    typedef ExportBase IteratorExtend;
    ///////////////////////////////////////////////////////////////////////
    ///  Class: Iterator
    ///////////////////////////////////////////////////////////////////////
    class _EXPORT_CLASS Iterator
    : virtual public IteratorImplement, public IteratorExtend {
    public:
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        Iterator(const list_iterator& at, const list_const_iterator& end)
        : m_at(at), m_end(end) {
        }
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        virtual boolean_t hasNext() const {
            return (m_at != m_end);
        }
        virtual TElement& next() {
            return *(m_at++);
        }
        virtual bool remove(list& from) {
            if (m_at != from.end()) {
                from.erase(m_at);
                m_end = (m_at = from.end());
                return true;
            }
            return false;
        }
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
    protected:
        list_iterator m_at;
        list_const_iterator m_end;
    };

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    List(const List& copy): m_list(copy.m_list) {
    }
    List() {
    }
    virtual ~List() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual boolean_t add(const TElement& e) {
        m_list.push_back(e);
        return true;
    }
    virtual boolean_t remove(const Iterator& i) {
        return false;
    }
    virtual void clear() {
        m_list.clear();
    }
    virtual boolean_t isEmpty() const {
        return (1 > m_list.size());
    }
    virtual int_t size() const {
        return (int_t)(m_list.size());
    }
    virtual Iterator iterator() const {
        return Iterator(((list&)(m_list)).begin(), m_list.end());
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    list m_list;
};

} // namespace util 
} // namespace java 
} // namespace xos 

#endif // _XOS_JAVA_UTIL_LIST_HPP 
