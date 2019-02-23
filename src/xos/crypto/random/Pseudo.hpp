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
///   File: Pseudo.hpp
///
/// Author: $author$
///   Date: 2/18/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_CRYPTO_RANDOM_PSEUDO_HPP
#define _XOS_CRYPTO_RANDOM_PSEUDO_HPP

#include "xos/crypto/random/Generator.hpp"
#include "xos/crypto/Reader.hpp"
#include "xos/os/Logger.hpp"
#include "thirdparty/gnu/glibc/stdlib/rand_r.h"

namespace xos {
namespace crypto {
namespace random {

///////////////////////////////////////////////////////////////////////
///  Class: Pseudo
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS PseudoImplement
: virtual public Generator, virtual public Reader {
};
typedef ExportBase PseudoExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Pseudo
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Pseudo: virtual public PseudoImplement, public PseudoExtend {
public:
    typedef PseudoImplement Implements;
    typedef PseudoExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Pseudo(unsigned seed): m_avail(0), m_seed(seed), m_rand(0) {
    }
    Pseudo(): m_avail(0), m_seed(0), m_rand(0) {
    }
    virtual ~Pseudo() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Generate(void* out, size_t size) {
        uint8_t* bytes;

        if ((bytes = (uint8_t*)(out))) {
            size_t i, j, count, length;

            for (length = 0; length < size; ) {

                if (1 > m_avail) {
                    if (!(m_seed)) {
                        time_t t = time(&t);
                        m_seed = (unsigned)(t);
                        XOS_LOG_TRACE("seed = " << m_seed);
                    }
                    m_rand = (unsigned)rand_r(&m_seed);
                    m_avail = sizeof(m_rand);
                    XOS_LOG_TRACE("rand = " << m_rand);
                }

                if ((count = size-length) > m_avail)
                    count = m_avail;

                for (j = 0, i = 0; i < count; ++i) {
                    if ((bytes[length+j] = (uint8_t)(m_rand & 0xFF))) {
                        ++j;
                    }
                    m_rand >>= 8;
                }

                length += j;
                m_avail -= count;
            }
            return size;
        }
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Read(BYTE* bytes, size_t size) {
        return Generate(bytes, size);
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual unsigned Seed(unsigned seed) {
        m_seed = seed;
        m_avail = 0;
        m_rand = 0;
        return m_seed;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    size_t m_avail;
    unsigned m_seed;
    unsigned m_rand;
};

} // namespace random 
} // namespace crypto 
} // namespace xos 

#endif // _XOS_CRYPTO_RANDOM_PSEUDO_HPP 
