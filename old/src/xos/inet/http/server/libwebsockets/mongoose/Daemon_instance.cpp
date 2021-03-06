///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2013 $organization$
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
///   File: Daemon.cpp
///
/// Author: $author$
///   Date: 12/8/2013
///////////////////////////////////////////////////////////////////////
#include "xos/inet/http/server/libwebsockets/mongoose/Daemon.hpp"
#include "xos/inet/http/server/libwebsockets/Daemon.cpp"
#include "xos/inet/http/server/mongoose/Daemon.cpp"
#include "xos/inet/http/server/Daemon.cpp"
#include "xos/os/server/Daemon.cpp"
#include "xos/os/Daemon.cpp"

namespace xos {
namespace http {
namespace server {
namespace libwebsockets {
namespace mongoose {

static Daemon the_daemon(Processor::GetTheInstance());

} // namespace mongoose
} // namespace libwebsockets 
} // namespace server 
} // namespace http 
} // namespace xos 

namespace xos {

Daemon& Daemon::GetTheInstance() {
    return http::server::libwebsockets::mongoose::the_daemon;
}

} // namespace xos
