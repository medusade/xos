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
///   File: Palette.hpp
///
/// Author: $author$
///   Date: 8/17/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_IMAGE_LIB_LIBPNG_PALETTE_HPP
#define _XOS_IMAGE_LIB_LIBPNG_PALETTE_HPP

#include "xos/image/lib/libpng/Color.hpp"
#include "xos/image/lib/libpng/Struct.hpp"
#include "xos/image/lib/libpng/Png.hpp"
#include "xos/os/Logger.hpp"
#include "xos/base/Created.hpp"
#include "xos/base/Attached.hpp"

namespace xos {
namespace image {
namespace libpng {

typedef ColorImplement PaletteImplement;
typedef Color PaletteExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Palette
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Palette
: virtual public PaletteImplement, public PaletteExtend {
public:
    typedef PaletteImplement Implements;
    typedef PaletteExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Palette
    (Struct& pngStruct, InfoInterface& pngInfo,
     png_colorp attached = 0, bool isCreated = false)
    : Extends(attached, isCreated), 
      m_pngStruct(pngStruct),
      m_pngInfo(pngInfo),
      m_colors(0) {
    }
    virtual ~Palette() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int Get() {
        png_uint_32 result;
        png_structp structAttached;
        png_infop infoAttached;
        png_colorp detached;
        int colors;

        if ((structAttached = m_pngStruct.AttachedTo())
            && (infoAttached = m_pngInfo.AttachedTo())) {

            if ((result = png_get_PLTE
                (structAttached, infoAttached, &detached, &colors))) {
                 Attach(detached, colors);
                 return colors;
            } else {
                XOS_LOG_ERROR("failed " << result << " on png_get_PLTE()");
            }
        }
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual AttachedT Attach(AttachedT detached, int colors) {
        m_colors = colors;
        return Extends::Attach(detached);
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    Struct& m_pngStruct;
    InfoInterface& m_pngInfo;
    int m_colors;
};

} // namespace libpng 
} // namespace image 
} // namespace xos 

#endif // _XOS_IMAGE_LIB_LIBPNG_PALETTE_HPP 
