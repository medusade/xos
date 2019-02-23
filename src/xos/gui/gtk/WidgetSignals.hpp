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
///   File: WidgetSignals.hpp
///
/// Author: $author$
///   Date: 4/28/2016
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_GTK_WIDGETSIGNALS_HPP
#define _XOS_GUI_GTK_WIDGETSIGNALS_HPP

#include "xos/gui/gtk/Gtk.hpp"

namespace xos {
namespace gtk {

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS WidgetSignals: virtual public Implement {
public:
    typedef Implement Implements;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual gboolean OnWidgetSignalDestroy(GtkWidget* widget) {
        WidgetSignals* forward_to = WidgetSignalsForwardTo();
        XOS_LOG_MESSAGE_DEBUG("OnWidgetSignalDestroy(GtkWidget* widget = " << GPointerToString(widget) << ")...");
        if ((forward_to)) {
            return forward_to->OnWidgetSignalDestroy(widget);
        }
        XOS_LOG_MESSAGE_DEBUG("...OnWidgetSignalDestroy(GtkWidget* widget = " << GPointerToString(widget) << ")");
        return TRUE;
    }
    static void OnWidgetSignalDestroyCallback
    (GtkWidget* widget, WidgetSignals* widgetSignals) {
        if ((widget) && (widgetSignals)) {
            widgetSignals->OnWidgetSignalDestroy(widget);
        } else {
            if ((widget)) {
                XOS_LOG_ERROR("unexpected widgetSignals == 0");
            } else {
                XOS_LOG_ERROR("unexpected widget == 0");
            }
        }
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual WidgetSignals* ForwardWidgetSignalsTo(WidgetSignals* to) {
        return 0;
    }
    virtual WidgetSignals* WidgetSignalsForwardTo() const {
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace gtk 
} // namespace xos 

#endif // _XOS_GUI_GTK_WIDGETSIGNALS_HPP 
