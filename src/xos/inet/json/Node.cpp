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
///   File: Json.cpp
///
/// Author: $author$
///   Date: 12/31/2013
///////////////////////////////////////////////////////////////////////
#include "xos/inet/json/Node.hpp"
#include "xos/os/Logger.hpp"

namespace xos {
namespace json {

String& Node::To(String &to) const {
    if (!(m_value.size())) {
        if (NamedNode > (m_type)) {
            XOS_LOG_ERROR("invalid node type (" << m_type << ") for value");
        } else {
            if (0 < (m_name.Length())) {
                XOS_LOG_TRACE("literal \"" << m_name << "\"");
                m_name.ToLiteral(to);
            } else {
                to.Append("\"");
                to.Append("\"");
                XOS_LOG_TRACE("literal \"\"");
            }
        }
    } else {
        NodeList::const_iterator b = m_value.begin();
        NodeList::const_iterator e = m_value.end();
        NodeList::const_iterator i;
        if (b != e) {
            const Node& v = *b;
            if (!(m_name.Length())) {
                if ((v.m_name.Length())) {
                    if ((v.m_value.size())) {
                        if (ObjectNode != (m_type)) {
                            XOS_LOG_ERROR("invalid node type (" << m_type << ") for object");
                        } else {
                            XOS_LOG_TRACE("object {...");
                            to.Append("{");
                            for (i = b; i != e; ++i) {
                                const Node& f = *i;
                                if ((i != b)) {
                                    to.Append(",");
                                }
                                f.To(to);
                            }
                            to.Append("}");
                            XOS_LOG_TRACE("...} object");
                        }
                    } else {
                        v.To(to);
                    }
                } else {
                    if (ArrayNode != (m_type)) {
                        XOS_LOG_ERROR("invalid node type (" << m_type << ") for array");
                    } else {
                        XOS_LOG_TRACE("array [...");
                        to.Append("[");
                        for (i = b; i != e; ++i) {
                            const Node& e = *i;
                            if ((i != b)) {
                                to.Append(",");
                            }
                            e.To(to);
                        }
                        to.Append("]");
                        XOS_LOG_TRACE("...] array");
                    }
                }
            } else {
                if ((NamedNode == m_type)) {
                    to.Append("\"");
                    to.Append(m_name);
                    to.Append("\":");
                    XOS_LOG_TRACE("\"" << m_name << "\":");
                }
                v.To(to);
            }
        }
    }
    return to;
}

} // namespace json 
} // namespace xos 
