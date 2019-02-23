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
///   Date: 2/17/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_CRYPTO_RANDOM_INTERFACE_HPP
#define _XOS_CRYPTO_RANDOM_INTERFACE_HPP

#include "xos/crypto/Base.hpp"

namespace xos {
namespace crypto {
namespace random {

typedef InterfaceBase InterfaceImplement;
///////////////////////////////////////////////////////////////////////
///  Class: Interface
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Interface: virtual public InterfaceImplement {
public:
    typedef InterfaceImplement Implements;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Generate(void* out, size_t outSize) = 0;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace random
} // namespace crypto
} // namespace xos

#endif // _XOS_CRYPTO_RANDOM_INTERFACE_HPP
