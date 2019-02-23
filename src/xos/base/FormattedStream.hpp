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
///   File: FormattedStream.hpp
///
/// Author: $author$
///   Date: 3/6/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_BASE_FORMATTEDSTREAM_HPP
#define _XOS_BASE_FORMATTEDSTREAM_HPP

#include "xos/base/Stream.hpp"
#include "xos/base/Coded.hpp"

namespace xos {

///////////////////////////////////////////////////////////////////////
///  Class: FormattedStreamT
///////////////////////////////////////////////////////////////////////
template
<class TImplement,
 typename TWhat = void, typename TEnd = int,
 typename TWhence = StreamLockedInterface::Whence,
 TWhence VFromBegin = StreamLockedInterface::FromBegin>

class _EXPORT_CLASS FormattedStreamT: virtual public TImplement {
public:
    typedef TImplement Implements;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t ReadFormatted(const char* format, ...) {
        ssize_t count = 0;
        va_list va;
        va_start(va, format);
        count = ReadFormattedV(format, va);
        va_end(va);
        return count;
    }
    virtual ssize_t ReadFormattedV(const char* format, va_list va) {
        ssize_t count = 0;
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t WriteFormatted(const char* format, ...) {
        ssize_t count = 0;
        va_list va;
        va_start(va, format);
        count = WriteFormattedV(format, va);
        va_end(va);
        return count;
    }
    virtual ssize_t WriteFormattedV(const char* format, va_list va) {
        ssize_t count = 0;
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t ReadFormatted(const wchar_t* format, ...) {
        ssize_t count = 0;
        va_list va;
        va_start(va, format);
        count = ReadFormattedV(format, va);
        va_end(va);
        return count;
    }
    virtual ssize_t ReadFormattedV(const wchar_t* format, va_list va) {
        ssize_t count = 0;
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t WriteFormatted(const wchar_t* format, ...) {
        ssize_t count = 0;
        va_list va;
        va_start(va, format);
        count = WriteFormattedV(format, va);
        va_end(va);
        return count;
    }
    virtual ssize_t WriteFormattedV(const wchar_t* format, va_list va) {
        ssize_t count = 0;
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Read(TWhat* what, size_t size) { return 0; }
    virtual ssize_t Write(const TWhat* what, ssize_t size = -1) { return 0; }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Fill(){ return 0; }
    virtual ssize_t Flush(){ return 0; }
    virtual ssize_t Seek(size_t size, TWhence whence = VFromBegin) { return 0; }
    virtual ssize_t Tell() const { return 0; }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

typedef FormattedStreamT<CharStreamBase, char> FormattedStream;
typedef FormattedStreamT<TCharStreamBase, tchar_t> TFormattedStream;
typedef FormattedStreamT<WCharStreamBase, wchar_t> WFormattedStream;

typedef FormattedStreamT<Coded<char, CharStreamBase>, char> CodedFormattedStream;
typedef FormattedStreamT<Coded<tchar_t, TCharStreamBase>, tchar_t> TCodedFormattedStream;
typedef FormattedStreamT<Coded<wchar_t, WCharStreamBase>, wchar_t> WCodedFormattedStream;

} // namespace xos

#endif // _XOS_BASE_FORMATTEDSTREAM_HPP
