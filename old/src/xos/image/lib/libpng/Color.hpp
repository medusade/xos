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
///   Date: 8/17/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_IMAGE_LIB_LIBPNG_COLOR_HPP
#define _XOS_IMAGE_LIB_LIBPNG_COLOR_HPP

#include "xos/image/lib/libpng/Png.hpp"
#include "xos/base/Created.hpp"

#include "xos/image/lib/libpng/Struct.hpp"
#include "xos/image/lib/libpng/Png.hpp"
#include "xos/os/Logger.hpp"
#include "xos/base/Created.hpp"
#include "xos/base/Attached.hpp"

namespace xos {
namespace image {
namespace libpng {

typedef Attached
<png_colorp, int, 0, 
 ExportBase,  ColorImplement> ColorAttached;

typedef Created
<png_colorp, int, 0, 
 ColorAttached, ColorImplement> ColorExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Color
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Color
: virtual public ColorImplement, public ColorExtend {
public:
    typedef ColorImplement Implements;
    typedef ColorExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Color
    (png_colorp attached = 0, bool isCreated = false)
    : Extends(attached, isCreated) {
    }
    virtual ~Color() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace libpng 
} // namespace image 
} // namespace xos 

#endif // _XOS_IMAGE_LIB_LIBPNG_COLOR_HPP 
