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
///   File: UIMessage.hpp
///
/// Author: $author$
///   Date: 1/6/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOWS_UIMESSAGE_HPP
#define _XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOWS_UIMESSAGE_HPP

#include "xos/webrtc/peerconnection/client/UIMessage.hpp"
#include "xos/webrtc/peerconnection/client/MainWindow.hpp"
#include "xos/webrtc/peerconnection/client/SocketServer.hpp"

namespace xos {
namespace webrtc {
namespace peerconnection {
namespace client {

///////////////////////////////////////////////////////////////////////
///  Class: UIMessage::Thread
///
/// Author: $author$
///   Date: 1/6/2013
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS UIMessage::Thread {
public:
    enum ThreadWindowMessages 
    {
        UI_MESSAGE_THREAD_UI_MESSAGE = (WM_APP+1),
        UI_MESSAGE_THREAD_UI_CALLBACK,
        UI_MESSAGE_THREAD_QUIT,
        UI_MESSAGE_THREAD_WAKEUP
    };

    typedef client::physical::SocketServer SocketServerExtend;
    ///////////////////////////////////////////////////////////////////////
    ///  Class: SocketServer
    ///
    /// Author: $author$
    ///   Date: 1/12/2013
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
                    OnWindowMessage(m_peerWindow, msg);
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

    Thread()
    : m_tid(0), m_trd(0), m_uiWindow(0)
    {
    }
    virtual ~Thread()
    {
        Destroy();
    }

    virtual bool Create(MainWindow* uiWindow)
    {
        bool isSuccess = false;
        HANDLE trd;
        DWORD tid;

        if (!(m_trd) && !(m_uiWindow))
        {
            m_uiWindow = uiWindow;
            if ((trd = CreateThread(NULL, 0, ThreadRun, (LPVOID)(this), 0, &tid)))
            {
                m_trd = trd;
                m_tid = tid;
                isSuccess = true;
            }
            else
            m_uiWindow = 0;
        }
        return isSuccess;
    }
    virtual bool Destroy()
    {
        bool isSuccess = false;
        if ((m_trd) && (m_uiWindow))
        {
            m_uiWindow->PostUIMessage(MainWindow::UI_THREAD_QUIT, 0,0);
            WaitForSingleObject(m_trd, INFINITE);
            CloseHandle(m_trd);
            m_trd = 0;
            m_tid = 0;
            m_uiWindow = 0;
            isSuccess = true;
        }
        return isSuccess;
    }

    static bool OnWindowMessage(MainWindow& uiWindow, MSG& msg) {
        bool isQuitMessage = false;
        if ((msg.hwnd))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        switch(msg.message)
        {
        case UI_MESSAGE_THREAD_UI_MESSAGE:
            if ((isQuitMessage = ((int)(LOWORD(msg.wParam))
                == MainWindow::UI_THREAD_QUIT)))
                break;
            uiWindow.PostUIMessage
            ((int)(LOWORD(msg.wParam)), 
             (int)(HIWORD(msg.wParam)), (void*)(msg.lParam));
            break;

        case UI_MESSAGE_THREAD_UI_CALLBACK:
            uiWindow.PostUIMessage
            (MainWindow::UI_THREAD_CALLBACK, 
             (int)(msg.wParam), (void*)(msg.lParam));
            break;

        case UI_MESSAGE_THREAD_QUIT:
        case WM_NULL:
            isQuitMessage = true;
        }
        return isQuitMessage;
    }

 protected:
    virtual DWORD Run()
    {
        talk_base::Thread* thread;

        if ((m_uiWindow))
        if ((thread = talk_base::ThreadManager::Instance()->WrapCurrentThread()))
        {
            talk_base::Thread* oldThread;

            if (thread != (oldThread = talk_base::ThreadManager::Instance()->CurrentThread()))
                talk_base::ThreadManager::Instance()->SetCurrentThread(thread);

            if ((talk_base::ThreadManager::Instance()->CurrentThread()))
            {
                SocketServer socketServer(*m_uiWindow);
                socketServer.Run();
            }

            if (thread != oldThread)
            {
                talk_base::ThreadManager::Instance()->SetCurrentThread(oldThread);
                talk_base::ThreadManager::Instance()->UnwrapCurrentThread();
            }
        }
        return 0;
    }
    static DWORD WINAPI ThreadRun(LPVOID lpParameter)
    {
        DWORD result = 1;
        Thread* thread;
        if ((thread = (Thread*)(lpParameter)))
            result = thread->Run();
        return result;
    }

 protected:
    DWORD m_tid;
    HANDLE m_trd;
    MainWindow* m_uiWindow;
};

namespace windows {
} // namespace windows 
} // namespace client 
} // namespace peerconnection 
} // namespace webrtc 
} // namespace xos 

#endif // _XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOWS_UIMESSAGE_HPP 
