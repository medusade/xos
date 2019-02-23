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
///   File: UrlEncodedReader.hpp
///
/// Author: $author$
///   Date: 11/25/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_INET_HTTP_URLENCODEDREADER_HPP
#define _XOS_INET_HTTP_URLENCODEDREADER_HPP

#include "xos/base/Reader.hpp"

#define XOS_INET_HTTP_URL_ENCODED_FORM_CONTENT_TYPE_NAME \
    "application/x-www-form-urlencoded"

#define XOS_INET_HTTP_URL_ENCODED_READER_CHAR_IS_X(x) \
    (((x) >= '0' && (x) <= '9') \
    || ((x) >= 'a' && (x) <= 'f') \
    || ((x) >= 'A' && (x) <= 'F'))

#define XOS_INET_HTTP_URL_ENCODED_READER_X2CHAR(x) \
    (((x) >= '0' && (x) <= '9')?((x)-'0') \
    :(((x) >= 'a' && (x) <= 'f')?((x)-'a'+10) \
    :((x)-'A'+10)))

#define XOS_INET_HTTP_URL_ENCODED_READER_CHAR2X(x) \
    (((x) >= 0 && (x) <= 9)?((x)+'0') \
    :(((x) >= 10 && (x) <= 15)?((x)+'a'-10) \
    :'.'))

namespace xos {
namespace http {

typedef CharReader UrlEncodedReaderImplement;
typedef Base UrlEncodedReaderExtend;
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS UrlEncodedReader
: virtual public UrlEncodedReaderImplement, public UrlEncodedReaderExtend {
public:
    typedef UrlEncodedReaderImplement Implements;
    typedef UrlEncodedReaderExtend Extends;
    typedef UrlEncodedReader Derives;
    typedef CharStream Reader;
    typedef WhatT What;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    UrlEncodedReader(Reader& reader)
    : m_reader(reader),
      m_get(&Derives::StartGet),
      m_content_length(-1),
      m_percent('%'),
      m_space(' '),
      m_x1(0),
      m_x2(0) {
    }
    virtual ~UrlEncodedReader() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Read(What* what, size_t size) {
        ssize_t count = 0;
        ssize_t length = 0;
        if (what) {
            while (size) {
                if (!(length = Get(*what)))
                    continue;
                if (0 > length)
                    return count;
                count += length;
                what++;
                --size;
            }
        }
        return count;
    }
    virtual ssize_t Reset() {
        ssize_t count = m_reader.Seek(0);
        m_get = &Derives::StartGet;
        m_content_length = -1;
        return count;
    }
    virtual ssize_t Tell() const {
        ssize_t count = m_reader.Tell();
        return count;
    }
protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Get(What& what) {
        ssize_t count = -1;
        if ((m_get) && (m_content_length)) {
            if (0 < m_content_length)
                --m_content_length;
            count = (this->*m_get)(what);
        }
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t StartGet(What& what) {
        ssize_t count = -1;
        ssize_t length = 0;
        char c;

        if (0 < (length = m_reader.Read(&what, 1))) {
            count = length;
            switch(c = (char)(what))
            {
            case '+':
                what = m_space;
                break;

            case '%':
                count = 0;
                m_get = &Derives::X1Get;
                break;
            }
        }
        return count;
    }
    virtual ssize_t X1Get(What& what) {
        ssize_t count = -1;
        ssize_t length = 0;
        char c;

        if (0 < (length = m_reader.Read(&what, 1))) {
            count = length;
            c = (char)(what);
            if (XOS_INET_HTTP_URL_ENCODED_READER_CHAR_IS_X(c))
            {
                //
                // %X
                //
                count = 0;
                m_x1 = (What)(XOS_INET_HTTP_URL_ENCODED_READER_X2CHAR(c));
                m_get = &Derives::X2Get;
            }
            else
            {
                //
                // %[^X]
                //
                m_x1 = what;
                what = m_percent;
                m_get = &Derives::XGet;
            }
        }
        return count;
    }
    virtual ssize_t X2Get(What& what) {
        ssize_t count = -1;
        ssize_t length = 0;
        char c;

        if (0 < (length = m_reader.Read(&what, 1))) {
            count = length;
            c = (char)(what);
            if (XOS_INET_HTTP_URL_ENCODED_READER_CHAR_IS_X(c))
            {
                //
                // %XX
                //
                m_x2 = (What)(XOS_INET_HTTP_URL_ENCODED_READER_X2CHAR(c));
                what = (m_x1 << 4) | m_x2;
                m_get = &Derives::StartGet;
            }
            else
            {
                //
                // %X[^X]
                //
                m_x2 = what;
                what = m_x1;
                m_x1 = m_x2;
                m_get = &Derives::XGet;
            }
        }
        return count;
    }
    virtual ssize_t XGet(What& what) {
        ssize_t count = 0;
        what = m_x1;
        m_get = &Derives::StartGet;
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    typedef ssize_t (Derives::*MGet)(What&);
    Reader& m_reader;
    MGet m_get;
    ssize_t m_content_length;
    What m_percent;
    What m_space;
    What m_x1;
    What m_x2;
};

} // namespace http 
} // namespace xos 

#endif // _XOS_INET_HTTP_URLENCODEDREADER_HPP 
