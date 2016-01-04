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
///   File: Platform.hpp
///
/// Author: $author$
///   Date: 7/26/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_PLATFORM_HPP
#define _XOS_PLATFORM_HPP

#include "xos/base/Platform_build.hpp"
#include "xos/base/Platform_compiler.hpp"
#include "xos/base/Platform_includes.hpp"
#include "xos/base/Platform_defines.hpp"
#include "xos/base/Platform_types.hpp"
#include "xos/base/Platform_api.hpp"

#if defined(WINDOWS) 
void _PLATFORM_EXPORT sleep(int count);
#endif // defined(WINDOWS) 

namespace xos {
} // namespace xos

#endif // _XOS_PLATFORM_HPP 
