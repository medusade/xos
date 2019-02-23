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
///   File: iOptMain.hh
///
/// Author: $author$
///   Date: 1/31/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_COCOA_IOPTMAIN_HH
#define _XOS_GUI_COCOA_IOPTMAIN_HH

#include "xos/gui/cocoa/iMain.hh"
#include "xos/os/MainOpt.hpp"

///////////////////////////////////////////////////////////////////////
/// Protocol: iOpt
///////////////////////////////////////////////////////////////////////
@protocol iOpt
    - (int)usage:(int)argc argv:(char**)argv env:(char**)env;
    - (int)getOptions:(int)argc argv:(char**)argv env:(char**)env;
    - (int)onOption:(int)optval optarg:(const char*)optarg optname:(const char*)optname optind:(int)optind argc:(int)argc argv:(char**)argv env:(char**)env;
    - (int)onLoggingOption:(int)optval optarg:(const char*)optarg optname:(const char*)optname optind:(int)optind argc:(int)argc argv:(char**)argv env:(char**)env;
    - (const char*)optionUsage:(const char*&)optarg longopt:(const struct option*)longopt;
    - (const char*)options:(const struct option*&)longopts;
    - (const char*)arguments:(const char**&)args;
@end

///////////////////////////////////////////////////////////////////////
/// Protocol: iOptMain
///////////////////////////////////////////////////////////////////////
@protocol iOptMain <iRunMain, iOpt>
@end

///////////////////////////////////////////////////////////////////////
/// Interface: iOptMain
///////////////////////////////////////////////////////////////////////
@interface iOptMain: iRunMain <iOptMain> {
    bool m_didUsage;
    }
    - (id)init;
    - (int)usage:(int)argc argv:(char**)argv env:(char**)env;
    - (int)getOptions:(int)argc argv:(char**)argv env:(char**)env;
    - (int)onOption:(int)optval optarg:(const char*)optarg optname:(const char*)optname optind:(int)optind argc:(int)argc argv:(char**)argv env:(char**)env;
    - (int)onLoggingOption:(int)optval optarg:(const char*)optarg optname:(const char*)optname optind:(int)optind argc:(int)argc argv:(char**)argv env:(char**)env;
    - (const char*)optionUsage:(const char*&)optarg longopt:(const struct option*)longopt;
    - (const char*)options:(const struct option*&)longopts;
    - (const char*)arguments:(const char**&)args;
@end
#endif // _XOS_GUI_COCOA_IOPTMAIN_HH 
        

