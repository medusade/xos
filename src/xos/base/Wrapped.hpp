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
///   File: Wrapped.hpp
///
/// Author: $author$
///   Date: 10/8/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_WRAPPED_HPP
#define _XOS_WRAPPED_HPP

#include "xos/base/Base.hpp"
#include <string.h>

namespace xos {

template
<typename TWrapped,
 typename TInitialized = int,
 class TExtend = ExportBase,
 class TImplement = InterfaceBase>

class _EXPORT_CLASS Wrapped: virtual public TImplement, public TExtend {
public:
    typedef TImplement Implements;
    typedef TExtend Extends;
    typedef TWrapped WrappedT;
    typedef TInitialized InitializedT;

    Wrapped(TWrapped& wrapped, TInitialized initialized): m_wrapped(wrapped) {
        memset(&m_wrapped, initialized, sizeof(TWrapped));
    }
    Wrapped(TInitialized initialized): m_wrapped(m_wrappedDefault) {
        memset(&m_wrapped, initialized, sizeof(TWrapped));
    }
    Wrapped(TWrapped& wrapped): m_wrapped(wrapped) {}
    Wrapped(const Wrapped& copy): m_wrapped(m_wrappedDefault) {
        memcpy(&m_wrapped, &copy.m_wrapped, sizeof(TWrapped));
    }
    Wrapped(): m_wrapped(m_wrappedDefault) {}
    virtual ~Wrapped() {}

    virtual Wrapped& Copy(const TWrapped& wrapped) {
        memcpy(&m_wrapped, &wrapped, sizeof(TWrapped));
        return *this;
    }
    virtual Wrapped& operator = (const Wrapped& copy) {
        memcpy(&m_wrapped, &copy.m_wrapped, sizeof(TWrapped));
        return *this;
    }

    inline Wrapped& wrapper() const {
        return (Wrapped&)(*this);
    }
    inline TWrapped& wrapped() const {
        return (TWrapped&)(m_wrapped); 
    }
    inline operator TWrapped& () const {
        return (TWrapped&)(m_wrapped); 
    }

protected:
    TWrapped m_wrappedDefault;
    TWrapped& m_wrapped;
};

} // namespace xos 

#endif // _XOS_WRAPPED_HPP 
