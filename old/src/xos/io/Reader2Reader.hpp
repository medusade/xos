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
///   File: Reader2Reader.hpp
///
/// Author: $author$
///   Date: 5/30/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_IO_READER2READER_HPP
#define _XOS_IO_READER2READER_HPP

#include "xos/io/Reader.hpp"
#include "xos/base/Reader.hpp"

namespace xos {

typedef ExportBase Reader2ReaderExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Reader2ReaderT
///////////////////////////////////////////////////////////////////////
template
<typename TWhat = void,
 class TReader = Reader,
 class T2Reader = io::Reader,
 class TExtend = Reader2ReaderExtend,
 typename TWhence = StreamLockedInterface::Whence,
 TWhence VFromBegin = StreamLockedInterface::FromBegin,
 TWhence VFromEnd = StreamLockedInterface::FromEnd,
 TWhence VFromCurrent = StreamLockedInterface::FromCurrent,
 typename T2Whence = xos::io::Whence,
 T2Whence V2FromBegin = xos::io::FromBegin,
 T2Whence V2FromEnd = xos::io::FromEnd,
 T2Whence V2FromCurrent = xos::io::FromCurrent>

class _EXPORT_CLASS Reader2ReaderT: virtual public TReader, public TExtend {
public:
    typedef TReader Implements;
    typedef TExtend Extends;
    typedef TWhat WhatT;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Reader2ReaderT(T2Reader& reader): m_reader(reader) {
    }
    virtual ~Reader2ReaderT() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Read(WhatT* what, size_t size) {
        return m_reader.Read(what, size);
    }
    virtual ssize_t Seek(size_t size, TWhence whence = VFromBegin) {
        T2Whence t2whence = (VFromBegin!=whence)?((VFromEnd!=whence)?(V2FromCurrent):(V2FromEnd)):(V2FromBegin);
        return m_reader.Seek(size, t2whence);
    }
    virtual ssize_t Tell() const {
        return m_reader.Tell();
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    T2Reader& m_reader;
};

typedef Reader2ReaderT<> Reader2Reader;
typedef Reader2ReaderT<char, CharReader, io::Reader> CharReader2Reader;
typedef Reader2ReaderT<char, CharReader, io::CharReader> CharReader2CharReader;

namespace io {

} // namespace io 
} // namespace xos 

#endif // _XOS_IO_READER2READER_HPP 
