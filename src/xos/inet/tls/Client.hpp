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
///   File: Client.hpp
///
/// Author: $author$
///   Date: 4/26/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_TLS_CLIENT_HPP
#define _XOS_TLS_CLIENT_HPP

#include "xos/inet/tls/ClientHello.hpp"
#include "xos/inet/tls/Connection.hpp"

namespace xos {
namespace tls {

typedef ConnectionImplements ClientImplements;
typedef Connection ClientExtends;
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Client: virtual public ClientImplements, public ClientExtends {
public:
    typedef ClientImplements Implements;
    typedef ClientExtends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Client(io::Reader& reader, io::Writer& writer)
    : Extends(reader, writer) {
    }
    virtual ~Client() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace tls
} // namespace xos 

#endif // _XOS_TLS_CLIENT_HPP 
