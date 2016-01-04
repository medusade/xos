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
///   File: Main.hpp
///
/// Author: $author$
///   Date: 7/5/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_X11_XT_OPENGL_HELLO_MAIN_HPP
#define _XOS_GUI_X11_XT_OPENGL_HELLO_MAIN_HPP

#include "app/gui/x11/opengl/hello/Main.hpp"

#define XOS_GUI_X11_XT_OPENGL_HELLO_MAIN_APP_NAME "xos::gui::x11::xt::opengl::Hello"
#define XOS_GUI_X11_XT_OPENGL_HELLO_MAIN_APP_CLASS_NAME \
    XOS_GUI_X11_XT_OPENGL_HELLO_MAIN_APP_NAME

namespace xos {
namespace x11 {
namespace xt {
namespace opengl {
namespace hello {

///////////////////////////////////////////////////////////////////////
///  Class: MainT
///////////////////////////////////////////////////////////////////////
template
<class TImplement, class TExtend>

class _EXPORT_CLASS MainT
: virtual public TImplement,
  public x11::opengl::hello::MainT<TImplement, TExtend> {
public:
    typedef TImplement Implements;
    typedef x11::opengl::hello::MainT<TImplement, TExtend> Extends;
    typedef MainT Derives;

    typedef bool (Derives::*MOnHandleXtEvent)
    (XtWidget xtWidget, XtPointer xtPointer, 
     XEvent& xEvent, Boolean& continueToDispatch);

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: MainT
    ///////////////////////////////////////////////////////////////////////
    MainT
    (const XtChar* appName = XOS_GUI_X11_XT_OPENGL_HELLO_MAIN_APP_NAME,
     const XtChar* appClassName = XOS_GUI_X11_XT_OPENGL_HELLO_MAIN_APP_CLASS_NAME)
    : m_onButtonRelease(0)
    {
        this->m_appName = appName;
        this->m_appClassName = appClassName;
    }
    virtual ~MainT() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void OnXtCallback
    (XtWidget xtWidget, XtPointer clientData, XtPointer callData) {
        Widget& formWidget = FormWidget();
        XOS_LOG_INFO("...");
        formWidget.UnmanageChild();
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool OnHandle_RenderRaw_ButtonRelease_XtEvent
    (XtWidget xtWidget, XtPointer xtPointer, XEvent& xEvent, Boolean& continueToDispatch) {
        bool isHandled = false;
        this->m_render = &Derives::Render;
        m_onButtonRelease = &Derives::OnHandle_Render_ButtonRelease_XtEvent;
        this->m_window.Invalidate();
        return isHandled;
    }
    virtual bool OnHandle_Render_ButtonRelease_XtEvent
    (XtWidget xtWidget, XtPointer xtPointer, XEvent& xEvent, Boolean& continueToDispatch) {
        bool isHandled = false;
        this->m_render = &Derives::RenderIn;
        m_onButtonRelease = &Derives::OnHandle_RenderIn_ButtonRelease_XtEvent;
        this->m_window.Invalidate();
        return isHandled;
    }
    virtual bool OnHandle_RenderIn_ButtonRelease_XtEvent
    (XtWidget xtWidget, XtPointer xtPointer, XEvent& xEvent, Boolean& continueToDispatch) {
        Widget& formWidget = FormWidget();
        bool isHandled = false;
        this->m_render = &Derives::RenderRaw;
        m_onButtonRelease = &Derives::OnHandle_RenderRaw_ButtonRelease_XtEvent;
        formWidget.ManageChild();
        return isHandled;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool OnHandle_ButtonRelease_XtEvent
    (XtWidget xtWidget, XtPointer xtPointer, XEvent& xEvent, Boolean& continueToDispatch) {
        bool isHandled = false;
        if ((m_onButtonRelease))
            (this->*m_onButtonRelease)
            (xtWidget, xtPointer, xEvent, continueToDispatch);
        else
        OnHandle_RenderRaw_ButtonRelease_XtEvent
        (xtWidget, xtPointer, xEvent, continueToDispatch);
        return isHandled;
    }
    virtual bool OnHandle_Expose_XtEvent
    (XtWidget xtWidget, XtPointer xtPointer, XEvent& xEvent, Boolean& continueToDispatch) {
        bool isHandled = false;
        if ((this->m_window.AttachedTo()))
        if ((this->m_render))
            (this->*(this->m_render))();
        else
        this->RenderRaw();
        return isHandled;
    }
    virtual bool OnHandle_UnmapNotify_XtEvent
    (XtWidget xtWidget, XtPointer xtPointer, XEvent& xEvent, Boolean& continueToDispatch) {
        bool isHandled = false;
        if ((this->m_window.AttachedTo()))
            this->m_glRenderer.Finish();
        this->m_window.Detach();
        return isHandled;
    }
    virtual bool OnHandle_MapNotify_XtEvent
    (XtWidget xtWidget, XtPointer xtPointer, XEvent& xEvent, Boolean& continueToDispatch) {
        bool isHandled = false;
        if ((this->m_window.Attach(this->m_display.AttachedTo(), XtWindow(xtWidget)))) {
            if ((this->m_glRenderer.Init(this->m_display.AttachedTo(), XtWindow(xtWidget)))) {
                if ((this->m_glRenderer.Prepare()))
                    return isHandled;
            }
            this->m_window.Detach();
        }
        return isHandled;
    }
    virtual bool OnHandle_ConfigureNotify_XtEvent
    (XtWidget xtWidget, XtPointer xtPointer, XEvent& xEvent, Boolean& continueToDispatch) {
        bool isHandled = false;
        if ((this->m_window.AttachedTo()))
            this->m_glRenderer.Reshape
            (xEvent.xconfigure.width, xEvent.xconfigure.height);
        this->m_window.Invalidate();
        return isHandled;
    }
    virtual bool OnHandle_ClientMessage_XtEvent
    (XtWidget xtWidget, XtPointer xtPointer, XEvent& xEvent, Boolean& continueToDispatch) {
        Widget& shellWidget = ShellWidget();
        bool isHandled = false;
        if (xEvent.xclient.message_type == this->m_atomWmProtocols.AttachedTo())
        if (xEvent.xclient.data.l[0] == this->m_atomWmDeleteWindow.AttachedTo())
        if (xtWidget == shellWidget.AttachedTo()) {
            isHandled = OnHandle_ClientMessage_WM_DELETE_WINDOW_XtEvent
            (xtWidget, xtPointer, xEvent, continueToDispatch);
        }
        return isHandled;
    }
    virtual bool OnHandle_ClientMessage_WM_DELETE_WINDOW_XtEvent
    (XtWidget xtWidget, XtPointer xtPointer, XEvent& xEvent, Boolean& continueToDispatch) {
        bool isHandled = false;
        XOS_LOG_INFO("WM_DELETE_WINDOW...");
        this->SetDoneProcessingXEvents();
        if ((this->m_window.AttachedTo()))
            this->m_glRenderer.Finish();
        this->m_window.Detach();
        return isHandled;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual xt::Widget& ShellWidget() const = 0;
    virtual xt::Widget& FormWidget() const = 0;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    MOnHandleXtEvent m_onButtonRelease;
};

} // namespace hello 
} // namespace opengl 
} // namespace xt 
} // namespace x11 
} // namespace xos 

#endif // _XOS_GUI_X11_XT_OPENGL_HELLO_MAIN_HPP 
