///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2013 $organization$
///
/// This software is provided by the author and contributors ``as is'' 
/// and any express or implied warranties, including, but not limited to, 
/// the implied warranties of merchantability and fitness for a particular 
/// purpose are disclaimed. In no event shall the author or contributors 
/// be liable for any direct, indirect, incidental, special, exemplary, 
/// or consequential damages (including, but not limited to, procurement 
/// of substitute goods or services; loss of use, data, or profits; or 
/// business interruption) however caused and on any theory of liability, 
/// whether in contract, strict liability, or tort (including negligence 
/// or otherwise) arising in any way out of the use of this software, 
/// even if advised of the possibility of such damage.
///
///   File: Window.hpp
///
/// Author: $author$
///   Date: 1/10/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_WINDOWS_WINDOW_HPP
#define _XOS_GUI_WINDOWS_WINDOW_HPP

#include "xos/gui/windows/WindowMessageTarget.hpp"
#include "xos/gui/windows/HWnd.hpp"
#include "xos/os/Logger.hpp"

#define XOS_GUI_WINDOWS_DEFAULT_WINDOW_STYLE \
    WS_VISIBLE | WS_OVERLAPPED | WS_THICKFRAME | \
    WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX

#define XOS_GUI_WINDOWS_DEFAULT_WINDOW_EXSTYLE 0

namespace xos {
namespace windows {

typedef WindowMessageTargetImplement WindowImplement;
typedef HWnd WindowExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Window
///
/// Author: $author$
///   Date: 1/10/2013
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Window: virtual public WindowImplement, public WindowExtend {
public:
    typedef WindowImplement Implements;
    typedef WindowExtend Extends;

    Window(HINSTANCE hInstance, HWND detached=0, bool isCreated=false)
    : Extends(hInstance, detached, isCreated) {
    }
    Window(HWND detached=0, bool isCreated=false)
    : Extends(0, detached, isCreated) {
    }
    virtual ~Window() {
        if (!(Destroyed()))
            XOS_LOG_ERROR("failed on Destroyed()");
    }

    virtual bool Create
    (HINSTANCE hInstance, LPCTSTR className, 
     LPCTSTR windowName=NULL, HWND hParentWnd=NULL_HANDLE, 
     HMENU hMenu=NULL_HANDLE, DWORD style=XOS_GUI_WINDOWS_DEFAULT_WINDOW_STYLE,
     DWORD exStyle=XOS_GUI_WINDOWS_DEFAULT_WINDOW_EXSTYLE, 
     int x=CW_USEDEFAULT, int y=CW_USEDEFAULT, 
     int width=CW_USEDEFAULT, int height=CW_USEDEFAULT,
     LPVOID lParam=NULL)
    {
        bool isSuccess = Create
        (exStyle, className, windowName, style, 
         x,y, width,height, hParentWnd, hMenu, hInstance, lParam);
        return isSuccess;
    }
    virtual bool Create
    (DWORD exStyle, LPCTSTR className, 
     LPCTSTR windowName, DWORD style, 
     int x, int y, int width, int height, 
     HWND hParentWnd, HMENU hMenu, 
     HINSTANCE hInstance, LPVOID lParam) 
    {
        bool isSuccess = false;
        HWND detached;

        if (!(Destroyed()))
            return false;

        if ((isSuccess = (NULL != (detached = CreateDetached
            (exStyle, className, windowName, style, 
             x, y, width, height, hParentWnd, hMenu, hInstance, 
             (lParam)?(lParam):((WindowMessageTargetImplement*)(this)))))))
            AttachCreated(hInstance, detached);

        return isSuccess;
    }
    virtual bool Destroy() {
        bool isSuccess = false;
        HWND detached;        
        if ((detached = Detach()))
            isSuccess = DestroyDetached(detached);
        return isSuccess;
    }

    virtual HWND CreateDetached
    (DWORD exStyle, LPCTSTR className, 
     LPCTSTR windowName, DWORD style, 
     int x, int y, int width, int height, 
     HWND hParentWnd, HMENU hMenu, 
     HINSTANCE hInstance, LPVOID lParam) const
    {
        HWND detached = NULL;
        if (!(detached = CreateWindowEx
            (exStyle, className, windowName, style, 
             x, y, width, height, hParentWnd, hMenu, hInstance, lParam))) {   
            XOS_LOG_ERROR("failed on CreateWindowEx()"); 
        }
        return detached;
    }
    virtual bool DestroyDetached(HWND detached) const
    {
        bool isSuccess = false;
        if ((detached))
        if (!(isSuccess = (FALSE != DestroyWindow(detached)))) {
            XOS_LOG_ERROR("failed on DestroyWindow()"); 
        }
        return isSuccess;
    }

    virtual bool Show(int nCmdShow=SW_SHOWNORMAL) {
        HWND hWnd;
        if ((hWnd = AttachedTo()))
        if ((ShowWindow(hWnd, nCmdShow)))
            return true;
        return false;
    }
    virtual bool Hide(int nCmdShow=SW_HIDE) {
        return Show(nCmdShow);
    }

    virtual bool Invalidate(bool eraseBackground=true) {
        HWND hWnd;
        if ((hWnd = AttachedTo())) {
            if ((::InvalidateRect(hWnd, NULL, eraseBackground)))
                return true;
        }
        return false;
    }
    virtual bool Validate() {
        HWND hWnd;
        if ((hWnd = AttachedTo())) {
            if ((::ValidateRect(hWnd, NULL)))
                return true;
        }
        return false;
    }
};

} // namespace windows 
} // namespace xos 

#endif // _XOS_GUI_WINDOWS_WINDOW_HPP 
