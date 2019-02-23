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
///   File: MainWindow.hh
///
/// Author: $author$
///   Date: 2/18/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_COCOA_NETWORK_UUID_MAINWINDOW_HH
#define _XOS_GUI_COCOA_NETWORK_UUID_MAINWINDOW_HH

#include "iUuid.hh"
#include "../../../network/uuid/MainWindow.hpp"
#include "xos/base/Base.hpp"

namespace xos {
namespace gui {
namespace cocoa {
namespace network {
namespace uuid {

typedef gui::network::uuid::MainWindow MainWindowExtend;
///////////////////////////////////////////////////////////////////////
///  Class: MainWindow
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS MainWindow: public MainWindowExtend {
public:
    typedef MainWindowExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    MainWindow()
    : m_controlView(0) {
    }
    virtual ~MainWindow() {
        Finish();
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Init(iUuidMainWindow* mainWindow) {
        return Extends::Init();
    }
    virtual bool Finish() {
        return Extends::Finish();
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool UuidGenerate() {
        return Extends::UuidGenerate();
    }
    virtual bool UuidGenerateUpdate() {
        return Extends::UuidGenerateUpdate();
    }
    virtual bool UuidGenerateCancel() {
        return Extends::UuidGenerateCancel();
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
    inline iUuidControlView* SetControl(iUuidControlView* control) {
        if ((m_controlView = control))
            GetMacAddresses();
        return m_controlView;
    }
    inline iUuidControlView* GetControl() const {
        return m_controlView;
    }
    inline iUuidControlView*& control() const {
        return (iUuidControlView*&)(m_controlView);
    }
protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool PostUuidGenerateEvent() {
        return false;
    }
    virtual bool GetUuidText(String& uuidText) {
        if ((m_controlView)) {
            [m_controlView getText:uuidText];
            return true;
        }
        return false;
    }
    virtual bool GetUuidFileName(String& fileName) {
        if ((m_controlView)) {
            [m_controlView getFile:fileName];
            return true;
        }
        return false;
    }
    virtual bool ShowUuid(const String& uuidX) {
        if ((m_controlView)) {
            [m_controlView setUuid:uuidX];
            return true;
        }
        return false;
    }
    virtual bool ClearUuid() {
        if ((m_controlView)) {
            String uuidText;
            [m_controlView setUuid:uuidText];
            return true;
        }
        return false;
    }
    virtual bool AddMacAddress(const String& macAddressX) {
        if ((m_controlView)) {
            [m_controlView addMacAddress:macAddressX];
            return true;
        }
        return false;
    }
    virtual bool ClearMacAddresses() {
        if ((m_controlView)) {
            [m_controlView clearMacAddress];
            return true;
        }
        return false;
    }
    virtual bool SetMacAddress(const String& macAddressX) {
        if ((m_controlView)) {
            [m_controlView setMacAddress:macAddressX];
            return true;
        }
        return false;
    }
    virtual bool GetMacAddress(String& macAddressX) const {
        if ((m_controlView)) {
            [m_controlView getMacAddress:macAddressX];
            return true;
        }
        return false;
    }
    virtual bool ShowProgress(size_t maximum, size_t amount) {
        if ((m_controlView)) {
            [m_controlView showProgress:maximum amount:amount];
            return true;
        }
        return false;
    }
    virtual bool UpdateProgress(size_t amount) {
        if ((m_controlView)) {
            [m_controlView updateProgress:amount];
            return true;
        }
        return false;
    }
    virtual bool HideProgress() {
        if ((m_controlView)) {
            [m_controlView hideProgress];
            return true;
        }
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    iUuidControlView* m_controlView;
};

} // namespace uuid
} // namespace network 
} // namespace cocoa 
} // namespace gui 
} // namespace xos 

#endif // _XOS_GUI_COCOA_NETWORK_UUID_MAINWINDOW_HH 
