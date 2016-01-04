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
///   File: Sha256.hpp
///
/// Author: $author$
///   Date: 1/29/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_CRYPTO_HASH_SHA256_HPP
#define _XOS_CRYPTO_HASH_SHA256_HPP

#include "xos/crypto/hash/Base.hpp"

namespace xos {
namespace crypto {
namespace hash {

typedef hash::BaseImplement Sha256Implement;
typedef hash::Base Sha256Extend;
///////////////////////////////////////////////////////////////////////
///  Class: Sha256
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Sha256
: virtual public Sha256Implement, public Sha256Extend {
public:
    typedef Sha256Implement Implements;
    typedef Sha256Extend Extends;
    enum {
        WORDSIZE    = 4,
        LENGTHSIZE  = 8
    };
    enum {
        HASHSIZE  = 32,
        KONSTSIZE = 64,
        BLOCKSIZE = 64,
        KEYMIN    = 1,
        KEYMAX    = BLOCKSIZE,
        KEYSIZE   = BLOCKSIZE
    };
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Sha256(void* out, size_t outsize, const void* in, ssize_t inlen = -1)
    : Extends(HASHSIZE, BLOCKSIZE, KEYMIN, KEYMAX, m_key, m_mac, m_hash) {
        this->operator~();
        if (0 > (this->operator()(out, outsize, in, inlen))) {
            Error error = Error::Failed;
            throw (error);
        }
    }
    Sha256(const Sha256& copy)
    : Extends(HASHSIZE, BLOCKSIZE, KEYMIN, KEYMAX, m_key, m_mac, m_hash) {
        this->operator=(copy);
    }
    Sha256(): Extends(HASHSIZE, BLOCKSIZE, KEYMIN, KEYMAX, m_key, m_mac, m_hash) {
        this->operator~();
    }
    virtual ~Sha256() {
        this->operator~();
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual Sha256& operator = (const Sha256& copy) {
        m_A = copy.m_A; m_B = copy.m_B;
        m_C = copy.m_C; m_D = copy.m_D;
        m_E = copy.m_E; m_F = copy.m_F;
        m_G = copy.m_G; m_H = copy.m_H;
        m_l = copy.m_l; m_h = copy.m_h;
        memcpy(m_in, copy.m_in, sizeof(m_in));
        memcpy(m_key, copy.m_key, sizeof(m_key));
        memcpy(m_mac, copy.m_mac, sizeof(m_mac));
        memcpy(m_hash, copy.m_hash, sizeof(m_hash));
        return *this;
    }
    virtual Sha256& operator ~ () {
        m_A = 0; m_B = 0;
        m_C = 0; m_D = 0;
        m_E = 0; m_F = 0;
        m_G = 0; m_H = 0;
        m_l = 0; m_h = 0;
        memset(m_in, 0, sizeof(m_in));
        memset(m_key, 0, sizeof(m_key));
        memset(m_mac, 0, sizeof(m_mac));
        memset(m_hash, 0, sizeof(m_hash));
        return *this;
    }
protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void Initial();
    virtual void Final();
    virtual void Transform();
    virtual void Update(const uint8_t* in, unsigned inlen);
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    static uint32_t m_K[KONSTSIZE];
    uint32_t m_A, m_B, m_C, m_D, m_E, m_F, m_G, m_H, m_l, m_h;
    uint8_t m_hash[HASHSIZE];
    uint8_t m_mac[HASHSIZE];
    uint8_t m_in[BLOCKSIZE];
    uint8_t m_key[BLOCKSIZE];
};

} // namespace hash
} // namespace crypto 
} // namespace xos 

#endif // _XOS_CRYPTO_HASH_SHA256_HPP 
