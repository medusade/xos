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
///   File: iHelloMain.hh
///
/// Author: $author$
///   Date: 1/31/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_HELLO_COCOA_IHELLOMAIN_HH
#define _XOS_GUI_HELLO_COCOA_IHELLOMAIN_HH

#include "xos/gui/cocoa/iWindowMain.hh"
#include "xos/gui/cocoa/iOptMain.hh"
#include "xos/gui/cocoa/iMain.hh"
#include "xos/gui/opengl/cocoa/Context.hh"
#include "xos/gui/opengl/cocoa/ImageRenderer.hh"
#include "../../hello/Image.hpp"

namespace xos {
typedef xos::app::gui::hello::ImageT
<xos::InterfaceBase, xos::ExportBase> Image;
}

///////////////////////////////////////////////////////////////////////
/// Interface: iHelloGLImageView
///////////////////////////////////////////////////////////////////////
@interface iHelloGLImageView: iOpenGLView {
    bool m_preparedOpenGL;
    GLuint m_texture;
    void* m_image;
    unsigned m_imageWidth, m_imageHeight, m_imageDepth, m_imageSize;
    xos::gui::opengl::cocoa::ImageRenderer m_openglRenderer;
    }
    - (iHelloGLImageView*)init:(iRect)frame image:(xos::Image&)image;
    - (void)prepareOpenGL;
    - (void)reshape;
    - (void)drawRect:(iRect)rect;
@end

///////////////////////////////////////////////////////////////////////
/// Interface: iHelloMainView
///////////////////////////////////////////////////////////////////////
@interface iHelloMainView: iMainView {
    xos::Image m_image;
    xos::String m_imageFile;
    iHelloGLImageView* m_glImageView;
    }
    - (id)init:(const xos::String&)imageFile;
@end

///////////////////////////////////////////////////////////////////////
/// Interface: iHelloMainWindow
///////////////////////////////////////////////////////////////////////
@interface iHelloMainWindow: iMainWindow {
    xos::String m_imageFile;
    }
    - (iMainWindow*)initWithRect:(iRect)contentRect imageFile:(const xos::String&)imageFile;
    - (iView*)createMainView:(int)argc argv:(char**)argv env:(char**)env;
@end

///////////////////////////////////////////////////////////////////////
/// Interface: iHelloMain
///////////////////////////////////////////////////////////////////////
@interface iHelloMain: iWindowMain {
    xos::String m_imageFile;
    }
    - (iMainWindow*)createMainWindow:(iRect)contentRect argc:(int)argc argv:(char**)argv env:(char**)env;
    - (int)onOption:(int)optval optarg:(const char*)optarg optname:(const char*)optname optind:(int)optind argc:(int)argc argv:(char**)argv env:(char**)env;
    - (const char*)optionUsage:(const char*&)optarg longopt:(const struct option*)longopt;
    - (const char*)options:(const struct option*&)longopts;
    - (const char*)arguments:(const char**&)args;
@end

#endif // _XOS_GUI_HELLO_COCOA_IHELLOMAIN_HH 
