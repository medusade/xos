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
///   File: Transport.hpp
///
/// Author: $author$
///   Date: 9/22/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_NETWORK_IP_TRANSPORT_HPP_
#define _XOS_NETWORK_IP_TRANSPORT_HPP_

#include "xos/network/Transport.hpp"
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <netdb.h>

namespace xos {
namespace network {
namespace ip {

typedef network::TransportImplement TransportImplement;
typedef network::Transport TransportExtend;

class _EXPORT_CLASS Transport: virtual public TransportImplement, public TransportExtend {
public:
    typedef TransportImplement Implements;
    typedef TransportExtend Extends;

    enum { Protocol = IPPROTO_RAW };

    Transport(){}
    virtual ~Transport(){}

    virtual int GetProtocol() const {
        return Protocol;
    }
};

} // namespace ip 
} // namespace network 
} // namespace xos 

#endif // _XOS_NETWORK_IP_TRANSPORT_HPP_ 
        

