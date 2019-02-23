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
#ifndef _XOS_GUI_OPENGL_IMAGERENDERER_HPP
#define _XOS_GUI_OPENGL_IMAGERENDERER_HPP

#include "xos/gui/opengl/namespace.hpp"
#include "xos/gui/ImageRenderer.hpp"
#include "xos/gui/opengl/Context.hpp"
#include "xos/gui/opengl/Rectangle.hpp"
#include "xos/gui/opengl/Size.hpp"
#include "xos/gui/opengl/Point.hpp"

namespace xos {
namespace opengl {

typedef gui::ImageRendererInterface ImageRendererImplement;
typedef ExportBase ImageRendererExtend;
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
    : m_width(0), m_height(0),
      m_inMinWidth(100), m_inMinHeight(100),
      m_inOffsetX(10), m_inOffsetY(10),
      m_inRatio(4), m_inRatioTo(1),
      m_textureMagFilter(GL_LINEAR), 
      m_textureMinFilter(GL_LINEAR) {
    }
    virtual ~ImageRenderer() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Prepare() {
        glGenTextures(1, &m_texture);
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_CULL_FACE);
        return !(GL_NO_ERROR != glGetError()); 
    }
    virtual bool Reshape(int width, int height) {
        m_width = width; m_height = height;
        glViewport(0, 0, width, height);
        return !(GL_NO_ERROR != glGetError()); 
    }
    virtual bool SwapBuffers() {
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Render
    (const void* image, int imageWidth, int imageHeight,
     const void* inImage, int inImageWidth, int inImageHeight) {
         return RenderResizedImage
         (m_texture, image, imageWidth, imageHeight, 
          inImage, inImageWidth, inImageHeight, 
          m_width, m_height, m_inOffsetX, m_inOffsetY, 
          m_inMinWidth, m_inMinHeight, m_inRatio, m_inRatioTo);
    }
    virtual bool Render
    (const void* image, int imageWidth, int imageHeight) {
         return RenderResizedImage
         (m_texture, image, imageWidth, imageHeight, m_width, m_height);
    }
    virtual bool RenderRaw
    (const void* image, int imageWidth, int imageHeight) {
         return RenderImage
         (m_texture, image, imageWidth, imageHeight);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool RenderResizedImage
    (GLuint glTexture, 
     const void* image, unsigned width, unsigned height, 
     const void* inImage, unsigned inWidth, unsigned inHeight, 
     unsigned toWidth, unsigned toHeight, unsigned inX, unsigned inY, 
     unsigned minInWidth, unsigned minInHeight, unsigned inRatio, unsigned inRatioTo = 1,
     GLint textureMagFilter = GL_LINEAR, GLint textureMinFilter = GL_LINEAR) {
        BeginRenderImage();
        Image2DTexture(glTexture, image, width, height);
        Rectangle rect(Size(width, height), Size(toWidth, toHeight));
        RenderTexture(glTexture, rect.origin, rect.size);

        if ((toWidth >= minInWidth) && (toHeight >= minInHeight))
        {
            float oX = (float)(inX);
            float oY = (float)(inY);
            float r = (float)(inRatio);
            float rTo = (float)(inRatioTo);
            float x = rect.origin.x + rect.size.width - (oX / toWidth);
            float y = rect.origin.y + rect.size.height - (oY / toHeight);

            Image2DTexture(glTexture, inImage, inWidth, inHeight);

            Rectangle inRect(Size(inWidth, inHeight), Size(toWidth, toHeight));

            RenderTexture
            (glTexture, 
             Point(x - ((inRect.size.width * rTo) / r), y - ((inRect.size.height * rTo) / r)),
             Size(((inRect.size.width * rTo) / r), ((inRect.size.height * rTo) / r)));
        }
        EndRenderImage();
        return !(GL_NO_ERROR != glGetError()); 
    }
    virtual bool RenderResizedImage
    (GLuint glTexture, const void* image, 
     unsigned width, unsigned height, unsigned toWidth, unsigned toHeight,
     GLint textureMagFilter = GL_LINEAR, GLint textureMinFilter = GL_LINEAR) {
        BeginRenderImage();
        Image2DTexture(glTexture, image, width, height);
        Rectangle rect(Size(width, height), Size(toWidth, toHeight));
        RenderTexture(glTexture, rect.origin, rect.size);
        EndRenderImage();
        return !(GL_NO_ERROR != glGetError()); 
    }
    virtual bool RenderImage
    (GLuint glTexture, const void* image, unsigned width, unsigned height,
     GLint textureMagFilter = GL_LINEAR, GLint textureMinFilter = GL_LINEAR) {
        BeginRenderImage();
        Image2DTexture(glTexture, image, width, height);
        RenderTexture(glTexture, Point(0, 0), Size(1, 1));
        EndRenderImage();
        return !(GL_NO_ERROR != glGetError()); 
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool BeginRenderImage()
    {
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_TEXTURE_2D);
        
        glMatrixMode (GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0, 1, 1, 0);
        
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        return !(GL_NO_ERROR != glGetError()); 
    }
    virtual bool EndRenderImage()
    {
        glFlush();
        return !(GL_NO_ERROR != glGetError()); 
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Image2DTexture
    (GLuint glTexture, const void* image, unsigned width, unsigned height,
     GLint textureMagFilter = GL_LINEAR, GLint textureMinFilter = GL_LINEAR) {
        glBindTexture(GL_TEXTURE_2D, glTexture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, textureMagFilter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, textureMinFilter);
        glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, image);
        return !(GL_NO_ERROR != glGetError()); 
    }
    virtual bool RenderTexture(GLuint glTexture, Point p, Size s) {
        glBindTexture(GL_TEXTURE_2D, glTexture);
        glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex2f(p.x, p.y);
        glTexCoord2f(1, 0); glVertex2f(p.x + s.width, p.y);
        glTexCoord2f(1, 1); glVertex2f(p.x + s.width, p.y + s.height);
        glTexCoord2f(0, 1); glVertex2f(p.x, p.y + s.height);
        glEnd();
        return !(GL_NO_ERROR != glGetError()); 
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    int m_width, m_height;
    int m_inMinWidth, m_inMinHeight;
    int m_inOffsetX, m_inOffsetY;
    int m_inRatio, m_inRatioTo;
    GLint m_textureMagFilter, m_textureMinFilter;
    GLuint m_texture;
};

} // namespace opengl 
} // namespace xos 

#endif // _XOS_GUI_OPENGL_IMAGERENDERER_HPP 
