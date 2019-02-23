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
///   File: Wrapper.hpp
///
/// Author: $author$
///   Date: 3/1/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_BASE_WRAPPER_HPP
#define _XOS_BASE_WRAPPER_HPP

#include "xos/base/Base.hpp"

namespace xos {

///////////////////////////////////////////////////////////////////////
///  Class: Wrapper
///////////////////////////////////////////////////////////////////////
template
<typename TWrapped, class TExtend = ExportBase, class TImplement = InterfaceBase>

class _EXPORT_CLASS Wrapper: virtual public TImplement, public TExtend {
public:
    typedef TImplement Implements;
    typedef TExtend Extends;
    typedef TWrapped WrappedT;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Wrapper(TWrapped& wrapped, TWrapped& wrappedBase)
    : Extends(wrappedBase), m_wrapped(wrapped) {
    }
    Wrapper(TWrapped& wrapped): m_wrapped(wrapped) {
    }
    virtual ~Wrapper() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual TWrapped& wrapped() const {
        return (TWrapped&)(m_wrapped);
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    TWrapped& m_wrapped;
};

} // namespace xos 

#endif // _XOS_BASE_WRAPPER_HPP 
