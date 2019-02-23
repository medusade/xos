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
///   File: Node.hpp
///
/// Author: $author$
///   Date: 12/31/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_JSON_NODE_HPP
#define _XOS_JSON_NODE_HPP

#include "xos/base/String.hpp"
#include <sstream>
#include <list>

#define XOS_JSON_TRUE "true"
#define XOS_JSON_FALSE "false"
#define XOS_JSON_NULL "null"

namespace xos {
namespace json {

enum NodeType {
  ObjectNode,
  ArrayNode,
  NamedNode,
  NullNode,
  NumberNode,
  BooleanNode,
  StringNode
};
class _EXPORT_CLASS Node;
typedef std::list<Node> NodeList;
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Node {
public:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Node(const String& name, const char* value): m_type(NamedNode) {
        String sValue(value);
        m_name = name;
        m_value.push_back(Node(sValue));
    }
    Node(const String& name, int value): m_type(NamedNode) {
        m_name = name;
        m_value.push_back(Node(value));
    }
    Node(const String& name, float value): m_type(NamedNode) {
        m_name = name;
        m_value.push_back(Node(value));
    }
    Node(const String& name, double value): m_type(NamedNode) {
        m_name = name;
        m_value.push_back(Node(value));
    }
    Node(const String& name, bool value): m_type(NamedNode) {
        m_name = name;
        m_value.push_back(Node(value));
    }
    Node(const String& name, const String& value): m_type(NamedNode) {
        m_name = name;
        m_value.push_back(Node(value));
    }
    Node(const String& name, const Node& value): m_type(NamedNode) {
        m_name = name;
        if ((value.m_value.size())) {
            m_value.push_back(Node(value.m_type, value.m_value));
        } else {
            m_value.push_back(Node(value.m_name));
        }
    }
    Node(const String& name, NodeType type, const char* value): m_type(NamedNode) {
        String sValue(value);
        m_name = name;
        m_value.push_back(Node(type,sValue));
    }
    Node(const String& name, NodeType type, const String& value): m_type(NamedNode) {
        m_name = name;
        m_value.push_back(Node(type,value));
    }
    ///////////////////////////////////////////////////////////////////////
    Node(NodeType type, const NodeList& value): m_type(type) {
        m_value = value;
    }
    Node(NodeType type, const String& name): m_type(type) {
        m_name = name;
    }
    Node(NodeType type): m_type(type) {
    }
    ///////////////////////////////////////////////////////////////////////
    Node(const char* value): m_type(StringNode) {
        m_name = value;
    }
    Node(int value): m_type(NumberNode) {
        std::stringstream ss;
        ss << value;
        m_name = ss.str();
    }
    Node(float value): m_type(NumberNode) {
        std::stringstream ss;
        ss << value;
        m_name = ss.str();
    }
    Node(double value): m_type(NumberNode) {
        std::stringstream ss;
        ss << value;
        m_name = ss.str();
    }
    Node(bool value): m_type(BooleanNode) {
        m_name = (value)?(XOS_JSON_TRUE):(XOS_JSON_FALSE);
    }
    Node(const String& value): m_type(StringNode) {
        m_name = value;
    }
    Node(const Node& copy)
    : m_type(copy.m_type), m_name(copy.m_name), m_value(copy.m_value) {
    }
    Node(): m_type(NullNode), m_name(XOS_JSON_NULL) {
    }
    virtual ~Node() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual Node& Put(const String& name, const char* value) {
        String sValue(value);
        m_value.push_back(Node(name,sValue));
        return *this;
    }
    virtual Node& Put(const String& name, int value) {
        m_value.push_back(Node(name,value));
        return *this;
    }
    virtual Node& Put(const String& name, float value) {
        m_value.push_back(Node(name,value));
        return *this;
    }
    virtual Node& Put(const String& name, double value) {
        m_value.push_back(Node(name,value));
        return *this;
    }
    virtual Node& Put(const String& name, bool value) {
        m_value.push_back(Node(name,value));
        return *this;
    }
    virtual Node& Put(const String& name, const String& value) {
        m_value.push_back(Node(name,value));
        return *this;
    }
    virtual Node& Put(const String& name, const Node& value) {
        m_value.push_back(Node(name,value));
        return *this;
    }
    virtual Node& Put(const String& name, NodeType type, const char* value) {
        String sValue(value);
        m_value.push_back(Node(name,type,sValue));
        return *this;
    }
    virtual Node& Put(const String& name, NodeType type, const String& value) {
        m_value.push_back(Node(name,type,value));
        return *this;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual Node& Put(NodeType type, const char* name) {
        String sName(name);
        m_value.push_back(Node(type,sName));
        return *this;
    }
    virtual Node& Put(NodeType type, const String& name) {
        m_value.push_back(Node(type,name));
        return *this;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual Node& Put(const char* value) {
        String sValue(value);
        m_value.push_back(Node(sValue));
        return *this;
    }
    virtual Node& Put(int value) {
        m_value.push_back(Node(value));
        return *this;
    }
    virtual Node& Put(float value) {
        m_value.push_back(Node(value));
        return *this;
    }
    virtual Node& Put(double value) {
        m_value.push_back(Node(value));
        return *this;
    }
    virtual Node& Put(bool value) {
        m_value.push_back(Node(value));
        return *this;
    }
    virtual Node& Put(const String& value) {
        m_value.push_back(Node(value));
        return *this;
    }
    virtual Node& Put(const Node& value) {
        m_value.push_back(Node(value));
        return *this;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int& Get(int& value, const String& name) const {
        const Node* v;
        if ((v = Find(name))) {
            NodeList::const_iterator b = v->m_value.begin();
            NodeList::const_iterator e = v->m_value.end();
            if (b != e) {
                if (!(b->m_value.size())) {
                    std::stringstream ss(b->m_name);
                    ss >> value;
                }
            }
        }
        return value;
    }
    virtual float& Get(float& value, const String& name) const {
        const Node* v;
        if ((v = Find(name))) {
            NodeList::const_iterator b = v->m_value.begin();
            NodeList::const_iterator e = v->m_value.end();
            if (b != e) {
                if (!(b->m_value.size())) {
                    std::stringstream ss(b->m_name);
                    ss >> value;
                }
            }
        }
        return value;
    }
    virtual double& Get(double& value, const String& name) const {
        const Node* v;
        if ((v = Find(name))) {
            NodeList::const_iterator b = v->m_value.begin();
            NodeList::const_iterator e = v->m_value.end();
            if (b != e) {
                if (!(b->m_value.size())) {
                    std::stringstream ss(b->m_name);
                    ss >> value;
                }
            }
        }
        return value;
    }
    virtual bool& Get(bool& value, const String& name) const {
        const Node* v;
        if ((v = Find(name))) {
            NodeList::const_iterator b = v->m_value.begin();
            NodeList::const_iterator e = v->m_value.end();
            if (b != e) {
                if (!(b->m_value.size())) {
                    value = !(b->m_name.Compare(XOS_JSON_TRUE));
                }
            }
        }
        return value;
    }
    virtual String& Get(String& value, const String& name) const {
        const Node* v;
        if ((v = Find(name))) {
            NodeList::const_iterator b = v->m_value.begin();
            NodeList::const_iterator e = v->m_value.end();
            if (b != e) {
                if (!(b->m_value.size())) {
                    value = b->m_name;
                }
            }
        }
        return value;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual String& To(String& to) const;
protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const Node* Find(const String& name) const {
        NodeList::const_iterator b = m_value.begin();
        NodeList::const_iterator e = m_value.end();
        if (b != e) {
            if (0 < (b->m_name.Length())) {
                for (NodeList::const_iterator i = b; i != e; ++i) {
                    const Node& v = (*i);
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
protected:
    NodeType m_type;
    String m_name;
    NodeList m_value;
};

} // namespace json
} // namespace xos 

#endif // _XOS_JSON_NODE_HPP
