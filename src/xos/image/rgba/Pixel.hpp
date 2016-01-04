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
///   File: Pixel.hpp
///
/// Author: $author$
///   Date: 8/15/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_IMAGE_RGBA_PIXEL_HPP
#define _XOS_IMAGE_RGBA_PIXEL_HPP

#include "xos/image/Pixel.hpp"
#include "xos/image/rgba/Color.hpp"

namespace xos {
namespace image {
namespace rgba {

///////////////////////////////////////////////////////////////////////
///  Class: PixelInterfaceT
///////////////////////////////////////////////////////////////////////
template 
<typename TColorSample, 
 typename TColorSaturated,
 TColorSaturated VColorSaturated,
 class TImplement>

class _EXPORT_CLASS PixelInterfaceT: virtual public TImplement {
public:
    typedef TImplement Implements;
    typedef TColorSample tColorSample;
    enum { vColorSaturated = VColorSaturated };
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void Set
    (tColorSample red,
     tColorSample green,
     tColorSample blue,
     tColorSample alpha = vColorSaturated) = 0;
    virtual void Get
    (tColorSample red,
     tColorSample green,
     tColorSample blue,
     tColorSample alpha) const = 0;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual tColorSample red() const = 0;
    virtual tColorSample green() const = 0;
    virtual tColorSample blue() const = 0;
    virtual tColorSample alpha() const = 0;
};

///////////////////////////////////////////////////////////////////////
///  Class: PixelT
///////////////////////////////////////////////////////////////////////
template 
<typename TColorSample, 
 typename TColorSaturated,
 TColorSaturated VColorSaturated,
 class TImplement, class TExtend>

class _EXPORT_CLASS PixelT
: virtual public TImplement, public TExtend {
public:
    typedef TImplement Implements;
    typedef TExtend Extends;
    typedef TColorSample tColorSample;
    enum { vColorSaturated = VColorSaturated };
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    PixelT
    (tColorSample red = 0,
     tColorSample green = 0,
     tColorSample blue = 0,
     tColorSample alpha = vColorSaturated) {
         Set(red, green, blue, alpha);
    }
    virtual ~PixelT() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void Set
    (tColorSample red,
     tColorSample green,
     tColorSample blue,
     tColorSample alpha = vColorSaturated) {
         m_sample[color::channel::Red] = red;
         m_sample[color::channel::Green] = green;
         m_sample[color::channel::Blue] = blue;
         m_sample[color::channel::Alpha] = alpha;
    }
    virtual void Get
    (tColorSample red,
     tColorSample green,
     tColorSample blue,
     tColorSample alpha) const {
          red = m_sample[color::channel::Red];
          green = m_sample[color::channel::Green];
          blue = m_sample[color::channel::Blue];
          alpha = m_sample[color::channel::Alpha];
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual tColorSample red() const { return m_sample[color::channel::Red]; }
    virtual tColorSample green() const { return m_sample[color::channel::Green]; }
    virtual tColorSample blue() const { return m_sample[color::channel::Blue]; }
    virtual tColorSample alpha() const { return m_sample[color::channel::Alpha]; }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    tColorSample m_sample[color::Channels];
};

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
typedef PixelInterfaceT
<uint8_t, uint8_t, (uint8_t)(-1), image::PixelInterface> Pixel32Interface;

typedef PixelT
<uint8_t, uint8_t, (uint8_t)(-1), Pixel32Interface, image::Pixel> Pixel8;

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
typedef PixelInterfaceT
<uint16_t, uint16_t, (uint16_t)(-1), image::PixelInterface> Pixel64Interface;

typedef PixelT
<uint16_t, uint16_t, (uint16_t)(-1), Pixel64Interface, image::Pixel> Pixel16;

} // namespace rgba 
} // namespace image 
} // namespace xos 

#endif // _XOS_IMAGE_RGBA_PIXEL_HPP 
