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
///   File: ConnectWindow.hpp
///
/// Author: $author$
///   Date: 1/17/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOWS_CONNECTWINDOW_HPP
#define _XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOWS_CONNECTWINDOW_HPP

#include "xos/webrtc/peerconnection/client/MainWindow.hpp"
#include "xos/gui/windows/Window.hpp"
#include "xos/gui/windows/WindowClass.hpp"

namespace xos {
namespace webrtc {
namespace peerconnection {
namespace client {
namespace windows {

typedef xos::windows::WindowImplement ConnectWindowImplement;
typedef xos::windows::Window ConnectWindowExtend;
///////////////////////////////////////////////////////////////////////
///  Class: ConnectWindow
///
/// Author: $author$
///   Date: 1/17/2013
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS ConnectWindow
: virtual public ConnectWindowImplement,
  public ConnectWindowExtend
{
public:
    typedef ConnectWindowImplement Implements;
    typedef ConnectWindowExtend Extends;
    using Extends::Create;

    ConnectWindow(client::MainWindow& mainWindow)
    : m_mainWindow(mainWindow) {
    }
    virtual ~ConnectWindow() {
    }

    virtual bool OnSize(xos::windows::Window& parent) {
        HWND hParent;
        RECT rc;
        if ((hParent = parent.AttachedTo())) {
            if ((GetClientRect(hParent, &rc))) {
                int width = ((rc.right-rc.left)*3)/4;
                int height = ((rc.bottom-rc.top)*3)/4;
                int x = ((rc.right-rc.left)-width)/2;
                int y = ((rc.bottom-rc.top)-height)/2;
                if ((MoveWindow(AttachedTo(), x,y, width,height, TRUE)))
                    return true;
            }
        }
        return false;
    }
    virtual bool Create(xos::windows::Window& parent) {
        HINSTANCE hParentInstance;
        HWND hParent;
        RECT rc;
        if ((hParentInstance = parent.AttachedToHInstance()))
        if ((hParent = parent.AttachedTo()))
        if ((GetClientRect(hParent, &rc)))
        {
            int width = ((rc.right-rc.left)*3)/4;
            int height = ((rc.bottom-rc.top)*3)/4;
            int x = ((rc.right-rc.left)-width)/2;
            int y = ((rc.bottom-rc.top)-height)/2;
            return Create
            (hParentInstance, 
             xos::windows::WindowClass::DefaultWindowClassNameChars(),
             xos::windows::WindowClass::DefaultWindowClassNameChars(),
             hParent, NULL, WS_VISIBLE | WS_CHILD,0, x,y, width,height);
        }
        return false;
    }
protected:
    client::MainWindow& m_mainWindow;
};

} // namespace windows 
} // namespace client 
} // namespace peerconnection 
} // namespace webrtc 
} // namespace xos 

#endif // _XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOWS_CONNECTWINDOW_HPP 
