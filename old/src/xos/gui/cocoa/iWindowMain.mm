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
///   File: iWindowMain.mm
///
/// Author: $author$
///   Date: 1/31/2014
///////////////////////////////////////////////////////////////////////

#include "xos/gui/cocoa/iWindowMain.hh"

///////////////////////////////////////////////////////////////////////
/// Implentation: iMainView
///////////////////////////////////////////////////////////////////////
@implementation iMainView
    - (void)drawRect:(iRect)rect {
        [[NSColor XOS_GUI_COCOA_IWINDOWMAIN_VIEW_BG_COLOR] set];
        NSRectFill([self bounds]);
    }
@end

///////////////////////////////////////////////////////////////////////
/// Implentation: iMainWindow
///////////////////////////////////////////////////////////////////////
@implementation iMainWindow
    - (iMainWindow*)initWithRect:(iRect)contentRect {
        iWindowStyleMask style = XOS_GUI_COCOA_IWINDOWMAIN_WINDOW_STYLE;
        iBackingStoreType backing = XOS_GUI_COCOA_IWINDOWMAIN_WINDOW_BACKING;
        BOOL defer = XOS_GUI_COCOA_IWINDOWMAIN_WINDOW_DEFER;
        m_mainView = 0;
        m_app = 0;
        self = [super initWithContentRect:contentRect styleMask:style backing:backing defer:defer];
        [self setTitle:[iString stringWithUTF8String:XOS_GUI_COCOA_IWINDOWMAIN_WINWOW_TITLE]];
        [self setDelegate:self];
        return self;
    }
    - (iView*)createMainView:(int)argc argv:(char**)argv env:(char**)env {
        m_mainView = [[iMainView alloc] init];
        return m_mainView;
    }
    - (iApplication*)setApplication:(iApplication*)app {
        m_app = app;
        return m_app;
    }
    - (iApplication*)application {
        return m_app;
    }
    -(void)windowWillClose:(iNotification*)notification {
        iApplication* app;
        if ((app = [self application]))
            [app stop:self];
    }
@end

///////////////////////////////////////////////////////////////////////
/// Implentation: iWindowMain
///////////////////////////////////////////////////////////////////////
@implementation iWindowMain
    - (id)init {
        m_mainWindow = 0;
        m_app = 0;
        m_pool = 0;
        return self;
    }
    - (iMainWindow*)createMainWindow:(iRect)contentRect argc:(int)argc argv:(char**)argv env:(char**)env {
        iMainWindow* mainWindow = [[iMainWindow alloc] initWithRect:contentRect];
        return mainWindow;
    }
    - (int)runApplication:(iApplication*)app argc:(int)argc argv:(char**)argv env:(char**)env {
        int err = 0;
        [app run];
        return err;
    }
    - (int)run:(int)argc argv:(char**)argv env:(char**)env {
        iRect contentRect = iMakeRect(XOS_GUI_COCOA_IWINDOWMAIN_WINWOW_X,XOS_GUI_COCOA_IWINDOWMAIN_WINWOW_Y, XOS_GUI_COCOA_IWINDOWMAIN_WINWOW_WIDTH, XOS_GUI_COCOA_IWINDOWMAIN_WINWOW_HEIGHT);
        iView* mainView;
        int err = 0;
        XOS_LOG_TRACE("in...");
        if ((m_pool = [[iAutoreleasePool alloc] init])) {
            if ((m_app = [iApplication sharedApplication])) {
                if ((m_mainWindow = [self createMainWindow:contentRect argc:argc argv:argv env:env])) {
                    if ((mainView = [m_mainWindow createMainView:argc argv:argv env:env])) {
                        [m_mainWindow setApplication:m_app];
                        [m_mainWindow setContentView:mainView];
                        [m_mainWindow makeKeyAndOrderFront: nil];
                        err = [self runApplication:m_app argc:argc argv:argv env:env];
                    } else {
                        XOS_LOG_ERROR("failed on [m_mainWindow createMainView:...]");
                        [m_mainWindow release];
                        m_mainWindow = 0;
                    }
                } else {
                    XOS_LOG_ERROR("failed on [self createMainWindow...]");
                }
                m_app = 0;
            } else {
                XOS_LOG_ERROR("failed on [iApplication sharedApplication]");
            }
            [m_pool release];
            m_pool = 0;
        } else {
            XOS_LOG_ERROR("failed on [[iAutoreleasePool alloc] init]");
        }
        XOS_LOG_TRACE("...out");
        return err;
    }
@end
        

