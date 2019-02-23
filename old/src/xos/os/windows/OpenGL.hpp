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
///   File: OpenGL.hpp
///
/// Author: $author$
///   Date: 10/19/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_OS_WINDOWS_OPENGL_HPP
#define _XOS_OS_WINDOWS_OPENGL_HPP

#include "xos/base/Base.hpp"

#ifndef _XOS_PLATFORM_GL_GL_HPP
#include <gl/gl.h>
#define GL_BGR GL_BGR_EXT
#define GL_BGRA GL_BGRA_EXT
#endif // _XOS_PLATFORM_GL_GL_HPP 
#ifndef _XOS_PLATFORM_GL_GLU_HPP
#include <gl/glu.h>
#endif // _XOS_PLATFORM_GL_GLU_HPP 

namespace xos {
namespace windows {

} // namespace windows 
} // namespace xos 

#endif // _XOS_OS_WINDOWS_OPENGL_HPP 
