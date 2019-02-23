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
///   File: SizedReader.hpp
///
/// Author: $author$
///   Date: 6/1/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_BASE_SIZEDREADER_HPP
#define _XOS_BASE_SIZEDREADER_HPP

#include "xos/base/Reader.hpp"
#include "xos/os/Logger.hpp"

namespace xos {

///////////////////////////////////////////////////////////////////////
///  Class: SizedReaderT
///////////////////////////////////////////////////////////////////////
template
<typename TWhat = void, class TReader = Reader,
 class TImplement = TReader, class TExtend = ExportBase>

class _EXPORT_CLASS SizedReaderT: virtual public TImplement, public TExtend {
public:
    typedef TImplement Implements;
    typedef TExtend Extends;
    typedef TWhat WhatT;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    SizedReaderT
    (TReader& reader, ssize_t length = -1, size_t tell = 0)
    : m_reader(reader), m_length(length), m_tell(tell) {
    }
    virtual ~SizedReaderT() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Read(WhatT* what, size_t size) {
        ssize_t count = 0;
        if ((what) && (size)) {
            if (0 <= (m_length)) {
                if (m_length < (m_tell + size))
                    size = m_length - m_tell;
            }
            if (0 > (count = m_reader.Read(what, size))) {
                XOS_LOG_ERROR("failed " << count << " on Read(what, " << size << ")");
            } else {
                m_tell += count;
            }
        }
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    TReader& m_reader;
    ssize_t m_length;
    size_t m_tell;
};

typedef SizedReaderT<> SizedReader;

typedef SizedReaderT<char, CharReader> SizedCharReader;
typedef SizedReaderT<wchar_t, WCharReader> SizedWCharReader;
typedef SizedReaderT<tchar_t, TCharReader> SizedTCharReader;

typedef SizedReaderT<BYTE, BYTEReader> SizedBYTEReader;
typedef SizedReaderT<WORD, WORDReader> SizedWORDReader;

} // namespace xos

#endif // _XOS_BASE_SIZEDREADER_HPP 
