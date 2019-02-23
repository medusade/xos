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
#ifndef _XOS_GUI_OPENGL_HELLO_MAIN_HPP
#define _XOS_GUI_OPENGL_HELLO_MAIN_HPP

#include "xos/gui/opengl/ImageRenderer.hpp"
#include "xos/gui/ImageRenderer.hpp"
#include "xos/os/Main.hpp"
#include "xos/os/Logger.hpp"

#define XOS_GUI_OPENGL_HELLO_DEFAULT_IMAGE_FILENAME "video-frame-bgra.raw"
#define XOS_GUI_OPENGL_HELLO_DEFAULT_IMAGE_WIDTH 352
#define XOS_GUI_OPENGL_HELLO_DEFAULT_IMAGE_HEIGHT 288
#define XOS_GUI_OPENGL_HELLO_DEFAULT_IMAGE_DEPTH 4

#define XOS_GUI_OPENGL_HELLO_OPENGL_OPT "opengl"
#define XOS_GUI_OPENGL_HELLO_OPENGL_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_REQUIRED
#define XOS_GUI_OPENGL_HELLO_OPENGL_OPTARG "{on | off}"
#define XOS_GUI_OPENGL_HELLO_OPENGL_OPTUSE "OpenGL on/off"
#define XOS_GUI_OPENGL_HELLO_OPENGL_OPTVAL_S "g:"
#define XOS_GUI_OPENGL_HELLO_OPENGL_OPTVAL_C 'g'

#define XOS_GUI_OPENGL_HELLO_OPTIONS_CHARS XOS_GUI_OPENGL_HELLO_OPENGL_OPTVAL_S
#define XOS_GUI_OPENGL_HELLO_OPTIONS_OPTIONS \
            {XOS_GUI_OPENGL_HELLO_OPENGL_OPT, XOS_GUI_OPENGL_HELLO_OPENGL_OPTARG_REQUIRED, 0, XOS_GUI_OPENGL_HELLO_OPENGL_OPTVAL_C},

namespace xos {
namespace opengl {
namespace hello {

///////////////////////////////////////////////////////////////////////
///  Class: MainT
///////////////////////////////////////////////////////////////////////
template
<class TImplement, class TExtend>

class _EXPORT_CLASS MainT
: virtual public TImplement, public TExtend {
public:
    typedef TImplement Implements;
    typedef TExtend Extends;
    typedef MainT Derives;

    typedef void (Derives::*MRender)();

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: MainT
    ///////////////////////////////////////////////////////////////////////
    MainT()
    : m_image(0), 
      m_imageSize(0), 
      m_imageFile(XOS_GUI_OPENGL_HELLO_DEFAULT_IMAGE_FILENAME), 
      m_imageWidth(XOS_GUI_OPENGL_HELLO_DEFAULT_IMAGE_WIDTH),  
      m_imageHeight(XOS_GUI_OPENGL_HELLO_DEFAULT_IMAGE_HEIGHT),  
      m_imageDepth(XOS_GUI_OPENGL_HELLO_DEFAULT_IMAGE_DEPTH),
      m_render(0) {
    }
    virtual ~MainT() {
        FreeImage();
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void RenderRaw() {
        if ((m_image)) {
	    gui::ImageRendererInterface& glRenderer = GlRenderer();
            glRenderer.RenderRaw
            (m_image, m_imageWidth, m_imageHeight);
            glRenderer.SwapBuffers();
        }
    }
    virtual void Render() {
        if ((m_image)) {
	    gui::ImageRendererInterface& glRenderer = GlRenderer();
            glRenderer.Render
            (m_image, m_imageWidth, m_imageHeight);
            glRenderer.SwapBuffers();
        }
    }
    virtual void RenderIn() {
        if ((m_image)) {
	    gui::ImageRendererInterface& glRenderer = GlRenderer();
            glRenderer.Render
            (m_image, m_imageWidth, m_imageHeight,
             m_image, m_imageWidth, m_imageHeight);
            glRenderer.SwapBuffers();
        }
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void* LoadImageFile() {
        LoadImageFile(m_imageFile);
        return m_image;
    }
    virtual void* LoadImageFile(const char* chars) {
        if ((chars) && (chars != m_imageFile))
            m_imageFile = chars;

        if ((m_imageFile)) {
            m_imageSize = (m_imageWidth*m_imageHeight*m_imageDepth);
            if ((m_image = malloc(m_imageSize))) {
                FILE* file = 0;
                size_t count = 0;
                if ((file = fopen(m_imageFile, "rb"))) {
                    count = fread(m_image, m_imageSize, 1, file);
                    fclose(file);
                    if (1 > (count)) {
                        XOS_LOG_ERROR("failed on fread() of \"" << m_imageFile << "\"");
                        free(m_image);
                        m_image = 0;
                        m_imageSize = 0;
                    }
                } else {
                    XOS_LOG_ERROR("failed on fopen(\"" << m_imageFile << "\",...)");
                    free(m_image);
                    m_image = 0;
                    m_imageSize = 0;
                }
            } else {
                XOS_LOG_ERROR("failed on malloc(" << m_imageSize << ")");
                m_imageSize = 0;
            }
        }
        return m_image;
    }
    virtual void FreeImage() {
        if ((m_image)) {
            free(m_image);
            m_image = 0;
            m_imageSize = 0;
        }
    }
    virtual void* Image() const {
        return (void*)(m_image);
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual gui::ImageRendererInterface& GlRenderer() const = 0;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    void* m_image;
    const char* m_imageFile;
    unsigned m_imageWidth, m_imageHeight, m_imageDepth, m_imageSize;
    MRender m_render;
};

} // namespace hello 
} // namespace opengl 
} // namespace xos 

#endif // _XOS_GUI_OPENGL_HELLO_MAIN_HPP 
