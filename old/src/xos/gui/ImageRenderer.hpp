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
#ifndef _XOS_GUI_IMAGERENDERER_HPP
#define _XOS_GUI_IMAGERENDERER_HPP

#include "xos/base/Base.hpp"

#define XOS_GUI_IMAGERENDERER_IN_MIN_WIDTH  100
#define XOS_GUI_IMAGERENDERER_IN_MIN_HEIGHT 100
#define XOS_GUI_IMAGERENDERER_IN_OFFSET_X   10
#define XOS_GUI_IMAGERENDERER_IN_OFFSET_Y   10
#define XOS_GUI_IMAGERENDERER_IN_RATIO      4
#define XOS_GUI_IMAGERENDERER_IN_RATIO_TO   1

namespace xos {
namespace gui {

typedef InterfaceBase ImageRendererInterfaceImplement;
///////////////////////////////////////////////////////////////////////
///  Class: ImageRendererInterface
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS ImageRendererInterface: virtual public ImageRendererInterfaceImplement
{
public:
    typedef ImageRendererInterfaceImplement Implements;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Prepare() {
	return true;
    }
    virtual bool Reshape(int width, int height) {
	return true;
    }
    virtual bool SwapBuffers() {
	return true;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Render
    (const void* image, int imageWidth, int imageHeight,
     const void* inImage, int inImageWidth, int inImageHeight) {
	 return false;
    }
    virtual bool Render
    (const void* image, int imageWidth, int imageHeight) {
	 return false;
    }
    virtual bool RenderRaw
    (const void* image, int imageWidth, int imageHeight) {
	 return false;
    }
};

typedef ImageRendererInterface ImageRendererImplement;
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
	  m_inMinWidth(XOS_GUI_IMAGERENDERER_IN_MIN_WIDTH),
	  m_inMinHeight(XOS_GUI_IMAGERENDERER_IN_MIN_HEIGHT),
	  m_inOffsetX(XOS_GUI_IMAGERENDERER_IN_OFFSET_X),
	  m_inOffsetY(XOS_GUI_IMAGERENDERER_IN_OFFSET_Y),
	  m_inRatio(XOS_GUI_IMAGERENDERER_IN_RATIO),
	  m_inRatioTo(XOS_GUI_IMAGERENDERER_IN_RATIO_TO) {
    }
    virtual ~ImageRenderer() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Reshape(int width, int height) {
	m_width = width;
	m_height = height;
	return true;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    int m_width, m_height;
    int m_inMinWidth, m_inMinHeight;
    int m_inOffsetX, m_inOffsetY;
    int m_inRatio, m_inRatioTo;
};

} // namespace gui
} // namespace xos

#endif // _XOS_GUI_IMAGERENDERER_HPP
