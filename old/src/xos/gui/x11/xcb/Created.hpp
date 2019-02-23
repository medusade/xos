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
///   Date: 3/18/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_X11_XCB_CREATED_HPP
#define _XOS_GUI_X11_XCB_CREATED_HPP

#include "xos/gui/x11/xcb/Attached.hpp"
#include "xos/base/Created.hpp"

namespace xos {
namespace x11 {
namespace xcb {

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
    (xcb_connection_t* connection=0, AttachedT detached=0, bool isCreated=false) {
        Construct(connection, detached, isCreated);
    }
    virtual ~Created() {
    }
    virtual void Construct
    (xcb_connection_t* connection, AttachedT detached, bool isCreated) {
        Extends::Extends::Construct(connection, detached);
        this->SetIsCreated(isCreated);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual AttachedT AttachCreated
    (xcb_connection_t* connection, AttachedT detached, bool isCreated=true) {
        return Attach(connection, detached, isCreated);
    }
    virtual AttachedT Attach
    (xcb_connection_t* connection, AttachedT detached, bool isCreated=false) {
        AttachedT attached;
        attached = Extends::Extends::Attach(connection, detached);
        this->SetIsCreated(isCreated);
        return attached;
    }
    virtual AttachedT Detach(xcb_connection_t*& connection, bool& isCreated) {
        isCreated = this->IsCreated();
        return Extends::Extends::Detach(connection);
    }
};

} // namespace xcb 
} // namespace x11 
} // namespace xos 

#endif // _XOS_GUI_X11_XCB_CREATED_HPP 
