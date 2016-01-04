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
///   File: Environment.hpp
///
/// Author: $author$
///   Date: 3/5/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_INET_HTTP_CGI_ENVIRONMENT_HPP
#define _XOS_INET_HTTP_CGI_ENVIRONMENT_HPP

#include "xos/os/Logger.hpp"
#include "xos/os/File.hpp"
#include "xos/base/String.hpp"
#include "xos/base/Wrapped.hpp"
#include "xos/base/Base.hpp"
#include "xos/base/Types.hpp"

#define XOS_INET_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_GATEWAY_INTERFACE "GATEWAY_INTERFACE"
#define XOS_INET_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_SERVER_NAME "SERVER_NAME"
#define XOS_INET_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_SERVER_PORT "SERVER_PORT"
#define XOS_INET_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_SERVER_PROTOCOL "SERVER_PROTOCOL"
#define XOS_INET_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_SERVER_SOFTWARE "SERVER_SOFTWARE"
#define XOS_INET_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_AUTH_TYPE "AUTH_TYPE"
#define XOS_INET_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_CONTENT_FILE "CONTENT_FILE"
#define XOS_INET_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_CONTENT_LENGTH "CONTENT_LENGTH"
#define XOS_INET_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_CONTENT_TYPE "CONTENT_TYPE"
#define XOS_INET_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_OUTPUT_FILE "OUTPUT_FILE"
#define XOS_INET_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_PATH_INFO "PATH_INFO"
#define XOS_INET_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_PATH_TRANSLATED "PATH_TRANSLATED"
#define XOS_INET_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_QUERY_STRING "QUERY_STRING"
#define XOS_INET_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_REMOTE_ADDR "REMOTE_ADDR"
#define XOS_INET_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_REMOTE_USER "REMOTE_USER"
#define XOS_INET_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_REQUEST_LINE "REQUEST_LINE"
#define XOS_INET_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_REQUEST_METHOD "REQUEST_METHOD"
#define XOS_INET_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_REMOTE_HOST "REMOTE_HOST"
#define XOS_INET_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_REMOTE_IDENT "REMOTE_IDENT"
#define XOS_INET_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_HTTP_ACCEPT "HTTP_ACCEPT"
#define XOS_INET_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_HTTP_USER_AGENT "HTTP_USER_AGENT"
#define XOS_INET_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_SCRIPT_NAME "SCRIPT_NAME"

#define XOS_INET_HTTP_CGI_ENVIRONMENT_VARIABLE_NAMES \
    XOS_INET_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_GATEWAY_INTERFACE, \
    XOS_INET_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_SERVER_NAME, \
    XOS_INET_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_SERVER_PORT, \
    XOS_INET_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_SERVER_PROTOCOL, \
    XOS_INET_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_SERVER_SOFTWARE, \
    XOS_INET_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_AUTH_TYPE, \
    XOS_INET_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_CONTENT_FILE, \
    XOS_INET_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_CONTENT_LENGTH, \
    XOS_INET_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_CONTENT_TYPE, \
    XOS_INET_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_OUTPUT_FILE, \
    XOS_INET_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_PATH_INFO, \
    XOS_INET_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_PATH_TRANSLATED, \
    XOS_INET_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_QUERY_STRING, \
    XOS_INET_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_REMOTE_ADDR, \
    XOS_INET_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_REMOTE_USER, \
    XOS_INET_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_REQUEST_LINE, \
    XOS_INET_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_REQUEST_METHOD, \
    XOS_INET_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_REMOTE_HOST, \
    XOS_INET_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_REMOTE_IDENT, \
    XOS_INET_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_HTTP_ACCEPT, \
    XOS_INET_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_HTTP_USER_AGENT, \
    XOS_INET_HTTP_CGI_ENVIRONMENT_VARIABLE_NAME_SCRIPT_NAME

namespace xos {
namespace http {
namespace cgi {

typedef InterfaceBase EnvironmentImplement;
typedef ExportBase EnvironmentExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Environment
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Environment: virtual public EnvironmentImplement, public EnvironmentExtend {
public:
    typedef EnvironmentImplement Implements;
    typedef EnvironmentExtend Extends;

    typedef InterfaceBase VariableImplement;
    typedef ExportBase VariableExtend;
    ///////////////////////////////////////////////////////////////////////
    ///  Class: Variable
    ///////////////////////////////////////////////////////////////////////
    class _EXPORT_CLASS Variable: virtual public VariableImplement, public VariableExtend {
    public:
        typedef VariableImplement Implements;
        typedef VariableExtend Extends;

        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        typedef int Which;
        enum {
            None = 0,

            GATEWAY_INTERFACE,
            SERVER_NAME,
            SERVER_PORT,
            SERVER_PROTOCOL,
            SERVER_SOFTWARE,
            AUTH_TYPE,
            CONTENT_FILE,
            CONTENT_LENGTH,
            CONTENT_TYPE,
            OUTPUT_FILE,
            PATH_INFO,
            PATH_TRANSLATED,
            QUERY_STRING,
            REMOTE_ADDR,
            REMOTE_USER,
            REQUEST_LINE,
            REQUEST_METHOD,
            REMOTE_HOST,
            REMOTE_IDENT,
            HTTP_ACCEPT,
            HTTP_USER_AGENT,
            SCRIPT_NAME,

            Next,
            First = (None + 1),
            Last = (Next - 1),
            Count = ((Last - First) + 1)
        };
        typedef Wrapped<const char*> Chars;

        typedef InterfaceBase NameImplement;
        typedef Chars NameExtend;
        ///////////////////////////////////////////////////////////////////////
        ///  Class: Name
        ///////////////////////////////////////////////////////////////////////
        class _EXPORT_CLASS Name: virtual public NameImplement, public NameExtend {
        public:
            typedef NameImplement Implements;
            typedef NameExtend Extends;
            ///////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////
            Name(Which which): m_which(which) {
                m_wrapped = OfWhich(m_which);
            }
            Name(const Name& copy): Extends(copy), m_which(copy.m_which) {
            }
            Name(): m_which(None) {
            }
            ///////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////
            virtual Name& operator = (Which which) {
                m_wrapped = OfWhich(m_which = which);
                return *this;
            }
            ///////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////
            static const char* OfWhich(Which which) {
                static const char* of[Count] = {
                    XOS_INET_HTTP_CGI_ENVIRONMENT_VARIABLE_NAMES
                };
                if ((which >= First) && (which <= Last))
                    return of[which - First];
                return 0;
            }
            static Which WhichOf(const char* of) {
                if ((of)) {
                    const char* toOf;
                    for (Which which = First; which <= Last; ++which) {
                        if ((toOf = OfWhich(which))) {
                            if (!(xos::Chars::Compare(of, toOf)))
                                return which;
                        }
                    }
                }
                return None;
            }
            ///////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////
        protected:
            Which m_which;
        };

        typedef InterfaceBase ValueImplement;
        typedef Chars ValueExtend;
        ///////////////////////////////////////////////////////////////////////
        ///  Class: Value
        ///////////////////////////////////////////////////////////////////////
        class _EXPORT_CLASS Value: virtual public ValueImplement, public ValueExtend {
        public:
            typedef ValueImplement Implements;
            typedef ValueExtend Extends;
            ///////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////
            Value(Which which) {
                Get(which);
            }
            Value(const String& chars): m_chars(chars) {
                m_wrapped = m_chars.Chars();
            }
            Value(const Value& copy): Extends(copy) {
            }
            Value() {
            }
            ///////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////
            virtual Value& Get(Which which) {
                const char* of;
                m_wrapped = 0;
                if ((of = Name::OfWhich(which))) {
                    if ((m_wrapped = getenv(of))) {
                        m_chars.Assign(m_wrapped);
                        m_wrapped = m_chars.Chars();
                    }
                }
                return *this;
            }
            virtual Value& operator = (Which which) {
                Get(which);
                return *this;
            }
            virtual Value& operator = (const String& chars) {
                m_chars = chars;
                m_wrapped = m_chars.Chars();
                return *this;
            }
            ///////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////
            inline ssize_t Length() const {
                if ((m_wrapped))
                    return m_chars.Length();
                return -1;
            }
            ///////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////
        protected:
            String m_chars;
        };

        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        Variable(Which which): m_name(which), m_value(which) {
        }
        Variable(const Variable& copy)
        : m_name(copy.m_name), m_value(copy.m_value) {
        }
        Variable() {
        }
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        virtual Variable& Get(Which which) {
            m_name = which;
            m_value = which;
            return *this;
        }
        virtual Variable& operator = (Which which) {
            Get(which);
            return *this;
        }
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        inline Name& name() const {
            return (Name&)(m_name);
        }
        inline Value& value() const {
            return (Value&)(m_value);
        }
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
    protected:
        Name m_name;
        Value m_value;
    };

    ///////////////////////////////////////////////////////////////////////
    ///  Class: ReaderEvents
    ///////////////////////////////////////////////////////////////////////
    class _EXPORT_CLASS ReaderEvents {
    public:
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        virtual bool OnReadInit() {
            return true;
        }
        virtual bool OnReadFinish() {
            return true;
        }
        virtual bool OnReadVariable(const String& name, const String& value) {
            return true;
        }
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
    };
    ///////////////////////////////////////////////////////////////////////
    ///  Class: EventsReader
    ///////////////////////////////////////////////////////////////////////
    class _EXPORT_CLASS EventsReader {
    public:
        typedef EventsReader Derives;
        typedef char char_t;
        typedef CharStreamBase Stream;
        typedef CharFileBase File;
        typedef bool (Derives::*MOnChar)(const char_t& c);
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        EventsReader(ReaderEvents& events): m_events(events), m_onChar(0) {
        }
        virtual ~EventsReader() {
        }
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        virtual ssize_t Read(const String& fileName) {
            ssize_t count = -1;
            File file;
            if (!(file.Find(fileName.Chars())))
                return count;
            if ((file.Open(fileName.Chars(), XOS_FILE_MODE_READ_BINARY))) {
                count = Read(file);
                file.Close();
            }
            return count;
        }
        virtual ssize_t Read(Stream& stream, ssize_t length = -1) {
            ssize_t count = -1;

            if ((Init())) {
                ssize_t read;
                char_t c;

                if ((count = 0) <= (length)) {
                    for (int i = 0; i < length; ++i) {
                        if (0 < (read = stream.Read(&c, 1))) {
                            if ((OnChar(c))) {
                                count += read;
                                continue;
                            }
                            return -1;
                        }
                        break;
                    }
                } else {
                    do {
                        if (0 < (read = stream.Read(&c, 1))) {
                            if ((OnChar(c))) {
                                count += read;
                                continue;
                            }
                            return -1;
                        }
                    } while (0 < read);
                }

                if (!(Finish()))
                    count = -1;
            }
            return count;
        }
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        virtual bool Init() {
            m_onChar = 0;
            if ((m_events.OnReadInit())) {
                m_name.Clear();
                m_onChar = &Derives::OnNameChar;
                return true;
            }
            return false;
        }
        virtual bool Finish() {
            bool success = true;
            if ((&Derives::OnNameChar == m_onChar)) {
                XOS_LOG_TRACE("value = \"" << m_value << "\"");
                success = m_events.OnReadVariable(m_name, m_value);
            }
            m_onChar = 0;
            if (!(m_events.OnReadFinish()))
                success = false;
        }
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        virtual bool OnChar(const char_t& c) {
            if ((m_onChar))
                return (this->*m_onChar)(c);
            return false;
        }
        virtual bool OnNameChar(const char_t& c) {
            if ((c == '=')) {
                XOS_LOG_TRACE("name = \"" << m_name << "\"");
                m_value.Clear();
                m_onChar = &Derives::OnValueChar;
            } else {
                m_name.Append(&c, 1);
            }
            return true;
        }
        virtual bool OnValueChar(const char_t& c) {
            bool success = true;
            if (c == '\n') {
                XOS_LOG_TRACE("value = \"" << m_value << "\"");
                success = m_events.OnReadVariable(m_name, m_value);
                m_name.Clear();
                m_onChar = &Derives::OnNameChar;
            } else {
                if (c != '\r')
                m_value.Append(&c, 1);
            }
            return success;
        }
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
    protected:
        ReaderEvents& m_events;
        MOnChar m_onChar;
        String m_name, m_value;
    };
    ///////////////////////////////////////////////////////////////////////
    ///  Class: Reader
    ///////////////////////////////////////////////////////////////////////
    class _EXPORT_CLASS Reader: virtual public ReaderEvents {
    public:
        typedef ReaderEvents Implements;
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        Reader(Environment& e): m_e(e) {
        }
        virtual ~Reader() {
        }
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        virtual ssize_t Read(const String& fileName) {
            EventsReader r(*this);
            ssize_t count = r.Read(fileName);
            return count;
        }
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        virtual bool OnReadInit() {
            m_e.Clear();
            return true;
        }
        virtual bool OnReadFinish() {
            return true;
        }
        virtual bool OnReadVariable(const String& name, const String& value) {
            const char* of;
            if ((of = name.Chars())) {
                Environment::Variable::Which which;
                if (Environment::Variable::None != (which = Environment::Variable::Name::WhichOf(of))) {
                    XOS_LOG_TRACE("got \"" << name << "\" = \"" << value << "\"");
                    m_e.Got(which, value);
                }
            }
            return true;
        }
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
    protected:
        Environment& m_e;
    };

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Environment() {
    }
    virtual ~Environment() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Got(Variable::Which which, const String& value) {
        bool success = false;
        if ((which >= Variable::First) && (which <= Variable::Last)) {
            Variable& variable = m_variable[which-Variable::First];
            variable.name() = which;
            variable.value() = value;
            success = true;
        }
        return success;
    }
    virtual bool Get() {
        bool success = false;
        for (Variable::Which which = Variable::First; which <= Variable::Last; ++which) {
            Variable& variable = m_variable[which-Variable::First];
            const char* value;
            if ((value = ((variable = which).value())) != 0) {
                XOS_LOG_TRACE("found env \"" << variable.name() << "\" = \"" << value << "\"");
            } else {
                XOS_LOG_TRACE("unable to find env \"" << variable.name() << "\"");
            }
        }
        return success;
    }
    virtual void Clear() {
        for (Variable::Which which = Variable::First; which <= Variable::Last; ++which) {
            Variable& variable = m_variable[which-Variable::First];
            variable.name() = 0;
            variable.value() = 0;
        }
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual Variable& operator[](Variable::Which which) const {
        if ((which >= Variable::First) && (which <= Variable::Last)) {
            return (Variable&)(m_variable[which-Variable::First]);
        }
        return (Variable&)(m_variableNone);
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    Variable m_variable[Variable::Count];
    Variable m_variableNone;
};

} // namespace cgi
} // namespace http
} // namespace xos 

#endif // _XOS_INET_HTTP_CGI_ENVIRONMENT_HPP 
