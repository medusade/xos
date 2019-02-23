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
///   Date: 4/25/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_IO_SOCKET_READER_HPP
#define _XOS_IO_SOCKET_READER_HPP

#include "xos/io/Reader.hpp"
#include "xos/io/socket/Sequence.hpp"
#include "xos/network/Socket.hpp"
#include "xos/base/Attacher.hpp"

namespace xos {
namespace io {
namespace socket {

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
        ssize_t amount = 0;
        ssize_t read;
        uint8_t* bytes;
        network::Socket* socket;
        if ((socket = this->AttachedTo()) && (bytes = (uint8_t*)(what)) && (size = (this->SizeOf(size)))) {
            do {
                if (0 >= (read = socket->Recv(bytes, size, 0))) {
                    if ((this->Logging())) {
                        XOS_LOG_TRACE("failed on socket->Recv(bytes, " << size << ", 0)");
                    }
                    return count;
                } else {
                    amount += read;
                    size -= read;
                    bytes += read;
                }
            } while (0 < size);
            count = this->SizeOf(amount);
        }
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef ReaderT<> Reader;

namespace attached {

typedef AttacherT<network::Socket*, int, 0, socket::Reader> ReaderImplement;
typedef AttachedT<network::Socket*, int, 0, ReaderImplement> ReaderExtend;
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
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    ReaderT(network::Socket* attachedTo): Extends(attachedTo) {}
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef ReaderT<> Reader;

} // namespace attached
} // namespace socket
} // namespace io 
} // namespace xos 

#endif // _XOS_IO_SOCKET_READER_HPP 
