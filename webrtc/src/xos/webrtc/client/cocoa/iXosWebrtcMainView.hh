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
///   File: iXosWebrtcMainView.hh
///
/// Author: $author$
///   Date: 3/7/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_WEBRTC_CLIENT_COCOA_IXOSWEBRTCMAINVIEW_HH
#define _XOS_WEBRTC_CLIENT_COCOA_IXOSWEBRTCMAINVIEW_HH

#include "xos/gui/cocoa/iXosWindowMain.hh"
#include "xos/gui/opengl/cocoa/Context.hh"
#include "xos/webrtc/client/cocoa/OpenGL.hh"
#include "xos/webrtc/client/ImageInterface.hpp"

namespace xos {
namespace webrtc {
namespace client {
namespace cocoa {

///////////////////////////////////////////////////////////////////////
///  Class: ImageObserver
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS ImageObserver;

} // namespace cocoa 
} // namespace client 
} // namespace webrtc 
} // namespace xos 

#if defined(OBJC)  
///////////////////////////////////////////////////////////////////////
/// Interface: iXosWebrtcMainView
///
///    Author: $author$
///      Date: 3/7/2013
///////////////////////////////////////////////////////////////////////
@interface iXosWebrtcMainView: NSOpenGLView {
    void* m_imageData;
    const char* m_imageFile;
    unsigned m_imageWidth, m_imageHeight, m_imageDepth, m_imageSize;
    bool m_invalid;
    xos::webrtc::client::ImageInterface* m_image;
    xos::webrtc::client::cocoa::ImageObserver* m_imageObserver;
    xos::webrtc::client::cocoa::opengl::VideoRenderer m_openglRenderer;
    }
    - (id)init:(NSRect)rect;
    - (void)prepareOpenGL;
    - (void)reshape;
    - (void)drawRect:(NSRect)rect;
    - (void)InvalidateWindow:(bool)eraseBackground;
    - (void)ValidateWindow;
    - (void)SetImage:(xos::webrtc::client::ImageInterface*)image;
    - (void)SetImageFile:(const char*)chars;
    - (void*)ReadImageFile;
@end
#else // defined(OBJC)  
#endif // defined(OBJC)  

#endif // _XOS_WEBRTC_CLIENT_COCOA_IXOSWEBRTCMAINVIEW_HH 
