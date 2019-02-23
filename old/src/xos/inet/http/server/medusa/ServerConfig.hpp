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
///   File: ServerConfig.hpp
///
/// Author: $author$
///   Date: 6/6/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_INET_HTTP_SERVER_MEDUSA_SERVERCONFIG_HPP
#define _XOS_INET_HTTP_SERVER_MEDUSA_SERVERCONFIG_HPP

#include "xos/inet/http/Content.hpp"
#include "xos/inet/http/Mime.hpp"
#include "xos/fs/Path.hpp"
#include "xos/base/String.hpp"

#define XOS_INET_HTTP_SERVER_MEDUSA_SERVERCONFIG_DOCUMENT_ROOT "/home/medusa"
#define XOS_INET_HTTP_SERVER_MEDUSA_SERVERCONFIG_CONTENT_TYPE \
    XOS_HTTP_CONTENT_TYPE_NAME_UNKNOWN

namespace xos {
namespace http {
namespace server {
namespace medusa {

typedef InterfaceBase ServerConfigImplement;
typedef ExportBase ServerConfigExtend;
///////////////////////////////////////////////////////////////////////
///  Class: ServerConfig
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS ServerConfig: virtual public ServerConfigImplement, public ServerConfigExtend {
public:
    typedef ServerConfigImplement Implements;
    typedef ServerConfigExtend Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    ServerConfig(const String& documentRoot)
    : m_documentRoot(documentRoot),
      m_contentType(XOS_INET_HTTP_SERVER_MEDUSA_SERVERCONFIG_CONTENT_TYPE) {
    }
    ServerConfig()
    : m_documentRoot(XOS_INET_HTTP_SERVER_MEDUSA_SERVERCONFIG_DOCUMENT_ROOT),
      m_contentType(XOS_INET_HTTP_SERVER_MEDUSA_SERVERCONFIG_CONTENT_TYPE) {
    }
    virtual ~ServerConfig() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual String& TranslatePath
    (String& to, const String& from, char directorySeparator = '/') const {
        const char* chars;
        size_t length;
        to.Assign(m_documentRoot);
        if ((chars = to.HasChars(length)) && (chars[length-1] != directorySeparator)) {
            if ((chars = from.HasChars(length)) && (chars[0] != directorySeparator)) {
                to.Append(&directorySeparator, 1);
            }
        }
        to.Append(from);
        return to;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const String& SetDocumentRoot(const String& to) {
        m_documentRoot.Assign(to);
        return m_documentRoot;
    }
    virtual const String& DocumentRoot() const {
        return m_documentRoot;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual String GetContentTypeOf(const String& of) const {
        fs::Path path(of.Chars());

        if ((path.Separate())) {
            String extension(path.GetFileExtension());
            if ((extension.HasChars())) {
                Mime::Type& type = Mime::Type::GetTheInstance();
                String name;

                XOS_LOG_DEBUG("extension = \"" << extension << "\"");
                if ((type.GetNameOfExtension(name, extension))) {
                    XOS_LOG_DEBUG("type = \"" << name << "\"");
                    return name;
                }
            }
        }
        return m_contentType;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    String m_documentRoot;
    String m_contentType;
};

} // namespace medusa 
} // namespace server 
} // namespace http 
} // namespace xos 

#endif // _XOS_INET_HTTP_SERVER_MEDUSA_SERVERCONFIG_HPP 
