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
///   File: ReadStruct.hpp
///
/// Author: $author$
///   Date: 8/15/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_IMAGE_LIB_LIBPNG_READSTRUCT_HPP
#define _XOS_IMAGE_LIB_LIBPNG_READSTRUCT_HPP

#include "xos/image/lib/libpng/Info.hpp"
#include "xos/image/lib/libpng/Struct.hpp"
#include "xos/os/FileOrBuffer.hpp"
#include "xos/base/Buffer.hpp"
#include "xos/base/Stream.hpp"

namespace xos {
namespace image {
namespace libpng {

typedef StructImplement ReadStructImplement;
typedef Struct ReadStructExtend;
///////////////////////////////////////////////////////////////////////
///  Class: ReadStruct
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS ReadStruct
: virtual public ReadStructImplement, public ReadStructExtend {
public:
    typedef ReadStructImplement Implements;
    typedef ReadStructExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    ReadStruct
    (ByteStream& in, png_structp attached = 0, bool isCreated = false)
    : Extends(attached, isCreated), m_in(in) {
    }
    ReadStruct
    (png_structp attached = 0, bool isCreated = false)
    : Extends(attached, isCreated), m_in(m_buffer) {
    }
    virtual ~ReadStruct() {
        if (!(Destroyed())) {
            XOS_LOG_ERROR("failed on Destroyed()");
            throw (Error(Error::Failed));
        }
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Create() {
        AttachedT detached;

        if ((Destroyed()))
        if (((detached = png_create_read_struct
            (PNG_LIBPNG_VER_STRING, ((png_voidp)this), ErrorFn, WarnFn)))) {
            png_set_read_fn(detached, ((png_voidp)this), ReadFn);
            AttachCreated(detached);
            return true;
        } else {
            XOS_LOG_ERROR("failed on png_create_read_struct()");
        }
        return false;
    }
    virtual bool Destroy() {
        AttachedT detached;
        if ((detached = Detach())) {
            png_destroy_read_struct
            (&detached, png_infopp_NULL, png_infopp_NULL);
            return true;
        }
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Read(Info& pngInfo, const char* fileName) {
        ssize_t count = 0;
        if ((Open(fileName))) {
            count = pngInfo.Read();
            Close();
        }
        return count;
    }
    virtual ssize_t Read
    (Info& pngInfo, const uint8_t* buffer, size_t size, ssize_t length=-1) {
        ssize_t count = 0;
        if ((AttachBuffer(buffer, size, length))) {
            count = pngInfo.Read();
            DetachBuffer();
        }
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Open(const char* fileName) {
        AttachedT attached;
        if ((attached = AttachedTo()))
        if ((m_buffer.Open(fileName)))
            return true;
        return false;
    }
    virtual bool Close() {
        AttachedT attached;
        if ((attached = AttachedTo()))
        if ((m_buffer.Close()))
            return true;
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const uint8_t* AttachBuffer
    (const uint8_t* buffer, size_t size, ssize_t length=-1) {
        buffer = m_buffer.Attach(buffer, size, length);
        return buffer;
    }
    virtual const uint8_t* DetachBuffer() {
        const uint8_t* buffer = m_buffer.Detach();
        return buffer;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void OnReadFn
    (png_structp structp, png_bytep bytep, png_size_t size) {
        size_t length;
        if (0 > (length = m_in.Read(bytep, (size_t)(size)))) {
            XOS_LOG_ERROR("failed to read " << size << " bytes");
            m_bytesRead = length;
        }
        else
        m_bytesRead += length;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    static void ReadFn
    (png_structp structp, png_bytep bytep, png_size_t size) {
        png_voidp error_ptr;
        ReadStruct* pngReadStruct;

        if ((pngReadStruct = (ReadStruct*)(error_ptr = png_get_io_ptr(structp))))
            pngReadStruct->OnReadFn(structp, bytep, size);
        else
        {   XOS_LOG_ERROR("failed with png_get_io_ptr(structp) == 0"); }
    }
protected:
    ByteFileOrBuffer m_buffer;
    ByteStream& m_in;
};

} // namespace libpng 
} // namespace image 
} // namespace xos 

#endif // _XOS_IMAGE_LIB_LIBPNG_READSTRUCT_HPP 
