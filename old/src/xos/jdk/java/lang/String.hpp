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
///   File: String.hpp
///
/// Author: $author$
///   Date: 2/24/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_JAVA_LANG_STRING_HPP
#define _XOS_JAVA_LANG_STRING_HPP

#include "xos/jdk/java/io/Serializable.hpp"
#include "xos/jdk/java/lang/Comparable.hpp"
#include "xos/jdk/java/lang/CharSequence.hpp"
#include "xos/jdk/java/lang/Object.hpp"
#include "xos/jdk/java/Types.hpp"

namespace xos {
namespace java {
namespace lang {

///////////////////////////////////////////////////////////////////////
///  Class: StringImplement
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS StringImplement
: virtual public io::Serializable,
  virtual public Comparable<String>,
  virtual public CharSequence,
  virtual public ObjectImplement {
public:
};
typedef Object StringExtend;
///////////////////////////////////////////////////////////////////////
///  Class: String
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS String: virtual public StringImplement, public StringExtend {
public:
    typedef StringImplement Implements;
    typedef StringExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    String(const char* copy): m_wrapped(copy) {
    }
    String(const string_t& copy): m_wrapped(copy) {
    }
    String(const String& copy): m_wrapped(copy.m_wrapped) {
    }
    String() {
    }
    virtual ~String() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int_t compareTo(const String& to) const {
        int_t unequal = 1;
        return unequal;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual char_t charAt(int_t index) const {
        int_t len = (int_t)(m_wrapped.Length());
        char_t c = 0;
        if ((index >= 0) && (index < len))
            return m_wrapped.at(index);
        return c;
    }
    virtual int_t length() const {
        int_t len = (int_t)(m_wrapped.Length());
        return len;
    }
    virtual String subSequence(int_t start, int_t end) const {
        int_t len = (int_t)(m_wrapped.Length());
        String s;
        if ((start >= 0) && (start < len) && (end >= start) && (end < len))
            return String(m_wrapped.substr(start, end));
        return s;
    }
    virtual String toString() const {
        String s(*this);
        return s;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual operator cstring_t() const {
        cstring_t s(m_wrapped.Chars());
        return s;
    }
    virtual operator wstring_t() const {
        wstring_t s(m_wrapped.Chars());
        return s;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    string_t m_wrapped;
};

} // namespace lang 
} // namespace java 
} // namespace xos 

#endif // _XOS_JAVA_LANG_STRING_HPP 
