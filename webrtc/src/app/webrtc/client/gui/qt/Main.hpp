///////////////////////////////////////////////////////////////////////
/// Copyright 2013, Google Inc.
///
/// Redistribution and use in source and binary forms, with or without
/// modification, are permitted provided that the following conditions are met:
/// 
///  1. Redistributions of source code must retain the above copyright notice,
///     this list of conditions and the following disclaimer.
///  2. Redistributions in binary form must reproduce the above copyright notice,
///     this list of conditions and the following disclaimer in the documentation
///     and/or other materials provided with the distribution.
///  3. The name of the author may not be used to endorse or promote products
///     derived from this software without specific prior written permission.
/// 
/// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
/// WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
/// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
/// EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
/// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
/// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
/// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
/// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
/// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
/// ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
///
///   File: Main.hpp
///
/// Author: $author$
///   Date: 8/1/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_APP_WEBRTC_CLIENT_GUI_QT_MAIN_HPP
#define _XOS_APP_WEBRTC_CLIENT_GUI_QT_MAIN_HPP

#include "app/webrtc/client/gui/qt/MainWindow.hpp"
#include "app/webrtc/client/gui/Main.hpp"
#include "xos/gui/qt/WindowMain.hpp"

#define XOS_APP_WEBRTC_CLIENT_GUI_QT_MAIN_OPTIONS_CHARS \
        XOS_APP_WEBRTC_CLIENT_GUI_MAIN_OPTIONS_CHARS \
        XOS_GUI_QT_MAIN_OPTIONS_CHARS

#define XOS_APP_WEBRTC_CLIENT_GUI_QT_MAIN_OPTIONS_OPTIONS \
            XOS_APP_WEBRTC_CLIENT_GUI_MAIN_OPTIONS_OPTIONS \
            XOS_GUI_QT_MAIN_OPTIONS_OPTIONS

namespace xos {
namespace app {
namespace webrtc {
namespace client {
namespace gui {
namespace qt {

typedef xos::gui::qt::WindowMainImplement MainImplement;
typedef xos::app::webrtc::client::gui::MainT
<MainImplement, xos::gui::qt::WindowMain> MainExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Main
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Main
: virtual public MainImplement, public MainExtend {
public:
    typedef MainImplement Implements;
    typedef MainExtend Extends;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: Main
    ///////////////////////////////////////////////////////////////////////
    Main(): m_mainWindow(0) {
    }
    virtual ~Main() {
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual QMainWindow* CreateMainWindow
    (QApplication& qApplication, int argc, char** argv, char** env)
    {
        if ((m_mainWindow = new MainWindow(m_useOpenGL, m_useWindow))) {
            if ((m_mainWindow->Init()))
                return m_mainWindow;
            delete m_mainWindow;
            m_mainWindow = 0;
        }
        return m_mainWindow;
    }
    virtual bool DestroyMainWindow
    (QMainWindow* mainWindow, QApplication& qApplication, 
     int argc, char** argv, char** env)
    {
        bool isSuccess = false;
        if ((isSuccess = ((mainWindow != 0) && (mainWindow == m_mainWindow)))) {
            isSuccess = m_mainWindow->Finish();
            delete m_mainWindow;
            m_mainWindow = 0;
        }
        return isSuccess;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const char* Options
    (const struct option*& longopts)
    {
        int err = 0;
        static const char* chars = XOS_APP_WEBRTC_CLIENT_GUI_QT_MAIN_OPTIONS_CHARS;
        static struct option optstruct[]= {
            XOS_APP_WEBRTC_CLIENT_GUI_QT_MAIN_OPTIONS_OPTIONS
            {0, 0, 0, 0}};
        longopts = optstruct;
        return chars;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    MainWindow* m_mainWindow;
};

} // namespace qt 
} // namespace gui 
} // namespace client 
} // namespace webrtc 
} // namespace app 
} // namespace xos 

#endif // _XOS_APP_WEBRTC_CLIENT_GUI_QT_MAIN_HPP 
