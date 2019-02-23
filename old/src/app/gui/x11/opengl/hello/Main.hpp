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
///   File: Main.hpp
///
/// Author: $author$
///   Date: 7/5/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_X11_OPENGL_HELLO_MAIN_HPP
#define _XOS_GUI_X11_OPENGL_HELLO_MAIN_HPP

#include "app/gui/opengl/hello/Main.hpp"
#include "xos/gui/opengl/x11/Context.hpp"
#include "xos/gui/opengl/x11/ImageRenderer.hpp"
#include "xos/gui/x11/Window.hpp"

namespace xos {
namespace x11 {
namespace opengl {
namespace hello {

///////////////////////////////////////////////////////////////////////
///  Class: MainT
///////////////////////////////////////////////////////////////////////
template
<class TImplement, class TExtend>

class _EXPORT_CLASS MainT
    : virtual public TImplement, 
      public xos::opengl::hello::MainT<TImplement, TExtend> {
public:
    typedef TImplement Implements;
    typedef xos::opengl::hello::MainT<TImplement, TExtend> Extends;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: MainT
    ///////////////////////////////////////////////////////////////////////
    MainT(){
    }
    virtual ~MainT() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual gui::ImageRendererInterface& GlRenderer() const {
        return (gui::ImageRendererInterface&)(m_glRenderer);
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    x11::Window m_window;
    gui::opengl::x11::ImageRenderer m_glRenderer;
};

} // namespace hello 
} // namespace opengl 
} // namespace x11 
} // namespace xos 

#endif // _XOS_GUI_X11_OPENGL_HELLO_MAIN_HPP 
