///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2012 $organization$
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
///   File: Socket.cpp
///
/// Author: $author$
///   Date: 10/2/2012
///////////////////////////////////////////////////////////////////////
#include "xos/network/unix/Socket.hpp"

namespace xos {
namespace network {

Socket* Socket::New(int domain, int type, int protocol) {
    Socket* s = 0;
    bool isOpen = false;
    unix::socket_fd_t detached = 0;
    //
    // Create and attach bsd socket
    //
    if ((isOpen = (0 <= (detached = socket(domain, type, (AF_LOCAL != domain)?(protocol):(0)))))) {
        s = new unix::Socket(detached, isOpen);
    } else {
        XOS_LOG_ERROR("failed " << errno << " on socket()");
    }
    return s;
}
void Socket::Delete(Socket* s) {
    delete s;
}

} // namespace network 
} // namespace xos 

namespace xos {
namespace network {
namespace unix {

} // namespace unix 
} // namespace network 
} // namespace xos 
