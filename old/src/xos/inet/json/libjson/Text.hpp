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
///   File: Text.hpp
///
/// Author: $author$
///   Date: 1/1/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_JSON_LIBJSON_TEXT_HPP
#define _XOS_JSON_LIBJSON_TEXT_HPP

#include "xos/inet/json/Text.hpp"
#include "xos/inet/json/Node.hpp"
#include "xos/os/Logger.hpp"
#include <libjson.h>

namespace xos {
namespace json {
namespace libjson {

typedef InterfaceBase ToNodeImplement;
typedef Base ToNodeExtend;
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
template
<typename TNode,
 class TExtend = ToNodeExtend,
 class TImplement = ToNodeImplement>

class _EXPORT_CLASS ToNodeT
: virtual public TImplement, public TExtend {
public:
    typedef TImplement Implements;
    typedef TExtend Extends;
    typedef ToNodeT Derives;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    ToNodeT(TNode& to,const String& from): m_to(0), m_v(0) {
        To(to, from);
    }
    ToNodeT(): m_to(0), m_v(0) {
    }
    virtual ~ToNodeT() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual TNode& To(TNode& to,const String& from) {
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
                    m_v->Put(NullNode, XOS_JSON_NULL);
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
                TNode* oldV = m_v;
                TNode v;
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
                TNode* oldV = m_v;
                TNode v;
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
                        m_v->Put(name, NullNode, XOS_JSON_NULL);
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
                TNode* oldV = m_v;
                TNode v;
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
                TNode* oldV = m_v;
                TNode v;
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
    TNode* m_v;
};

typedef ToNodeT<Node> ToNode;

} // namespace libjson
} // namespace json 
} // namespace xos 

#endif // _XOS_JSON_LIBJSON_TEXT_HPP 
