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
///   File: Md5.hpp
///
/// Author: $author$
///   Date: 1/25/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_CRYPTO_HASH_MD5_HPP
#define _XOS_CRYPTO_HASH_MD5_HPP

#include "xos/crypto/hash/Base.hpp"

namespace xos {
namespace crypto {
namespace hash {

typedef hash::BaseImplement Md5Implement;
typedef hash::Base Md5Extend;
///////////////////////////////////////////////////////////////////////
///  Class: Md5
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Md5
: virtual public Md5Implement, public Md5Extend {
public:
    typedef Md5Implement Implements;
    typedef Md5Extend Extends;
    enum {
        HASHSIZE  = 16,
        BLOCKSIZE = 64,
        KEYMIN    = 1,
        KEYMAX    = BLOCKSIZE,
        KEYSIZE   = BLOCKSIZE
    };
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Md5(void* out, size_t outsize, const void* in, ssize_t inlen = -1)
    : Extends(HASHSIZE, BLOCKSIZE, KEYMIN, KEYMAX, m_key, m_mac, m_hash) {
        this->operator~();
        if (0 > (this->operator()(out, outsize, in, inlen))) {
            Error error = Error::Failed;
            throw (error);
        }
    }
    Md5(const Md5& copy)
    : Extends(HASHSIZE, BLOCKSIZE, KEYMIN, KEYMAX, m_key, m_mac, m_hash) {
        this->operator=(copy);
    }
    Md5(): Extends(HASHSIZE, BLOCKSIZE, KEYMIN, KEYMAX, m_key, m_mac, m_hash) {
        this->operator~();
    }
    virtual ~Md5() {
        this->operator~();
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual Md5& operator = (const Md5& copy) {
        m_A = copy.m_A; m_B = copy.m_B;
        m_C = copy.m_C; m_D = copy.m_D;
        m_L = copy.m_L; m_H = copy.m_H;
        memcpy(m_in, copy.m_in, sizeof(m_in));
        memcpy(m_key, copy.m_key, sizeof(m_key));
        memcpy(m_mac, copy.m_mac, sizeof(m_mac));
        memcpy(m_hash, copy.m_hash, sizeof(m_hash));
        return *this;
    }
    virtual Md5& operator ~ () {
        m_A = 0; m_B = 0;
        m_C = 0; m_D = 0;
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
    uint32_t m_A, m_B, m_C, m_D, m_L, m_H;
    uint8_t m_hash[HASHSIZE];
    uint8_t m_in[BLOCKSIZE];
    uint8_t m_key[BLOCKSIZE];
    uint8_t m_mac[HASHSIZE];
};

} // namespace hash 
} // namespace crypto 
} // namespace xos 

#endif // _XOS_CRYPTO_HASH_MD5_HPP 
