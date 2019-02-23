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
///   File: Created.hpp
///
/// Author: $author$
///   Date: 3/20/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_X11_CREATED_HPP
#define _XOS_GUI_X11_CREATED_HPP

#include "xos/gui/x11/Attached.hpp"
#include "xos/base/Created.hpp"

namespace xos {
namespace x11 {

///////////////////////////////////////////////////////////////////////
///  Class: Created
///////////////////////////////////////////////////////////////////////
template
<class TAttached,
 class TUnattached=TAttached,
 TUnattached VUnattached=0,
 class TExtend=xos::Created
 <TAttached, TUnattached, VUnattached, 
  Attached<TAttached, TUnattached, VUnattached> >, 
 class TImplement=InterfaceBase>

class _EXPORT_CLASS Created
: virtual public TImplement, public TExtend {
public:
    typedef TImplement Implements;
    typedef TExtend Extends;

    typedef TAttached AttachedT;
    typedef TUnattached UnattachedT;
    static const UnattachedT Unattached=VUnattached;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: Created
    ///////////////////////////////////////////////////////////////////////
    Created
    (XDisplay* display=0, AttachedT detached=0, bool isCreated=false) {
        Construct(display, detached, isCreated);
    }
    virtual ~Created() {
    }
    virtual void Construct
    (XDisplay* display, AttachedT detached, bool isCreated) {
        Extends::Extends::Construct(display, detached);
        this->SetIsCreated(isCreated);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual AttachedT AttachCreated
    (XDisplay* display, AttachedT detached, bool isCreated=true) {
        return Attach(display, detached, isCreated);
    }
    virtual AttachedT Attach
    (XDisplay* display, AttachedT detached, bool isCreated=false) {
        AttachedT attached;
        attached = Extends::Extends::Attach(display, detached);
        this->SetIsCreated(isCreated);
        return attached;
    }
    virtual AttachedT Detach(XDisplay*& display, bool& isCreated) {
        isCreated = this->IsCreated();
        return Extends::Extends::Detach(display);
    }
    virtual AttachedT Detach() {
        return Extends::Extends::Detach();
    }
};

} // namespace x11 
} // namespace xos 

#endif // _XOS_GUI_X11_CREATED_HPP 
