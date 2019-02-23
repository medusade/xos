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
///   File: Widget.hpp
///
/// Author: $author$
///   Date: 4/2/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_X11_XT_WIDGET_HPP
#define _XOS_GUI_X11_XT_WIDGET_HPP

#include "xos/gui/x11/xt/WidgetClass.hpp"
#include "xos/gui/x11/xt/Callback.hpp"
#include "xos/gui/x11/xt/ArgList.hpp"
#include "xos/gui/x11/Attached.hpp"
#include "xos/gui/x11/Created.hpp"

#define XOS_GUI_X11_XT_WIDGET_CLASS 0
#define XOS_GUI_X11_XT_WIDGET_NAME "xos::x11::xt::Widget"
#define XOS_GUI_X11_XT_WIDGET_CLASS_NAME XOS_GUI_X11_XT_WIDGET_NAME

namespace xos {
namespace x11 {
namespace xt {

///////////////////////////////////////////////////////////////////////
///  Class: WidgetInterface
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS WidgetInterface
: virtual public CallbackInterface {
public:
};
typedef WidgetInterface WidgetImplement;
typedef Attached<XtWidget, int, 0> WidgetAttached;
typedef xos::Created<XtWidget, int, 0, WidgetAttached> WidgetCreated;
typedef Created<XtWidget, int, 0, WidgetCreated> WidgetExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Widget
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Widget
: virtual public WidgetImplement, public WidgetExtend {
public:
    typedef WidgetImplement Implements;
    typedef WidgetExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: Widget
    ///////////////////////////////////////////////////////////////////////
    Widget
    (XDisplay* xDisplay = 0, XtWidget xtWidget = 0, 
     XtWidgetClass xtWidgetClass = 0, 
     const XtChar* widgetName = XOS_GUI_X11_XT_WIDGET_NAME, 
     bool isCreated = false)
    : Extends(xDisplay, xtWidget, isCreated), 
      m_widgetClass(xtWidgetClass), 
      m_widgetName(widgetName) {
    }
    virtual ~Widget() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Create
    (XDisplay* display, const XtChar* widgetName, 
     XtWidget widgetParent, XtWidgetClass widgetClass,
     XtArgList argList = 0, XtCardinal argCount = 0, bool isManaged = false) {
         XtWidget detached;
         if ((detached = CreateAttached
             (display, widgetName, widgetParent, 
              widgetClass, argList, argCount, isManaged))) {
             return true;
         }
         return false;
    }
    virtual bool Destroy() {
        bool isSuccess = false;
        bool isCreated = false;
        XDisplay* display = 0;
        XtWidget detached;
        if ((detached = Detach(display, isCreated))) {
            isSuccess = DestroyDetached(detached);
        }
        m_widgetClass.Detach();
        m_widgetName.Clear();
        return isSuccess;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual XtWidget CreateAttached
    (XDisplay* display, XtWidget& widgetParent, 
     XtArgList argList = 0, XtCardinal argCount = 0, bool isManaged = false) {
        const XtChar* widgetName = 0; 
        XtWidgetClass widgetClass = 0;
        XtWidget detached = CreateAttached
        (display, widgetName, widgetParent, widgetClass, argList, argCount, isManaged);
        return detached;
    }
    virtual XtWidget CreateAttached
    (XDisplay* display, const XtChar*& widgetName, XtWidget& widgetParent, 
     XtArgList argList = 0, XtCardinal argCount = 0, bool isManaged = false) {
        XtWidgetClass widgetClass = 0;
        XtWidget detached = CreateAttached
        (display, widgetName, widgetParent, widgetClass, argList, argCount, isManaged);
        return detached;
    }
    virtual XtWidget CreateAttached
    (XDisplay* display, const XtChar*& widgetName, 
     XtWidget& widgetParent, XtWidgetClass& widgetClass,
     XtArgList argList = 0, XtCardinal argCount = 0, bool isManaged = false) {
        XtWidget detached = 0;
        if ((Destroyed())) {
            if ((detached = CreateDetached
                (widgetName, widgetParent, widgetClass, argList, argCount, isManaged))) {
                AttachWidgetName(widgetName);
                AttachWidgetClass(widgetClass);
                AttachCreated(display, detached);
            }
        }
        return detached;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual XtWidget CreateDetached
    (const XtChar*& widgetName, XtWidget& widgetParent, XtWidgetClass& widgetClass,
     XtArgList argList = 0, XtCardinal argCount = 0, bool isManaged = false) {
        XtWidget detached = 0;

        if (!(widgetName))
            widgetName = DetachedWidgetName();

        if (!(widgetClass))
            widgetClass = DetachedWidgetClass();

        if ((widgetName) && (widgetClass)) {
            if ((detached = XtCreateWidget
                (widgetName, widgetClass, widgetParent, argList, argCount))) {
                if ((isManaged))
                    XtManageChild(detached);
            } else {
                XOS_LOG_ERROR("failed on XtCreateWidget()");
            }
        }
        return detached;
    }
    virtual bool DestroyDetached(XtWidget detached) {
        bool isSuccess = false;
        if ((detached)) {
            XtDestroyWidget(detached);
            isSuccess = true;
        }
        return isSuccess;
    }
    virtual XtWidgetClass AttachWidgetClass(XtWidgetClass xtWidgetClass) {
        if ((xtWidgetClass) && (xtWidgetClass != m_widgetClass.AttachedTo()))
            m_widgetClass.Attach(xtWidgetClass);
        return xtWidgetClass;
    }
    virtual const XtChar* AttachWidgetName(const XtChar* xtWidgetName) {
        if ((xtWidgetName) && (xtWidgetName != m_widgetName.Chars()))
            m_widgetName.Assign(xtWidgetName);
        return xtWidgetName;
    }
    virtual XtWidgetClass DetachedWidgetClass() const {
        return m_widgetClass.AttachedTo();
    }
    virtual const XtChar* DetachedWidgetName() const {
        return m_widgetName.Chars();
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool ManageChild() {
        XtWidget detached;
        if ((detached = AttachedTo())) {
            XtManageChild(detached);
            return true;
        }
        return false;
    }
    virtual bool UnmanageChild() {
        XtWidget detached;
        if ((detached = AttachedTo())) {
            XtUnmanageChild(detached);
            return true;
        }
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool AddCallback
    (const XtString callbackName, CallbackInterface* callback) {
        return AddCallback(callbackName, (XtPointer)(callback));
    }
    virtual bool AddCallback
    (const XtString callbackName, XtPointer callbackData = 0) {
        return AddCallback(callbackName, XtCallback, callbackData);
    }
    virtual bool AddCallback
    (const XtString callbackName, XtCallbackProc callbackProc, XtPointer callbackData = 0) {
        XtWidget attached = 0;
        if ((callbackName) && (callbackProc) && (attached = AttachedTo())) {
            XtAddCallback(attached, callbackName, callbackProc, callbackData);
            return true;
        }
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual size_t SetValuesL
    (const XtChar* argName, XtArgVal argValue, ...) {
        size_t count = 0;
        va_list va;
        va_start(va, argValue);
        count = SetValuesV(argName, argValue, va);
        va_end(va);
        return count;
    }
    virtual size_t SetValuesV
    (const XtChar* argName, XtArgVal argValue, va_list va) {
        size_t count = 0;
        XtArgList argList;
        if ((argList = m_argList.SetV(argName, argValue, va)))
            count = SetValues(argList, m_argList.Length());
        return count;
    }
    virtual size_t SetValues
    (XtArgList argList, size_t length) {
        size_t count = 0;
        XtWidget xtWidget;
        if ((argList) && (0 < length) && (xtWidget = AttachedTo()))
            XtSetValues(xtWidget, argList, count = length);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual size_t GetValuesL
    (const XtChar* argName, XtArgVal* argValue, ...) {
        size_t count = 0;
        return count;
    }
    virtual size_t GetValuesV
    (const XtChar* argName, XtArgVal* argValue, va_list va) {
        size_t count = 0;
        return count;
    }
    virtual size_t GetValues
    (XtArgList argList, size_t length) {
        size_t count = 0;
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    WidgetClass m_widgetClass;
    String m_widgetName;
    ArgList m_argList;
};

} // namespace xt 
} // namespace x11 
} // namespace xos 

#endif // _XOS_GUI_X11_XT_WIDGET_HPP 
