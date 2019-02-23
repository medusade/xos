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
///   File: Class.hpp
///
/// Author: $author$
///   Date: 5/12/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_INET_ASN1_CLASS_HPP
#define _XOS_INET_ASN1_CLASS_HPP

#include "xos/inet/asn1/Base.hpp"

namespace xos {
namespace asn1 {

///////////////////////////////////////////////////////////////////////
///    Enum: class_t
///////////////////////////////////////////////////////////////////////
typedef int class_t;
enum {
    CLASS_Bit         = (6),

    CLASS_Undefined   = (-1),
    CLASS_Universal   = (0),
    CLASS_Application = (1 << CLASS_Bit),
    CLASS_Context     = (2 << CLASS_Bit),
    CLASS_Private     = (3 << CLASS_Bit),

    CLASS_Mask        = (3 << CLASS_Bit)
};

///////////////////////////////////////////////////////////////////////
///  Class: Class
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Class: virtual public Implement, public Base {
public:
    typedef Implement Implements;
    typedef Base Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Class(class_t value = CLASS_Universal): m_value(value), m_name(NameOf(value)) {
    }
    virtual ~Class() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual class_t SetValue(class_t to) {
        SetName(NameOf(to));
        return m_value = to;
    }
    virtual class_t Value() const {
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
    static const char* NameOf(class_t ofValue) {
        const char* name = "undefined";
        switch(ofValue) {
        case CLASS_Universal:
            return "Universal";

        case CLASS_Application:
            return "Application";

        case CLASS_Context:
            return "Context";

        case CLASS_Private:
            return "Private";
        }
        return name;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    class_t m_value;
    const char* m_name;
};

} // namespace asn1
} // namespace xos 

#endif // _XOS_INET_ASN1_CLASS_HPP 
        

