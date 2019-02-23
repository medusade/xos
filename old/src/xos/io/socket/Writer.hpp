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
///   Date: 4/25/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_IO_SOCKET_WRITER_HPP
#define _XOS_IO_SOCKET_WRITER_HPP

#include "xos/io/Writer.hpp"
#include "xos/io/socket/Sequence.hpp"
#include "xos/network/Socket.hpp"

namespace xos {
namespace io {
namespace socket {

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
        ssize_t written;
        xos::network::Socket* socket;
        if ((socket = this->AttachedTo()) && (what)) {
            if (0 < (length = (sizeof(SizedT)*length))) {
                if (0 >= (written = socket->Send(what, length, 0))) {
                    if ((this->Logging())) {
                        XOS_LOG_ERROR("failed on socket->Send(what, " << length << ")");
                    }
                } else {
                    count += this->SizeOf(written);
                }
            } else {
                for (const SizedT* sized = (const SizedT*)(what); *sized; ++sized) {
                    if (0 >= (written = socket->Send(sized, sizeof(SizedT), 0))) {
                        if ((this->Logging())) {
                            XOS_LOG_ERROR("failed on socket->Send(what, " << sizeof(SizedT) << ")");
                        }
                        break;
                    } else {
                        count += this->SizeOf(written);
                    }
                }
            }
        }
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef WriterT<> Writer;

} // namespace socket 
} // namespace io 
} // namespace xos 

#endif // _XOS_IO_SOCKET_WRITER_HPP 
