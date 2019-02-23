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
///   File: Literal.hpp
///
/// Author: $author$
///   Date: 1/5/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_BASE_LITERAL_HPP
#define _XOS_BASE_LITERAL_HPP

#include "xos/base/String.hpp"
#include <sstream>

#define XOS_BASE_LITERAL_FALSE "false"
#define XOS_BASE_LITERAL_TRUE "true"

namespace xos {

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS LiteralImplement: virtual public InterfaceBase {
public:
    typedef InterfaceBase Implements;
    typedef int Type;
    enum {
        TypeString,
        TypeBool,
        TypeInt,
        TypeFloat,
        TypeDouble
    };
};
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
template
<typename TChar,
 class TExtend = StringT<TChar> >

class _EXPORT_CLASS LiteralT: virtual public LiteralImplement, public TExtend {
public:
    typedef LiteralImplement Implements;
    typedef TExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    LiteralT(const double& value): m_type(TypeDouble) {
        Assign(value);
    }
    LiteralT(const float& value): m_type(TypeFloat) {
        Assign(value);
    }
    LiteralT(const int& value): m_type(TypeInt) {
        Assign(value);
    }
    LiteralT(const bool& value): m_type(TypeBool) {
        Assign(value);
    }
    LiteralT(const TExtend& value): Extends(value), m_type(TypeString) {
    }
    LiteralT(const TChar* value): Extends(value), m_type(TypeString) {
    }
    LiteralT(const LiteralT& copy): m_type(copy.m_type) {
    }
    LiteralT(): m_type(TypeString) {
    }
    virtual ~LiteralT() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    LiteralT& Assign(const double& value) {
        std::stringstream ss;
        ss << value;
        Extends::Assign(ss.str());
        m_type = TypeDouble;
        return *this;
    }
    LiteralT& Assign(const float& value) {
        std::stringstream ss;
        ss << value;
        Extends::Assign(ss.str());
        m_type = TypeFloat;
        return *this;
    }
    LiteralT& Assign(const int& value) {
        std::stringstream ss;
        ss << value;
        Extends::Assign(ss.str());
        m_type = TypeInt;
        return *this;
    }
    LiteralT& Assign(const bool& value) {
        Extends::Assign((value)?(XOS_BASE_LITERAL_TRUE):(XOS_BASE_LITERAL_FALSE));
        m_type = TypeBool;
        return *this;
    }
    LiteralT& Assign(const TExtend& value) {
        Extends::Assign(value);
        m_type = TypeString;
        return *this;
    }
    LiteralT& Assign(const TChar* value) {
        Extends::Assign(value);
        m_type = TypeString;
        return *this;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Type& type() {
        return (Type&)(m_type);
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    TExtend& To(TExtend& to) const {
        if (TypeString != (m_type)) {
            to.Append(*this);
        } else {
            to.Append("\"");
            to.Append(*this);
            to.Append("\"");
        }
        return to;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    LiteralT& operator = (const TChar* value) {
        return Assign(value);
    }
    LiteralT& operator = (const double& value) {
        return Assign(value);
    }
    LiteralT& operator = (const float& value) {
        return Assign(value);
    }
    LiteralT& operator = (const int& value) {
        return Assign(value);
    }
    LiteralT& operator = (const bool& value) {
        return Assign(value);
    }
    LiteralT& operator = (const TExtend& value) {
        return Assign(value);
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    static const TExtend& True() {
        static const TExtend value(XOS_BASE_LITERAL_TRUE);
        return value;
    }
    static const TExtend& False() {
        static const TExtend value(XOS_BASE_LITERAL_FALSE);
        return value;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    Type m_type;
};

typedef LiteralT<char, String> Literal;

} // namespace xos 

#endif // _XOS_BASE_LITERAL_HPP 
