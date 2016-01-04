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
///   File: iXosWindowMain.mm
///
/// Author: $author$
///   Date: 12/20/2012
///////////////////////////////////////////////////////////////////////
#include "iXosWindowMain.hh"

#if defined(OBJC)
///////////////////////////////////////////////////////////////////////
/// Implentation: iXosMainView
///
///       Author: $author$
///         Date: 12/20/2012
///////////////////////////////////////////////////////////////////////
@implementation iXosMainView
    - (void)drawRect:(NSRect)rect {
        [[NSColor DEFAULT_IXOSWINDOWMAIN_VIEW_BG_COLOR] set];
        NSRectFill([self bounds]);
    }
@end

///////////////////////////////////////////////////////////////////////
/// Implentation: iXosMainWindow
///
///       Author: $author$
///         Date: 12/21/2012
///////////////////////////////////////////////////////////////////////
@implementation iXosMainWindow
    - (NSView*)CreateMainView:(int)argc argv:(char**)argv env:(char**)env {
        iXosMainView* view = 0;
        if ((view = [[iXosMainView alloc] init])) {
        }
        return view;
    }
    - (NSApplication*)Application {
        return 0;
    }
    -(void)windowWillClose:(NSNotification*)notification {
        NSApplication* app;
        if ((app = [self Application]))
            [app stop:self];
        else
        [[NSApplication sharedApplication] stop:self];
    }
@end

///////////////////////////////////////////////////////////////////////
/// Implentation: iXosWindowMain
///
///       Author: $author$
///         Date: 12/20/2012
///////////////////////////////////////////////////////////////////////
@implementation iXosWindowMain
    - (iXosWindowMain*)init {
        [super init];
        m_pool = 0;
        m_app = 0;
        m_window = 0;
        return self;
    }
    - (iXosMainWindow*)CreateMainWindow:(int)argc argv:(char**)argv env:(char**)env {
        NSRect rect = NSMakeRect(DEFAULT_IXOSWINDOWMAIN_WINWOW_X,DEFAULT_IXOSWINDOWMAIN_WINWOW_Y, DEFAULT_IXOSWINDOWMAIN_WINWOW_WIDTH, DEFAULT_IXOSWINDOWMAIN_WINWOW_HEIGHT);
        NSUInteger style = NSTitledWindowMask| NSClosableWindowMask | NSMiniaturizableWindowMask | NSResizableWindowMask;
        NSBackingStoreType backing = NSBackingStoreBuffered;
        iXosMainWindow* window = 0;
        NSView* view = 0;

        if ((window = [[iXosMainWindow alloc] initWithContentRect:rect styleMask:style backing:backing defer:NO])) {
            [window setTitle:@DEFAULT_IXOSWINDOWMAIN_WINWOW_TITLE];
            [window setDelegate:window];
            if ((view = [window CreateMainView:argc argv:argv env:env])) {
                [window setContentView:view];
            }
        }
        return window;
    }
    - (int)BeforeRun:(int)argc argv:(char**)argv env:(char**)env {
        int err = 0;
        if ((m_window = [self CreateMainWindow:argc argv:argv env:env])) {
            [m_window makeKeyAndOrderFront: nil];
        }
        return err;
    }
    - (int)AfterRun:(int)argc argv:(char**)argv env:(char**)env {
        int err = 0;
        return err;
    }
    - (int)Run:(int)argc argv:(char**)argv env:(char**)env {
        int err = 0;
        if ((m_pool = [[NSAutoreleasePool alloc] init])) {
            if ((m_app = [NSApplication sharedApplication])) {
                if (!(err = [self BeforeRun:argc argv:argv env:env])) {
                    [m_app run];
                    err = [self AfterRun:argc argv:argv env:env];
                }
            }
            [m_pool release];
            m_pool = 0;
        }
        return err;
    }
@end
#else // defined(OBJC)  
#endif // defined(OBJC)  
