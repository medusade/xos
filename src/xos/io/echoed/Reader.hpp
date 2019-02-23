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
///   Date: 7/4/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_IO_ECHOED_READER_HPP
#define _XOS_IO_ECHOED_READER_HPP

#include "xos/io/Reader.hpp"
#include "xos/io/Writer.hpp"

namespace xos {
namespace io {
namespace echoed {

typedef io::Reader ReaderImplement;
typedef ExportBase ReaderExtend;
///////////////////////////////////////////////////////////////////////
///  Class: ReaderT
///////////////////////////////////////////////////////////////////////
template
<typename TWhat = void, typename TSized = char,
 typename TEnd = int, TEnd VEnd = 0,
 class TReader = io::Reader, class TWriter = io::Writer,
 class TImplement = ReaderImplement, class TExtend = ReaderExtend>

class _EXPORT_CLASS ReaderT: virtual public TImplement, public TExtend {
public:
    typedef TImplement Implements;
    typedef TExtend Extends;

    typedef TWriter Writer;
    typedef TWhat WhatT;
    typedef TSized SizedT;
    typedef TEnd EndT;
    enum { End = VEnd };

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    ReaderT
    (Reader& reader, Writer& writer)
    : m_reader(reader), m_writer(writer) {
    }
    virtual ~ReaderT() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Read(WhatT* what, size_t size) {
        ssize_t count = 0;
        if (0 < (count = m_reader.Read(what, size))) {
            ssize_t amount;
            if (0 > (amount = m_writer.Write(what, size))) {
                XOS_LOG_ERROR("failed " << amount << " on Write(..., " << size << ")");
            }
        }
        return count;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    Reader& m_reader;
    Writer& m_writer;
};
typedef ReaderT<> Reader;

} // namespace echoed 
} // namespace io 
} // namespace xos 

#endif // _XOS_IO_ECHOED_READER_HPP 
