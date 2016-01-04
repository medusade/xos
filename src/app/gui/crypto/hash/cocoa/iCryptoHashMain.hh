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
///   File: iCryptoHashMain.hh
///
/// Author: $author$
///   Date: 1/27/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_CRYPTO_HASH_COCOA_ICRYPTOHASHMAIN_HH
#define _XOS_GUI_CRYPTO_HASH_COCOA_ICRYPTOHASHMAIN_HH

#include "xos/gui/cocoa/iXosWindowMain.hh"
#include "app/gui/crypto/hash/MainWindow.hpp"

///////////////////////////////////////////////////////////////////////
/// Interface: iLabel
///////////////////////////////////////////////////////////////////////
@interface iLabel: NSTextField {
    }
    - (id)initWithFrame:(NSRect)frame text:(const char*)text;
@end

///////////////////////////////////////////////////////////////////////
/// Interface: iEdit
///////////////////////////////////////////////////////////////////////
@interface iEdit: NSTextField {
    }
    - (id)initWithFrame:(NSRect)frame;
    - (void)setText:(const xos::String&)text;
    - (void)getText:(xos::String&)text;
@end

///////////////////////////////////////////////////////////////////////
/// Interface: iText
///////////////////////////////////////////////////////////////////////
@interface iText: iEdit {
    }
    - (id)initWithFrame:(NSRect)frame;
@end

///////////////////////////////////////////////////////////////////////
/// Interface: iButton
///////////////////////////////////////////////////////////////////////
@interface iButton: NSButton {
    }
    - (id)initWithFrame:(NSRect)frame
                   text:(const char*)text
                  target:(NSObject*)target
                  action:(SEL)action;
@end

///////////////////////////////////////////////////////////////////////
/// Interface: iCheck
///////////////////////////////////////////////////////////////////////
@interface iCheck: iButton {
    }
    - (id)initWithFrame:(NSRect)frame
                   text:(const char*)text
                  target:(NSObject*)target
                  action:(SEL)action;
@end

///////////////////////////////////////////////////////////////////////
/// Interface: iProgress
///////////////////////////////////////////////////////////////////////
@interface iProgress: NSProgressIndicator {
    }
    - (id)initWithFrame:(NSRect)frame;
    - (void)setValue:(size_t)value;
    - (void)show;
    - (void)hide;
@end

///////////////////////////////////////////////////////////////////////
/// Interface: iCryptoHashControlView
///////////////////////////////////////////////////////////////////////
@interface iCryptoHashControlView: NSView {
    iLabel* m_hashLabel;
    iEdit* m_hash;
    iCheck* m_upper;

    iLabel* m_fileLabel;
    iEdit* m_file;
    iButton* m_ok;

    iLabel* m_textLabel;
    iEdit* m_text;
    iButton* m_cancel;

    iProgress* m_progress;
    }
    - (id)initWithFrameAndTarget:(NSRect)frame target:(NSObject*)target;
    - (void)setHash:(const xos::String&)text;
    - (void)getHash:(xos::String&)text;
    - (void)setFile:(const xos::String&)text;
    - (void)getFile:(xos::String&)text;
    - (void)setText:(const xos::String&)text;
    - (void)getText:(xos::String&)text;
    - (void)showProgress:(size_t)maximum amount:(size_t)amount;
    - (void)updateProgress:(size_t)amount;
    - (void)hideProgress;
@end

///////////////////////////////////////////////////////////////////////
/// Interface: iCryptoHashMainView
///////////////////////////////////////////////////////////////////////
@interface iCryptoHashMainView: NSView {
    iCryptoHashControlView* m_control;
    }
    - (id)initWithFrameAndTarget:(NSRect)frame target:(NSObject*)target;
    - (void)resizeSubviewsWithOldSize:(NSSize)oldBoundsSize;
    - (iCryptoHashControlView*)control;
@end

namespace xos {
namespace gui {
namespace crypto {
namespace hash {
namespace cocoa {

typedef hash::MainWindow<ExportBase> MainWindowExtend;
///////////////////////////////////////////////////////////////////////
///  Class: MainWindow
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS MainWindow: public MainWindowExtend {
public:
    typedef MainWindowExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    MainWindow()
    : Extends(GetTheHash(), GetTheHashName()),
      m_control(0) {
    }
    virtual ~MainWindow() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Hash() {
        String s;
        if (GetHashText(s)) {
            XOS_LOG_DEBUG("text = \"" << s << "\"");
            if (0 < s.Length())
                return Extends::HashText();
        }
        if (GetHashFileName(s)) {
            XOS_LOG_DEBUG("file = \"" << s << "\"");
            if (0 < s.Length())
                return Extends::HashFile();
        }
        return Extends::HashBlank();
    }
    virtual bool HashFileUpdate() {
        return Extends::HashFileUpdate();
    }
    virtual bool HashCancel() {
        return Extends::HashCancel();
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool SetIsUpperX(bool to = true) {
        return Extends::SetIsUpperX(to);
    }
    virtual bool GetIsUpperX() const {
        return Extends::GetIsUpperX();
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    inline iCryptoHashControlView*& control() const {
        return (iCryptoHashControlView*&)(m_control);
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    static xos::crypto::hash::Interface& GetTheHash();
    static const char* GetTheHashName();
protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool GetHashText(String& hashText) {
        if ((m_control)) {
            [m_control getText:hashText];
            return true;
        }
        return false;
    }
    virtual bool GetHashFileName(String& fileName) {
        if ((m_control)) {
            [m_control getFile:fileName];
            return true;
        }
        return false;
    }
    virtual bool PostUpdateFileHashEvent();
    virtual bool ShowHash(const String& hashX) {
        if ((m_control)) {
            [m_control setHash:hashX];
            return true;
        }
        return false;
    }
    virtual bool ClearHash() {
        if ((m_control)) {
            String hashText;
            [m_control setHash:hashText];
            return true;
        }
        return false;
    }
    virtual bool ShowProgress(size_t maximum, size_t amount) {
        if ((m_control)) {
            [m_control showProgress:maximum amount:amount];
            return true;
        }
        return false;
    }
    virtual bool UpdateProgress(size_t amount) {
        if ((m_control)) {
            [m_control updateProgress:amount];
            return true;
        }
        return false;
    }
    virtual bool HideProgress() {
        if ((m_control)) {
            [m_control hideProgress];
            return true;
        }
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    iCryptoHashControlView* m_control;
};

} // namespace cocoa
} // namespace hash
} // namespace crypto
} // namespace gui
} // namespace xos

///////////////////////////////////////////////////////////////////////
/// Interface: iCryptoHashMainWindow
///////////////////////////////////////////////////////////////////////
@interface iCryptoHashMainWindow: iXosMainWindow {
    NSApplication* m_app;
    iCryptoHashMainView* m_mainView;
    xos::gui::crypto::hash::cocoa::MainWindow m_mainWindow;
    }
    - (id)initWithSize:(NSSize)size app:(NSApplication*)app;
    - (void)okClicked:(id)sender;
    - (void)cancelClicked:(id)sender;
    - (void)upperClicked:(id)sender;
    - (void)updateFileHash:(id)sender;
    - (NSDragOperation)draggingEntered:(id <NSDraggingInfo>)sender;
    - (BOOL)performDragOperation:(id <NSDraggingInfo>)sender;
    - (NSApplication*)Application;
@end

///////////////////////////////////////////////////////////////////////
/// Interface: iCryptoHashMain
///////////////////////////////////////////////////////////////////////
@interface iCryptoHashMain: iXosWindowMain {
    }
    - (iXosMainWindow*)CreateMainWindow:(int)argc argv:(char**)argv env:(char**)env;
    - (int)BeforeRun:(int)argc argv:(char**)argv env:(char**)env;
    - (int)AfterRun:(int)argc argv:(char**)argv env:(char**)env;
@end

#endif // _XOS_GUI_CRYPTO_HASH_COCOA_ICRYPTOHASHMAIN_HH 
