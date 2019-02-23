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
///   File: iHash.hh
///
/// Author: $author$
///   Date: 2/5/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_COCOA_CRYPTO_HASH_IHASH_HH
#define _XOS_GUI_COCOA_CRYPTO_HASH_IHASH_HH

#include "xos/gui/cocoa/iWindowMain.hh"

namespace xos {
namespace gui {
namespace crypto {
namespace hash {
namespace cocoa {

class _EXPORT_CLASS MainWindow;

} // namespace cocoa
} // namespace hash
} // namespace crypto
} // namespace gui
} // namespace xos

///////////////////////////////////////////////////////////////////////
/// Interface: iHashControlView
///////////////////////////////////////////////////////////////////////
@interface iHashControlView: iView {
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
    iButton* m_quit;
    }
    - (id)initWithFrameAndTarget:(iRect)frame target:(iObject*)target;
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
/// Interface: iHashMainView
///////////////////////////////////////////////////////////////////////
@interface iHashMainView: iMainView {
    iHashControlView* m_control;
    }
    - (id)initWithFrameAndTarget:(iRect)frame target:(iObject*)target;
    - (void)resizeSubviewsWithOldSize:(iSize)oldBoundsSize;
    - (iHashControlView*)control;
@end

///////////////////////////////////////////////////////////////////////
/// Interface: iHashMainWindow
///////////////////////////////////////////////////////////////////////
@interface iHashMainWindow: iMainWindow {
    xos::gui::crypto::hash::cocoa::MainWindow* m_mainWindow;
    }
    - (iMainWindow*)initWithRect:(iRect)contentRect mainWindow:(xos::gui::crypto::hash::cocoa::MainWindow*)mainWindow;
    - (void)dealloc;
    - (iView*)createMainView:(int)argc argv:(char**)argv env:(char**)env;
    - (void)okClicked:(id)sender;
    - (void)cancelClicked:(id)sender;
    - (void)quitClicked:(id)sender;
    - (void)upperClicked:(id)sender;
    - (void)updateFileHash:(id)sender;
    - (iDragOperation)draggingEntered:(id <iDraggingInfo>)sender;
    - (BOOL)performDragOperation:(id <iDraggingInfo>)sender;
@end

///////////////////////////////////////////////////////////////////////
/// Interface: iHashMain
///////////////////////////////////////////////////////////////////////
@interface iHashMain: iWindowMain {
    }
    - (iMainWindow*)createMainWindow:(iRect)contentRect argc:(int)argc argv:(char**)argv env:(char**)env;
@end

#endif // _XOS_GUI_COCOA_CRYPTO_HASH_IHASH_HH
