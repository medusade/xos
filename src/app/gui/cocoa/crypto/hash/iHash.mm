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
///   File: iHash.mm
///
/// Author: $author$
///   Date: 2/5/2014
///////////////////////////////////////////////////////////////////////
#include "iHash.hh"
#include "MainWindow.hh"

#define XOS_GUI_COCOA_CRYPTO_HASH_IHASH_HASH_SIZE 20
#define XOS_GUI_COCOA_CRYPTO_HASH_IHASH_HASH_NAME "Hash"

#define XOS_GUI_COCOA_CRYPTO_HASH_IHASH_WINWOW_TITLE_PREFIX "i"
#define XOS_GUI_COCOA_CRYPTO_HASH_IHASH_WINWOW_TITLE \
    XOS_GUI_COCOA_CRYPTO_HASH_IHASH_WINWOW_TITLE_PREFIX \
    XOS_GUI_COCOA_CRYPTO_HASH_IHASH_HASH_NAME

#define XOS_GUI_COCOA_CRYPTO_HASH_IHASH_CONTROL_BORDER 10
#define XOS_GUI_COCOA_CRYPTO_HASH_IHASH_CONTROL_LABEL_LENGTH 8
#define XOS_GUI_COCOA_CRYPTO_HASH_IHASH_CONTROL_HASH_LABEL "Hash"
#define XOS_GUI_COCOA_CRYPTO_HASH_IHASH_CONTROL_FILE_LABEL "File"
#define XOS_GUI_COCOA_CRYPTO_HASH_IHASH_CONTROL_TEXT_LABEL "Text"
#define XOS_GUI_COCOA_CRYPTO_HASH_IHASH_CONTROL_CASE_LABEL "Case"
#define XOS_GUI_COCOA_CRYPTO_HASH_IHASH_CONTROL_UPPER_LABEL "Upper"
#define XOS_GUI_COCOA_CRYPTO_HASH_IHASH_CONTROL_LOWER_LABEL "Lower"
#define XOS_GUI_COCOA_CRYPTO_HASH_IHASH_CONTROL_OK_LABEL "Ok"
#define XOS_GUI_COCOA_CRYPTO_HASH_IHASH_CONTROL_CANCEL_LABEL "Cancel"
#define XOS_GUI_COCOA_CRYPTO_HASH_IHASH_CONTROL_QUIT_LABEL "Quit"

#define XOS_GUI_COCOA_CRYPTO_HASH_IHASH_MENU_QUIT_KEY "q"
#define XOS_GUI_COCOA_CRYPTO_HASH_IHASH_MENU_QUIT_LABEL \
    XOS_GUI_COCOA_CRYPTO_HASH_IHASH_CONTROL_QUIT_LABEL " "

#define XOS_GUI_COCOA_CRYPTO_HASH_IHASH_CONTROL_HASH_SIZE 20
#define XOS_GUI_COCOA_CRYPTO_HASH_IHASH_CONTROL_HASH_SIZE_MAX 48

///////////////////////////////////////////////////////////////////////
/// Implentation: iHashControlView
///////////////////////////////////////////////////////////////////////
@implementation iHashControlView
- (id)initWithFrameAndTarget:(iRect)frame target:(iObject*)target {
    m_hashLabel = 0;
    m_hash = 0;
    m_upper = 0;
    m_fileLabel = 0;
    m_file = 0;
    m_ok = 0;
    m_textLabel = 0;
    m_text = 0;
    m_cancel = 0;
    m_progress = 0;
    m_quit = 0;
    if (([super initWithFrame:frame])) {
        iRect rect = [self bounds];
        const char* okLabel = XOS_GUI_COCOA_CRYPTO_HASH_IHASH_CONTROL_OK_LABEL;
        const char* cancelLabel = XOS_GUI_COCOA_CRYPTO_HASH_IHASH_CONTROL_CANCEL_LABEL;
        const char* quitLabel = XOS_GUI_COCOA_CRYPTO_HASH_IHASH_CONTROL_QUIT_LABEL;
        const char* upperLabel = XOS_GUI_COCOA_CRYPTO_HASH_IHASH_CONTROL_UPPER_LABEL;
        const char* textLabel = XOS_GUI_COCOA_CRYPTO_HASH_IHASH_CONTROL_TEXT_LABEL;
        const char* fileLabel = XOS_GUI_COCOA_CRYPTO_HASH_IHASH_CONTROL_FILE_LABEL;
        const char* hashLabel = xos::gui::crypto::hash::cocoa::MainWindow::GetTheHashName();
        size_t hashSize = xos::gui::crypto::hash::cocoa::MainWindow::GetTheHash().HashSize();
        size_t hashSizeMax = XOS_GUI_COCOA_CRYPTO_HASH_IHASH_CONTROL_HASH_SIZE_MAX;
        size_t labelLength = XOS_GUI_COCOA_CRYPTO_HASH_IHASH_CONTROL_LABEL_LENGTH;
        size_t buttonLabelLength = XOS_GUI_COCOA_CRYPTO_HASH_IHASH_CONTROL_LABEL_LENGTH;
        size_t x = XOS_GUI_COCOA_CRYPTO_HASH_IHASH_CONTROL_BORDER;
        size_t y = XOS_GUI_COCOA_CRYPTO_HASH_IHASH_CONTROL_BORDER;
        size_t rowWidth = XOS_GUI_COCOA_CRYPTO_HASH_IHASH_CONTROL_BORDER*2;
        size_t width = XOS_GUI_COCOA_CRYPTO_HASH_IHASH_CONTROL_BORDER*2;
        size_t height = XOS_GUI_COCOA_CRYPTO_HASH_IHASH_CONTROL_BORDER*2;
        size_t charWidth = 10;
        size_t charHeight = 20;
        size_t hashWidth;
        size_t hashWidthMax;
        iRect frame;

        [self setAutoresizesSubviews:NO];

        if (((hashWidth = hashSize*charWidth*2) > (hashWidthMax = hashSizeMax*charWidth*2)))
            hashWidth = hashWidthMax;

        frame = NSMakeRect(x+charWidth*labelLength, y, hashWidth, charHeight);

        if ((m_progress = [[iProgress alloc] initWithFrame:frame])) {
            [self addSubview:m_progress];
            if (width < (rowWidth += frame.size.width))
                width = rowWidth;
            height += frame.size.height;

            frame.origin.x += frame.size.width+2;
            frame.size.width = charWidth*buttonLabelLength;

            if ((m_quit = [[iButton alloc] initWithFrame:frame text:quitLabel target:target action:@selector(quitClicked:)])) {
                [self addSubview:m_quit];
                if (width < (rowWidth += frame.size.width))
                    width = rowWidth;
            }
            y += frame.size.height;
            rowWidth = XOS_GUI_COCOA_CRYPTO_HASH_IHASH_CONTROL_BORDER*2;
        }
        frame = NSMakeRect(x, y, charWidth*labelLength, charHeight);

        if ((m_textLabel = [[iLabel alloc] initWithFrame:frame text:textLabel])) {
            [self addSubview:m_textLabel];
            if (width < (rowWidth += frame.size.width))
                width = rowWidth;
            height += frame.size.height;
            frame.origin.x += frame.size.width;
            frame.size.width = hashWidth;

            if ((m_text = [[iEdit alloc] initWithFrame:frame])) {
                [self addSubview:m_text];
                if (width < (rowWidth += frame.size.width))
                    width = rowWidth;
                frame.origin.x += frame.size.width+2;
                frame.size.width = charWidth*buttonLabelLength;

                if ((m_cancel = [[iButton alloc] initWithFrame:frame text:cancelLabel target:target action:@selector(cancelClicked:)])) {
                    [self addSubview:m_cancel];
                    if (width < (rowWidth += frame.size.width))
                        width = rowWidth;
                }
            }
            y += frame.size.height;
            rowWidth = XOS_GUI_COCOA_CRYPTO_HASH_IHASH_CONTROL_BORDER*2;
        }
        frame = NSMakeRect(x, y, charWidth*labelLength, charHeight);

        if ((m_fileLabel = [[iLabel alloc] initWithFrame:frame text:fileLabel])) {
            [self addSubview:m_fileLabel];
            if (width < (rowWidth += frame.size.width))
                width = rowWidth;
            height += frame.size.height;
            frame.origin.x += frame.size.width;
            frame.size.width = hashWidth;

            if ((m_file = [[iEdit alloc] initWithFrame:frame])) {
                [self addSubview:m_file];
                if (width < (rowWidth += frame.size.width))
                    width = rowWidth;
                frame.origin.x += frame.size.width+2;
                frame.size.width = charWidth*buttonLabelLength;

                if ((m_ok = [[iButton alloc] initWithFrame:frame text:okLabel target:target action:@selector(okClicked:)])) {
                    [self addSubview:m_ok];
                    if (width < (rowWidth += frame.size.width))
                        width = rowWidth;
                }
            }
            y += frame.size.height;
            rowWidth = XOS_GUI_COCOA_CRYPTO_HASH_IHASH_CONTROL_BORDER*2;
        }
        frame = NSMakeRect(x, y, charWidth*labelLength, charHeight);

        if ((m_hashLabel = [[iLabel alloc] initWithFrame:frame text:hashLabel])) {
            [self addSubview:m_hashLabel];
            if (width < (rowWidth += frame.size.width))
                width = rowWidth;
            height += frame.size.height;
            frame.origin.x += frame.size.width;
            frame.size.width = hashWidth;

            if ((m_hash = [[iText alloc] initWithFrame:frame])) {
                [self addSubview:m_hash];
                if (width < (rowWidth += frame.size.width))
                    width = rowWidth;
                frame.origin.x += frame.size.width+2;
                frame.size.width = charWidth*buttonLabelLength;

                if ((m_upper = [[iCheck alloc] initWithFrame:frame text:upperLabel target:target action:@selector(upperClicked:)])) {
                    [m_upper setState:NSOnState];
                    [self addSubview:m_upper];
                    if (width < (rowWidth += frame.size.width))
                        width = rowWidth;
                }
            }
        }
        frame = [self frame];
        frame.size.width = width;
        frame.size.height = height;
        [self setFrame:frame];
    }
    return self;
}
- (void)setHash:(const xos::String&)text{
    if ((m_hash)) [m_hash setText:text];
}
- (void)getHash:(xos::String&)text{
    if ((m_hash)) [m_hash getText:text];
}
- (void)setFile:(const xos::String&)text{
    if ((m_file)) [m_file setText:text];
}
- (void)getFile:(xos::String&)text{
    if ((m_file)) [m_file getText:text];
}
- (void)setText:(const xos::String&)text{
    if ((m_text)) [m_text setText:text];
}
- (void)getText:(xos::String&)text{
    if ((m_text)) [m_text getText:text];
}
- (void)showProgress:(size_t)maximum amount:(size_t)amount {
    if ((m_progress)) {
        [m_progress setMaxValue:maximum];
        [m_progress setValue:amount];
        [m_progress show];
    }
}
- (void)updateProgress:(size_t)amount {
    if ((m_progress)) {
        [m_progress setValue:amount];
    }
}
- (void)hideProgress {
    if ((m_progress)) {
        [m_progress hide];
    }
}
@end

///////////////////////////////////////////////////////////////////////
/// Implentation: iHashMainView
///////////////////////////////////////////////////////////////////////
@implementation iHashMainView
- (id)initWithFrameAndTarget:(iRect)frame target:(iObject*)target {
    m_control = 0;
    if (([super initWithFrame:frame])) {
        iRect rect = [self bounds];
        if ((m_control = [[iHashControlView alloc] initWithFrameAndTarget:rect target:target])) {
            [self addSubview:m_control];
            [self resizeSubviewsWithOldSize:rect.size];
            [self setAutoresizesSubviews:YES];
        }
    }
    return self;
}
- (void)resizeSubviewsWithOldSize:(iSize)oldBoundsSize {
    if ((m_control)) {
        iRect cr = [m_control frame];
        iRect r = [self bounds];
        if ((r.size.width > cr.size.width)) {
            cr.origin.x = (r.size.width-cr.size.width)/2;
        }
        if ((r.size.height > cr.size.height)) {
            cr.origin.y = (r.size.height-cr.size.height)/2;
        }
        [m_control setFrameOrigin:cr.origin];
        [m_control setNeedsDisplay:YES];
    }
}
- (iHashControlView*)control {
    return m_control;
}
@end

//////////////////////////////////////////////////////////////////////
/// Implentation: iHashMainWindow
///////////////////////////////////////////////////////////////////////
@implementation iHashMainWindow
    - (iHashMainWindow*)initWithRect:(iRect)contentRect mainWindow:(xos::gui::crypto::hash::cocoa::MainWindow*)mainWindow {
        const char* chars;
        iString* string;
        [super initWithRect:contentRect];
        [self registerForDraggedTypes:[iArray arrayWithObjects:iFilenamesPboardType, nil]];
        if ((m_mainWindow = mainWindow))
            m_mainWindow->Init(self);
        if ((chars = xos::gui::crypto::hash::cocoa::MainWindow::GetTheHashName())) {
            xos::String name(XOS_GUI_COCOA_CRYPTO_HASH_IHASH_WINWOW_TITLE_PREFIX);
            name.Append(chars);
            if ((chars = name.Chars())) {
                if ((string = [NSString stringWithUTF8String:chars])) {
                    [self setTitle:string];
                }
            }
        } else {
            if ((string = [iString stringWithUTF8String:XOS_GUI_COCOA_CRYPTO_HASH_IHASH_WINWOW_TITLE]))
                [self setTitle:string];
        }
        return self;
    }
    - (void)dealloc {
        if ((m_mainWindow))
            m_mainWindow->Finish();
        [super dealloc];
    }
    - (iView*)createMainView:(int)argc argv:(char**)argv env:(char**)env {
        iRect contentRect = [[self contentView] bounds];
        contentRect.origin.x = 0; contentRect.origin.y = 0;
        if ((m_mainView = [[iHashMainView alloc] initWithFrameAndTarget:contentRect target:self])) {
            iHashControlView* control;
            [self setContentView:m_mainView];
            if ((control = ([m_mainView control]))) {
                NSRect cFrame = [control frame];
                [self setContentMinSize:cFrame.size];
                cFrame.size.width += 20;
                cFrame.size.height += 20;
                [self setContentSize:cFrame.size];
                if ((m_mainWindow))
                    m_mainWindow->SetControl(control);
            }
        }
        return m_mainView;
    }
    - (void)okClicked:(id)sender {
        XOS_LOG_DEBUG("Ok...");
        if ((m_mainWindow))
            m_mainWindow->Hash();
    }
    - (void)cancelClicked:(id)sender {
        XOS_LOG_DEBUG("Cancel...");
        if ((m_mainWindow))
            m_mainWindow->HashCancel();
    }
    - (void)quitClicked:(id)sender {
        iApplication* app;
        XOS_LOG_DEBUG("Quit...");
        if ((m_mainWindow))
            m_mainWindow->HashCancel();
        if ((app = [self application]))
            [app stop:self];
    }
    -(void)windowWillClose:(iNotification*)notification {
        iApplication* app;
        if ((m_mainWindow))
            m_mainWindow->HashCancel();
        if ((app = [self application]))
            [app stop:self];
    }
    - (void)upperClicked:(id)sender {
        iCheck* check;
        XOS_LOG_DEBUG("Upper...");
        if ((m_mainWindow) && (check = ((iCheck*)sender)))
            m_mainWindow->SetIsUpperX(iOnState == [check state]);
    }
    - (void)updateFileHash:(id)sender {
        XOS_LOG_DEBUG("Update...");
        if ((m_mainWindow))
            m_mainWindow->HashFileUpdate();
    }
    - (iDragOperation)draggingEntered:(id <iDraggingInfo>)sender {
        iPasteboard* pboard = [sender draggingPasteboard];
        iDragOperation sourceDragMask = [sender draggingSourceOperationMask];

        if ([[pboard types] containsObject:iFilenamesPboardType]) {
            if (sourceDragMask & iDragOperationLink) {
                return iDragOperationCopy;
            } else if (sourceDragMask & iDragOperationCopy) {
                return iDragOperationCopy;
            }
        }
        return iDragOperationNone;
    }
- (BOOL)performDragOperation:(id <iDraggingInfo>)sender {
    iPasteboard *pboard = [sender draggingPasteboard];
    iDragOperation sourceDragMask = [sender draggingSourceOperationMask];
    XOS_LOG_DEBUG("dropped");
    if ( [[pboard types] containsObject:iFilenamesPboardType] ) {
        iArray* files;
        if ((files = [pboard propertyListForType:iFilenamesPboardType])) {
            iString* fileName;
            XOS_LOG_DEBUG("dropped files");
            if ((fileName = [files objectAtIndex:0])) {
                const char* chars;
                if ((chars = [fileName UTF8String])) {
                    XOS_LOG_DEBUG("dropped file \"" << chars << "\"");
                    if ((m_mainView)) {
                        iHashControlView* control;
                        if ((control = [m_mainView control])) {
                            xos::String fileString(chars);
                            [control setFile:fileString];
                            if ((m_mainWindow))
                                m_mainWindow->Hash();
                            return YES;
                        }
                    }
                }
            }
        }
    }
    return NO;
}
@end

///////////////////////////////////////////////////////////////////////
/// Implentation: iHashMain
///////////////////////////////////////////////////////////////////////
@implementation iHashMain
    - (iMainWindow*)createMainWindow:(iRect)contentRect argc:(int)argc argv:(char**)argv env:(char**)env {
        static xos::gui::crypto::hash::cocoa::MainWindow mainWindow;
        iMainWindow* window;
        if ((window = [[iHashMainWindow alloc] initWithRect:contentRect mainWindow:&mainWindow])) {
            iMenu* menubar = [[iMenu new] autorelease];
            iMenuItem* appMenuItem = [[iMenuItem new] autorelease];
            iMenu* appMenu = [[iMenu new] autorelease];
            iString* appName = [[iProcessInfo processInfo] processName];
            iString* quitTitle = [@XOS_GUI_COCOA_CRYPTO_HASH_IHASH_MENU_QUIT_LABEL stringByAppendingString:appName];
            iMenuItem* quitMenuItem = [[[iMenuItem alloc] initWithTitle:quitTitle action:@selector(terminate:) keyEquivalent:@XOS_GUI_COCOA_CRYPTO_HASH_IHASH_MENU_QUIT_KEY] autorelease];
            [appMenu addItem:quitMenuItem];
            [appMenuItem setSubmenu:appMenu];
            [menubar addItem:appMenuItem];
            [m_app setMainMenu:menubar];
        }
        return window;
    }
@end

///////////////////////////////////////////////////////////////////////
/// Implentation: iMain
///////////////////////////////////////////////////////////////////////
@implementation iMain
    + (id<iMain>)create {
        return [[iHashMain alloc] init];
    }
@end
