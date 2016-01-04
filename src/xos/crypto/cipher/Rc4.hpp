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
///   File: Rc4.hpp
///
/// Author: $author$
///   Date: 5/20/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_CRYPTO_CIPHER_RC4_HPP
#define _XOS_CRYPTO_CIPHER_RC4_HPP

#include "xos/crypto/cipher/Interface.hpp"

namespace xos {
namespace crypto {
namespace cipher {

typedef Interface Rc4Implement;
typedef Base Rc4Extend;
///////////////////////////////////////////////////////////////////////
///  Class: Rc4
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Rc4: virtual public Rc4Implement, public Rc4Extend {
public:
    typedef Rc4Implement Implements;
    typedef Rc4Extend Extends;

    enum {
        BLOCKSIZE = 1,
        KEYMIN    = 8,
        KEYMAX    = 256,
        KEYSIZE   = 128,
        IVMIN     = 0,
        IVMAX     = 0,
        IVSIZE    = 0
    };

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Rc4() {
    }
    virtual ~Rc4() {
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
    virtual ssize_t operator()
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
    virtual ssize_t BlockSize() const {
        return BLOCKSIZE;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    uint8_t m_x, m_y, m_data[256];
};

} // namespace cipher 
} // namespace crypto 
} // namespace xos 

#endif // _XOS_CRYPTO_CIPHER_RC4_HPP 
