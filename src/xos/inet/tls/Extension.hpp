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
///   File: Extension.hpp
///
/// Author: $author$
///   Date: 4/21/2016
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_INET_TLS_EXTENSION_HPP
#define _XOS_INET_TLS_EXTENSION_HPP

#include "xos/inet/tls/Base.hpp"

namespace xos {
namespace tls {

/* RFC 5246
      struct {
          ExtensionType extension_type;
          opaque extension_data<0..2^16-1>;
      } Extension;

      enum {
          signature_algorithms(13), (65535)
      } ExtensionType;
*/

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS ExtensionType: virtual public Implement, public Extend {
public:
    typedef Implement Implements;
    typedef Extend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    ExtensionType(uint16_t which = EXTENSION_UNKNOWN): m_which(which) {
    }
    ExtensionType(const ExtensionType& copy): m_which(copy.Which()) {
    }
    virtual ~ExtensionType() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual uint16_t SetWhich(uint16_t to) {
        m_which = to;
        return m_which;
    }
    virtual uint16_t Which() const {
        return m_which;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Write(io::Writer& writer) {
        ssize_t count = 0;
        ssize_t amount = 0;
        if (0 < (amount = WriteMsb(writer, m_which, sizeof(m_which)))) {
            count += amount;
        }
        return count;
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
    uint16_t m_which;
};

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Extension: virtual public Implement, public Extend {
public:
    typedef Implement Implements;
    typedef Extend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Extension(uint16_t which = EXTENSION_UNKNOWN): m_extension_type(which) {
    }
    Extension(const ExtensionType& extension_type): m_extension_type(extension_type) {
    }
    Extension(const Extension& copy): m_extension_type(copy.extension_type()) {
    }
    virtual ~Extension() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ExtensionType& set_extension_type(const ExtensionType& to) {
        m_extension_type = to;
        return m_extension_type;
    }
    virtual const ExtensionType& extension_type() const {
        return m_extension_type;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Write(io::Writer& writer) {
        ssize_t count = 0;
        ssize_t amount = 0;
        if (0 < (amount = m_extension_type.Write(writer))) {
            count += amount;
        }
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t SizeOf() const {
        ssize_t count = m_extension_type.SizeOf();
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    ExtensionType m_extension_type;
};

} // namespace tls 
} // namespace xos 

#endif // _XOS_INET_TLS_EXTENSION_HPP 
