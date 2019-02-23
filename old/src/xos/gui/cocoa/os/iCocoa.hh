///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2014 $organization$
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
///   File: iCocoa.hh
///
/// Author: $author$
///   Date: 1/31/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_COCOA_OS_ICOCOA_HH
#define _XOS_GUI_COCOA_OS_ICOCOA_HH

#include "xos/gui/cocoa/os/iOsX.hh"
#include <Foundation/Foundation.h>
#include <Cocoa/Cocoa.h>

#if defined(APPLE_IOS)  
#include "xos/gui/cocoa/ios/iCocoa.hh"
#else // defined(APPLE_IOS)
#include "xos/gui/cocoa/osx/iCocoa.hh"
#endif // defined(APPLE_IOS)

#endif // _XOS_GUI_COCOA_OS_ICOCOA_HH 
