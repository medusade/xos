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
///   File: Reader.hpp
///
/// Author: $author$
///   Date: 11/25/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_BASE_READER_HPP
#define _XOS_BASE_READER_HPP

#include "xos/base/Stream.hpp"

namespace xos {

template
<typename TWhat = void,
 class TImplement = Stream,
 typename TWhence = StreamLockedInterface::Whence,
 TWhence VFromBegin = StreamLockedInterface::FromBegin>
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS ReaderT: virtual public TImplement {
public:
    typedef TImplement Implements;
    typedef TWhat WhatT;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Read(WhatT* what, size_t size) { return -1; }
    virtual ssize_t Write(const WhatT* what, ssize_t size = -1) { return -1; }

    virtual ssize_t Fill() { return -1; }
    virtual ssize_t Flush() { return -1; }

    virtual ssize_t Reset() { return Seek(0); }
    virtual ssize_t Seek(size_t size, TWhence whence = VFromBegin) { return -1; }
    virtual ssize_t Tell() const { return -1; }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

typedef ReaderT<void, Stream> Reader;

typedef ReaderT<char, CharStream> CharReader;
typedef ReaderT<wchar_t, WCharStream> WCharReader;
typedef ReaderT<tchar_t, TCharStream> TCharReader;

typedef ReaderT<BYTE, BYTEStream> BYTEReader;
typedef ReaderT<WORD, WORDStream> WORDReader;

} // namespace xos

#endif // _XOS_BASE_READER_HPP 
