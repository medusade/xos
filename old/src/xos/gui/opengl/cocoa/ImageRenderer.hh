///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2014 $organization$
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
///   File: ImageRenderer.hh
///
/// Author: $author$
///   Date: 1/22/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_OPENGL_COCOA_IMAGERENDERER_HH
#define _XOS_GUI_OPENGL_COCOA_IMAGERENDERER_HH

#include "xos/gui/opengl/namespace.hpp"
#include "xos/gui/opengl/ImageRenderer.hpp"
#include "xos/gui/opengl/cocoa/Context.hh"

namespace xos {
namespace opengl {
namespace cocoa {

typedef opengl::ImageRendererImplement ImageRendererImplement;
typedef opengl::ImageRenderer ImageRendererExtend;
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS ImageRenderer
: virtual public ImageRendererImplement, public ImageRendererExtend {
public:
    typedef ImageRendererImplement Implements;
    typedef ImageRendererExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    ImageRenderer() {
    }
    virtual ~ImageRenderer() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Init(xos::gui::opengl::ContextImplemented& impl) {
        return m_context.Init(impl);
    }
    virtual bool Finish(xos::gui::opengl::ContextImplemented& impl) {
        return m_context.Finish(impl);
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool SwapBuffers() {
#if defined(OBJC)
        NSOpenGLContext* glContext;
        if ((glContext = m_context.GetContext())) {
            [glContext flushBuffer];
            return true;
        }
#else // defined(OBJC)
#endif // defined(OBJC)
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    xos::gui::opengl::cocoa::Context m_context;
};

} // namespace cocoa 
} // namespace opengl 
} // namespace xos 

#endif // _XOS_GUI_OPENGL_COCOA_IMAGERENDERER_HH 
