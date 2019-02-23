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
///   Date: 5/5/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_CRYPTO_RANDOM_GENERATOR_HPP
#define _XOS_CRYPTO_RANDOM_GENERATOR_HPP

#include "xos/crypto/random/Interface.hpp"

namespace xos {
namespace crypto {
namespace random {

typedef Interface GeneratorImplement;
///////////////////////////////////////////////////////////////////////
///  Class: Generator
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Generator: virtual public GeneratorImplement {
public:
    typedef GeneratorImplement Implements;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Generate(void* out, size_t outSize) {
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace random 
} // namespace crypto 
} // namespace xos 

#endif // _XOS_CRYPTO_RANDOM_GENERATOR_HPP 
