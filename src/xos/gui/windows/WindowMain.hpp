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
///   File: WindowMain.hpp
///
/// Author: $author$
///   Date: 1/11/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_WINDOWS_WINDOWMAIN_HPP
#define _XOS_GUI_WINDOWS_WINDOWMAIN_HPP

#include "xos/gui/windows/Main.hpp"
#include "xos/gui/windows/MainWindow.hpp"
#include "xos/gui/windows/Window.hpp"
#include "xos/gui/windows/WindowClass.hpp"

namespace xos {
namespace windows {

typedef MainImplement WindowMainImplement;
typedef Main WindowMainExtend;
///////////////////////////////////////////////////////////////////////
///  Class: WindowMain
///
/// Author: $author$
///   Date: 1/11/2013
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS WindowMain
: virtual public WindowMainImplement,
  public WindowMainExtend
{
public:
    typedef WindowMainImplement Implements;
    typedef WindowMainExtend Extends;

    WindowMain() {
    }
    virtual ~WindowMain() {
    }

    virtual int WinMainLoop
    (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int cmdShow) {
        int err = 0;
        MSG msg;
        while ((GetMessage(&msg, NULL, 0,0))) {
            if ((TranslateMessage(&msg))) {
                DispatchMessage(&msg);
            }
        }
        return err;
    }
    virtual int WinMain
    (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int cmdShow) {
        int err = 1;
        MainWindow* mainWindow;
        if ((mainWindow = GetMainWindow())) {
            err = WinMainLoop(hInstance, hPrevInstance, cmdLine, cmdShow);
        }
        return err;
    }
    virtual int BeforeWinMain
    (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int cmdShow) {
        int err = 1;
        WindowClass* mainWindowClass;
        MainWindow* mainWindow;
        if ((mainWindowClass = RegisterMainWindowClass
            (hInstance, hPrevInstance, cmdLine, cmdShow))) 
        {
            if ((mainWindow = CreateMainWinow
                (*mainWindowClass, hInstance, hPrevInstance, cmdLine, cmdShow)))
                return 0;
            UnregisterMainWindowClass
            (mainWindowClass, hInstance, hPrevInstance, cmdLine, cmdShow);
        }
        return err;
    }
    virtual int AfterWinMain
    (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int cmdShow) {
        int err = 0;
        MainWindow* mainWindow;
        WindowClass* mainWindowClass;

        if ((mainWindow = GetMainWindow()))
        if (!(DestroyMainWindow
            (mainWindow, hInstance, hPrevInstance, cmdLine, cmdShow)))
            err = 1;

        if ((mainWindowClass = GetMainWindowClass()))
        if (!(UnregisterMainWindowClass
            (mainWindowClass, hInstance, hPrevInstance, cmdLine, cmdShow)))
            err = 1;

        return err;
    }

    virtual MainWindow* CreateMainWinow
    (WindowClass& mainWindowClass,
     HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int cmdShow) {
        LPCTSTR className;
        if ((className = mainWindowClass.GetWindowClassName()))
            if ((m_mainWindow.Create(hInstance, className, className)))
                return &m_mainWindow;
        return 0;
    }
    virtual bool DestroyMainWindow
    (MainWindow* mainWindow,
     HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int cmdShow) {
        if ((mainWindow))
            return mainWindow->Destroy();
        return false;
    }
    virtual MainWindow* GetMainWindow() const {
        return (MainWindow*)(&m_mainWindow);
    }

    virtual WindowClass* RegisterMainWindowClass
    (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int cmdShow) {
        if ((m_mainWindowClass.Register(hInstance)))
            return &m_mainWindowClass;
        return 0;
    }
    virtual bool UnregisterMainWindowClass
    (WindowClass* mainWindowClass, 
     HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int cmdShow) {
        if ((mainWindowClass))
            return mainWindowClass->Unregister();
        return false;
    }
    virtual WindowClass* GetMainWindowClass() const {
        return (WindowClass*)(&m_mainWindowClass);
    }

    virtual bool GetMessage
    (MSG* lpMsg, HWND hWnd, UINT wMsgFiltrerMin, UINT wMsgFilterMax) {
        if ((::GetMessage(lpMsg, hWnd, wMsgFiltrerMin, wMsgFilterMax)))
            return true;
        return false;
    }
    virtual bool TranslateMessage(const MSG* lpMsg) {
        ::TranslateMessage(lpMsg);
        return true;
    }
    virtual bool DispatchMessage(const MSG* lpMsg) {
        ::DispatchMessage(lpMsg);
        return true;
    }

protected:
    WindowClass m_mainWindowClass;
    MainWindow m_mainWindow;
};


} // namespace windows 
} // namespace xos 


#endif // _XOS_GUI_WINDOWS_WINDOWMAIN_HPP 
        

