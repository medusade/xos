///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2013 $organization$
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
///   File: ImageRenderer.hpp
///
/// Author: $author$
///   Date: 3/27/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_OPENGL_X11_IMAGERENDERER_HPP
#define _XOS_GUI_OPENGL_X11_IMAGERENDERER_HPP

#include "xos/gui/opengl/ImageRenderer.hpp"
#include "xos/gui/opengl/x11/Context.hpp"

namespace xos {
namespace gui {
namespace opengl {
namespace x11 {

typedef ImageRendererImplement ImageRendererImplement;
typedef ImageRenderer ImageRendererExtend;
///////////////////////////////////////////////////////////////////////
///  Class: ImageRenderer
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS ImageRenderer
: virtual public ImageRendererImplement, public ImageRendererExtend {
public:
    typedef ImageRendererImplement Implements;
    typedef ImageRendererExtend Extends;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: ImageRenderer
    ///////////////////////////////////////////////////////////////////////
    ImageRenderer()
    : m_xDisplay(0),
      m_xWindow(None) {
    }
    virtual ~ImageRenderer() {
        Finish();
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Init(XDisplay* xDisplay, XWindow xWindow) {
        bool isSuccess = false;
        if ((xDisplay) && (xWindow)) {
            ContextImplemented glContextImplemented(*xDisplay, xWindow);
            if ((isSuccess = m_glContext.Init(glContextImplemented))) {
                m_xDisplay = xDisplay;
                m_xWindow = xWindow;
            }
        }
        return isSuccess;
    }
    virtual bool Finish()
    {
        bool isSuccess = false;
        if ((m_xDisplay) && (m_xWindow)) {
            ContextImplemented glContextImplemented(*m_xDisplay, m_xWindow);
            isSuccess = m_glContext.Finish(glContextImplemented);
            m_xDisplay = 0;
            m_xWindow = 0;
        }
        return isSuccess;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool SwapBuffers() {
        m_glContext.SwapBuffers();
        return !(GL_NO_ERROR != glGetError()); 
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    Context m_glContext;
    XDisplay* m_xDisplay;
    XWindow m_xWindow;
};

} // namespace x11 
} // namespace opengl 
} // namespace gui 
} // namespace xos 

#endif // _XOS_GUI_OPENGL_X11_IMAGERENDERER_HPP 
