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
///   File: LibJingleTrace.hpp
///
/// Author: $author$
///   Date: 10/18/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_WEBRTC_CLIENT_LIBJINGLETRACE_HPP
#define _XOS_WEBRTC_CLIENT_LIBJINGLETRACE_HPP

#include "xos/webrtc/client/Trace.hpp"
#include "xos/webrtc/talk/base/Stream.hpp"

#define XOS_WEBRTC_LIBJINGLETRACE_DEFAULT_FILE_EXTENSION "LibJingle"

namespace xos {
namespace webrtc {
namespace client {

class _EXPORT_CLASS LibJingleTrace: public Trace {
public:
    typedef talk_base::LoggingSeverity LoggingSeverity;
    typedef talk_base::FileStream FileStream;
    typedef talk_base::StreamState StreamState;
    typedef xos::webrtc::talk::base::Stream OutStream;

    OutStream m_stream;
    FileStream m_fileStream;

    LibJingleTrace(Stream& stream, Level levelsFilter) {
        Init(stream, levelsFilter);
    }
    LibJingleTrace(const std::string& traceFileName, Level levelsFilter) {
        Init(traceFileName, levelsFilter);
    }
    LibJingleTrace() {
    }

    virtual bool Init
    (Stream& stream,
     Level levelsFilter = XOS_WEBRTC_CLIENT_TRACE_DEFAULT_TRACE_LEVELS) {
        LoggingSeverity loggingSeverity = ToLoggingSeverity(levelsFilter);
        if ((m_stream.Open(&stream))) {
            talk_base::LogMessage::AddLogToStream(&m_stream, loggingSeverity);
            return true;
        }
        return false;
    }
    virtual bool Init
    (const std::string& traceFileName,
     Level levelsFilter = XOS_WEBRTC_CLIENT_TRACE_DEFAULT_TRACE_LEVELS) {
        LoggingSeverity loggingSeverity = ToLoggingSeverity(levelsFilter);
        int err;
        if ((m_fileStream.Open(traceFileName, "w", &err))) {
            if ((m_fileStream.DisableBuffering())) {
                talk_base::LogMessage::AddLogToStream(&m_fileStream, loggingSeverity);
                return true;
            }
            m_fileStream.Close();
        }
        return false;
    }
    virtual bool Finish() {
        StreamState streamState;

        if (talk_base::SS_CLOSED != (streamState = m_stream.GetState())) {
            talk_base::LogMessage::RemoveLogToStream(&m_stream);
            m_stream.Close();
        }
        if (talk_base::SS_CLOSED != (streamState = m_fileStream.GetState())) {
            talk_base::LogMessage::RemoveLogToStream(&m_fileStream);
            m_fileStream.Close();
        }
        return true;
    }

    virtual LoggingSeverity ToLoggingSeverity
    (xos::webrtc::client::Trace::Level traceLevelsFilter) const
    {
        LoggingSeverity loggingSeverity = (LoggingSeverity)(talk_base::LS_ERROR+1);
        LoggingSeverity newLoggingSeverity;
        xos::webrtc::client::Trace::Level level;

        for (level = 1; 0 < level; level <<= 1)
        {
            switch (level & traceLevelsFilter)
            {
            case XOS_WEBRTC_CLIENT_TRACE_LEVEL_ERROR:
                if (loggingSeverity > (newLoggingSeverity = talk_base::LS_ERROR))
                    loggingSeverity = newLoggingSeverity;
                break;

            case XOS_WEBRTC_CLIENT_TRACE_LEVEL_WARNING:
                if (loggingSeverity > (newLoggingSeverity = talk_base::LS_WARNING))
                    loggingSeverity = newLoggingSeverity;
                break;

            case XOS_WEBRTC_CLIENT_TRACE_LEVEL_INFO:
                if (loggingSeverity > (newLoggingSeverity = talk_base::LS_INFO))
                    loggingSeverity = newLoggingSeverity;
                break;

            case XOS_WEBRTC_CLIENT_TRACE_LEVEL_FUNC:
                if (loggingSeverity > (newLoggingSeverity = talk_base::LS_INFO))
                    loggingSeverity = newLoggingSeverity;
                break;

            case XOS_WEBRTC_CLIENT_TRACE_LEVEL_DEBUG:
                if (loggingSeverity > (newLoggingSeverity = talk_base::LS_VERBOSE))
                    loggingSeverity = newLoggingSeverity;
                break;

            case XOS_WEBRTC_CLIENT_TRACE_LEVEL_TRACE:
                if (loggingSeverity > (newLoggingSeverity = talk_base::LS_SENSITIVE))
                    loggingSeverity = newLoggingSeverity;
                break;
            }
        }
        return loggingSeverity;
    }
};

} // namespace client 
} // namespace webrtc 
} // namespace xos 

#endif // _XOS_WEBRTC_CLIENT_LIBJINGLETRACE_HPP 
