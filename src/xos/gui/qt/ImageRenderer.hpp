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
///   Date: 7/21/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_QT_IMAGERENDERER_HPP
#define _XOS_GUI_QT_IMAGERENDERER_HPP

#include "xos/gui/ImageRenderer.hpp"
#include "xos/gui/Rectangle.hpp"
#include "xos/gui/qt/Gui.hpp"

namespace xos {
namespace gui {
namespace qt {

typedef gui::ImageRendererImplement ImageRendererImplement;
typedef gui::ImageRenderer ImageRendererExtend;
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
    ImageRenderer(QWidget* widget = 0)
    : m_widget(widget) {
    }
    virtual ~ImageRenderer() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Init(QWidget* widget) {
        if ((m_widget = widget))
            return true;
        return false;
    }
    virtual bool Finish() {
        if ((m_widget)) {
            m_widget = 0;
            return true;
        }
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Render
    (const void* image, int imageWidth, int imageHeight,
     const void* inImage, int inImageWidth, int inImageHeight) {
	    gui::Size fromSize(imageWidth, imageHeight);
	    gui::Size toSize(m_width, m_height);
	    gui::Rectangle rect(fromSize, toSize);

	    if ((Render
	         (image, imageWidth, imageHeight, 
              m_width,m_height, rect.origin.x,rect.origin.y,
              Qt::KeepAspectRatio, Qt::SmoothTransformation))) {
            if ((m_width >= m_inMinWidth) && (m_height >= m_inMinHeight)) {
                int x = rect.origin.x + rect.size.width - m_inOffsetX;
                int y = rect.origin.y + rect.size.height - m_inOffsetY;
                int width = (rect.size.width*m_inRatioTo)/m_inRatio;
                int height = (rect.size.height*m_inRatioTo)/m_inRatio;
	            gui::Size fromInSize(inImageWidth, inImageHeight);
	            gui::Size toInSize(width, height);
	            gui::Rectangle InRect(fromInSize, toInSize);
	            return Render
	            (inImage, inImageWidth, inImageHeight, 
                 InRect.size.width,InRect.size.height, 
                 x-InRect.size.width,y-InRect.size.height,
                 Qt::KeepAspectRatio, Qt::SmoothTransformation);
            }
        }
	    return false;
    }
    virtual bool Render
    (const void* image, int imageWidth, int imageHeight) {
	    gui::Size fromSize(imageWidth, imageHeight);
	    gui::Size toSize(m_width, m_height);
	    gui::Rectangle rect(fromSize, toSize);
	    return Render
	    (image, imageWidth, imageHeight, 
         m_width,m_height, rect.origin.x,rect.origin.y,
         Qt::KeepAspectRatio, Qt::SmoothTransformation);
    }
    virtual bool RenderRaw
    (const void* image, int imageWidth, int imageHeight) {
	    return Render
	    (image, imageWidth, imageHeight, 
         m_width,m_height, 0,0, 
         Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    }
    virtual bool Render
    (const void* image, int imageWidth, int imageHeight,
     int width, int height, int x, int y,
     Qt::AspectRatioMode aspectRatioMode, Qt::TransformationMode transformationMode) {
	    if ((m_widget)) {
	        QImage qImage
	        ((const unsigned char*)(image),
	         imageWidth, imageHeight, QImage::Format_ARGB32);
	        QPainter qPainter(m_widget);
	        qPainter.drawImage
	        (x,y, qImage.scaled(width, height, aspectRatioMode, transformationMode));
	        return true;
	    }
	    return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    QWidget* m_widget;
};

} // namespace qt
} // namespace gui
} // namespace xos

#endif // _XOS_GUI_QT_IMAGERENDERER_HPP
