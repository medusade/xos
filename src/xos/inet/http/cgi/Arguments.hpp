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
///   File: Arguments.hpp
///
/// Author: $author$
///   Date: 3/9/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_INET_HTTP_CGI_ARGUMENTS_HPP
#define _XOS_INET_HTTP_CGI_ARGUMENTS_HPP

#include "xos/os/Logger.hpp"
#include "xos/os/File.hpp"
#include "xos/base/Array.hpp"
#include "xos/base/String.hpp"
#include "xos/base/StringBase.hpp"

namespace xos {
namespace http {
namespace cgi {

typedef InterfaceBase ArgumentsImplement;
typedef ExportBase ArgumentsExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Arguments
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Arguments: virtual public ArgumentsImplement, public ArgumentsExtend {
public:
    typedef ArgumentsImplement Implements;
    typedef ArgumentsExtend Extends;

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
        virtual bool OnReadValue(const String& value) {
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
                m_onChar = &Derives::OnNameChar;
                return true;
            }
            return false;
        }
        virtual bool Finish() {
            bool success = true;
            if ((&Derives::OnValueChar == m_onChar)) {
                XOS_LOG_TRACE("value = \"" << m_value << "\"");
                success = m_events.OnReadValue(m_value);
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
            if ((c != ' ') && (c != '\t') && (c != '\r') && (c != '\n')) {
                m_value.Assign(&c, 1);
                m_onChar = &Derives::OnValueChar;
            }
            return true;
        }
        virtual bool OnValueChar(const char_t& c) {
            bool success = true;
            if ((c == ' ') || (c == '\t') || (c == '\r') || (c == '\n')) {
                XOS_LOG_TRACE("value = \"" << m_value << "\"");
                //printf("value = \"%s\"\n", m_value.Chars());
                success = m_events.OnReadValue(m_value);
                m_onChar = &Derives::OnNameChar;
            } else {
                m_value.Append(&c, 1);
            }
            return success;
        }
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
    protected:
        ReaderEvents& m_events;
        MOnChar m_onChar;
        String m_value;
    };
    ///////////////////////////////////////////////////////////////////////
    ///  Class: NameValueEventsReader
    ///////////////////////////////////////////////////////////////////////
    class _EXPORT_CLASS NameValueEventsReader: public EventsReader {
    public:
        typedef EventsReader Extends;
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        NameValueEventsReader(ReaderEvents& events): Extends(events) {
        }
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        virtual bool OnNameChar(const char_t& c) {
            if ((c == '=')) {
                XOS_LOG_TRACE("name = \"" << m_name << "\"");
                //printf("name = \"%s\"\n", m_name.Chars());
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
                //printf("value = \"%s\"\n", m_value.Chars());
                success = m_events.OnReadValue(m_value);
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
        String m_name;
    };
    ///////////////////////////////////////////////////////////////////////
    ///  Class: Reader
    ///////////////////////////////////////////////////////////////////////
    class _EXPORT_CLASS Reader: virtual public ReaderEvents {
    public:
        typedef ReaderEvents Implements;
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        Reader(Arguments& a): m_a(a) {
        }
        virtual ~Reader() {
        }
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        virtual ssize_t NameValueRead(const String& fileName) {
            NameValueEventsReader r(*this);
            ssize_t count = r.Read(fileName);
            return count;
        }
        virtual ssize_t Read(const String& fileName) {
            EventsReader r(*this);
            ssize_t count = r.Read(fileName);
            return count;
        }
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        virtual bool OnReadInit() {
            m_a.Clear();
            return true;
        }
        virtual bool OnReadFinish() {
            m_a.AppendEnd();
            return true;
        }
        virtual bool OnReadValue(const String& value) {
            m_a.Append(value);
            return true;
        }
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
    protected:
        Arguments& m_a;
    };

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Arguments() {
    }
    virtual ~Arguments() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int Get(int argc, char** argv, char** env) {
        Clear();
        for (int a = 0; a < argc; ++a) {
            Append(argv[a]);
        }
        return argc;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void Append(const String& value) {
        Append(value.Chars());
    }
    virtual void Append(const char* value) {
        const StringBase s(value);
        //printf("s = \"%s\"\n", s.c_str());
        if (0 < (m_s.Append(&s, 1))) {
            char* v = m_s[m_s.Length()-1].str();
            //printf("v = \"%s\"\n", v);
            m_v.Append(&v, 1);
        }
    }
    virtual void AppendEnd() {
        char* v = 0;
        m_v.Append(&v, 1);
        m_v.SetLength(m_v.Length()-1);
    }
    virtual void Clear() {
        m_v.Clear();
        m_s.Clear();
        AppendEnd();
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    inline int c() const {
        return m_v.Length();
    }
    inline char** v() const {
        return m_v.Elements();
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    typedef Array<char*> V;
    typedef Array<StringBase> S;
protected:
    V m_v;
    S m_s;
};

} // namespace cgi 
} // namespace http 
} // namespace xos 

#endif // _XOS_INET_HTTP_CGI_ARGUMENTS_HPP 
