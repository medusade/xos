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
///   File: Color.hpp
///
/// Author: $author$
///   Date: 3/25/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_X11_COLOR_HPP
#define _XOS_GUI_X11_COLOR_HPP

#include "xos/gui/x11/Created.hpp"
#include "xos/gui/x11/Attached.hpp"
#include "xos/os/Logger.hpp"

namespace xos {
namespace x11 {

typedef InterfaceBase ColorImplement;
typedef Attached<XPixel, int, 0> ColorAttached;
typedef xos::Created<XPixel, int, 0, ColorAttached> ColorCreated;
typedef Created<XPixel, int, 0, ColorCreated> ColorExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Color
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Color: virtual public ColorImplement, public ColorExtend {
public:
    typedef ColorImplement Implements;
    typedef ColorExtend Extends;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: Color
    ///////////////////////////////////////////////////////////////////////
    Color(XDisplay* xDisplay=0, XPixel detached=0, bool isCreated=false)
    : Extends(xDisplay, detached, isCreated), m_xColormap(0) {
    }
    virtual ~Color() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool AllocateRGB8
    (XDisplay& xDisplay, XColormap xColormap, uint8_t r, uint8_t g, uint8_t b) {
        bool isSuccess = CreateRGB8(xDisplay, xColormap, r,g,b);
        return isSuccess;
    }
    virtual bool Free() {
        bool isSuccess = Destroy();
        return isSuccess;
    }
    virtual bool CreateRGB8
    (XDisplay& xDisplay, XColormap xColormap, uint8_t r, uint8_t g, uint8_t b) {
        bool isSuccess = false;
        if ((Destroyed()) && (xColormap)) {
            XColor xColor;
            RGB8ToXColor(xColor, r,g,b);
            if ((XAllocColor(&xDisplay, xColormap, &xColor))) {
                XPixel detached = xColor.pixel;
                m_xColormap = xColormap;
                AttachCreated(&xDisplay, detached);
                isSuccess = true;
            } else  {
                XOS_LOG_ERROR("failed on XAllocColor()");
            }
        }
        return isSuccess;
    }
    virtual bool Destroy() {
        bool isSuccess = false;
        bool isCreated = false;
        XDisplay* xDisplay = 0;
        XColormap xColormap = m_xColormap;
        XPixel detached = Detach(xDisplay, isCreated);
        m_xColormap = 0;
        if ((detached) && (xColormap)) {
            XFreeColors(xDisplay, xColormap, &detached, 1, 0);
            isSuccess = true;
        }
        return isSuccess;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Lookup
    (XDisplay& xDisplay, XColormap xColormap, const char* colorName) {
        bool isSuccess = false;
        if ((Destroyed()) && (xColormap) && (colorName)) {
            XColor xColorDefinition;
            XColor xColor;
            if ((XLookupColor(&xDisplay, xColormap, colorName, &xColorDefinition, &xColor))) {
                XPixel detached = xColor.pixel;
                m_xColormap = xColormap;
                Attach(&xDisplay, detached);
                isSuccess = true;
            } else {
                XOS_LOG_ERROR("failed on XLookupColor()");
            }
        }
        return isSuccess;
    }
    virtual bool QueryRGB8
    (XDisplay& xDisplay, XColormap xColormap, uint8_t r, uint8_t g, uint8_t b) {
        bool isSuccess = false;
        if ((Destroyed()) && (xColormap)) {
            XPixel detached;
            XColor xColor;
            RGB8ToXColor(xColor, r,g,b);
            XQueryColor(&xDisplay, xColormap, &xColor);
            detached = xColor.pixel;
            m_xColormap = xColormap;
            Attach(&xDisplay, detached);
            isSuccess = true;
        }
        return isSuccess;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool AttachWhiteOfScreen(XDisplay& xDisplay, XScreen& xScreen) {
        bool isSuccess = false;
        if ((Destroyed())) {
            XPixel detached = XWhitePixelOfScreen(&xScreen);
            Attach(&xDisplay, detached);
            isSuccess = true;
        }
        return isSuccess;
    }
    virtual bool AttachBlackOfScreen(XDisplay& xDisplay, XScreen& xScreen) {
        bool isSuccess = false;
        if ((Destroyed())) {
            XPixel detached = XBlackPixelOfScreen(&xScreen);
            Attach(&xDisplay, detached);
            isSuccess = true;
        }
        return isSuccess;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    static void RGB8ToXColor(XColor& color, uint8_t r, uint8_t g, uint8_t b) {
        unsigned long iL = (1 << (16))-1;
        unsigned short iS = (1 << (8))-1;
        unsigned short rS = (unsigned short)((iL*r)/iS);
        unsigned short gS = (unsigned short)((iL*g)/iS);
        unsigned short bS = (unsigned short)((iL*b)/iS);

        memset(&color, 0, sizeof(XColor));
        color.red = rS;
        color.green = gS;
        color.blue = bS;
    }
    virtual operator XPixel() const {
        return m_attachedTo;
    }

protected:
    XColormap m_xColormap;
};

} // namespace x11 
} // namespace xos 

#endif // _XOS_GUI_X11_COLOR_HPP 
