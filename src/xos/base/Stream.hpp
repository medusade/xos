///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2012 $organization$
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
///   File: Stream.hpp
///
/// Author: $author$
///   Date: Aug 15, 2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_STREAM_HPP_
#define _XOS_STREAM_HPP_

#include "xos/base/Locked.hpp"

namespace xos {

class EXPORT_CLASS StreamLockedInterface: virtual public LockedInterface {
public:
    typedef LockedInterface Implements;
    enum Whence {
        FromBegin,
        FromEnd,
        FromCurrent
    };
};

template
<class TWhat=void, class TEnd=int, TEnd VEnd=0,
 class TImplement=StreamLockedInterface, 
 typename TWhence=StreamLockedInterface::Whence,
 TWhence VFromBegin=StreamLockedInterface::FromBegin, 
 typename TStatus=LockedInterface::Status,
 TStatus VSuccess=LockedInterface::Success>

class EXPORT_CLASS StreamBaseT: virtual public TImplement {
public:
    typedef TImplement Implements;
    typedef TWhat WhatT;
    typedef TEnd EndT;

    virtual ssize_t Read(WhatT* what, size_t size) = 0;
    virtual ssize_t Write(const WhatT* what, ssize_t size = -1) = 0;

    virtual ssize_t Fill() = 0;
    virtual ssize_t Flush() = 0;

    virtual ssize_t Seek(size_t size, TWhence whence = VFromBegin) = 0;
    virtual ssize_t Tell() const = 0;

    virtual bool Lock(){ return true; }
    virtual bool Unlock(){ return true; }
    virtual TStatus TryLock(){ return VSuccess; }
    virtual TStatus TimedLock(mseconds_t waitMilliseconds){ return VSuccess; }

protected:
    static const EndT End = (EndT)(VEnd);
};

typedef StreamBaseT<void> StreamBase;

typedef StreamBaseT<char> CharStreamBase;
typedef StreamBaseT<wchar_t> WCharStreamBase;
typedef StreamBaseT<tchar_t> TCharStreamBase;

typedef StreamBaseT<uint8_t> ByteStreamBase;
typedef StreamBaseT<uint16_t> WordStreamBase;
typedef StreamBaseT<uint32_t> LongWordStreamBase;

typedef StreamBaseT<BYTE> BYTEStreamBase;
typedef StreamBaseT<WORD> WORDStreamBase;

template <class TImplement=StreamBase>
class EXPORT_CLASS StreamT: virtual public TImplement {
public:
    typedef TImplement Implements;
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
};

typedef StreamT<StreamBase> Stream;

typedef StreamT<CharStreamBase> CharStream;
typedef WCharStreamBase WCharStream;
typedef TCharStreamBase TCharStream;

typedef ByteStreamBase ByteStream;
typedef WordStreamBase WordStream;
typedef LongWordStreamBase LongWordStream;

typedef BYTEStreamBase BYTEStream;
typedef WORDStreamBase WORDStream;

} // namespace xos

#endif // _XOS_STREAM_HPP_ 
