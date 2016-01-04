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
///   Date: 5/10/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_IO_ATTACHED_READER_HPP
#define _XOS_IO_ATTACHED_READER_HPP

#include "xos/io/Reader.hpp"
#include "xos/io/attached/Sequence.hpp"

namespace xos {
namespace io {
namespace attached {

///////////////////////////////////////////////////////////////////////
///  Class: ReaderSequence
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS ReaderSequence
: virtual public const_Sequence, virtual public io::Reader {};
///////////////////////////////////////////////////////////////////////
///  Class: ReaderT
///////////////////////////////////////////////////////////////////////
template
<typename TWhat = void, typename TSized = char,
 typename TEnd = int, TEnd VEnd = 0, class TImplement = ReaderSequence>

class _EXPORT_CLASS ReaderT: virtual public TImplement {
public:
    typedef TImplement Implements;
    typedef TWhat WhatT;
    typedef TSized SizedT;
    typedef TEnd EndT;
    enum { End = VEnd };
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Read(WhatT* what, size_t size) {
        ssize_t count = 0;
        ssize_t amount;
        ssize_t told;
        const WhatT* attached;
        const SizedT* sizedAttached;
        SizedT* sizedWhat;
        if ((sizedAttached = (const SizedT*)(attached = this->AttachedTo()))
            && (sizedWhat = ((SizedT*)what)) && (size) && (0 <= (told = this->Tell()))) {
            ssize_t length;
            if (0 > (length = this->Length())) {
                for (size_t i = 0; i < size; ++i) {
                    const SizedT& sized = sizedAttached[told+i];
                    if ((sized != End)) {
                        sizedWhat[i] = sized;
                        ++count;
                    }
                }
            } else {
                if (length < (told + size)) {
                    size = length - told;
                }
                for (size_t i = 0; i < size; ++i) {
                    const SizedT& sized = sizedAttached[told+i];
                    sizedWhat[i] = sized;
                    ++count;
                }
            }
            if (0 < (count)) {
                if ((amount = this->Seek(told += count)) != told) {
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
typedef ReaderT<> Reader;

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS BYTEReaderSequence
: virtual public const_BYTESequence, virtual public io::BYTEReader {};
typedef ReaderT<BYTE, BYTE, int, 0, BYTEReaderSequence> BYTEReader;

} // namespace attached
} // namespace io 
} // namespace xos 

#endif // _XOS_IO_ATTACHED_READER_HPP 
