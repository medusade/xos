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
///   File: Context.hpp
///
/// Author: $author$
///   Date: 3/26/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_OPENGL_X11_CONTEXT_HPP
#define _XOS_GUI_OPENGL_X11_CONTEXT_HPP

#include "xos/gui/x11/Created.hpp"
#include "xos/gui/x11/Attached.hpp"
#include "xos/gui/opengl/Context.hpp"
#include "xos/os/Logger.hpp"

namespace xos {
namespace gui {
namespace opengl {

typedef xos::x11::XDisplay XDisplay;
typedef xos::x11::XWindow XWindow;
///////////////////////////////////////////////////////////////////////
///  Class: ContextImplemented
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS ContextImplemented {
public:
    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: ContextImplemented
    ///////////////////////////////////////////////////////////////////////
    ContextImplemented(XDisplay& xDisplay, XWindow xWindow)
    : m_xDisplay(xDisplay), m_xWindow(xWindow) {}
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    XDisplay& xDisplay() const {
        return (XDisplay&)(m_xDisplay);
    }
    XWindow xWindow() const {
        return m_xWindow;
    }
protected:
    XDisplay& m_xDisplay;
    XWindow m_xWindow;
};

namespace x11 {

typedef InterfaceBase ContextImplement;
typedef xos::x11::Attached<GLXContext, int, 0> ContextAttached;
typedef xos::Created<GLXContext, int, 0, ContextAttached> ContextCreated;
typedef xos::x11::Created<GLXContext, int, 0, ContextCreated> ContextExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Context
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Context: virtual public ContextImplement, public ContextExtend {
public:
    typedef ContextImplement Implements;
    typedef ContextExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: Context
    ///////////////////////////////////////////////////////////////////////
    Context(XDisplay* xDisplay=0, XWindow xWindow=0, GLXContext detached=0, bool isCreated=false)
    : Extends(xDisplay, detached, isCreated), m_window(xWindow) {
    }
    virtual ~Context() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Init(ContextImplemented& impl) {
        bool isSuccess = false;
        XDisplay* xDisplay = &impl.xDisplay();
        XWindow xWindow = impl.xWindow();
        XWindowAttributes watt;

        if ((XGetWindowAttributes(xDisplay, xWindow, &watt))) {
            GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
            int screen = XScreenNumberOfScreen(watt.screen);
            XVisualInfo* vi = glXChooseVisual(xDisplay, screen, att);
            if ((vi)) {
                GLXContext detached = glXCreateContext(xDisplay, vi, NULL, GL_TRUE);
                if ((detached)) {
                    if ((glXMakeCurrent(xDisplay, xWindow, detached))) {
                        m_window = xWindow;
                        Attach(xDisplay, detached);
                        return true;
                    } else {
                        XOS_LOG_ERROR("failed on glXMakeCurrent()");
                    }
                    glXDestroyContext(xDisplay, detached);
                } else {
                    XOS_LOG_ERROR("failed on glXCreateContext()");
                }
            } else {
                XOS_LOG_ERROR("failed on glXChooseVisual()");
            }
        } else {
            XOS_LOG_ERROR("failed on XGetWindowAttributes()");
        }
        return isSuccess;
    }
    virtual bool Finish(ContextImplemented& impl) {
        bool isSuccess = false;
        bool isCreated = false;
        XDisplay* xDisplay = 0;
        XWindow xWindow = m_window;
        GLXContext detached = Detach(xDisplay, isCreated);
        m_window = 0;
        if ((isSuccess = ((xDisplay) && (xWindow) && (detached)))) {
            if (!(glXMakeCurrent(xDisplay, None, 0))) {
                XOS_LOG_ERROR("failed on glXMakeCurrent()");
                isSuccess = false;
            }
            glXDestroyContext(xDisplay, detached);
        }
        return isSuccess;
    }
    virtual bool SwapBuffers() {
        bool isSuccess = false;
        if ((m_display) && (m_window)) {
            glXSwapBuffers(m_display, m_window);
            return true;
        }
        return isSuccess;
    }

protected:
    XWindow m_window;
};

} // namespace x11 
} // namespace opengl 
} // namespace gui 
} // namespace xos 

#endif // _XOS_GUI_OPENGL_X11_CONTEXT_HPP 
