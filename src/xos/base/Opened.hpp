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
///   File: Opened.hpp
///
/// Author: $author$
///   Date: Aug 5, 2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_OPENED_HPP_
#define _XOS_OPENED_HPP_

#include "xos/base/Attached.hpp"

namespace xos {

template
<class TAttached,
 class TUnattached=TAttached,
 TUnattached VUnattached=0,
 class TExtend=Attached<TAttached, TUnattached, VUnattached>,
 class TImplement=InterfaceBase>

class EXPORT_CLASS Opened: virtual public TImplement, public TExtend {
public:
    typedef TImplement Implements;
    typedef TExtend Extends;

    typedef TAttached AttachedT;
    typedef TUnattached UnattachedT;
    static const UnattachedT Unattached=VUnattached;

    Opened
    (AttachedT attachedTo=((AttachedT)(Unattached)), bool isOpen=false)
    : Extends(attachedTo), m_isOpen(isOpen){}
    virtual ~Opened()
    {
        Error error = xos::Error::Failed;
        if (!(Closed()))
            throw(error);
    }

    virtual bool Closed(){
        if ((m_isOpen))
            return Close();
        return true;
    }
    virtual bool Close(){
        m_isOpen = false;
        this->m_attachedTo = ((AttachedT)(Unattached));
        return true;
    }
    virtual AttachedT AttachOpened(AttachedT attachedTo, bool isOpen=true){
        return Attach(attachedTo, isOpen);
    }
    virtual AttachedT Attach(AttachedT attachedTo, bool isOpen){
        m_isOpen = isOpen;
        return this->m_attachedTo = attachedTo;
    }
    virtual AttachedT Detach(bool& isOpen){
        AttachedT detached = this->m_attachedTo;
        isOpen = m_isOpen;
        m_isOpen = false;
        this->m_attachedTo = ((AttachedT)(Unattached));
        return detached;
    }
    virtual AttachedT Attach(AttachedT attachedTo){
        m_isOpen = false;
        return this->m_attachedTo = attachedTo;
    }
    virtual AttachedT Detach(){
        AttachedT detached = this->m_attachedTo;
        m_isOpen = false;
        this->m_attachedTo = ((AttachedT)(Unattached));
        return detached;
    }
    virtual bool SetIsOpen(bool isTrue=true){
        return m_isOpen = isTrue;
    }
    virtual bool IsOpen() const {
        return m_isOpen;
    }
protected:
    bool m_isOpen;
};

} // namespace xos

#endif // _XOS_OPENED_HPP_ 
