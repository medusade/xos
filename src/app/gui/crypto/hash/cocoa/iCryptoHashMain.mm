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
///   File: iCryptoHashMain.mm
///
/// Author: $author$
///   Date: 1/27/2014
///////////////////////////////////////////////////////////////////////
#include "app/gui/crypto/hash/cocoa/iCryptoHashMain.hh"
#include "xos/os/os/Thread.hpp"
#include "xos/os/os/Semaphore.hpp"
#include "xos/base/Waiter.hpp"

#define XOS_GUI_CRYPTO_HASH_COCOA_ICRYPTOHASH_WINWOW_TITLE_PREFIX "iXos"
#define XOS_GUI_CRYPTO_HASH_COCOA_ICRYPTOHASH_WINWOW_TITLE \
    XOS_GUI_CRYPTO_HASH_COCOA_ICRYPTOHASH_WINWOW_TITLE_PREFIX "CryptoHash"

#define XOS_GUI_CRYPTO_HASH_COCOA_ICRYPTOHASH_CONTROL_BORDER 10
#define XOS_GUI_CRYPTO_HASH_COCOA_ICRYPTOHASH_CONTROL_LABEL_LENGTH 8
#define XOS_GUI_CRYPTO_HASH_COCOA_ICRYPTOHASH_CONTROL_HASH_LABEL "Hash"
#define XOS_GUI_CRYPTO_HASH_COCOA_ICRYPTOHASH_CONTROL_FILE_LABEL "File"
#define XOS_GUI_CRYPTO_HASH_COCOA_ICRYPTOHASH_CONTROL_TEXT_LABEL "Text"
#define XOS_GUI_CRYPTO_HASH_COCOA_ICRYPTOHASH_CONTROL_CASE_LABEL "Case"
#define XOS_GUI_CRYPTO_HASH_COCOA_ICRYPTOHASH_CONTROL_UPPER_LABEL "Upper"
#define XOS_GUI_CRYPTO_HASH_COCOA_ICRYPTOHASH_CONTROL_LOWER_LABEL "Lower"
#define XOS_GUI_CRYPTO_HASH_COCOA_ICRYPTOHASH_CONTROL_OK_LABEL "Ok"
#define XOS_GUI_CRYPTO_HASH_COCOA_ICRYPTOHASH_CONTROL_CANCEL_LABEL "Cancel"

#define XOS_GUI_CRYPTO_HASH_COCOA_ICRYPTOHASH_CONTROL_HASH_SIZE 20
#define XOS_GUI_CRYPTO_HASH_COCOA_ICRYPTOHASH_CONTROL_HASH_SIZE_MAX 48

namespace xos {
namespace gui {
namespace crypto {
namespace hash {
namespace cocoa {

typedef xos::os::Thread Thread;
typedef xos::os::Semaphore Semaphore;
typedef xos::Waiter<Semaphore> Waiter;
///////////////////////////////////////////////////////////////////////
///  Class: ThreadRun
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS ThreadRun: public Thread::Run {
public:
    typedef Thread::Run Extends;
    ThreadRun(iCryptoHashMainWindow* mainWindow): m_mainWindow(mainWindow) {
    }
    virtual void operator()() {
        for (bool done = false; !done;) {
            try {
                volatile Waiter waitr(m_updateFileHash);
                XOS_LOG_DEBUG("...waited on m_updateFileHash");
                [m_mainWindow performSelectorOnMainThread:@selector(updateFileHash:) withObject:m_mainWindow waitUntilDone:NO];
            } catch (const WaitInterface::Status& status) {
                XOS_LOG_DEBUG("...failed wait m_updateFileHash");
                done = true;
            } catch (const Error& error) {
                XOS_LOG_ERROR("...failed " << error << " on wait m_updateFileHash");
                done = true;
            }
        }
    }
    void Stop() {
        m_updateFileHash.Destroy();
    }
    void UpdateFileHash() {
        m_updateFileHash.Release();
    }
protected:
    iCryptoHashMainWindow* m_mainWindow;
    Semaphore m_updateFileHash;
};

static ThreadRun* the_threadRun = 0;
static Thread* the_thread = 0;

///////////////////////////////////////////////////////////////////////
///  Class: MainWindow
///////////////////////////////////////////////////////////////////////
bool MainWindow::PostUpdateFileHashEvent() {
    if ((the_thread) && (the_threadRun)) {
        the_threadRun->UpdateFileHash();
        return true;
    }
    return false;
}

} // namespace cocoa
} // namespace hash
} // namespace crypto
} // namespace gui
} // namespace xos

///////////////////////////////////////////////////////////////////////
/// Implentation: iLabel
///////////////////////////////////////////////////////////////////////
@implementation iLabel
    - (id)initWithFrame:(NSRect)frame text:(const char*)text {
        NSString* string = 0;
        [super initWithFrame:frame];
        [self setBezeled:NO];
        [self setDrawsBackground:NO];
        [self setEditable:NO];
        [self setSelectable:NO];
        if ((string = [NSString stringWithUTF8String:text])) {
            [self setStringValue:string];
        }
        return self;
}
@end

///////////////////////////////////////////////////////////////////////
/// Implentation: iEdit
///////////////////////////////////////////////////////////////////////
@implementation iEdit
    - (id)initWithFrame:(NSRect)frame {
        if (([super initWithFrame:frame])) {
            NSCell* cell;
            if ((cell = [self cell])) {
                [cell setUsesSingleLineMode:YES];
                [cell setWraps:NO];
                [cell setScrollable:YES];
            }
        }
        return self;
    }
    - (void)setText:(const xos::String&)text {
        const char* chars;
        if ((chars = text.Chars())) {
            NSString* string;
            if ((string = [NSString stringWithUTF8String:chars])) {
                [self setStringValue:string];
            }
        }
    }
    - (void)getText:(xos::String&)text {
        NSString* string;
        if ((string = [self stringValue])) {
            const char* chars;
            if ((chars = [string UTF8String])) {
                text.Assign(chars);
            }
        }
    }
@end

///////////////////////////////////////////////////////////////////////
/// Implentation: iText
///////////////////////////////////////////////////////////////////////
@implementation iText
    - (id)initWithFrame:(NSRect)frame {
        [super initWithFrame:frame];
        [self setEditable:NO];
        [self setSelectable:YES];
        return self;
    }
@end

///////////////////////////////////////////////////////////////////////
/// Implentation: iButton
///////////////////////////////////////////////////////////////////////
@implementation iButton
- (id)initWithFrame:(NSRect)frame
               text:(const char*)text
              target:(NSObject*)target
              action:(SEL)action {
        NSString* string = 0;
        if (([super initWithFrame:frame])) {
            [self setTarget:target];
            [self setAction:action];
            if ((string = [NSString stringWithUTF8String:text])) {
                [self setTitle:string];
            }
        }
        return self;
}
@end

///////////////////////////////////////////////////////////////////////
/// Implentation: iCheck
///////////////////////////////////////////////////////////////////////
@implementation iCheck
- (id)initWithFrame:(NSRect)frame
               text:(const char*)text
              target:(NSObject*)target
              action:(SEL)action {
        if (([super initWithFrame:frame text:text target:target action:action])) {
            [self setButtonType:NSSwitchButton];
            [self setBezelStyle:0];
            [self setState:NSOffState];
        }
        return self;
}
@end

///////////////////////////////////////////////////////////////////////
/// Implentation: iProgress
///////////////////////////////////////////////////////////////////////
@implementation iProgress
    - (id)initWithFrame:(NSRect)frame {
        if (([super initWithFrame:frame])) {
            [self setMinValue:0];
            [self setMaxValue:100];
            [self setDoubleValue:50];
            [self setStyle:NSProgressIndicatorBarStyle];
            [self setIndeterminate:NO];
            [self setHidden:YES];
        }
        return self;
    }
    - (void)setValue:(size_t)value {
        [self setDoubleValue:value];
    }
    - (void)show {
        [self setHidden:NO];
        [self startAnimation:self];
    }
    - (void)hide {
        [self stopAnimation:self];
        [self setHidden:YES];
    }
@end

///////////////////////////////////////////////////////////////////////
/// Implentation: iCryptoHashControlView
///////////////////////////////////////////////////////////////////////
@implementation iCryptoHashControlView
    - (id)initWithFrameAndTarget:(NSRect)frame target:(NSObject*)target {
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
        if (([super initWithFrame:frame])) {
            NSRect rect = [self bounds];
            const char* okLabel = XOS_GUI_CRYPTO_HASH_COCOA_ICRYPTOHASH_CONTROL_OK_LABEL;
            const char* cancelLabel = XOS_GUI_CRYPTO_HASH_COCOA_ICRYPTOHASH_CONTROL_CANCEL_LABEL;
            const char* upperLabel = XOS_GUI_CRYPTO_HASH_COCOA_ICRYPTOHASH_CONTROL_UPPER_LABEL;
            const char* textLabel = XOS_GUI_CRYPTO_HASH_COCOA_ICRYPTOHASH_CONTROL_TEXT_LABEL;
            const char* fileLabel = XOS_GUI_CRYPTO_HASH_COCOA_ICRYPTOHASH_CONTROL_FILE_LABEL;
            const char* hashLabel = xos::gui::crypto::hash::cocoa::MainWindow::GetTheHashName();
            size_t hashSize = xos::gui::crypto::hash::cocoa::MainWindow::GetTheHash().HashSize();
            size_t hashSizeMax = XOS_GUI_CRYPTO_HASH_COCOA_ICRYPTOHASH_CONTROL_HASH_SIZE_MAX;
            size_t labelLength = XOS_GUI_CRYPTO_HASH_COCOA_ICRYPTOHASH_CONTROL_LABEL_LENGTH;
            size_t buttonLabelLength = XOS_GUI_CRYPTO_HASH_COCOA_ICRYPTOHASH_CONTROL_LABEL_LENGTH;
            size_t x = XOS_GUI_CRYPTO_HASH_COCOA_ICRYPTOHASH_CONTROL_BORDER;
            size_t y = XOS_GUI_CRYPTO_HASH_COCOA_ICRYPTOHASH_CONTROL_BORDER;
            size_t rowWidth = XOS_GUI_CRYPTO_HASH_COCOA_ICRYPTOHASH_CONTROL_BORDER*2;
            size_t width = XOS_GUI_CRYPTO_HASH_COCOA_ICRYPTOHASH_CONTROL_BORDER*2;
            size_t height = XOS_GUI_CRYPTO_HASH_COCOA_ICRYPTOHASH_CONTROL_BORDER*2;
            size_t charWidth = 10;
            size_t charHeight = 20;
            size_t hashWidth;
            size_t hashWidthMax;
            NSRect frame;

            [self setAutoresizesSubviews:NO];

            if (((hashWidth = hashSize*charWidth*2) > (hashWidthMax = hashSizeMax*charWidth*2)))
                hashWidth = hashWidthMax;

            frame = NSMakeRect(x+charWidth*labelLength, y, hashWidth, charHeight);

            if ((m_progress = [[iProgress alloc] initWithFrame:frame])) {
                [self addSubview:m_progress];
                if (width < (rowWidth += frame.size.width))
                    width = rowWidth;
                height += frame.size.height;
                y += frame.size.height;
                rowWidth = XOS_GUI_CRYPTO_HASH_COCOA_ICRYPTOHASH_CONTROL_BORDER*2;
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
                rowWidth = XOS_GUI_CRYPTO_HASH_COCOA_ICRYPTOHASH_CONTROL_BORDER*2;
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
                rowWidth = XOS_GUI_CRYPTO_HASH_COCOA_ICRYPTOHASH_CONTROL_BORDER*2;
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
/// Implentation: iCryptoHashMainView
///////////////////////////////////////////////////////////////////////
@implementation iCryptoHashMainView
    - (id)initWithFrameAndTarget:(NSRect)frame target:(NSObject*)target {
        m_control = 0;
        if (([super initWithFrame:frame])) {
            NSRect rect = [self bounds];
            if ((m_control = [[iCryptoHashControlView alloc] initWithFrameAndTarget:rect target:target])) {
                [self addSubview:m_control];
                [self resizeSubviewsWithOldSize:rect.size];
                [self setAutoresizesSubviews:YES];
            }
        }
        return self;
    }
    - (void)resizeSubviewsWithOldSize:(NSSize)oldBoundsSize {
        if ((m_control)) {
            NSRect cr = [m_control frame];
            NSRect r = [self bounds];
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
    - (iCryptoHashControlView*)control {
        return m_control;
    }
@end

///////////////////////////////////////////////////////////////////////
/// Implentation: iCryptoHashMainWindow
///////////////////////////////////////////////////////////////////////
@implementation iCryptoHashMainWindow
    - (id)initWithSize:(NSSize)size app:(NSApplication*)app {
        NSRect superRect = [[NSScreen mainScreen] visibleFrame];
        NSRect contentRect = NSMakeRect(superRect.origin.x, superRect.origin.y+superRect.size.height-size.height, size.width, size.height);
        NSUInteger windowStyle = NSTitledWindowMask| NSClosableWindowMask | NSMiniaturizableWindowMask | NSResizableWindowMask;
        NSBackingStoreType bufferingType = NSBackingStoreBuffered;
        BOOL deferCreation = NO;
        const char* nameChars = 0;
        m_app = app;
        m_mainView = 0;
        if (([super initWithContentRect:contentRect styleMask:windowStyle backing:bufferingType defer:deferCreation])) {
            [self setTitle:@XOS_GUI_CRYPTO_HASH_COCOA_ICRYPTOHASH_WINWOW_TITLE];
            [self setDelegate:self];
            [self registerForDraggedTypes:[NSArray arrayWithObjects:NSFilenamesPboardType, nil]];
            if ((nameChars = xos::gui::crypto::hash::cocoa::MainWindow::GetTheHashName())) {
                xos::String name(XOS_GUI_CRYPTO_HASH_COCOA_ICRYPTOHASH_WINWOW_TITLE_PREFIX);
                NSString* string;
                name.Append(nameChars);
                if ((nameChars = name.Chars())) {
                    if ((string = [NSString stringWithUTF8String:nameChars])) {
                        [self setTitle:string];
                    }
                }
            }
            contentRect = [[self contentView] bounds];
            contentRect.origin.x = 0; contentRect.origin.y = 0;
            if ((m_mainView = [[iCryptoHashMainView alloc] initWithFrameAndTarget:contentRect target:self])) {
                iCryptoHashControlView* control;
                [self setContentView:m_mainView];
                if ((control = (m_mainWindow.control() = [m_mainView control]))) {
                    NSRect cFrame = [control frame];
                    [self setContentMinSize:cFrame.size];
                    cFrame.size.width += 20;
                    cFrame.size.height += 20;
                    [self setContentSize:cFrame.size];
                }
            }
        }
        return self;
    }
    - (void)okClicked:(id)sender {
        XOS_LOG_DEBUG("Ok...");
        m_mainWindow.Hash();
    }
    - (void)cancelClicked:(id)sender {
        XOS_LOG_DEBUG("Cancel...");
        m_mainWindow.HashCancel();
    }
    - (void)upperClicked:(id)sender {
        iCheck* check;
        XOS_LOG_DEBUG("Upper...");
        if ((check = ((iCheck*)sender)))
            m_mainWindow.SetIsUpperX(NSOnState == [check state]);
    }
    - (void)updateFileHash:(id)sender {
        XOS_LOG_DEBUG("Update...");
        m_mainWindow.HashFileUpdate();
    }
    - (NSDragOperation)draggingEntered:(id <NSDraggingInfo>)sender {
        NSPasteboard* pboard = [sender draggingPasteboard];
        NSDragOperation sourceDragMask = [sender draggingSourceOperationMask];

        if ([[pboard types] containsObject:NSFilenamesPboardType]) {
            if (sourceDragMask & NSDragOperationLink) {
                return NSDragOperationCopy;
            } else if (sourceDragMask & NSDragOperationCopy) {
                return NSDragOperationCopy;
            }
        }
        return NSDragOperationNone;
    }
    - (BOOL)performDragOperation:(id <NSDraggingInfo>)sender {
        NSPasteboard *pboard = [sender draggingPasteboard];
        NSDragOperation sourceDragMask = [sender draggingSourceOperationMask];
        XOS_LOG_DEBUG("dropped");
        if ( [[pboard types] containsObject:NSFilenamesPboardType] ) {
            NSArray* files;
            if ((files = [pboard propertyListForType:NSFilenamesPboardType])) {
                NSString* fileName;
                XOS_LOG_DEBUG("dropped files");
                if ((fileName = [files objectAtIndex:0])) {
                    const char* chars;
                    if ((chars = [fileName UTF8String])) {
                        XOS_LOG_DEBUG("dropped file \"" << chars << "\"");
                        if ((m_mainView)) {
                            iCryptoHashControlView* control;
                            if ((control = [m_mainView control])) {
                                xos::String fileString(chars);
                                [control setFile:fileString];
                                m_mainWindow.Hash();
                                return YES;
                            }
                        }
                    }
                }
            }
        }
        return NO;
    }
    - (NSApplication*)Application {
        return m_app;
    }
@end

///////////////////////////////////////////////////////////////////////
/// Implentation: iCryptoHashMain
///////////////////////////////////////////////////////////////////////
@implementation iCryptoHashMain
    - (iXosMainWindow*)CreateMainWindow:(int)argc argv:(char**)argv env:(char**)env {
        NSSize size = NSMakeSize(DEFAULT_IXOSWINDOWMAIN_WINWOW_WIDTH, DEFAULT_IXOSWINDOWMAIN_WINWOW_HEIGHT);
        iCryptoHashMainWindow* mainWindow;
        if ((mainWindow = [[iCryptoHashMainWindow alloc] initWithSize:size app:m_app])) {
            if ((xos::gui::crypto::hash::cocoa::the_threadRun = new xos::gui::crypto::hash::cocoa::ThreadRun(mainWindow))) {
                xos::gui::crypto::hash::cocoa::the_thread = new xos::gui::crypto::hash::cocoa::Thread(*xos::gui::crypto::hash::cocoa::the_threadRun);
            }
        }
        return mainWindow;
    }
    - (int)BeforeRun:(int)argc argv:(char**)argv env:(char**)env {
        int err = [super BeforeRun:argc argv:argv env:env];
        return err;
    }
    - (int)AfterRun:(int)argc argv:(char**)argv env:(char**)env {
        int err = 0;
        if ((xos::gui::crypto::hash::cocoa::the_thread)) {
            xos::gui::crypto::hash::cocoa::the_threadRun->Stop();
            delete xos::gui::crypto::hash::cocoa::the_thread;
        }
        if ((xos::gui::crypto::hash::cocoa::the_threadRun)) {
            delete xos::gui::crypto::hash::cocoa::the_threadRun;
        }
        err = [super AfterRun:argc argv:argv env:env];
        return err;
    }
@end

///////////////////////////////////////////////////////////////////////
/// Implentation: iXosMain
///////////////////////////////////////////////////////////////////////
@implementation iXosMain
+ (id<iXosMain>)Allocate {
    return [[iCryptoHashMain alloc] init];
}
@end
