///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2012 $organization$
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
///   File: Reference.hpp
///
/// Author: $author$
///   Date: 10/12/2012
///////////////////////////////////////////////////////////////////////
#ifndef _REFERENCE_HPP
#define _REFERENCE_HPP

#include "xos/base/Base.hpp"

namespace xos {

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class Referenced {
public:
    Referenced(unsigned count): m_count(count) {}
    unsigned Increment() {
        return ++m_count;
    }
    unsigned Decrement() {
        return --m_count;
    }
    static Referenced* New(unsigned count) {
        return new Referenced(count);
    }
    static void Delete(Referenced* reference) {
        delete reference;
    }
protected:
    unsigned m_count;
};

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
template
<class TInstance,
 class TReferenced=Referenced,
 class TExtend=Base>

class Reference: public TExtend {
public:
    typedef TExtend Extends;
    typedef TInstance Instance;
    typedef TReferenced Referenced;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Reference(TInstance* instance=0)
    : m_instance(instance),
      m_referenced(0)
    {
        if (m_instance)
            m_referenced = TReferenced::New(1);
    }
    Reference(const Reference& reference) 
    : m_instance(0),
      m_referenced(0)
    {
        if (reference.m_referenced != 0)
        {
            m_instance = reference.m_instance;
            m_referenced = reference.m_referenced;
            m_referenced->Increment();
        }
    }
    template <class TDerivedInstance>
    Reference(const Reference<TDerivedInstance, TReferenced>& reference) 
    : m_instance(0),
      m_referenced(0)
    {
        TInstance* instance;

        if ((instance = (TInstance*)(reference.operator->())) != 0)
        {
            m_instance = instance;
            m_referenced = reference.m_referenced;
            m_referenced->Increment();
        }
    }
    virtual ~Reference() {
        Clear();
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual Instance* Set(Instance* instance) {
        if ((m_instance = instance)) {
            if ((m_referenced = TReferenced::New(1))) {
                return instance;
            } else {
                m_instance = 0;
            }
        }
        return 0;
    }
    virtual void Clear() {
        if (m_referenced) {
            if (m_instance) {
                if ((m_referenced->Decrement()) == 0) {
                    TReferenced::Delete(m_referenced);
                    Delete(m_instance);
                }
                m_instance = 0;
            }
             m_referenced = 0;
        }
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void Copy(const Reference& reference) {
        Reference& thisReference = *this;
        Clear();
        if (reference.m_referenced) {
            m_instance = reference.m_instance;
            m_referenced = reference.m_referenced;
            m_referenced->Increment();
        }
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual Reference& operator = (const Reference& reference) {
        Reference& thisReference = *this;
        Copy(reference);
        return thisReference;
    }
    virtual Instance* operator ->() const {
        return (Instance*)(m_instance);
    }
    virtual Instance& operator *() const {
        return (Instance&)(*m_instance);
    }
    virtual bool operator !() const {
        return !(m_instance != 0);
    }
    virtual operator bool() const {
        return (m_instance != 0);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    static void Delete(TInstance* instance) {
        delete instance;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    TInstance* m_instance;
    TReferenced* m_referenced;
};

} // namespace xos 

#endif // _REFERENCE_HPP 
