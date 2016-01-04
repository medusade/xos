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
///   File: Aes.hpp
///
/// Author: $author$
///   Date: 5/21/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_CRYPTO_CIPHER_AES_HPP
#define _XOS_CRYPTO_CIPHER_AES_HPP

#include "xos/crypto/cipher/Interface.hpp"

namespace xos {
namespace crypto {
namespace cipher {

typedef Interface AesImplement;
typedef Base AesExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Aes
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Aes: virtual public AesImplement, public AesExtend {
public:
    typedef AesImplement Implements;
    typedef AesExtend Extends;

    enum {
        BLOCKSIZE = 16,

        KEYMIN    = 16,
        KEYMAX    = 32,
        KEYINC    = 8,
        KEYSIZE   = 16,

        IVMIN     = 16,
        IVMAX     = 16,
        IVINC     = 16,
        IVSIZE    = 16
    };

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Aes() {
    }
    virtual ~Aes() {
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
    typedef uint8_t tKey[KEYMAX];

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t InitEncryptKeySchedule
    (const uint8_t* key, unsigned keysize);

    virtual ssize_t InitDecryptKeySchedule
    (const uint8_t* key, unsigned keysize);

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void EncryptBlock
    (tBlock output, const tBlock input);

    virtual void DecryptBlock
    (tBlock output, const tBlock input);

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void EncodeBlock
    (tBlock output, const tBlock input);

    virtual void DecodeBlock
    (tBlock output, const tBlock input);

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    unsigned m_keysize;
    tKey m_key;
    tBlock m_iv;
    tBlock m_padd;

    unsigned nr;
    uint32_t* rk;
    uint32_t buf[68];
};

} // namespace cipher 
} // namespace crypto 
} // namespace xos 

#endif // _XOS_CRYPTO_CIPHER_AES_HPP 
