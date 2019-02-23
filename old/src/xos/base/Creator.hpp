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
///   File: Creator.hpp
///
/// Author: $author$
///   Date: 4/14/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_BASE_CREATOR_HPP
#define _XOS_BASE_CREATOR_HPP

#include "xos/base/Attacher.hpp"
#include "xos/base/Base.hpp"

namespace xos {

typedef InterfaceBase CreatorImplements;
///////////////////////////////////////////////////////////////////////
///  Class: CreatorT
///////////////////////////////////////////////////////////////////////
template <class TImplement = CreatorImplements>
class _EXPORT_CLASS CreatorT: virtual public TImplement {
public:
    typedef TImplement Implements;
    ///////////////////////////////////////////////////////////////////////
    ///  Enum: Exception
    ///////////////////////////////////////////////////////////////////////
    enum Exception {
        FailedToCreate,
        FailedToDestroy
    };
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool SetIsCreated(bool isTrue = true) = 0;
    virtual bool IsCreated() const = 0;
    virtual bool IsDestroyed() const = 0;
    virtual bool Destroyed() = 0;
    virtual bool Destroy() = 0;
    virtual bool Create() = 0;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef CreatorT<> Creator;

///////////////////////////////////////////////////////////////////////
///  Class: CreatorImplementT
///////////////////////////////////////////////////////////////////////
template <class TImplement = Creator>
class _EXPORT_CLASS CreatorImplementT: virtual public TImplement {
public:
    typedef TImplement Implements;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool SetIsCreated(bool isTrue = true) { return false; }
    virtual bool IsCreated() const { return false; }
    virtual bool IsDestroyed() const { return !IsCreated(); }
    virtual bool Destroyed() {
        if ((IsCreated()))
            return Destroy();
        return true; }
    virtual bool Destroy() { return false; }
    virtual bool Create() { return false; }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef CreatorImplementT<> CreatorImplement;

///////////////////////////////////////////////////////////////////////
///  Class: CreatorExtendT
///////////////////////////////////////////////////////////////////////
template <class TImplement = CreatorImplement, class TExtend = ExportBase>
class _EXPORT_CLASS CreatorExtendT: virtual public TImplement, public TExtend {
public:
    typedef TImplement Implements;
    typedef TExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    CreatorExtendT(bool isCreated = false): m_isCreated(isCreated) {}
    virtual ~CreatorExtendT() {
        if (!(this->Destroyed())) {
            Creator::Exception e(Creator::FailedToDestroy);
            throw(e);
        }
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool SetIsCreated(bool isTrue = true) {
        m_isCreated = isTrue;
        return m_isCreated;
    }
    virtual bool IsCreated() const {
        return m_isCreated;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    bool m_isCreated;
};
typedef CreatorExtendT<> CreatorExtend;

typedef CreatorImplement CreatedImplements;
typedef ExportBase CreatedExtends;
///////////////////////////////////////////////////////////////////////
///  Class: CreatedT
///////////////////////////////////////////////////////////////////////
template
<typename TAttached, typename TUnattached = TAttached, TUnattached VUnattached = 0,
 class TImplement = AttacherT
  <TAttached, TUnattached, VUnattached, CreatedImplements>,
 class TExtend = AttachedT
 <TAttached, TUnattached, VUnattached, TImplement, CreatedExtends> >

class _EXPORT_CLASS CreatedT: virtual public TImplement, public TExtend {
public:
    typedef TImplement Implements;
    typedef TExtend Extends;

    typedef TAttached Attached;
    static const TUnattached Unattached = VUnattached;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    CreatedT
    (Attached attachedTo=((Attached)(Unattached)), bool isCreated = false)
    : Extends(attachedTo), m_isCreated(isCreated) {
    }
    virtual ~CreatedT() {
        if (!(this->Destroyed())) {
            Creator::Exception e = Creator::FailedToDestroy;
            throw (e);
        }
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual Attached AttachCreated(Attached attachedTo, bool isCreated = true) {
        attachedTo = this->Attach(attachedTo);
        this->SetIsCreated(isCreated);
        return attachedTo;
    }
    virtual Attached DetachCreated(bool& isCreated){
        Attached detached = this->Detach();
        isCreated = this->IsCreated();
        this->SetIsCreated(false);
        return detached;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual Attached Attach(Attached attachedTo) {
        attachedTo = Extends::Attach(attachedTo);
        this->SetIsCreated(false);
        return attachedTo;
    }
    virtual Attached Detach(){
        Attached detached = Extends::Detach();
        this->SetIsCreated(false);
        return detached;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool SetIsCreated(bool isTrue = true) {
        m_isCreated = isTrue;
        return m_isCreated;
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

#endif // _XOS_BASE_CREATOR_HPP 
