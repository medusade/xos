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
///   File: WmHints.hpp
///
/// Author: $author$
///   Date: 4/24/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_X11_XM_WMHINTS_HPP
#define _XOS_GUI_X11_XM_WMHINTS_HPP

#include "xos/gui/x11/xm/MwmUtil.hpp"
#include "xos/gui/x11/Property.hpp"
#include "xos/base/Wrapped.hpp"

#define XOS_GUI_X11_XM_WMHINTS_NAME _XA_MOTIF_WM_HINTS
#define XOS_GUI_X11_XM_WMHINTS_FORMAT 32

namespace xos {
namespace x11 {
namespace xm {

typedef x11::PropertyImplement WmHintsImplement;
typedef Wrapped<XWmHints, int, x11::Property, WmHintsImplement> WmHintsExtend;
///////////////////////////////////////////////////////////////////////
///  Class: WmHints
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS WmHints
: virtual public WmHintsImplement, public WmHintsExtend {
public:
    typedef WmHintsImplement Implements;
    typedef WmHintsExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: WmHints
    ///////////////////////////////////////////////////////////////////////
    WmHints
    (const char* atomName = XOS_GUI_X11_XM_WMHINTS_NAME,
     int propertyFormat = XOS_GUI_X11_XM_WMHINTS_FORMAT,
     int propertyLength = sizeof(WrappedT)/(XOS_GUI_X11_XM_WMHINTS_FORMAT/8))
    {
        m_atomName = atomName;
        m_propertyFormat = propertyFormat;
        m_propertyLength = propertyLength;
    }
    virtual ~WmHints() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Change
    (XDisplay& xDisplay, XWindow xWindow,
     CARD32 flags = 0, CARD32 functions = 0, 
     CARD32 decorations = 0, INT32 input_mode = 0) {
        m_wrapped.flags = flags;

        if (flags & MWM_HINTS_FUNCTIONS)
            m_wrapped.functions = functions;

        if (flags & MWM_HINTS_DECORATIONS)
            m_wrapped.decorations = decorations;

        if (flags & MWM_HINTS_INPUT_MODE)
            m_wrapped.input_mode = input_mode;

        if ((Extends::Change(xDisplay, xWindow)))
            return true;
        return false;
    }
    virtual uint8_t& Byte() const {
        return (uint8_t&)(m_wrapped);
    }
    virtual operator XWmHints&() const {
        return (XWmHints&)(m_wrapped);
    }
};

} // namespace xm 
} // namespace x11 
} // namespace xos 

#endif // _XOS_GUI_X11_XM_WMHINTS_HPP 
