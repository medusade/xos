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
///   File: PrivateKey.hpp
///
/// Author: $author$
///   Date: 5/18/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_CRYPTO_RSA_PRIVATEKEY_HPP
#define _XOS_CRYPTO_RSA_PRIVATEKEY_HPP

#include "xos/crypto/rsa/Key.hpp"

namespace xos {
namespace crypto {
namespace rsa {

///////////////////////////////////////////////////////////////////////
///  Class: PrivateKeyImplement
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS PrivateKeyImplement: virtual public KeyImplement {
public:
    typedef KeyImplement Implements;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool CreateMSB
    (const BYTE *p, const BYTE *q,
     const BYTE *dmp1, const BYTE *dmq1,
     const BYTE *iqmp, unsigned pbytes) {
        return false;
    }
    virtual bool Create(unsigned pbytes) {
        return false;
    }
    virtual bool Destroy() {
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool SetMSB
    (const BYTE *p, const BYTE *q,
     const BYTE *dmp1, const BYTE *dmq1,
     const BYTE *iqmp, unsigned pbytes) {
        return false;
    }
    virtual int GetMSB
    (BYTE *p, BYTE *q,
     BYTE *dmp1, BYTE *dmq1,
     BYTE *iqmp, unsigned pbytes) const {
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

#endif // _XOS_CRYPTO_RSA_PRIVATEKEY_HPP 
