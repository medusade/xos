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
///   File: Main.hpp
///
/// Author: $author$
///   Date: 1/26/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_CRYPTO_HASH_QT_MAIN_HPP
#define _XOS_GUI_CRYPTO_HASH_QT_MAIN_HPP

#include "app/gui/crypto/hash/qt/MainWindow.hpp"
#include "xos/gui/qt/WindowMain.hpp"

namespace xos {
namespace gui {
namespace crypto {
namespace hash {
namespace qt {

typedef xos::gui::crypto::hash::qt::MainWindow MainWindow;
typedef xos::gui::qt::WindowMainImplement MainImplement;
typedef xos::gui::qt::WindowMain MainExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Main
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Main
: virtual public MainImplement, public MainExtend {
public:
    typedef MainImplement Implements;
    typedef MainExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Main() {
    }
    virtual ~Main() {
        if ((m_mainWindow))
            delete m_mainWindow;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual QMainWindow* CreateMainWindow
    (QApplication& qApplication,
     int argc, char** argv, char** env) {
        if ((m_mainWindow = new MainWindow(GetHash(), GetHashName()))) {
            if (!(m_mainWindow->Init())) {
                delete m_mainWindow;
                m_mainWindow = 0;
            }
        }
        return m_mainWindow;
    }
    virtual bool DestroyMainWindow
    (QMainWindow* mainWindow, QApplication& qApplication,
     int argc, char** argv, char** env) {
        bool isSuccess = false;
        if ((mainWindow) && (mainWindow == m_mainWindow)) {
            m_mainWindow->Finish();
            delete m_mainWindow;
            m_mainWindow = 0;
            isSuccess = true;
        }
        return isSuccess;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual xos::crypto::hash::Interface& GetHash() const;
    virtual const char* GetHashName() const;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    MainWindow* m_mainWindow;
};

} // namespace qt 
} // namespace hash 
} // namespace crypto 
} // namespace gui 
} // namespace xos 

#endif // _XOS_GUI_CRYPTO_HASH_QT_MAIN_HPP 
