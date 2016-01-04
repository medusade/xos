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
///   File: Hash.hpp
///
/// Author: $author$
///   Date: 7/27/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_CRYPTO_HASH_MXDE_HASH_HPP
#define _XOS_CRYPTO_HASH_MXDE_HASH_HPP

#include "xos/crypto/hash/Interface.hpp"
#include "ccryptohash.hxx"

namespace xos {
namespace crypto {
namespace hash {
namespace mxde {

///////////////////////////////////////////////////////////////////////
///  Class: HashT
///////////////////////////////////////////////////////////////////////
template <class TImplement, class TExtend, class THash>
class _EXPORT_CLASS HashT
: virtual public TImplement, public TExtend {
public:
    typedef TImplement Implements;
    typedef TExtend Extends;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: HashT
    ///////////////////////////////////////////////////////////////////////
    HashT() {
    }
    virtual ~HashT() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Initialize(const void* key = 0, ssize_t keylen = -1) {
        if (0 <= (keylen = (ssize_t)(m_hash.Initialize((uint8_t*)(key), (TLENGTH)(keylen)))))
            return keylen;
        return -Error::Failed;
    }
    virtual ssize_t Finalize(void* out, size_t outsize) {
        ssize_t outlen;
        if (0 <= (outlen = (ssize_t)(m_hash.Finalize((uint8_t*)(out), (TLENGTH)(outsize)))))
            return outlen;
        return -Error::Failed;
    }
    virtual ssize_t Hash(const void* in, ssize_t inlen = -1) {
        if (0 <= (inlen = (ssize_t)(m_hash.Hash((uint8_t*)(in), (TLENGTH)(inlen)))))
            return inlen;
        return -Error::Failed;
    }
    virtual ssize_t HashSize() const {
        ssize_t hashlen;
        if (0 <= (hashlen = (ssize_t)(m_hash.HashSize())))
            return hashlen;
        return -Error::Failed;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    THash m_hash;
};

} // namespace mxde 
} // namespace hash 
} // namespace crypto 
} // namespace xos 

#endif // _XOS_CRYPTO_HASH_MXDE_HASH_HPP 
