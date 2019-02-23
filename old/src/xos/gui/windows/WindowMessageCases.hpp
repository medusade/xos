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
///   File: WindowMessageCases.hpp
///
/// Author: $author$
///   Date: 1/10/2013
///////////////////////////////////////////////////////////////////////
#if defined(XOS_GUI_WINDOWS_WINDOWMESSAGECASES_MEMBER_CASES_SWITCH)
        switch(msg)
        {
#endif // defined(XOS_GUI_WINDOWS_WINDOWMESSAGECASES_MEMBER_CASES_SWITCH) 

           case WM_NCCREATE:
                lResult = On_WM_NCCREATE_WindowMessage
                (hWnd, msg, wParam, lParam);
                break;

           case WM_NCDESTROY:
                lResult = On_WM_NCDESTROY_WindowMessage
                (hWnd, msg, wParam, lParam);
                break;

           case WM_CREATE:
                lResult = On_WM_CREATE_WindowMessage
                (hWnd, msg, wParam, lParam);
                break;

           case WM_DESTROY:
                lResult = On_WM_DESTROY_WindowMessage
                (hWnd, msg, wParam, lParam);
                break;

           case WM_PAINT:
                lResult = On_WM_PAINT_WindowMessage
                (hWnd, msg, wParam, lParam);
                break;

           case WM_PAINTICON:
                lResult = On_WM_PAINTICON_WindowMessage
                (hWnd, msg, wParam, lParam);
                break;

           case WM_ERASEBKGND:
                lResult = On_WM_ERASEBKGND_WindowMessage
                (hWnd, msg, wParam, lParam);
                break;

           case WM_ICONERASEBKGND:
                lResult = On_WM_ICONERASEBKGND_WindowMessage
                (hWnd, msg, wParam, lParam);
                break;

           case WM_SHOWWINDOW:
                lResult = On_WM_SHOWWINDOW_WindowMessage
                (hWnd, msg, wParam, lParam);
                break;

           case WM_CLOSE:
                lResult = On_WM_CLOSE_WindowMessage
                (hWnd, msg, wParam, lParam);
                break;

           case WM_MOVE:
                lResult = On_WM_MOVE_WindowMessage
                (hWnd, msg, wParam, lParam);
                break;

           case WM_SIZE:
                lResult = On_WM_SIZE_WindowMessage
                (hWnd, msg, wParam, lParam);
                break;

           case WM_ACTIVATE:
                lResult = On_WM_ACTIVATE_WindowMessage
                (hWnd, msg, wParam, lParam);
                break;

           case WM_ENABLE:
                lResult = On_WM_ENABLE_WindowMessage
                (hWnd, msg, wParam, lParam);
                break;

           case WM_SETFOCUS:
                lResult = On_WM_SETFOCUS_WindowMessage
                (hWnd, msg, wParam, lParam);
                break;

           case WM_KILLFOCUS:
                lResult = On_WM_KILLFOCUS_WindowMessage
                (hWnd, msg, wParam, lParam);
                break;

           case WM_QUERYOPEN:
                lResult = On_WM_QUERYOPEN_WindowMessage
                (hWnd, msg, wParam, lParam);
                break;

           case WM_COMMAND:
                lResult = On_WM_COMMAND_WindowMessage
                (hWnd, msg, wParam, lParam);
                break;

           case WM_QUIT:
                lResult = On_WM_QUIT_WindowMessage
                (hWnd, msg, wParam, lParam);
                break;

           case WM_NOTIFY:
                lResult = On_WM_NOTIFY_WindowMessage
                (hWnd, msg, wParam, lParam);
                break;

           case WM_PARENTNOTIFY:
                lResult = On_WM_PARENTNOTIFY_WindowMessage
                (hWnd, msg, wParam, lParam);
                break;

           case WM_DROPFILES:
                lResult = On_WM_DROPFILES_WindowMessage
                (hWnd, msg, wParam, lParam);
                break;

           case WM_QUERYDRAGICON:
                lResult = On_WM_QUERYDRAGICON_WindowMessage
                (hWnd, msg, wParam, lParam);
                break;

           case WM_NCPAINT:
                lResult = On_WM_NCPAINT_WindowMessage
                (hWnd, msg, wParam, lParam);
                break;

           case WM_NCACTIVATE:
                lResult = On_WM_NCACTIVATE_WindowMessage
                (hWnd, msg, wParam, lParam);
                break;

           case WM_NCCALCSIZE:
                lResult = On_WM_NCCALCSIZE_WindowMessage
                (hWnd, msg, wParam, lParam);
                break;

           case WM_NCHITTEST:
                lResult = On_WM_NCHITTEST_WindowMessage
                (hWnd, msg, wParam, lParam);
                break;

           case WM_MOUSEMOVE:
                lResult = On_WM_MOUSEMOVE_WindowMessage
                (hWnd, msg, wParam, lParam);
                break;

           case WM_MOUSEHOVER:
                lResult = On_WM_MOUSEHOVER_WindowMessage
                (hWnd, msg, wParam, lParam);
                break;

           case WM_MOUSELEAVE:
                lResult = On_WM_MOUSELEAVE_WindowMessage
                (hWnd, msg, wParam, lParam);
                break;

           case WM_LBUTTONDOWN:
                lResult = On_WM_LBUTTONDOWN_WindowMessage
                (hWnd, msg, wParam, lParam);
                break;

           case WM_LBUTTONUP:
                lResult = On_WM_LBUTTONUP_WindowMessage
                (hWnd, msg, wParam, lParam);
                break;

           case WM_LBUTTONDBLCLK:
                lResult = On_WM_LBUTTONDBLCLK_WindowMessage
                (hWnd, msg, wParam, lParam);
                break;

           case WM_RBUTTONDOWN:
                lResult = On_WM_RBUTTONDOWN_WindowMessage
                (hWnd, msg, wParam, lParam);
                break;

           case WM_RBUTTONUP:
                lResult = On_WM_RBUTTONUP_WindowMessage
                (hWnd, msg, wParam, lParam);
                break;

           case WM_RBUTTONDBLCLK:
                lResult = On_WM_RBUTTONDBLCLK_WindowMessage
                (hWnd, msg, wParam, lParam);
                break;

           case WM_MBUTTONDOWN:
                lResult = On_WM_MBUTTONDOWN_WindowMessage
                (hWnd, msg, wParam, lParam);
                break;

           case WM_MBUTTONUP:
                lResult = On_WM_MBUTTONUP_WindowMessage
                (hWnd, msg, wParam, lParam);
                break;

           case WM_MBUTTONDBLCLK:
                lResult = On_WM_MBUTTONDBLCLK_WindowMessage
                (hWnd, msg, wParam, lParam);
                break;

           case WM_XBUTTONDOWN:
                lResult = On_WM_XBUTTONDOWN_WindowMessage
                (hWnd, msg, wParam, lParam);
                break;

           case WM_XBUTTONUP:
                lResult = On_WM_XBUTTONUP_WindowMessage
                (hWnd, msg, wParam, lParam);
                break;

           case WM_XBUTTONDBLCLK:
                lResult = On_WM_XBUTTONDBLCLK_WindowMessage
                (hWnd, msg, wParam, lParam);
                break;

           case WM_MOUSEWHEEL:
                lResult = On_WM_MOUSEWHEEL_WindowMessage
                (hWnd, msg, wParam, lParam);
                break;

           case WM_NCMOUSEMOVE:
                lResult = On_WM_NCMOUSEMOVE_WindowMessage
                (hWnd, msg, wParam, lParam);
                break;

           case WM_NCMOUSEHOVER:
                lResult = On_WM_NCMOUSEHOVER_WindowMessage
                (hWnd, msg, wParam, lParam);
                break;

           case WM_NCMOUSELEAVE:
                lResult = On_WM_NCMOUSELEAVE_WindowMessage
                (hWnd, msg, wParam, lParam);
                break;

           case WM_NCLBUTTONDOWN:
                lResult = On_WM_NCLBUTTONDOWN_WindowMessage
                (hWnd, msg, wParam, lParam);
                break;

           case WM_NCLBUTTONUP:
                lResult = On_WM_NCLBUTTONUP_WindowMessage
                (hWnd, msg, wParam, lParam);
                break;

           case WM_NCLBUTTONDBLCLK:
                lResult = On_WM_NCLBUTTONDBLCLK_WindowMessage
                (hWnd, msg, wParam, lParam);
                break;

           case WM_NCRBUTTONDOWN:
                lResult = On_WM_NCRBUTTONDOWN_WindowMessage
                (hWnd, msg, wParam, lParam);
                break;

           case WM_NCRBUTTONUP:
                lResult = On_WM_NCRBUTTONUP_WindowMessage
                (hWnd, msg, wParam, lParam);
                break;

           case WM_NCRBUTTONDBLCLK:
                lResult = On_WM_NCRBUTTONDBLCLK_WindowMessage
                (hWnd, msg, wParam, lParam);
                break;

           case WM_NCMBUTTONDOWN:
                lResult = On_WM_NCMBUTTONDOWN_WindowMessage
                (hWnd, msg, wParam, lParam);
                break;

           case WM_NCMBUTTONUP:
                lResult = On_WM_NCMBUTTONUP_WindowMessage
                (hWnd, msg, wParam, lParam);
                break;

           case WM_NCMBUTTONDBLCLK:
                lResult = On_WM_NCMBUTTONDBLCLK_WindowMessage
                (hWnd, msg, wParam, lParam);
                break;

           case WM_NCXBUTTONDOWN:
                lResult = On_WM_NCXBUTTONDOWN_WindowMessage
                (hWnd, msg, wParam, lParam);
                break;

           case WM_NCXBUTTONUP:
                lResult = On_WM_NCXBUTTONUP_WindowMessage
                (hWnd, msg, wParam, lParam);
                break;

           case WM_NCXBUTTONDBLCLK:
                lResult = On_WM_NCXBUTTONDBLCLK_WindowMessage
                (hWnd, msg, wParam, lParam);
                break;

           case WM_USER:
                lResult = On_WM_USER_WindowMessage
                (hWnd, msg, wParam, lParam);
                break;

           default:
                lResult = OnWindowMessageDefault
                (hWnd, msg, wParam, lParam);
                break;

#if defined(XOS_GUI_WINDOWS_WINDOWMESSAGECASES_MEMBER_CASES_SWITCH)
        }
#endif // defined(XOS_GUI_WINDOWS_WINDOWMESSAGECASES_MEMBER_CASES_SWITCH) 
