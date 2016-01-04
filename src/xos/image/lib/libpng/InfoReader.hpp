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
///   File: InfoReader.hpp
///
/// Author: $author$
///   Date: 8/18/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_IMAGE_LIB_LIBPNG_INFOREADER_HPP
#define _XOS_IMAGE_LIB_LIBPNG_INFOREADER_HPP

#include "xos/image/lib/libpng/ReadStruct.hpp"
#include "xos/image/lib/libpng/Info.hpp"

namespace xos {
namespace image {
namespace libpng {

typedef InfoImplement InfoReaderImplement;
typedef Info InfoReaderExtend;
///////////////////////////////////////////////////////////////////////
///  Class: InfoReader
///
/// Author: $author$
///   Date: 8/18/2013
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS InfoReader
: virtual public InfoReaderImplement, public InfoReaderExtend {
public:
    typedef InfoReaderImplement Implements;
    typedef InfoReaderExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    InfoReader
    (ReadStruct& pngReadStruct,
     png_infop attached=0, bool isCreated=false)
    : Extends(pngReadStruct, attached, isCreated),
      m_pngReadStruct(pngReadStruct) {
    }
    virtual ~InfoReader() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Create() {
        if ((m_pngReadStruct.Create())) {
            if ((Extends::Create()))
                return true;
            m_pngReadStruct.Destroy();
        }
        return false;
    }
    virtual bool Destroy() {
        bool success = Extends::Destroy();
        if (!(m_pngReadStruct.Destroy()))
            success = false;
        return success;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Open(const char* fileName) {
        if ((m_pngReadStruct.Open(fileName)))
            return true;
        return false;
    }
    virtual bool Close() {
        if ((m_pngReadStruct.Close()))
            return true;
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const uint8_t* AttachBuffer
    (const uint8_t* buffer, size_t size, ssize_t length=-1) {
        buffer = m_pngReadStruct.AttachBuffer(buffer, size, length);
        return buffer;
    }
    virtual const uint8_t* DetachBuffer() {
        const uint8_t* buffer = m_pngReadStruct.DetachBuffer();
        return buffer;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    ReadStruct& m_pngReadStruct;
};

} // namespace libpng 
} // namespace image 
} // namespace xos 

#endif // _XOS_IMAGE_LIB_LIBPNG_INFOREADER_HPP 
