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
///   File: iXosWebrtcMainView.mm
///
/// Author: $author$
///   Date: 3/7/2013
///////////////////////////////////////////////////////////////////////
#include "xos/webrtc/client/cocoa/iXosWebrtcMainView.hh"

#define XOS_WEBRTC_CLIENT_COCOA_IXOSWEBRTCMAINVIEW_DEFAULT_IMAGE_FILE "frame.raw"
#define XOS_WEBRTC_CLIENT_COCOA_IXOSWEBRTCMAINVIEW_DEFAULT_IMAGE_WIDTH 352
#define XOS_WEBRTC_CLIENT_COCOA_IXOSWEBRTCMAINVIEW_DEFAULT_IMAGE_HEIGHT 288
#define XOS_WEBRTC_CLIENT_COCOA_IXOSWEBRTCMAINVIEW_DEFAULT_IMAGE_DEPTH 4

#define XOS_WEBRTC_CLIENT_COCOA_IXOSWEBRTCMAINVIEW_DEFAULT_BG_COLOR blackColor

#if !defined(OBJC)
struct iXosWebrtcMainView;
#endif // !defined(OBJC)

namespace xos {
namespace webrtc {
namespace client {
namespace cocoa {

///////////////////////////////////////////////////////////////////////
///  Class: ImageObserver
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS ImageObserver: virtual public ImageObserverInterface {
public:
    typedef ImageObserverInterface Implements;
    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: ImageObserver
    ///////////////////////////////////////////////////////////////////////
    ImageObserver(): m_view(0), m_image(0) {
    }
    virtual ~ImageObserver() {
    }
    ///////////////////////////////////////////////////////////////////////
    // Register/Unregister Observer
    ///////////////////////////////////////////////////////////////////////
    virtual void Register(ImageInterface* image, iXosWebrtcMainView* view) {
        if ((image) && (view)) {
            image->RegisterImageObserver(this);
            m_image = m_image;
            m_view = view;
        }
    }
    virtual void Unregister() {
        if ((m_image)) {
            m_image->UnregisterImageObserver(this);
            m_image = 0;
        }
        m_view = 0;
    }
    ///////////////////////////////////////////////////////////////////////
    // Invalidate/Validate Window
    ///////////////////////////////////////////////////////////////////////
    virtual bool InvalidateWindow(bool eraseBackground = true)  { 
#if defined(OBJC)
        if ((m_view))
            [m_view InvalidateWindow:eraseBackground];
#endif // defined(OBJC)
        return true; 
    }
    virtual bool ValidateWindow()  { 
#if defined(OBJC)
        if ((m_view))
            [m_view ValidateWindow];
#endif // defined(OBJC)
        return true; 
    }
protected:
    iXosWebrtcMainView* m_view;
    ImageInterface* m_image;
};

} // namespace cocoa 
} // namespace client 
} // namespace webrtc 
} // namespace xos 

#if defined(OBJC)  
///////////////////////////////////////////////////////////////////////
/// Implentation: iXosWebrtcMainView
///
///       Author: $author$
///         Date: 3/7/2013
///////////////////////////////////////////////////////////////////////
@implementation iXosWebrtcMainView
    - (id)init:(NSRect)rect {
        [super initWithFrame:rect pixelFormat:[NSOpenGLView defaultPixelFormat]];
        m_imageData = 0;
        m_imageFile = XOS_WEBRTC_CLIENT_COCOA_IXOSWEBRTCMAINVIEW_DEFAULT_IMAGE_FILE;
        m_imageWidth = XOS_WEBRTC_CLIENT_COCOA_IXOSWEBRTCMAINVIEW_DEFAULT_IMAGE_WIDTH; 
        m_imageHeight = XOS_WEBRTC_CLIENT_COCOA_IXOSWEBRTCMAINVIEW_DEFAULT_IMAGE_HEIGHT; 
        m_imageDepth = XOS_WEBRTC_CLIENT_COCOA_IXOSWEBRTCMAINVIEW_DEFAULT_IMAGE_DEPTH; 
        m_imageSize = 0;
        m_invalid = false;
        m_image = 0;
        m_imageObserver = 0;
        return self;
    }
    - (void)prepareOpenGL {
        xos::gui::opengl::ContextImplemented openglContextImpl(self);

        if (!(m_imageData = [self ReadImageFile]))
            return;

        if ((m_openglRenderer.Init(openglContextImpl))) {
            m_openglRenderer.Prepare();
            return;
        }
        free(m_imageData);
        m_imageData = 0;
    }
    - (void)reshape {
        NSRect rect = [self bounds];
        if ((m_imageData)) {
            m_openglRenderer.Reshape(rect.size.width, rect.size.height);
        }
        [super reshape];
    }
    - (void)drawRect:(NSRect)rect {
        if ((m_image) && (m_invalid)) {
            uint8 *remoteImage, *localImage;
            int remoteImageFormat, localImageFormat;
            int remoteImageWidth, remoteImageHeight;
            int localImageWidth, localImageHeight;

            if ((remoteImage = m_image->AcquireRemoteImage
                (remoteImageWidth, remoteImageHeight, remoteImageFormat))) 
            {
                if ((localImage = m_image->AcquireLocalImage
                    (localImageWidth, localImageHeight, localImageFormat))) 
                {
                    m_openglRenderer.Render
                    (remoteImage, remoteImageWidth, remoteImageHeight,
                     localImage, localImageWidth, localImageHeight);
                    m_image->ReleaseLocalImage(localImage);
                } else {
                    m_openglRenderer.Render
                    (remoteImage, remoteImageWidth, remoteImageHeight);
                }
                m_invalid = false;
                m_image->ReleaseRemoteImage(remoteImage);
            } else {
                if ((localImage = m_image->AcquireLocalImage
                    (localImageWidth, localImageHeight, localImageFormat))) 
                {
                    m_openglRenderer.Render
                    (localImage, localImageWidth, localImageHeight);
                    m_invalid = false;
                    m_image->ReleaseLocalImage(localImage);
                } else {
                    [[NSColor XOS_WEBRTC_CLIENT_COCOA_IXOSWEBRTCMAINVIEW_DEFAULT_BG_COLOR] set];
                    NSRectFill([self bounds]);
                    m_invalid = false;
                }
            }
        } else {
            if ((m_imageData) && (!m_image)) {
                m_openglRenderer.Render
                (m_imageData, m_imageWidth, m_imageHeight,
                 m_imageData, m_imageWidth, m_imageHeight);
            } else {
                [[NSColor XOS_WEBRTC_CLIENT_COCOA_IXOSWEBRTCMAINVIEW_DEFAULT_BG_COLOR] set];
                NSRectFill([self bounds]);
            }
        }
    }
    - (void)InvalidateWindow:(bool)eraseBackground {
        m_invalid = true;
        [self setNeedsDisplay:YES];
    }
    - (void)ValidateWindow {
        m_invalid = false;
        [self setNeedsDisplay:NO];
    }
    - (void)SetImage:(xos::webrtc::client::ImageInterface*)image {
        if ((image)) {
            if ((m_imageObserver = new xos::webrtc::client::cocoa::ImageObserver())) {
                m_imageObserver->Register(m_image = image, self);
            }
        } else {
            if ((m_image)) {
                if ((m_imageObserver)) {
                    m_imageObserver->Unregister();
                    delete m_imageObserver;
                    m_imageObserver = 0;
                }
                m_image = 0;
            }
        }
    }
    - (void)SetImageFile:(const char*)chars {
        m_imageFile = chars;
    }
    - (void*)ReadImageFile {
        if ((m_imageData = malloc(m_imageSize=(m_imageWidth*m_imageHeight*m_imageDepth)))) {
            FILE* file = 0;
            size_t count = 0;
            if ((file = fopen(m_imageFile, "rb"))) {
                count = fread(m_imageData, m_imageSize, 1, file);
                fclose(file);
                if (1 > (count)) {
                    XOS_LOG_ERROR("failed on fread() of \"" << m_imageFile << "\"");
                    free(m_imageData);
                    m_imageData = 0;
                }
            } else {
                XOS_LOG_ERROR("failed on fopen(\"" << m_imageFile << "\",...)");
                free(m_imageData);
                m_imageData = 0;
            }
        }
        return m_imageData;
    }
@end
#else // defined(OBJC)  
#endif // defined(OBJC)  
