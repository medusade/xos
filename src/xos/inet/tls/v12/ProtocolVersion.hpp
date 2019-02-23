///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2016 $organization$
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
///   File: ProtocolVersion.hpp
///
/// Author: $author$
///   Date: 4/21/2016
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_INET_TLS_V12_PROTOCOLVERSION_HPP
#define _XOS_INET_TLS_V12_PROTOCOLVERSION_HPP

#include "xos/inet/tls/ProtocolVersion.hpp"

namespace xos {
namespace tls {
namespace v12 {

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS ProtocolVersion
: virtual public tls::ProtocolVersion::Implements, public tls::ProtocolVersion {
public:
    typedef tls::ProtocolVersion::Implements Implements;
    typedef tls::ProtocolVersion Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    ProtocolVersion
    (uint8_t major = TLS_PROTOCOL_VERSION_1_MAJOR,
     uint8_t minor = TLS_PROTOCOL_VERSION_1_2_MINOR): Extends(major, minor) {
    }
    virtual ~ProtocolVersion() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace v12 
} // namespace tls 
} // namespace xos 

#endif // _XOS_INET_TLS_V12_PROTOCOLVERSION_HPP 
