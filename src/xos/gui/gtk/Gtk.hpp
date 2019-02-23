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
///   File: Gtk.hpp
///
/// Author: $author$
///   Date: 4/28/2016
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_GTK_GTK_HPP
#define _XOS_GUI_GTK_GTK_HPP

#include "xos/gui/gdk/Gdk.hpp"
#include "xos/base/Creator.hpp"
#include "xos/base/Types.hpp"
#include <gtk/gtk.h>

#if !defined(G_POINTER)
#define G_POINTER(p) ((gpointer)(p))
#endif // !defined(G_POINTER)

#if ((GTK_MAJOR_VERSION == 3))
#if ((GTK_MINOR_VERSION < 8))
#define gtk_tree_view_set_activate_on_single_click(w, v)
#endif // ((GTK_MINOR_VERSION < 8))
#endif // ((GTK_MAJOR_VERSION == 3))

namespace xos {
namespace gtk {

typedef ImplementBase Implement;
typedef Base Extend;

typedef TypesT<gchar> GChars;
typedef StringT<gchar> GString;

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS GPointerToString: public String {
public:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    GPointerToString(gpointer p) {
        this->Append("0x");
        this->Appendx(((uint8_t*)&p), sizeof(p));
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace gtk
} // namespace xos 

#endif // _XOS_GUI_GTK_GTK_HPP 
