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
///   File: Key.hpp
///
/// Author: $author$
///   Date: 1/15/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_CRYPTO_RSA_MP_KEY_HPP
#define _XOS_CRYPTO_RSA_MP_KEY_HPP

#include "xos/crypto/rsa/Key.hpp"
#include "mpz_msb.h"

namespace xos {
namespace crypto {
namespace rsa {
namespace mp {

typedef rsa::KeyImplement KeyImplement;
typedef rsa::Key KeyExtend;
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Key
: virtual public KeyImplement, public KeyExtend {
public:
    typedef KeyImplement Implements;
    typedef KeyExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Key() {
    }
    virtual ~Key() {
        if (!(Destroyed())) {
            Error error = xos::Error::Failed;
            throw(error);
        }
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Create(unsigned modbytes) {
        if (!(Destroyed())) {
            return false;
        }
        mpz_init_set_ui(&m_temp,0);
        m_modbytes = modbytes;
        return SetIsCreated(true);
    }
    virtual bool Destroy() {
        bool success = true;
        m_modbytes = 0;
        m_isCreated = false;
        mpz_clear(&m_temp);
        return success;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    MP_INT m_temp;
};

} // namespace mp
} // namespace rsa 
} // namespace crypto 
} // namespace xos 

#endif // _XOS_CRYPTO_RSA_MP_KEY_HPP 
