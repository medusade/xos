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
///   File: Main.hpp
///
/// Author: $author$
///   Date: 4/29/2016
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_GTK_APPLICATION_MAIN_HPP
#define _XOS_GUI_GTK_APPLICATION_MAIN_HPP

#include "xos/gui/gtk/application/MainSignals.hpp"
#include "xos/gui/gtk/Main.hpp"

#define XOS_GUI_GTK_APPLICATION_FLAGS G_APPLICATION_FLAGS_NONE
#define XOS_GUI_GTK_APPLICATION_ID "xos.gtk.application"

namespace xos {
namespace gtk {
namespace application {

typedef gtk::MainImplements MainImplements;
typedef gtk::Main MainExtends;
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Main
: virtual public MainSignals,
  virtual public MainImplements, public MainExtends {
public:
    typedef MainImplements Implements;
    typedef MainExtends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Main()
    : m_applicationId(XOS_GUI_GTK_APPLICATION_ID),
      m_applicationFlags(XOS_GUI_GTK_APPLICATION_FLAGS),
      m_application(0) {
    }
    virtual ~Main() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int EventLoop(int argc, char** argv, char** env) {
        int err = 1;
        int applicationArgc = 0;
        char** applicationArgv = 0;
        const gchar* applicationId = m_applicationId.Chars();
        GApplicationFlags applicationFlags =  m_applicationFlags;
        GtkApplication* application = 0;

        XOS_LOG_MESSAGE_DEBUG("BeforeCreateApplication()...");
        if (!(err = BeforeCreateApplication
             (applicationId, applicationFlags, argc,argv,env))) {
            int err2 = 0;

            XOS_LOG_MESSAGE_DEBUG("CreateApplication()...");
            if ((application = CreateApplication
                 (applicationId, applicationFlags, argc,argv,env))) {

                XOS_LOG_MESSAGE_DEBUG("AfterCreateApplication()...");
                if (!(err = AfterCreateApplication
                     (application, applicationId, applicationFlags, argc,argv,env))) {

                    XOS_LOG_MESSAGE_DEBUG("ConnectSignalActivate()...");
                    if ((ConnectSignalActivate(application))) {

                        XOS_LOG_MESSAGE_DEBUG("gtk_application_run()...");
                        if ((err = g_application_run
                             (G_APPLICATION(m_application = application), applicationArgc, applicationArgv))) {
                            XOS_LOG_ERROR("failed " << err << " on g_application_run()");
                        } else {
                            XOS_LOG_MESSAGE_DEBUG("...gtk_application_run()");
                        }
                        XOS_LOG_MESSAGE_DEBUG("DisconnectSignalActivate()...");
                        DisconnectSignalActivate(application);
                    }
                }
                XOS_LOG_MESSAGE_DEBUG("DestroyApplication()...");
                if ((err2 = DestroyApplication
                     (application, applicationId, applicationFlags, argc,argv,env))) {
                    if (!err) err = err2;
                }
            }
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual GtkApplication* CreateApplication
    (const gchar* applicationId, GApplicationFlags applicationFlags,
     int argc, char** argv, char** env) {
        GtkApplication* application = 0;
        XOS_LOG_MESSAGE_DEBUG("gtk_application_new(applicationId = \"" << applicationId << "\",...)...");
        if ((application = gtk_application_new(applicationId, applicationFlags))) {
            XOS_LOG_MESSAGE_DEBUG("...gtk_application_new(applicationId = \"" << applicationId << "\",...)");
        } else {
            XOS_LOG_ERROR("...failed on gtk_application_new(applicationId = \"" << applicationId << "\",...)");
        }
        return application;
    }
    virtual int DestroyApplication
    (GtkApplication* application,
     const gchar* applicationId, GApplicationFlags applicationFlags,
     int argc, char** argv, char** env) {
        if ((application)) {
            XOS_LOG_MESSAGE_DEBUG("g_object_unref()...");
            g_object_unref(application);
            XOS_LOG_MESSAGE_DEBUG("...g_object_unref()");
            return 0;
        }
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int BeforeCreateApplication
    (const gchar* applicationId, GApplicationFlags applicationFlags,
     int argc, char** argv, char** env) {
        return 0;
    }
    virtual int AfterCreateApplication
    (GtkApplication* application,
     const gchar* applicationId, GApplicationFlags applicationFlags,
     int argc, char** argv, char** env) {
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool ConnectSignalActivate(GtkApplication* detached) {
        const char* signal_name = "activate";
        if ((detached)) {
            gulong handlerId = 0;
            XOS_LOG_MESSAGE_DEBUG("g_signal_connect(" << GPointerToString(detached) << ", ..., \"" << signal_name << "\")...");
            if ((handlerId = g_signal_connect
                 (detached, signal_name,
                  G_CALLBACK(MainSignals::MainSignalActivateCallback),
                  G_POINTER((MainSignals*)this)))) {
                XOS_LOG_MESSAGE_DEBUG("...g_signal_connect(" << GPointerToString(detached) << ", ..., \"" << signal_name << "\")");
                return true;
            } else {
                XOS_LOG_ERROR("failed on g_signal_connect(" << GPointerToString(detached) << ", ..., \"" << signal_name << "\")");
            }
        }
        return false;
    }
    virtual bool DisconnectSignalActivate(GtkApplication* detached) {
        if ((detached)) {
            guint handlers = 0;
            XOS_LOG_MESSAGE_DEBUG("g_signal_handlers_disconnect_by_func(" << GPointerToString(detached) << ", ...)...");
            if ((handlers = g_signal_handlers_disconnect_by_func
                 (detached,
                  G_POINTER(MainSignals::MainSignalActivateCallback),
                  G_POINTER((MainSignals*)this)))) {
                XOS_LOG_MESSAGE_DEBUG("...g_signal_handlers_disconnect_by_func(" << GPointerToString(detached) << ", ...)...");
                return true;
            } else {
                XOS_LOG_ERROR("failed on g_signal_handlers_disconnect_by_func(" << GPointerToString(detached) << ", ...)");
            }
        }
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    GString m_applicationId;
    GApplicationFlags m_applicationFlags;
    GtkApplication* m_application;
};

} // namespace application 
} // namespace gtk 
} // namespace xos 

#endif // _XOS_GUI_GTK_APPLICATION_MAIN_HPP 
