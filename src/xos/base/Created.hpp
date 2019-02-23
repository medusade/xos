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
///   File: Created.hpp
///
/// Author: $author$
///   Date: 10/5/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_CREATED_HPP
#define _XOS_CREATED_HPP

#include "xos/base/Attached.hpp"

namespace xos {

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
template
<class TAttached,
 class TUnattached=TAttached,
 TUnattached VUnattached=0,
 class TExtend=Attached<TAttached, TUnattached, VUnattached>,
 class TImplement=InterfaceBase>

class _EXPORT_CLASS Created: virtual public TImplement, public TExtend {
public:
    typedef TImplement Implements;
    typedef TExtend Extends;

    typedef TAttached AttachedT;
    typedef TUnattached UnattachedT;
    static const UnattachedT Unattached=VUnattached;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Created
    (AttachedT attachedTo=((AttachedT)(Unattached)), bool isCreated=false)
    : Extends(attachedTo), m_isCreated(isCreated){
    }
    virtual ~Created() {
        Error error = xos::Error::Failed;
        if (!(Destroyed()))
            throw(error);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void Construct
    (AttachedT attachedTo, bool isCreated) {
        Extends::Construct(attachedTo);
        m_isCreated = isCreated;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Destroyed(){
        if ((m_isCreated))
            return Destroy();
        else Detach();
        return true;
    }
    virtual bool Destroy(){
        m_isCreated = false;
        this->m_attachedTo = ((AttachedT)(Unattached));
        return true;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual AttachedT AttachCreated(AttachedT attachedTo, bool isCreated=true){
        return Attach(attachedTo, isCreated);
    }
    virtual AttachedT Attach(AttachedT attachedTo, bool isCreated){
        m_isCreated = isCreated;
        return this->m_attachedTo = attachedTo;
    }
    virtual AttachedT Detach(bool& isCreated){
        AttachedT detached = this->m_attachedTo;
        isCreated = m_isCreated;
        m_isCreated = false;
        this->m_attachedTo = ((AttachedT)(Unattached));
        return detached;
    }
    virtual AttachedT Attach(AttachedT attachedTo){
        m_isCreated = false;
        return this->m_attachedTo = attachedTo;
    }
    virtual AttachedT Detach(){
        AttachedT detached = this->m_attachedTo;
        m_isCreated = false;
        this->m_attachedTo = ((AttachedT)(Unattached));
        return detached;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool SetIsCreated(bool isTrue=true){
        return m_isCreated = isTrue;
    }
    virtual bool IsCreated() const {
        return m_isCreated;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    bool m_isCreated;
};

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
template
<class TExtend = ExportBase,
 class TImplement = InterfaceBase>

class _EXPORT_CLASS CreatedBaseT: virtual public TImplement, public TExtend {
public:
    typedef TImplement Implements;
    typedef TExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    CreatedBaseT(bool isCreated=false)
    : m_isCreated(isCreated) {
    }
    virtual ~CreatedBaseT() {
        if (!(Destroyed())) {
            Error error = xos::Error::Failed;
            throw(error);
        }
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Destroyed(){
        if ((m_isCreated))
            return Destroy();
        return true;
    }
    virtual bool Destroy(){
        m_isCreated = false;
        return true;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool SetIsCreated(bool isTrue=true){
        return m_isCreated = isTrue;
    }
    virtual bool IsCreated() const {
        return m_isCreated;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    bool m_isCreated;
};

} // namespace xos

#endif // _XOS_CREATED_HPP 
