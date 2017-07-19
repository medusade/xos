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
///   File: Window.hpp
///
/// Author: $author$
///   Date: 10/20/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_WEBRTC_CLIENT_WINDOWS_CONSOLE_WINDOW_HPP
#define _XOS_WEBRTC_CLIENT_WINDOWS_CONSOLE_WINDOW_HPP

#include "xos/webrtc/client/console/Window.hpp"
#include "xos/webrtc/client/windows/UIMessage.hpp"

namespace xos {
namespace webrtc {
namespace client {
namespace windows {
namespace console {

typedef client::WindowImplement WindowImplement;
typedef client::Window WindowExtend;

class _EXPORT_CLASS Window: virtual public WindowImplement, public WindowExtend
{
public:
    typedef WindowImplement Implements;
    typedef WindowExtend Extends;

    UIMessage::Thread m_msgThread;

    Window
    (const char* serverName=0, int serverPort=0,
     bool showConnectionState = XOS_WEBRTC_CLIENT_WINDOW_DEFAULT_SHOW_CONNECTION_STATE,
     bool handleButtonEvents = XOS_WEBRTC_CLIENT_WINDOW_DEFAULT_HANDLE_BUTTON_EVENTS)
    : Extends(serverName, serverPort, showConnectionState, handleButtonEvents) {
        m_useUIMessageQueue = true;
        m_useOpenGLRenderer = false;
        m_autoConnectToPeerOn = true;
        m_autoConnectToPeerAfterOn = true;
    }
    virtual ~Window() {
    }

    virtual bool CreateUIMessageThread()
    {
        bool isSuccess = false;
        isSuccess = m_msgThread.CreateMessageThread(this);
        return isSuccess;
    }
    virtual bool DestroyUIMessageThread()
    {
        bool isSuccess = m_msgThread.DestroyMessageThread();
        return isSuccess;
    }
    virtual UIMessage::ThreadId GetUIMessageThreadId()
    {
        return &m_msgThread;
    }

    virtual bool PostUIMessage
    (int msg_id, int id, void* data)
    { 
        OnDefaultAction(msg_id, id, data);
        return true; 
    }
    virtual void PostUIThreadMessage
    (UIMessage::ThreadId tid, int msg_id, int id, void* data)
    {
        if ((tid))
            tid->PostThreadMessage
            (UIMessage::Thread::UI_MESSAGE_THREAD_UI_MESSAGE, 
             MAKEWPARAM(msg_id, id), (LPARAM)(data));
    }

    virtual void OnOpen()
    {
        CreateUIMessageThread();
        Extends::OnOpen();
    }
    virtual void OnClose()
    {
        Extends::OnClose();
        DestroyUIMessageThread();
    }
};

} // namespace console 
} // namespace windows 
} // namespace client 
} // namespace webrtc 
} // namespace xos 

#endif // _XOS_WEBRTC_CLIENT_WINDOWS_CONSOLE_WINDOW_HPP 
        

