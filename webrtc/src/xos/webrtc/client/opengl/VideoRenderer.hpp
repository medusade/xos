///////////////////////////////////////////////////////////////////////
/// Copyright 2013, Google Inc.
///
/// Redistribution and use in source and binary forms, with or without
/// modification, are permitted provided that the following conditions are met:
/// 
///  1. Redistributions of source code must retain the above copyright notice,
///     this list of conditions and the following disclaimer.
///  2. Redistributions in binary form must reproduce the above copyright notice,
///     this list of conditions and the following disclaimer in the documentation
///     and/or other materials provided with the distribution.
///  3. The name of the author may not be used to endorse or promote products
///     derived from this software without specific prior written permission.
/// 
/// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
/// WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
/// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
/// EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
/// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
/// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
/// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
/// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
/// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
/// ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
///
///   File: VideoRenderer.hpp
///
/// Author: $author$
///   Date: 2/24/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_WEBRTC_CLIENT_OPENGL_VIDEORENDERER_HPP
#define _XOS_WEBRTC_CLIENT_OPENGL_VIDEORENDERER_HPP

#include "xos/webrtc/client/LocalWindow.hpp"
#include "xos/gui/opengl/Context.hpp"
#include "xos/gui/opengl/Rectangle.hpp"
#include "xos/base/Base.hpp"

namespace xos {
namespace webrtc {
namespace client {
namespace opengl {

typedef InterfaceBase VideoRendererImplement;
typedef ExportBase VideoRendererExtend;
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS VideoRenderer
: virtual public VideoRendererImplement, public VideoRendererExtend {
public:
    typedef VideoRendererImplement Implements;
    typedef VideoRendererExtend Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    VideoRenderer()
    : m_dontUse(false),
      m_hasFailed(false),
      m_localWindowMinimum(XOS_WEBRTC_CLIENT_LOCAL_WINDOW_MINIMUM),
      m_localWindowOffet(XOS_WEBRTC_CLIENT_LOCAL_WINDOW_OFFSET),
      m_localWindowRatio(XOS_WEBRTC_CLIENT_LOCAL_WINDOW_RATIO),
      m_textureMagFilter(GL_LINEAR),
      m_textureMinFilter(GL_LINEAR)
    {}
    virtual ~VideoRenderer() {}

    virtual bool Init() { return true; }
    virtual bool Finish() { return true; }

    virtual void Prepare() {
        if ((GetHasFailed())) return;
        glGenTextures(1, &m_texture);
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_CULL_FACE);
        SetHasFailed(GL_NO_ERROR != glGetError());
    }
    virtual void Reshape(int width, int height) {
        if ((GetHasFailed())) return;
        m_width = width; m_height = height;
        glViewport(0, 0, width, height);
    }
    virtual void Render
    (const void* remoteImage, int remoteImageWidth, int remoteImageHeight,
     const void* localImage, int localImageWidth, int localImageHeight) {
        if ((GetHasFailed())) return;
        BeginRender();

        LoadTexture
        (m_texture, remoteImage, remoteImageWidth, remoteImageHeight);

        gui::opengl::Rectangle rrect
        (gui::opengl::Size(remoteImageWidth, remoteImageHeight), 
         gui::opengl::Size(m_width, m_height));

        RenderTexture(m_texture, rrect.origin, rrect.size);

        if ((m_width >= m_localWindowMinimum) && (m_height >= m_localWindowMinimum)) {
            float o = (float)(m_localWindowOffet);
            float r = (float)(m_localWindowRatio);
            float x = rrect.origin.x + rrect.size.width - (o / m_width);
            float y = rrect.origin.y + rrect.size.height - (o / m_height);

            LoadTexture
            (m_texture, localImage, localImageWidth, localImageHeight);

            gui::opengl::Rectangle rect
            (gui::opengl::Size(localImageWidth, localImageHeight), 
             gui::opengl::Size(m_width, m_height));

            RenderTexture
            (m_texture, gui::opengl::Point(x - rect.size.width / r, y - rect.size.height / r),
             gui::opengl::Size(rect.size.width / r, rect.size.height / r));
        }
        EndRender();
    }
    virtual void Render
    (const void* remoteImage, int remoteImageWidth, int remoteImageHeight) {
        if ((GetHasFailed())) return;
        BeginRender();

        LoadTexture
        (m_texture, remoteImage, remoteImageWidth, remoteImageHeight);

        gui::opengl::Rectangle rect
        (gui::opengl::Size(remoteImageWidth, remoteImageHeight), 
         gui::opengl::Size(m_width, m_height));

        RenderTexture(m_texture, rect.origin, rect.size);
        EndRender();
    }
    virtual void BeginRender() {
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glEnable(GL_TEXTURE_2D);
        glMatrixMode (GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0, 1, 1, 0);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }
    virtual void EndRender() {
        glFlush();
    }
    virtual void LoadTexture
    (GLuint texture, const void* image, int w, int h) {
        if ((GetHasFailed())) return;
        glBindTexture(GL_TEXTURE_2D, m_texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_textureMagFilter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_textureMinFilter);
        glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0, TextureImageFormat(), GL_UNSIGNED_BYTE, image);
        SetHasFailed(GL_NO_ERROR != glGetError());
    }
    virtual void RenderTexture
    (GLuint texture, gui::opengl::Point p, gui::opengl::Size s) {
        if ((GetHasFailed())) return;
        glBindTexture(GL_TEXTURE_2D, m_texture);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(p.x, p.y);
        glTexCoord2f(1.0f, 0.0f); glVertex2f(p.x + s.width, p.y);
        glTexCoord2f(1.0f, 1.0f); glVertex2f(p.x + s.width, p.y + s.height);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(p.x, p.y + s.height);
        glEnd();
        SetHasFailed(GL_NO_ERROR != glGetError());
    }

    virtual void SwapBuffers(){}

    virtual GLenum TextureImageFormat() const 
    { return GL_BGRA; }

    virtual bool SetHasFailed(bool isTrue=true)
    { if ((isTrue)) HasFailed(); return m_hasFailed; }
    virtual bool GetHasFailed() const 
    { return m_hasFailed; }

    virtual void HasFailed()
    { m_hasFailed = true; DontUse();}

    virtual void DontUse()
    { SetDontUse(); }
    virtual void Use()
    { SetDontUse(false); }

    virtual bool SetDontUse(bool isTrue=true)
    { if (!(m_hasFailed)) m_dontUse = isTrue; return m_dontUse; }
    virtual bool GetDontUse() const
    { return m_dontUse; }

protected:
    bool m_dontUse;
    bool m_hasFailed;
    int m_width;
    int m_height;
    int m_localWindowMinimum;
    int m_localWindowOffet;
    int m_localWindowRatio;
    GLint m_textureMagFilter;
    GLint m_textureMinFilter;
    GLuint m_texture;
};

} // namespace opengl 
} // namespace client 
} // namespace webrtc 
} // namespace xos 

#endif // _XOS_WEBRTC_CLIENT_OPENGL_VIDEORENDERER_HPP 
