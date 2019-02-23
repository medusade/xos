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
///   File: WindowMessageTarget.hpp
///
/// Author: $author$
///   Date: 1/10/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_WINDOWS_WINDOWMESSAGETARGET_HPP
#define _XOS_GUI_WINDOWS_WINDOWMESSAGETARGET_HPP

#include "xos/gui/windows/HWnd.hpp"

namespace xos {
namespace windows {

///////////////////////////////////////////////////////////////////////
///  Class: WindowMessageTargetImplement
///
/// Author: $author$
///   Date: 1/10/2013
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS WindowMessageTargetImplement
: virtual public HWndImplement {
public:
    typedef HWndImplement Implements;

#include "xos/gui/windows/WindowMessageMembers.hpp"
    virtual LRESULT OnWindowMessage
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        LRESULT lResult = 0;
        switch(msg) {
#include "xos/gui/windows/WindowMessageCases.hpp"
        }
        return lResult;
    }
    static LRESULT CALLBACK WindowProc
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        LRESULT lResult = 0;
		WindowMessageTargetImplement* window;

		if (!(window = (WindowMessageTargetImplement*)(GetWindowLongPtr(hWnd, GWL_USERDATA))))
		if ((WM_NCCREATE == (msg)))
		{
			CREATESTRUCT* cs;
			if ((cs = (CREATESTRUCT*)(lParam)))
			if ((window = (WindowMessageTargetImplement*)(cs->lpCreateParams)))
            {
                if (!(window->AttachedTo())) window->Attach(hWnd);
                if (!(window->AttachedToHInstance())) window->AttachHInstance(cs->hInstance);
				SetWindowLongPtr(hWnd, GWL_USERDATA, (LONG_PTR)(window));
            }
		}

		if ((window))
			lResult = window->OnWindowMessage(hWnd, msg, wParam, lParam);
		else
		lResult = ::DefWindowProc(hWnd, msg, wParam, lParam);
        return lResult;
    }
};

} // namespace windows 
} // namespace xos 

#endif // _XOS_GUI_WINDOWS_WINDOWMESSAGETARGET_HPP 
