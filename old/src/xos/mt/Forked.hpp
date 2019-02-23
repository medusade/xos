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
///   File: Forked.hpp
///
/// Author: $author$
///   Date: 10/17/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_MT_FORKED_HPP
#define _XOS_MT_FORKED_HPP

#include "xos/mt/Forker.hpp"
#include "xos/base/Attacher.hpp"

namespace xos {
namespace mt {

typedef ForkerImplement ForkedImplements;
typedef ExportBase ForkedExtends;
///////////////////////////////////////////////////////////////////////
///  Class: ForkedT
///////////////////////////////////////////////////////////////////////
template
<typename TAttached, typename TUnattached = TAttached, TUnattached VUnattached = 0,
 class TImplement = AttacherT
  <TAttached, TUnattached, VUnattached, ForkedImplements>,
 class TExtend = AttachedT
 <TAttached, TUnattached, VUnattached, TImplement, ForkedExtends> >

class _EXPORT_CLASS ForkedT: virtual public TImplement, public TExtend {
public:
    typedef TImplement Implements;
    typedef TExtend Extends;

    typedef TAttached Attached;
    static const TUnattached Unattached = VUnattached;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    ForkedT
    (Attached attachedTo=((Attached)(Unattached)), bool isForked = false)
    : Extends(attachedTo), m_isForked(isForked) {
    }
    virtual ~ForkedT() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual Attached AttachForked(Attached detached, bool isForked = true) {
        detached = Extends::Attach(detached);
        this->SetIsForked(isForked);
        return detached;
    }
    virtual Attached Attach(Attached detached) {
        detached = Extends::Attach(detached);
        this->SetIsForked(false);
        return detached;
    }
    virtual Attached Detach() {
        Attached detached = Extends::Detach();
        this->SetIsForked(false);
        return detached;
    }

	///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool SetIsForked(bool isTrue = true) {
        this->m_isForked = isTrue;
        return this->m_isForked;
    }
    virtual bool IsForked() const {
        return this->m_isForked;
    }
    virtual bool IsJoined() const {
        return !this->m_isForked;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    bool m_isForked;
};

} // namespace mt 
} // namespace xos 

#endif // _XOS_MT_FORKED_HPP 
