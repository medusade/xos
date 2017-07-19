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
///   File: ConductorInterface.hpp
///
/// Author: $author$
///   Date: 12/25/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_WEBRTC_PEERCONNECTION_CLIENT_CONDUCTORINTERFACE_HPP
#define _XOS_WEBRTC_PEERCONNECTION_CLIENT_CONDUCTORINTERFACE_HPP

#include "xos/base/String.hpp"
#include "xos/base/Base.hpp"

namespace xos {
namespace webrtc {
namespace peerconnection {
namespace client {

typedef InterfaceBase ConductorInterfaceImplement;
///////////////////////////////////////////////////////////////////////
///  Class: ConductorInterface
///
/// Author: $author$
///   Date: 12/25/2012
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS ConductorInterface: virtual public ConductorInterfaceImplement {
public:
    typedef ConductorInterfaceImplement Implements;

    virtual bool StartLogin(const std::string& server, int port) = 0;
    virtual void DisconnectFromServer(bool doClose=false) = 0;
    virtual void ConnectToPeer(int peer_id) = 0;
    virtual void DisconnectFromCurrentPeer() = 0;
    virtual void UIThreadCallback(int msg_id, void* data) = 0;
    virtual void Close() = 0;
    virtual bool SendMessageToPeer(const std::string& messageEnvelope) = 0;
    virtual bool SendMessage(const std::string& messageEnvelope) = 0;
};

///////////////////////////////////////////////////////////////////////
///  Class: ConductorImplement
///
/// Author: $author$
///   Date: 12/25/2012
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS ConductorImplement: virtual public ConductorInterface {
public:
    typedef ConductorInterface Implements;

    virtual ~ConductorImplement() {
    }
    virtual bool StartLogin(const std::string& server, int port) {
        bool isSuccess = false;
        ConductorInterface* delegated = 0;
        if ((delegated = DelegatedConductor())) {
            isSuccess = delegated->StartLogin(server, port);
        }
        return isSuccess;
    }
    virtual void DisconnectFromServer(bool doClose=false) {
        ConductorInterface* delegated = 0;
        if ((delegated = DelegatedConductor())) {
            delegated->DisconnectFromServer(doClose);
        }
    }
    virtual void ConnectToPeer(int peer_id) {
        ConductorInterface* delegated = 0;
        if ((delegated = DelegatedConductor())) {
            delegated->ConnectToPeer(peer_id);
        }
    }
    virtual void DisconnectFromCurrentPeer() {
        ConductorInterface* delegated = 0;
        if ((delegated = DelegatedConductor())) {
            delegated->DisconnectFromCurrentPeer();
        }
    }
    virtual void UIThreadCallback(int msg_id, void* data) {
        ConductorInterface* delegated = 0;
        if ((delegated = DelegatedConductor())) {
            delegated->UIThreadCallback(msg_id, data);
        }
    }
    virtual void Close() {
        ConductorInterface* delegated = 0;
        if ((delegated = DelegatedConductor())) {
            delegated->Close();
        }
    }
    virtual bool SendMessageToPeer(const std::string& messageEnvelope) {
        bool isSuccess = false;
        ConductorInterface* delegated = 0;
        if ((delegated = DelegatedConductor())) {
            isSuccess = delegated->SendMessageToPeer(messageEnvelope);
        } else {
            isSuccess = SendMessage(messageEnvelope);
        }
        return isSuccess;
    }
    virtual bool SendMessage(const std::string& messageEnvelope) {
        bool isSuccess = false;
        ConductorInterface* delegated = 0;
        if ((delegated = DelegatedConductor())) {
            isSuccess = delegated->SendMessageToPeer(messageEnvelope);
        }
        return isSuccess;
    }

    virtual ConductorInterface* DelegateConductor(ConductorInterface* delegated) {
        return 0;
    }
    virtual ConductorInterface* DelegatedConductor() const {
        return 0;
    }
};

} // namespace client 
} // namespace peerconnection 
} // namespace webrtc 
} // namespace xos 


#endif // _XOS_WEBRTC_PEERCONNECTION_CLIENT_CONDUCTORINTERFACE_HPP 
        

