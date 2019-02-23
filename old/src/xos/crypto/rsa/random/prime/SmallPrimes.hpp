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
///   File: SmallPrimes.hpp
///
/// Author: $author$
///   Date: 4/29/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_CRYPTO_RSA_RANDOM_PRIME_SMALLPRIMES_HPP
#define _XOS_CRYPTO_RSA_RANDOM_PRIME_SMALLPRIMES_HPP

#include "xos/base/Base.hpp"

#define SMALL_PRIMES_SIZE 1028

namespace xos {
namespace crypto {
namespace rsa {
namespace random {
namespace prime {

extern const unsigned short g_small_primes[SMALL_PRIMES_SIZE];

} // namespace prime
} // namespace random 
} // namespace rsa 
} // namespace crypto 
} // namespace xos 

#endif // _XOS_CRYPTO_RSA_RANDOM_PRIME_SMALLPRIMES_HPP 
