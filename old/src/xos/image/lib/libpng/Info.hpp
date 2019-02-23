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
///   File: Info.hpp
///
/// Author: $author$
///   Date: 8/17/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_IMAGE_LIB_LIBPNG_INFO_HPP
#define _XOS_IMAGE_LIB_LIBPNG_INFO_HPP

#include "xos/image/lib/libpng/Palette.hpp"
#include "xos/image/lib/libpng/Struct.hpp"
#include "xos/image/lib/libpng/Png.hpp"
#include "xos/os/Logger.hpp"
#include "xos/base/Created.hpp"
#include "xos/base/Attached.hpp"

namespace xos {
namespace image {
namespace libpng {

typedef Attached
<png_infop, int, 0, 
 ExportBase,  InfoImplement> InfoAttached;

typedef Created
<png_infop, int, 0, 
 InfoAttached, InfoImplement> InfoExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Info
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Info
: virtual public InfoImplement, public InfoExtend {
public:
    typedef InfoImplement Implements;
    typedef InfoExtend Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Info
    (Struct& pngStruct, png_infop attached = 0, bool isCreated = false)
    : Extends(attached, isCreated), 
      m_pngStruct(pngStruct),
      m_colorPalette(pngStruct, *this),
      m_imageRow(0),
      m_imageRows(0),
      m_imageRowsPerRead(1) {
    }
    virtual ~Info() {
        if (!(Destroyed())) {
            XOS_LOG_ERROR("failed on Destroyed()"); 
            throw (Error(Error::Failed));
        }
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Create() {
        png_structp structAttached;
        AttachedT detached;

        if ((Destroyed()))
        if ((structAttached = m_pngStruct.AttachedTo()))
        if ((detached = png_create_info_struct(structAttached))) {
            AttachCreated(detached);
            return true;
        } else {
            XOS_LOG_ERROR("failed on png_create_info_struct()");
        }
        return false;
    }
    virtual bool Destroy() {
        bool success = FreedImageRows();
        png_structp structAttached;
        AttachedT detached;

        if ((structAttached = m_pngStruct.AttachedTo()))
        if ((detached = Detach())) {
            png_destroy_info_struct(structAttached, &detached);
        } else {
            success = false;
        }
        return success;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual png_int_32 Read() {
        png_int_32 failed = 0;
        png_int_32 count = failed;
        png_structp structAttached;
        AttachedT attached;
        png_int_32 readCount;
        png_uint_32 oldBytesRead;
        png_uint_32 rows, rowBytes;
        int colorType, bitDepth, colorChannels, paletteColors;

        if (0 >= (count = ReadInfo
            (rows, rowBytes, colorType, bitDepth, colorChannels, paletteColors)))
            return failed;

        // Allocate the memory to hold the image rows. 
        //
        if ((m_imageRow = AllocateImageRows(rowBytes, rows)))
            m_imageRows = rows;
        else
        return failed;

        if (!(attached = AttachedTo()) || !(structAttached = m_pngStruct.AttachedTo()))
            return failed;

        oldBytesRead = m_pngStruct.SetBytesRead(0);

        // Read the image all at once 
        //
        png_read_image(structAttached, m_imageRow);

        if (0 < (readCount = m_pngStruct.SetBytesRead(oldBytesRead)))
            count += readCount;
        else
        return failed;

        if (0 < (readCount = ReadEnd()))
            count += readCount;
        else
        return failed;

        return count;
    }
    virtual png_int_32 ReadBegin(png_int_32 rowsPerRead = 0) {
        png_int_32 failed = 0;
        png_int_32 count = failed;
        png_uint_32 rows, rowBytes;
        int colorType, bitDepth, colorChannels, paletteColors;

        if (0 >= (count = ReadInfo
            (rows, rowBytes, colorType, bitDepth, colorChannels, paletteColors)))
            return failed;

        if (0 > (rowsPerRead))
            rowsPerRead = rows;
        else
        if (1 > (rowsPerRead))
        if (0 >= (rowsPerRead = imageRowsPerRead()))
            return failed;
            
        // Allocate the memory to hold the image rows. 
        //
        if ((m_imageRow = AllocateImageRows(rowBytes, rowsPerRead)))
            m_imageRows = rowsPerRead;
        else
        return failed;

        return count;
    }
    virtual png_int_32 ReadEnd() {
        png_int_32 failed = 0;
        png_int_32 count = failed;
        png_structp structAttached;
        AttachedT attached;
        png_uint_32 oldBytesRead;

        if (!(attached = AttachedTo()) || !(structAttached = m_pngStruct.AttachedTo()))
            return failed;

        oldBytesRead = m_pngStruct.SetBytesRead(0);

        // read rest of file, and get additional chunks in info_ptr
        //
        png_read_end(structAttached, attached);

        if (0 >= (count = m_pngStruct.SetBytesRead(oldBytesRead)))
            return failed;

        return count;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual png_int_32 ReadInfo
    (png_uint_32& rows, png_uint_32& rowBytes,
     int& colorType, int& bitDepth, int& colorChannels, int& paletteColors) {
        png_int_32 failed = 0;
        png_int_32 count = failed;
        png_structp structAttached;
        AttachedT attached;
        png_uint_32 oldBytesRead;

        if (!(attached = AttachedTo()) || !(structAttached = m_pngStruct.AttachedTo()))
            return failed;

        oldBytesRead = m_pngStruct.SetBytesRead(0);

        // The call to png_read_info() gives all of the information from the
        // PNG file before the first IDAT (image data chunk).
        //
        png_read_info(structAttached, attached);

        if (0 >= (count = m_pngStruct.SetBytesRead(oldBytesRead)))
            return failed;

        if ((0 >= (rows = this->imageHeight())))
            return failed;

        if ((0 >= (rowBytes = this->imageRowBytes())))
            return failed;

        if (0 >= (bitDepth = this->colorBitDepth()))
            return failed;

        if (0 > (colorType = this->colorType()))
            return failed;

        if (0 > (colorChannels = this->colorChannels()))
            return failed;

        if (PNG_COLOR_MASK_PALETTE != (PNG_COLOR_MASK_PALETTE & colorType))
            paletteColors = 0;
        else
        if (0 > (paletteColors = m_colorPalette.Get()))
            return failed;

        return count;
    }
    virtual png_int_32 ReadRows() {
        png_int_32 failed = 0;
        png_int_32 count = failed;
        png_structp structAttached;
        AttachedT attached;
        png_uint_32 oldBytesRead;

        if (!(attached = AttachedTo()) || !(structAttached = m_pngStruct.AttachedTo()))
            return failed;

        if ((!m_imageRows) || (!m_imageRow))
            return failed;

        oldBytesRead = m_pngStruct.SetBytesRead(0);

        // Read m_imageRows rows at a time 
        //        
        png_read_rows(structAttached, m_imageRow, png_bytepp_NULL, m_imageRows);

        if (0 >= (count = m_pngStruct.SetBytesRead(oldBytesRead)))
            return failed;

        return count;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    bool FreedImageRows() {
        bool success = false;
        if ((m_imageRow) && (m_imageRows)) {
            success = FreeImageRows(m_imageRow, m_imageRows);
            m_imageRow = 0;
            m_imageRows = 0;
        }
        return success;
    }
    bool FreeImageRows(png_bytep* imageRow, png_uint_32 imageRows) {
        bool success = false;
        if ((success = ((imageRow) && (imageRows)))) {
            png_bytep* pImageRow = imageRow;
            png_uint_32 row;

            for (row = imageRows; row; --row, pImageRow++)
                FreeImageRow(*pImageRow);

            delete[] imageRow;
        }
        return success;
    }
    virtual png_bytep* AllocateImageRows(png_uint_32 rowBytes, png_uint_32 rows) {
        png_bytep* imageRow = 0;
        png_structp structAttached;
        AttachedT attached;

        if ((rowBytes) && (rows) && (attached = AttachedTo()) 
            && (structAttached = m_pngStruct.AttachedTo())) {
            png_uint_32 row;

            if ((imageRow = new png_bytep[rows])) {
                for (row = 0; row < rows; row++) {
                    if ((imageRow[row] = AllocateImageRow(rowBytes)))
                        continue;
                    for (row++; row > 0; )
                        FreeImageRow(imageRow[--row]);
                    break;
                }
                if (row < rows) {
                    delete[] imageRow;
                    imageRow = 0;
                }
            } else {
                XOS_LOG_ERROR("failed on new png_bytep[" << rows<< "]");
            }
        }
        return imageRow;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual png_bytep AllocateImageRow(png_uint_32 rowBytes) {
        png_bytep imageRow = 0;
        png_structp structAttached;
        AttachedT attached;

        if ((attached = AttachedTo()) 
            && (structAttached = m_pngStruct.AttachedTo())) {

            if (!(imageRow = (png_bytep)
                (png_malloc(structAttached, rowBytes))))
            {   XOS_LOG_ERROR("failed on png_malloc()"); }
        }
        return imageRow;
    }
    bool FreeImageRow(png_bytep imageRow) {
        bool success = false;
        png_structp structAttached;
        AttachedT attached;

        if ((success = ((imageRow) && (attached = AttachedTo()) 
            && (structAttached = m_pngStruct.AttachedTo())))) {
            png_free(structAttached, imageRow);
        }
        return success;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int colorBitDepth() const {
        int value = 0;
        png_structp structAttached;
        AttachedT attached;
        if ((attached = AttachedTo()) 
            && (structAttached = m_pngStruct.AttachedTo())) {
            if (0 > (value = png_get_bit_depth(structAttached, attached)))
            {   XOS_LOG_ERROR("failed " << value << "on png_get_bit_depth()"); }
        }
        return value;
    }
    virtual int colorChannels() const {
        int value = 0;
        png_structp structAttached;
        AttachedT attached;
        if ((attached = AttachedTo()) 
            && (structAttached = m_pngStruct.AttachedTo())) {
            if (0 > (value = png_get_channels(structAttached, attached)))
            {   XOS_LOG_ERROR("failed " << value << "on png_get_channels()"); }
        }
        return value;
    }
    virtual int colorType() const {
        int value = 0;
        png_structp structAttached;
        AttachedT attached;
        if ((attached = AttachedTo()) 
            && (structAttached = m_pngStruct.AttachedTo())) {
            if (0 > (value = png_get_color_type(structAttached, attached)))
            {   XOS_LOG_ERROR("failed " << value << "on png_get_color_type()"); }
        }
        return value;
    }
    virtual int filterType() const {
        int value = 0;
        png_structp structAttached;
        AttachedT attached;
        if ((attached = AttachedTo()) 
            && (structAttached = m_pngStruct.AttachedTo())) {
            if (0 > (value = png_get_filter_type(structAttached, attached)))
            {   XOS_LOG_ERROR("failed " << value << "on png_get_filter_type()"); }
        }
        return value;
    }
    virtual int interlaceType() const {
        int value = 0;
        png_structp structAttached;
        AttachedT attached;
        if ((attached = AttachedTo()) 
            && (structAttached = m_pngStruct.AttachedTo())) {
            if (0 > (value = png_get_interlace_type(structAttached, attached)))
            {   XOS_LOG_ERROR("failed " << value << "on png_get_interlace_type()"); }
        }
        return value;
    }
    virtual int compressionType() const {
        int value = 0;
        png_structp structAttached;
        AttachedT attached;
        if ((attached = AttachedTo()) 
            && (structAttached = m_pngStruct.AttachedTo())) {
            if (0 > (value = png_get_compression_type(structAttached, attached)))
            {   XOS_LOG_ERROR("failed " << value << "on png_get_compression_type()"); }
        }
        return value;
    }
    virtual png_uint_32 imageWidth() const {
        png_uint_32 value = 0;
        png_structp structAttached;
        AttachedT attached;
        if ((attached = AttachedTo()) 
            && (structAttached = m_pngStruct.AttachedTo())) {
            if (1 > (value = png_get_image_width(structAttached, attached)))
            {   XOS_LOG_ERROR("failed " << value << "on png_get_image_width()"); }
        }
        return value;
    }
    virtual png_uint_32 imageHeight() const {
        png_uint_32 value = 0;
        png_structp structAttached;
        AttachedT attached;
        if ((attached = AttachedTo()) 
            && (structAttached = m_pngStruct.AttachedTo())) {
            if (1 > (value = png_get_image_height(structAttached, attached)))
            {   XOS_LOG_ERROR("failed " << value << "on png_get_image_height()"); }
        }
        return value;
    }
    virtual png_uint_32 imageRowBytes() const {
        png_uint_32 value = 0;
        png_structp structAttached;
        AttachedT attached;
        if ((attached = AttachedTo()) 
            && (structAttached = m_pngStruct.AttachedTo())) {
            if (1 > (value = png_get_rowbytes(structAttached, attached)))
            {   XOS_LOG_ERROR("failed " << value << "on png_get_rowbytes()"); }
        }
        return value;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual png_bytep* imageRow
    (png_uint_32& imageRows, png_uint_32& imageRowBytes) const {
        imageRows = this->imageRows();
        imageRowBytes = this->imageRowBytes();
        return m_imageRow;
    }
    virtual png_uint_32 imageRows() const {
        return m_imageRows;
    }
    virtual png_uint_32 imageRowsPerRead() const {
        return m_imageRowsPerRead;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    Struct& m_pngStruct;
    Palette m_colorPalette;
    png_bytep* m_imageRow;
    png_uint_32 m_imageRows;
    png_uint_32 m_imageRowsPerRead;
};

} // namespace libpng 
} // namespace image 
} // namespace xos 

#endif // _XOS_IMAGE_LIB_LIBPNG_INFO_HPP 
