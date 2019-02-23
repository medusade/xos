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
///   File: CipherSuites.hpp
///
/// Author: $author$
///   Date: 4/26/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_TLS_CIPHERSUITES_HPP
#define _XOS_TLS_CIPHERSUITES_HPP

#include "xos/inet/tls/CipherSuite.hpp"

namespace xos {
namespace tls {

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS CipherSuites: virtual public Implement, public Extend {
public:
    typedef Implement Implements;
    typedef Extend Extends;
    typedef tls::Vector<uint16_t, sizeof(uint16_t), uint16_t> Vector;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    CipherSuites(uint16_t which = NULL_WITH_NULL_NULL) {
        set_vector(which);
    }
    virtual ~CipherSuites() {}
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Read(io::Reader& reader) {
        ssize_t count = 0;
        return count;
    }
    virtual ssize_t Write(io::Writer& writer) {
        ssize_t count = 0;
        ssize_t amount = 0;
        XOS_LOG_MESSAGE_DEBUG("" << __XOS_LOGGER_CLASS__ << "::Write()...");
        if (0 < (amount = m_vector.Write(writer))) {
            count += amount;
            XOS_LOG_MESSAGE_DEBUG("..." << count << " = " << __XOS_LOGGER_CLASS__ << "::Write()");
        }
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual Vector& set_vector(uint16_t which) {
        uint8_t bytes[sizeof(uint16_t)];
        for (uint8_t i = 0; i < sizeof(bytes); ++i, which >>= 8) {
            bytes[(sizeof(uint16_t)-1)-i] = (which & 15);
        }
        m_vector.Set(*((uint16_t*)(bytes)), 1);
        return m_vector;
    }
    virtual Vector& set_vector(const Vector& to) {
        m_vector.Assign(to);
        return m_vector;
    }
    virtual const Vector& vector() const {
        return m_vector;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t SizeOf() const {
        ssize_t count = 0;
        count += m_vector.SizeOf();
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    Vector m_vector;
};

} // namespace tls
} // namespace xos 

#endif // _XOS_TLS_CIPHERSUITES_HPP 
