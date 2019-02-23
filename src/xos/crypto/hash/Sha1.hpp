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
///   File: Sha1.hpp
///
/// Author: $author$
///   Date: 1/29/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_CRYPTO_HASH_SHA1_HPP
#define _XOS_CRYPTO_HASH_SHA1_HPP

#include "xos/crypto/hash/Base.hpp"

namespace xos {
namespace crypto {
namespace hash {

typedef hash::BaseImplement Sha1Implement;
typedef hash::Base Sha1Extend;
///////////////////////////////////////////////////////////////////////
///  Class: Sha1
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Sha1
: virtual public Sha1Implement, public Sha1Extend {
public:
    typedef Sha1Implement Implements;
    typedef Sha1Extend Extends;
    enum {
        HASHSIZE  = 20,
        BLOCKSIZE = 64,
        KEYMIN    = 1,
        KEYMAX    = BLOCKSIZE,
        KEYSIZE   = BLOCKSIZE
    };
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Sha1(void* out, size_t outsize, const void* in, ssize_t inlen = -1)
    : Extends(HASHSIZE, BLOCKSIZE, KEYMIN, KEYMAX, m_key, m_mac, m_hash) {
        this->operator~();
        if (0 > (this->operator()(out, outsize, in, inlen))) {
            Error error = Error::Failed;
            throw (error);
        }
    }
    Sha1(const Sha1& copy)
    : Extends(HASHSIZE, BLOCKSIZE, KEYMIN, KEYMAX, m_key, m_mac, m_hash) {
        this->operator=(copy);
    }
    Sha1(): Extends(HASHSIZE, BLOCKSIZE, KEYMIN, KEYMAX, m_key, m_mac, m_hash) {
        this->operator~();
    }
    virtual ~Sha1() {
        this->operator~();
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual Sha1& operator = (const Sha1& copy) {
        m_A = copy.m_A; m_B = copy.m_B;
        m_C = copy.m_C; m_D = copy.m_D; m_E = copy.m_E;
        m_L = copy.m_L; m_H = copy.m_H;
        memcpy(m_in, copy.m_in, sizeof(m_in));
        memcpy(m_key, copy.m_key, sizeof(m_key));
        memcpy(m_mac, copy.m_mac, sizeof(m_mac));
        memcpy(m_hash, copy.m_hash, sizeof(m_hash));
        return *this;
    }
    virtual Sha1& operator ~ () {
        m_A = 0; m_B = 0;
        m_C = 0; m_D = 0; m_E = 0;
        m_L = 0; m_H = 0;
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
    uint32_t m_A, m_B, m_C, m_D, m_E, m_L, m_H;
    uint8_t m_hash[HASHSIZE];
    uint8_t m_in[BLOCKSIZE];
    uint8_t m_key[BLOCKSIZE];
    uint8_t m_mac[HASHSIZE];
};

} // namespace hash
} // namespace crypto 
} // namespace xos 

#endif // _XOS_CRYPTO_HASH_SHA1_HPP 
