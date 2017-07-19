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
///   File: SocketServer.hpp
///
/// Author: $author$
///   Date: 10/15/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_WEBRTC_TALK_BASE_SOCKETSERVER_HPP
#define _XOS_WEBRTC_TALK_BASE_SOCKETSERVER_HPP

#include "xos/base/Base.hpp"
#include "talk/base/thread.h"
#include "talk/base/physicalsocketserver.h"

#if defined(MACOSX)
#include "talk/base/macsocketserver.h"
#include "talk/base/macasyncsocket.h"
#endif // defined(MACOSX)

#if defined(WINDOWS)
#include "talk/base/win32socketserver.h"
#endif // defined(WINDOWS)

namespace xos {
namespace webrtc {
namespace talk {
namespace base {

template 
<class TExtend = talk_base::PhysicalSocketServer>

class _EXPORT_CLASS SocketServer: public TExtend {
public:
    typedef TExtend Extends;

    SocketServer(): m_thread(0) {
        if ((this->m_thread = talk_base::Thread::Current()))
            this->m_thread->set_socketserver(this);
    }
    virtual ~SocketServer() {
        if ((this->m_thread))
            this->m_thread->set_socketserver(0);
    }

    virtual bool Run() {
        bool isSuccess = false;
        if ((isSuccess = (0 != (this->m_thread))))
            this->m_thread->Run();
        return isSuccess;
    }

    virtual bool Wait(int cms, bool process_io) {
        if ((PeekQuitMessage(cms, process_io))) {
            if ((this->m_thread))
                this->m_thread->Quit();
        }
        return Extends::Wait(0, process_io);
    }

    virtual bool PeekQuitMessage(int& cms, bool& process_io) 
    { return false; }

    virtual void SetThread(talk_base::Thread* thread) {
        if ((this->m_thread))
            this->m_thread->set_socketserver(0);

        if ((this->m_thread = thread))
            this->m_thread->set_socketserver(this);
    }
protected:
    talk_base::Thread* m_thread;
};

namespace physical {

typedef SocketServer<> SocketServer;

} // namespace physical 

} // namespace base 
} // namespace talk 
} // namespace webrtc 
} // namespace xos 

#endif // _XOS_WEBRTC_TALK_BASE_SOCKETSERVER_HPP 
