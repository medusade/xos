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
///   Date: 5/16/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_IO_ATTACHED_WRITER_HPP
#define _XOS_IO_ATTACHED_WRITER_HPP

#include "xos/io/Writer.hpp"
#include "xos/io/attached/Sequence.hpp"

namespace xos {
namespace io {
namespace attached {

///////////////////////////////////////////////////////////////////////
///  Class: WriterSequence
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS WriterSequence
: virtual public Sequence, virtual public io::Writer {};
///////////////////////////////////////////////////////////////////////
///  Class: WriterT
///////////////////////////////////////////////////////////////////////
template
<typename TWhat = void, typename TSized = char,
 typename TEnd = int, TEnd VEnd = 0, class TImplement = WriterSequence>

class _EXPORT_CLASS WriterT: virtual public TImplement {
public:
    typedef TImplement Implements;
    typedef TWhat WhatT;
    typedef TSized SizedT;
    typedef TEnd EndT;
    enum { End = VEnd };
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Write(const WhatT* what, ssize_t length) {
        ssize_t count = 0;
        ssize_t amount;
        ssize_t told;
        WhatT* attached;
        SizedT* sizedAttached;
        const SizedT* sizedWhat;
        if ((sizedAttached = (SizedT*)(attached = this->AttachedTo()))
            && (sizedWhat = ((const SizedT*)what)) && (length) && (0 <= (told = this->Tell()))) {
            ssize_t size;
            if (0 > (size = this->Size())) {
                if (0 > (length)) {
                    SizedT sized;
                    for (size_t i = 0; ((sized = sizedWhat[i]) != End); ++i, ++count) {
                        sizedAttached[told+i] = sized;
                    }
                } else {
                    for (size_t i = 0; i < length; ++i, ++count) {
                        sizedAttached[told+i] = sizedWhat[i];
                    }
                }
            } else {
                if (0 > (length)) {
                    for (size_t i = 0; i < size; ++i, ++count) {
                        const SizedT& sized = sizedWhat[i];
                        if ((sized != End)) {
                            sizedAttached[told+i] = sized;
                        } else {
                            break;
                        }
                    }
                } else {
                    if (size < (told + length)) {
                        length = size - told;
                    }
                    for (size_t i = 0; i < length; ++i, ++count) {
                        sizedAttached[told+i] = sizedWhat[i];
                    }
                }
            }
            if (0 < (count)) {
                if ((amount = this->SetLength(told += count)) != told) {
                    XOS_LOG_ERROR("failed " << amount << " on SetLength(" << told << ")");
                    return -1;
                }
                if ((amount = this->Seek(told)) != told) {
                    XOS_LOG_ERROR("failed " << amount << " on Seek(" << told << ")");
                    return -1;
                }
            }
        }
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef WriterT<> Writer;

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS CharWriterSequence
: virtual public CharSequence, virtual public io::CharWriter {};
typedef WriterT<char, char, int, 0, CharWriterSequence> CharWriter;

class _EXPORT_CLASS WCharWriterSequence
: virtual public WCharSequence, virtual public io::WCharWriter {};
typedef WriterT<wchar_t, wchar_t, int, 0, WCharWriterSequence> WCharWriter;

class _EXPORT_CLASS TCharWriterSequence
: virtual public TCharSequence, virtual public io::TCharWriter {};
typedef WriterT<tchar_t, tchar_t, int, 0, TCharWriterSequence> TCharWriter;

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS BYTEWriterSequence
: virtual public BYTESequence, virtual public io::BYTEWriter {};
typedef WriterT<BYTE, BYTE, int, 0, BYTEWriterSequence> BYTEWriter;

} // namespace attached
} // namespace io 
} // namespace xos 

#endif // _XOS_IO_ATTACHED_WRITER_HPP 
