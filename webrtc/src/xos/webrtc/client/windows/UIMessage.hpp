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
///   Date: 10/20/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_WEBRTC_CLIENT_WINDOWS_UIMESSAGE_HPP
#define _XOS_WEBRTC_CLIENT_WINDOWS_UIMESSAGE_HPP

#include "xos/webrtc/client/UIMessage.hpp"
#include "xos/webrtc/client/SocketServer.hpp"
#include "xos/webrtc/client/Window.hpp"

namespace xos {
namespace webrtc {
namespace client {

class _EXPORT_CLASS UIMessage::Thread {
public:
    enum ThreadWindowMessages 
    {
        UI_MESSAGE_THREAD_UI_MESSAGE = (WM_APP+1),
        UI_MESSAGE_THREAD_UI_CALLBACK,
        UI_MESSAGE_THREAD_QUIT
    };

    typedef client::physical::SocketServer SocketServerExtend;

    class _EXPORT_CLASS SocketServer: public SocketServerExtend {
    public:
        typedef SocketServerExtend Extends;

        SocketServer(Window& peerWindow): Extends(peerWindow) {
        }
        virtual ~SocketServer() {
        }
        virtual bool Wait(int cms, bool process_io) {
            MSG msg;

            if ((PeekMessage(&msg, NULL, 0,0, TRUE)))
                OnWindowMessage(m_peerWindow, msg);

            return Extends::Wait(0, process_io);
        }
    };

    DWORD m_tid;
    HANDLE m_trd;
    Window* m_uiWindow;

    Thread(): m_tid(0), m_trd(0), m_uiWindow(0) {
    }
    virtual ~Thread() {
        DestroyMessageThread();
    }

    ///////////////////////////////////////////////////////////////////////
    // socket server message thread
    ///////////////////////////////////////////////////////////////////////
    virtual bool Create(Window* uiWindow) {
        bool isSuccess = false;
        HANDLE trd;
        DWORD tid;

        if (!(m_trd)) {
            m_uiWindow = uiWindow;
            if ((trd = CreateThread
                (NULL, 0, RunThread, (LPVOID)(this), 0, &tid))) {
                m_trd = trd;
                m_tid = tid;
                isSuccess = true;
            } else {
                m_uiWindow = 0;
            }
        }
        return isSuccess;
    }
    virtual bool Destroy() {
        bool isSuccess = false;
        if ((m_trd) && (m_uiWindow))
        {
            m_uiWindow->PostUIMessage(Window::UI_THREAD_QUIT, 0,0);
            WaitForSingleObject(m_trd, INFINITE);
            CloseHandle(m_trd);
            m_trd = 0;
            m_tid = 0;
            m_uiWindow = 0;
            isSuccess = true;
        }
        return isSuccess;
    }
    virtual void Run()
    {
        talk_base::Thread* thread;

        if ((m_uiWindow)) {
            m_uiWindow->OnUIMessageThreadStarted();
            if ((thread = talk_base::ThreadManager::WrapCurrentThread()))
            {
                talk_base::Thread* oldThread;

                if (thread != (oldThread = talk_base::ThreadManager::CurrentThread()))
                    talk_base::ThreadManager::SetCurrent(thread);

                if ((talk_base::ThreadManager::CurrentThread()))
                {
                    SocketServer socketServer(*m_uiWindow);
                    socketServer.Run();
                }

                if (thread != oldThread)
                {
                    talk_base::ThreadManager::SetCurrent(oldThread);
                    talk_base::ThreadManager::UnwrapCurrentThread();
                }
            }
            m_uiWindow->OnUIMessageThreadFinished();
        }
    }
    static DWORD WINAPI RunThread(LPVOID lpParameter) {
        DWORD result = 1;
        Thread* thread;

        if ((thread = (Thread*)(lpParameter)))
            thread->Run();
        return result;
    }

    ///////////////////////////////////////////////////////////////////////
    // uiWindow message thread
    ///////////////////////////////////////////////////////////////////////
    virtual bool CreateMessageThread(Window* uiWindow) {
        bool isSuccess = false;
        HANDLE trd;
        DWORD tid;

        if (!(m_trd))
        if ((trd = CreateThread
            (NULL, 0, UIWindowThread, (LPVOID)(uiWindow), 0, &tid)))
        {
            m_trd = trd;
            m_tid = tid;
            m_uiWindow = 0;
            isSuccess = true;
        }
        return isSuccess;
    }
    static DWORD WINAPI UIWindowThread(LPVOID lpParameter) {
        DWORD result = 1;
        Window* uiWindow;
        bool isQuitMessage;
        MSG msg;

        if ((uiWindow = (Window*)(lpParameter)))
        while ((GetMessage(&msg, NULL, 0, 0)))
        {
            if ((isQuitMessage = OnWindowMessage(*uiWindow, msg)))
                return result;
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////
    // hWnd message thread
    ///////////////////////////////////////////////////////////////////////
    virtual bool CreateMessageThread(HWND hWnd) {
        bool isSuccess = false;
        HANDLE trd;
        DWORD tid;

        if (!(m_trd))
        if ((trd = CreateThread
            (NULL, 0,HwndThread, (LPVOID)(hWnd), 0, &tid)))
        {
            m_trd = trd;
            m_tid = tid;
            m_uiWindow = 0;
            isSuccess = true;
        }
        return isSuccess;
    }
    static DWORD WINAPI HwndThread(LPVOID lpParameter) {
        DWORD result = 1;
        bool isQuitMessage;
        HWND hWnd;
        MSG msg;

        if ((hWnd = (HWND)(lpParameter)))
        while ((GetMessage(&msg, NULL, 0, 0)))
        {
            if ((isQuitMessage = OnWindowMessage(hWnd, msg)))
                return result;
        }
        return result;
    }
    virtual bool DestroyMessageThread() {
        bool isSuccess = false;
        if ((m_trd) && (!m_uiWindow)) {
            ::PostThreadMessage(m_tid, UI_MESSAGE_THREAD_QUIT, 0, 0);
            WaitForSingleObject(m_trd, INFINITE);
            CloseHandle(m_trd);
            m_trd = 0;
            m_tid = 0;
            m_uiWindow = 0;
            isSuccess = true;
        }
        return isSuccess;
    }
    /*virtual bool DestroyMessageThread() {
        bool isSuccess = false;
        if ((m_trd))
        {
            ::PostThreadMessage(m_tid, UI_MESSAGE_THREAD_QUIT, 0, 0);
            WaitForSingleObject(m_trd, INFINITE);
            CloseHandle(m_trd);
            m_trd = 0;
            m_tid = 0;
            isSuccess = true;
        }
        return isSuccess;
    }*/

    ///////////////////////////////////////////////////////////////////////
    // post messages
    ///////////////////////////////////////////////////////////////////////
    virtual bool PostUIThreadMessage(int msg_id, int id, void* data) {
        return (FALSE != (PostThreadMessage
        (UI_MESSAGE_THREAD_UI_MESSAGE, 
         MAKEWPARAM(msg_id, id), (LPARAM)(data))));
    }
    virtual BOOL PostThreadMessage(UINT msg, WPARAM wParam, LPARAM lParam) {
        DWORD tid = GetCurrentThreadId();
        return ::PostThreadMessage(tid, msg, wParam, lParam);
    }

    ///////////////////////////////////////////////////////////////////////
    // message thread id
    ///////////////////////////////////////////////////////////////////////
    virtual DWORD SetCurrentThreadId(DWORD tid) {
        m_tid = tid;
        return m_tid;
    }
    virtual DWORD GetCurrentThreadId() const {
        if (!(m_tid))
            return ::GetCurrentThreadId();
        return m_tid;
    }

    /*virtual void Run() {
        if ((m_uiWindow)) {
            bool done;
            MSG msg;
            do {
                if (!(done = !(GetMessage(&msg, NULL, 0, 0)))) {
                    if ((msg.hwnd)) {
                        TranslateMessage(&msg);
                        DispatchMessage(&msg);
                    } else {
                        if (!(done = (msg.message == UI_MESSAGE_THREAD_QUIT))) {
                            switch(msg.message)
                            {
                            case UI_MESSAGE_THREAD_UI_MESSAGE:
                                if (!(done = (Window::UI_THREAD_QUIT == ((int)(LOWORD(msg.wParam)))))) {
                                    m_uiWindow->OnUIMessage
                                    ((int)(LOWORD(msg.wParam)), 
                                     (int)(HIWORD(msg.wParam)), (void*)(msg.lParam));
                                }
                                break;

                            case UI_MESSAGE_THREAD_UI_CALLBACK:
                                m_uiWindow->OnUIMessage
                                (Window::UI_THREAD_CALLBACK, 
                                 (int)(msg.wParam), (void*)(msg.lParam));
                                break;
                            }
                        }
                    }
                }
            } while (!(done));
        }
    }*/

    ///////////////////////////////////////////////////////////////////////
    // on window msg for uiWindow
    ///////////////////////////////////////////////////////////////////////
    static bool OnWindowMessage(Window& uiWindow, MSG& msg) {
        bool isQuitMessage = false;
        if ((msg.hwnd)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        switch(msg.message) {
        case UI_MESSAGE_THREAD_UI_MESSAGE:
            if ((isQuitMessage = ((int)(LOWORD(msg.wParam)) == Window::UI_THREAD_QUIT)))
                break;
            uiWindow.PostUIMessage
            ((int)(LOWORD(msg.wParam)), 
             (int)(HIWORD(msg.wParam)), (void*)(msg.lParam));
            break;

        case UI_MESSAGE_THREAD_UI_CALLBACK:
            uiWindow.PostUIMessage
            (Window::UI_THREAD_CALLBACK, 
             (int)(msg.wParam), (void*)(msg.lParam));
            break;

        case UI_MESSAGE_THREAD_QUIT:
        case WM_NULL:
            isQuitMessage = true;
        }
        return isQuitMessage;
    }

    ///////////////////////////////////////////////////////////////////////
    // on window msg for hWnd
    ///////////////////////////////////////////////////////////////////////
    static bool OnWindowMessage(HWND hWnd, MSG& msg) {
        bool isQuitMessage = false;
        if ((msg.hwnd)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        switch(msg.message) {
        case UI_MESSAGE_THREAD_UI_MESSAGE:
            if ((isQuitMessage = ((int)(LOWORD(msg.wParam)) == Window::UI_THREAD_QUIT)))
                break;
            PostMessage(hWnd, msg.message, msg.wParam, msg.lParam);
            break;

        case UI_MESSAGE_THREAD_UI_CALLBACK:
            PostMessage(hWnd, msg.message, msg.wParam, msg.lParam);
            break;

        case UI_MESSAGE_THREAD_QUIT:
        case WM_NULL:
            isQuitMessage = true;
        }
        return isQuitMessage;
    }

    /*static DWORD WINAPI MessageThreadThread(LPVOID lpParameter) {
        DWORD result = 1;
        Thread* thread;

        if ((thread = (Thread*)(lpParameter)))
            thread->Run();
        return result;
    }*/
    /*static DWORD WINAPI MessageThreadUIWindow(LPVOID lpParameter) {
        DWORD result = 1;
        Window* uiWindow;
        bool isQuitMessage;
        MSG msg;

        if ((uiWindow = (Window*)(lpParameter)))
        while ((GetMessage(&msg, NULL, 0, 0)))
        {
            if ((isQuitMessage = OnWindowMessage(*uiWindow, msg)))
                return result;
        }
        return result;
    }*/
    /*static DWORD WINAPI MessageThreadHwnd(LPVOID lpParameter) {
        DWORD result = 1;
        bool isQuitMessage;
        HWND hWnd;
        MSG msg;

        if ((hWnd = (HWND)(lpParameter)))
        while ((GetMessage(&msg, NULL, 0, 0)))
        {
            if ((isQuitMessage = OnWindowMessage(hWnd, msg)))
                return result;
        }
        return result;
    }*/
};

typedef UIMessage::Thread::SocketServer WindowSocketServerExtends;

class _EXPORT_CLASS Window::SocketServer: public WindowSocketServerExtends {
public:
    typedef WindowSocketServerExtends Extends;
    SocketServer(Window& peerWindow): Extends(peerWindow) {
    }
};

namespace windows {

class _EXPORT_CLASS UIMessage {
public:
    typedef client::UIMessage::ThreadId ThreadId;
    typedef client::UIMessage::Thread ThreadExtends;
    class _EXPORT_CLASS Thread;
};

class _EXPORT_CLASS UIMessage::Thread: public UIMessage::ThreadExtends {
public:
    typedef UIMessage::ThreadExtends Extends;

    virtual bool CreateMessageThread(Window* uiWindow, SocketServer* socketServer = 0) {
        return Extends::Create(uiWindow);
    }
    virtual bool Create(Window* uiWindow, SocketServer* socketServer = 0) {
        return Extends::Create(uiWindow);
    }
    virtual bool DestroyMessageThread(){
        return Destroy();
    }
};

} // namespace windows
} // namespace client 
} // namespace webrtc 
} // namespace xos 

#endif // _XOS_WEBRTC_CLIENT_WINDOWS_UIMESSAGE_HPP 
