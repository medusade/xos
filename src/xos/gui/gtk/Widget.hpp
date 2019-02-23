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
///   File: Widget.hpp
///
/// Author: $author$
///   Date: 4/28/2016
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_GTK_WIDGET_HPP
#define _XOS_GUI_GTK_WIDGET_HPP

#include "xos/gui/gtk/WidgetSignals.hpp"

namespace xos {
namespace gtk {

typedef GtkWidget* WidgetAttachedTo;
typedef CreatorImplementT<Implement> WidgetCreator;
typedef AttacherT<WidgetAttachedTo, int, 0, WidgetCreator> WidgetAttacher;
typedef AttachedT<WidgetAttachedTo, int, 0, WidgetAttacher, Extend> WidgetAttached;
typedef CreatedT<WidgetAttachedTo, int, 0, WidgetAttacher, WidgetAttached> WidgetCreated;
typedef WidgetAttacher WidgetImplements;
typedef WidgetCreated WidgetExtends;
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Widget
: virtual public WidgetSignals,
  virtual public WidgetImplements, public WidgetExtends {
public:
    typedef WidgetImplements Implements;
    typedef WidgetExtends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Widget(Attached detached = 0, bool isCreated = false)
    : Extends(detached, isCreated) {
    }
    virtual ~Widget() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Destroy() {
        Attached detached = 0;
        if ((detached = this->Detach())) {
            if ((DestroyDetached(detached))) {
                return true;
            }
        }
        return false;
    }
    virtual bool DestroyDetached(Attached detached) const {
        if ((detached)) {
            XOS_LOG_MESSAGE_DEBUG("gtk_widget_destroy(detached = " << GPointerToString(detached) << ")...")
            gtk_widget_destroy(detached);
            XOS_LOG_MESSAGE_DEBUG("...gtk_widget_destroy(detached = " << GPointerToString(detached) << ")")
            return true;
        }
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace gtk 
} // namespace xos 

#endif // _XOS_GUI_GTK_WIDGET_HPP 
