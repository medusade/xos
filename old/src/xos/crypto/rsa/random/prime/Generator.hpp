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
///   File: Generator.hpp
///
/// Author: $author$
///   Date: 4/29/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_CRYPTO_RSA_RANDOM_PRIME_GENERATOR_HPP
#define _XOS_CRYPTO_RSA_RANDOM_PRIME_GENERATOR_HPP

#include "xos/crypto/rsa/random/Reader.hpp"

#if !defined(_RSA_NO_SMALL_PRIME_TEST)
#include "SmallPrimes.hpp"
#define _RSA_SMALL_PRIME_DIFFERENCE 0x7
#endif // !defined(_CRSA_NO_SMALL_PRIME_TEST)

#if !defined(_RSA_NO_MILLER_RABIN_TEST)
#define _RSA_MILLER_RABIN_REPS 25
#endif // !defined(_CRSA_NO_MILLER_RABIN_TEST)

namespace xos {
namespace crypto {
namespace rsa {
namespace random {
namespace prime {

///////////////////////////////////////////////////////////////////////
///  Class: Generator
///////////////////////////////////////////////////////////////////////
template <typename TBIGPRIME, class TImplement>
class _EXPORT_CLASS Generator: virtual public TImplement {
public:
    typedef TImplement Implements;
    typedef TBIGPRIME BIGPRIME;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

///////////////////////////////////////////////////////////////////////
///  Class: GeneratorExtend
///////////////////////////////////////////////////////////////////////
template <typename TBIGPRIME, class TImplement, class TExtend = ExportBase>
class _EXPORT_CLASS GeneratorExtend: virtual public TImplement, public TExtend {
public:
    typedef TImplement Implements;
    typedef TExtend Extends;
    typedef TBIGPRIME BIGPRIME;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    GeneratorExtend() {
#if !defined(_RSA_NO_SMALL_PRIME_TEST)
        m_small_primes = g_small_primes;
        m_small_prime_difference = _RSA_SMALL_PRIME_DIFFERENCE;
#endif // !defined(_CRSA_NO_SMALL_PRIME_TEST)
#if !defined(_RSA_NO_MILLER_RABIN_TEST)
        m_miller_rabin_reps = _RSA_MILLER_RABIN_REPS;
#endif // !defined(_CRSA_NO_MILLER_RABIN_TEST)
    }
    virtual ~GeneratorExtend() {}
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
#if !defined(_RSA_NO_SMALL_PRIME_TEST)
    const unsigned short* m_small_primes;
    long m_small_prime_difference;
    long m_moduli[SMALL_PRIMES_SIZE];
#endif /* !defined(_RSA_NO_SMALL_PRIME_TEST) */
#if !defined(_RSA_NO_MILLER_RABIN_TEST)
    unsigned m_miller_rabin_reps;
#endif /* !defined(_RSA_NO_MILLER_RABIN_TEST) */
};

} // namespace prime
} // namespace random 
} // namespace rsa 
} // namespace crypto 
} // namespace xos 

#endif // _XOS_CRYPTO_RSA_RANDOM_PRIME_GENERATOR_HPP 
