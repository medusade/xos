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
///   File: Trace.cpp
///
/// Author: $author$
///   Date: 1/7/2013
///////////////////////////////////////////////////////////////////////
#include "xos/webrtc/peerconnection/client/Trace.hpp"
#include "xos/webrtc/peerconnection/client/WebRtcTrace.hpp"
#include "xos/webrtc/peerconnection/client/LibJingleTrace.hpp"
#include "xos/os/Logger.hpp"
#include <sstream>

namespace xos {
namespace webrtc {
namespace peerconnection {
namespace client {

///////////////////////////////////////////////////////////////////////
///  Class: TraceImplemented
///
/// Author: $author$
///   Date: 1/7/2013
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS TraceImplemented: public Trace {
public:
    bool m_traceIsCritical;

    std::string m_webRtcTraceFileExtension;
    std::string m_libJingleTraceFileExtension;

    WebRtcTrace m_webRtcTrace;
    LibJingleTrace m_libJingleTrace;

    TraceImplemented(Stream& stream, Level levelsFilter)
    : m_traceIsCritical
      (XOS_WEBRTC_PEERCONNECTION_CLIENT_TRACE_DEFAULT_TRACE_IS_CRITICAL),      
      m_webRtcTraceFileExtension
      (XOS_WEBRTC_WEBRTCTRACE_DEFAULT_FILE_EXTENSION),
      m_libJingleTraceFileExtension
      (XOS_WEBRTC_LIBJINGLETRACE_DEFAULT_FILE_EXTENSION)
    {
        if (!(Init(stream, levelsFilter))) {
            throw(Error(Error::Failed));
        }
    }
    TraceImplemented(const std::string& traceFileName, Level levelsFilter) 
    : m_traceIsCritical
      (XOS_WEBRTC_PEERCONNECTION_CLIENT_TRACE_DEFAULT_TRACE_IS_CRITICAL),      
      m_webRtcTraceFileExtension
      (XOS_WEBRTC_WEBRTCTRACE_DEFAULT_FILE_EXTENSION),
      m_libJingleTraceFileExtension
      (XOS_WEBRTC_LIBJINGLETRACE_DEFAULT_FILE_EXTENSION)
    {
        if (!(Init(traceFileName, levelsFilter))) {
            throw(Error(Error::Failed));
        }
    }

    virtual bool Init
    (Stream& stream,
     Level levelsFilter = XOS_WEBRTC_PEERCONNECTION_CLIENT_TRACE_DEFAULT_TRACE_LEVELS) {
         return false;
    }
    virtual bool Init
    (const std::string& traceFileName,
     Level levelsFilter = XOS_WEBRTC_PEERCONNECTION_CLIENT_TRACE_DEFAULT_TRACE_LEVELS) {
        const char* pathSeparator = 0;
        const char* traceFileNameChars = 0;
        std::string traceFileNameBase(traceFileName);
        std::string traceFileNameExt;
        std::string traceFileNamePath;

        if ((traceFileNameChars = traceFileName.c_str()))
            pathSeparator = strrchr(traceFileNameChars, '.');

        if ((pathSeparator))
        {
            traceFileNameBase.assign(traceFileNameChars, (pathSeparator-traceFileNameChars+1));
            traceFileNameExt.assign(pathSeparator);
        }
        else
        traceFileNameBase.append(".");

        traceFileNamePath = traceFileNameBase;
        traceFileNamePath += m_webRtcTraceFileExtension;
        traceFileNamePath += traceFileNameExt;

        if (!(m_webRtcTrace.Init(traceFileNamePath, levelsFilter)))
        {
            XOS_LOG_ERROR("failed on m_webRtcTrace.Init(\"" << traceFileNamePath.c_str() << "\",...)\n");
            if ((m_traceIsCritical))
                return false;
        }

        traceFileNamePath = traceFileNameBase;
        traceFileNamePath += m_libJingleTraceFileExtension;
        traceFileNamePath += traceFileNameExt;

        if ((m_libJingleTrace.Init(traceFileNamePath, levelsFilter))) {
            return true;
        } else {
            XOS_LOG_ERROR("() failed on m_libJingleTrace.Init(\"" << traceFileNamePath.c_str() << "\",...)\n");
            if ((m_traceIsCritical))
                return false;
        }
        return false;
    }
    virtual bool Finish() {
         return true;
    }
};

///////////////////////////////////////////////////////////////////////
///  Class: Trace
///
/// Author: $author$
///   Date: 1/7/2013
///////////////////////////////////////////////////////////////////////
Trace::Trace(Stream& stream, Level levelsFilter): m_implemented(0) {
    Init(stream, levelsFilter);
}
Trace::Trace(const std::string& traceFileName, Level levelsFilter): m_implemented(0) {
    Init(traceFileName, levelsFilter);
}
Trace::Trace(): m_implemented(0) {
}
Trace::~Trace() {
    Finish();
}

bool Trace::Init(Stream& stream, Level levelsFilter) {
    try {
        if ((m_implemented = new TraceImplemented(stream, levelsFilter))) {
            return true;
        }
    } catch (xos::Error) {
    }
    return false;
}
bool Trace::Init(const std::string& traceFileName, Level levelsFilter) {
    const char* pathSeparator = 0;
    const char* traceFileNameChars = 0;
    std::string traceFileNameBase(traceFileName);
    std::string traceFileNameTime;
    std::string traceFileNameExt;
    std::string traceFileNamePath;
    std::stringstream s;
    struct tm* tm;
    time_t t;

    //
    // Separate file name and extension
    //
    if ((traceFileNameChars = traceFileName.c_str()))
        pathSeparator = strrchr(traceFileNameChars, '.');

    if ((pathSeparator))
    {
        // name before '.'
        traceFileNameBase.assign(traceFileNameChars, (pathSeparator-traceFileNameChars));
        // extension including '.'
        traceFileNameExt.assign(pathSeparator);
    }

    //
    // Generate time string to make file name unique to second
    //
    time(&t);
    if ((tm = localtime(&t)))
    {
        s << '-';
        s << (tm->tm_year+1900);
        if (10 > (tm->tm_mon+1)) s << 0;
        s << (tm->tm_mon+1);
        if (10 > (tm->tm_mday)) s << 0;
        s << (tm->tm_mday);
        s << '-';
        if (10 > (tm->tm_hour)) s << 0;
        s << (tm->tm_hour);
        if (10 > (tm->tm_min)) s << 0;
        s << (tm->tm_min);
        if (10 > (tm->tm_sec)) s << 0;
        s << (tm->tm_sec);

        traceFileNameTime = s.str();
    }

    //
    // Generate unique filename
    //
    traceFileNamePath = traceFileNameBase;
    traceFileNamePath += traceFileNameTime;
    traceFileNamePath += traceFileNameExt;

    try {
        if ((m_implemented = new TraceImplemented(traceFileNamePath, levelsFilter))) {
            return true;
        }
    } catch (xos::Error) {
    }
    return false;
}
bool Trace::Finish() {
    if ((m_implemented)) {
        try {
            delete m_implemented;
            m_implemented = 0;
            return true;
        } catch(xos::Error) {
            m_implemented = 0;
        }
    }
    return false;
}

} // namespace client 
} // namespace peerconnection 
} // namespace webrtc 
} // namespace xos 


        

