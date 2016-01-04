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
///   File: ProtocolVersion.hpp
///
/// Author: $author$
///   Date: 4/25/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_TLS_PROTOCOLVERSION_HPP
#define _XOS_TLS_PROTOCOLVERSION_HPP

#include "xos/inet/tls/Base.hpp"

namespace xos {
namespace tls {

/* RFC 2246
    struct {
        uint8 major, minor;
    } ProtocolVersion;
*/

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS ProtocolVersion: virtual public Implement, virtual public Extend {
public:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    ProtocolVersion
    (uint8_t major = TLS_PROTOCOL_VERSION_MAJOR,
     uint8_t minor = TLS_PROTOCOL_VERSION_MINOR)
    : m_major(major), m_minor(minor) {}
    virtual ~ProtocolVersion() {}
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Read(io::Reader& reader) {
        ssize_t count = 0;
        return count;
    }
    virtual ssize_t Write(io::Writer& writer) {
        ssize_t count = 0;
        ssize_t amount = 0;
        XOS_LOG_DEBUG("class " << __XOS_LOGGER_CLASS__ << "...");
        if (0 < (amount = WriteMsb(writer, m_major, 1))) {
            count += amount;
            if (0 < (amount = WriteMsb(writer, m_minor, 1))) {
                count += amount;
            }
        }
        return count;
    }
    virtual ssize_t SizeOf() const {
        ssize_t count = 0;
        count += sizeof(m_major);
        count += sizeof(m_minor);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    uint8_t m_major, m_minor;
};

} // namespace tls
} // namespace xos 

#endif // _XOS_TLS_PROTOCOLVERSION_HPP 
