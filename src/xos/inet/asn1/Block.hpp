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
///   File: Block.hpp
///
/// Author: $author$
///   Date: 5/12/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_INET_ASN1_BLOCK_HPP
#define _XOS_INET_ASN1_BLOCK_HPP

#include "xos/inet/asn1/Length.hpp"
#include "xos/inet/asn1/Type.hpp"
#include "xos/inet/asn1/Form.hpp"
#include "xos/inet/asn1/Class.hpp"
#include "xos/inet/asn1/Base.hpp"

namespace xos {
namespace asn1 {

///////////////////////////////////////////////////////////////////////
///  Class: Block
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Block: virtual public Implement, public Base {
public:
    typedef Implement Implements;
    typedef Base Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Block() {
    }
    virtual ~Block() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Read(io::BYTEReader& reader) {
        ssize_t count = 0;
        ssize_t amount;
        if (0 < (count = m_type.Read(reader))) {
            if (0 >= (amount = m_length.Read(reader))) {
                return amount;
            } else {
                count += amount;
            }
        }
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual class_t Class() const {
        return (m_type.Class());
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual form_t Form() const {
        return (m_type.Form());
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual type_t Type() const {
        return (m_type.Value());
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual size_t Length() const {
        return (m_length.Value());
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual size_t Size() const {
        return (m_length.Value()+m_length.Size()+m_type.Size());
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    asn1::Type m_type;
    asn1::Length m_length;
};

} // namespace asn1 
} // namespace xos 

#endif // _XOS_INET_ASN1_BLOCK_HPP 
