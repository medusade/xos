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
///   File: MainWindow.hpp
///
/// Author: $author$
///   Date: 1/12/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_WINDOWS_MAINWINDOW_HPP
#define _XOS_GUI_WINDOWS_MAINWINDOW_HPP

#include "xos/gui/windows/Window.hpp"

namespace xos {
namespace windows {

typedef WindowImplement MainWindowImplement;
typedef Window MainWindowExtend;
///////////////////////////////////////////////////////////////////////
///  Class: MainWindow
///
/// Author: $author$
///   Date: 1/12/2013
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS MainWindow
: virtual public MainWindowImplement,
  public MainWindowExtend
{
public:
    typedef MainWindowImplement Implements;
    typedef MainWindowExtend Extends;

    MainWindow(HWND detached=0, bool isCreated=false)
    : Extends(detached, isCreated)
    {
    }
    virtual ~MainWindow()
    {
    }
    virtual LRESULT On_WM_CLOSE_WindowMessage
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        LRESULT lResult = 0;
        PostQuitMessage(0);
        lResult = OnWindowMessageDefault(hWnd,msg,wParam,lParam);
        return lResult;
    }
};

} // namespace windows 
} // namespace xos 

#endif // _XOS_GUI_WINDOWS_MAINWINDOW_HPP 
