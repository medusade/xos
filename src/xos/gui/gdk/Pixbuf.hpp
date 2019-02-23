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
///   File: Pixbuf.hpp
///
/// Author: $author$
///   Date: 4/28/2016
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_GDK_PIXBUF_HPP
#define _XOS_GUI_GDK_PIXBUF_HPP

#include "xos/gui/gdk/Gdk.hpp"
#include "xos/base/Creator.hpp"

namespace xos {
namespace gdk {

typedef GdkPixbuf* PixbufAttachedTo;
typedef CreatorT<Implement> PixbufCreator;
typedef AttacherT<PixbufAttachedTo, int, 0, PixbufCreator> PixbufAttacher;
typedef AttachedT<PixbufAttachedTo, int, 0, PixbufAttacher, Extend> PixbufAttached;
typedef CreatedT<PixbufAttachedTo, int, 0, PixbufAttacher, PixbufAttached> PixbufCreated;
typedef PixbufAttacher PixbufImplements;
typedef PixbufCreated PixbufExtends;
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Pixbuf: virtual public PixbufImplements, public PixbufExtends {
public:
    typedef PixbufImplements Implements;
    typedef PixbufExtends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Pixbuf(Attached detached = 0, bool isCreated = false)
    : Extends(detached, isCreated) {
    }
    virtual ~Pixbuf() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Create(const char* fileName) {
        Attached detached = 0;
        if ((detached = CreateAttached(fileName))) {
            this->SetIsCreated();
            return true;
        }
        return false;
    }
    virtual bool Destroy() {
        Attached detached = 0;
        if ((detached = this->Detach())) {
            if ((this->DestroyDetached(detached))) {
                return true;
            }
        }
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual Attached CreateAttached(const char* fileName) {
        Attached detached = 0;
        if ((this->Destroyed())) {
            if ((detached = CreateDetached(fileName))) {
                this->Attach(detached);
            }
        }
        return detached;
    }
    virtual Attached CreateDetached(const char* fileName) const {
        Attached detached = 0;
        if ((fileName)) {
            GError* error = 0;
            String errorString;
            XOS_LOG_MESSAGE_DEBUG("gdk_pixbuf_new_from_file(fileName = " << fileName << ", &error)");
            if ((detached = gdk_pixbuf_new_from_file(fileName, &error))) {
                XOS_LOG_MESSAGE_DEBUG("...gdk_pixbuf_new_from_file(fileName = " << fileName << ", &error)");
            } else {
                if ((error)) {
                    errorString.Append(error->code);
                    errorString.AppendL(" (\"", ((error->message)?(error->message):("")), "\")", NULL);
                }
                XOS_LOG_ERROR("failed " << errorString << " on gdk_pixbuf_new_from_file(\"" << fileName << "\",...)");
            }
        }
        return detached;
    }
    virtual bool DestroyDetached(Attached detached) const {
        bool success = false;
        if ((detached)) {
            g_object_unref(detached);
            success = true;
        }
        return success;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace gdk 
} // namespace xos 

#endif // _XOS_GUI_GDK_PIXBUF_HPP 
