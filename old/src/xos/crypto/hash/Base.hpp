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
///   Date: 1/25/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_CRYPTO_HASH_BASE_HPP
#define _XOS_CRYPTO_HASH_BASE_HPP

#include "xos/crypto/hash/Interface.hpp"
#include "xos/crypto/hash/Mac.hpp"
#include "xos/base/Types.hpp"

namespace xos {
namespace crypto {
namespace hash {

typedef hash::Interface BaseImplement;
typedef crypto::Base BaseExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Base
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Base: virtual public BaseImplement, public BaseExtend {
public:
    typedef BaseImplement Implements;
    typedef BaseExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Base
    (ssize_t hashsize,
     ssize_t blocksize,
     ssize_t keymin,
     ssize_t keymax,
     uint8_t* keybuff,
     uint8_t* macbuff,
     uint8_t* hashbuff)
     : m_hashsize(hashsize),
       m_blocksize(blocksize),
       m_keymin(keymin),
       m_keymax(keymax),
       m_keylen(0),
       m_keysize(0),
       m_keybuff(keybuff),
       m_macbuff(macbuff),
       m_hashbuff(hashbuff) {
    }
    virtual ~Base() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Initialize(const void* key = 0, ssize_t keylen = -1) {
        const uint8_t* keybytes;
        ssize_t i;

        if ((keybytes = ((const uint8_t*)key))) {
            if (0 > keylen)
                keylen = Bytes::Count(keybytes);

            if (keylen < m_keymin)
                return -Error::InvalidParameterSize;

            if (keylen > m_keymax)
                return -Error::InvalidParameterSize;

            m_keylen = keylen;
            m_keysize = m_keymax;
            memcpy(m_keybuff, keybytes, keylen);
            memset(m_keybuff+keylen, 0, m_keymax-keylen);

            //
            // HMAC
            //
            for (i=0; i<m_keymax; i++)
                m_keybuff[i] ^= mac::OPAD;
        }
        else m_keysize = m_keylen = keylen = 0;

        Initial();

        if (m_keysize) {
            //
            // HMAC
            //
            for (i=0; i<m_keysize; i++)
                m_keybuff[i] = (m_keybuff[i]^mac::OPAD)^mac::IPAD;

            Update(m_keybuff, m_keysize);

            //
            // HMAC
            //
            for (i=0; i<m_keysize; i++)
                m_keybuff[i] = (m_keybuff[i]^mac::IPAD)^mac::OPAD;
        }
        return keylen;
    }
    virtual ssize_t Finalize(void* out, size_t outsize) {
        ssize_t outlen = (ssize_t)(outsize);

        if (outlen > m_hashsize)
            outlen = m_hashsize;

        Final();

        if (m_keysize) {
            //
            // HMAC
            //
            memcpy(m_macbuff, m_hashbuff, m_hashsize);
            Initial();
            Update(m_keybuff, m_keysize);
            Update(m_macbuff, m_hashsize);
            Final();
        }

        memcpy(out, m_hashbuff, outlen);
        return outlen;
    }
    virtual ssize_t Hash(const void* in, ssize_t inlen = -1) {
        const uint8_t* inbytes;
        if ((inbytes = ((const uint8_t*)in))) {
            if (0 > inlen)
                inlen = Bytes::Count(inbytes);
            Update(inbytes, inlen);
        } else {
            inlen = 0;
        }
        return inlen;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t HashSize() const {
        return m_hashsize;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t operator()
    (void* out, size_t outsize, const void* in, ssize_t inlen = -1) {
        ssize_t count = 0;
        if ((out) && (outsize)) {
            if (0 <= (count = Initialize())) {
                if ((in) && (inlen)) {
                    if (0 > (count = Hash(in, inlen)))
                        return count;
                }
                count = Finalize(out, outsize);
            }
        }
        return count;
    }
protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void Initial() = 0;
    virtual void Final() = 0;
    virtual void Update(const uint8_t* in, unsigned inlen) = 0;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    ssize_t m_hashsize;
    ssize_t m_blocksize;
    ssize_t m_keymin;
    ssize_t m_keymax;
    ssize_t m_keysize;
    ssize_t m_keylen;
    uint8_t* m_keybuff;
    uint8_t* m_macbuff;
    uint8_t* m_hashbuff;
};

} // namespace hash 
} // namespace crypto 
} // namespace xos 

#endif // _XOS_CRYPTO_HASH_BASE_HPP 
