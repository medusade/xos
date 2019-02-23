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
///   File: Endpoint.hpp
///
/// Author: $author$
///   Date: 9/26/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_NETWORK_IP_ENDPOINT_HPP
#define _XOS_NETWORK_IP_ENDPOINT_HPP

#include "xos/network/Endpoint.hpp"

namespace xos {
namespace network {
namespace ip {

typedef network::Endpoint EndpointImplement;

class _EXPORT_CLASS Endpoint
: virtual public EndpointImplement
{
public:
    typedef EndpointImplement Implements;
};

} // namespace xos 
} // namespace network 
} // namespace ip 

#endif // _XOS_NETWORK_IP_ENDPOINT_HPP 
