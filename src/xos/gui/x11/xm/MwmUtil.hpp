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
///   File: MwmUtil.hpp
///
/// Author: $author$
///   Date: 4/7/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_X11_XM_MWMUTIL_HPP
#define _XOS_GUI_X11_XM_MWMUTIL_HPP

#include "xos/gui/x11/Intrinsic.hpp"

#define BOOL XOS_GUI_X11_XM_MWMUTIL_BOOL
#define INT8 XOS_GUI_X11_XM_MWMUTIL_INT8
#define INT32 XOS_GUI_X11_XM_MWMUTIL_INT32
#include <Xm/MwmUtil.h>
#undef INT32
#undef INT8
#undef BOOL

namespace xos {
namespace x11 {
namespace xm {

typedef ::XOS_GUI_X11_XM_MWMUTIL_BOOL BOOL;
typedef ::XOS_GUI_X11_XM_MWMUTIL_INT8 INT8;
typedef ::XOS_GUI_X11_XM_MWMUTIL_INT32 INT32;
typedef ::MwmHints XWmHints;

} // namespace xm 
} // namespace x11 
} // namespace xos 

#endif // _XOS_GUI_X11_XM_MWMUTIL_HPP 
