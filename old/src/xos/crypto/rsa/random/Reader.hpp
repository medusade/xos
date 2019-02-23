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
///   File: Reader.hpp
///
/// Author: $author$
///   Date: 4/29/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_CRYPTO_RSA_RANDOM_READER_HPP
#define _XOS_CRYPTO_RSA_RANDOM_READER_HPP

#include "xos/crypto/Reader.hpp"

namespace xos {
namespace crypto {
namespace rsa {
namespace random {

typedef InterfaceBase ReaderImplement;
///////////////////////////////////////////////////////////////////////
///  Class: Reader
///////////////////////////////////////////////////////////////////////
template <typename TBIGPRIME, class TImplement = ReaderImplement>
class _EXPORT_CLASS Reader: virtual public TImplement {
public:
    typedef TImplement Implements;
    typedef TBIGPRIME BIGPRIME;

    typedef InterfaceBase ObserverImplement;
    ///////////////////////////////////////////////////////////////////////
    ///  Class: Observer
    ///////////////////////////////////////////////////////////////////////
    class _EXPORT_CLASS Observer: virtual public ObserverImplement {
    public:
        typedef ObserverImplement Implements;
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        virtual ssize_t OnRead(BIGPRIME* n, size_t bytes) {
            Observer* delegated = ObserverDelegated(n);
            if ((delegated))
                return delegated->OnRead(n, bytes);
            return bytes;
        }
        virtual Observer* ObserverDelegated(BIGPRIME* n) const {
            return 0;
        }
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
    };

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t ReadMSB(BIGPRIME* n, size_t bytes, crypto::Reader& reader) {
        return 0;
    }
    virtual ssize_t Get(BYTE& byte, crypto::Reader& reader) {
        ssize_t count = 0;
#if !defined(_RSA_NO_REMOVE_ZEROS)
            do {
#endif // !defined(_RSA_NO_REMOVE_ZEROS)
                if (0 >= (count = reader.Read(&byte, 1)))
                    return count;
#if !defined(_RSA_NO_REMOVE_ZEROS)
            } while (!(byte & 0xF) || !(byte & 0xF0));
#endif // !defined(_CRSA_NO_REMOVE_ZEROS)
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace random 
} // namespace rsa 
} // namespace crypto 
} // namespace xos 

#endif // _XOS_CRYPTO_RSA_RANDOM_READER_HPP 
