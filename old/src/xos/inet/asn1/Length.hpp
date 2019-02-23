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
///   File: Length.hpp
///
/// Author: $author$
///   Date: 5/12/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_INET_ASN1_LENGTH_HPP
#define _XOS_INET_ASN1_LENGTH_HPP

#include "xos/inet/asn1/Base.hpp"
#include "xos/io/Reader.hpp"

namespace xos {
namespace asn1 {

///////////////////////////////////////////////////////////////////////
///  Class: Length
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Length: virtual public Implement, public Base {
public:
    typedef Implement Implements;
    typedef Base Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Length(size_t value = 0, BYTE size = 0, bool isIndefinite = false)
    : m_value(value), m_size(size), m_isIndefinite(isIndefinite) {
    }
    Length(const Length& copy) {
        Copy(copy);
    }
    virtual ~Length() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Read(io::BYTEReader& reader) {
        ssize_t count = 0;
        ssize_t amount;
        BYTE bytes;
        BYTE byte;

        if (0 < (count = reader.Read(&byte, 1))) {
            m_isIndefinite = false;
            m_size = 1;

            if (byte < 128) {
                m_value = byte;
             } else {
                m_value = 0;

                if (byte > 128) {
                    for (bytes = (byte & 127); (bytes > 0); --bytes, m_size++, count++) {
                        if  (0 >= (amount = reader.Read(&byte, 1))) {
                            return amount;
                        }
                        m_value = (m_value << 8) | byte;
                    }
                } else {
                    m_isIndefinite = true;
                }
            }
        }
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual Length& Copy(const Length& copy) {
        m_value = copy.Value();
        m_size = copy.Size();
        m_isIndefinite = copy.IsIndefinite();
        *this;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual size_t Value() const {
        return m_value;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual size_t Size() const {
        return m_size;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool IsIndefinite() const {
        return m_isIndefinite;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    bool m_isIndefinite;
    size_t m_value;
    size_t m_size;
};

} // namespace asn1 
} // namespace xos 

#endif // _XOS_INET_ASN1_LENGTH_HPP 
