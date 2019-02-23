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
///   File: socket.cpp
///
/// Author: $author$
///   Date: Sep 27, 2012
///////////////////////////////////////////////////////////////////////
#include "xos/os/Logger.hpp"
#include <sys/socket.h>

int sendmsg(SOCKET s, const struct msghdr* msg, int flags) {
    XOS_LOG_ERROR("sendmsg unsupported in WinSock");
    WSASetLastError(WSAEINVAL);
    return SOCKET_ERROR;
}
int recvmsg(SOCKET s, struct msghdr* msg, int flags) {
    XOS_LOG_ERROR("recvmsg unsupported in WinSock");
    WSASetLastError(WSAEINVAL);
    return SOCKET_ERROR;
}

namespace xos {
} // namespace xos
