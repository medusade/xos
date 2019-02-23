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
///   File: Property.hpp
///
/// Author: $author$
///   Date: 4/7/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_X11_PROPERTY_HPP
#define _XOS_GUI_X11_PROPERTY_HPP

#include "xos/gui/x11/Atom.hpp"

namespace xos {
namespace x11 {

typedef AtomImplement PropertyImplement;
typedef Atom PropertyExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Property
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Property
: virtual public PropertyImplement, public PropertyExtend {
public:
    typedef PropertyImplement Implements;
    typedef PropertyExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: Property
    ///////////////////////////////////////////////////////////////////////
    Property
    (uint8_t propertyByte,
     const char* atomName = 0)
    : m_propertyByte(propertyByte),
      m_propertyFormat(8),
      m_propertyLength(1),
      m_atomName(atomName) {
    }
    Property
    (const char* atomName = 0,
     int propertyFormat = 8,
     int propertyLength = 1)
    : m_propertyByte(0),
      m_propertyFormat(propertyFormat),
      m_propertyLength(propertyLength),
      m_atomName(atomName) {
    }
    virtual ~Property() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Change
    (XDisplay& xDisplay, XWindow xWindow, int propertyMode = PropModeReplace) {
        uint8_t& propertyByte = Byte();
        XAtom xAtom;

        if (!(None != (xAtom = AttachedTo())))
        if (!(None != (xAtom = AttachIntern(xDisplay))))
            return false;

        XChangeProperty
        (&xDisplay, xWindow, xAtom, xAtom, 
         m_propertyFormat, propertyMode,  &propertyByte, m_propertyLength);
        return true;
    }
    virtual XAtom AttachIntern
    (XDisplay& xDisplay, bool onlyExists=false) {
        XAtom detached = 0;
        if ((m_atomName))
            detached = Extends::AttachIntern(xDisplay, m_atomName, onlyExists);
        return detached;
    }
    virtual uint8_t& Byte() const {
        return (uint8_t&)(m_propertyByte);
    }

protected:
    uint8_t m_propertyByte;
    int m_propertyFormat;
    int m_propertyLength;
    const char* m_atomName;
};

} // namespace x11 
} // namespace xos 

#endif // _XOS_GUI_X11_PROPERTY_HPP 
