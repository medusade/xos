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
///   File: Intrinsic.hpp
///
/// Author: $author$
///   Date: 3/29/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_X11_INTRINSIC_HPP
#define _XOS_GUI_X11_INTRINSIC_HPP

#include "xos/gui/x11/Xlib.hpp"
#include <X11/Intrinsic.h>

#if !defined(XtNend)
#define XtNend ((XtChar*)(0))
#endif /* !defined(XtNend) */

namespace xos {
namespace x11 {

typedef ::Arg XtArg;
typedef ::ArgList XtArgList;
typedef char XtChar;
typedef ::String XtString;
typedef ::Widget XtWidget;
typedef ::WidgetClass XtWidgetClass;
typedef ::Cardinal XtCardinal;
typedef ::Boolean XtBoolean;
typedef ::Dimension XtDimension;
typedef ::Position XtPosition;

} // namespace x11 
} // namespace xos 

#endif // _XOS_GUI_X11_INTRINSIC_HPP 
