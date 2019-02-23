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
///   File: Des.hpp
///
/// Author: $author$
///   Date: 5/20/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_CRYPTO_CIPHER_DES_HPP
#define _XOS_CRYPTO_CIPHER_DES_HPP

#include "xos/crypto/cipher/Interface.hpp"

namespace xos {
namespace crypto {
namespace cipher {

typedef Interface DesImplement;
typedef Base DesExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Des
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Des: virtual public DesImplement, public DesExtend {
public:
    typedef DesImplement Implements;
    typedef DesExtend Extends;

    enum {
        BLOCKSIZE = 8,
        KEYMIN    = 8,
        KEYMAX    = 8,
        KEYSIZE   = 8,
        IVMIN     = 8,
        IVMAX     = 8,
        IVSIZE    = 8
    };

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Des() {
    }
    virtual ~Des() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Initialize
    (const void* key, ssize_t keylen = -1,
     const void* iv = 0, ssize_t ivlen = -1,
     const void* padd = 0, ssize_t paddlen = -1);

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Encrypt
    (void* out, size_t outsize, const void* in, ssize_t inlen = -1);

    virtual ssize_t Decrypt
    (void* out, size_t outsize, const void* in, ssize_t inlen = -1);

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t KeySizeMin() const {
        return KEYMIN;
    }
    virtual ssize_t KeySizeMax() const {
        return KEYMAX;
    }
    virtual ssize_t KeySize() const {
        return KEYSIZE;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t IVSizeMin() const {
        return IVMIN;
    }
    virtual ssize_t IVSizeMax() const {
        return IVMAX;
    }
    virtual ssize_t IVSize() const {
        return IVSIZE;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t BlockSize() const {
        return BLOCKSIZE;
    }

protected:
    typedef uint8_t tBlock[BLOCKSIZE];
    typedef uint8_t tKey[BLOCKSIZE*3];
    typedef uint32_t tSchedule[32];

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    void InitSchedule
    (tSchedule schedule, const tBlock key);

    void Encode
    (uint32_t data[2], tSchedule schedule);

    void Decode
    (uint32_t data[2], tSchedule schedule);

    virtual void EncryptBlock
    (tBlock out, const tBlock in);

    virtual void DecryptBlock
    (tBlock out, const tBlock in);

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    static const uint32_t m_setkey[8][64];
    static const uint32_t m_encrypt[8][64];

    tKey m_key;
    tBlock m_iv;
    tBlock m_padd;
    tSchedule m_schedule[3];
};

///////////////////////////////////////////////////////////////////////
///  Class: Des3
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Des3: virtual public DesImplement, public Des {
public:
    typedef DesImplement Implements;
    typedef Des Extends;

    enum {
        KEYMIN    = Extends::KEYMIN*3,
        KEYMAX    = Extends::KEYMAX*3,
        KEYSIZE   = Extends::KEYSIZE*3
    };

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Des3() {
    }
    virtual ~Des3() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Initialize
    (const void* key, ssize_t keylen = -1,
     const void* iv = 0, ssize_t ivlen = -1,
     const void* padd = 0, ssize_t paddlen = -1);

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void EncryptBlock
    (tBlock out, const tBlock in);

    virtual void DecryptBlock
    (tBlock out, const tBlock in);

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace cipher
} // namespace crypto 
} // namespace xos 

#endif // _XOS_CRYPTO_CIPHER_DES_HPP 
