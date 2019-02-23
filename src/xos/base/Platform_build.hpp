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
///   File: Platform_build.hpp
///
/// Author: $author$
///   Date: Jul 28, 2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_PLATFORM_BUILD_HPP_
#define _XOS_PLATFORM_BUILD_HPP_

//
// Determine build platform
//

//
// Define WIN32 if any of the Win32 variants are selected
//
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__Win32__) || defined(__win32__)
#if defined(PLATFORM_DEFINED_DEBUG) 
#error defined WIN32
#endif // defined(PLATFORM_DEFINED_DEBUG)
#if !defined(WIN32)
#define WIN32
#endif //  !defined(WIN32)
#endif //  defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__Win32__) || defined(__win32__)

//
// Define WIN64 if any of the Win64 variants are selected
//
#if defined(WIN64) || defined(_WIN64) || defined(__WIN64__) || defined(__Win64__) || defined(__win64__)
#if defined(PLATFORM_DEFINED_DEBUG) 
#error defined WIN64
#endif // defined(PLATFORM_DEFINED_DEBUG)
#if !defined(WIN64)
#define WIN64
#endif //  !defined(WIN64)
#endif //  defined(WIN64) || defined(_WIN64) || defined(__WIN64__) || defined(__Win64__) || defined(__win64__)

//
// Define WINDOWS if any of the Windows variants are selected
//
#if defined(WIN64) || defined(WIN32)
#if defined(PLATFORM_DEFINED_DEBUG) 
#error defined WINDOWS
#endif // defined(PLATFORM_DEFINED_DEBUG)
#if !defined(WINDOWS) 
#define WINDOWS 
#endif // !defined(WINDOWS)
#endif // defined(WIN64) || defined(WIN32)

//
// Define MACOSX if any of the Mac OSX variants are selected
//
#if defined(APPLE) || defined(__APPLE__) || defined(__MACOS__) || defined(__MACOSX__) || defined(__MacOSX__) || defined(__macosx__)
#if defined(PLATFORM_DEFINED_DEBUG) 
#error defined MACOSX
#endif // defined(PLATFORM_DEFINED_DEBUG)
#if !defined(MACOSX)
#define MACOSX
#endif // !defined(MACOSX)
#endif // defined(APPLE) || defined(__APPLE__) || defined(__MACOS__) || defined(__MACOSX__) || defined(__MacOSX__) || defined(__macosx__)

//
// Define LINUX if any of the Linux variants are selected
//
#if defined(LINUX) || defined(__LINUX__) || defined(__Linux__) || defined(__linux__)
#if defined(PLATFORM_DEFINED_DEBUG) 
#error defined LINUX
#endif // defined(PLATFORM_DEFINED_DEBUG)
#if !defined(LINUX)
#define LINUX
#endif // !defined(LINUX)
#endif // defined(LINUX) || defined(__LINUX__) || defined(__Linux__) || defined(__linux__) */

namespace xos {
} // namespace xos

#endif // _XOS_PLATFORM_BUILD_HPP_ 
