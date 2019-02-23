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
///   File: TcpConnection.hpp
///
/// Author: $author$
///   Date: 5/25/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_INET_HTTP_SERVER_MEDUSA_TCPCONNECTION_HPP
#define _XOS_INET_HTTP_SERVER_MEDUSA_TCPCONNECTION_HPP

#include "xos/network/Sockets.hpp"
#include "xos/mt/Queue.hpp"
#include "xos/io/Reader.hpp"
#include "xos/io/Writer.hpp"
#include "xos/base/Reference.hpp"

namespace xos {
namespace http {
namespace server {
namespace medusa {

typedef io::Reader TcpConnectionReader;
typedef io::Writer TcpConnectionWriter;
///////////////////////////////////////////////////////////////////////
///  Class: TcpConnectionImplement
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS TcpConnectionImplement
: virtual public TcpConnectionReader, virtual public TcpConnectionWriter {
};
typedef ExportBase TcpConnectionExtend;
///////////////////////////////////////////////////////////////////////
///  Class: TcpConnection
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS TcpConnection
: virtual public TcpConnectionImplement, public TcpConnectionExtend {
public:
    typedef TcpConnectionImplement Implements;
    typedef TcpConnectionExtend Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    TcpConnection(const network::SocketReference& sock): m_sock(sock) {
    }
    TcpConnection(const TcpConnection& copy): m_sock(copy.m_sock) {
    }
    TcpConnection() {
    }
    virtual ~TcpConnection() {
        Close();
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void Close() {
        m_sock.Clear();
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Read(void* what, size_t size) {
        uint8_t* byte;
        if (((m_sock) != 0) && (byte = ((uint8_t*)what)) && (size)) {
            network::Socket& sock = *m_sock;
            ssize_t count = 0;
            ssize_t amount;
            while (0 < (size)) {
                if (0 > (amount = sock.Recv(byte, size, 0))) {
                    return amount;
                } else {
                    if (0 < (size)) {
                        byte += amount;
                        count += amount;
                        size -= amount;
                    } else {
                        return count;
                    }
                }
            }
            return count;
        }
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Write(const void* what, ssize_t size = -1) {
        const uint8_t* byte;
        if (((m_sock) != 0) && (byte = ((const uint8_t*)what)) && (size)) {
            network::Socket& sock = *m_sock;
            ssize_t count = 0;
            ssize_t amount;
            if (0 < (size)) {
                if (0 > (amount = sock.Send(byte, size, 0))) {
                    return amount;
                } else {
                    count += amount;
                }
            }
            return count;
        }
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    network::SocketReference m_sock;
};

typedef mt::QueueT<TcpConnection> TcpConnections;

} // namespace medusa
} // namespace server 
} // namespace http 
} // namespace xos 

#endif // _XOS_INET_HTTP_SERVER_MEDUSA_TCPCONNECTION_HPP 
