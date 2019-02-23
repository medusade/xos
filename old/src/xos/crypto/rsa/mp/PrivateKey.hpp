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
///   File: PrivateKey.hpp
///
/// Author: $author$
///   Date: 1/15/2014
///
/// Tatu Ylonen's RSA private key implementation modified to be a C++
/// class that uses the gmp used in the original C version.
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_CRYPTO_RSA_MP_PRIVATEKEY_HPP
#define _XOS_CRYPTO_RSA_MP_PRIVATEKEY_HPP

#include "xos/crypto/rsa/PrivateKey.hpp"
#include "xos/crypto/rsa/mp/Key.hpp"
#include "mpz_msb.h"

namespace xos {
namespace crypto {
namespace rsa {
namespace mp {

class _EXPORT_CLASS KeyGenerator;
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS PrivateKeyImplement
: virtual public rsa::PrivateKeyImplement, virtual public mp::KeyImplement {
};
typedef Key PrivateKeyExtend;
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS PrivateKey
: virtual public PrivateKeyImplement, public PrivateKeyExtend {
friend class KeyGenerator;
public:
    typedef PrivateKeyImplement Implements;
    typedef PrivateKeyExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    PrivateKey
    (const BYTE *p,
     const BYTE *q,
     const BYTE *dmp1,
     const BYTE *dmq1,
     const BYTE *iqmp,
     unsigned pbytes)
    : m_pbytes(0) {
        if (!(CreateMSB(p, q, dmp1, dmq1, iqmp, pbytes))) {
            Error error = Error::Failed;
            throw(error);
        }
    }
    PrivateKey
    (const MP_INT& p,
     const MP_INT& q,
     const MP_INT& dmp1,
     const MP_INT& dmq1,
     const MP_INT& iqmp,
     unsigned pbytes)
    : m_pbytes(0) {
        if (!(Create(p, q, dmp1, dmq1, iqmp, pbytes))) {
            Error error = Error::Failed;
            throw(error);
        }
    }
    PrivateKey(unsigned pbytes)
    : m_pbytes(0) {
        if (!(Create(pbytes))) {
            Error error = Error::Failed;
            throw(error);
        }
    }
    PrivateKey(const PrivateKey& copy)
    : m_pbytes(0) {
        if (!(Create(copy.m_p, copy.m_q, copy.m_dmp1, copy.m_dmq1, copy.m_iqmp, copy.m_pbytes))) {
            Error error = Error::Failed;
            throw(error);
        }
    }
    PrivateKey()
    : m_pbytes(0) {
    }
    virtual ~PrivateKey() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Create
    (const MP_INT& p,
     const MP_INT& q,
     const MP_INT& dmp1,
     const MP_INT& dmq1,
     const MP_INT& iqmp,
     unsigned pbytes) {
        if ((Create(pbytes))) {
            if ((Set(p,q,dmp1,dmq1,iqmp))) {
                return true;
            }
            Destroy();
        }
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Set
    (const MP_INT& p,
     const MP_INT& q,
     const MP_INT& dmp1,
     const MP_INT& dmq1,
     const MP_INT& iqmp) {
        if ((m_pbytes)) {
            mpz_set(&m_p,&p);
            mpz_set(&m_q,&q);
            mpz_set(&m_dmp1,&dmp1);
            mpz_set(&m_dmq1,&dmq1);
            mpz_set(&m_iqmp,&iqmp);
            return true;
        }
        return false;
    }
    virtual int Get
    (MP_INT& p,
     MP_INT& q,
     MP_INT& dmp1,
     MP_INT& dmq1,
     MP_INT& iqmp) const {
        if ((m_pbytes)) {
            mpz_set(&p,&m_p);
            mpz_set(&q,&m_q);
            mpz_set(&dmp1,&m_dmp1);
            mpz_set(&dmq1,&m_dmq1);
            mpz_set(&iqmp,&m_iqmp);
            return m_pbytes;
        }
        return -Error::Failed;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool CreateMSB
    (const BYTE *p,
     const BYTE *q,
     const BYTE *dmp1,
     const BYTE *dmq1,
     const BYTE *iqmp,
     unsigned pbytes) {
        if ((Create(pbytes))) {
            if ((SetMSB(p,q,dmp1,dmq1,iqmp,pbytes))) {
                return true;
            }
            Destroy();
        }
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool SetMSB
    (const BYTE *p,
     const BYTE *q,
     const BYTE *dmp1,
     const BYTE *dmq1,
     const BYTE *iqmp,
     unsigned pbytes) {
        if ((p) && (q) && (dmp1) && (dmq1) && (iqmp)) {
            if ((m_pbytes)) {
                mpz_set_msb(&m_p,p,pbytes);
                mpz_set_msb(&m_q,q,pbytes);
                mpz_set_msb(&m_dmp1,dmp1,pbytes);
                mpz_set_msb(&m_dmq1,dmq1,pbytes);
                mpz_set_msb(&m_iqmp,iqmp,pbytes);
                return true;
            }
        }
        return false;
    }
    virtual int GetMSB
    (BYTE *p,
     BYTE *q,
     BYTE *dmp1,
     BYTE *dmq1,
     BYTE *iqmp,
     unsigned pbytes) const {
        if ((p) && (q) && (dmp1) && (dmq1) && (iqmp) && (pbytes >= m_pbytes)) {
            if ((m_pbytes)) {
                return pbytes;
            }
        }
        return -Error::Failed;
    }
    virtual int GetPMSB(BYTE *p, unsigned pbytes) const {
        if ((p) && (pbytes >= m_pbytes)) {
            if ((m_pbytes)) {
                mpz_get_msb(p, m_pbytes, &m_p);
                return pbytes;
            }
        }
        return -Error::Failed;
    }
    virtual int GetQMSB(BYTE *p, unsigned pbytes) const {
        if ((p) && (pbytes >= m_pbytes)) {
            if ((m_pbytes)) {
                mpz_get_msb(p, m_pbytes, &m_q);
                return pbytes;
            }
        }
        return -Error::Failed;
    }
    virtual int GetDmp1MSB(BYTE *p, unsigned pbytes) const {
        if ((p) && (pbytes >= m_pbytes)) {
            if ((m_pbytes)) {
                mpz_get_msb(p, m_pbytes, &m_dmp1);
                return pbytes;
            }
        }
        return -Error::Failed;
    }
    virtual int GetDmq1MSB(BYTE *p, unsigned pbytes) const {
        if ((p) && (pbytes >= m_pbytes)) {
            if ((m_pbytes)) {
                mpz_get_msb(p, m_pbytes, &m_dmq1);
                return pbytes;
            }
        }
        return -Error::Failed;
    }
    virtual int GetIqmpMSB(BYTE *p, unsigned pbytes) const {
        if ((p) && (pbytes >= m_pbytes)) {
            if ((m_pbytes)) {
                mpz_get_msb(p, m_pbytes, &m_iqmp);
                return pbytes;
            }
        }
        return -Error::Failed;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Create(unsigned pbytes) {
        if (!(Destroyed())) {
            return false;
        }
        if ((Extends::Create(pbytes*2))) {
            mpz_init_set_ui(&m_p,0);
            mpz_init_set_ui(&m_q,0);
            mpz_init_set_ui(&m_dmp1,0);
            mpz_init_set_ui(&m_dmq1,0);
            mpz_init_set_ui(&m_iqmp,0);
            mpz_init_set_ui(&m_ptemp,0);
            mpz_init_set_ui(&m_qtemp,0);
            m_pbytes = pbytes;
            return true;
        }
        return false;
    }
    virtual bool Destroy() {
        bool success = true;
        if (!(Extends::Destroy())) {
            success = false;
        }
        mpz_clear(&m_p);
        mpz_clear(&m_q);
        mpz_clear(&m_dmp1);
        mpz_clear(&m_dmq1);
        mpz_clear(&m_iqmp);
        mpz_clear(&m_ptemp);
        mpz_clear(&m_qtemp);
        return success;
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
        if ((m_pbytes) && (m_modbytes)) {
            if ((in) && (m_modbytes == inbytes)
                && (out) && (outsize >= m_modbytes)) {
                mpz_set_msb(&m_temp,(const BYTE*)in,inbytes);

                /* Compute q2 = (value mod q) ^ dmq1 mod q.
                 */
                mpz_mod(&m_qtemp,&m_temp,&m_q);
                mpz_powm(&m_qtemp,&m_qtemp,&m_dmq1,&m_q);

                /* Compute p2 = (value mod p) ^ dmp1 mod p.
                 */
                mpz_mod(&m_ptemp,&m_temp,&m_p);
                mpz_powm(&m_ptemp,&m_ptemp,&m_dmp1,&m_p);

                /* if q2 > p then q2 = q2 - p
                 */
                if ((subp=(mpz_cmp(&m_qtemp,&m_p)>0))!=0)
                    mpz_sub(&m_qtemp,&m_qtemp,&m_p);

                /* Compute k = (((p2 + p) - q2) mod p) * iqmp mod p.
                 */
                mpz_add(&m_temp,&m_ptemp,&m_p);
                mpz_sub(&m_temp,&m_temp,&m_qtemp);
                mpz_mul(&m_ptemp,&m_temp,&m_iqmp);
                mpz_mmod(&m_temp,&m_ptemp,&m_p);

                /* Compute value = q2 + q * k.
                 */
                mpz_mul(&m_ptemp,&m_temp,&m_q);
                mpz_add(&m_temp,&m_ptemp,&m_qtemp);

                /* if we subtracted p before then add it back here
                 */
                if (subp)
                    mpz_add(&m_temp,&m_temp,&m_p);

                mpz_get_msb((BYTE*)out,inbytes,&m_temp);
                return m_modbytes;
            }
        }
        return -Error::Failed;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    unsigned m_pbytes;
    MP_INT m_p;
    MP_INT m_q;
    MP_INT m_dmp1;
    MP_INT m_dmq1;
    MP_INT m_iqmp;
    MP_INT m_ptemp;
    MP_INT m_qtemp;
};

} // namespace mp
} // namespace rsa 
} // namespace crypto 
} // namespace xos 

#endif // _XOS_CRYPTO_RSA_MP_PRIVATEKEY_HPP 
