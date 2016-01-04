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
///   File: Key.hpp
///
/// Author: $author$
///   Date: 1/13/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_CRYPTO_RSA_KEY_HPP
#define _XOS_CRYPTO_RSA_KEY_HPP

#include "xos/base/Created.hpp"

namespace xos {
namespace crypto {
namespace rsa {

typedef InterfaceBase KeyInterface;
typedef ExportBase KeyBase;
///////////////////////////////////////////////////////////////////////
///  Class: KeyImplement
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS KeyImplement: virtual public KeyInterface {
public:
    typedef KeyInterface Implements;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual unsigned SetModBytes(unsigned to) {
        return 0;
    }
    virtual unsigned ModBytes() const {
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef CreatedBaseT<KeyBase, KeyImplement> KeyExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Key
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Key
: virtual public KeyImplement, public KeyExtend {
public:
    typedef KeyImplement Implements;
    typedef KeyExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Key(): m_modbytes(0) {
    }
    virtual ~Key() {
        if (!(Destroyed())) {
            Error error = xos::Error::Failed;
            throw(error);
        }
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual unsigned SetModBytes(unsigned to) {
        return m_modbytes = to;
    }
    virtual unsigned ModBytes() const {
        return m_modbytes;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    unsigned m_modbytes;
};

} // namespace rsa 
} // namespace crypto 
} // namespace xos 

#endif // _XOS_CRYPTO_RSA_KEY_HPP 
