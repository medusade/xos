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
///   File: Platform.hpp
///
/// Author: $author$
///   Date: 7/6/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_WX_PLATFORM_HPP
#define _XOS_GUI_WX_PLATFORM_HPP

#if !defined(ssize_t)
#define ssize_t xos_platform_ssize_t
#endif // !defined(ssize_t)

#if !defined(NO_IMPLEMENT_CLASS)
#define NO_IMPLEMENT_CLASS
#endif // !defined(NO_IMPLEMENT_CLASS)

#include "xos/base/Platform.hpp"

#if defined(NO_IMPLEMENT_CLASS)
#undef NO_IMPLEMENT_CLASS
#endif // defined(NO_IMPLEMENT_CLASS)

#if defined(ssize_t)
#undef ssize_t
#endif // defined(ssize_t)

namespace xos {
namespace wx {

} // namespace wx 
} // namespace xos 

#endif // _XOS_GUI_WX_PLATFORM_HPP 
