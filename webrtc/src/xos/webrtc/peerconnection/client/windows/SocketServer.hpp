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
///   Date: 12/25/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOWS_SOCKETSERVER_HPP
#define _XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOWS_SOCKETSERVER_HPP

#include "xos/webrtc/peerconnection/client/SocketServer.hpp"
#include "xos/webrtc/peerconnection/client/windows/UIMessage.hpp"
#include "talk/base/win32socketinit.h"
#include "talk/base/win32socketserver.h"
#include "talk/base/thread.h"
#include "talk/base/criticalsection.h"

namespace xos {
namespace webrtc {
namespace peerconnection {
namespace client {
namespace windows {

typedef client::physical::SocketServer SocketServerExtend;
///////////////////////////////////////////////////////////////////////
///  Class: SocketServer
///
/// Author: $author$
///   Date: 12/25/2012
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS SocketServer: public SocketServerExtend {
public:
    typedef SocketServerExtend Extends;

    SocketServer(MainWindow& peerWindow): Extends(peerWindow), m_wakeup(false) {
    }
    virtual ~SocketServer() {
    }
    virtual bool Wait(int cms, bool process_io) {
        MSG msg;

        if (process_io) {
            if ((PeekMessage(&msg, NULL, 0,0, TRUE))) {
                UIMessage::Thread::OnWindowMessage(m_peerWindow, msg);
            }
        } else {
            if (0 > (cms)) {
                bool isSuccess = true;
                int msg_id, id;
                void* data;
                if ((isSuccess = (m_peerWindow.GetUIMessage
                    (msg_id, id, data, 
                     MainWindow::UI_THREAD_WAKEUP, 
                     MainWindow::UI_THREAD_WAKEUP))))
                {
                    talk_base::CritScope scope(&crit_);
                    if (m_wakeup) {
                        m_wakeup = false;
                        return true;
                    }
                }
                return isSuccess;
                //return Extends::Wait(0, process_io);
            }
        }
        return Extends::Wait(0, process_io);
    }
    virtual void WakeUp() {
        {
            talk_base::CritScope scope(&crit_);
            if (m_wakeup)
                return;
            m_wakeup = true;
        }
        m_peerWindow.PostUIMessage(MainWindow::UI_THREAD_WAKEUP, 0, 0);
        //Extends::WakeUp();
    }
    virtual bool PeekUIMessage(int& msg_id, int& id, void*& data) {
        bool isSuccess;
        if ((isSuccess = m_peerWindow.PeekUIMessage(msg_id, id, data))) {
            if (MainWindow::UI_THREAD_WAKEUP == (msg_id)) {
                m_peerWindow.PostUIMessage(MainWindow::UI_THREAD_WAKEUP, 0, 0);
                return false;
            }
        }
    }
protected:
    talk_base::CriticalSection crit_;
    bool m_wakeup;
};

} // namespace windows 
} // namespace client 
} // namespace peerconnection 
} // namespace webrtc 
} // namespace xos 

#endif // _XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOWS_SOCKETSERVER_HPP 
