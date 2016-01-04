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
#ifndef _XOS_APP_GUI_HELLO_HPP
#define _XOS_APP_GUI_HELLO_HPP

#include "xos/os/Logger.hpp"

#define XOS_APP_GUI_HELLO_DEFAULT_IMAGE_FILENAME "video-frame-bgra.raw"
#define XOS_APP_GUI_HELLO_DEFAULT_IMAGE_WIDTH 352
#define XOS_APP_GUI_HELLO_DEFAULT_IMAGE_HEIGHT 288
#define XOS_APP_GUI_HELLO_DEFAULT_IMAGE_DEPTH 4

namespace xos {
namespace app {
namespace gui {
namespace hello {

///////////////////////////////////////////////////////////////////////
///  Class: ImageT
///////////////////////////////////////////////////////////////////////
template
<class TImplement, class TExtend>

class _EXPORT_CLASS ImageT
: virtual public TImplement, public TExtend {
public:
    typedef TImplement Implements;
    typedef TExtend Extends;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: ImageT
    ///////////////////////////////////////////////////////////////////////
    ImageT()
    : m_image(0), 
      m_imageSize(0), 
      m_imageWidth(XOS_APP_GUI_HELLO_DEFAULT_IMAGE_WIDTH),  
      m_imageHeight(XOS_APP_GUI_HELLO_DEFAULT_IMAGE_HEIGHT),  
      m_imageDepth(XOS_APP_GUI_HELLO_DEFAULT_IMAGE_DEPTH), 
      m_imageFile(XOS_APP_GUI_HELLO_DEFAULT_IMAGE_FILENAME), 
      m_defaultImageFile(XOS_APP_GUI_HELLO_DEFAULT_IMAGE_FILENAME) {
    }
    virtual ~ImageT() {
        FreeImage();
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void* LoadImageFile(const std::string& imageFile) {
        const char* chars;
        if ((0 < (imageFile.length())) && (chars = imageFile.c_str()))
            LoadImageFile(chars);
        return m_image;
    }
    virtual void* LoadImageFile() {
        LoadImageFile(m_imageFile);
        return m_image;
    }
    virtual void* LoadImageFile(const char* chars) {
        FreeImage();

        if ((chars) && (chars != m_imageFile))
            SetImageFile(chars);

        if ((m_imageFile)) {
            FILE* file = 0;
            XOS_LOG_TRACE("fopen(\"" << m_imageFile << "\", \"rb\")...");
            if ((file = fopen(m_imageFile, "rb"))) {
                XOS_LOG_TRACE("...fopen(\"" << m_imageFile << "\", \"rb\")");
                if ((AllocateImage(m_imageWidth, m_imageHeight, m_imageDepth))) {
                    size_t count = 0;
                    XOS_LOG_TRACE("fread(...," << m_imageSize << ", 1, ...)...");
                    count = fread(m_image, m_imageSize, 1, file);
                    XOS_LOG_TRACE("..." << count << " = fread(...," << m_imageSize << ", 1, ...)...");
                    fclose(file);
                    if (1 > (count)) {
                        XOS_LOG_ERROR("failed on fread() of \"" << m_imageFile << "\"");
                        FreeImage();
                    }
                }
            } else {
                XOS_LOG_ERROR("failed on fopen(\"" << m_imageFile << "\",...)");
                InitImage();
            }
        }
        return m_image;
    }
    virtual void* AllocateImage
    (int imageWidth, int imageHeight, int imageDepth) {
        void* image = 0;
        int imageSize;
        if (0 < (imageSize = (imageWidth*imageHeight*imageDepth))) {
            FreeImage();
            if ((image = malloc(imageSize))) {
                m_image = image;
                m_imageSize = imageSize;
                m_imageWidth = imageWidth;
                m_imageHeight = imageHeight;
                m_imageDepth = imageDepth;
            } else {
                XOS_LOG_ERROR("failed on malloc(" << imageSize << ")");
            }
        }
        return image;
    }
    virtual void FreeImage() {
        if ((m_image)) {
            free(m_image);
        }
        InitImage();
    }
    virtual void InitImage() {
        m_image = 0;
        m_imageSize = 0;
        m_imageWidth = XOS_APP_GUI_HELLO_DEFAULT_IMAGE_WIDTH;  
        m_imageHeight = XOS_APP_GUI_HELLO_DEFAULT_IMAGE_HEIGHT;  
        m_imageDepth = XOS_APP_GUI_HELLO_DEFAULT_IMAGE_DEPTH; 
        m_imageFile = m_defaultImageFile;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    const char* SetImageFile(const char* chars) {
        if ((chars)) {
            m_imageFileString.Assign(chars);
            if ((chars = m_imageFileString.Chars()))
                m_imageFile = chars;
        }
        return chars;
    }
    const char* ImageFile() const {
        return m_imageFile;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void* Image() const {
        return (void*)(m_image);
    }
    virtual unsigned ImageSize() const {
        return (m_imageSize);
    }
    virtual unsigned ImageWidth() const {
        return (m_imageWidth);
    }
    virtual unsigned ImageHeight() const {
        return (m_imageHeight);
    }
    virtual unsigned ImageDepth() const {
        return (m_imageDepth);
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    void* m_image;
    unsigned m_imageSize, m_imageWidth, m_imageHeight, m_imageDepth;
    const char* m_imageFile;
    const char* m_defaultImageFile;
    String m_imageFileString;
};

} // namespace hello 
} // namespace gui 
} // namespace app 
} // namespace xos 

#endif // _XOS_APP_GUI_HELLO_HPP 
