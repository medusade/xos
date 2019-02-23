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
///   File: Form.hpp
///
/// Author: $author$
///   Date: 5/12/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_INET_ASN1_FORM_HPP
#define _XOS_INET_ASN1_FORM_HPP

#include "xos/inet/asn1/Base.hpp"

namespace xos {
namespace asn1 {

///////////////////////////////////////////////////////////////////////
///    Enum: form_t
///////////////////////////////////////////////////////////////////////
typedef int form_t;
enum {
    FORM_Bit       = (5),

    FORM_Undefined = (-1),
    FORM_Primative = (0),
    FORM_Construct = (1 << FORM_Bit),

    FORM_Mask      = (1 << FORM_Bit)
};

///////////////////////////////////////////////////////////////////////
///  Class: Form
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Form: virtual public Implement, public Base {
public:
    typedef Implement Implements;
    typedef Base Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Form(form_t value = FORM_Primative): m_value(value), m_name(NameOf(value)) {
    }
    virtual ~Form() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual form_t SetValue(form_t to) {
        SetName(NameOf(to));
        return m_value = to;
    }
    virtual form_t Value() const {
        return m_value;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const char* SetName(const char* to) {
        return m_name = to;
    }
    virtual const char* Name() const {
        return m_name;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    static const char* NameOf(form_t ofValue) {
        const char* name = "undefined";
        switch(ofValue) {
        case FORM_Primative:
            return "Primative";

        case FORM_Construct:
            return "Construct";
        }
        return name;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    form_t m_value;
    const char* m_name;
};

} // namespace asn1
} // namespace xos 

#endif // _XOS_INET_ASN1_FORM_HPP 
        

