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
///   File: CompressionMethods.hpp
///
/// Author: $author$
///   Date: 4/26/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_TLS_COMPRESSIONMETHODS_HPP
#define _XOS_TLS_COMPRESSIONMETHODS_HPP

#include "xos/inet/tls/Base.hpp"

namespace xos {
namespace tls {

typedef uint8_t CompressionMethod;
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS CompressionMethods: virtual public Implement, virtual public Extend {
public:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    CompressionMethods(const uint8_t* method, uint8_t length) {
        m_vector.Assign(method, length);
    }
    CompressionMethods(uint8_t method = COMPRESSION_METHOD_NULL) {
        m_vector.Set(method, 1);
    }
    virtual ~CompressionMethods() {}
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
        if (0 < (amount = m_vector.Write(writer))) {
            count += amount;
        }
        return count;
    }
    virtual ssize_t SizeOf() const {
        ssize_t count = 0;
        count += m_vector.SizeOf();
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    Vector<CompressionMethod, 1, uint8_t> m_vector;
};

} // namespace tls
} // namespace xos 

#endif // _XOS_TLS_COMPRESSIONMETHODS_HPP 
