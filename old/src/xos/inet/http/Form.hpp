///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2013 $organization$
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
///   Date: 11/26/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_INET_HTTP_FORM_HPP
#define _XOS_INET_HTTP_FORM_HPP

#include "xos/inet/http/FormReader.hpp"
#include "xos/base/Named.hpp"

namespace xos {
namespace http {

typedef FormReader::Observer FormImplement;
typedef Base FormExtend;
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Form: virtual public FormImplement, public FormExtend {
public:
    typedef FormImplement Implements;
    typedef FormExtend Extends;

    typedef Named Field;
    typedef NamedList Fields;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Form(const Fields& fields): m_fields(fields) {
    }
    Form(const Form& copy): m_fields(copy.m_fields) {
    }
    Form() {
    }
    virtual ~Form()  {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void OnRead(const String& name,const String& value) {
        XOS_LOG_TRACE("name = \"" << name << "\", value = \"" << value << "\"");
        m_fields.push_back(Field(name, value));
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool GetField(Field& field, const String& name) const {
        Fields::const_iterator b  = m_fields.begin();
        Fields::const_iterator e  = m_fields.end();
        for (Fields::const_iterator i = b; i != e; ++i) {
            const Field& f = *i;
            if (!(f.CompareName(name))) {
                field = f;
                return true;
            }
        }
        return false;
    }
    virtual Fields& fields() const {
        return (Fields&)(m_fields);
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual Form& operator = (const Form& copy) {
        m_fields = copy.m_fields;
        return *this;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    Fields m_fields;
};

} // namespace http 
} // namespace xos 

#endif // _XOS_INET_HTTP_FORM_HPP 
