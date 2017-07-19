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
///   Date: 2/17/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_WEBRTC_CLIENT_CONNECTORPAIR_HPP
#define _XOS_WEBRTC_CLIENT_CONNECTORPAIR_HPP

#include "xos/webrtc/client/Conductor.hpp"
#include "xos/webrtc/client/Connection.hpp"
#include "xos/webrtc/client/Window.hpp"

namespace xos {
namespace webrtc {
namespace client {

typedef InterfaceBase ConnectorPairImplement;
typedef ExportBase ConnectorPairExtend;

class _EXPORT_CLASS ConnectorPair: virtual public ConnectorPairImplement, public ConnectorPairExtend {
public:
    typedef ConnectorPairImplement Implements;
    typedef ConnectorPairExtend Extends;

    ConnectorPair
    (Window& userInterface, 
     const std::string& traceFileName,
     Trace::Level traceLevels = XOS_WEBRTC_CLIENT_TRACE_DEFAULT_TRACE_LEVELS,
     VideoCodec::Mode videoCodecMode = XOS_WEBRTC_CLIENT_VIDEO_CODEC_DEFAULT_VIDEO_CODEC_MODE)
    : m_userInterface(userInterface),
      m_videoCodecMode(videoCodecMode),
      m_videoCodec(m_videoCodecMode),
      m_traceFileName(traceFileName),
      m_traceLevels(traceLevels),
      m_trace(m_traceFileName, m_traceLevels),
      m_conductor(m_videoCodec, m_trace, &m_connection, &m_userInterface) {
    }
    virtual ~ConnectorPair() {
    }

protected:
    Window& m_userInterface;
    VideoCodec::Mode m_videoCodecMode;
    VideoCodec m_videoCodec;
    std::string m_traceFileName;
    Trace::Level m_traceLevels;
    Trace m_trace;
    Connection m_connection;
    Conductor m_conductor;
};

} // namespace client 
} // namespace webrtc 
} // namespace xos 

#endif // _XOS_WEBRTC_CLIENT_CONNECTORPAIR_HPP 
