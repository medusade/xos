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
///   File: Mime.cpp
///
/// Author: $author$
///   Date: 6/13/2014
///////////////////////////////////////////////////////////////////////
#include "xos/inet/http/Mime.hpp"
#include "xos/base/Types.hpp"
#include <map>
#include "xos/inet/http/ExtensionMimeTypeName.cpp"

namespace xos {
namespace http {
namespace actual {
namespace Mime {

typedef http::Mime::TypeImplement TypeImplement;
typedef http::Mime::Type TypeExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Type
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Type: virtual public TypeImplement,public TypeExtend {
public:
    typedef TypeImplement Implements;
    typedef TypeExtend Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Type() {
        const char *extension, *name;
        for (unsigned i = 0; (extension = g_extensionMimeTypeName[i].extension)
             && (name = g_extensionMimeTypeName[i].mimeTypeName); ++i) {
            m_extensionToName.insert(std::pair<const char*, const char*>(extension, name));
        }
    }
    virtual ~Type() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool GetNameOfExtension(String& name, const String& of) const {
        ExtensionToName::const_iterator i;
        if ((i = m_extensionToName.find(of.Chars())) != (m_extensionToName.end())) {
            name.Assign(i->second);
            return true;
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    typedef const char* const_chars;
    struct Compare {
      bool operator() (const const_chars& l, const const_chars& r) const {
          return (0 > (Chars::CompareCase(l,r)));
      }
    };
    typedef std::map<const_chars, const_chars, Compare> ExtensionToName;
protected:
    ExtensionToName m_extensionToName;
};

} // namespace Mime
} // namespace avtual

///////////////////////////////////////////////////////////////////////
///  Class: Mime::Type
///////////////////////////////////////////////////////////////////////
Mime::Type& Mime::Type::GetTheInstance() {
    static actual::Mime::Type theInstance;
    return theInstance;
}

} // namespace http 
} // namespace xos 
