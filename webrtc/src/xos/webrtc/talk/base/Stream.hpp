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
///   File: Stream.hpp
///
/// Author: $author$
///   Date: 10/24/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_WEBRTC_TALK_BASE_STREAM_HPP
#define _XOS_WEBRTC_TALK_BASE_STREAM_HPP

#include "xos/base/Stream.hpp"
#include "talk/base/stream.h"

namespace xos {
namespace webrtc {
namespace talk {
namespace base {

typedef talk_base::StreamInterface StreamExtend;

class _EXPORT_CLASS Stream: public StreamExtend {
public:
    typedef StreamExtend Extends;

    typedef talk_base::StreamState StreamState;
    typedef talk_base::StreamResult StreamResult;
    typedef talk_base::StreamEvent StreamEvent;

    xos::Stream* m_stream;
    StreamState m_state;

    Stream(xos::Stream* stream = 0) 
    : m_stream(stream),
      m_state(talk_base::SS_CLOSED)
    {
    }
    virtual ~Stream() {
    }

    virtual StreamResult Read
    (void* buffer, size_t buffer_len,
     size_t* read, int* error)
    { 
        StreamResult result = talk_base::SR_ERROR; 
        return result; 
    }
    virtual StreamResult Write
    (const void* data, size_t data_len,
     size_t* written, int* error)
    { 
        StreamResult result = talk_base::SR_ERROR; 
        ssize_t count;
        if ((m_stream))
        if (data_len == (count = m_stream->Write((const void*)(data), data_len)))
            result = talk_base::SR_SUCCESS;
        return result; 
    }

    virtual bool Open(xos::Stream* stream)
    {
        if ((m_stream = stream))
        {
            m_state = talk_base::SS_OPEN;
            return true;
        }
        return false;
    }
    virtual void Close()
    {
        m_stream = 0;
        m_state = talk_base::SS_CLOSED;
    }

    virtual StreamState GetState() const
    { 
        return m_state; 
    }
};

} // namespace base 
} // namespace talk 
} // namespace webrtc 
} // namespace xos 

#endif // _XOS_WEBRTC_TALK_BASE_STREAM_HPP 
