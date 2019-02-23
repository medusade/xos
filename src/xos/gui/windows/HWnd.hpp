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
///   File: HWnd.hpp
///
/// Author: $author$
///   Date: 1/11/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_WINDOWS_HWND_HPP
#define _XOS_GUI_WINDOWS_HWND_HPP

#include "xos/base/Created.hpp"
#include "xos/base/Attached.hpp"

namespace xos {
namespace windows {

typedef AttachedImplement
<HWND, int, 0, InterfaceBase> HWNDAttachedImplement;

typedef Attached
<HWND, int, 0, ExportBase, HWNDAttachedImplement> HWNDAttached;

typedef Created
<HWND, int, 0, HWNDAttached, HWNDAttachedImplement> HWNDCreated;

///////////////////////////////////////////////////////////////////////
///  Class: HWndImplement
///
/// Author: $author$
///   Date: 1/16/2013
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS HWndImplement: virtual public HWNDAttachedImplement {
public:
    virtual HINSTANCE AttachHInstance(HINSTANCE hInstance) {
        return 0;
    }
    virtual HINSTANCE DetachHInstance() {
        return 0;
    }
    virtual HINSTANCE AttachedToHInstance() const {
        return 0;
    }
};
typedef HWNDCreated HWndExtend;
///////////////////////////////////////////////////////////////////////
///  Class: HWnd
///
/// Author: $author$
///   Date: 1/16/2013
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS HWnd: virtual public HWndImplement, public HWndExtend {
public:
    typedef HWndExtend Extends;
    using Extends::AttachCreated;
    using Extends::Attach;

    HWnd(HINSTANCE hInstance=0, HWND detached=0, bool isCreated=false)
    : Extends(detached, isCreated),
      m_hInstance(hInstance) {
    }

    virtual HWND AttachCreated(HINSTANCE hInstance, HWND detached, bool isCreated=true) {
        m_hInstance = hInstance;
        return AttachCreated(detached, isCreated);
    }
    virtual HWND Attach(HINSTANCE hInstance, HWND detached, bool isCreated=false) {
        m_hInstance = hInstance;
        return AttachCreated(detached, isCreated);
    }
    virtual HWND Detach(HINSTANCE& hInstance, bool& isCreated) {
        HWND detached = 0;
        hInstance = m_hInstance;
        m_hInstance = 0;
        detached = Extends::Detach(isCreated);
        return detached;
    }
    virtual HWND Detach(bool& isCreated) {
        HWND detached = 0;
        m_hInstance = 0;
        detached = Extends::Detach(isCreated);
        return detached;
    }
    virtual HWND Detach() {
        HWND detached = 0;
        m_hInstance = 0;
        detached = Extends::Detach();
        return detached;
    }

    virtual HINSTANCE AttachHInstance(HINSTANCE hInstance) {
        m_hInstance = hInstance;
        return m_hInstance;
    }
    virtual HINSTANCE DetachHInstance() {
        HINSTANCE hInstance = m_hInstance;
        m_hInstance = 0;
        return hInstance;
    }
    virtual HINSTANCE AttachedToHInstance() const {
        return m_hInstance;
    }

protected:
    HINSTANCE m_hInstance;
};

} // namespace windows 
} // namespace xos 

#endif // _XOS_GUI_WINDOWS_HWND_HPP 
