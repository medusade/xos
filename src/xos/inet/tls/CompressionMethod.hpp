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
///   File: CompressionMethod.hpp
///
/// Author: $author$
///   Date: 4/24/2016
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_INET_TLS_COMPRESSIONMETHOD_HPP
#define _XOS_INET_TLS_COMPRESSIONMETHOD_HPP

#include "xos/inet/tls/Base.hpp"

namespace xos {
namespace tls {

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS CompressionMethod: virtual public Implement, public Extend {
public:
    typedef Implement Implements;
    typedef Extend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    CompressionMethod(uint8_t which = COMPRESSION_METHOD_NULL): m_which(which) {
    }
    CompressionMethod(const CompressionMethod& copy): m_which(copy.which()) {
    }
    virtual ~CompressionMethod() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Read(io::Reader& reader) {
        ssize_t count = 0;
        ssize_t amount = 0;
        XOS_LOG_MESSAGE_DEBUG("" << __XOS_LOGGER_CLASS__ << "::ReadMsb()...");
        if (0 < (amount = ReadMsb(reader, m_which, sizeof(m_which)))) {
            XOS_LOG_MESSAGE_DEBUG("...which = " << m_which << " on " << __XOS_LOGGER_CLASS__ << "::ReadMsb()");
            count += amount;
        }
        return count;
    }
    virtual ssize_t Write(io::Writer& writer) {
        ssize_t count = 0;
        ssize_t amount = 0;
        XOS_LOG_MESSAGE_DEBUG("" << __XOS_LOGGER_CLASS__ << "::WriteMsb()...");
        if (0 < (amount = WriteMsb(writer, m_which, sizeof(m_which)))) {
            XOS_LOG_MESSAGE_DEBUG("..." << amount << " = " << __XOS_LOGGER_CLASS__ << "::WriteMsb()");
            count += amount;
        }
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual uint8_t set_which(uint8_t to) {
        return m_which;
    }
    virtual uint8_t which() const {
        return m_which;
    }
    virtual operator uint8_t() const {
        return m_which;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t SizeOf() const {
        ssize_t count = sizeof(m_which);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    uint8_t m_which;
};

} // namespace tls 
} // namespace xos 

#endif // _XOS_INET_TLS_COMPRESSIONMETHOD_HPP 
