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
///   File: NumberImplement.hpp
///
/// Author: $author$
///   Date: 4/20/2015
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_CRYPTO_RSA_MP_NUMBER_HPP
#define _XOS_CRYPTO_RSA_MP_NUMBER_HPP

#include "xos/crypto/Base.hpp"
#include "xos/base/Creator.hpp"
#include "xos/base/Attacher.hpp"
#include "xos/os/Logger.hpp"
#include "mpz_msb.h"
#include <gmp.h>

namespace xos {
namespace crypto {
namespace rsa {
namespace mp {

typedef MP_INT BIGPRIME;
typedef MP_INT BIGINT;

///////////////////////////////////////////////////////////////////////
///  Class: NumberImplement
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS NumberImplement: virtual public InterfaceBase {
public:
    typedef InterfaceBase Implements;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS NumberExtend
: virtual public NumberImplement, public ExportBase {
public:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    NumberExtend() {}
    virtual ~NumberExtend() {}
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

typedef CreatorImplementT<CreatorT<NumberImplement> > NumberCreator;
typedef AttacherT<MP_INT*, int, 0, NumberCreator> NumberAttacher;
typedef AttachedT<MP_INT*, int, 0, NumberAttacher, NumberExtend> NumberAttached;
typedef CreatedT<MP_INT*, int, 0, NumberAttacher, NumberAttached> NumberCreated;
typedef NumberAttacher NumberImplements;
typedef NumberCreated NumberExtends;
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Number
: virtual public NumberImplements, public NumberExtends {
public:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Number(unsigned initialValue = 0) {
        if (!(this->Create(initialValue))) {
            Exception e = FailedToCreate;
            XOS_LOG_ERROR("Throwing FailedToCreate...");
            throw (e);
        }
    }
    virtual ~Number() {
        if (!(this->Destroyed())) {
            Exception e = FailedToDestroy;
            XOS_LOG_ERROR("Throwing FailedToDestroy...");
            throw (e);
        }
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Create(unsigned initialValue = 0) {
        MP_INT* detached = 0;
        if ((detached = this->AttachCreated(&m_value))) {
            mpz_init_set_ui(detached, initialValue);
            return true;
        }
        return true; 
    }
    virtual bool Destroy() {
        MP_INT* detached = 0;
        if ((detached = this->Detach())) {
            mpz_clear(detached);
            return true;
        }
        return false; 
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t ToMSB(BYTE* to, unsigned bytes) {
        ssize_t size = 0;
        if ((to) && (bytes)) {
            MP_INT* detached = 0;
            if ((detached = this->AttachedTo())) {
                mp_size_t mpsize = 0;
                if (bytes <= (mpsize = mpz_get_msb(to, bytes, detached))) {
                    size = mpsize;
                }
            }
        }
        return size;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    MP_INT m_value;
};

} // namespace mp 
} // namespace rsa 
} // namespace crypto 
} // namespace xos 

#endif // _XOS_CRYPTO_RSA_MP_NUMBER_HPP 
