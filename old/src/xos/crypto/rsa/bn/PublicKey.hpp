///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1995 Tatu Ylonen <ylo@cs.hut.fi>, Espoo, Finland
/// All rights reserved
/// Copyright (C) 1995-1997 Eric Young (eay@cryptsoft.com)
/// All rights reserved.
/// 
/// This package is an SSL implementation written
/// by Eric Young (eay@cryptsoft.com).
/// The implementation was written so as to conform with Netscapes SSL.
/// 
/// This library is free for commercial and non-commercial use as long as
/// the following conditions are aheared to.  The following conditions
/// apply to all code found in this distribution, be it the RC4, RSA,
/// lhash, DES, etc., code; not just the SSL code.  The SSL documentation
/// included with this distribution is covered by the same copyright terms
/// except that the holder is Tim Hudson (tjh@cryptsoft.com).
/// 
/// Copyright remains Eric Young's, and as such any Copyright notices in
/// the code are not to be removed.
/// If this package is used in a product, Eric Young should be given attribution
/// as the author of the parts of the library used.
/// This can be in the form of a textual message at program startup or
/// in documentation (online or textual) provided with the package.
/// 
/// Redistribution and use in source and binary forms, with or without
/// modification, are permitted provided that the following conditions
/// are met:
/// 1. Redistributions of source code must retain the copyright
///    notice, this list of conditions and the following disclaimer.
/// 2. Redistributions in binary form must reproduce the above copyright
///    notice, this list of conditions and the following disclaimer in the
///    documentation and/or other materials provided with the distribution.
/// 3. All advertising materials mentioning features or use of this software
///    must display the following acknowledgement:
///    "This product includes cryptographic software written by
///     Eric Young (eay@cryptsoft.com)"
///    The word 'cryptographic' can be left out if the rouines from the library
///    being used are not cryptographic related :-).
/// 4. If you include any Windows specific code (or a derivative thereof) from
///    the apps directory (application code) you must include an acknowledgement:
///    "This product includes software written by Tim Hudson (tjh@cryptsoft.com)"
/// 
/// THIS SOFTWARE IS PROVIDED BY ERIC YOUNG ``AS IS'' AND
/// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
/// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
/// ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
/// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
/// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
/// OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
/// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
/// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
/// OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
/// SUCH DAMAGE.
/// 
/// The licence and distribution terms for any publically available version or
/// derivative of this code cannot be changed.  i.e. this code cannot simply be
/// copied and put under another distribution licence
/// [including the GNU Public Licence.]
///
///   File: PublicKey.hpp
///
/// Author: $author$
///   Date: 1/14/2014
///
/// Tatu Ylonen's RSA public key implementation modified to be a C++
/// class that uses Eric Young's big number library instead of gmp used
/// in the original C version.
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_CRYPTO_RSA_BN_PUBLICKEY_HPP
#define _XOS_CRYPTO_RSA_BN_PUBLICKEY_HPP

#include "xos/crypto/rsa/PublicKey.hpp"
#include "xos/crypto/rsa/bn/Key.hpp"
#include "bn_msb.h"

namespace xos {
namespace crypto {
namespace rsa {
namespace bn {

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS PublicKeyImplement
: virtual public rsa::PublicKeyImplement,  virtual public bn::KeyImplement {
};
typedef Key PublicKeyExtend;
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS PublicKey
: virtual public PublicKeyImplement, public PublicKeyExtend {
friend class KeyGenerator;
public:
    typedef PublicKeyImplement Implements;
    typedef PublicKeyExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    PublicKey
    (const BYTE* modulus, unsigned modbytes,
     const BYTE* exponent, unsigned expbytes)
    : m_expbytes(0), m_modulus(0), m_exponent(0) {
        if (!(CreateMSB(modulus, modbytes, exponent, expbytes))) {
            Error error = Error::Failed;
            throw(error);
        }
    }
    PublicKey
    (const BIGNUM* modulus, unsigned modbytes,
     const BIGNUM* exponent, unsigned expbytes)
    : m_expbytes(0), m_modulus(0), m_exponent(0) {
        if (!(Create(modulus, modbytes, exponent, expbytes))) {
            Error error = Error::Failed;
            throw(error);
        }
    }
    PublicKey(const PublicKey& copy)
    : m_expbytes(0), m_modulus(0), m_exponent(0) {
        if (!(Create(copy.m_modulus, copy.m_modbytes, copy.m_exponent, copy.m_expbytes))) {
            Error error = Error::Failed;
            throw(error);
        }
    }
    PublicKey(): m_expbytes(0), m_modulus(0), m_exponent(0) {
    }
    virtual ~PublicKey() {
        if (!(Destroyed())) {
            Error error = Error::Failed;
            throw(error);
        }
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool CreateMSB
    (const BYTE* modulus, unsigned modbytes,
     const BYTE* exponent, unsigned expbytes) {
        if ((modulus) && (modbytes) && (exponent) && (expbytes)) {
            if ((Create(modbytes, expbytes))) {
                if ((SetMSB(modulus, modbytes, exponent, expbytes))) {
                    return true;
                }
                Destroy();
            }
        }
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool SetMSB
    (const BYTE* modulus, unsigned modbytes,
     const BYTE* exponent, unsigned expbytes) {
        if ((modulus) && (modbytes) && (exponent) && (expbytes)) {
            if ((m_modulus) && (m_exponent)) {
                BN_set_msb(m_modulus, modulus, m_modbytes = modbytes);
                BN_set_msb(m_exponent, exponent, m_expbytes = expbytes);
                return true;
            }
        }
        return false;
    }
    virtual int GetMSB
    (unsigned& explen, BYTE* modulus, unsigned modbytes,
     BYTE* exponent, unsigned expbytes) const {
        if ((modulus) && (modbytes) && (exponent) && (expbytes)) {
            if ((m_modulus) && (modbytes >= m_modbytes)
                && (m_exponent) && (expbytes >= m_expbytes)) {
                BN_get_msb(m_modulus, modulus, m_modbytes);
                BN_get_msb(m_exponent, exponent, m_expbytes);
                explen = m_expbytes;
                return m_modbytes;
            }
        }
        return -Error::Failed;
    }
    virtual int GetModulusMSB
    (BYTE* modulus, unsigned modbytes) const {
        if ((modulus) && (modbytes)) {
            if ((m_modulus) && (modbytes >= m_modbytes)) {
                BN_get_msb(m_modulus, modulus, m_modbytes);
                return m_modbytes;
            }
        }
        return -Error::Failed;
    }
    virtual int GetExponentMSB
    (BYTE* exponent, unsigned expbytes) const {
        if ((exponent) && (expbytes)) {
            if ((m_exponent) && (expbytes >= m_expbytes)) {
                BN_get_msb(m_exponent, exponent, m_expbytes);
                return m_expbytes;
            }
        }
        return -Error::Failed;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Create
    (const BIGNUM* modulus, unsigned modbytes,
     const BIGNUM* exponent, unsigned expbytes) {
        if ((modulus) && (modbytes) && (exponent) && (expbytes)) {
            if ((Create(modbytes, expbytes))) {
                if ((Set(modulus, exponent))) {
                    return true;
                }
                Destroy();
            }
        }
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Set
    (const BIGNUM* modulus, const BIGNUM* exponent) {
        if ((modulus) && (exponent)) {
            if ((m_modulus) && (m_exponent)) {
                BN_copy(m_modulus, (BIGNUM*)(modulus));
                BN_copy(m_exponent, (BIGNUM*)(exponent));
                return true;
            }
        }
        return false;
    }
    virtual int Get
    (unsigned& explen, BIGNUM* modulus, BIGNUM* exponent) const {
        if ((modulus) && (exponent)) {
            if ((m_modulus) && (m_exponent)) {
                BN_copy(modulus, m_modulus);
                BN_copy(exponent, m_exponent);
                explen = m_expbytes;
                return m_modbytes;
            }
        }
        return -Error::Failed;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Create(unsigned modbytes, unsigned expbytes) {
        if (!(Destroyed())) {
            return false;
        }
        if ((Extends::Create(modbytes))) {
            if ((m_modulus = BN_new())!=0) {
                if ((m_exponent = BN_new())!=0) {
                    m_modbytes = modbytes;
                    m_expbytes = expbytes;
                    return true;
                    BN_free(m_exponent);
                }
                BN_free(m_modulus);
            }
            Extends::Destroy();
        }
        return false;
    }
    virtual bool Destroy() {
        bool success = true;
        m_expbytes = 0;
        if (!(Extends::Destroy())) {
            success = false;
        }
        if (!(BN_free(m_exponent))) {
            success = false;
        }
        if (!(BN_free(m_modulus))) {
            success = false;
        }
        return success;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual unsigned SetExpBytes(unsigned to) {
        m_expbytes = to;
        return m_expbytes;
    }
    virtual unsigned ExpBytes() const {
        return m_expbytes;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t operator()
    (void* out, size_t outsize, const void* in, ssize_t inlen) {
        size_t inbytes;
        bool subp;
        if ((in) && (0 > inlen)) {
            inlen = (int)(strlen((const char*)in));
        }
        if ((inbytes = ((size_t)(inlen))) && (inbytes < m_modbytes)) {
            memset((char*)(in)+inbytes,0,m_modbytes-inbytes);
            inbytes = m_modbytes;
        }
        if ((m_modulus) && (m_modbytes)
            && (m_exponent) && (m_expbytes) && (m_temp) && (m_ctx)) {
            if ((in) && (m_modbytes == inbytes) && (out) && (outsize >= m_modbytes)) {

                BN_set_msb(m_temp, (const BYTE*)in, inbytes);

                BN_mod_exp(m_temp, m_temp, m_exponent, m_modulus, m_ctx);

                BN_get_msb(m_temp, (BYTE*)out, inbytes);
                return m_modbytes;
            }
        }
        return -Error::Failed;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    unsigned m_expbytes;
    BIGNUM *m_modulus;
    BIGNUM *m_exponent;
};

} // namespace bn 
} // namespace rsa 
} // namespace crypto 
} // namespace xos 

#endif // _XOS_CRYPTO_RSA_BN_PUBLICKEY_HPP 
