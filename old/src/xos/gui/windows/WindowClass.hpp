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
///   File: WindowClass.hpp
///
/// Author: $author$
///   Date: 1/11/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_WINDOWS_WINDOWCLASS_HPP
#define _XOS_GUI_WINDOWS_WINDOWCLASS_HPP

#include "xos/gui/windows/Window.hpp"
#include "xos/gui/windows/Atom.hpp"
#include "xos/base/String.hpp"
#include "xos/os/Logger.hpp"

#define XOS_GUI_WINDOWS_WINDOWCLASS_CLASSNAME_CHARS "xos::windows::WindowClass"

namespace xos {
namespace windows {

typedef InterfaceBase WindowClassImplement;
typedef ATOMRegistered WindowClassExtend;
///////////////////////////////////////////////////////////////////////
///  Class: WindowClass
///
/// Author: $author$
///   Date: 1/11/2013
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS WindowClass
: virtual public WindowClassImplement,
  public WindowClassExtend {
public:
    typedef WindowClassImplement Implements;
    typedef WindowClassExtend Extends;

    WindowClass
    (LPCTSTR windowClassNameChars=_T(XOS_GUI_WINDOWS_WINDOWCLASS_CLASSNAME_CHARS),
     WNDPROC wndProc=Window::WindowProc,
     int windowExtra=(int)(sizeof(Window*)),
     int windowExtraOffset=0,
     int classExtra=0,
     int classExtraOffset=0,
     UINT style=0,
     ATOM detached=0, bool isRegistered=false)
    : Extends(detached, isRegistered),
      m_windowClassName(windowClassNameChars),
      m_windowClassNameChars(m_windowClassName.Chars()),
      m_wndProc(wndProc),
      m_hBackgroundBrush(0),
      m_hCursor(0),
      m_windowExtra(windowExtra),
      m_windowExtraOffset(windowExtraOffset),
      m_classExtra(classExtra),
      m_classExtraOffset(classExtraOffset),
      m_style(style) {
    }
    virtual ~WindowClass() {
    }

    virtual bool Register
    (HINSTANCE instance, LPCTSTR classname=NULL, WNDPROC wndproc=NULL,
     LPCTSTR menuname=NULL, HICON icon=NULL, HICON iconsm=NULL,
     HCURSOR cursor=NULL, HBRUSH background=NULL, UINT style=0,
     int wndextra=-1, int clsextra=-1) {
        bool isSuccess = false;
        ATOM detached;

        if (!(Unregistered())) {
            XOS_LOG_ERROR("failed on Unregistered()");
            return false;
        }

        if (classname)
            SetWindowClassName(classname);
        else
        if (!(classname = GetWindowClassName()))
            return false;

        if (!wndproc)
        if (!(wndproc = GetWindowProc()))
            return false;

        if (!background)
            background = GetBackground();

        if (0 > wndextra)
            wndextra = GetWindowExtra();

        if (0 > clsextra)
            clsextra = GetClassExtra();

        if (!style)
            style = GetStyle();

        if ((isSuccess = (NULL != (detached = RegisterDetached
            (m_wndClass, instance, classname, wndproc, menuname, icon, 
             iconsm, cursor, background, style, wndextra, clsextra)))))
             AttachRegistered(detached);

        return isSuccess;
    }
    virtual bool Unregister() {
        bool isSuccess = false;
        ATOM detached;
        if ((detached = Detach()))
            isSuccess = UnregisterDetached(detached, m_wndClass);
        return isSuccess;
    }
    virtual ATOM RegisterDetached
    (WNDCLASSEX& wndClass, 
     HINSTANCE instance, LPCTSTR classname, WNDPROC wndproc=NULL,
     LPCTSTR menuname=NULL, HICON icon=NULL, HICON iconsm=NULL,
     HCURSOR cursor=NULL, HBRUSH background=NULL, UINT style=0,
     int wndextra=0, int clsextra=0, bool isInitial=false)
    {
        ATOM detached = NULL;

        memset(&wndClass, 0, sizeof(WNDCLASSEX));
        wndClass.cbSize = sizeof(WNDCLASSEX);
        wndClass.hInstance = instance;
        wndClass.lpszClassName = classname;
        wndClass.style = style;
        wndClass.cbClsExtra = clsextra;
        wndClass.cbWndExtra = wndextra;

        if ((NULL != menuname) || isInitial)
            wndClass.lpszMenuName = menuname;

        if ((NULL != icon) || isInitial)
            wndClass.hIcon = icon;

        if ((NULL != iconsm) || isInitial)
            wndClass.hIconSm = iconsm;

        if ((NULL != cursor) || isInitial)
            wndClass.hCursor = cursor;

        else if (NULL == wndClass.hCursor)
                wndClass.hCursor = GetDefaultCursor();

        if ((NULL != background) || isInitial)
            wndClass.hbrBackground = background;

        else if (NULL == wndClass.hbrBackground)
                wndClass.hbrBackground = GetDefaultBackground();

        if ((NULL != wndproc) || isInitial)
            wndClass.lpfnWndProc = wndproc;

        else if (NULL == wndClass.lpfnWndProc)
                wndClass.lpfnWndProc = GetDefaultWindowProc();

        if (!(NULL != (detached = RegisterClassEx(&wndClass))))
            XOS_LOG_ERROR("failed on RegisterClassEx()");

        return detached;
    }
    virtual bool UnregisterDetached
    (ATOM detached, const WNDCLASSEX& wndClass)
    {
        bool isSuccess = false;
        if ((detached))
        if (!(isSuccess = (TRUE != (UnregisterClass
            (wndClass.lpszClassName, wndClass.hInstance)))))
            XOS_LOG_ERROR("failed on UnregisterClass()");
        return isSuccess;
    }

    virtual ssize_t SetWindowClassName(LPCTSTR chars, TLENGTH length=-1) {
        ssize_t count = 0;
        m_windowClassName.assign(chars, length);
        if (0 < (count = m_windowClassName.length()))
        if ((chars = m_windowClassName.c_str()))
            m_windowClassNameChars = chars;
        return count;
    }
    virtual LPCTSTR GetWindowClassName() const {
        LPCTSTR chars = m_windowClassNameChars;
        return chars;
    }

    virtual WNDPROC SetWindowProc(WNDPROC wndProc) {
        m_wndProc = wndProc;
        return wndProc;
    }
    virtual WNDPROC GetWindowProc() const {
        WNDPROC wndProc = m_wndProc;
        return wndProc;
    }
    virtual WNDPROC GetDefaultWindowProc() const 
    {
        WNDPROC wndproc = DefWindowProc;
        return wndproc;
    }

    virtual int SetWindowExtra(int bytes) {
        int count = (m_windowExtra = bytes);
        return count;
    }
    virtual int GetWindowExtra() const {
        int count = m_windowExtra;
        return count;
    }

    virtual int SetWindowExtraOffset
    (int bytes) 
    {
        int count = 0;
        return count;
    }
    virtual int GetWindowExtraOffset() const 
    {
        int count = m_windowExtraOffset;
        return count;
    }

    virtual int SetClassExtra
    (int bytes) 
    {
        int count = (m_classExtra = bytes);
        return count;
    }
    virtual int GetClassExtra() const 
    {
        int count = m_classExtra;
        return count;
    }

    virtual int SetClassExtraOffset
    (int bytes) 
    {
        int count = 0;
        return count;
    }
    virtual int GetClassExtraOffset() const 
    {
        int count = m_classExtraOffset;
        return count;
    }

    virtual HBRUSH SetBackground(HBRUSH hBrush) 
    {
        m_hBackgroundBrush = hBrush;
        return hBrush;
    }
    virtual HBRUSH GetBackground() const 
    {
        HBRUSH hBrush = NULL;
        hBrush = m_hBackgroundBrush;
        return hBrush;
    }
    virtual HBRUSH GetDefaultBackground() const 
    {
        HBRUSH handle = (HBRUSH)GetStockObject(WHITE_BRUSH);
        return handle;
    }

    virtual HCURSOR SetCursor(HCURSOR hCursor) 
    {
        HCURSOR handle = (m_hCursor = hCursor);
        return handle;
    }
    virtual HCURSOR GetCursor() const 
    {
        HCURSOR handle = m_hCursor;
        return handle;
    }
    virtual HCURSOR GetDefaultCursor() const 
    {
        HCURSOR handle = LoadCursor(NULL, IDC_ARROW);
        return handle;
    }

    virtual UINT SetStyle
    (UINT toStyle) 
    {
        UINT style = 0;
        style = (m_style = toStyle);
        return style;
    }
    virtual UINT GetStyle() const 
    {
        UINT style = 0;
        style = (m_style);
        return style;
    }

    static LPCTSTR DefaultWindowClassNameChars() {
        static LPCTSTR chars = _T(XOS_GUI_WINDOWS_WINDOWCLASS_CLASSNAME_CHARS);
        return chars;
    }

protected:
    TString m_windowClassName;
    LPCTSTR m_windowClassNameChars;
    WNDPROC m_wndProc;
    HBRUSH m_hBackgroundBrush;
    HCURSOR m_hCursor;
    int m_windowExtra;
    int m_windowExtraOffset;
    int m_classExtra;
    int m_classExtraOffset;
    UINT m_style;
    WNDCLASSEX m_wndClass;
};


} // namespace windows 
} // namespace xos 


#endif // _XOS_GUI_WINDOWS_WINDOWCLASS_HPP 
        

