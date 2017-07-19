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
///   File: ConnectorPair.hpp
///
/// Author: $author$
///   Date: 1/13/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_WEBRTC_PEERCONNECTION_CLIENT_CONNECTORPAIR_HPP
#define _XOS_WEBRTC_PEERCONNECTION_CLIENT_CONNECTORPAIR_HPP

#include "xos/webrtc/peerconnection/client/MainWindow.hpp"
#include "xos/webrtc/peerconnection/client/Conductor.hpp"
#include "xos/webrtc/peerconnection/client/Connection.hpp"
#include "xos/webrtc/peerconnection/client/Trace.hpp"

namespace xos {
namespace webrtc {
namespace peerconnection {
namespace client {

typedef InterfaceBase ConnectorPairImplement;
typedef ExportBase ConnectorPairExtend;
///////////////////////////////////////////////////////////////////////
///  Class: ConnectorPair
///
/// Author: $author$
///   Date: 1/13/2013
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS ConnectorPair
: virtual public ConnectorPairImplement,
  public ConnectorPairExtend
{
public:
    typedef ConnectorPairImplement Implements;
    typedef ConnectorPairExtend Extends;

    MainWindow& m_mainWindow;
    std::string m_webrtcTraceFileName;
    Trace::Level m_webrtcTraceLevels;
    Trace m_webrtcTrace;
    Connection m_connection;
    Conductor m_conductor;

    ConnectorPair
    (MainWindow& mainWindow,
     const std::string& webrtcTraceFileName,
     Trace::Level webrtcTraceLevels) 
    : m_mainWindow(mainWindow),
      m_webrtcTraceFileName(webrtcTraceFileName),
      m_webrtcTraceLevels(webrtcTraceLevels),
      m_webrtcTrace(m_webrtcTraceFileName, m_webrtcTraceLevels),
      m_conductor(&m_connection, &m_mainWindow)
    {
    }
    virtual ~ConnectorPair() {
    }
};

} // namespace client 
} // namespace peerconnection 
} // namespace webrtc 
} // namespace xos 

#endif // _XOS_WEBRTC_PEERCONNECTION_CLIENT_CONNECTORPAIR_HPP 
