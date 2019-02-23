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
///   File: PublicKey.hpp
///
/// Author: $author$
///   Date: 5/18/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_CRYPTO_RSA_PUBLICKEY_HPP
#define _XOS_CRYPTO_RSA_PUBLICKEY_HPP

#include "xos/crypto/rsa/Key.hpp"

namespace xos {
namespace crypto {
namespace rsa {

///////////////////////////////////////////////////////////////////////
///  Class: PublicKeyImplement
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS PublicKeyImplement: virtual public KeyImplement {
public:
    typedef KeyImplement Implements;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool CreateMSB
    (const BYTE* modulus, unsigned modbytes,
     const BYTE* exponent, unsigned expbytes) {
        return false;
    }
    virtual bool Create(unsigned modbytes, unsigned expbytes) {
        return false;
    }
    virtual bool Destroy() {
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool SetMSB
    (const BYTE* modulus, unsigned modbytes,
     const BYTE* exponent, unsigned expbytes) {
        return false;
    }
    virtual int GetMSB
    (unsigned& explen,
     BYTE* modulus, unsigned modbytes,
     BYTE* exponent, unsigned expbytes) const {
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual unsigned SetExpBytes(unsigned to) {
        return 0;
    }
    virtual unsigned ExpBytes() const {
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t operator()
    (void* out, size_t outsize, const void* in, ssize_t inlen) {
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace rsa 
} // namespace crypto 
} // namespace xos 

#endif // _XOS_CRYPTO_RSA_PUBLICKEY_HPP 
