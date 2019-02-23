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
///   File: Version.hpp
///
/// Author: $author$
///   Date: 3/13/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_INET_HTTP_VERSION_HPP
#define _XOS_INET_HTTP_VERSION_HPP

#include "xos/base/String.hpp"

#define XOS_HTTP_VERSION_PROTOCOL "HTTP"
#define XOS_HTTP_VERSION_MAJOR_NO 1
#define XOS_HTTP_VERSION_MAJOR XOS_STRING(XOS_HTTP_VERSION_MAJOR_NO)
#define XOS_HTTP_VERSION_MINOR_NO 1
#define XOS_HTTP_VERSION_MINOR XOS_STRING(XOS_HTTP_VERSION_MINOR_NO)

namespace xos {
namespace http {

typedef String::Implements VersionImplement;
typedef String VersionExtend;
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Version: virtual public VersionImplement, public VersionExtend {
public:
    typedef VersionImplement Implements;
    typedef VersionExtend Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Version(const String& value): Extends(value) {
        Separate();
    }
    Version(const char* value): Extends(value) {
        Separate();
    }
    Version(const Version& copy)
    : m_protocol(copy.m_protocol),
      m_major(copy.m_major),
      m_minor(copy.m_minor) {
        Combine();
    }
    Version()
    : m_protocol(XOS_HTTP_VERSION_PROTOCOL),
      m_major(XOS_HTTP_VERSION_MAJOR),
      m_minor(XOS_HTTP_VERSION_MINOR) {
        Combine();
    }
    virtual ~Version() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Combine(const String& protocol, const String& major, const String& minor) {
        m_protocol = protocol;
        m_major = major;
        m_minor = minor;
        return Combine();
    }
    virtual bool Combine() {
        if ((m_protocol.Length()) && (m_major.Length())) {
            Assign(m_protocol);
            Append("/");
            Append(m_major);
            Append(".");
            Append(m_minor);
            return true;
        }
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual bool Separate(String& protocol, String& major, String& minor) {
        if ((Separate())) {
            protocol = m_protocol;
            major = m_major;
            minor = m_minor;
            return true;
        }
        return false;
    }
    virtual bool Separate() {
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual Version& Set(const Version& copy) {
        m_protocol.Assign(copy.m_protocol);
        m_major.Assign(copy.m_major);
        m_minor.Assign(copy.m_minor);
        Combine();
        return *this;
    }
    virtual Version& Set
    (const String& protocol, const String& major, const String& minor) {
        Combine(protocol, major, minor);
        return *this;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const String& SetProtocol(const String& to) {
        m_protocol.Assign(to);
        return m_protocol;
    }
    virtual const String& GetProtocol() const {
        return m_protocol;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const String& SetMajor(const String& to) {
        m_major.Assign(to);
        return m_major;
    }
    virtual const String& GetMajor() const {
        return m_major;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const String& SetMinor(const String& to) {
        m_minor.Assign(to);
        return m_minor;
    }
    virtual const String& GetMinor() const {
        return m_minor;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual String& protocol() const {
        return (String&)(m_protocol);
    }
    virtual String& major() const {
        return (String&)(m_major);
    }
    virtual String& minor() const {
        return (String&)(m_minor);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    String m_protocol;
    String m_major;
    String m_minor;
};

} // namespace http
} // namespace xos 

#endif // _XOS_INET_HTTP_VERSION_HPP 
