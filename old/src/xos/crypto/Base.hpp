///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2014 $organization$
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
///   File: Base.hpp
///
/// Author: $author$
///   Date: 1/24/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_CRYPTO_BASE_HPP
#define _XOS_CRYPTO_BASE_HPP

#include "xos/base/Base.hpp"

namespace xos {
namespace crypto {

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
enum {
    ERROR_KEY_SIZE,
    ERROR_KEY_SIZE_OVER,
    ERROR_KEY_SIZE_UNDER,

    ERROR_IV_SIZE,
    ERROR_IV_SIZE_OVER,
    ERROR_IV_SIZE_UNDER,

    ERROR_BLOCK_SIZE,
    ERROR_BLOCK_SIZE_OVER,
    ERROR_BLOCK_SIZE_UNDER,

    ERROR_IN_SIZE,
    ERROR_IN_SIZE_OVER,
    ERROR_IN_SIZE_UNDER,

    ERROR_OUT_SIZE,
    ERROR_OUT_SIZE_OVER,
    ERROR_OUT_SIZE_UNDER
};

typedef InterfaceBase BaseImplement;
typedef ExportBase BaseExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Base
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Base
: virtual public BaseImplement, public BaseExtend {
public:
    typedef BaseImplement Implements;
    typedef BaseExtend Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    inline UINT64 MSBToU64(const BYTE* bytes) {
        UINT64 value = (((((((((((((((UINT64)bytes[0])<<8) | bytes[1])<<8) | bytes[2])<<8) | bytes[3])<<8) | bytes[4])<<8) | bytes[5])<<8) | bytes[6])<<8) | bytes[7];
        return value;
    }
    inline BYTE* U64ToMSB(BYTE* bytes, UINT64 value) {
        *(bytes+=7)=(BYTE)(value & 0xFF);
        *(--bytes)=(BYTE)((value>>=8) & 0xFF);
        *(--bytes)=(BYTE)((value>>=8) & 0xFF);
        *(--bytes)=(BYTE)((value>>=8) & 0xFF);
        *(--bytes)=(BYTE)((value>>=8) & 0xFF);
        *(--bytes)=(BYTE)((value>>=8) & 0xFF);
        *(--bytes)=(BYTE)((value>>=8) & 0xFF);
        *(--bytes)=(BYTE)((value>>=8) & 0xFF);
        return bytes;
    }
    ///////////////////////////////////////////////////////////////////////
    inline UINT64 LSBToU64(const BYTE* bytes) {
        UINT64 value = (((((((((((((((UINT64)bytes[7])<<8) | bytes[6])<<8) | bytes[5])<<8) | bytes[4])<<8) | bytes[3])<<8) | bytes[2])<<8) | bytes[1])<<8) | bytes[0];
        return value;
    }
    inline BYTE* U64ToLSB(BYTE* bytes, UINT64 value) {
        *(bytes)=(BYTE)(value & 0xFF);
        *(++bytes)=(BYTE)((value>>=8) & 0xFF);
        *(++bytes)=(BYTE)((value>>=8) & 0xFF);
        *(++bytes)=(BYTE)((value>>=8) & 0xFF);
        *(++bytes)=(BYTE)((value>>=8) & 0xFF);
        *(++bytes)=(BYTE)((value>>=8) & 0xFF);
        *(++bytes)=(BYTE)((value>>=8) & 0xFF);
        *(++bytes)=(BYTE)((value>>=8) & 0xFF);
        return bytes;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    inline UINT32 MSBToU32(const BYTE* bytes) {
        UINT32 value = (((((((UINT32)bytes[0])<<8) | bytes[1])<<8) | bytes[2])<<8) | bytes[3];
        return value;
    }
    inline BYTE* U32ToMSB(BYTE* bytes, UINT32 value) {
        *(bytes+=3)=(BYTE)(value & 0xFF);
        *(--bytes)=(BYTE)((value>>=8) & 0xFF);
        *(--bytes)=(BYTE)((value>>=8) & 0xFF);
        *(--bytes)=(BYTE)((value>>=8) & 0xFF);
        return bytes;
    }
    ///////////////////////////////////////////////////////////////////////
    inline UINT32 LSBToU32(const BYTE* bytes) {
        UINT32 value = (((((((UINT32)bytes[3])<<8) | bytes[2])<<8) | bytes[1])<<8) | bytes[0];
        return value;
    }
    inline BYTE* U32ToLSB(BYTE* bytes, UINT32 value) {
        *(bytes)=(BYTE)(value & 0xFF);
        *(++bytes)=(BYTE)((value>>=8) & 0xFF);
        *(++bytes)=(BYTE)((value>>=8) & 0xFF);
        *(++bytes)=(BYTE)((value>>=8) & 0xFF);
        return bytes;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    inline BYTE *Copy8(BYTE *to, const BYTE *from) {
        *(to++) = *(from++);
        *(to++) = *(from++);
        *(to++) = *(from++);
        *(to++) = *(from++);
        *(to++) = *(from++);
        *(to++) = *(from++);
        *(to++) = *(from++);
        *(to++) = *(from++);
        return to;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    inline BYTE* CopyRepeat
    (BYTE* to, int tosize, const BYTE* from, int fromsize) {
        for (int i=0; i<tosize; i+=fromsize)
        for (int j=0,k=i; (k<tosize) && (j<fromsize); k++,j++)
            to[k] = from[j];
        return to;
    }
};

} // namespace crypto 
} // namespace xos 

#endif // _XOS_CRYPTO_BASE_HPP 
