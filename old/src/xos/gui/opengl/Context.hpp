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
#ifndef _XOS_GUI_OPENGL_CONTEXT_HPP
#define _XOS_GUI_OPENGL_CONTEXT_HPP

#include "xos/gui/opengl/namespace.hpp"
#include "xos/base/Base.hpp"
#include "xos/base/Platform.hpp"

#if defined(WINDOWS) 
// Windows 
#ifndef _XOS_PLATFORM_GL_GL_HPP
#include <gl/gl.h>
#define GL_BGR GL_BGR_EXT
#define GL_BGRA GL_BGRA_EXT
#endif // _XOS_PLATFORM_GL_GL_HPP 
#ifndef _XOS_PLATFORM_GL_GLU_HPP
#include <gl/glu.h>
#endif // _XOS_PLATFORM_GL_GLU_HPP
typedef GLuint NSOpenGLPixelFormatAttribute;
struct NSOpenGLPixelFormat;
struct NSOpenGLContext;
struct NSOpenGLView;
#else // defined(WINDOWS) 
// Unix 
#if defined(MACOSX) 
// Mac OSX 
#include <OpenGL/OpenGL.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else // defined(MACOSX) 
// Otherwise 
//#include<X11/X.h>
//#include<X11/Xlib.h>
#include<GL/gl.h>
#include<GL/glu.h>
//#include<GL/glx.h>
#endif // defined(MACOSX) 
#endif // defined(WINDOWS) 

namespace xos {
namespace opengl {

class _EXPORT_CLASS ContextImplemented;

///////////////////////////////////////////////////////////////////////
/// Typedef: ContextImplement
///
///  Author: $author$
///    Date: 12/21/2012
///////////////////////////////////////////////////////////////////////
typedef InterfaceBase
ContextImplement;
///////////////////////////////////////////////////////////////////////
/// Typedef: ContextExtend
///
///  Author: $author$
///    Date: 12/21/2012
///////////////////////////////////////////////////////////////////////
typedef ExportBase
ContextExtend;

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

    Context() {}
    ~Context() {}

    virtual bool Init(ContextImplemented& impl) {
        bool isSuccess = true;
        return isSuccess;
    }
    virtual bool Finish(ContextImplemented& impl) {
        bool isSuccess = true;
        return isSuccess;
    }
};

} // namespace gui 
} // namespace xos 

#endif // _XOS_GUI_OPENGL_CONTEXT_HPP 
