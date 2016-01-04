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
///   File: PrivateKey.hpp
///
/// Author: $author$
///   Date: 1/13/2014
///
/// Tatu Ylonen's RSA private key implementation modified to be a C++
/// class that uses Eric Young's big number library instead of gmp used
/// in the original C version.
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_CRYPTO_RSA_BN_PRIVATEKEY_HPP
#define _XOS_CRYPTO_RSA_BN_PRIVATEKEY_HPP

#include "xos/crypto/rsa/PrivateKey.hpp"
#include "xos/crypto/rsa/bn/Key.hpp"
#include "bn_msb.h"

namespace xos {
namespace crypto {
namespace rsa {
namespace bn {

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS PrivateKeyImplement
: virtual public rsa::PrivateKeyImplement, virtual public bn::KeyImplement {
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
    : m_p(0), m_q(0),
      m_dmp1(0), m_dmq1(0),
      m_iqmp(0), m_ptemp(0), m_qtemp(0) {
        if (!(CreateMSB(p, q, dmp1, dmq1, iqmp, pbytes))) {
            Error error = Error::Failed;
            throw(error);
        }
    }
    PrivateKey
    (const BIGNUM *p,
     const BIGNUM *q,
     const BIGNUM *dmp1,
     const BIGNUM *dmq1,
     const BIGNUM *iqmp,
     unsigned pbytes)
    : m_p(0), m_q(0),
      m_dmp1(0), m_dmq1(0),
      m_iqmp(0), m_ptemp(0), m_qtemp(0) {
        if (!(Create(p, q, dmp1, dmq1, iqmp, pbytes))) {
            Error error = Error::Failed;
            throw(error);
        }
    }
    PrivateKey(unsigned pbytes)
    : m_p(0), m_q(0),
      m_dmp1(0), m_dmq1(0),
      m_iqmp(0), m_ptemp(0), m_qtemp(0) {
        if (!(Create(pbytes))) {
            Error error = Error::Failed;
            throw(error);
        }
    }
    PrivateKey(const PrivateKey& copy)
    : m_p(0), m_q(0),
      m_dmp1(0), m_dmq1(0),
      m_iqmp(0), m_ptemp(0), m_qtemp(0) {
        if (!(Create(copy.m_p, copy.m_q, copy.m_dmp1, copy.m_dmq1, copy.m_iqmp, copy.m_pbytes))) {
            Error error = Error::Failed;
            throw(error);
        }
    }
    PrivateKey()
    : m_p(0), m_q(0),
      m_dmp1(0), m_dmq1(0),
      m_iqmp(0), m_ptemp(0), m_qtemp(0) {
    }
    virtual ~PrivateKey() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Create
    (const BIGNUM *p,
     const BIGNUM *q,
     const BIGNUM *dmp1,
     const BIGNUM *dmq1,
     const BIGNUM *iqmp,
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
    (const BIGNUM *p,
     const BIGNUM *q,
     const BIGNUM *dmp1,
     const BIGNUM *dmq1,
     const BIGNUM *iqmp) {
        if ((p) && (q) && (dmp1) && (dmq1) && (iqmp)) {
            if ((m_p) && (m_q) && (m_dmp1) && (m_dmq1) && (m_iqmp)) {
                BN_copy(m_p,(BIGNUM*)(p));
                BN_copy(m_q,(BIGNUM*)(q));
                BN_copy(m_dmp1,(BIGNUM*)(dmp1));
                BN_copy(m_dmq1,(BIGNUM*)(dmq1));
                BN_copy(m_iqmp,(BIGNUM*)(iqmp));
                return true;
            }
        }
        return false;
    }
    virtual int Get
    (BIGNUM *p,
     BIGNUM *q,
     BIGNUM *dmp1,
     BIGNUM *dmq1,
     BIGNUM *iqmp) const {
        if ((p) && (q) && (dmp1) && (dmq1) && (iqmp)) {
            if ((m_p) && (m_q) && (m_dmp1) && (m_dmq1) && (m_iqmp) && (m_pbytes)) {
                BN_copy(p,m_p);
                BN_copy(q,m_q);
                BN_copy(dmp1,m_dmp1);
                BN_copy(dmq1,m_dmq1);
                BN_copy(iqmp,m_iqmp);
                return m_pbytes;
            }
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
            if ((m_p) && (m_q) && (m_dmp1) && (m_dmq1) && (m_iqmp)) {
                BN_set_msb(m_p,p,pbytes);
                BN_set_msb(m_q,q,pbytes);
                BN_set_msb(m_dmp1,dmp1,pbytes);
                BN_set_msb(m_dmq1,dmq1,pbytes);
                BN_set_msb(m_iqmp,iqmp,pbytes);
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
            if ((m_p) && (m_q) && (m_dmp1) && (m_dmq1) && (m_iqmp)) {
                BN_get_msb(m_p,p,m_pbytes);
                BN_get_msb(m_q,q,m_pbytes);
                BN_get_msb(m_dmp1,dmp1,m_pbytes);
                BN_get_msb(m_dmq1,dmq1,m_pbytes);
                BN_get_msb(m_iqmp,iqmp,m_pbytes);
                return pbytes;
            }
        }
        return -Error::Failed;
    }
    virtual int GetPMSB
    (BYTE *p, unsigned pbytes) const {
        if ((p) && (pbytes >= m_pbytes)) {
            if ((m_p)) {
                BN_get_msb(m_p,p,m_pbytes);
                return pbytes;
            }
        }
        return -Error::Failed;
    }
    virtual int GetQMSB
    (BYTE *q, unsigned pbytes) const {
        if ((q) && (pbytes >= m_pbytes)) {
            if ((m_q)) {
                BN_get_msb(m_q,q,m_pbytes);
                return pbytes;
            }
        }
        return -Error::Failed;
    }
    virtual int GetDmp1MSB
    (BYTE *dmp1, unsigned pbytes) const {
        if ((dmp1) && (pbytes >= m_pbytes)) {
            if ((m_dmp1)) {
                BN_get_msb(m_dmp1,dmp1,m_pbytes);
                return pbytes;
            }
        }
        return -Error::Failed;
    }
    virtual int GetDmq1MSB
    (BYTE *dmq1, unsigned pbytes) const {
        if ((dmq1) && (pbytes >= m_pbytes)) {
            if ((m_dmq1)) {
                BN_get_msb(m_dmq1,dmq1,m_pbytes);
                return pbytes;
            }
        }
        return -Error::Failed;
    }
    virtual int GetIqmpMSB
    (BYTE *iqmp, unsigned pbytes) const {
        if ((iqmp) && (pbytes >= m_pbytes)) {
            if ((m_iqmp)) {
                BN_get_msb(m_iqmp,iqmp,m_pbytes);
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
        if ((m_p=BN_new())) {
            if ((m_q=BN_new())) {
                if ((m_dmp1=BN_new())) {
                    if ((m_dmq1=BN_new())) {
                        if ((m_iqmp=BN_new())) {
                            if ((m_ptemp=BN_new())) {
                                if ((m_qtemp=BN_new())) {
                                    if ((Extends::Create(pbytes*2))) {
                                        m_pbytes = pbytes;
                                        return true;
                                    }
                                    BN_free(m_qtemp);
                                }
                                BN_free(m_ptemp);
                            }
                            BN_free(m_iqmp);
                        }
                        BN_free(m_dmq1);
                    }
                    BN_free(m_dmp1);
                }
                BN_free(m_q);
            }
            BN_free(m_p);
        }
        return false;
    }
    virtual bool Destroy() {
        bool success = true;
        if (!(BN_free(m_p))) {
            success = false;
        }
        if (!(BN_free(m_q))) {
            success = false;
        }
        if (!(BN_free(m_dmp1))) {
            success = false;
        }
        if (!(BN_free(m_dmq1))) {
            success = false;
        }
        if (!(BN_free(m_iqmp))) {
            success = false;
        }
        if (!(BN_free(m_ptemp))) {
            success = false;
        }
        if (!(BN_free(m_qtemp))) {
            success = false;
        }
        if (!(Extends::Destroy())) {
            success = false;
        }
        return success;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual unsigned SetPBytes(unsigned to) {
        m_pbytes = to;
        return m_pbytes;
    }
    virtual unsigned PBytes() const {
        return m_pbytes;
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
        if ((m_p) && (m_q) && (m_dmp1) && (m_dmq1)
            && (m_iqmp) && (m_pbytes) && (m_temp) && (m_ctx) && (m_modbytes)) {
            if ((in) && (m_modbytes == inbytes)
                && (out) && (outsize >= m_modbytes)) {

                BN_set_msb(m_temp,(const BYTE*)in,inbytes);

                /* Compute q2 = (value mod q) ^ dmq1 mod q.
                 */
                BN_mod(m_qtemp,m_temp,m_q,m_ctx);
                BN_mod_exp(m_qtemp,m_qtemp,m_dmq1,m_q,m_ctx);

                /* Compute p2 = (value mod p) ^ dmp1 mod p.
                 */
                BN_mod(m_ptemp,m_temp,m_p,m_ctx);
                BN_mod_exp(m_ptemp,m_ptemp,m_dmp1,m_p,m_ctx);

                /* if q2 > p then q2 = q2 - p
                 */
                if ((subp=(BN_cmp(m_qtemp,m_p)>0))!=0)
                    BN_sub(m_qtemp,m_qtemp,m_p);

                /* Compute k = (((p2 + p) - q2) mod p) * iqmp mod p.
                 */
                BN_add(m_temp,m_ptemp,m_p);
                BN_sub(m_temp,m_temp,m_qtemp);
                BN_mul(m_ptemp,m_temp,m_iqmp);
                BN_mod(m_temp,m_ptemp,m_p,m_ctx);

                /* Compute value = q2 + q * k.
                 */
                BN_mul(m_ptemp,m_temp,m_q);
                BN_add(m_temp,m_ptemp,m_qtemp);

                /* if we subtracted p before the add it back here
                 */
                if (subp)
                    BN_add(m_temp,m_temp,m_p);

                BN_get_msb(m_temp,(BYTE*)out,inbytes);

                return m_modbytes;
            }
        }
        return -Error::Failed;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    unsigned m_pbytes;
    BIGNUM* m_p;
    BIGNUM* m_q;
    BIGNUM* m_dmp1;
    BIGNUM* m_dmq1;
    BIGNUM* m_iqmp;
    BIGNUM* m_ptemp;
    BIGNUM* m_qtemp;
};

} // namespace bn 
} // namespace rsa 
} // namespace crypto 
} // namespace xos 

#endif // _XOS_CRYPTO_RSA_BN_PRIVATEKEY_HPP 
