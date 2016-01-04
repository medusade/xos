////////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2013 $organization$
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
///   File: Named.hpp
///
/// Author: $author$
///   Date: 11/26/2013
////////////////////////////////////////////////////////////////////////
#ifndef _XOS_BASE_NAMED_HPP
#define _XOS_BASE_NAMED_HPP

#include "xos/base/String.hpp"
#include <deque>
#include <list>
#include <vector>

namespace xos {

template
<typename TName = String, typename TValue = String,
 class TExtend = Base, class TImplement = InterfaceBase>
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS NamedT: virtual public TImplement, public TExtend {
public:
    typedef TImplement Implements;
    typedef TExtend Extends;
    typedef TName NameT;
    typedef TValue ValueT;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    NamedT(const NameT& name, const ValueT& value)
    : m_name(name), m_value(value) {
    }
    NamedT(const NamedT& copy)
    : m_name(copy.m_name), m_value(copy.m_value) {
    }
    NamedT() {
    }
    virtual ~NamedT()  {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const NameT& SetName(const NameT& to) {
        m_name = to;
        return m_name;
    }
    virtual const NameT& GetName() const {
        return m_name;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ValueT& SetValue(const ValueT& to) {
        m_value = to;
        return m_value;
    }
    virtual const ValueT& GetValue() const {
        return m_value;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int CompareName(const NameT& to) const {
        return m_name.Compare(to);
    }
    ///////////////////////////////////////////////////////////////////////
    virtual NameT& name() const {
        return (NameT&)(m_name);
    }
    virtual ValueT& value() const {
        return (ValueT&)(m_value);
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    NameT m_name;
    ValueT m_value;
};

typedef NamedT<String, String> Named;
typedef std::deque<Named> NamedQueue;
typedef std::list<Named> NamedList;
typedef std::vector<Named> NamedVector;

} // namespace xos

#endif // _XOS_BASE_NAMED_HPP 
