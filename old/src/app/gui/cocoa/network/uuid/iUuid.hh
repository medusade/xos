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
///   File: iUuid.hh
///
/// Author: $author$
///   Date: 2/18/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_COCOA_NETWORK_UUID_IUUID_HH
#define _XOS_GUI_COCOA_NETWORK_UUID_IUUID_HH

#include "xos/gui/cocoa/iWindowMain.hh"

namespace xos {
namespace gui {
namespace cocoa {
namespace network {
namespace uuid {

class _EXPORT_CLASS MainWindow;

} // namespace uuid
} // namespace network
} // namespace cocoa
} // namespace gui
} // namespace xos

///////////////////////////////////////////////////////////////////////
/// Interface: iUuidControlView
///////////////////////////////////////////////////////////////////////
@interface iUuidControlView: iView {
    iLabel* m_uuidLabel;
    iEdit* m_uuid;
    iCheck* m_upper;

    iLabel* m_macAddressLabel;
    iPullDown* m_macAddress;
    iButton* m_ok;

    iLabel* m_typeLabel;
    iPullDown* m_type;
    iButton* m_cancel;

    iProgress* m_progress;
    iButton* m_quit;
    }
    - (id)initWithFrameAndTarget:(iRect)frame target:(iObject*)target;
    - (void)setUuid:(const xos::String&)text;
    - (void)getUuid:(xos::String&)text;
    - (void)clearMacAddress;
    - (void)addMacAddress:(const xos::String&)text;
    - (void)setMacAddress:(const xos::String&)text;
    - (void)getMacAddress:(xos::String&)text;
    - (void)clearType;
    - (void)addType:(const xos::String&)text;
    - (void)setType:(const xos::String&)text;
    - (void)getType:(xos::String&)text;
    - (void)showProgress:(size_t)maximum amount:(size_t)amount;
    - (void)updateProgress:(size_t)amount;
    - (void)hideProgress;
@end

///////////////////////////////////////////////////////////////////////
/// Interface: iUuidMainView
///////////////////////////////////////////////////////////////////////
@interface iUuidMainView: iMainView {
    iUuidControlView* m_control;
    }
    - (id)initWithFrameAndTarget:(iRect)frame target:(iObject*)target;
    - (void)resizeSubviewsWithOldSize:(iSize)oldBoundsSize;
    - (iUuidControlView*)control;
@end

///////////////////////////////////////////////////////////////////////
/// Interface: iUuidMainWindow
///////////////////////////////////////////////////////////////////////
@interface iUuidMainWindow: iMainWindow {
    xos::gui::cocoa::network::uuid::MainWindow* m_mainWindow;
    }
    - (iMainWindow*)initWithRect:(iRect)contentRect mainWindow:(xos::gui::cocoa::network::uuid::MainWindow*)mainWindow;
    - (void)dealloc;
    - (iView*)createMainView:(int)argc argv:(char**)argv env:(char**)env;
    - (void)okClicked:(id)sender;
    - (void)cancelClicked:(id)sender;
    - (void)quitClicked:(id)sender;
    - (void)upperClicked:(id)sender;
    - (void)updateFileUuid:(id)sender;
    - (iDragOperation)draggingEntered:(id <iDraggingInfo>)sender;
    - (BOOL)performDragOperation:(id <iDraggingInfo>)sender;
@end

///////////////////////////////////////////////////////////////////////
/// Interface: iUuidMain
///////////////////////////////////////////////////////////////////////
@interface iUuidMain: iWindowMain {
    }
    - (iMainWindow*)createMainWindow:(iRect)contentRect argc:(int)argc argv:(char**)argv env:(char**)env;
@end

#endif // _XOS_GUI_COCOA_NETWORK_UUID_IUUID_HH
