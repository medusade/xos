///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2013 $organization$
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
///   File: Sha1.hpp
///
/// Author: $author$
///   Date: 7/27/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_CRYPTO_HASH_MXDE_SHA1_HPP
#define _XOS_CRYPTO_HASH_MXDE_SHA1_HPP

#include "xos/crypto/hash/mxde/Hash.hpp"
#include "csha1.hxx"

namespace xos {
namespace crypto {
namespace hash {
namespace mxde {

typedef HashT<Interface, ExportBase, cSHA1> Sha1;

} // namespace mxde 
} // namespace hash 
} // namespace crypto 
} // namespace xos 

#endif // _XOS_CRYPTO_HASH_MXDE_SHA1_HPP 
