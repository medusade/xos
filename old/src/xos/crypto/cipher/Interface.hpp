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
///   File: Interface.hpp
///
/// Author: $author$
///   Date: 5/20/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_CRYPTO_CIPHER_INTERFACE_HPP
#define _XOS_CRYPTO_CIPHER_INTERFACE_HPP

#include "xos/crypto/Base.hpp"

namespace xos {
namespace crypto {
namespace cipher {

typedef BaseImplement InterfaceImplement;
///////////////////////////////////////////////////////////////////////
///  Class: Interface
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Interface: virtual public InterfaceImplement {
public:
    typedef InterfaceImplement Implements;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Initialize
    (const void* key, ssize_t keylen = -1,
     const void* iv = 0, ssize_t ivlen = -1,
     const void* padd = 0, ssize_t paddlen = -1) {
        ssize_t count = 0;
        return count;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Encrypt
    (void* out, size_t outsize, const void* in, ssize_t inlen = -1) {
        ssize_t count = 0;
        return count;
    }
    virtual ssize_t Decrypt
    (void* out, size_t outsize, const void* in, ssize_t inlen = -1) {
        ssize_t count = 0;
        return count;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t operator()
    (void* out, size_t outsize, const void* in, ssize_t inlen = -1) {
        ssize_t count = 0;
        return count;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t KeySizeMin() const {
        return 0;
    }
    virtual ssize_t KeySizeMax() const {
        return 0;
    }
    virtual ssize_t KeySize() const {
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t IVSizeMin() const {
        return 0;
    }
    virtual ssize_t IVSizeMax() const {
        return 0;
    }
    virtual ssize_t IVSize() const {
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t BlockSize() const {
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool IsBlock() const {
        return (1 > BlockSize());
    }
    virtual bool IsStream() const {
        return (1 == BlockSize());
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace cipher 
} // namespace crypto 
} // namespace xos 

#endif // _XOS_CRYPTO_CIPHER_INTERFACE_HPP 
