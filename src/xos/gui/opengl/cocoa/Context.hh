///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2012 $organization$
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
///   File: Context.hh
///
/// Author: $author$
///   Date: 12/22/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_COCOA_CONTEXT_HH
#define _XOS_GUI_COCOA_CONTEXT_HH

#include "xos/gui/opengl/Context.hpp"
#include <Cocoa/Cocoa.h>

namespace xos {
namespace opengl {

///////////////////////////////////////////////////////////////////////
///  Class: ContextImplemented
///
/// Author: $author$
///   Date: 12/22/2012
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS ContextImplemented {
public:
    ContextImplemented(NSOpenGLView* view): m_view(view) {}

    NSOpenGLPixelFormat* AcquirePixelFormat(NSOpenGLPixelFormatAttribute* attributes) const;
    bool ReleasePixelFormat(NSOpenGLPixelFormat* pixelFormat) const;

    NSOpenGLPixelFormat* SetPixelFormat(NSOpenGLPixelFormat* toPixelFormat);
    NSOpenGLPixelFormat* GetPixelFormat() const;

    NSOpenGLContext* GetContext() const;
    NSOpenGLView* GetView() const { return m_view; }
protected:
    NSOpenGLView* m_view;
};

namespace cocoa {

///////////////////////////////////////////////////////////////////////
/// Typedef: ContextImplement
///
///  Author: $author$
///    Date: 12/22/2012
///////////////////////////////////////////////////////////////////////
typedef opengl::ContextImplement
ContextImplement;
///////////////////////////////////////////////////////////////////////
/// Typedef: ContextExtend
///
///  Author: $author$
///    Date: 12/22/2012
///////////////////////////////////////////////////////////////////////
typedef opengl::Context
ContextExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Context
///
/// Author: $author$
///   Date: 12/22/2012
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Context
: virtual public ContextImplement,
  public ContextExtend
{
public:
    typedef ContextImplement Implements;
    typedef ContextExtend Extends;

    NSOpenGLView* m_view;
    NSOpenGLPixelFormat* m_pixelFormat;

    Context(): m_view(0), m_pixelFormat(0) {}
    virtual ~Context(){}

    virtual bool Init(ContextImplemented& impl) {
        bool isSuccess = false;
        NSOpenGLPixelFormatAttribute* pixelFormatAttributes;
        NSOpenGLPixelFormat* pixelFormat;
        if ((m_view = impl.GetView())) {
            if ((pixelFormatAttributes = GetPixelFormatAttributes())) {
                if ((m_pixelFormat = impl.GetPixelFormat())) {
                    if ((pixelFormat = impl.AcquirePixelFormat(pixelFormatAttributes))) {
                        isSuccess = !(pixelFormat != impl.SetPixelFormat(pixelFormat));
                        impl.ReleasePixelFormat(pixelFormat);
                        return isSuccess;
                    }
                    m_pixelFormat = 0;
                }
            }
            m_view = 0;
        }
        return isSuccess;
    }
    virtual bool Finish(ContextImplemented& impl) {
        bool isSuccess = false;
        if ((m_pixelFormat)) {
            isSuccess = !(m_pixelFormat != impl.SetPixelFormat(m_pixelFormat));
            m_pixelFormat = 0;
        }
        return isSuccess;
    }

    virtual NSOpenGLPixelFormatAttribute* GetPixelFormatAttributes() const;
    virtual NSOpenGLContext* GetContext() const;
};

} // namespace cocoa 
} // namespace gui 
} // namespace xos 

#endif // _XOS_GUI_COCOA_CONTEXT_HH 
