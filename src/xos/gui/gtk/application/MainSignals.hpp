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
///   File: MainSignals.hpp
///
/// Author: $author$
///   Date: 4/29/2016
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_GTK_APPLICATION_MAINSIGNALS_HPP
#define _XOS_GUI_GTK_APPLICATION_MAINSIGNALS_HPP

#include "xos/gui/gtk/Gtk.hpp"

namespace xos {
namespace gtk {
namespace application {

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS MainSignals: virtual public Implement {
public:
    typedef Implement Implements;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual gboolean OnMainSignalActivate(GtkApplication* application) {
        MainSignals* forward_to = MainSignalsForwardTo();
        XOS_LOG_MESSAGE_DEBUG("OnMainSignalActivate(GtkApplication* application = " << GPointerToString(application) << ")...");
        if ((forward_to)) {
            return forward_to->OnMainSignalActivate(application);
        }
        XOS_LOG_MESSAGE_DEBUG("...OnMainSignalActivate(GtkApplication* application = " << GPointerToString(application) << ")");
        return TRUE;
    }
    static void MainSignalActivateCallback
    (GtkApplication* application, MainSignals* mainSignals) {
        if ((application) && (mainSignals)) {
            mainSignals->OnMainSignalActivate(application);
        } else {
            if ((application)) {
                XOS_LOG_ERROR("unexpected mainSignals == 0");
            } else {
                XOS_LOG_ERROR("unexpected application == 0");
            }
        }
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual MainSignals* ForwardMainSignalsTo(MainSignals* to) {
        return 0;
    }
    virtual MainSignals* MainSignalsForwardTo() const {
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace application
} // namespace gtk 
} // namespace xos 

#endif // _XOS_GUI_GTK_APPLICATION_MAINSIGNALS_HPP 
