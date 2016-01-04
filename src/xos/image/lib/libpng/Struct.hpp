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
///   File: Struct.hpp
///
/// Author: $author$
///   Date: 8/15/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_IMAGE_LIB_LIBPNG_STRUCT_HPP
#define _XOS_IMAGE_LIB_LIBPNG_STRUCT_HPP

#include "xos/image/lib/libpng/Png.hpp"
#include "xos/os/Logger.hpp"
#include "xos/base/Created.hpp"
#include "xos/base/Attached.hpp"

namespace xos {
namespace image {
namespace libpng {

typedef Attached
<png_structp, int, 0, 
 ExportBase,  StructImplement> StructAttached;

typedef Created
<png_structp, int, 0, 
 StructAttached, StructImplement> StructExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Struct
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Struct
: virtual public StructImplement, public StructExtend {
public:
    typedef StructImplement Implements;
    typedef StructExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Struct
    (png_structp attached = 0, bool isCreated = false)
    : Extends(attached, isCreated),
      m_bytesRead(0), 
      m_bytesWritten(0) {
    }
    virtual ~Struct() {
        if (!(Destroyed())) {
            XOS_LOG_ERROR("failed on Destroyed()"); 
            throw (Error(Error::Failed));
        }
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Create() { return false; }
    virtual bool Destroy() { return false; }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void OnError(png_structp structp, png_const_charp charp) {
    }
    virtual void OnWarn(png_structp structp, png_const_charp charp) {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    static void ErrorFn(png_structp structp, png_const_charp charp) {
        png_voidp error_ptr;
        Struct* pngStruct;
        if ((pngStruct = (Struct*)(error_ptr = png_get_error_ptr(structp))))
            pngStruct->OnError(structp, charp);
    }
    static void WarnFn(png_structp structp, png_const_charp charp) {
        png_voidp error_ptr;
        Struct* pngStruct;
        if ((pngStruct = (Struct*)(error_ptr = png_get_error_ptr(structp))))
            pngStruct->OnWarn(structp, charp);
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual png_uint_32 SetBytesRead(png_uint_32 bytesRead) { 
        png_uint_32 bytes = m_bytesRead;
        m_bytesRead = bytesRead; 
        return bytes; 
    }
    virtual png_uint_32 SetBytesWritten(png_uint_32 bytesWritten) { 
        png_uint_32 bytes = m_bytesWritten;
        m_bytesWritten = bytesWritten; 
        return bytes; 
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual png_uint_32 bytesRead() const { 
        return m_bytesRead; 
    }
    virtual png_uint_32 bytesWritten() const { 
        return m_bytesWritten; 
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    png_uint_32 m_bytesRead, m_bytesWritten;
};

} // namespace libpng 
} // namespace image 
} // namespace xos 

#endif // _XOS_IMAGE_LIB_LIBPNG_STRUCT_HPP 
