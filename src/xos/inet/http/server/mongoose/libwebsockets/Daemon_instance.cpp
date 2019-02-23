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
///   Date: 12/23/2013
///////////////////////////////////////////////////////////////////////
#include "xos/inet/http/server/mongoose/libwebsockets/Daemon.hpp"

namespace xos {
namespace http {
namespace server {
namespace mongoose {
namespace libwebsockets {

static Daemon the_daemon(Processor::GetTheInstance());

} // namespace libwebsockets
} // namespace mongoose 
} // namespace server 
} // namespace http 
} // namespace xos 

namespace xos {

Daemon& Daemon::GetTheInstance() {
    return http::server::mongoose::libwebsockets::the_daemon;
}

} // namespace xos
