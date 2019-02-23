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
///   MacAddress: iUuid.mm
///
/// Author: $author$
///   Date: 2/18/2014
///////////////////////////////////////////////////////////////////////
#include "iUuid.hh"
#include "MainWindow.hh"

#define XOS_GUI_COCOA_NETWORK_UUID_IUUID_UUID_SIZE 20
#define XOS_GUI_COCOA_NETWORK_UUID_IUUID_UUID_NAME "Uuid"

#define XOS_GUI_COCOA_NETWORK_UUID_IUUID_WINWOW_TITLE_PREFIX "i"
#define XOS_GUI_COCOA_NETWORK_UUID_IUUID_WINWOW_TITLE \
    XOS_GUI_COCOA_NETWORK_UUID_IUUID_WINWOW_TITLE_PREFIX \
    XOS_GUI_COCOA_NETWORK_UUID_IUUID_UUID_NAME

#define XOS_GUI_COCOA_NETWORK_UUID_IUUID_CONTROL_BORDER 10
#define XOS_GUI_COCOA_NETWORK_UUID_IUUID_CONTROL_LABEL_LENGTH 8
#define XOS_GUI_COCOA_NETWORK_UUID_IUUID_CONTROL_UUID_LABEL "Uuid"
#define XOS_GUI_COCOA_NETWORK_UUID_IUUID_CONTROL_MACADDRESS_LABEL "MacAddress"
#define XOS_GUI_COCOA_NETWORK_UUID_IUUID_CONTROL_TYPE_LABEL "Type"
#define XOS_GUI_COCOA_NETWORK_UUID_IUUID_CONTROL_CASE_LABEL "Case"
#define XOS_GUI_COCOA_NETWORK_UUID_IUUID_CONTROL_UPPER_LABEL "Upper"
#define XOS_GUI_COCOA_NETWORK_UUID_IUUID_CONTROL_LOWER_LABEL "Lower"
#define XOS_GUI_COCOA_NETWORK_UUID_IUUID_CONTROL_OK_LABEL "Ok"
#define XOS_GUI_COCOA_NETWORK_UUID_IUUID_CONTROL_CANCEL_LABEL "Cancel"
#define XOS_GUI_COCOA_NETWORK_UUID_IUUID_CONTROL_QUIT_LABEL "Quit"

#define XOS_GUI_COCOA_NETWORK_UUID_IUUID_CONTROL_UUID_SIZE 20
#define XOS_GUI_COCOA_NETWORK_UUID_IUUID_CONTROL_UUID_SIZE_MAX 48

///////////////////////////////////////////////////////////////////////
/// Implentation: iUuidControlView
///////////////////////////////////////////////////////////////////////
@implementation iUuidControlView
    - (id)initWithFrameAndTarget:(iRect)frame target:(iObject*)target {
        m_uuidLabel = 0;
        m_uuid = 0;
        m_upper = 0;
        m_macAddressLabel = 0;
        m_macAddress = 0;
        m_ok = 0;
        m_typeLabel = 0;
        m_type = 0;
        m_cancel = 0;
        m_progress = 0;
        if (([super initWithFrame:frame])) {
            iRect rect = [self bounds];
            const char* okLabel = XOS_GUI_COCOA_NETWORK_UUID_IUUID_CONTROL_OK_LABEL;
            const char* cancelLabel = XOS_GUI_COCOA_NETWORK_UUID_IUUID_CONTROL_CANCEL_LABEL;
            const char* quitLabel = XOS_GUI_COCOA_NETWORK_UUID_IUUID_CONTROL_QUIT_LABEL;
            const char* upperLabel = XOS_GUI_COCOA_NETWORK_UUID_IUUID_CONTROL_UPPER_LABEL;
            const char* typeLabel = XOS_GUI_COCOA_NETWORK_UUID_IUUID_CONTROL_TYPE_LABEL;
            const char* macAddressLabel = XOS_GUI_COCOA_NETWORK_UUID_IUUID_CONTROL_MACADDRESS_LABEL;
            const char* uuidLabel = XOS_GUI_COCOA_NETWORK_UUID_IUUID_CONTROL_UUID_LABEL;
            size_t uuidSize = XOS_GUI_COCOA_NETWORK_UUID_IUUID_CONTROL_UUID_SIZE;
            size_t uuidSizeMax = XOS_GUI_COCOA_NETWORK_UUID_IUUID_CONTROL_UUID_SIZE_MAX;
            size_t labelLength = XOS_GUI_COCOA_NETWORK_UUID_IUUID_CONTROL_LABEL_LENGTH;
            size_t buttonLabelLength = XOS_GUI_COCOA_NETWORK_UUID_IUUID_CONTROL_LABEL_LENGTH;
            size_t x = XOS_GUI_COCOA_NETWORK_UUID_IUUID_CONTROL_BORDER;
            size_t y = XOS_GUI_COCOA_NETWORK_UUID_IUUID_CONTROL_BORDER;
            size_t rowWidth = XOS_GUI_COCOA_NETWORK_UUID_IUUID_CONTROL_BORDER*2;
            size_t width = XOS_GUI_COCOA_NETWORK_UUID_IUUID_CONTROL_BORDER*2;
            size_t height = XOS_GUI_COCOA_NETWORK_UUID_IUUID_CONTROL_BORDER*2;
            size_t charWidth = 10;
            size_t charHeight = 20;
            size_t uuidWidth;
            size_t uuidWidthMax;
            iRect frame;

            [self setAutoresizesSubviews:NO];

            if (((uuidWidth = uuidSize*charWidth*2) > (uuidWidthMax = uuidSizeMax*charWidth*2)))
                uuidWidth = uuidWidthMax;

            frame = NSMakeRect(x+charWidth*labelLength, y, uuidWidth, charHeight);

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
                rowWidth = XOS_GUI_COCOA_NETWORK_UUID_IUUID_CONTROL_BORDER*2;
            }
            frame = NSMakeRect(x, y, charWidth*labelLength, charHeight);

            if ((m_macAddressLabel = [[iLabel alloc] initWithFrame:frame text:macAddressLabel])) {
                [self addSubview:m_macAddressLabel];
                if (width < (rowWidth += frame.size.width))
                    width = rowWidth;
                height += frame.size.height;
                frame.origin.x += frame.size.width;
                frame.size.width = uuidWidth;

                if ((m_macAddress = [[iPullDown alloc] initWithFrame:frame])) {
                    [self addSubview:m_macAddress];
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
                rowWidth = XOS_GUI_COCOA_NETWORK_UUID_IUUID_CONTROL_BORDER*2;
            }
            frame = NSMakeRect(x, y, charWidth*labelLength, charHeight);

            if ((m_typeLabel = [[iLabel alloc] initWithFrame:frame text:typeLabel])) {
                [self addSubview:m_typeLabel];
                if (width < (rowWidth += frame.size.width))
                    width = rowWidth;
                height += frame.size.height;
                frame.origin.x += frame.size.width;
                frame.size.width = uuidWidth;

                if ((m_type = [[iPullDown alloc] initWithFrame:frame])) {
                    [self addSubview:m_type];
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
                rowWidth = XOS_GUI_COCOA_NETWORK_UUID_IUUID_CONTROL_BORDER*2;
            }
            frame = NSMakeRect(x, y, charWidth*labelLength, charHeight);

            if ((m_uuidLabel = [[iLabel alloc] initWithFrame:frame text:uuidLabel])) {
                [self addSubview:m_uuidLabel];
                if (width < (rowWidth += frame.size.width))
                    width = rowWidth;
                height += frame.size.height;
                frame.origin.x += frame.size.width;
                frame.size.width = uuidWidth;

                if ((m_uuid = [[iText alloc] initWithFrame:frame])) {
                    [self addSubview:m_uuid];
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
    - (void)setUuid:(const xos::String&)text{
        if ((m_uuid)) [m_uuid setText:text];
    }
    - (void)getUuid:(xos::String&)text{
        if ((m_uuid)) [m_uuid getText:text];
    }
    - (void)clearMacAddress {
        if ((m_macAddress)) {
            const xos::String text;
            [m_macAddress removeAllItems];
            [m_macAddress addItemWithText:text];
        }
    }
    - (void)addMacAddress:(const xos::String&)text {
        if ((m_macAddress)) [m_macAddress addItemWithText:text];
    }
    - (void)setMacAddress:(const xos::String&)text {
    }
    - (void)getMacAddress:(xos::String&)text {
        if ((m_macAddress)) [m_macAddress getSelectedItemText:text];
    }
    - (void)clearType {
    }
    - (void)addType:(const xos::String&)text {
    }
    - (void)setType:(const xos::String&)text {
    }
    - (void)getType:(xos::String&)text {
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
/// Implentation: iUuidMainView
///////////////////////////////////////////////////////////////////////
@implementation iUuidMainView
    - (id)initWithFrameAndTarget:(iRect)frame target:(iObject*)target {
        m_control = 0;
        if (([super initWithFrame:frame])) {
            iRect rect = [self bounds];
            if ((m_control = [[iUuidControlView alloc] initWithFrameAndTarget:rect target:target])) {
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
    - (iUuidControlView*)control {
        return m_control;
    }
@end

//////////////////////////////////////////////////////////////////////
/// Implentation: iUuidMainWindow
///////////////////////////////////////////////////////////////////////
@implementation iUuidMainWindow
    - (iUuidMainWindow*)initWithRect:(iRect)contentRect mainWindow:(xos::gui::cocoa::network::uuid::MainWindow*)mainWindow {
        const char* chars;
        iString* string;
        [super initWithRect:contentRect];
        [self registerForDraggedTypes:[iArray arrayWithObjects:iFilenamesPboardType, nil]];
        if ((m_mainWindow = mainWindow))
            m_mainWindow->Init(self);
        if ((chars = XOS_GUI_COCOA_NETWORK_UUID_IUUID_UUID_NAME)) {
            xos::String name(XOS_GUI_COCOA_NETWORK_UUID_IUUID_WINWOW_TITLE_PREFIX);
            name.Append(chars);
            if ((chars = name.Chars())) {
                if ((string = [NSString stringWithUTF8String:chars])) {
                    [self setTitle:string];
                }
            }
        } else {
            if ((string = [iString stringWithUTF8String:XOS_GUI_COCOA_NETWORK_UUID_IUUID_WINWOW_TITLE]))
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
        if ((m_mainView = [[iUuidMainView alloc] initWithFrameAndTarget:contentRect target:self])) {
            iUuidControlView* control;
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
            m_mainWindow->UuidGenerate();
    }
    - (void)cancelClicked:(id)sender {
        XOS_LOG_DEBUG("Cancel...");
        if ((m_mainWindow))
            m_mainWindow->UuidGenerateCancel();
    }
    - (void)quitClicked:(id)sender {
        iApplication* app;
        XOS_LOG_DEBUG("Quit...");
        if ((m_mainWindow))
            m_mainWindow->UuidGenerateCancel();
        if ((app = [self application]))
            [app stop:self];
    }
    -(void)windowWillClose:(iNotification*)notification {
        iApplication* app;
        if ((m_mainWindow))
            m_mainWindow->UuidGenerateCancel();
        if ((app = [self application]))
            [app stop:self];
    }
    - (void)upperClicked:(id)sender {
        iCheck* check;
        XOS_LOG_DEBUG("Upper...");
        if ((m_mainWindow) && (check = ((iCheck*)sender)))
            m_mainWindow->SetIsUpperX(iOnState == [check state]);
    }
    - (void)updateFileUuid:(id)sender {
        XOS_LOG_DEBUG("Update...");
        if ((m_mainWindow))
            m_mainWindow->UuidGenerateUpdate();
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
                            iUuidControlView* control;
                            if ((control = [m_mainView control])) {
                                xos::String fileString(chars);
                                [control setFile:fileString];
                                if ((m_mainWindow))
                                    m_mainWindow->UuidGenerate();
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
/// Implentation: iUuidMain
///////////////////////////////////////////////////////////////////////
@implementation iUuidMain
    - (iMainWindow*)createMainWindow:(iRect)contentRect argc:(int)argc argv:(char**)argv env:(char**)env {
        static xos::gui::cocoa::network::uuid::MainWindow mainWindow;
        return [[iUuidMainWindow alloc] initWithRect:contentRect mainWindow:&mainWindow];
    }
@end

///////////////////////////////////////////////////////////////////////
/// Implentation: iMain
///////////////////////////////////////////////////////////////////////
@implementation iMain
    + (id<iMain>)create {
        return [[iUuidMain alloc] init];
    }
@end
