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
#ifndef _XOS_IMAGE_PIXEL_HPP
#define _XOS_IMAGE_PIXEL_HPP

#include "xos/base/Base.hpp"

namespace xos {
namespace image {

typedef InterfaceBase PixelInterfaceImplement;
///////////////////////////////////////////////////////////////////////
///  Class: PixelInterface
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS PixelInterface: virtual public PixelInterfaceImplement {
public:
    typedef PixelInterfaceImplement Implements;
};

typedef PixelInterface PixelImplement;
typedef ExportBase PixelExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Pixel
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Pixel
: virtual public PixelImplement, public PixelExtend {
public:
    typedef PixelImplement Implements;
    typedef PixelExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Pixel() {
    }
    virtual ~Pixel() {
    }
};

} // namespace image 
} // namespace xos 


#endif // _XOS_IMAGE_PIXEL_HPP 
        

