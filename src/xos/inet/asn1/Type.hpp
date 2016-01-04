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
///   File: Type.hpp
///
/// Author: $author$
///   Date: 5/12/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_INET_ASN1_TYPE_HPP
#define _XOS_INET_ASN1_TYPE_HPP

#include "xos/inet/asn1/Base.hpp"
#include "xos/inet/asn1/Form.hpp"
#include "xos/inet/asn1/Class.hpp"
#include "xos/io/Reader.hpp"

namespace xos {
namespace asn1 {

///////////////////////////////////////////////////////////////////////
///    Enum: type_t
///////////////////////////////////////////////////////////////////////
typedef int type_t;
enum {
    TYPE_Bit             = (0),

    TYPE_Undefined       = (-1),
    TYPE_Any             = (0),
    TYPE_Boolean         = (1),
    TYPE_Integer         = (2),
    TYPE_BitString       = (3),
    TYPE_OctetString     = (4),
    TYPE_Null            = (5),
    TYPE_ObjectID        = (6),
    TYPE_Object          = (7),
    TYPE_External        = (8),
    TYPE_Real            = (9),
    TYPE_Enum            = (10),

    TYPE_Sequence        = (16),
    TYPE_Set             = (17),
    TYPE_NumericString   = (18),
    TYPE_PrintableString = (19),
    TYPE_TeletexString   = (20),
    TYPE_VideotexString  = (21),
    TYPE_IA5String       = (22),
    TYPE_UTCTime         = (23),
    TYPE_GeneralizedTime = (24),
    TYPE_GraphicString   = (25),
    TYPE_VisibleString   = (26),
    TYPE_GeneralString   = (27),

    TYPE_Mask            = (31)
};

///////////////////////////////////////////////////////////////////////
///  Class: Type
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Type: virtual public Implement, public Base {
public:
    typedef Implement Implements;
    typedef Base Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Type
    (type_t value = TYPE_Any,
     form_t formValue = FORM_Primative,
     class_t classValue = CLASS_Universal)
    : m_value(value), m_name(NameOf(value)),
      m_form(formValue), m_class(classValue) {
    }
    Type(const Type& copy) {
        Copy(copy);
    }
    virtual ~Type() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Read(io::BYTEReader& reader) {
        ssize_t count = 0;
        BYTE byte;
        if (0 < (count = reader.Read(&byte, 1))) {
            m_form.SetValue(byte & FORM_Mask);
            m_class.SetValue(byte & CLASS_Mask);
            SetValue(byte & TYPE_Mask);
        }
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual Type& Copy(const Type& copy) {
        Set(copy.Value(), copy.m_form.Value(), copy.m_class.Value());
        *this;
    }
    virtual type_t Set(type_t toValue, form_t toFormValue, class_t toClassValue) {
        m_class.SetValue(toClassValue);
        m_form.SetValue(toFormValue);
        return SetValue(toValue);
    }
    virtual class_t Class() const {
        return m_class.Value();
    }
    virtual form_t Form() const {
        return m_form.Value();
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual type_t SetValue(type_t to) {
        SetName(NameOf(to));
        return m_value = to;
    }
    virtual type_t Value() const {
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
    static const char* NameOf(type_t ofValue) {
        static const char* name0[] = {
            "Any",
            "Boolean",
            "Integer",
            "BitString",
            "OctetString",
            "Null",
            "ObjectID",
            "Object",
            "External",
            "Real",
            "Enum"
         };
        static const CHAR* name1[] = {
            "Sequence",
            "Set",
            "NumericString",
            "PrintableString",
            "TeletexString",
            "VideotexString",
            "IA5String",
            "UTCTime",
            "GeneralizedTime",
            "GraphicString",
            "VisibleString",
            "GeneralString"
         };
        const char* name = "undefined";

        if ((ofValue >= TYPE_Any) && (ofValue <= TYPE_Enum)) {
            name = name0[ofValue - TYPE_Any];
        } else {
            if ((ofValue >= TYPE_Sequence) && (ofValue <= TYPE_GeneralString)) {
                name = name1[ofValue - TYPE_Sequence];
            }
        }
        return name;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    type_t m_value;
    const char* m_name;
    asn1::Form m_form;
    asn1::Class m_class;
};

} // namespace asn1
} // namespace xos 

#endif // _XOS_INET_ASN1_TYPE_HPP 
