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
///   File: Context.hpp
///
/// Author: $author$
///   Date: 12/21/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_OPENGL_WINDOWS_CONTEXT_HPP
#define _XOS_GUI_OPENGL_WINDOWS_CONTEXT_HPP

#include "xos/gui/opengl/Context.hpp"

namespace xos {
//namespace gui {
namespace opengl {

///////////////////////////////////////////////////////////////////////
///  Class: ContextImplemented
///
/// Author: $author$
///   Date: 12/21/2012
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS ContextImplemented {
public:
    ContextImplemented(HWND hWnd): m_hWnd(hWnd) {}
    HWND GetWnd() { return m_hWnd; }
protected:
    HWND m_hWnd;
};

namespace windows {

typedef opengl::ContextImplement ContextImplement;
typedef opengl::Context ContextExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Context
///
/// Author: $author$
///   Date: 12/21/2012
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Context
: virtual public ContextImplement,
  public ContextExtend
{
public:
    typedef ContextImplement Implements;
    typedef ContextExtend Extends;

    Context() 
    : m_hWnd(0), m_hDC(0), m_hRC(0) 
    {}

    virtual bool Init(ContextImplemented& impl) {
        bool isSuccess = false;
        if ((Extends::Init(impl))) {
            if ((m_hWnd = impl.GetWnd())) {
                if ((m_hDC = GetDC(m_hWnd))) {
                    PIXELFORMATDESCRIPTOR pfd, *ppfd;
                    int pixelformat;

                    ppfd = &pfd;
                    ppfd->nSize = sizeof(PIXELFORMATDESCRIPTOR);
                    ppfd->nVersion = 1;
                    ppfd->dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
                    ppfd->dwLayerMask = PFD_MAIN_PLANE;
                    ppfd->iPixelType = PFD_TYPE_COLORINDEX;
                    ppfd->cColorBits = 16;
                    ppfd->cDepthBits = 16;
                    ppfd->cAccumBits = 0;
                    ppfd->cStencilBits = 0;

                    if ((pixelformat = ChoosePixelFormat(m_hDC, ppfd))) {
                        if ((SetPixelFormat(m_hDC, pixelformat, ppfd))) {
                            if ((m_hRC = wglCreateContext(m_hDC))) {
                                if ((wglMakeCurrent(m_hDC, m_hRC))) {
                                    return isSuccess = true;
                                }
                                wglDeleteContext(m_hRC);
                                m_hRC = 0;
                            }
                        }
                    }
                    ReleaseDC(m_hWnd, m_hDC);
                    m_hDC = 0;
                }
                m_hWnd = NULL;
            }
        }
        return isSuccess;
    }
    virtual bool Finish(ContextImplemented& impl) {
        bool isSuccess = true;
        if ((m_hRC)) {
            if ((m_hDC)) {
                if (!(wglMakeCurrent(NULL, NULL))) {
                    isSuccess = false;
                }
            }
            wglDeleteContext(m_hRC);
            m_hRC = 0;
        }
        if ((m_hDC)) {
            if ((m_hWnd)) {
                if (!(ReleaseDC(m_hWnd, m_hDC))) {
                    isSuccess = false;
                }
            }
            m_hDC = 0;
        }
        if ((m_hWnd)) {
            m_hWnd = 0;
        }
        if (!(Extends::Finish(impl))) {
            isSuccess = false;
        }
        return isSuccess;
    }

    virtual bool SwapBuffers() {
        if ((m_hDC)) {
            if ((::SwapBuffers(m_hDC))) {
                return true;
            }
        }
        return false;
    }

protected:
    HWND m_hWnd;
    HDC m_hDC;
    HGLRC m_hRC;
};

} // namespace windows 
} // namespace opengl 
//} // namespace gui 
} // namespace xos 

#endif // _XOS_GUI_OPENGL_WINDOWS_CONTEXT_HPP 
