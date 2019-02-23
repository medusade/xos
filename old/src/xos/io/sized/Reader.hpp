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
///   File: Reader.hpp
///
/// Author: $author$
///   Date: 5/14/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_IO_SIZED_READER_HPP
#define _XOS_IO_SIZED_READER_HPP

#include "xos/io/Reader.hpp"
#include "xos/io/Seeked.hpp"

namespace xos {
namespace io {
namespace sized {

typedef io::Reader ReaderImplement;
typedef SeekedT<0, io::Reader> ReaderExtend;
///////////////////////////////////////////////////////////////////////
///  Class: ReaderT
///////////////////////////////////////////////////////////////////////
template
<typename TWhat = void, typename TSized = char,
 typename TEnd = int, TEnd VEnd = 0,
 class TImplement = ReaderImplement, class TExtend = ReaderExtend>

class _EXPORT_CLASS ReaderT: virtual public TImplement, public TExtend {
public:
    typedef TImplement Implements;
    typedef TExtend Extends;
    typedef TWhat WhatT;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    ReaderT(TImplement& reader, ssize_t length, size_t tell = 0)
    : Extends(length, length, tell), m_reader(reader) {
    }
    virtual ~ReaderT() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Read(WhatT* what, size_t size) {
        if ((what) && (0 < size)) {
            ssize_t length;
            if (0 > (length = this->Length())) {
                length = m_reader.Read(what, size);
            } else {
                size_t tell;
                if (length < (((tell = this->Tell()) + size))) {
                    size = length - tell;
                }
                if (0 < (length = m_reader.Read(what, size))) {
                    this->SetTell(tell + length);
                }
            }
            return length;
        }
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    TImplement& m_reader;
};
typedef ReaderT<> Reader;

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
typedef ReaderT<char, char, int, 0, io::CharReader, SeekedT<0, io::CharReader> > CharReader;
typedef ReaderT<wchar_t, wchar_t, int, 0, io::WCharReader, SeekedT<0, io::WCharReader> > WCharReader;
typedef ReaderT<tchar_t, tchar_t, int, 0, io::TCharReader, SeekedT<0, io::TCharReader> > TCharReader;

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
typedef ReaderT<BYTE, BYTE, int, 0, io::BYTEReader, SeekedT<0, io::BYTEReader> > BYTEReader;
typedef ReaderT<WORD, WORD, int, 0, io::WORDReader, SeekedT<0, io::WORDReader> > WORDReader;

} // namespace sized
} // namespace io 
} // namespace xos 

#endif // _XOS_IO_SIZED_READER_HPP 
