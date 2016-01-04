///////////////////////////////////////////////////////////////////////
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
///   File: Registered.hpp
///
/// Author: $author$
///   Date: 1/11/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_BASE_REGISTERED_HPP
#define _XOS_BASE_REGISTERED_HPP

#include "xos/base/Attached.hpp"

namespace xos {

template
<class TAttached,
 class TUnattached=TAttached,
 TUnattached VUnattached=0,
 class TExtend=Attached<TAttached, TUnattached, VUnattached>,
 class TImplement=InterfaceBase>

class _EXPORT_CLASS Registered: virtual public TImplement, public TExtend {
public:
    typedef TImplement Implements;
    typedef TExtend Extends;

    typedef TAttached AttachedT;
    typedef TUnattached UnattachedT;
    static const UnattachedT Unattached=VUnattached;

    Registered
    (AttachedT attachedTo=((AttachedT)(Unattached)), bool isRegistered=false)
    : Extends(attachedTo), m_isRegistered(isRegistered){}
    virtual ~Registered()
    {
        Error error = xos::Error::Failed;
        if (!(Unregistered()))
            throw(error);
    }

    virtual bool Unregistered(){
        if ((m_isRegistered))
            return Unregister();
        else Detach();
        return true;
    }
    virtual bool Unregister(){
        m_isRegistered = false;
        this->m_attachedTo = ((AttachedT)(Unattached));
        return true;
    }
    virtual AttachedT AttachRegistered(AttachedT attachedTo, bool isRegistered=true){
        return Attach(attachedTo, isRegistered);
    }
    virtual AttachedT Attach(AttachedT attachedTo, bool isRegistered){
        m_isRegistered = isRegistered;
        return this->m_attachedTo = attachedTo;
    }
    virtual AttachedT Detach(bool& isRegistered){
        AttachedT detached = this->m_attachedTo;
        isRegistered = m_isRegistered;
        m_isRegistered = false;
        this->m_attachedTo = ((AttachedT)(Unattached));
        return detached;
    }
    virtual AttachedT Attach(AttachedT attachedTo){
        m_isRegistered = false;
        return this->m_attachedTo = attachedTo;
    }
    virtual AttachedT Detach(){
        AttachedT detached = this->m_attachedTo;
        m_isRegistered = false;
        this->m_attachedTo = ((AttachedT)(Unattached));
        return detached;
    }
    virtual bool SetIsRegistered(bool isTrue=true){
        return m_isRegistered = isTrue;
    }
    virtual bool IsRegistered() const {
        return m_isRegistered;
    }
protected:
    bool m_isRegistered;
};

} // namespace xos 

#endif // _XOS_BASE_REGISTERED_HPP 
