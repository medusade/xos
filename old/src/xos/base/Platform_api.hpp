///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2012 $organization$
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
///   File: Platform_api.hpp
///
/// Author: $author$
///   Date: 11/1/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_BASE_PLATFORM_API_HPP
#define _XOS_BASE_PLATFORM_API_HPP

#include "xos/base/Platform_build.hpp"

#if defined(WINDOWS) 
// Windows 
// ...
#if !defined(UNIX_API) 
// Windows API 
#if !defined(WINDOWS_API) 
#define WINDOWS_API
#endif // !defined(WINDOWS_API) 
#else // !defined(UNIX_API) 
// Otherwise 
#endif // !defined(UNIX_API) 
// ...
// Windows 
#else // defined(WINDOWS) 
// Unix 
// ...
#if !defined(WINDOWS_API) 
// Unix API 
#if !defined(UNIX_API) 
#define UNIX_API
#endif // !defined(UNIX_API) 
#else // !defined(WINDOWS_API) 
// Otherwise 
#endif // !defined(WINDOWS_API) 
// ...
// Unix 
#endif // defined(WINDOWS) 

namespace xos {
} // namespace xos 

#endif // _XOS_BASE_PLATFORM_API_HPP 
