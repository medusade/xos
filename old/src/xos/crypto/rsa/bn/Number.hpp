///////////////////////////////////////////////////////////////////////
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
///   File: Number.hpp
///
/// Author: $author$
///   Date: 4/29/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_CRYPTO_RSA_BN_NUMBER_HPP
#define _XOS_CRYPTO_RSA_BN_NUMBER_HPP

#include "xos/crypto/Base.hpp"
#include "xos/base/Creator.hpp"
#include "xos/base/Attacher.hpp"
#include "xos/os/Logger.hpp"
#include "bn_msb.h"

namespace xos {
namespace crypto {
namespace rsa {
namespace bn {

typedef BIGNUM BIGPRIME;
typedef BIGNUM* BIGINT;

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS NumberImplement: virtual public InterfaceBase {
public:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool BN_CTX_free(BN_CTX*& a) {
        if ((a)) {
            ::BN_CTX_free(a);
            a = 0;
            return true;
        }
        return false;
    }
    virtual bool BN_free(BIGNUM*& a) {
        if ((a)) {
            ::BN_free(a);
            a = 0;
            return true;
        }
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS NumberExtend: virtual public NumberImplement, public ExportBase {
public:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    NumberExtend() {}
    virtual ~NumberExtend() {}
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

typedef CreatorImplementT<CreatorT<NumberImplement> > NumberCreator;
typedef AttacherT<BIGNUM*, int, 0, NumberCreator> NumberAttacher;
typedef AttachedT<BIGNUM*, int, 0, NumberAttacher, NumberExtend> NumberAttached;
typedef CreatedT<BIGNUM*, int, 0, NumberAttacher, NumberAttached> NumberCreated;
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
        BIGNUM* detached = 0;
        if ((detached = BN_new())) {
            this->AttachCreated(detached);
            ::BN_set_word(detached, initialValue);
            return true;
        }
        return true; 
    }
    virtual bool Destroy() {
        BIGNUM* detached = 0;
        if ((detached = this->Detach())) {
            ::BN_free(detached);
            return true;
        }
        return false; 
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t ToMSB(BYTE* to, unsigned bytes) {
        ssize_t size = 0;
        if ((to) && (bytes)) {
            BIGNUM* detached = 0;
            if ((detached = this->AttachedTo())) {
                BN_get_msb(detached, to, bytes);
                size = bytes;
            }
        }
        return size;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace bn
} // namespace rsa
} // namespace crypto
} // namespace xos 

#endif // _XOS_CRYPTO_RSA_BN_NUMBER_HPP
