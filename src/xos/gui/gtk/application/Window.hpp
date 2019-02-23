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
///   File: Window.hpp
///
/// Author: $author$
///   Date: 4/29/2016
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_GTK_APPLICATION_WINDOW_HPP
#define _XOS_GUI_GTK_APPLICATION_WINDOW_HPP

#include "xos/gui/gtk/Widget.hpp"

namespace xos {
namespace gtk {
namespace application {

typedef WidgetImplements WindowImplements;
typedef Widget WindowExtends;
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Window: virtual public WindowImplements, public WindowExtends {
public:
    typedef WindowImplements Implements;
    typedef WindowExtends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Window(Attached detached = 0, bool isCreated = false)
    : Extends(detached, isCreated) {
    }
    virtual ~Window() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool SetDefaultSize(gint width, gint height) {
        Attached detached = 0;
        if ((detached = this->AttachedTo())) {
            XOS_LOG_MESSAGE_DEBUG("gtk_window_set_default_size(..., width = " << width << ", height = " << height << ")...");
            gtk_window_set_default_size(GTK_WINDOW(detached), width,height);
            return true;
        }
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Create(GtkApplication* application) {
        Attached detached = 0;
        if ((detached = CreateAttached(application))) {
            this->SetIsCreated();
            return true;
        }
        return false;
    }
    virtual Attached CreateAttached(GtkApplication* application) {
        if ((this->Destroyed())) {
            Attached detached = 0;
            if ((detached = CreateDetached(application))) {
                this->Attach(detached);
                return detached;
            }
        }
        return 0;
    }
    virtual Attached CreateDetached(GtkApplication* application) const {
        if ((application)) {
            Attached detached = 0;
            XOS_LOG_MESSAGE_DEBUG("gtk_application_window_new()...");
            if ((detached = gtk_application_window_new(application))) {
                XOS_LOG_MESSAGE_DEBUG("...gtk_application_window_new()");
                return detached;
            } else {
                XOS_LOG_ERROR("...failed on gtk_application_window_new()");
            }
        }
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace application 
} // namespace gtk 
} // namespace xos 

#endif // _XOS_GUI_GTK_APPLICATION_WINDOW_HPP 
