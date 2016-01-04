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
///   Date: 7/3/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_X11_XM_HELLO_MAIN_HPP
#define _XOS_GUI_X11_XM_HELLO_MAIN_HPP

#include "xos/gui/x11/xm/Main.hpp"
#include "xos/gui/x11/xm/ApplicationShell.hpp"
#include "xos/gui/x11/xm/MainWindow.hpp"
#include "xos/gui/x11/xm/PushButton.hpp"
#include "xos/gui/x11/xm/String.hpp"
#include "app/gui/x11/xt/opengl/hello/Main.hpp"

namespace xos {
namespace x11 {
namespace xm {
namespace hello {

typedef xm::MainImplement MainImplement;
typedef xm::Main MainExtendExtend;
typedef xt::opengl::hello::MainT
<MainImplement, MainExtendExtend> MainExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Main
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Main
: virtual public MainImplement, public MainExtend {
public:
    typedef MainImplement Implements;
    typedef MainExtend Extends;
    typedef Main Derives;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: Main
    ///////////////////////////////////////////////////////////////////////
    Main
    (const XtChar* appName = XOS_GUI_X11_XM_MAIN_APP_NAME,
     const XtChar* appClassName = XOS_GUI_X11_XM_MAIN_APP_CLASS_NAME)
    : Extends(appName, appClassName) {
    }
    virtual ~Main() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int AfterOpenDisplay
    (XDisplay& xDisplay, XScreen& xScreen, int argc, char** argv, char** env) {

        xt::String helloString("Hello");

        ArgList shellArgList
        (XtNtitle,(XtArgVal)(helloString.AttachedTo()), 
         XtNx,0, XtNy,0, XtNwidth,400, XtNheight,100, XtNend);

        ArgList formArgList
        (XtNinput,True, XmNmargin,0, XmNshadowThickness,0,
         XtNx,0, XtNy,0, XtNwidth,400, XtNheight,100, XtNend);

        String helloLabel(helloString.AttachedTo());

        ArgList commandArgList
        (XmNlabelString,(XtArgVal)(helloLabel.AttachedTo()), 
         XtNx,0, XtNy,0, XtNwidth,400, XtNheight,10, XtNend);

        int err = 0;
        XAtom xAtom;
        XtWidget shellWidget;
        XtWidget formWidget;
        XtWidget commandWidget;

        AllocateStandardColors(xDisplay, xScreen, argc, argv, env);

        AttachStandardAtoms(xDisplay, xScreen, argc, argv, env);

        if ((xAtom = m_atomWmDeleteWindow.AttachedTo()))

        if ((shellWidget = m_shellWidget.CreateAttached
            (&xDisplay, shellArgList, shellArgList.Length()))) {

            m_shellWidget.SetIsCreated(false);

            if ((formWidget = m_formWidget.CreateAttached
                (&xDisplay, shellWidget, formArgList, formArgList.Length()))) {

                m_formWidget.SetIsCreated(false);
                m_formWidget.ManageChild();

                if ((commandWidget = m_commandWidget.CreateAttached
                    (&xDisplay, formWidget, commandArgList, commandArgList.Length()))) {

                    m_commandWidget.SetIsCreated(false);
                    m_commandWidget.ManageChild();
                    m_commandWidget.AddCallback
                    (XmNactivateCallback, (CallbackInterface*)(this));
                }
            }

            m_shellWidget.Realize();

            if (!(LoadImageFile())) {
                m_shellWidget.SetValuesL
                (XtNbackground, m_redColor.AttachedTo(), XtNend);
            }

            XtAddEventHandler
            (shellWidget, NoEventMask | ButtonPressMask | ButtonReleaseMask | ExposureMask | VisibilityChangeMask | StructureNotifyMask, True,
             HandleXtEvent, (XtPointer)((EventHandlerInterface*)(this)));

            XSetWMProtocols
            (&xDisplay, XtWindow(shellWidget), &xAtom, 1);
        }
        return err;
    }
    virtual int BeforeCloseDisplay
    (XDisplay& xDisplay, XScreen& xScreen, int argc, char** argv, char** env) {
        int err = 0;
        FreeStandardColors(xDisplay, xScreen, argc, argv, env);
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual xt::Widget& ShellWidget() const {
        return (xt::Widget&)(m_shellWidget);
    }
    virtual xt::Widget& FormWidget() const {
        return (xt::Widget&)(m_formWidget);
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    ApplicationShell m_shellWidget;
    MainWindow m_formWidget;
    PushButton m_commandWidget;
};

} // namespace hello 
} // namespace xm 
} // namespace x11 
} // namespace xos 

#endif // _XOS_GUI_X11_XM_HELLO_MAIN_HPP 
