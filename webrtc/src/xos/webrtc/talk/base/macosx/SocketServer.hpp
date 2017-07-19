///////////////////////////////////////////////////////////////////////
/// Copyright 2013, Google Inc.
///
/// Redistribution and use in source and binary forms, with or without
/// modification, are permitted provided that the following conditions are met:
/// 
///  1. Redistributions of source code must retain the above copyright notice,
///     this list of conditions and the following disclaimer.
///  2. Redistributions in binary form must reproduce the above copyright notice,
///     this list of conditions and the following disclaimer in the documentation
///     and/or other materials provided with the distribution.
///  3. The name of the author may not be used to endorse or promote products
///     derived from this software without specific prior written permission.
/// 
/// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
/// WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
/// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
/// EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
/// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
/// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
/// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
/// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
/// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
/// ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
///
///   File: SocketServer.hpp
///
/// Author: $author$
///   Date: 3/7/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_WEBRTC_TALK_BASE_MACOSX_SOCKETSERVER_HPP
#define _XOS_WEBRTC_TALK_BASE_MACOSX_SOCKETSERVER_HPP

#include "xos/webrtc/talk/base/SocketServer.hpp"

namespace xos {
namespace webrtc {
namespace talk {
namespace base {
namespace macosx {

#if defined(MACOSX_SOCKETSERVER) 
// Mac SocketServer 
typedef talk_base::MacCarbonSocketServer SocketServerExtend;
#else // defined(MACOSX_SOCKETSERVER) 
// Otherwise
typedef talk_base::PhysicalSocketServer SocketServerExtend;
#endif // defined(MACOSX_SOCKETSERVER) 

typedef SocketServer<SocketServerExtend> SocketServer;

} // namespace macosx 
} // namespace base 
} // namespace talk 
} // namespace webrtc 
} // namespace xos 

#endif // _XOS_WEBRTC_TALK_BASE_MACOSX_SOCKETSERVER_HPP 
