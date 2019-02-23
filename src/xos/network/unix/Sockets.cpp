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
///   Date: 10/3/2012
///////////////////////////////////////////////////////////////////////
#include "xos/network/unix/Sockets.hpp"
#include "xos/network/Sockets.cpp"
#include "xos/network/unix/Socket.cpp"

namespace xos {
namespace network {

bool Sockets::Startup() {
    bool success = true;
    return success;
}
bool Sockets::Cleanup() {
    bool success = true;
    return success;
}
int Sockets::GetLastError() {
    int err = errno;
    return err;
}

} // namespace network 
} // namespace xos 

namespace xos {
namespace network {
namespace unix {

} // namespace unix 
} // namespace network 
} // namespace xos 
