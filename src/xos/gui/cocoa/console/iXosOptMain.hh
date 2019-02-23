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
///   File: iXosOptMain.hh
///
/// Author: $author$
///   Date: 12/23/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_COCOA_CONSOLE_IXOSOPTMAIN_HH
#define _XOS_GUI_COCOA_CONSOLE_IXOSOPTMAIN_HH

#include "xos/gui/cocoa/console/iXosBaseMain.hh"
#include "xos/os/MainOpt.hpp"

#if defined(OBJC)  
///////////////////////////////////////////////////////////////////////
/// Protocol: iXosOptMain
///
///   Author: $author$
///     Date: 12/23/2012
///////////////////////////////////////////////////////////////////////
@protocol iXosOptMain <iXosBaseMain>
    - (int)Usage:(int)argc argv:(char**)argv env:(char**)env;
    - (int)GetOptions:(int)argc argv:(char**)argv env:(char**)env;
    - (int)OnOption:(int)optval optarg:(const char*)optarg optname:(const char*)optname optind:(int)optind argc:(int)argc argv:(char**)argv env:(char**)env;
    - (int)OnLoggingOption:(int)optval optarg:(const char*)optarg optname:(const char*)optname optind:(int)optind argc:(int)argc argv:(char**)argv env:(char**)env;
    - (const char*)OptionUsage:(const char*&)optarg longopt:(const struct option*)longopt;
    - (const char*)Options:(const struct option*&)longopts;
    - (const char*)Arguments:(const char**&)args;
@end
///////////////////////////////////////////////////////////////////////
/// Interface: iXosOptMain
///
///    Author: $author$
///      Date: 12/23/2012
///////////////////////////////////////////////////////////////////////
@interface iXosOptMain: iXosBaseMain <iXosOptMain> {
    bool m_didUsage;
    }
    - (iXosOptMain*)init;
    - (int)Run:(int)argc argv:(char**)argv env:(char**)env;
    - (int)Main:(int)argc argv:(char**)argv env:(char**)env;
    - (int)Usage:(int)argc argv:(char**)argv env:(char**)env;
    - (int)GetOptions:(int)argc argv:(char**)argv env:(char**)env;
    - (int)OnOption:(int)optval optarg:(const char*)optarg optname:(const char*)optname optind:(int)optind argc:(int)argc argv:(char**)argv env:(char**)env;
    - (const char*)OptionUsage:(const char*&)optarg longopt:(const struct option*)longopt;
    - (const char*)Options:(const struct option*&)longopts;
    - (const char*)Arguments:(const char**&)args;
@end
#else // defined(OBJC)  
#endif // defined(OBJC)

#endif // _XOS_GUI_COCOA_CONSOLE_IXOSOPTMAIN_HH 
