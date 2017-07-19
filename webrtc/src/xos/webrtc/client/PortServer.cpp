///////////////////////////////////////////////////////////////////////
/// Copyright 2012, Google Inc.
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
///   File: PortServer.cpp
///
/// Author: $author$
///   Date: 10/16/2012
///////////////////////////////////////////////////////////////////////
#include "xos/webrtc/client/PortServer.hpp"

#if !defined(NO_WEBRTC_PORTALLOCATOR_PATCH) 
namespace cricket {
extern bool portallocator_pref_relay_get();
extern void portallocator_pref_relay_set(bool on = true);
} // namespace
#else // !defined(NO_WEBRTC_PORTALLOCATOR_PATCH) 
#endif // !defined(NO_WEBRTC_PORTALLOCATOR_PATCH) 

namespace xos {
namespace webrtc {
namespace client {

///////////////////////////////////////////////////////////////////////
///  Class: PortServer::Options
///////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
///  Function: PortServer::Options::SetUseRelayServer
///////////////////////////////////////////////////////////////////////
void PortServer::Options::SetUseRelayServer(bool val) {
#if !defined(NO_WEBRTC_PORTALLOCATOR_PATCH) 
    cricket::portallocator_pref_relay_set(val);
#else // !defined(NO_WEBRTC_PORTALLOCATOR_PATCH) 
    OptionsInterface* delegated=DelegatedPortServerOptions();
    if ((delegated)) delegated->SetUseRelayServer(val);
#endif // !defined(NO_WEBRTC_PORTALLOCATOR_PATCH) 
}
///////////////////////////////////////////////////////////////////////
///  Function: PortServer::Options::GetUseRelayServer
///////////////////////////////////////////////////////////////////////
bool PortServer::Options::GetUseRelayServer() const {
    bool val = false;
#if !defined(NO_WEBRTC_PORTALLOCATOR_PATCH) 
    val = cricket::portallocator_pref_relay_get();
#else // !defined(NO_WEBRTC_PORTALLOCATOR_PATCH) 
    OptionsInterface* delegated=DelegatedPortServerOptions();
    if ((delegated)) val = delegated->GetUseRelayServer();
#endif // !defined(NO_WEBRTC_PORTALLOCATOR_PATCH) 
    return val;
}

} // namespace client 
} // namespace webrtc 
} // namespace xos 
