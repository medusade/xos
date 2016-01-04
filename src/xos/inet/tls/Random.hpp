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

#include "xos/inet/tls/Base.hpp"

namespace xos {
namespace tls {

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Random: virtual public Implement, virtual public Extend {
public:
    enum { Size = 28 };
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Random
    (uint32_t gmt_unix_time, const opaque* random_bytes, size_t length)
    : m_gmt_unix_time(gmt_unix_time) {
        if (Size < (length))
            length = Size;
        Opaque::Copy(m_random_bytes, random_bytes, length);
    }
    Random
    (uint32_t gmt_unix_time, opaque random_byte)
    : m_gmt_unix_time(gmt_unix_time) {
        Opaque::Set(m_random_bytes, random_byte, Size);
    }
    Random()
    : m_gmt_unix_time(0) {
        Opaque::Set(m_random_bytes, 0, Size);
    }
    virtual ~Random() {}
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
        if (0 < (amount = m_gmt_unix_time.Write(writer))) {
            count += amount;
            if (0 < (amount = WriteOpaque(writer, m_random_bytes, Size))) {
                count += amount;
            }
        }
        return count;
    }
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
    opaque m_random_bytes[Size];
};

} // namespace tls
} // namespace xos 

#endif // _XOS_TLS_RANDOM_HPP 
