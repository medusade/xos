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
///   File: Xlib.hpp
///
/// Author: $author$
///   Date: 3/20/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_X11_XLIB_HPP
#define _XOS_GUI_X11_XLIB_HPP

#include "xos/base/Platform.hpp"
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xresource.h>
#include <X11/xpm.h>
#include <X11/ICE/ICE.h>
#include <X11/ICE/ICElib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glx.h>

#if defined(DefaultScreen)
#define XOS_GUI_X11_XLIB_DefaultScreen DefaultScreen
#undef DefaultScreen
#endif // defined(DefaultScreen)

#if defined(Status)
typedef Status XOS_GUI_X11_XLIB_Status;
#undef Status
typedef XOS_GUI_X11_XLIB_Status Status;
#endif // defined(Status)

#if defined(Bool)
typedef Bool XOS_GUI_X11_XLIB_Bool;
#undef Bool
typedef XOS_GUI_X11_XLIB_Bool Bool;
#endif // defined(Bool)

#if defined(True)
enum { XOS_GUI_X11_XLIB_True = True };
#undef True
enum { True = XOS_GUI_X11_XLIB_True };
#endif // defined(True)

#if defined(False)
enum { XOS_GUI_X11_XLIB_False = False };
#undef False
enum { False = XOS_GUI_X11_XLIB_False };
#endif // defined(False)

#if defined(None)
enum { XOS_GUI_X11_XLIB_None = None };
#undef None
enum { None = XOS_GUI_X11_XLIB_None };
#endif // defined(None)

#if defined(Success)
enum { XOS_GUI_X11_XLIB_Success = Success };
#undef Success
enum { Success = XOS_GUI_X11_XLIB_Success };
#endif // defined(Success)

namespace xos {
namespace x11 {

typedef short XOffset;
typedef unsigned short XSize;
typedef ::Status XStatus;
typedef ::Display XDisplay;
typedef ::Screen XScreen;
typedef ::Visual XVisual;
typedef ::Window XWindow;
typedef ::Pixel XPixel;
typedef ::Atom XAtom;
typedef ::Colormap XColormap;
typedef int XEventType;
typedef long XEventMask;
typedef unsigned long XSetWindowAttributesMask;

} // namespace x11 
} // namespace xos 

#endif // _XOS_GUI_X11_XLIB_HPP 
