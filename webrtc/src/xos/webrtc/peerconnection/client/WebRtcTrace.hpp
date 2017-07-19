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
///   File: WebRtcTrace.hpp
///
/// Author: $author$
///   Date: 1/7/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_WEBRTC_PEERCONNECTION_CLIENT_WEBRTCTRACE_HPP
#define _XOS_WEBRTC_PEERCONNECTION_CLIENT_WEBRTCTRACE_HPP

#include "xos/webrtc/peerconnection/client/Trace.hpp"
#include "system_wrappers/source/trace_impl.h"

#define XOS_WEBRTC_WEBRTCTRACE_DEFAULT_FILE_EXTENSION "WebRtc"

namespace xos {
namespace webrtc {
namespace peerconnection {
namespace client {

typedef ::webrtc::TraceCallback WebRtcTraceImplement;
typedef ExportBase WebRtcTraceExtend;
///////////////////////////////////////////////////////////////////////
///  Class: WebRtcTrace
///
/// Author: $author$
///   Date: 1/7/2013
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS WebRtcTrace: virtual public WebRtcTraceImplement, public WebRtcTraceExtend {
public:
    typedef WebRtcTraceImplement Implements;
    typedef WebRtcTraceExtend Extends;
    typedef Trace::Level Level;

    bool m_isInitialized;
    Stream* m_stream;

    WebRtcTrace(Stream& stream, Level levelsFilter) 
    : m_isInitialized(false),
      m_stream(0)
    {
    }
    WebRtcTrace(const std::string& traceFileName, Level levelsFilter) 
    : m_isInitialized(false),
      m_stream(0)
    {
    }
    WebRtcTrace()
    : m_isInitialized(false),
      m_stream(0)
    {
    }

    virtual bool Init
    (Stream& stream,
     Level levelsFilter = XOS_WEBRTC_PEERCONNECTION_CLIENT_TRACE_DEFAULT_TRACE_LEVELS) {
        WebRtc_UWord32 webrtcTraceLevelFilter = ToWebrtcTraceLevelFilter(levelsFilter);

        if ((m_isInitialized))
        if (!(Finish()))
            return false;

        ::webrtc::Trace::CreateTrace();
        ::webrtc::Trace::SetTraceCallback(this);
        ::webrtc::Trace::SetLevelFilter(webrtcTraceLevelFilter);
        m_stream = &stream;
        m_isInitialized = true;
        return true;
    }
    virtual bool Init
    (const std::string& traceFileName,
     Level levelsFilter = XOS_WEBRTC_PEERCONNECTION_CLIENT_TRACE_DEFAULT_TRACE_LEVELS) {
        WebRtc_UWord32 webrtcTraceLevelFilter = ToWebrtcTraceLevelFilter(levelsFilter);

        if ((m_isInitialized))
        if (!(Finish()))
            return false;

        ::webrtc::Trace::CreateTrace();
        ::webrtc::Trace::SetTraceFile(traceFileName.c_str());
        ::webrtc::Trace::SetLevelFilter(webrtcTraceLevelFilter);
        m_stream = 0;
        m_isInitialized = true;
        return true;
    }
    virtual bool Finish() {
        if ((m_isInitialized)) {
            ::webrtc::Trace::ReturnTrace();
            m_isInitialized = false;
            m_stream = 0;
            return true;
        }
        return false;
    }

    virtual void Print
    (const ::webrtc::TraceLevel level, 
     const char *traceString, const int length) {}

    virtual WebRtc_UWord32 ToWebrtcTraceLevelFilter
    (xos::webrtc::peerconnection::client::Trace::Level traceLevelsFilter) const {
        WebRtc_UWord32 webrtcTraceLevelFilter = ::webrtc::kTraceNone;
        xos::webrtc::peerconnection::client::Trace::Level level;

        if (0 > (traceLevelsFilter)) {
            webrtcTraceLevelFilter = ::webrtc::kTraceDefault;
        } else {
            for (level = 1; 0 < level; level <<= 1) {
                switch (level & traceLevelsFilter) {
                case XOS_WEBRTC_PEERCONNECTION_CLIENT_TRACE_LEVEL_ERROR:
                    webrtcTraceLevelFilter |= (::webrtc::kTraceError | ::webrtc::kTraceCritical);
                    break;

                case XOS_WEBRTC_PEERCONNECTION_CLIENT_TRACE_LEVEL_WARNING:
                    webrtcTraceLevelFilter |= (::webrtc::kTraceWarning);
                    break;

                case XOS_WEBRTC_PEERCONNECTION_CLIENT_TRACE_LEVEL_INFO:
                    webrtcTraceLevelFilter |= (::webrtc::kTraceStateInfo);
                    break;

                case XOS_WEBRTC_PEERCONNECTION_CLIENT_TRACE_LEVEL_FUNC:
                    webrtcTraceLevelFilter |= (::webrtc::kTraceApiCall | ::webrtc::kTraceModuleCall);
                    break;

                case XOS_WEBRTC_PEERCONNECTION_CLIENT_TRACE_LEVEL_DEBUG:
                    webrtcTraceLevelFilter |= (::webrtc::kTraceDebug | ::webrtc::kTraceInfo | ::webrtc::kTraceStateInfo);
                    break;

                case XOS_WEBRTC_PEERCONNECTION_CLIENT_TRACE_LEVEL_TRACE:
                    webrtcTraceLevelFilter |= (::webrtc::kTraceAll);
                    break;
                }
            }
        }
        return webrtcTraceLevelFilter;
    }
};

} // namespace client 
} // namespace peerconnection 
} // namespace webrtc 
} // namespace xos 

#endif // _XOS_WEBRTC_PEERCONNECTION_CLIENT_WEBRTCTRACE_HPP 
