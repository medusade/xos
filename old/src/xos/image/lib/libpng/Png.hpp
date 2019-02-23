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
///   File: Png.hpp
///
/// Author: $author$
///   Date: 8/15/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_IMAGE_LIB_LIBPNG_PNG_HPP
#define _XOS_IMAGE_LIB_LIBPNG_PNG_HPP

#include "xos/base/Created.hpp"
#include "xos/base/Attached.hpp"
#include "xos/base/Base.hpp"
#include <png.h>

namespace xos {
namespace image {
namespace libpng {

//
// Struct
//
typedef AttachedInterface
<png_structp, int, 0, InterfaceBase> StructInterface;

typedef AttachedImplement
<png_structp, int, 0, StructInterface> StructImplement;

typedef Attached
<png_structp, int, 0, 
 ExportBase,  StructImplement> StructAttached;

//
// Info
//
typedef AttachedInterface
<png_infop, int, 0, InterfaceBase> InfoInterface;

typedef AttachedImplement
<png_infop, int, 0, InfoInterface> InfoImplement;

typedef Attached
<png_infop, int, 0, 
 ExportBase,  InfoImplement> InfoAttached;

//
// Color
//
typedef AttachedInterface
<png_colorp, int, 0, InterfaceBase> ColorInterface;

typedef AttachedImplement
<png_colorp, int, 0, ColorInterface> ColorImplement;

typedef Attached
<png_colorp, int, 0, 
 ExportBase,  ColorImplement> ColorAttached;

} // namespace libpng 
} // namespace image 
} // namespace xos 

#endif // _XOS_IMAGE_LIB_LIBPNG_PNG_HPP 
