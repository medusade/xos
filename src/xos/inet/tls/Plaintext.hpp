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
///   File: Plaintext.hpp
///
/// Author: $author$
///   Date: 4/26/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_TLS_PLAINTEXT_HPP
#define _XOS_TLS_PLAINTEXT_HPP

#include "xos/inet/tls/ContentType.hpp"
#include "xos/inet/tls/ProtocolVersion.hpp"

namespace xos {
namespace tls {

/* RFC 2246
    struct {
        ContentType type;
        ProtocolVersion version;
        uint16 length;
        opaque fragment[TLSPlaintext.length];
    } TLSPlaintext;
*/

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Plaintext: virtual public Implement, virtual public Extend {
public:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Plaintext(const ContentType& type, const ProtocolVersion& version)
    : m_type(type), m_version(version) {}
    Plaintext() {}
    virtual ~Plaintext() {}
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Read(io::Reader& reader) {
        ssize_t count = 0;
        ssize_t amount = 0;
        XOS_LOG_DEBUG("class " << __XOS_LOGGER_CLASS__ << "...");
        if (0 < (amount = ReadMsb(reader, m_type, sizeof(m_type)))) {
            count += amount;
            if (0 < (amount = m_version.Read(reader))) {
                count += amount;
                if (0 < (amount = m_fragment.Read(reader))) {
                    count += amount;
                }
            }
        }
        return count;
    }
    virtual ssize_t Write(io::Writer& writer) {
        ssize_t count = 0;
        ssize_t amount = 0;
        XOS_LOG_DEBUG("class " << __XOS_LOGGER_CLASS__ << "...");
        if (0 < (amount = WriteMsb(writer, m_type, sizeof(m_type)))) {
            count += amount;
            if (0 < (amount = m_version.Write(writer))) {
                count += amount;
                if (0 < (amount = m_fragment.Write(writer))) {
                    count += amount;
                }
            }
        }
        return count;
    }
    virtual ssize_t Write(io::Writer& writer, Implement& fragment) {
        ssize_t count = 0;
        ssize_t amount = 0;
        XOS_LOG_DEBUG("class " << __XOS_LOGGER_CLASS__ << "...");
        if (0 < (amount = WriteMsb(writer, m_type, sizeof(m_type)))) {
            count += amount;
            if (0 < (amount = m_version.Write(writer))) {
                count += amount;
                if (0 < (amount = fragment.SizeOf())) {
                    uint16_t length = (uint16_t)(amount);
                    XOS_LOG_DEBUG("fragment length = " << length << "");
                    if (0 < (amount = WriteMsb(writer, length, sizeof(uint16_t)))) {
                        count += amount;
                        if (0 < (amount = fragment.Write(writer))) {
                            count += amount;
                        }
                    }
                }
            }
        }
        return count;
    }
    virtual ssize_t SizeOf() const {
        ssize_t count = 0;
        count += sizeof(m_type);
        count += m_version.SizeOf();
        count += m_fragment.SizeOf();
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    ContentType m_type;
    ProtocolVersion m_version;
    Vector<opaque, 2, uint16_t> m_fragment;
};

} // namespace tls
} // namespace xos 

#endif // _XOS_TLS_PLAINTEXT_HPP 
