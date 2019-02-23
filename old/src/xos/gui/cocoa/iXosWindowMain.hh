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
///   File: iXosWindowMain.hh
///
/// Author: $author$
///   Date: 12/20/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_COCOA_IXOSWINDOWMAIN_HH
#define _XOS_GUI_COCOA_IXOSWINDOWMAIN_HH

#include <Cocoa/Cocoa.h>
#include "console/iXosOptMain.hh"

#define DEFAULT_IXOSWINDOWMAIN_WINWOW_TITLE "iXosWindowMain"
#define DEFAULT_IXOSWINDOWMAIN_WINWOW_X 0
#define DEFAULT_IXOSWINDOWMAIN_WINWOW_Y 2048
#define DEFAULT_IXOSWINDOWMAIN_WINWOW_WIDTH 256
#define DEFAULT_IXOSWINDOWMAIN_WINWOW_HEIGHT 256

#define DEFAULT_IXOSWINDOWMAIN_VIEW_BG_COLOR whiteColor

#if defined(OBJC)  
///////////////////////////////////////////////////////////////////////
/// Interface: iXosMainView
///
///    Author: $author$
///      Date: 12/20/2012
///////////////////////////////////////////////////////////////////////
@interface iXosMainView: NSView {
    }
    - (void)drawRect:(NSRect)rect;
@end

///////////////////////////////////////////////////////////////////////
/// Interface: iXosMainWindow
///
///    Author: $author$
///      Date: 12/21/2012
///////////////////////////////////////////////////////////////////////
@interface iXosMainWindow: NSWindow <NSWindowDelegate> {
    }
    - (NSView*)CreateMainView:(int)argc argv:(char**)argv env:(char**)env;
    - (NSApplication*)Application;
    - (void)windowWillClose:(NSNotification*)notification;
@end

///////////////////////////////////////////////////////////////////////
/// Protocol: iXosWindowMain
///
///   Author: $author$
///     Date: 12/20/2012
///////////////////////////////////////////////////////////////////////
@protocol iXosWindowMain <iXosOptMain>
    - (iXosMainWindow*)CreateMainWindow:(int)argc argv:(char**)argv env:(char**)env;
    - (int)BeforeRun:(int)argc argv:(char**)argv env:(char**)env;
    - (int)AfterRun:(int)argc argv:(char**)argv env:(char**)env;
@end

///////////////////////////////////////////////////////////////////////
/// Interface: iXosWindowMain
///
///    Author: $author$
///      Date: 12/20/2012
///////////////////////////////////////////////////////////////////////
@interface iXosWindowMain: iXosOptMain <iXosWindowMain> {
    NSAutoreleasePool *m_pool;
    NSApplication *m_app;
    iXosMainWindow *m_window;
    }
    - (iXosWindowMain*)init;
    - (iXosMainWindow*)CreateMainWindow:(int)argc argv:(char**)argv env:(char**)env;
    - (int)BeforeRun:(int)argc argv:(char**)argv env:(char**)env;
    - (int)AfterRun:(int)argc argv:(char**)argv env:(char**)env;
    - (int)Run:(int)argc argv:(char**)argv env:(char**)env;
@end
#else // defined(OBJC)  
#endif // defined(OBJC)  

#endif // _XOS_GUI_COCOA_IXOSWINDOWMAIN_HH 
