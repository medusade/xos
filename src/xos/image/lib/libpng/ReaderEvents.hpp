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
///   File: ReaderEvents.hpp
///
/// Author: $author$
///   Date: 8/18/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_IMAGE_LIB_LIBPNG_READEREVENTS_HPP
#define _XOS_IMAGE_LIB_LIBPNG_READEREVENTS_HPP

#include "xos/image/rgba/Pixel.hpp"
#include "xos/image/Pixel.hpp"
#include "xos/base/Base.hpp"

namespace xos {
namespace image {
namespace libpng {

typedef InterfaceBase ReaderEventsImplement;
typedef ExportBase ReaderEventsExtend;
///////////////////////////////////////////////////////////////////////
///  Class: ReaderEvents
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS ReaderEvents
: virtual public ReaderEventsImplement, public ReaderEventsExtend {
public:
    typedef ReaderEventsImplement Implements;
    typedef ReaderEventsExtend Extends;
    typedef rgba::Pixel8 Pixel;
    typedef rgba::Pixel16 Pixel16;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    ReaderEvents(ReaderEvents* delegated=0)
    : m_delegated(delegated) {
    }
    virtual ~ReaderEvents() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool OnPNGPixel
    (Pixel& pixel,
     BYTE* colByte, TSIZE colBytes, TSIZE col, 
     TSIZE row, TSIZE height, TSIZE width, 
     TSIZE bitDepth, TSIZE colorChannels,
     UINT colorType, UINT filterType, 
     UINT interlaceType, UINT compressionType) {
         ReaderEvents* delegated;
         if ((delegated = DelegatedEvents())) {
             return delegated->OnPNGPixel
            (pixel, colByte, colBytes, col, row, 
             height, width, bitDepth, colorChannels,
             colorType, filterType, interlaceType, compressionType);
         }
         return true;
    }
    virtual bool OnPNGPixel16
    (Pixel16& pixel,
     BYTE* colByte, TSIZE colBytes, TSIZE col, 
     TSIZE row, TSIZE height, TSIZE width, 
     TSIZE bitDepth, TSIZE colorChannels,
     UINT colorType, UINT filterType, 
     UINT interlaceType, UINT compressionType) {
         ReaderEvents* delegated;
         if ((delegated = DelegatedEvents())) {
             return delegated->OnPNGPixel16
            (pixel, colByte, colBytes, col, row, 
             height, width, bitDepth, colorChannels,
             colorType, filterType, interlaceType, compressionType);
         }
         return true;
    }
    virtual bool OnBeginPNGCol
    (BYTE* colByte, TSIZE colBytes, TSIZE col, 
     TSIZE row, TSIZE height, TSIZE width, 
     TSIZE bitDepth, TSIZE colorChannels,
     UINT colorType, UINT filterType, 
     UINT interlaceType, UINT compressionType) {
         ReaderEvents* delegated;
         if ((delegated = DelegatedEvents())) {
             return delegated->OnBeginPNGCol
            (colByte, colBytes, col, row, 
             height, width, bitDepth, colorChannels,
             colorType, filterType, interlaceType, compressionType);
         }
         return true;
    }
    virtual bool OnEndPNGCol
    (BYTE* colByte, TSIZE colBytes, TSIZE col, 
     TSIZE row, TSIZE height, TSIZE width, 
     TSIZE bitDepth, TSIZE colorChannels,
     UINT colorType, UINT filterType, 
     UINT interlaceType, UINT compressionType) {
         ReaderEvents* delegated;
         if ((delegated = DelegatedEvents())) {
             return delegated->OnEndPNGCol
            (colByte, colBytes, col, row, 
             height, width, bitDepth, colorChannels,
             colorType, filterType, interlaceType, compressionType);
         }
    }
    virtual bool OnPNGCol
    (BYTE* colByte, TSIZE colBytes, TSIZE col, 
     TSIZE row, TSIZE height, TSIZE width, 
     TSIZE bitDepth, TSIZE colorChannels,
     UINT colorType, UINT filterType, 
     UINT interlaceType, UINT compressionType) {
         ReaderEvents* delegated;
         if ((delegated = DelegatedEvents())) {
             return delegated->OnPNGCol
            (colByte, colBytes, col, row, 
             height, width, bitDepth, colorChannels,
             colorType, filterType, interlaceType, compressionType);
         }
         return true;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool OnBeginPNGRow
    (BYTE* rowByte, TSIZE rowBytes, 
     TSIZE row, TSIZE height, TSIZE width, 
     TSIZE bitDepth, TSIZE colorChannels,
     UINT colorType, UINT filterType, 
     UINT interlaceType, UINT compressionType) {
         ReaderEvents* delegated;
         if ((delegated = DelegatedEvents())) {
             return delegated->OnBeginPNGRow
            (rowByte, rowBytes, row, 
             height, width, bitDepth, colorChannels,
             colorType, filterType, interlaceType, compressionType);
         }
         return true;
    }
    virtual bool OnEndPNGRow
    (BYTE* rowByte, TSIZE rowBytes, 
     TSIZE row, TSIZE height, TSIZE width, 
     TSIZE bitDepth, TSIZE colorChannels,
     UINT colorType, UINT filterType, 
     UINT interlaceType, UINT compressionType) {
         ReaderEvents* delegated;
         if ((delegated = DelegatedEvents())) {
             return delegated->OnEndPNGRow
            (rowByte, rowBytes, row, 
             height, width, bitDepth, colorChannels,
             colorType, filterType, interlaceType, compressionType);
         }
         return true;
    }
    virtual bool OnPNGRow
    (BYTE* rowByte, TSIZE rowBytes, 
     TSIZE row, TSIZE height, TSIZE width, 
     TSIZE bitDepth, TSIZE colorChannels,
     UINT colorType, UINT filterType, 
     UINT interlaceType, UINT compressionType) {
         ReaderEvents* delegated;
         if ((delegated = DelegatedEvents())) {
             return delegated->OnPNGRow
            (rowByte, rowBytes, row, 
             height, width, bitDepth, colorChannels,
             colorType, filterType, interlaceType, compressionType);
         }
         return true;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool OnBeginPNGImage
    (TSIZE height, TSIZE width, 
     TSIZE bitDepth, TSIZE colorChannels,
     UINT colorType, UINT filterType, 
     UINT interlaceType, UINT compressionType) {
         ReaderEvents* delegated;
         if ((delegated = DelegatedEvents())) {
             return delegated->OnBeginPNGImage
            (height, width, bitDepth, colorChannels,
             colorType, filterType, interlaceType, compressionType);
         }
         return true;
    }
    virtual bool OnEndPNGImage
    (TSIZE height, TSIZE width, 
     TSIZE bitDepth, TSIZE colorChannels,
     UINT colorType, UINT filterType, 
     UINT interlaceType, UINT compressionType) {
         ReaderEvents* delegated;
         if ((delegated = DelegatedEvents())) {
             return delegated->OnEndPNGImage
            (height, width, bitDepth, colorChannels,
             colorType, filterType, interlaceType, compressionType);
         }
         return true;
    }
    virtual bool OnPNGImage
    (TSIZE height, TSIZE width, 
     TSIZE bitDepth, TSIZE colorChannels,
     UINT colorType, UINT filterType, 
     UINT interlaceType, UINT compressionType) {
         ReaderEvents* delegated;
         if ((delegated = DelegatedEvents())) {
             return delegated->OnPNGImage
            (height, width, bitDepth, colorChannels,
             colorType, filterType, interlaceType, compressionType);
         }
         return true;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ReaderEvents* DelegateEvents(ReaderEvents* delegatedTo) {
        return m_delegated;
    }
    virtual ReaderEvents* DelegatedEvents() const {
        return m_delegated;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    ReaderEvents* m_delegated;
};

} // namespace libpng 
} // namespace image 
} // namespace xos 

#endif // _XOS_IMAGE_LIB_LIBPNG_READEREVENTS_HPP 
