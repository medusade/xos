///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1995 Tatu Ylonen <ylo@cs.hut.fi>, Espoo, Finland
/// All rights reserved
/// Copyright (C) 1991, 1993, 1994, 1995, 1996 Free Software Foundation, Inc.
/// 
/// This file is part of the GNU MP Library.
/// 
/// The GNU MP Library is free software; you can redistribute it and/or modify
/// it under the terms of the GNU Library General Public License as published by
/// the Free Software Foundation; either version 2 of the License, or (at your
/// option) any later version.
/// 
/// The GNU MP Library is distributed in the hope that it will be useful, but
/// WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
/// or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
/// License for more details.
/// 
/// You should have received a copy of the GNU Library General Public License
/// along with the GNU MP Library; see the file COPYING.LIB.  If not, write to
/// the Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
/// MA 02111-1307, USA.
///
///   File: PublicKey.hpp
///
/// Author: $author$
///   Date: 1/15/2014
///
/// Tatu Ylonen's RSA public key implementation modified to be a C++
/// class that uses the gmp used in the original C version.
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_CRYPTO_RSA_MP_PUBLICKEY_HPP
#define _XOS_CRYPTO_RSA_MP_PUBLICKEY_HPP

#include "xos/crypto/rsa/PublicKey.hpp"
#include "xos/crypto/rsa/mp/Key.hpp"
#include "mpz_msb.h"

namespace xos {
namespace crypto {
namespace rsa {
namespace mp {

class _EXPORT_CLASS KeyGenerator;
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS PublicKeyImplement
: virtual public rsa::PublicKeyImplement,  virtual public mp::KeyImplement {
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
    : m_expbytes(0) {
        if (!(CreateMSB(modulus, modbytes, exponent, expbytes))) {
            Error error = Error::Failed;
            throw(error);
        }
    }
    PublicKey
    (const MP_INT& modulus, unsigned modbytes,
     const MP_INT& exponent, unsigned expbytes)
    : m_expbytes(0) {
        if (!(Create(modulus, modbytes, exponent, expbytes))) {
            Error error = Error::Failed;
            throw(error);
        }
    }
    PublicKey(const PublicKey& copy)
    : m_expbytes(0) {
        if (!(Create(copy.m_modulus, copy.m_modbytes, copy.m_exponent, copy.m_expbytes))) {
            Error error = Error::Failed;
            throw(error);
        }
    }
    PublicKey(): m_expbytes(0) {
    }
    virtual ~PublicKey() {
        if (!(Destroy())) {
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
            mpz_set_msb(&m_modulus, modulus, m_modbytes = modbytes);
            mpz_set_msb(&m_exponent, exponent, m_expbytes = expbytes);
            return true;
        }
        return false;
    }
    virtual int GetMSB
    (unsigned& explen, BYTE* modulus, unsigned modbytes,
     BYTE* exponent, unsigned expbytes) const {
        if ((modulus) && (modbytes) && (exponent) && (expbytes)) {
            if ((modbytes >= m_modbytes) && (expbytes >= m_expbytes)) {
                mpz_get_msb(modulus, m_modbytes, &m_modulus);
                mpz_get_msb(exponent, m_expbytes, &m_exponent);
                explen = m_expbytes;
                return m_modbytes;
            }
        }
        return -Error::Failed;
    }
    virtual int GetModulusMSB
    (BYTE* modulus, unsigned modbytes) const {
        if ((modulus) && (modbytes)) {
            if ((modbytes >= m_modbytes)) {
                mpz_get_msb(modulus, m_modbytes, &m_modulus);
                return m_modbytes;
            }
        }
        return -Error::Failed;
    }
    virtual int GetExponentMSB
    (BYTE* exponent, unsigned expbytes) const {
        if ((exponent) && (expbytes)) {
            if ((expbytes >= m_expbytes)) {
                mpz_get_msb(exponent, m_expbytes, &m_exponent);
                return m_expbytes;
            }
        }
        return -Error::Failed;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Create
    (const MP_INT& modulus, unsigned modbytes,
     const MP_INT& exponent, unsigned expbytes) {
        if ((modbytes) && (expbytes)) {
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
    (const MP_INT& modulus, const MP_INT& exponent) {
        if ((m_modbytes)) {
            if ((m_expbytes)) {
                mpz_set(&m_modulus, (&modulus));
                mpz_set(&m_exponent, (&exponent));
                return true;
            }
        }
        return false;
    }
    virtual int Get
    (unsigned& explen, MP_INT& modulus, MP_INT& exponent) const {
        if ((m_modbytes)) {
            if ((m_expbytes)) {
                mpz_set(&modulus, &m_modulus);
                mpz_set(&exponent, &m_exponent);
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
            m_expbytes = expbytes;
            mpz_init_set_ui(&m_modulus,0);
            mpz_init_set_ui(&m_exponent,0);
            return true;
        }
        return false;
    }
    virtual bool Destroy() {
        bool success = true;
        m_expbytes = 0;
        if (!(Extends::Destroy())) {
            success = false;
        }
        mpz_clear(&m_modulus);
        mpz_clear(&m_exponent);
        return success;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t operator()
    (void* out, size_t outsize, const void* in, ssize_t inlen) {
        size_t inbytes;
        if ((in) && (0 > inlen)) {
            inlen = (int)(strlen((const char*)in));
        }
        if ((inbytes = ((size_t)(inlen))) && (inbytes < m_modbytes)) {
            memset((char*)(in)+inbytes,0,m_modbytes-inbytes);
            inbytes = m_modbytes;
        }
        if ((m_modbytes) && (m_expbytes)) {
            if ((in) && (m_modbytes == inbytes) && (out) && (outsize >= m_modbytes)) {

                mpz_set_msb(&m_temp, (const BYTE*)(in), inbytes);
                mpz_powm(&m_temp, &m_temp, &m_exponent, &m_modulus);
                mpz_get_msb((BYTE*)(out), inbytes, &m_temp);
                return m_modbytes;
            }
        }
        return -Error::Failed;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    unsigned m_expbytes;
    MP_INT m_modulus;
    MP_INT m_exponent;
};

} // namespace mp
} // namespace rsa 
} // namespace crypto 
} // namespace xos 

#endif // _XOS_CRYPTO_RSA_MP_PUBLICKEY_HPP 
