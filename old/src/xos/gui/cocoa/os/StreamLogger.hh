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
///   File: StreamLogger.hh
///
/// Author: $author$
///   Date: 2/1/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_COCOA_OS_STREAMLOGGER_HH
#define _XOS_GUI_COCOA_OS_STREAMLOGGER_HH

#include "xos/gui/cocoa/os/LoggerStream.hh"
#include "xos/gui/cocoa/os/Os.hh"

#if defined(APPLE_IOS)
#include "xos/gui/cocoa/ios/StreamLogger.hh"
#else // defined(APPLE_IOS)
#include "xos/gui/cocoa/osx/StreamLogger.hh"
#endif // defined(APPLE_IOS)

namespace xos {
namespace cocoa {
namespace os {

typedef os::StreamLogger StreamLogger;

} // namespace os
} // namespace cocoa 
} // namespace xos 

#endif // _XOS_GUI_COCOA_OS_STREAMLOGGER_HH 
