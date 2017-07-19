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
///   File: VideoRenderer.cpp
///
/// Author: $author$
///   Date: 2/24/2013
///////////////////////////////////////////////////////////////////////
#include "xos/webrtc/client/opengl/VideoRenderer.hpp"

namespace xos {
namespace webrtc {
namespace client {
namespace opengl {

/*///////////////////////////////////////////////////////////////////////
///  Class: VideoRenderer
///
/// Author: $author$
///   Date: 12/22/2012
///////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
///  Function: VideoRenderer::Prepare
///
///    Author: $author$
///      Date: 12/22/2012
///////////////////////////////////////////////////////////////////////
void VideoRenderer::Prepare() {
    if ((GetHasFailed())) return;

    glGenTextures(1, &m_texture);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    SetHasFailed(GL_NO_ERROR != glGetError());
}
///////////////////////////////////////////////////////////////////////
///  Function: VideoRenderer::Reshape
///
///    Author: $author$
///      Date: 12/22/2012
///////////////////////////////////////////////////////////////////////
void VideoRenderer::Reshape(int width, int height) {
    if ((GetHasFailed())) return;
    m_width = width; m_height = height;
    glViewport(0, 0, width, height);
}
///////////////////////////////////////////////////////////////////////
///  Function: VideoRenderer::Render
///
///    Author: $author$
///      Date: 12/22/2012
///////////////////////////////////////////////////////////////////////
void VideoRenderer::Render
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
///////////////////////////////////////////////////////////////////////
///  Function: VideoRenderer::Render
///
///    Author: $author$
///      Date: 12/22/2012
///////////////////////////////////////////////////////////////////////
void VideoRenderer::Render
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
///////////////////////////////////////////////////////////////////////
///  Function: VideoRenderer::BeginRender
///
///    Author: $author$
///      Date: 12/22/2012
///////////////////////////////////////////////////////////////////////
void VideoRenderer::BeginRender() {
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_TEXTURE_2D);

    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 1, 1, 0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
///////////////////////////////////////////////////////////////////////
///  Function: VideoRenderer::EndRender
///
///    Author: $author$
///      Date: 12/22/2012
///////////////////////////////////////////////////////////////////////
void VideoRenderer::EndRender() {
    glFlush();
}
///////////////////////////////////////////////////////////////////////
///  Function: VideoRenderer::LoadTexture
///
///    Author: $author$
///      Date: 12/22/2012
///////////////////////////////////////////////////////////////////////
void VideoRenderer::LoadTexture
(GLuint texture, const void* image, int w, int h) {
    if ((GetHasFailed())) return;

    glBindTexture(GL_TEXTURE_2D, m_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_textureMagFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_textureMinFilter);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0, TextureImageFormat(), GL_UNSIGNED_BYTE, image);

    SetHasFailed(GL_NO_ERROR != glGetError());
}
///////////////////////////////////////////////////////////////////////
///  Function: VideoRenderer::RenderTexture
///
///    Author: $author$
///      Date: 12/22/2012
///////////////////////////////////////////////////////////////////////
void VideoRenderer::RenderTexture
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
}*/

} // namespace opengl 
} // namespace client 
} // namespace webrtc 
} // namespace xos 
