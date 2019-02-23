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
///   File: Variant.hpp
///
/// Author: $author$
///   Date: 1/5/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_BASE_VARIANT_HPP
#define _XOS_BASE_VARIANT_HPP

#include "xos/base/Literal.hpp"
#include "xos/base/Named.hpp"
#include "xos/os/Logger.hpp"
#include <list>

namespace xos {

class _EXPORT_CLASS Variant;
typedef std::list<Variant> VariantList;
typedef xos::NamedT<Literal, VariantList> VariantExtend;
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Variant: public VariantExtend {
public:
    typedef VariantExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Variant(const String& name, const Variant& value) {
        m_name = name;
        if ((value.value().size())) {
            m_value.push_back(Variant(value.value()));
        } else {
            m_value.push_back(Variant(value.name()));
        }
    }
    Variant(const String& name, const VariantList& value) {
        m_name = name;
        m_value = value;
    }
    Variant(const String& name, const double& value) {
        m_name = name;
        m_value.push_back(Variant(value));
    }
    Variant(const String& name, const float& value) {
        m_name = name;
        m_value.push_back(Variant(value));
    }
    Variant(const String& name, const int& value) {
        m_name = name;
        m_value.push_back(Variant(value));
    }
    Variant(const String& name, const bool& value) {
        m_name = name;
        m_value.push_back(Variant(value));
    }
    Variant(const String& name, const String& value) {
        m_name = name;
        m_value.push_back(Variant(value));
    }
    Variant(const VariantList& value) {
        m_value = value;
    }
    Variant(const double& value) {
        m_name = value;
    }
    Variant(const float& value) {
        m_name = value;
    }
    Variant(const int& value) {
        m_name = value;
    }
    Variant(const bool& value) {
        m_name = value;
    }
    Variant(const String& value) {
        m_name = value;
    }
    Variant(const Variant& copy) {
        m_name = copy.m_name;
        m_value = copy.m_value;
    }
    Variant() {
    }
    virtual ~Variant() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual Variant& Put(const String& name, const Variant& value) {
        m_value.push_back(Variant(name,value));
        return *this;
    }
    virtual Variant& Put(const String& name, const double& value) {
        m_value.push_back(Variant(name,value));
        return *this;
    }
    virtual Variant& Put(const String& name, const float& value) {
        m_value.push_back(Variant(name,value));
        return *this;
    }
    virtual Variant& Put(const String& name, const int& value) {
        m_value.push_back(Variant(name,value));
        return *this;
    }
    virtual Variant& Put(const String& name, const bool& value) {
        m_value.push_back(Variant(name,value));
        return *this;
    }
    virtual Variant& Put(const String& name, const String& value) {
        m_value.push_back(Variant(name,value));
        return *this;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual Variant& Put(const Variant& value) {
        m_value.push_back(Variant(value));
        return *this;
    }
    virtual Variant& Put(const double& value) {
        m_value.push_back(Variant(value));
        return *this;
    }
    virtual Variant& Put(const float& value) {
        m_value.push_back(Variant(value));
        return *this;
    }
    virtual Variant& Put(const int& value) {
        m_value.push_back(Variant(value));
        return *this;
    }
    virtual Variant& Put(const bool& value) {
        m_value.push_back(Variant(value));
        return *this;
    }
    virtual Variant& Put(const String& value) {
        m_value.push_back(Variant(value));
        return *this;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual double& Get(double& value, const String& name) const {
        const Variant* v;
        if ((v = Find(name))) {
            VariantList::const_iterator b = v->m_value.begin();
            if (b != v->m_value.end()) {
                if (!(b->value().size())) {
                    if (Literal::TypeFloat == (b->name().type())) {
                        std::stringstream ss(b->name());
                        ss >> value;
                    }
                }
            }
        }
        return value;
    }
    virtual float& Get(float& value, const String& name) const {
        const Variant* v;
        if ((v = Find(name))) {
            VariantList::const_iterator b = v->m_value.begin();
            if (b != v->m_value.end()) {
                if (!(b->value().size())) {
                    if (Literal::TypeFloat == (b->name().type())) {
                        std::stringstream ss(b->name());
                        ss >> value;
                    }
                }
            }
        }
        return value;
    }
    virtual int& Get(int& value, const String& name) const {
        const Variant* v;
        if ((v = Find(name))) {
            VariantList::const_iterator b = v->m_value.begin();
            if (b != v->m_value.end()) {
                if (!(b->value().size())) {
                    if (Literal::TypeInt == (b->name().type())) {
                        std::stringstream ss(b->name());
                        ss >> value;
                    }
                }
            }
        }
        return value;
    }
    virtual bool& Get(bool& value, const String& name) const {
        const Variant* v;
        if ((v = Find(name))) {
            VariantList::const_iterator b = v->m_value.begin();
            if (b != v->m_value.end()) {
                if (!(b->value().size())) {
                    if (Literal::TypeBool == (b->name().type())) {
                        value = (b->name().Compare(Literal::True()));
                    }
                }
            }
        }
        return value;
    }
    virtual String& Get(String& value, const String& name) const {
        const Variant* v;
        if ((v = Find(name))) {
            VariantList::const_iterator b = v->m_value.begin();
            if (b != v->m_value.end()) {
                if (!(b->value().size())) {
                    value = b->name();
                }
            }
        }
        return value;
    }
    virtual Variant& Get(Variant& value, const String& name) const {
        const Variant* v;
        if ((v = Find(name))) {
            VariantList::const_iterator b = v->m_value.begin();
            if (b != v->m_value.end()) {
                if (!(b->value().size())) {
                    value = b->name();
                }
            }
        }
        return value;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual String& To(String& to) const {
        if ((m_value.size())) {
            VariantList::const_iterator b = m_value.begin();
            VariantList::const_iterator e = m_value.end();
            VariantList::const_iterator i;
            if ((i = b) != e) {
                if ((m_name.Length())) {
                    XOS_LOG_ERROR("unexpected field name");
                } else {
                    if (i->name().Length()) {
                        if (i->value().size()) {
                            XOS_LOG_TRACE("struct {...");
                            to.Append("{");
                            do {
                                if ((i != b)) {
                                    to.Append(",");
                                }
                                i->FieldTo(to);
                            } while (++i != e);
                            to.Append("}");
                            XOS_LOG_TRACE("...} struct");
                        } else {
                            XOS_LOG_ERROR("null field value");
                        }
                    } else {
                        if (i->value().size()) {
                            XOS_LOG_TRACE("array [...");
                            to.Append("[");
                            to.Append("{");
                            do {
                                if ((i != b)) {
                                    to.Append(",");
                                }
                                i->ElementTo(to);
                            } while (++i != e);
                            to.Append("]");
                            XOS_LOG_TRACE("...] array");
                        } else {
                            XOS_LOG_ERROR("null element value");
                        }
                    }
                }
            }
        } else {
            XOS_LOG_TRACE("literal \"" << m_name << "\"");
            m_name.To(to);
        }
        return to;
    }
protected:
    virtual String& FieldTo(String& to) const {
        if ((m_value.size())) {
            VariantList::const_iterator b = m_value.begin();
            VariantList::const_iterator e = m_value.end();
            VariantList::const_iterator i;
            if ((i = b) != e) {
                if ((m_name.Length())) {
                    to.Append("\"");
                    to.Append(m_name);
                    to.Append("\":");
                    XOS_LOG_TRACE("\"" << m_name << "\":");
                    i->To(to);
                } else {
                    XOS_LOG_ERROR("missing field name");
                }
            }
        } else {
            XOS_LOG_ERROR("missing field value");
        }
        return to;
    }
    virtual String& ElementTo(String& to) const {
        if ((m_value.size())) {
            VariantList::const_iterator b = m_value.begin();
            VariantList::const_iterator e = m_value.end();
            VariantList::const_iterator i;
            if ((i = b) != e) {
                if ((m_name.Length())) {
                    XOS_LOG_ERROR("unexpected field name");
                } else {
                    i->To(to);
                }
            }
        } else {
            XOS_LOG_ERROR("missing field value");
        }
        return to;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const Variant* Find(const String& name) const {
        VariantList::const_iterator b = m_value.begin();
        VariantList::const_iterator e = m_value.end();
        if (b != e) {
            if (0 < (b->name().Length())) {
                for (VariantList::const_iterator i = b; i != e; ++i) {
                    const Variant& v = (*i);
                    if (!(name.Compare(v.m_name))) {
                        return &v;
                    }
                }
            }
        }
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace xos

#endif // _XOS_BASE_VARIANT_HPP 
