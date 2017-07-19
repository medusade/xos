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
///   File: PortServer.hpp
///
/// Author: $author$
///   Date: 1/18/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_WEBRTC_PEERCONNECTION_CLIENT_PORTSERVER_HPP
#define _XOS_WEBRTC_PEERCONNECTION_CLIENT_PORTSERVER_HPP

#include "xos/base/String.hpp"

namespace xos {
namespace webrtc {
namespace peerconnection {
namespace client {

class _EXPORT_CLASS PortServer {
public:

typedef InterfaceBase OptionsInterfaceImplement;

class _EXPORT_CLASS OptionsInterface: virtual public OptionsInterfaceImplement {
public:
    typedef OptionsInterfaceImplement Implements;

    virtual void SetPortServerHost(const std::string& val) = 0;
    virtual std::string GetPortServerHost() const = 0;

    virtual void SetStunServerHost(const std::string& val) = 0;
    virtual std::string GetStunServerHost() const = 0;

    virtual void SetStunServerPort(int val) = 0;
    virtual int GetStunServerPort() const = 0;

    virtual void SetRelayServerHost(const std::string& val) = 0;
    virtual std::string GetRelayServerHost() const = 0;

    virtual void SetRelayServerPort(int val) = 0;
    virtual int GetRelayServerPort() const = 0;

    virtual void SetRelayUDPServerHost(const std::string& val) = 0;
    virtual std::string GetRelayUDPServerHost() const = 0;

    virtual void SetRelayUDPServerPort(int val) = 0;
    virtual int GetRelayUDPServerPort() const = 0;

    virtual void SetRelayTCPServerHost(const std::string& val) = 0;
    virtual std::string GetRelayTCPServerHost() const = 0;

    virtual void SetRelayTCPServerPort(int val) = 0;
    virtual int GetRelayTCPServerPort() const = 0;

    virtual void SetRelaySSLServerHost(const std::string& val) = 0;
    virtual std::string GetRelaySSLServerHost() const = 0;

    virtual void SetRelaySSLServerPort(int val) = 0;
    virtual int GetRelaySSLServerPort() const = 0;

    virtual void SetUseNumericServerAddresses(bool val = true) = 0;
    virtual bool GetUseNumericServerAddresses() const = 0;

    virtual void SetUseRelayServer(bool val = true) = 0;
    virtual bool GetUseRelayServer() const = 0;
};

class _EXPORT_CLASS OptionsImplement: virtual public OptionsInterface {
public:
    typedef OptionsInterface Implements;

    virtual void SetPortServerHost(const std::string& val) 
    { OptionsInterface* delegated=DelegatedPortServerOptions();
      if ((delegated)) delegated->SetPortServerHost(val); 
    }
    virtual std::string GetPortServerHost() const 
    { std::string val; OptionsInterface* delegated=DelegatedPortServerOptions();
      if ((delegated)) val = delegated->GetPortServerHost(); return val;
    }

    virtual void SetStunServerHost(const std::string& val) 
    { OptionsInterface* delegated=DelegatedPortServerOptions();
      if ((delegated)) delegated->SetStunServerHost(val); 
    }
    virtual std::string GetStunServerHost() const 
    { std::string val; OptionsInterface* delegated=DelegatedPortServerOptions();
      if ((delegated)) val = delegated->GetStunServerHost(); return val;
    }

    virtual void SetStunServerPort(int val) 
    {  OptionsInterface* delegated=DelegatedPortServerOptions();
      if ((delegated)) delegated->SetStunServerPort(val); 
    }
    virtual int GetStunServerPort() const 
    { int val=0; OptionsInterface* delegated=DelegatedPortServerOptions();
      if ((delegated)) val = delegated->GetStunServerPort(); return val;
    }

    virtual void SetRelayServerHost(const std::string& val) 
    {  OptionsInterface* delegated=DelegatedPortServerOptions();
      if ((delegated)) delegated->SetRelayServerHost(val); 
    }
    virtual std::string GetRelayServerHost() const 
    { std::string val; OptionsInterface* delegated=DelegatedPortServerOptions();
      if ((delegated)) val = delegated->GetRelayServerHost(); return val;
    }

    virtual void SetRelayServerPort(int val) 
    {  OptionsInterface* delegated=DelegatedPortServerOptions();
      if ((delegated)) delegated->SetRelayServerPort(val); }
    virtual int GetRelayServerPort() const 
    { int val=0; OptionsInterface* delegated=DelegatedPortServerOptions();
      if ((delegated)) val = delegated->GetRelayServerPort(); return val;
    }

    virtual void SetRelayUDPServerHost(const std::string& val) 
    {  OptionsInterface* delegated=DelegatedPortServerOptions();
      if ((delegated)) delegated->SetRelayUDPServerHost(val); 
    }
    virtual std::string GetRelayUDPServerHost() const 
    { std::string val; OptionsInterface* delegated=DelegatedPortServerOptions();
      if ((delegated)) val = delegated->GetRelayUDPServerHost(); return val;
    }

    virtual void SetRelayUDPServerPort(int val) 
    {  OptionsInterface* delegated=DelegatedPortServerOptions();
      if ((delegated)) delegated->SetRelayUDPServerPort(val); 
    }
    virtual int GetRelayUDPServerPort() const 
    { int val=0; OptionsInterface* delegated=DelegatedPortServerOptions();
      if ((delegated)) val = delegated->GetRelayUDPServerPort(); return val;
    }

    virtual void SetRelayTCPServerHost(const std::string& val) 
    {  OptionsInterface* delegated=DelegatedPortServerOptions();
      if ((delegated)) delegated->SetRelayTCPServerHost(val); 
    }
    virtual std::string GetRelayTCPServerHost() const 
    { std::string val; OptionsInterface* delegated=DelegatedPortServerOptions();
      if ((delegated)) val = delegated->GetRelayTCPServerHost(); return val;
    }

    virtual void SetRelayTCPServerPort(int val) 
    {  OptionsInterface* delegated=DelegatedPortServerOptions();
      if ((delegated)) delegated->SetRelayTCPServerPort(val); 
    }
    virtual int GetRelayTCPServerPort() const 
    { int val=0; OptionsInterface* delegated=DelegatedPortServerOptions();
      if ((delegated)) val = delegated->GetRelayTCPServerPort(); return val;
    }

    virtual void SetRelaySSLServerHost(const std::string& val) 
    {  OptionsInterface* delegated=DelegatedPortServerOptions();
      if ((delegated)) delegated->SetRelaySSLServerHost(val); 
    }
    virtual std::string GetRelaySSLServerHost() const 
    { std::string val; OptionsInterface* delegated=DelegatedPortServerOptions();
      if ((delegated)) val = delegated->GetRelaySSLServerHost(); return val;
    }

    virtual void SetRelaySSLServerPort(int val) 
    {  OptionsInterface* delegated=DelegatedPortServerOptions();
      if ((delegated)) delegated->SetRelaySSLServerPort(val); 
    }
    virtual int GetRelaySSLServerPort() const 
    { int val=0; OptionsInterface* delegated=DelegatedPortServerOptions();
      if ((delegated)) val = delegated->GetRelaySSLServerPort(); return val;
    }

    virtual void SetUseNumericServerAddresses(bool val = true) 
    {  OptionsInterface* delegated=DelegatedPortServerOptions();
      if ((delegated)) delegated->SetUseNumericServerAddresses(val); 
    }
    virtual bool GetUseNumericServerAddresses() const 
    { bool val=false; OptionsInterface* delegated=DelegatedPortServerOptions();
      if ((delegated)) val = delegated->GetUseNumericServerAddresses(); return val;
    }

    virtual void SetUseRelayServer(bool val = true) 
    {  OptionsInterface* delegated=DelegatedPortServerOptions();
      if ((delegated)) delegated->SetUseRelayServer(val); 
    }
    virtual bool GetUseRelayServer() const 
    { bool val=false;  OptionsInterface* delegated=DelegatedPortServerOptions();
      if ((delegated)) val = delegated->GetUseRelayServer(); return val;
    }

    virtual PortServer::OptionsInterface* DelegatePortServerOptions
    (PortServer::OptionsInterface* delegateTo)
    { return 0; }
    virtual PortServer::OptionsInterface* DelegatedPortServerOptions() const
    { return 0; }
};

};
} // namespace client 
} // namespace peerconnection 
} // namespace webrtc 
} // namespace xos 

#endif // _XOS_WEBRTC_PEERCONNECTION_CLIENT_PORTSERVER_HPP 
