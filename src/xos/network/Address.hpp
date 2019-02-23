///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2012 $organization$
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
///   File: Address.hpp
///
/// Author: $author$
///   Date: Sep 19, 2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_NETWORK_ADDRESS_HPP_
#define _XOS_NETWORK_ADDRESS_HPP_

#include "xos/network/Network.hpp"
#include "xos/base/Base.hpp"
#include <sys/socket.h>
#include <netdb.h>

namespace xos {
namespace network {

typedef InterfaceBase AddressInterfaceImplement;

class _EXPORT_CLASS AddressInterface: virtual public AddressInterfaceImplement {
public:
    typedef AddressInterfaceImplement Implements;
    virtual int GetFamily() const = 0;
};

typedef AddressInterface AddressImplement;
typedef ExportBase AddressExtend;

class _EXPORT_CLASS Address: virtual public AddressImplement, public AddressExtend {
public:
    typedef AddressImplement Implements;
    typedef AddressExtend Extends;

    enum { Family = AF_UNSPEC };

    Address(){}
    virtual ~Address(){}

    virtual int GetFamily() const {
        return Family;
    }
};

} // namespace network
} // namespace xos

#endif // _XOS_NETWORK_ADDRESS_HPP_
