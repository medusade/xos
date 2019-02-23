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
///   File: Attacher.hpp
///
/// Author: $author$
///   Date: 4/18/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_BASE_ATTACHER_HPP
#define _XOS_BASE_ATTACHER_HPP

#include "xos/base/Base.hpp"

namespace xos {

///////////////////////////////////////////////////////////////////////
///  Class: AttacherT
///////////////////////////////////////////////////////////////////////
template
<class TAttached, class TUnattached = TAttached,
 TUnattached VUnattached = 0, class TImplement = InterfaceBase>

class _EXPORT_CLASS AttacherT: virtual public TImplement {
public:
    typedef TImplement Implements;
    typedef TAttached Attached;
    static const TUnattached Unattached = VUnattached;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual Attached Attach(Attached attachedTo) {
        return ((Attached)(Unattached));
    }
    virtual Attached Detach() {
        return ((Attached)(Unattached));
    }
    virtual Attached AttachedTo() const {
        return ((Attached)(Unattached));
    }
    virtual operator Attached() const {
        return AttachedTo();
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

///////////////////////////////////////////////////////////////////////
///  Class: AttachedT
///////////////////////////////////////////////////////////////////////
template
<class TAttached, class TUnattached = TAttached, TUnattached VUnattached = 0,
 class TImplement = AttacherT<TAttached, TUnattached, VUnattached, InterfaceBase>,
 class TExtend = ExportBase>

class _EXPORT_CLASS AttachedT: virtual public TImplement, public TExtend {
public:
    typedef TImplement Implements;
    typedef TExtend Extends;
    typedef TAttached Attached;
    static const TUnattached Unattached = VUnattached;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    AttachedT(Attached attachedTo=((Attached)(Unattached))): m_attachedTo(attachedTo){}
    virtual ~AttachedT(){}
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual Attached Attach(Attached attachedTo){
        return m_attachedTo = attachedTo;
    }
    virtual Attached Detach(){
        Attached detached = m_attachedTo;
        m_attachedTo = ((Attached)(Unattached));
        return detached;
    }
    virtual Attached AttachedTo() const {
        return m_attachedTo;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    Attached m_attachedTo;
};

} // namespace xos

#endif // _XOS_BASE_ATTACHER_HPP 
