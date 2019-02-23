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
///   File: Reader.hpp
///
/// Author: $author$
///   Date: 4/20/2015
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_CRYPTO_RSA_MP_RANDOM_READER_HPP
#define _XOS_CRYPTO_RSA_MP_RANDOM_READER_HPP

#include "xos/crypto/rsa/random/Reader.hpp"
#include "xos/crypto/rsa/mp/Number.hpp"

namespace xos {
namespace crypto {
namespace rsa {
namespace mp {
namespace random {

typedef rsa::random::Reader<BIGPRIME> ReaderImplement;
typedef ReaderImplement::Observer ReaderObserver;
///////////////////////////////////////////////////////////////////////
///  Class: Reader
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Reader
: virtual public ReaderImplement, virtual public ReaderObserver {
public:
    typedef ReaderImplement ReaderImplements;
    typedef ReaderObserver ObserverImplements;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t ReadMSB(BIGPRIME* n, size_t bytes, crypto::Reader& reader) {
        BYTE byte;
        mpz_set_ui(n,0);
        for (size_t i=0; i<bytes; i++) {
            if (0 >= (Get(byte, reader)))
                return 0;
            mpz_mul_2exp(n,n,8);
            mpz_add_ui(n,n,byte);
        }
        bytes = OnRead(n, bytes);
        return bytes;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace random 
} // namespace mp 
} // namespace rsa 
} // namespace crypto 
} // namespace xos 

#endif // _XOS_CRYPTO_RSA_MP_RANDOM_READER_HPP 
