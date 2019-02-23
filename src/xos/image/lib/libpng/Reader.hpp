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
///   File: Reader.hpp
///
/// Author: $author$
///   Date: 8/18/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_IMAGE_LIB_LIBPNG_READER_HPP
#define _XOS_IMAGE_LIB_LIBPNG_READER_HPP

#include "xos/image/lib/libpng/ReaderEvents.hpp"
#include "xos/image/lib/libpng/InfoReader.hpp"
#include "xos/image/lib/libpng/ReadStruct.hpp"
#include "xos/image/lib/libpng/Struct.hpp"

namespace xos {
namespace image {
namespace libpng {

typedef ReaderEventsImplement ReaderImplement;
typedef ReaderEvents ReaderExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Reader
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Reader
: virtual public ReaderImplement, public ReaderExtend {
public:
    typedef ReaderImplement Implements;
    typedef ReaderExtend Extends;
    typedef Reader Derives;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Reader(ReaderEvents* delegated=0)
    : Extends(delegated),
      m_pngInfoReader(m_pngReadStruct),
      m_colBytes(0),
      m_onPNGCol(0),
      m_bytesRead(0) {
    }
    virtual ~Reader() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool On8BitPalette8BitPNGCol
    (BYTE* colByte, TSIZE colBytes, TSIZE col, 
     TSIZE row, TSIZE height, TSIZE width, 
     TSIZE bitDepth, TSIZE colorChannels,
     UINT colorType, UINT filterType, 
     UINT interlaceType, UINT compressionType) {
         return true;
    }
    virtual bool On8BitPalette16BitPNGCol
    (BYTE* colByte, TSIZE colBytes, TSIZE col, 
     TSIZE row, TSIZE height, TSIZE width, 
     TSIZE bitDepth, TSIZE colorChannels,
     UINT colorType, UINT filterType, 
     UINT interlaceType, UINT compressionType) {
         return true;
    }
    virtual bool On8BitRGBAPNGCol
    (BYTE* colByte, TSIZE colBytes, TSIZE col, 
     TSIZE row, TSIZE height, TSIZE width, 
     TSIZE bitDepth, TSIZE colorChannels,
     UINT colorType, UINT filterType, 
     UINT interlaceType, UINT compressionType) {
        Pixel pixel(colByte[0], colByte[1], colByte[2], colByte[3]);
        OnPNGPixel
        (pixel, colByte, colBytes, col, row, 
         height, width, bitDepth, colorChannels,
         colorType, filterType, interlaceType, compressionType);
        return true;
    }
    virtual bool On8BitRGBPNGCol
    (BYTE* colByte, TSIZE colBytes, TSIZE col, 
     TSIZE row, TSIZE height, TSIZE width, 
     TSIZE bitDepth, TSIZE colorChannels,
     UINT colorType, UINT filterType, 
     UINT interlaceType, UINT compressionType) {
        Pixel pixel(colByte[0], colByte[1], colByte[2]);
        OnPNGPixel
        (pixel, colByte, colBytes, col, row, 
         height, width, bitDepth, colorChannels,
         colorType, filterType, interlaceType, compressionType);
        return true;
    }
    virtual bool On16BitRGBAPNGCol
    (BYTE* colByte, TSIZE colBytes, TSIZE col, 
     TSIZE row, TSIZE height, TSIZE width, 
     TSIZE bitDepth, TSIZE colorChannels,
     UINT colorType, UINT filterType, 
     UINT interlaceType, UINT compressionType) {
        WORD* colWord = (WORD*)(colByte);
        Pixel16 pixel(colWord[0], colWord[1], colWord[2], colWord[3]);
        OnPNGPixel16
        (pixel, colByte, colBytes, col, row, 
         height, width, bitDepth, colorChannels,
         colorType, filterType, interlaceType, compressionType);
        return true;
    }
    virtual bool On16BitRGBPNGCol
    (BYTE* colByte, TSIZE colBytes, TSIZE col, 
     TSIZE row, TSIZE height, TSIZE width, 
     TSIZE bitDepth, TSIZE colorChannels,
     UINT colorType, UINT filterType, 
     UINT interlaceType, UINT compressionType) {
        WORD* colWord = (WORD*)(colByte);
        Pixel16 pixel(colWord[0], colWord[1], colWord[2]);
        OnPNGPixel16
        (pixel, colByte, colBytes, col, row, 
         height, width, bitDepth, colorChannels,
         colorType, filterType, interlaceType, compressionType);
        return true;
    }
    virtual bool OnPNGCol
    (BYTE* colByte, TSIZE colBytes, TSIZE col, 
     TSIZE row, TSIZE height, TSIZE width, 
     TSIZE bitDepth, TSIZE colorChannels,
     UINT colorType, UINT filterType, 
     UINT interlaceType, UINT compressionType) {
        if ((m_onPNGCol))
            (this->*m_onPNGCol)
            (colByte, colBytes, col, row, 
             height, width, bitDepth, colorChannels,
             colorType, filterType, interlaceType, compressionType);
        return true;
    }
    virtual bool OnPNGRow
    (BYTE* rowByte, TSIZE rowBytes, 
     TSIZE row, TSIZE height, TSIZE width, 
     TSIZE bitDepth, TSIZE colorChannels,
     UINT colorType, UINT filterType, 
     UINT interlaceType, UINT compressionType) {
        BYTE* colByte;
        TSIZE col;        
        for (colByte = rowByte, col = 0; 
             col < width; col++, colByte += m_colBytes)
        {
            if ((OnBeginPNGCol
                (colByte, m_colBytes, col, row, 
                 height, width, bitDepth, colorChannels,
                 colorType, filterType, interlaceType, compressionType)))
            if ((OnPNGCol
                (colByte, m_colBytes, col, row, 
                 height, width, bitDepth, colorChannels,
                 colorType, filterType, interlaceType, compressionType)))
            if ((OnEndPNGCol
                (colByte, m_colBytes, col, row, 
                 height, width, bitDepth, colorChannels,
                 colorType, filterType, interlaceType, compressionType)))
                continue;
            break;
        }
        return true;
    }
    virtual bool OnPNGColorType
    (TSIZE height, TSIZE width, 
     TSIZE bitDepth, TSIZE colorChannels,
     UINT colorType, UINT filterType, 
     UINT interlaceType, UINT compressionType) {
        switch(colorType) {

        case PNG_COLOR_TYPE_RGB:
            switch(bitDepth) {
            case 8:
                m_onPNGCol = &Derives::On8BitRGBPNGCol;
                break;
            case 16:
                m_onPNGCol = &Derives::On16BitRGBPNGCol;
                break;
            }
            break;
            
        case PNG_COLOR_TYPE_RGB_ALPHA:
            switch(bitDepth) {
            case 8:
                m_onPNGCol = &Derives::On8BitRGBAPNGCol;
                break;
            case 16:
                m_onPNGCol = &Derives::On16BitRGBAPNGCol;
                break;
            }
            break;
            
        case PNG_COLOR_TYPE_PALETTE:
            switch(bitDepth) {
            case 8:
                m_onPNGCol = &Derives::On8BitPalette8BitPNGCol;
                break;
            case 16:
                m_onPNGCol = &Derives::On8BitPalette16BitPNGCol;
                break;
            }
            break;
        }
        return true;
    }
    virtual bool OnPNGImage
    (TSIZE height, TSIZE width, 
     TSIZE bitDepth, TSIZE colorChannels,
     UINT colorType, UINT filterType, 
     UINT interlaceType, UINT compressionType) {
        png_bytep* imageRow;
        png_uint_32 imageRows;
        png_uint_32 rowBytes;
        png_bytep rowByte;
        png_uint_32 rowIndex;
        png_uint_32 row;
        png_int_32 count;
        
        OnPNGColorType
        (height, width, bitDepth, colorChannels,
         colorType, filterType, interlaceType, compressionType);

        m_colBytes = ((bitDepth+7)/8)*colorChannels;
                
        if ((imageRow = m_pngInfoReader.imageRow(imageRows, rowBytes)))
        if ((0 < (imageRows)) && (0 < (rowBytes)))
        for (row = 0; row < (png_uint_32)(height); row += imageRows) {

            if (0 > (count = m_pngInfoReader.ReadRows()))
                break;
                
            m_bytesRead += count;

            for (rowByte = imageRow[rowIndex = 0]; 
                 rowIndex < imageRows; rowByte = imageRow[++rowIndex]) {

                if ((OnBeginPNGRow
                    (rowByte, rowBytes, row+rowIndex,
                     height, width, bitDepth, colorChannels,
                     colorType, filterType, interlaceType, compressionType)))
                if ((OnPNGRow
                    (rowByte, rowBytes, row+rowIndex,
                     height, width, bitDepth, colorChannels,
                     colorType, filterType, interlaceType, compressionType)))
                if ((OnEndPNGRow
                    (rowByte, rowBytes, row+rowIndex,
                     height, width, bitDepth, colorChannels,
                     colorType, filterType, interlaceType, compressionType)))
                    continue;
                    
                return false;
            }
        }
        return true;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Read(const char* fileName) {
        ssize_t count = 0;
        if ((m_pngInfoReader.Create())) {
            if ((m_pngInfoReader.Open(fileName))) {
                count = Read(m_pngInfoReader);
                m_pngInfoReader.Close();
            }
            m_pngInfoReader.Destroy();
        }
        return count;
    }
    virtual ssize_t Read(const uint8_t* imageData, size_t imageSize) {
        ssize_t count = 0;
        if ((m_pngInfoReader.Create())) {
            if ((m_pngInfoReader.AttachBuffer(imageData, imageSize, imageSize))) {
                count = Read(m_pngInfoReader);
                m_pngInfoReader.DetachBuffer();
            }
            m_pngInfoReader.Destroy();
        }
        return count;
    }
    virtual ssize_t Read(InfoReader& pngInfoReader) {
        ssize_t count = 0;
        png_int_32 value;
        size_t height, width, bitDepth, colorChannels;
        unsigned colorType, filterType, interlaceType, compressionType;

        if (0 < (value = (m_bytesRead = pngInfoReader.ReadBegin(1))))
        if (0 <= (value = pngInfoReader.imageHeight()))
        if (0 <= (height = value))
        if (0 <= (value = pngInfoReader.imageWidth()))
        if (0 <= (width = value))
        if (0 <= (value = pngInfoReader.colorBitDepth()))
        if (0 <= (bitDepth = value))
        if (0 <= (value = pngInfoReader.colorChannels()))
        if (0 <= (colorChannels = value))
        if (0 <= (value = pngInfoReader.colorType()))
        if (0 <= (colorType = value))
        if (0 <= (value = pngInfoReader.filterType()))
        if (0 <= (filterType = value))
        if (0 <= (value = pngInfoReader.interlaceType()))
        if (0 <= (interlaceType = value))
        if (0 <= (value = pngInfoReader.compressionType()))
        if (0 <= (compressionType = value))
        if ((OnBeginPNGImage
            (height, width, bitDepth, colorChannels,
             colorType, filterType, interlaceType, compressionType)))
        if ((OnPNGImage
            (height, width, bitDepth, colorChannels,
             colorType, filterType, interlaceType, compressionType)))
        if (0 <= (value = pngInfoReader.ReadEnd()))
        if ((OnEndPNGImage
            (height, width, bitDepth, colorChannels,
             colorType, filterType, interlaceType, compressionType))) {
        }
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    typedef bool (Derives::*MOnPNGCol)
    (BYTE* colByte, TSIZE colBytes, TSIZE col, 
     TSIZE row, TSIZE height, TSIZE width, 
     TSIZE bitDepth, TSIZE colorChannels,
     UINT colorType, UINT filterType, 
     UINT interlaceType, UINT compressionType);

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    ReadStruct m_pngReadStruct;
    InfoReader m_pngInfoReader;
    TSIZE m_colBytes;
    MOnPNGCol m_onPNGCol;
    png_int_32 m_bytesRead;
};

} // namespace libpng 
} // namespace image 
} // namespace xos 

#endif // _XOS_IMAGE_LIB_LIBPNG_READER_HPP 
