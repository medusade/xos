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
///   File: iWindowMain.hh
///
/// Author: $author$
///   Date: 1/31/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_COCOA_IWINDOWMAIN_HH
#define _XOS_GUI_COCOA_IWINDOWMAIN_HH

#include "xos/gui/cocoa/iCocoa.hh"
#include "xos/gui/cocoa/iOptMain.hh"

#define XOS_GUI_COCOA_IWINDOWMAIN_WINWOW_TITLE "iWindowMain"
#define XOS_GUI_COCOA_IWINDOWMAIN_WINWOW_X 0
#define XOS_GUI_COCOA_IWINDOWMAIN_WINWOW_Y 2048
#define XOS_GUI_COCOA_IWINDOWMAIN_WINWOW_WIDTH 256
#define XOS_GUI_COCOA_IWINDOWMAIN_WINWOW_HEIGHT 256

#define XOS_GUI_COCOA_IWINDOWMAIN_VIEW_BG_COLOR whiteColor

#define XOS_GUI_COCOA_IWINDOWMAIN_WINDOW_STYLE iDefaultDesktopWindowMask
#define XOS_GUI_COCOA_IWINDOWMAIN_WINDOW_BACKING iDefaultDesktopWindowBacking
#define XOS_GUI_COCOA_IWINDOWMAIN_WINDOW_DEFER NO

///////////////////////////////////////////////////////////////////////
/// Protocol: iWindowDelegate
///////////////////////////////////////////////////////////////////////
@protocol iWindowDelegate <NSWindowDelegate>
@end

///////////////////////////////////////////////////////////////////////
/// Interface: iMainView
///////////////////////////////////////////////////////////////////////
@interface iMainView: iView {
    }
    - (void)drawRect:(iRect)rect;
@end

///////////////////////////////////////////////////////////////////////
/// Interface: iMainWindow
///////////////////////////////////////////////////////////////////////
@interface iMainWindow: iWindow <iWindowDelegate> {
    iView* m_mainView;
    iApplication* m_app;
    }
    - (iMainWindow*)initWithRect:(iRect)contentRect;
    - (iView*)createMainView:(int)argc argv:(char**)argv env:(char**)env;
    - (iApplication*)setApplication:(iApplication*)app;
    - (iApplication*)application;
    - (void)windowWillClose:(iNotification*)notification;
@end

///////////////////////////////////////////////////////////////////////
/// Interface: iWindowMain
///////////////////////////////////////////////////////////////////////
@interface iWindowMain: iOptMain <iOptMain> {
    iMainWindow* m_mainWindow;
    iApplication* m_app;
    iAutoreleasePool* m_pool;
    }
    - (id)init;
    - (iMainWindow*)createMainWindow:(iRect)contentRect argc:(int)argc argv:(char**)argv env:(char**)env;
    - (int)runApplication:(iApplication*)app argc:(int)argc argv:(char**)argv env:(char**)env;
    - (int)run:(int)argc argv:(char**)argv env:(char**)env;
@end

#endif // _XOS_GUI_COCOA_IWINDOWMAIN_HH 
