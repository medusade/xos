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
///   File: Writer.hpp
///
/// Author: $author$
///   Date: 2/19/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_BASE_WRITER_HPP
#define _XOS_BASE_WRITER_HPP

#include "xos/base/String.hpp"

namespace xos {

///////////////////////////////////////////////////////////////////////
///  Class: WriterBaseT
///////////////////////////////////////////////////////////////////////
template <typename TWhat, class TImplement = InterfaceBase>

class _EXPORT_CLASS WriterBaseT: virtual public TImplement {
public:
    typedef TImplement Implements;
    typedef TWhat What;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Write(const What* what, ssize_t length=-1) {
        ssize_t count = -Error::NotImplemented;
        return count;
    }
    virtual ssize_t Flush() {
        ssize_t count = 0;
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

typedef WriterBaseT<void> WriterBase;

///////////////////////////////////////////////////////////////////////
///  Class: WriterT
///////////////////////////////////////////////////////////////////////
template
<typename TWhat,
 typename TEnd = TWhat, TEnd VEnd = 0,
 class TImplement = WriterBaseT<TWhat, InterfaceBase> >

class _EXPORT_CLASS WriterT: virtual public TImplement {
public:
    typedef TImplement Implements;
    typedef TWhat What;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Writex(const uint8_t* bytes, ssize_t length=-1, char a = 'a', char between = 0) {
        ssize_t count = WriteX(bytes, length, a, between);
        return count;
    }
    virtual ssize_t WriteX(const uint8_t* bytes, ssize_t length=-1, char A = 'A', char between = 0) {
        ssize_t count = 0;
        const uint8_t* byte;
        if ((byte = bytes)) {
            What t = (What)(between);
            ssize_t written;
            uint8_t b;
            What x[2];
            if (0 <= length) {
                for (; 0 < length; --length) {
                    if ((byte != bytes) && (between)) {
                        if (0 > (written = Write(&t, 1)))
                            return written;
                        count += written;
                    }
                    b = (*byte++);
                    x[0] = DToX(b >> 4, A);
                    x[1] = DToX(b & 15, A);
                    if (0 > (written = Write(x, 2)))
                        return written;
                    count += written;
                }
            } else {
                for (; (b = (*byte)); ++byte) {
                    if ((byte != bytes) && (between)) {
                        if (0 > (written = Write(&t, 1)))
                            return written;
                        count += written;
                    }
                    x[0] = DToX(b >> 4, A);
                    x[1] = DToX(b & 15, A);
                    if (0 > (written = Write(x, 2)))
                        return written;
                    count += written;
                }
            }
        }
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    inline What DToX(uint8_t d, char A = 'A') const {
        What x = (What)(0);
        if ((0 <= d) && (9 >= d))
            x = (What)(('0') +  d);
        else
        if ((10 <= d) && (15 >= d))
            x = (What)((A) + (d - 10));
        return x;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t WriteFormatted(const What* format, ...) {
        ssize_t count = -Error::NotImplemented;
        return count;
    }
    virtual ssize_t WriteFormattedV(const What* format, va_list va) {
        ssize_t count = -Error::NotImplemented;
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Write(const What* what, ssize_t length=-1) {
        ssize_t count = -Error::NotImplemented;
        return count;
    }
    virtual ssize_t Flush() {
        ssize_t count = 0;
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
typedef WriterT<char> CharWriter;
typedef WriterT<tchar_t> TCharWriter;
typedef WriterT<wchar_t> WCharWriter;

///////////////////////////////////////////////////////////////////////
///  Class: StringWriterT
///////////////////////////////////////////////////////////////////////
template
<typename TString, typename TChar,
 typename TEnd = TChar, TEnd VEnd = 0,
 class TImplement = WriterT<TChar, TEnd, VEnd>,
 class TExtend = ExportBase>

class _EXPORT_CLASS StringWriterT: virtual public TImplement, public TExtend {
public:
    typedef TImplement Implements;
    typedef TExtend Extends;
    typedef TChar CharT;
    typedef TString StringT;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    StringWriterT(StringT& string): m_string(string) {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Write(const CharT* what, ssize_t length=-1) {
        ssize_t count = m_string.Length();
        if (0 > (length)) m_string.Append(what);
        else m_string.Append(what, length);
        return m_string.Length() - count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    StringT& m_string;
};

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
typedef StringWriterT<String, char> StringWriter;
typedef StringWriterT<TString, tchar_t> TStringWriter;
typedef StringWriterT<WString, wchar_t> WStringWriter;

} // namespace xos

#endif // _XOS_BASE_WRITER_HPP 
