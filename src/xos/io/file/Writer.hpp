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
///   Date: 4/19/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_IO_FILE_WRITER_HPP
#define _XOS_IO_FILE_WRITER_HPP

#include "xos/io/file/Sequence.hpp"
#include "xos/io/Writer.hpp"

namespace xos {
namespace io {
namespace file {

///////////////////////////////////////////////////////////////////////
///  Class: WriterSequence
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS WriterSequence
: virtual public Sequence, virtual public io::Writer
{};
typedef WriterT<void, char, int, 0, WriterSequence> WriterImplement;
///////////////////////////////////////////////////////////////////////
///  Class: WriterT
///////////////////////////////////////////////////////////////////////
template
<typename TWhat = void, typename TSized = char,
 typename TEnd = int, TEnd VEnd = 0,
 class TImplement = WriterImplement>

class _EXPORT_CLASS WriterT: virtual public TImplement {
public:
    typedef TImplement Implements;
    typedef TWhat WhatT;
    typedef TSized SizedT;
    typedef TEnd EndT;
    enum { End = VEnd };
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Write(const WhatT* what, ssize_t length = -1) {
        ssize_t count = 0;
        FILE* file;
        if ((file = this->AttachedTo()) && (what)) {
            if (0 < (length)) {
                if (0 >= (count = fwrite(what, sizeof(SizedT), length, file))) {
                    if ((this->Logging())) {
                        XOS_LOG_ERROR("failed on fwrite(what, " << sizeof(SizedT) << ", " << length << ", file)");
                    }
                }
            } else {
                size_t written;
                for (const SizedT* sized = (const SizedT*)(what); *sized; ++sized) {
                    if (0 >= (written = fwrite(sized, sizeof(SizedT), 1, file))) {
                        if ((this->Logging())) {
                            XOS_LOG_ERROR("failed on fwrite(what, " << sizeof(SizedT) << ", 1, file)");
                        }
                        break;
                    }
                    ++count;
                }
            }
        }
        return count;
    }
    virtual ssize_t Flush() {
        ssize_t count = 0;
        FILE* file;
        if ((file = this->AttachedTo())) {
            int err;
            if ((err = fflush(file))) {
                if ((this->Logging())) {
                    XOS_LOG_ERROR("failed on fflush(file)");
                }
            }
        }
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t WriteFormattedV(const WhatT* format, va_list va) {
        ssize_t count = 0;
        FILE* file;
        if ((file = this->AttachedTo()) && (format)) {
            if (0 > (count = vfprintf(file, (const SizedT*)(format), va))) {
                if ((this->Logging())) {
                    XOS_LOG_ERROR("failed on vfprintf(file, format, va)");
                }
            }
        }
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef WriterT<> Writer;

namespace attached {

typedef AttacherT<FILE*, int, 0, file::Writer> WriterImplement;
typedef AttachedT<FILE*, int, 0, WriterImplement> WriterExtend;
///////////////////////////////////////////////////////////////////////
///  Class: WriterT
///////////////////////////////////////////////////////////////////////
template
<typename TWhat = void, typename TSized = char,
 typename TEnd = int, TEnd VEnd = 0,
 class TImplement = WriterImplement, class TExtend = WriterExtend>

class _EXPORT_CLASS WriterT: virtual public TImplement, public TExtend {
public:
    typedef TImplement Implements;
    typedef TExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    WriterT(FILE* attachedTo): Extends(attachedTo) {}
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef WriterT<> Writer;

} // namespace attached
} // namespace file
} // namespace io 
} // namespace xos 

#endif // _XOS_IO_FILE_WRITER_HPP 
