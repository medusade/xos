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
///   File: WindowPeer.hpp
///
/// Author: $author$
///   Date: 10/21/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_WEBRTC_CLIENT_WINDOWPEER_HPP
#define _XOS_WEBRTC_CLIENT_WINDOWPEER_HPP

#include "xos/webrtc/client/PeerWindow.hpp"

namespace xos {
namespace webrtc {
namespace client {

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Window::WindowPeer
: virtual public UIMessage::ThreadObserverImplement {
public:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    WindowPeer(PeerWindow& uiWindow): m_uiWindow(uiWindow) {}
    virtual ~WindowPeer(){}

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Open() {
        bool isSuccess = m_uiWindow.OnWindowOpened(this);
        return isSuccess;
    }
    virtual bool Close() {
        bool isSuccess = m_uiWindow.OnWindowClosed(this);
        return isSuccess;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Attach() {
        bool isSuccess = false;
        XOS_LOG_DEBUG("...");
        if ((isSuccess = m_done.Create())) {
            if ((isSuccess = m_uiWindow.RegisterThreadObserver(this))) {
                if ((isSuccess = m_uiWindow.OnWindowAttached(this)))
                    return isSuccess;
                m_uiWindow.UnregisterThreadObserver(this);
            }
            m_done.Destroy();
        }
        return isSuccess;
    }
    virtual bool Detach() {
        bool isSuccess = m_uiWindow.OnWindowDetached(this);
        if (!(m_uiWindow.UnregisterThreadObserver(this)))
            isSuccess = false;
        if (!(m_done.Destroy()))
            isSuccess = false;
        return isSuccess;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool ConnectToServer
    (const std::string& serverName, int serverPort) {
        bool isTrue = false;
        XOS_LOG_DEBUG("...");
        isTrue = m_uiWindow.ConnectToServer(serverName, serverPort);
        return isTrue;
    }
    virtual bool DisconnectFromServer() {
        bool isTrue = m_uiWindow.DisconnectFromServer();
        return isTrue;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void OnQuit() {
        XOS_LOG_DEBUG("...");
        m_uiWindow.PostUIMessage(Window::UI_THREAD_QUIT, 0,0);
    }
    virtual void OnUIMessageThreadStarted() {
        XOS_LOG_DEBUG("...");
    }
    virtual void OnUIMessageThreadFinished() {
        XOS_LOG_DEBUG("...");
        m_done.Continue();
    }
    virtual bool TryWaitDone() {
        if (xos::WaitInterface::Success != m_done.TryWait())
            return false;
        return true;
    }
protected:
    PeerWindow& m_uiWindow;
    xos::os::Semaphore m_done;
};

} // namespace client 
} // namespace webrtc 
} // namespace xos 

#endif // _XOS_WEBRTC_CLIENT_WINDOWPEER_HPP 
