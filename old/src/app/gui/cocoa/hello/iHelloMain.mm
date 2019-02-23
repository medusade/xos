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
///   File: iHelloMain.mm
///
/// Author: $author$
///   Date: 1/31/2014
///////////////////////////////////////////////////////////////////////
#include "iHelloMain.hh"

#define IHELLO_WINDOW_TITLE "iHello"

#define IHELLO_MAIN_FILE_OPT "image-file"
#define IHELLO_MAIN_FILE_OPTARG_REQUIRED XOS_MAIN_OPT_ARGUMENT_REQUIRED
#define IHELLO_MAIN_FILE_OPTARG "path"
#define IHELLO_MAIN_FILE_OPTUSE "Image file path"
#define IHELLO_MAIN_FILE_OPTVAL_S "f:"
#define IHELLO_MAIN_FILE_OPTVAL_C 'f'

#define IHELLO_MAIN_FILE_OPTIONS_OPTION \
   {IHELLO_MAIN_FILE_OPT, \
    IHELLO_MAIN_FILE_OPTARG_REQUIRED, 0, \
    IHELLO_MAIN_FILE_OPTVAL_C},

#define IHELLO_MAIN_OPTIONS_CHARS \
    IHELLO_MAIN_FILE_OPTVAL_S \
    XOS_MAIN_OPTIONS_CHARS

#define IHELLO_MAIN_OPTIONS_OPTIONS \
    IHELLO_MAIN_FILE_OPTIONS_OPTION \
    XOS_MAIN_OPTIONS_OPTIONS

///////////////////////////////////////////////////////////////////////
/// Implentation: iHelloGLImageView
///////////////////////////////////////////////////////////////////////
@implementation iHelloGLImageView
    - (iHelloGLImageView*)init:(iRect)frame image:(xos::Image&)image {
        [super initWithFrame:frame pixelFormat:[NSOpenGLView defaultPixelFormat]];
        m_preparedOpenGL = false;
        m_image = image.Image();
        m_imageWidth = image.ImageWidth();
        m_imageHeight = image.ImageHeight();
        m_imageDepth = image.ImageDepth();
        m_imageSize = image.ImageSize();
        return self;
    }
    - (void)prepareOpenGL {
        xos::gui::opengl::ContextImplemented openglContextImpl(self);
        if ((m_openglRenderer.Init(openglContextImpl))) {
            m_preparedOpenGL = m_openglRenderer.Prepare();
        }
    }
    - (void)reshape {
        if ((m_preparedOpenGL)) {
            iRect rect = [self bounds];
            m_openglRenderer.Reshape(rect.size.width, rect.size.height);
        }
        [super reshape];
    }
    - (void)drawRect:(iRect)rect {
        if ((m_preparedOpenGL) && (m_image)) {
            m_openglRenderer.Render
            (m_image, m_imageWidth, m_imageHeight,
             m_image, m_imageWidth, m_imageHeight);
        }
    }
@end

///////////////////////////////////////////////////////////////////////
/// Implentation: iHelloHelloMainView
///////////////////////////////////////////////////////////////////////
@implementation iHelloMainView
    - (id)init:(const xos::String&)imageFile {
        bool loadedImage = false;
        [super init];
        m_imageFile = imageFile;
        m_glImageView = 0;
        if (0 < (m_imageFile.Length()))
            loadedImage = m_image.LoadImageFile(m_imageFile);
        else loadedImage = m_image.LoadImageFile();
        if ((loadedImage)) {
            iRect rect = iMakeRect(0,0, m_image.ImageWidth(), m_image.ImageHeight());
            if ((m_glImageView = [[iHelloGLImageView alloc] init:rect image:m_image])) {
                [self addSubview:m_glImageView];
                [self setAutoresizesSubviews:YES];
            }
        } else {
            XOS_LOG_ERROR("failed to load image \"" << m_imageFile << "\"");
        }
        return self;
    }
    - (void)resizeSubviewsWithOldSize:(NSSize)oldBoundsSize {
        if ((m_glImageView)) {
            iRect r = [self bounds];
            [m_glImageView setFrameSize:r.size];
        }
    }
@end

//////////////////////////////////////////////////////////////////////
/// Implentation: iHelloMainWindow
///////////////////////////////////////////////////////////////////////
@implementation iHelloMainWindow
    - (iHelloMainWindow*)initWithRect:(iRect)contentRect imageFile:(const xos::String&)imageFile{
        [super initWithRect:contentRect];
        [self setTitle:[iString stringWithUTF8String:IHELLO_WINDOW_TITLE]];
        m_imageFile = imageFile;
        return self;
    }
    - (iView*)createMainView:(int)argc argv:(char**)argv env:(char**)env {
        m_mainView = [[iHelloMainView alloc] init:m_imageFile];
        return m_mainView;
    }
@end

///////////////////////////////////////////////////////////////////////
/// Implentation: iHelloMain
///////////////////////////////////////////////////////////////////////
@implementation iHelloMain
    - (iMainWindow*)createMainWindow:(iRect)contentRect argc:(int)argc argv:(char**)argv env:(char**)env {
        return [[iHelloMainWindow alloc] initWithRect:contentRect imageFile:m_imageFile];
    }
    - (int)onOption:(int)optval optarg:(const char*)optarg optname:(const char*)optname optind:(int)optind argc:(int)argc argv:(char**)argv env:(char**)env {
        int err = 0;
        switch(optval) {
        case IHELLO_MAIN_FILE_OPTVAL_C:
            if ((optarg) && (optarg[0]))
                m_imageFile.Assign(optarg);
            break;
        default:
            err = [super onOption:optval optarg:optarg
                   optname:optname optind:optind
                   argc:argc argv:argv env:env];
        }
        return err;
    }
    - (const char*)optionUsage:(const char*&)optarg longopt:(const struct option*)longopt {
        const char* chars = "";
        switch(longopt->val) {
        case IHELLO_MAIN_FILE_OPTVAL_C:
            optarg = IHELLO_MAIN_FILE_OPTARG;
            chars = IHELLO_MAIN_FILE_OPTUSE;
            break;
        default:
            chars = [super optionUsage:optarg longopt:longopt];
        }
        return chars;
    }
    - (const char*)options:(const struct option*&)longopts {
        static const char* chars = IHELLO_MAIN_OPTIONS_CHARS;
        static struct option optstruct[]= {
            IHELLO_MAIN_OPTIONS_OPTIONS
            {0, 0, 0, 0}};
        longopts = optstruct;
        return chars;
    }
@end
        
///////////////////////////////////////////////////////////////////////
/// Implentation: iMain
///////////////////////////////////////////////////////////////////////
@implementation iMain
    + (id<iMain>)create {
        return [[iHelloMain alloc] init];
    }
@end
