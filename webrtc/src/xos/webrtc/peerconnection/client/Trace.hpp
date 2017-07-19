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
///   File: Trace.hpp
///
/// Author: $author$
///   Date: 1/7/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_WEBRTC_PEERCONNECTION_CLIENT_TRACE_HPP
#define _XOS_WEBRTC_PEERCONNECTION_CLIENT_TRACE_HPP

#include "xos/base/Stream.hpp"
#include <string>

#define XOS_WEBRTC_PEERCONNECTION_CLIENT_TRACE_DEFAULT_TRACE_FILEENV \
    "APPDATA"

#define XOS_WEBRTC_PEERCONNECTION_CLIENT_TRACE_DEFAULT_TRACE_FILEPATH \
    "Xos/"

#define XOS_WEBRTC_PEERCONNECTION_CLIENT_TRACE_DEFAULT_TRACE_FILEDIR \
    XOS_WEBRTC_PEERCONNECTION_CLIENT_TRACE_DEFAULT_TRACE_FILEPATH \
    "XosWebrtcClient/logs"

#define XOS_WEBRTC_PEERCONNECTION_CLIENT_TRACE_DEFAULT_TRACE_FILENAME \
    "XosWebrtcClient.log"

#define XOS_WEBRTC_PEERCONNECTION_CLIENT_TRACE_DEFAULT_TRACE_LEVELS \
    XOS_WEBRTC_PEERCONNECTION_CLIENT_TRACE_LEVELS_WARNING

#define XOS_WEBRTC_PEERCONNECTION_CLIENT_TRACE_DEFAULT_TRACE_IS_CRITICAL false

enum {
    XOS_WEBRTC_PEERCONNECTION_CLIENT_TRACE_LEVEL_NONE = 0,
    XOS_WEBRTC_PEERCONNECTION_CLIENT_TRACE_LEVEL_ERROR = 0x1,
    XOS_WEBRTC_PEERCONNECTION_CLIENT_TRACE_LEVEL_WARNING = 0x2,
    XOS_WEBRTC_PEERCONNECTION_CLIENT_TRACE_LEVEL_INFO = 0x4,
    XOS_WEBRTC_PEERCONNECTION_CLIENT_TRACE_LEVEL_FUNC = 0x8,
    XOS_WEBRTC_PEERCONNECTION_CLIENT_TRACE_LEVEL_DEBUG = 0x10,
    XOS_WEBRTC_PEERCONNECTION_CLIENT_TRACE_LEVEL_TRACE = 0x20
};
enum {
    XOS_WEBRTC_PEERCONNECTION_CLIENT_TRACE_LEVELS_NONE = 0,
    XOS_WEBRTC_PEERCONNECTION_CLIENT_TRACE_LEVELS_ERROR = 0x1,
    XOS_WEBRTC_PEERCONNECTION_CLIENT_TRACE_LEVELS_WARNING = 0x3,
    XOS_WEBRTC_PEERCONNECTION_CLIENT_TRACE_LEVELS_INFO = 0x7,
    XOS_WEBRTC_PEERCONNECTION_CLIENT_TRACE_LEVELS_FUNC = 0xF,
    XOS_WEBRTC_PEERCONNECTION_CLIENT_TRACE_LEVELS_DEBUG = 0x1F,
    XOS_WEBRTC_PEERCONNECTION_CLIENT_TRACE_LEVELS_TRACE = 0x3F
};

namespace xos {
namespace webrtc {
namespace peerconnection {
namespace client {

class _EXPORT_CLASS TraceImplemented;
///////////////////////////////////////////////////////////////////////
///  Class: Trace
///
/// Author: $author$
///   Date: 1/7/2013
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Trace {
public:
    typedef int Level;

    Trace
    (Stream& stream, 
     Level levelsFilter = XOS_WEBRTC_PEERCONNECTION_CLIENT_TRACE_DEFAULT_TRACE_LEVELS);
    Trace
    (const std::string& traceFileName,
     Level levelsFilter = XOS_WEBRTC_PEERCONNECTION_CLIENT_TRACE_DEFAULT_TRACE_LEVELS);
    Trace();
    virtual ~Trace();

    virtual bool Init
    (Stream& stream,
     Level levelsFilter = XOS_WEBRTC_PEERCONNECTION_CLIENT_TRACE_DEFAULT_TRACE_LEVELS);
    virtual bool Init
    (const std::string& traceFileName,
     Level levelsFilter = XOS_WEBRTC_PEERCONNECTION_CLIENT_TRACE_DEFAULT_TRACE_LEVELS);
    virtual bool Finish();

protected:
    TraceImplemented* m_implemented;
};

} // namespace client 
} // namespace peerconnection 
} // namespace webrtc 
} // namespace xos 

#endif // _XOS_WEBRTC_PEERCONNECTION_CLIENT_TRACE_HPP 
