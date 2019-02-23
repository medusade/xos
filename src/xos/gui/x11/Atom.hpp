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
///   File: Atom.hpp
///
/// Author: $author$
///   Date: 3/24/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_X11_ATOM_HPP
#define _XOS_GUI_X11_ATOM_HPP

#include "xos/gui/x11/Created.hpp"
#include "xos/gui/x11/Attached.hpp"

#define XOS_GUI_X11_ATOM_NAME_WM_PROTOCOLS "WM_PROTOCOLS"
#define XOS_GUI_X11_ATOM_NAME_WM_DELETE_WINDOW "WM_DELETE_WINDOW"

namespace xos {
namespace x11 {

typedef InterfaceBase AtomImplement;
typedef Attached<XAtom, int, 0> AtomAttached;
typedef xos::Created<XAtom, int, 0, AtomAttached> AtomCreated;
typedef Created<XAtom, int, 0, AtomCreated> AtomExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Atom
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Atom
: virtual public AtomImplement, public AtomExtend {
public:
    typedef AtomImplement Implements;
    typedef AtomExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: Atom
    ///////////////////////////////////////////////////////////////////////
    Atom(XDisplay* xDisplay=0, XAtom detached=0, bool isCreated=false)
    : Extends(xDisplay, detached, isCreated) {
    }
    virtual ~Atom() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual XAtom AttachIntern
    (XDisplay& xDisplay, const char* name, bool onlyExists=false) {
        XAtom detached = 0;
        if ((Destroyed())) {
            if ((detached = XInternAtom(&xDisplay, name, (Bool)(onlyExists?(True):(False))))) {
                Attach(&xDisplay, detached);
            }
        }
        return detached;
    }
};


} // namespace x11 
} // namespace xos 


#endif // _XOS_GUI_X11_ATOM_HPP 
        

