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
///   File: ToVariant.hpp
///
/// Author: $author$
///   Date: 1/6/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_JSON_LIBJSON_TOVARIANT_HPP
#define _XOS_JSON_LIBJSON_TOVARIANT_HPP

#include "xos/base/Variant.hpp"
#include <libjson.h>

namespace xos {
namespace json {
namespace libjson {

typedef InterfaceBase ToVariantImplement;
typedef Base ToVariantExtend;
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
template
<typename TVariant,
 class TExtend = ToVariantExtend,
 class TImplement = ToVariantImplement>

class _EXPORT_CLASS ToVariantT
: virtual public TImplement, public TExtend {
public:
    typedef TImplement Implements;
    typedef TExtend Extends;
    typedef ToVariantT Derives;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    ToVariantT(TVariant& to,const String& from): m_to(0), m_v(0) {
        To(to, from);
    }
    ToVariantT(): m_to(0), m_v(0) {
    }
    virtual ~ToVariantT() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual TVariant& To(TVariant& to,const String& from) {
        m_v = &to;
        m_to = &Derives::ToValue;
        To(from);
        m_to = 0;
        m_v = 0;
        return to;
    }
protected:
    virtual void To(const String& from) {
        const char* json;
        if ((json = from.Chars()) && (0 < from.Length())) {
            JSONNODE* node;
            if ((node = json_parse(json))) {
                ToValue(node);
            }
        }
    }
    virtual void Iterate(JSONNODE* node) {
        JSONNODE_ITERATOR begin = json_begin(node);
        JSONNODE_ITERATOR end = json_end(node);
        for (JSONNODE_ITERATOR i = begin; i != end; ++i) {
            if ((m_to)) {
                (this->*m_to)(*i);
            }
        }
    }
    virtual void ToValue(JSONNODE* node) {
        char type = json_type(node);
        switch (type) {
        case JSON_NODE:
            XOS_LOG_TRACE("JSON_NODE...");
            {
                MTo oldTo = m_to;
                m_to = &Derives::ToStruct;
                Iterate(node);
                m_to = oldTo;
            }
            XOS_LOG_TRACE("...JSON_NODE");
            break;
        case JSON_ARRAY:
            XOS_LOG_TRACE("JSON_ARRAY...");
            {
                MTo oldTo = m_to;
                m_to = &Derives::ToArray;
                Iterate(node);
                m_to = oldTo;
            }
            XOS_LOG_TRACE("...JSON_ARRAY");
            break;
        case JSON_STRING:
        case JSON_NUMBER:
        case JSON_BOOL:
        case JSON_NULL:
            {
                json_char *value;
                switch (type) {
                case JSON_STRING:
                    XOS_LOG_TRACE("JSON_STRING");
                    if ((value = json_as_string(node))) {
                        XOS_LOG_TRACE("value = \"" << value << "\"");
                        m_v->Put(String(value));
                        json_free(value);
                    }
                    break;
                case JSON_NUMBER:
                    XOS_LOG_TRACE("JSON_NUMBER");
                    m_v->Put((int)(json_as_int(node)));
                    break;
                case JSON_BOOL:
                    XOS_LOG_TRACE("JSON_BOOL");
                    m_v->Put(json_as_bool(node));
                    break;
                case JSON_NULL:
                    XOS_LOG_TRACE("JSON_NULL");
                    m_v->Put(0);
                    break;
                }
            }
            break;
        default:
            XOS_LOG_ERROR("invalid node type" << type);
        }
    }
    virtual void ToStruct(JSONNODE* node) {
        char type = json_type(node);
        switch (type) {
        case JSON_NODE:
            XOS_LOG_TRACE("JSON_NODE...");
            {
                TVariant* oldV = m_v;
                TVariant v;
                json_char *name;
                if ((name = json_name(node))) {
                    XOS_LOG_TRACE("name = \"" << name << "\"");
                    json_free(name);
                    m_v = &v;
                    Iterate(node);
                    m_v = oldV;
                    if ((name = json_name(node))) {
                        m_v->Put(name, v);
                        json_free(name);
                    }
                }
            }
            XOS_LOG_TRACE("...JSON_NODE");
            break;
        case JSON_ARRAY:
            XOS_LOG_TRACE("JSON_ARRAY...");
            {
                MTo oldTo = m_to;
                TVariant* oldV = m_v;
                TVariant v;
                json_char *name;
                if ((name = json_name(node))) {
                    XOS_LOG_TRACE("name = \"" << name << "\"");
                    json_free(name);
                    m_v = &v;
                    m_to = &Derives::ToArray;
                    Iterate(node);
                    m_to = oldTo;
                    m_v = oldV;
                    if ((name = json_name(node))) {
                        m_v->Put(name, v);
                        json_free(name);
                    }
                }
            }
            XOS_LOG_TRACE("...JSON_ARRAY");
            break;
        case JSON_STRING:
        case JSON_NUMBER:
        case JSON_BOOL:
        case JSON_NULL:
            {
                json_char *name, *value;
                if ((name = json_name(node))) {
                    XOS_LOG_TRACE("name = \"" << name << "\"");
                    switch (type) {
                    case JSON_STRING:
                        XOS_LOG_TRACE("JSON_STRING");
                        if ((value = json_as_string(node))) {
                            XOS_LOG_TRACE("value = \"" << value << "\"");
                            m_v->Put(name, String(value));
                            json_free(value);
                        }
                        break;
                    case JSON_NUMBER:
                        XOS_LOG_TRACE("JSON_NUMBER");
                        m_v->Put(name, (int)(json_as_int(node)));
                        break;
                    case JSON_BOOL:
                        XOS_LOG_TRACE("JSON_BOOL");
                        m_v->Put(name, json_as_bool(node));
                        break;
                    case JSON_NULL:
                        XOS_LOG_TRACE("JSON_NULL");
                        m_v->Put(name, 0);
                        break;
                    }
                    json_free(name);
                }
            }
            break;
        default:
            XOS_LOG_ERROR("invalid node type" << type);
        }
    }
    virtual void ToArray(JSONNODE* node) {
        char type = json_type(node);
        switch (type) {
        case JSON_NODE:
            XOS_LOG_TRACE("JSON_NODE...");
            {
                MTo oldTo = m_to;
                TVariant* oldV = m_v;
                TVariant v;
                m_v = &v;
                m_to = &Derives::ToStruct;
                Iterate(node);
                m_to = oldTo;
                m_v = oldV;
                m_v->Put(v);
            }
            XOS_LOG_TRACE("...JSON_NODE");
            break;
        case JSON_ARRAY:
            XOS_LOG_TRACE("JSON_ARRAY...");
            {
                TVariant* oldV = m_v;
                TVariant v;
                m_v = &v;
                Iterate(node);
                m_v = oldV;
                m_v->Put(v);
            }
            XOS_LOG_TRACE("...JSON_ARRAY");
            break;
        case JSON_STRING:
        case JSON_NUMBER:
        case JSON_BOOL:
        case JSON_NULL:
            ToValue(node);
            break;
        default:
            XOS_LOG_ERROR("invalid node type" << type);
        }
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    typedef void (Derives::*MTo)(JSONNODE* node);
protected:
    MTo m_to;
    TVariant* m_v;
};

typedef ToVariantT<Variant> ToVariant;

} // namespace libjson
} // namespace json 
} // namespace xos 

#endif // _XOS_JSON_LIBJSON_TOVARIANT_HPP 
