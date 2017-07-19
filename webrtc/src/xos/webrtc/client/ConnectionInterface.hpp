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
///   File: ConnectionInterface.hpp
///
/// Author: $author$
///   Date: 10/16/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_WEBRTC_CLIENT_CONNECTIONINTERFACE_HPP
#define _XOS_WEBRTC_CLIENT_CONNECTIONINTERFACE_HPP

#include "xos/base/String.hpp"
#include <map>

namespace xos {
namespace webrtc {
namespace client {

typedef InterfaceBase ConnectionInterfaceImplement;

class _EXPORT_CLASS ConnectionInterface: virtual public ConnectionInterfaceImplement {
public:
    typedef ConnectionInterfaceImplement Implements;
    typedef std::map<int, std::string> Peers;
};

typedef InterfaceBase ConnectionObserverInterfaceImplement;

class _EXPORT_CLASS ConnectionObserverInterface: virtual public ConnectionObserverInterfaceImplement {
public:
    typedef ConnectionObserverInterfaceImplement Implements;

    virtual void OnSignedIn() = 0;  
    virtual void OnDisconnected() = 0;
    virtual void OnFailedToConnect() = 0; 
    virtual void OnPeerConnected(int id, const std::string& name) = 0;
    virtual void OnPeerDisconnected(int peer_id) = 0;
    virtual void OnMessageFromPeer(int peer_id, const std::string& message) = 0;
    virtual void OnMessageSent(int err) = 0;
};

} // namespace client 
} // namespace webrtc 
} // namespace xos 

#endif // _XOS_WEBRTC_CLIENT_CONNECTIONINTERFACE_HPP 
