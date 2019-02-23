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
///   File: Sockets.cpp
///
/// Author: $author$
///   Date: 9/26/2012
///////////////////////////////////////////////////////////////////////
#include "xos/network/windows/Sockets.hpp"
#include "xos/network/Sockets.cpp"
#include "xos/network/windows/Socket.cpp"
#include "xos/network/windows/local/Socket.cpp"
#include "xos/network/os/Socket.cpp"
//#include "sys/Socket.cpp"

#if defined(WINSOCK_2)
#define WINSOCK_VERSION_MAJOR 2
#define WINSOCK_VERSION_MAJOR 2
#else // defined(WINSOCK_2)
#define WINSOCK_VERSION_MAJOR 1
#define WINSOCK_VERSION_MAJOR 1
#endif // defined(WINSOCK_2)

namespace xos {
namespace network {

WORD wsaVersion = MAKEWORD(WINSOCK_VERSION_MAJOR, WINSOCK_VERSION_MAJOR);
WSAData wsaData;

bool Sockets::Startup() {
    bool success = false;
    int err;
    if (!(success = !(err = WSAStartup(wsaVersion, &wsaData)))) {
        XOS_LOG_ERROR("failed " << GetLastError() << " on WSAStartup()");
    }
    return success;
}
bool Sockets::Cleanup() {
    bool success = false;
    int err;
    if (!(success = !(err = WSACleanup()))) {
        XOS_LOG_ERROR("failed " << GetLastError() << " on WSACleanup()");
    }
    return success;
}
int Sockets::GetLastError() {
    int err = WSAGetLastError();
    return err;
}

} // namespace network 
} // namespace xos 

namespace xos {
namespace network {
namespace windows {

} // namespace windows 
} // namespace network 
} // namespace xos 
