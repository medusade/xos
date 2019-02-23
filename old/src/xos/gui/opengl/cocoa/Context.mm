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
///   File: Context.mm
///
/// Author: $author$
///   Date: 12/22/2012
///////////////////////////////////////////////////////////////////////
#include "xos/gui/opengl/cocoa/Context.hh"

namespace xos {
namespace opengl {

///////////////////////////////////////////////////////////////////////
///  Class: ContextImplemented
///
/// Author: $author$
///   Date: 12/22/2012
///////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
///  Function: ContextImplemented::AcquirePixelFormat
///
///    Author: $author$
///      Date: 12/22/2012
///////////////////////////////////////////////////////////////////////
NSOpenGLPixelFormat* ContextImplemented::AcquirePixelFormat(NSOpenGLPixelFormatAttribute* attributes) const {
    NSOpenGLPixelFormat* pixelFormat = 0;
#if defined(OBJC) 
    pixelFormat = [[NSOpenGLPixelFormat alloc] initWithAttributes:(NSOpenGLPixelFormatAttribute*)attributes];
#else // defined(OBJC) 
#endif // defined(OBJC) 
    return pixelFormat;
}
///////////////////////////////////////////////////////////////////////
///  Function: ContextImplemented::ReleasePixelFormat
///
///    Author: $author$
///      Date: 12/22/2012
///////////////////////////////////////////////////////////////////////
bool ContextImplemented::ReleasePixelFormat(NSOpenGLPixelFormat* pixelFormat) const {
    bool isSuccess = false;
#if defined(OBJC) 
    if ((isSuccess = (0 != pixelFormat))) {
        [pixelFormat release];
    }
#else // defined(OBJC) 
#endif // defined(OBJC) 
    return isSuccess;
}
///////////////////////////////////////////////////////////////////////
///  Function: ContextImplemented::SetPixelFormat
///
///    Author: $author$
///      Date: 12/22/2012
///////////////////////////////////////////////////////////////////////
NSOpenGLPixelFormat* ContextImplemented::SetPixelFormat(NSOpenGLPixelFormat* toPixelFormat) {
    NSOpenGLPixelFormat* pixelFormat = 0;
#if defined(OBJC) 
    if (((m_view) && (toPixelFormat))) {
        [m_view setPixelFormat:(pixelFormat = toPixelFormat)];
    }
#else // defined(OBJC) 
#endif // defined(OBJC) 
    return pixelFormat;
}
///////////////////////////////////////////////////////////////////////
///  Function: ContextImplemented::GetPixelFormat
///
///    Author: $author$
///      Date: 12/22/2012
///////////////////////////////////////////////////////////////////////
NSOpenGLPixelFormat* ContextImplemented::GetPixelFormat() const {
    NSOpenGLPixelFormat* pixelFormat = 0;
#if defined(OBJC) 
    if ((m_view)) {
        pixelFormat = [m_view pixelFormat];
    }
#else // defined(OBJC) 
#endif // defined(OBJC) 
    return pixelFormat;
}
///////////////////////////////////////////////////////////////////////
///  Function: ContextImplemented::GetContext
///
///    Author: $author$
///      Date: 12/22/2012
///////////////////////////////////////////////////////////////////////
NSOpenGLContext* ContextImplemented::GetContext() const {
    NSOpenGLContext* context = 0;
#if defined(OBJC) 
    if ((m_view)) {
        context = [m_view openGLContext];
    }
#else // defined(OBJC) 
#endif // defined(OBJC) 
    return context;
}

namespace cocoa {

///////////////////////////////////////////////////////////////////////
///  Class: Context
///
/// Author: $author$
///   Date: 12/22/2012
///////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
///  Function: Context::GetPixelFormatAttributes
///
///    Author: $author$
///      Date: 12/22/2012
///////////////////////////////////////////////////////////////////////
NSOpenGLPixelFormatAttribute* Context::GetPixelFormatAttributes() const
{
#if defined(OBJC) 
    NSOpenGLPixelFormatAttribute attributes[] = {
        NSOpenGLPFAWindow,         // window rendered
        NSOpenGLPFAAccelerated,    // hardware accelerated
        NSOpenGLPFADoubleBuffer,   // double buffered
        //NSOpenGLPFAMinimumPolicy,  // meets or exceeds attributes
        0
    };
#else // defined(OBJC) 
    NSOpenGLPixelFormatAttribute* attributes = 0;
#endif // defined(OBJC) 
    return attributes;
}
///////////////////////////////////////////////////////////////////////
///  Function: Context::GetContext
///
///    Author: $author$
///      Date: 12/22/2012
///////////////////////////////////////////////////////////////////////
NSOpenGLContext* Context::GetContext() const {
    NSOpenGLContext* context = 0;
#if defined(OBJC) 
    if ((m_view)) {
        context = [m_view openGLContext];
    }
#else // defined(OBJC) 
#endif // defined(OBJC) 
    return context;
}
} // namespace cocoa 
} // namespace opengl 
} // namespace xos 
