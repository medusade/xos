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
///   File: Random.hpp
///
/// Author: $author$
///   Date: 4/26/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_TLS_RANDOM_HPP
#define _XOS_TLS_RANDOM_HPP

#include "xos/inet/tls/GmtUnixTime.hpp"
#include "xos/inet/tls/Base.hpp"

namespace xos {
namespace tls {

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Random: virtual public Implement, public Extend {
public:
    typedef Implement Implements;
    typedef Extend Extends;
    enum { Size = 28 };
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Random
    (uint32_t gmt_unix_time, const opaque_t* random_bytes, size_t length)
    : m_gmt_unix_time(gmt_unix_time) {
        set_random_bytes(random_bytes, length);
    }
    Random
    (uint32_t gmt_unix_time, opaque_t random_byte)
    : m_gmt_unix_time(gmt_unix_time) {
        set_random_bytes(random_byte);
    }
    Random
    (const GmtUnixTime& gmt_unix_time, const Random& copy)
    : m_gmt_unix_time(gmt_unix_time) {
        set_random_bytes(copy.random_bytes(), Size);
    }
    Random(opaque_t random_byte = 0)
    : m_gmt_unix_time(0) {
        set_random_bytes(random_byte);
    }
    virtual ~Random() {}
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Read(io::Reader& reader) {
        ssize_t count = 0;
        ssize_t amount = 0;
        XOS_LOG_MESSAGE_DEBUG("" << __XOS_LOGGER_CLASS__ << "::Read()...");
        if (0 < (amount = m_gmt_unix_time.Read(reader))) {
            count += amount;
            if (0 < (amount = ReadOpaque(reader, m_random_bytes, Size))) {
                count += amount;
                XOS_LOG_MESSAGE_DEBUG("..." << count << " = " << __XOS_LOGGER_CLASS__ << "::Read()");
            }
        }
        return count;
    }
    virtual ssize_t Write(io::Writer& writer) {
        ssize_t count = 0;
        ssize_t amount = 0;
        XOS_LOG_MESSAGE_DEBUG("" << __XOS_LOGGER_CLASS__ << "::Write()...");
        if (0 < (amount = m_gmt_unix_time.Write(writer))) {
            count += amount;
            if (0 < (amount = WriteOpaque(writer, m_random_bytes, Size))) {
                count += amount;
                XOS_LOG_MESSAGE_DEBUG("..." << count << " = " << __XOS_LOGGER_CLASS__ << "::Write()");
            }
        }
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual opaque_t* set_random_bytes(const opaque_t* to, size_t length) {
        if ((to) && (length)) {
            for (size_t remain = Size; remain; remain -= length) {
                if (remain < (length)) {
                    length = remain;
                }
                Opaques::Copy(m_random_bytes, to, length);
            }
        }
        return m_random_bytes;
    }
    virtual opaque_t* set_random_bytes(opaque_t to) {
        Opaques::Set(m_random_bytes, to, Size);
        return m_random_bytes;
    }
    virtual const opaque_t* random_bytes() const {
        return m_random_bytes;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t SizeOf() const {
        ssize_t count = 0;
        count += m_gmt_unix_time.SizeOf();
        count += Size;
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    GmtUnixTime m_gmt_unix_time;
    opaque_t m_random_bytes[Size];
};

} // namespace tls
} // namespace xos 

#endif // _XOS_TLS_RANDOM_HPP 
