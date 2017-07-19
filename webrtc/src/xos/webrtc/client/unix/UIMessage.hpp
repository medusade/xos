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
///   File: UIMessage.hpp
///
/// Author: $author$
///   Date: 10/22/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_WEBRTC_CLIENT_UNIX_UIMESSAGE_HPP
#define _XOS_WEBRTC_CLIENT_UNIX_UIMESSAGE_HPP

#include "xos/webrtc/client/UIMessage.hpp"
#include "xos/webrtc/client/SocketServer.hpp"
#include "xos/webrtc/client/Window.hpp"
#include "xos/os/unix/Thread.hpp"

namespace xos {
namespace webrtc {
namespace client {

typedef xos::Thread::Run UIMessageThreadExtend;
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS UIMessage::Thread: public UIMessageThreadExtend {
public:
    typedef UIMessageThreadExtend Extends;
    typedef client::physical::SocketServer SocketServer;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Thread(): m_thread(*this), m_uiWindow(0), m_socketServer(0) {
    }
    virtual ~Thread() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool CreateMessageThread(Window* uiWindow, SocketServer* socketServer = 0) {
        bool isSuccess = false;
        XOS_LOG_DEBUG("...");
        isSuccess = Create(uiWindow, socketServer);
        return isSuccess;
    }
    virtual bool DestroyMessageThread() {
        bool isSuccess = Destroy();
        return isSuccess;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Create(Window* uiWindow, SocketServer* socketServer = 0) {
        bool isSuccess = false;
        XOS_LOG_DEBUG(" in...");
        if (!(m_uiWindow) && (uiWindow)) {
            m_uiWindow = uiWindow;
            m_socketServer = socketServer;
            if ((isSuccess = m_thread.Create()))
                return isSuccess;
            else
            XOS_LOG_ERROR("failed on Extends::Create()");
            m_socketServer = 0;
            m_uiWindow = 0;
        }
        XOS_LOG_DEBUG(" ...out");
        return isSuccess;
    }
    virtual bool Destroy() {
        bool isSuccess = false;
        if ((m_uiWindow)) {
            m_uiWindow->PostUIMessage(Window::UI_THREAD_QUIT, 0,0);
            if ((isSuccess = m_thread.Destroy())) {
                m_socketServer = 0;
                m_uiWindow = 0;
            } else {
                XOS_LOG_ERROR("failed on Extends::Destroy()");
            }
        }
        return isSuccess;
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void operator()() {
        XOS_LOG_DEBUG(" in...");
        if ((m_uiWindow)) {
            m_uiWindow->OnUIMessageThreadStarted();
            if ((m_socketServer)) {
                XOS_LOG_DEBUG(" with m_socketServer ...\n");
                talk_base::AutoThread autoThread;
                m_socketServer->SetThread(talk_base::ThreadManager::CurrentThread());
                m_socketServer->Run();
                m_socketServer->SetThread(0);
            } else {
                XOS_LOG_DEBUG(" without m_socketServer ...\n");
                talk_base::AutoThread autoThread;
                SocketServer socketServer(*m_uiWindow);
                socketServer.Run();
            }
            m_uiWindow->OnUIMessageThreadFinished();
        }
        XOS_LOG_DEBUG("...out");
    }

protected:
    xos::unix::Thread m_thread;
    Window* m_uiWindow;
    SocketServer* m_socketServer;
};

typedef UIMessage::Thread::SocketServer WindowSocketServerExtends;
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Window::SocketServer: public WindowSocketServerExtends {
public:
    typedef WindowSocketServerExtends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    SocketServer(Window& peerWindow): Extends(peerWindow) {
    }
};

namespace unix {

typedef client::UIMessage UIMessage;

} // namespace unix 
} // namespace client 
} // namespace webrtc 
} // namespace xos 

#endif // _XOS_WEBRTC_CLIENT_UNIX_UIMESSAGE_HPP 
