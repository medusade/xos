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
///   File: Attached.hpp
///
/// Author: $author$
///   Date: 3/20/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_X11_ATTACHED_HPP
#define _XOS_GUI_X11_ATTACHED_HPP

#include "xos/gui/x11/Xlib.hpp"
#include "xos/base/Attached.hpp"

namespace xos {
namespace x11 {

///////////////////////////////////////////////////////////////////////
///  Class: Attached
///////////////////////////////////////////////////////////////////////
template
<class TAttached,
 class TUnattached=TAttached,
 TUnattached VUnattached=0,
 class TExtend=xos::Attached<TAttached, TUnattached, VUnattached>, 
 class TImplement=InterfaceBase>

class _EXPORT_CLASS Attached
: virtual public TImplement, public TExtend {
public:
    typedef TImplement Implements;
    typedef TExtend Extends;

    typedef TAttached AttachedT;
    typedef TUnattached UnattachedT;
    static const UnattachedT Unattached=VUnattached;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: Attached
    ///////////////////////////////////////////////////////////////////////
    Attached(AttachedT detached)
    : Extends(detached), m_display(0) {
    }
    Attached(XDisplay* display=0, AttachedT detached=((AttachedT)(Unattached)))
    : Extends(detached), m_display(display) {
    }
    virtual ~Attached() {
    }
    virtual void Construct(XDisplay* display, AttachedT detached) {
        Extends::Construct(detached);
        m_display = display;
    }
    virtual void Construct(AttachedT detached) {
        Extends::Construct(detached);
        m_display = 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual AttachedT Attach
    (XDisplay* display, AttachedT detached) {
        m_display = display;
        return Extends::Attach(detached);
    }
    virtual AttachedT Detach(XDisplay*& display) {
        display = m_display;
        m_display = 0;
        return Extends::Detach();
    }
    virtual AttachedT Detach() {
        m_display = 0;
        return Extends::Detach();
    }
    virtual AttachedT AttachedTo(XDisplay*& display) const {
        display = m_display;
        return Extends::AttachedTo();
    }
    virtual AttachedT AttachedTo() const {
        return Extends::AttachedTo();
    }
    virtual XDisplay* DisplayAttachedTo() const {
        return m_display;
    }

protected:
    XDisplay* m_display;
};

} // namespace x11 
} // namespace xos 

#endif // _XOS_GUI_X11_ATTACHED_HPP 
