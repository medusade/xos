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
///   Date: 4/19/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_IO_FILE_READER_HPP
#define _XOS_IO_FILE_READER_HPP

#include "xos/io/file/Sequence.hpp"
#include "xos/io/Reader.hpp"

namespace xos {
namespace io {
namespace file {

///////////////////////////////////////////////////////////////////////
///  Class: ReaderSequence
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS ReaderSequence
: virtual public Sequence, virtual public io::Reader
{};
///////////////////////////////////////////////////////////////////////
///  Class: ReaderT
///////////////////////////////////////////////////////////////////////
template
<typename TWhat = void, typename TSized = char,
 typename TEnd = int, TEnd VEnd = 0,
 class TImplement = ReaderSequence>

class _EXPORT_CLASS ReaderT: virtual public TImplement {
public:
    typedef TImplement Implements;
    typedef TWhat WhatT;
    typedef TSized SizedT;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Read(WhatT* what, size_t size) {
        ssize_t count = 0;
        FILE* file;
        if ((file = this->AttachedTo()) && (what) && (size)) {
            if (0 >= (count = fread(what, sizeof(SizedT), size, file))) {
                if ((this->Logging())) {
                    XOS_LOG_TRACE("failed on fread(what, " << sizeof(SizedT) << ", " << size << ", file)");
                }
            }
        }
        return count;
    }
    virtual ssize_t ReadFormattedV(const WhatT* format, va_list va) {
        ssize_t count = 0;
        FILE* file;
        if ((file = this->AttachedTo()) && (format)) {
            if (0 > (count = vfscanf(file, (const SizedT*)(format), va))) {
                if ((this->Logging())) {
                    XOS_LOG_TRACE("failed on vfscanf(file, \"" << (const SizedT*)(format) << "\", va)");
                }
            }
        }
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef ReaderT<> Reader;

} // namespace file 
} // namespace io 
} // namespace xos 

#endif // _XOS_IO_FILE_READER_HPP 
