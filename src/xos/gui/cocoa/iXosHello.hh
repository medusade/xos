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
///   File: iXosHello.hh
///
/// Author: $author$
///   Date: 12/21/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_COCOA_IXOSHELLO_HH
#define _XOS_GUI_COCOA_IXOSHELLO_HH

#include "iXosWindowMain.hh"
#include "xos/gui/opengl/cocoa/Context.hh"
#include "xos/gui/opengl/cocoa/ImageRenderer.hh"

#define DEFAULT_IXOSHELLO_VIEW_BG_COLOR redColor
#define DEFAULT_IXOSHELLO_BUTTON_TITLE "Hello"

///////////////////////////////////////////////////////////////////////
/// Interface: iXosHelloButton
///
///    Author: $author$
///      Date: 1/23/2014
///////////////////////////////////////////////////////////////////////
@interface iXosHelloButton: NSButton {
    }
    - (id)init:(NSRect)frame target:(NSObject*)target;
@end

///////////////////////////////////////////////////////////////////////
/// Interface: iXosHelloControlView
///
///    Author: $author$
///      Date: 1/23/2014
///////////////////////////////////////////////////////////////////////
@interface iXosHelloControlView: NSView {
    iXosHelloButton* m_helloButton;
    }
    - (id)init:(NSRect)frame target:(NSObject*)target;
@end

///////////////////////////////////////////////////////////////////////
/// Interface: iXosHelloMainView
///
///    Author: $author$
///      Date: 12/20/2012
///////////////////////////////////////////////////////////////////////
@interface iXosHelloMainView: NSOpenGLView {
    bool m_preparedOpenGL;
    GLuint m_texture;
    void* m_image;
    const char* m_imageFile;
    unsigned m_imageWidth, m_imageHeight, m_imageDepth, m_imageSize;
    xos::gui::opengl::cocoa::Context m_openglContext;
    xos::gui::opengl::cocoa::ImageRenderer m_openglRenderer;
    }
    - (id)init:(NSRect)frame;
    - (void)prepareOpenGL;
    - (void)reshape;
    - (void)drawRect:(NSRect)rect;
    - (void)SetImageFile:(const char*)chars;
    - (void*)ReadImageFile;
@end

///////////////////////////////////////////////////////////////////////
/// Interface: iXosHelloMainWindow
///
///    Author: $author$
///      Date: 12/21/2012
///////////////////////////////////////////////////////////////////////
@interface iXosHelloMainWindow: iXosMainWindow {
    const char* m_imageFile;
    NSView* m_currentView;
    iXosHelloMainView* m_mainView;
    iXosHelloControlView* m_controlView;
    }
    - (id)initWithContentRect:(NSRect)contentRect styleMask:(NSUInteger)windowStyle
                      backing:(NSBackingStoreType)bufferingType defer:(BOOL)deferCreation;
    - (NSView*)CreateMainView:(int)argc argv:(char**)argv env:(char**)env;
    - (void)SetImageFile:(const char*)chars;
    - (void)helloClicked:(id)sender;
    - (void)mouseUp:(NSEvent*)theEvent;
    - (void)switchView;
@end

///////////////////////////////////////////////////////////////////////
/// Interface: iXosHello
///
///    Author: $author$
///      Date: 12/21/2012
///////////////////////////////////////////////////////////////////////
@interface iXosHello: iXosWindowMain {
    const char* m_imageFile;
    }
    - (iXosMainWindow*)CreateMainWindow:(int)argc argv:(char**)argv env:(char**)env;
@end

#endif // _XOS_GUI_COCOA_IXOSHELLO_HH
