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
///   File: WindowMessageMembers.hpp
///
/// Author: $author$
///   Date: 1/10/2013
///////////////////////////////////////////////////////////////////////
#if defined(XOS_GUI_WINDOWS_WINDOWMESSAGEMEMBERS_CLASS)
#include "xos/base/Base.hpp"
namespace xos {
namespace windows {
///////////////////////////////////////////////////////////////////////
///  Class: WindowMessageMembers
///
/// Author: $author$
///   Date: 1/10/2013
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS WindowMessageMembers
{
public:
#endif // defined(XOS_GUI_WINDOWS_WINDOWMESSAGEMEMBERS_CLASS) 

    virtual LRESULT On_WM_NCCREATE_WindowMessage
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        LRESULT lResult = 0;
        lResult = OnWindowMessageDefault(hWnd,msg,wParam,lParam);
        return lResult;
    }
    virtual LRESULT On_WM_NCDESTROY_WindowMessage
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        LRESULT lResult = 0;
        lResult = OnWindowMessageDefault(hWnd,msg,wParam,lParam);
        return lResult;
    }
    virtual LRESULT On_WM_CREATE_WindowMessage
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        LRESULT lResult = 0;
        lResult = OnWindowMessageDefault(hWnd,msg,wParam,lParam);
        return lResult;
    }
    virtual LRESULT On_WM_DESTROY_WindowMessage
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        LRESULT lResult = 0;
        lResult = OnWindowMessageDefault(hWnd,msg,wParam,lParam);
        return lResult;
    }
    virtual LRESULT On_WM_PAINT_WindowMessage
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        LRESULT lResult = 0;
        lResult = OnWindowMessageDefault(hWnd,msg,wParam,lParam);
        return lResult;
    }
    virtual LRESULT On_WM_PAINTICON_WindowMessage
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        LRESULT lResult = 0;
        lResult = OnWindowMessageDefault(hWnd,msg,wParam,lParam);
        return lResult;
    }
    virtual LRESULT On_WM_ERASEBKGND_WindowMessage
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        LRESULT lResult = 0;
        lResult = OnWindowMessageDefault(hWnd,msg,wParam,lParam);
        return lResult;
    }
    virtual LRESULT On_WM_ICONERASEBKGND_WindowMessage
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        LRESULT lResult = 0;
        lResult = OnWindowMessageDefault(hWnd,msg,wParam,lParam);
        return lResult;
    }
    virtual LRESULT On_WM_SHOWWINDOW_WindowMessage
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        LRESULT lResult = 0;
        lResult = OnWindowMessageDefault(hWnd,msg,wParam,lParam);
        return lResult;
    }
    virtual LRESULT On_WM_CLOSE_WindowMessage
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        LRESULT lResult = 0;
        lResult = OnWindowMessageDefault(hWnd,msg,wParam,lParam);
        return lResult;
    }
    virtual LRESULT On_WM_MOVE_WindowMessage
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        LRESULT lResult = 0;
        lResult = OnWindowMessageDefault(hWnd,msg,wParam,lParam);
        return lResult;
    }
    virtual LRESULT On_WM_SIZE_WindowMessage
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        LRESULT lResult = 0;
        lResult = OnWindowMessageDefault(hWnd,msg,wParam,lParam);
        return lResult;
    }
    virtual LRESULT On_WM_ACTIVATE_WindowMessage
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        LRESULT lResult = 0;
        lResult = OnWindowMessageDefault(hWnd,msg,wParam,lParam);
        return lResult;
    }
    virtual LRESULT On_WM_ENABLE_WindowMessage
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        LRESULT lResult = 0;
        lResult = OnWindowMessageDefault(hWnd,msg,wParam,lParam);
        return lResult;
    }
    virtual LRESULT On_WM_SETFOCUS_WindowMessage
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        LRESULT lResult = 0;
        lResult = OnWindowMessageDefault(hWnd,msg,wParam,lParam);
        return lResult;
    }
    virtual LRESULT On_WM_KILLFOCUS_WindowMessage
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        LRESULT lResult = 0;
        lResult = OnWindowMessageDefault(hWnd,msg,wParam,lParam);
        return lResult;
    }
    virtual LRESULT On_WM_QUERYOPEN_WindowMessage
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        LRESULT lResult = 0;
        lResult = OnWindowMessageDefault(hWnd,msg,wParam,lParam);
        return lResult;
    }
    virtual LRESULT On_WM_COMMAND_WindowMessage
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        LRESULT lResult = 0;
        lResult = OnWindowMessageDefault(hWnd,msg,wParam,lParam);
        return lResult;
    }
    virtual LRESULT On_WM_QUIT_WindowMessage
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        LRESULT lResult = 0;
        lResult = OnWindowMessageDefault(hWnd,msg,wParam,lParam);
        return lResult;
    }
    virtual LRESULT On_WM_NOTIFY_WindowMessage
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        LRESULT lResult = 0;
        lResult = OnWindowMessageDefault(hWnd,msg,wParam,lParam);
        return lResult;
    }
    virtual LRESULT On_WM_PARENTNOTIFY_WindowMessage
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        LRESULT lResult = 0;
        lResult = OnWindowMessageDefault(hWnd,msg,wParam,lParam);
        return lResult;
    }
    virtual LRESULT On_WM_DROPFILES_WindowMessage
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        LRESULT lResult = 0;
        lResult = OnWindowMessageDefault(hWnd,msg,wParam,lParam);
        return lResult;
    }
    virtual LRESULT On_WM_QUERYDRAGICON_WindowMessage
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        LRESULT lResult = 0;
        lResult = OnWindowMessageDefault(hWnd,msg,wParam,lParam);
        return lResult;
    }
    virtual LRESULT On_WM_NCPAINT_WindowMessage
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        LRESULT lResult = 0;
        lResult = OnWindowMessageDefault(hWnd,msg,wParam,lParam);
        return lResult;
    }
    virtual LRESULT On_WM_NCACTIVATE_WindowMessage
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        LRESULT lResult = 0;
        lResult = OnWindowMessageDefault(hWnd,msg,wParam,lParam);
        return lResult;
    }
    virtual LRESULT On_WM_NCCALCSIZE_WindowMessage
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        LRESULT lResult = 0;
        lResult = OnWindowMessageDefault(hWnd,msg,wParam,lParam);
        return lResult;
    }
    virtual LRESULT On_WM_NCHITTEST_WindowMessage
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        LRESULT lResult = 0;
        lResult = OnWindowMessageDefault(hWnd,msg,wParam,lParam);
        return lResult;
    }
    virtual LRESULT On_WM_MOUSEMOVE_WindowMessage
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        LRESULT lResult = 0;
        lResult = OnWindowMessageDefault(hWnd,msg,wParam,lParam);
        return lResult;
    }
    virtual LRESULT On_WM_MOUSEHOVER_WindowMessage
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        LRESULT lResult = 0;
        lResult = OnWindowMessageDefault(hWnd,msg,wParam,lParam);
        return lResult;
    }
    virtual LRESULT On_WM_MOUSELEAVE_WindowMessage
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        LRESULT lResult = 0;
        lResult = OnWindowMessageDefault(hWnd,msg,wParam,lParam);
        return lResult;
    }
    virtual LRESULT On_WM_LBUTTONDOWN_WindowMessage
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        LRESULT lResult = 0;
        lResult = OnWindowMessageDefault(hWnd,msg,wParam,lParam);
        return lResult;
    }
    virtual LRESULT On_WM_LBUTTONUP_WindowMessage
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        LRESULT lResult = 0;
        lResult = OnWindowMessageDefault(hWnd,msg,wParam,lParam);
        return lResult;
    }
    virtual LRESULT On_WM_LBUTTONDBLCLK_WindowMessage
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        LRESULT lResult = 0;
        lResult = OnWindowMessageDefault(hWnd,msg,wParam,lParam);
        return lResult;
    }
    virtual LRESULT On_WM_RBUTTONDOWN_WindowMessage
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        LRESULT lResult = 0;
        lResult = OnWindowMessageDefault(hWnd,msg,wParam,lParam);
        return lResult;
    }
    virtual LRESULT On_WM_RBUTTONUP_WindowMessage
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        LRESULT lResult = 0;
        lResult = OnWindowMessageDefault(hWnd,msg,wParam,lParam);
        return lResult;
    }
    virtual LRESULT On_WM_RBUTTONDBLCLK_WindowMessage
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        LRESULT lResult = 0;
        lResult = OnWindowMessageDefault(hWnd,msg,wParam,lParam);
        return lResult;
    }
    virtual LRESULT On_WM_MBUTTONDOWN_WindowMessage
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        LRESULT lResult = 0;
        lResult = OnWindowMessageDefault(hWnd,msg,wParam,lParam);
        return lResult;
    }
    virtual LRESULT On_WM_MBUTTONUP_WindowMessage
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        LRESULT lResult = 0;
        lResult = OnWindowMessageDefault(hWnd,msg,wParam,lParam);
        return lResult;
    }
    virtual LRESULT On_WM_MBUTTONDBLCLK_WindowMessage
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        LRESULT lResult = 0;
        lResult = OnWindowMessageDefault(hWnd,msg,wParam,lParam);
        return lResult;
    }
    virtual LRESULT On_WM_XBUTTONDOWN_WindowMessage
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        LRESULT lResult = 0;
        lResult = OnWindowMessageDefault(hWnd,msg,wParam,lParam);
        return lResult;
    }
    virtual LRESULT On_WM_XBUTTONUP_WindowMessage
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        LRESULT lResult = 0;
        lResult = OnWindowMessageDefault(hWnd,msg,wParam,lParam);
        return lResult;
    }
    virtual LRESULT On_WM_XBUTTONDBLCLK_WindowMessage
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        LRESULT lResult = 0;
        lResult = OnWindowMessageDefault(hWnd,msg,wParam,lParam);
        return lResult;
    }
    virtual LRESULT On_WM_MOUSEWHEEL_WindowMessage
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        LRESULT lResult = 0;
        lResult = OnWindowMessageDefault(hWnd,msg,wParam,lParam);
        return lResult;
    }
    virtual LRESULT On_WM_NCMOUSEMOVE_WindowMessage
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        LRESULT lResult = 0;
        lResult = OnWindowMessageDefault(hWnd,msg,wParam,lParam);
        return lResult;
    }
    virtual LRESULT On_WM_NCMOUSEHOVER_WindowMessage
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        LRESULT lResult = 0;
        lResult = OnWindowMessageDefault(hWnd,msg,wParam,lParam);
        return lResult;
    }
    virtual LRESULT On_WM_NCMOUSELEAVE_WindowMessage
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        LRESULT lResult = 0;
        lResult = OnWindowMessageDefault(hWnd,msg,wParam,lParam);
        return lResult;
    }
    virtual LRESULT On_WM_NCLBUTTONDOWN_WindowMessage
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        LRESULT lResult = 0;
        lResult = OnWindowMessageDefault(hWnd,msg,wParam,lParam);
        return lResult;
    }
    virtual LRESULT On_WM_NCLBUTTONUP_WindowMessage
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        LRESULT lResult = 0;
        lResult = OnWindowMessageDefault(hWnd,msg,wParam,lParam);
        return lResult;
    }
    virtual LRESULT On_WM_NCLBUTTONDBLCLK_WindowMessage
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        LRESULT lResult = 0;
        lResult = OnWindowMessageDefault(hWnd,msg,wParam,lParam);
        return lResult;
    }
    virtual LRESULT On_WM_NCRBUTTONDOWN_WindowMessage
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        LRESULT lResult = 0;
        lResult = OnWindowMessageDefault(hWnd,msg,wParam,lParam);
        return lResult;
    }
    virtual LRESULT On_WM_NCRBUTTONUP_WindowMessage
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        LRESULT lResult = 0;
        lResult = OnWindowMessageDefault(hWnd,msg,wParam,lParam);
        return lResult;
    }
    virtual LRESULT On_WM_NCRBUTTONDBLCLK_WindowMessage
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        LRESULT lResult = 0;
        lResult = OnWindowMessageDefault(hWnd,msg,wParam,lParam);
        return lResult;
    }
    virtual LRESULT On_WM_NCMBUTTONDOWN_WindowMessage
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        LRESULT lResult = 0;
        lResult = OnWindowMessageDefault(hWnd,msg,wParam,lParam);
        return lResult;
    }
    virtual LRESULT On_WM_NCMBUTTONUP_WindowMessage
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        LRESULT lResult = 0;
        lResult = OnWindowMessageDefault(hWnd,msg,wParam,lParam);
        return lResult;
    }
    virtual LRESULT On_WM_NCMBUTTONDBLCLK_WindowMessage
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        LRESULT lResult = 0;
        lResult = OnWindowMessageDefault(hWnd,msg,wParam,lParam);
        return lResult;
    }
    virtual LRESULT On_WM_NCXBUTTONDOWN_WindowMessage
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        LRESULT lResult = 0;
        lResult = OnWindowMessageDefault(hWnd,msg,wParam,lParam);
        return lResult;
    }
    virtual LRESULT On_WM_NCXBUTTONUP_WindowMessage
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        LRESULT lResult = 0;
        lResult = OnWindowMessageDefault(hWnd,msg,wParam,lParam);
        return lResult;
    }
    virtual LRESULT On_WM_NCXBUTTONDBLCLK_WindowMessage
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        LRESULT lResult = 0;
        lResult = OnWindowMessageDefault(hWnd,msg,wParam,lParam);
        return lResult;
    }
    virtual LRESULT On_WM_USER_WindowMessage
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        LRESULT lResult = 0;
        lResult = OnWindowMessageDefault(hWnd,msg,wParam,lParam);
        return lResult;
    }

    virtual LRESULT OnWindowMessageDefault
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        LRESULT lResult = 0;
        lResult = DefWindowProc(hWnd,msg,wParam,lParam);
        return lResult;
    }

    virtual LRESULT DefWindowProc
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        LRESULT lResult = 0;
        lResult = ::DefWindowProc(hWnd,msg,wParam,lParam);
        return lResult;
    }

#if defined(XOS_GUI_WINDOWS_WINDOWMESSAGEMEMBERS_CLASS)
};
} // namespace windows 
} // namespace xos 
#endif // defined(XOS_GUI_WINDOWS_WINDOWMESSAGEMEMBERS_CLASS) 
