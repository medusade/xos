///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2016 $organization$
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
///   File: WindowMain.hpp
///
/// Author: $author$
///   Date: 4/29/2016
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_GTK_APPLICATION_WINDOWMAIN_HPP
#define _XOS_GUI_GTK_APPLICATION_WINDOWMAIN_HPP

#include "xos/gui/gtk/application/Main.hpp"
#include "xos/gui/gtk/application/Window.hpp"

namespace xos {
namespace gtk {
namespace application {

typedef application::MainImplements WindowMainImplements;
typedef application::Main WindowMainExtends;
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS WindowMain
: virtual public WindowMainImplements, public WindowMainExtends {
public:
    typedef WindowMainImplements Implements;
    typedef WindowMainExtends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    WindowMain(): m_mainWindow(0) {
    }
    virtual ~WindowMain() {
    }
protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual GtkWidget* CreateMainWindow(GtkApplication *application) {
        return Window().CreateDetached(application);
    }
    virtual bool DestroyMainWindow
    (GtkWidget* mainWindow, GtkApplication *application) {
        if ((mainWindow) && (application)
            && (application == (this->m_application))) {
            return Window().DestroyDetached(mainWindow);
        }
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool BeforeCreateMainWindow(GtkApplication *application) {
        return true;
    }
    virtual bool AfterCreateMainWindow
    (GtkWidget* mainWindow, GtkApplication *application) {
        return true;
    }
    virtual bool ShowMainWindow
    (GtkWidget* mainWindow, GtkApplication *application) {
        if ((mainWindow) && (application)) {
            XOS_LOG_MESSAGE_DEBUG("gtk_widget_show_all(mainWindow = " << GPointerToString(mainWindow) << ")...");
            gtk_widget_show_all(mainWindow);
            return true;
        }
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual gboolean OnMainSignalActivate(GtkApplication* application) {
        XOS_LOG_MESSAGE_DEBUG("OnMainSignalActivate(GtkApplication* application = " << GPointerToString(application) << ")...");
        if ((application)) {
            if ((this->BeforeCreateMainWindow(application))) {
                GtkWidget* mainWindow = 0;
                if ((mainWindow = this->CreateMainWindow(application))) {
                    if ((this->AfterCreateMainWindow(mainWindow, application))) {
                        if ((this->ShowMainWindow(mainWindow, application))) {
                            m_mainWindow = mainWindow;
                            mainWindow = 0;
                        }
                    }
                }
            }
        }
        XOS_LOG_MESSAGE_DEBUG("...OnMainSignalActivate(GtkApplication* application = " << GPointerToString(application) << ")");
        return TRUE;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    GtkWidget* m_mainWindow;
};

} // namespace application 
} // namespace gtk 
} // namespace xos 

#endif // _XOS_GUI_GTK_APPLICATION_WINDOWMAIN_HPP 
