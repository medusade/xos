///////////////////////////////////////////////////////////////////////
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
///   File: MillerRabin.hpp
///
/// Author: $author$
///   Date: 4/20/2015
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_CRYPTO_RSA_MP_RANDOM_PRIME_MILLERRABIN_HPP
#define _XOS_CRYPTO_RSA_MP_RANDOM_PRIME_MILLERRABIN_HPP

#include "xos/crypto/rsa/mp/random/Reader.hpp"
#include "xos/base/Creator.hpp"

namespace xos {
namespace crypto {
namespace rsa {
namespace mp {
namespace random {
namespace prime {

typedef CreatorImplementT
<CreatorT<rsa::mp::random::Reader> > MillerRabinImplement;
typedef CreatorExtendT<MillerRabinImplement> MillerRabinExtend;
///////////////////////////////////////////////////////////////////////
///  Class: MillerRabin
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS MillerRabin
: virtual public MillerRabinImplement,public MillerRabinExtend {
public:
    typedef MillerRabinImplement Implements;
    typedef MillerRabinExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    MillerRabin() {
    }
    virtual ~MillerRabin() {
        if (!(Destroyed())) {
            Exception e(FailedToDestroy);
            throw(e);
        }
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Create() {
        if ((Destroyed())) {
            mpz_init_set_ui(&m_n_minus_1,0);
            mpz_init_set_ui(&m_x,0);
            mpz_init_set_ui(&m_one,1);
            mpz_init_set_ui(&m_z,0);
            mpz_init_set_ui(&m_q,0);
            SetIsCreated(true);
            return true;
        }
        return false;
    }
    virtual bool Destroy() {
        if ((IsCreated())) {
            SetIsCreated(false);
            mpz_clear(&m_q);
            mpz_clear(&m_z);
            mpz_clear(&m_one);
            mpz_clear(&m_x);
            mpz_clear(&m_n_minus_1);
            return true;
        }
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool ProbablyPrime
    (BIGPRIME* n, size_t bytes, unsigned reps, crypto::Reader& random) {
        if ((IsCreated())) {
            unsigned bits = (bytes << 3);
            unsigned i,j,k;

            mpz_sub(&m_n_minus_1, n, &m_one);

            /* find q and k, such that n = 1 + 2^k * q
             * ie q = (n-1)/2^k
             */
            mpz_set(&m_q, &m_n_minus_1);

            for (k=0; (mpz_get_ui(&m_q)&1)==0; k++)
                mpz_tdiv_q_2exp(&m_q, &m_q, 1);

            for (i = 0; i < reps ; i++) {
                /* find random x such that 1 < x < n 
                 */
                do {
                    if (0 >= (ReadMSB(&m_x, bytes, random)))
                        return false;

                    /* make x < n
                     */
                    mpz_clrbit(&m_x, bits-1);
                } while (mpz_cmp(&m_x, &m_one) <= 0);

                /* z =  x^q mod n
                 */
                mpz_powm(&m_z, &m_x, &m_q, n);

                /* if z == 0 or z == n-1 then possibly prime
                 */
                if ((mpz_cmp(&m_z, &m_one) == 0)
                    || (mpz_cmp(&m_z, &m_n_minus_1) == 0))
                    continue;

                for (j = 1; j < k; j++) {
                    /* z = z^2 mod n
                     */
                    mpz_powm_ui(&m_z, &m_z, 2, n);

                    /* if z == n-1 then possibly prime
                     */
                    if (mpz_cmp(&m_z, &m_n_minus_1) == 0)
                        break;

                    /* if z == 1 then not prime
                     */
                    if (mpz_cmp(&m_z, &m_one) == 0)
                        return false;
                }

                if (j>=k)
                    return false;
            }
            return true;
        }
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    MP_INT m_n_minus_1;
    MP_INT m_x;
    MP_INT m_one;
    MP_INT m_z;
    MP_INT m_q;
};

} // namespace prime 
} // namespace random 
} // namespace mp 
} // namespace rsa 
} // namespace crypto 
} // namespace xos 

#endif // _XOS_CRYPTO_RSA_MP_RANDOM_PRIME_MILLERRABIN_HPP 
