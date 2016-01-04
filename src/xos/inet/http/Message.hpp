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
///   File: Message.hpp
///
/// Author: $author$
///   Date: 4/6/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_INET_HTTP_MESSAGE_HPP
#define _XOS_INET_HTTP_MESSAGE_HPP

#include "xos/base/StringReader.hpp"
#include "xos/base/StringWriter.hpp"
#include "xos/base/String.hpp"

namespace xos {
namespace http {

typedef String::Implements MessageImplement;
typedef String MessageExtend;
///////////////////////////////////////////////////////////////////////
/// Class: Message
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Message: virtual public MessageImplement, public MessageExtend {
public:
    typedef MessageImplement Implements;
    typedef MessageExtend Extends;

    typedef StringReader::Implements ReaderImplement;
    typedef StringReader ReaderExtend;
    ///////////////////////////////////////////////////////////////////////
    ///  Class: Reader
    ///////////////////////////////////////////////////////////////////////
    class _EXPORT_CLASS Reader: virtual public ReaderImplement, public ReaderExtend {
    public:
        typedef ReaderImplement Implements;
        typedef ReaderExtend Extends;
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        Reader(Message& message): Extends(message) {
        }
        virtual ~Reader() {
        }
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
    };

    typedef StringWriter::Implements WriterImplement;
    typedef StringWriter WriterExtend;
    ///////////////////////////////////////////////////////////////////////
    ///  Class: Writer
    ///////////////////////////////////////////////////////////////////////
    class _EXPORT_CLASS Writer: virtual public WriterImplement, public WriterExtend {
    public:
        typedef WriterImplement Implements;
        typedef WriterExtend Extends;
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        Writer(Message& message): Extends(message) {
        }
        virtual ~Writer() {
        }
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
    };

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Message(const String& value)
    : Extends(value), m_thisReader(*this), m_thisWriter(*this),
      m_reader(m_thisReader), m_writer(m_thisWriter) {
    }
    Message(const Message& copy)
    : Extends(copy), m_thisReader(*this), m_thisWriter(*this),
      m_reader(m_thisReader), m_writer(m_thisWriter) {
    }
    Message(CharReader& reader, CharWriter& writer)
    : m_thisReader(*this), m_thisWriter(*this),
      m_reader(reader), m_writer(writer) {
    }
    Message(CharReader& reader)
    : m_thisReader(*this), m_thisWriter(*this),
      m_reader(reader), m_writer(m_thisWriter) {
    }
    Message(CharWriter& writer)
    : m_thisReader(*this), m_thisWriter(*this),
      m_reader(m_thisReader), m_writer(m_writer) {
    }
    Message()
    : m_thisReader(*this), m_thisWriter(*this),
      m_reader(m_thisReader), m_writer(m_thisWriter) {
    }
    virtual ~Message() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual CharReader& GetReader() const {
        return ((CharReader&)m_reader);
    }
    virtual CharWriter& GetWriter() const {
        return ((CharWriter&)m_writer);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    Reader m_thisReader;
    Writer m_thisWriter;
    CharReader& m_reader;
    CharWriter& m_writer;
};

} // namespace http
} // namespace xos 

#endif // _XOS_INET_HTTP_MESSAGE_HPP 
