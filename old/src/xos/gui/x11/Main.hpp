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
///   Date: 3/20/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_X11_MAIN_HPP
#define _XOS_GUI_X11_MAIN_HPP

#include "xos/gui/x11/Display.hpp"
#include "xos/gui/x11/EventTarget.hpp"
#include "xos/gui/x11/Context.hpp"
#include "xos/gui/x11/Event.hpp"
#include "xos/gui/x11/Colormap.hpp"
#include "xos/gui/x11/Color.hpp"
#include "xos/gui/x11/Atom.hpp"
#include "xos/os/Main.hpp"

#define XOS_GUI_X11_MAIN_DISPLAY_NAME ":0"

#define XOS_GUI_X11_MAIN_DISPLAY_OPT "display"
#define XOS_GUI_X11_MAIN_DISPLAY_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_REQUIRED
#define XOS_GUI_X11_MAIN_DISPLAY_OPTARG "name"
#define XOS_GUI_X11_MAIN_DISPLAY_OPTUSE "Display Name"
#define XOS_GUI_X11_MAIN_DISPLAY_OPTVAL_S "s:"
#define XOS_GUI_X11_MAIN_DISPLAY_OPTVAL_C 's'
#define XOS_GUI_X11_MAIN_DISPLAY_OPTTION \
       {XOS_GUI_X11_MAIN_DISPLAY_OPT, \
        XOS_GUI_X11_MAIN_DISPLAY_OPTARG_REQUIRED, 0, \
        XOS_GUI_X11_MAIN_DISPLAY_OPTVAL_C},

#define XOS_GUI_X11_MAIN_OPTIONS_CHARS \
        XOS_GUI_X11_MAIN_DISPLAY_OPTVAL_S \
        XOS_MAIN_OPTIONS_CHARS

#define XOS_GUI_X11_MAIN_OPTIONS_OPTIONS \
        XOS_GUI_X11_MAIN_DISPLAY_OPTTION \
        XOS_MAIN_OPTIONS_OPTIONS

namespace xos {
namespace x11 {

///////////////////////////////////////////////////////////////////////
///  Class: Main
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS MainImplement
: virtual public EventTarget, 
  virtual public xos::MainImplement {
public:
    typedef EventTarget EventTargetImplements;
    typedef xos::MainImplement Implements;
};
typedef Main MainExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Main
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Main
: virtual public MainImplement, public MainExtend {
public:
    typedef MainImplement Implements;
    typedef MainExtend Extends;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: Main
    ///////////////////////////////////////////////////////////////////////
    Main()
    : m_displayNameChars(XOS_GUI_X11_MAIN_DISPLAY_NAME),
      m_doneProcessingXEvents(false) {
    }
    virtual ~Main() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int Run(int argc, char** argv, char** env) {
        int err = 0;
        int err2;

        XOS_LOG_DEBUG("before process XEvents...");

        if (!(err = BeforeProcessXEvents(argc, argv, env))) {
            XOS_LOG_DEBUG("process XEvents...");

            err = ProcessXEvents(argc, argv, env);

            XOS_LOG_DEBUG("after process XEvents...");

            if ((err2 = AfterProcessXEvents(argc, argv, env)))
            if (!(err)) err = err2;
        }
        return err;
    }
    virtual int BeforeRun(int argc, char** argv, char** env) {
        int err = 0;
        XDisplay* xDisplay;
        XScreen* xScreen;

        XOS_LOG_DEBUG("before open display...");

        if (!(err = BeforeOpenDisplay(argc, argv, env))) {
            XOS_LOG_DEBUG("open display...");

            if ((xDisplay = OpenDisplay(xScreen, argc, argv, env))) {
                XOS_LOG_DEBUG("after open display...");

                if (!(err = AfterOpenDisplay(*xDisplay, *xScreen, argc, argv, env))) {
                    XOS_LOG_DEBUG("create context...");

                    if ((CreateContext(*xDisplay, argc, argv, env))) {
                        return err;
                    }
                }
                CloseDisplay(argc, argv, env);
            }
        }
        return err;
    }
    virtual int AfterRun(int argc, char** argv, char** env) {
        int err = 0;

        XOS_LOG_DEBUG("destroy context...");

        if (!(m_context.Destroy()))
            err = 1;

        XOS_LOG_DEBUG("close display...");

        if (!(m_display.Close()))
            err = 1;
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool BeforeOnXEvent(const XEvent& xEvent) {
        return false;
    }
    virtual bool AfterOnXEvent(const XEvent& xEvent) {
        return false;
    }
    virtual bool OnXEvent(const XEvent& xEvent) {
        XDisplay* xDisplay = xEvent.xany.display;
        XWindow xWindow = xEvent.xany.window;
        bool isHandled = false;
        EventTarget* target;
        if ((target = (EventTarget*)(m_context.Find(*xDisplay, xWindow))))
        if ((isHandled = target->OnXEvent(xEvent)))
            return isHandled;
        isHandled = Implements::OnXEvent(xEvent);
        return isHandled;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int ProcessXEvents(int argc, char** argv, char** env) {
        int err = 0;

        XOS_LOG_DEBUG("in...");

        if (!(SetDoneProcessingXEvents(false))) {
            XDisplay* xDisplay;

            if ((xDisplay = m_display.AttachedTo())) {
                XEvent& xEvent = m_event.wrapped();

                XOS_LOG_DEBUG("processing XEvents...");

                while (!(GetDoneProcessingXEvents())) {
                    XOS_LOG_TRACE("next XEvent...");

                    if ((NextXEvent(xEvent, *xDisplay))) {
                        XOS_LOG_TRACE("...next XEvent");
                        ProcessXEvent(xEvent, *xDisplay);
                    } else {
                        XOS_LOG_TRACE("...NO next XEvent");
                        if ((NoNextXEvent(*xDisplay)))
                            break;
                    }
                }
                XOS_LOG_DEBUG("...processing XEvents");
            }
        }
        XOS_LOG_DEBUG("...out");
        return err;
    }
    virtual int BeforeProcessXEvents(int argc, char** argv, char** env) {
        int err = 0;
        return err;
    }
    virtual int AfterProcessXEvents(int argc, char** argv, char** env) {
        int err = 0;
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool ProcessNextXEvent() {
        XDisplay* xDisplay;
        if ((xDisplay = m_display.AttachedTo()))
            return ProcessNextXEvent(*xDisplay);
        return false;
    }
    virtual bool ProcessPeekXEvent() {
        XDisplay* xDisplay;
        if ((xDisplay = m_display.AttachedTo()))
            return ProcessPeekXEvent(*xDisplay);
        return false;
    }
    virtual bool ProcessNextXEvent(XDisplay& xDisplay) {
        return false;
    }
    virtual bool ProcessPeekXEvent(XDisplay& xDisplay) {
        return false;
    }
    virtual bool SetDoneProcessingXEvents(bool isTrue=true) {
        return m_doneProcessingXEvents = (isTrue);
    }
    virtual bool GetDoneProcessingXEvents() const {
        return m_doneProcessingXEvents;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool ProcessXEvent(XEvent& xEvent, XDisplay& xDisplay) {
        bool isHandled = false;
        if (!(isHandled = BeforeOnXEvent(xEvent)))
        if (!(isHandled = OnXEvent(xEvent)))
            isHandled = AfterOnXEvent(xEvent);
        return isHandled;
    }
    virtual bool NoNextXEvent(XDisplay& xDisplay) {
        return true;
    }
    virtual bool NextXEvent(XEvent& xEvent, XDisplay& xDisplay) {
        XNextEvent(&xDisplay, &xEvent);
        return true;
    }
    virtual bool PeekXEvent(XEvent& xEvent, XDisplay& xDisplay) {
        if (False != (XCheckIfEvent(&xDisplay, &xEvent, IsXEvent, (XPointer)(this))))
            return true;
        return false;
    }
    static Bool IsXEvent(XDisplay* xDisplay, XEvent* xEvent, XPointer arg) {
        return True;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int BeforeOpenDisplay(int argc, char** argv, char** env) {
        int err = 0;
        return err;
    }
    virtual int AfterOpenDisplay
    (XDisplay& xDisplay, XScreen& xScreen, int argc, char** argv, char** env) {
        int err = 0;
        err = AllocateStandardColors(xDisplay, xScreen, argc, argv, env);
        return err;
    }
    virtual int BeforeCloseDisplay
    (XDisplay& xDisplay, XScreen& xScreen, int argc, char** argv, char** env) {
        int err = 0;
        err = FreeStandardColors(xDisplay, xScreen, argc, argv, env);
        return err;
    }
    virtual int AfterCloseDisplay(int argc, char** argv, char** env) {
        int err = 0;
        return err;
    }
    virtual XDisplay* OpenDisplay
    (XScreen*& xScreen, int argc, char** argv, char** env) {
        const char* displayNameChars = m_displayNameChars;
        XDisplay* xDisplay = 0;
        if ((displayNameChars))
        if ((m_display.Open(displayNameChars))) {
            xScreen = m_display.ScreenAttachedTo();
            xDisplay = m_display.AttachedTo();
        } else {   
            XOS_LOG_ERROR("failed on m_display.Open(" << displayNameChars << ")"); 
        }
        return xDisplay;
    }
    virtual bool CloseDisplay(int argc, char** argv, char** env) {
        bool isSuccess = false;
        if (!(isSuccess = m_display.Close()))
        {   XOS_LOG_ERROR("failed on m_display.Close()"); }
        return isSuccess;
    }
    virtual bool CreateContext
    (XDisplay& xDisplay, int argc, char** argv, char** env) {
        bool isSuccess = false;
        if (!(isSuccess = m_context.Create(xDisplay)))
        {   XOS_LOG_ERROR("failed on m_context.Create()"); }
        return isSuccess;
    }
    virtual bool DestroyContext(int argc, char** argv, char** env) {
        bool isSuccess = false;
        if (!(isSuccess = m_context.Destroy()))
        {   XOS_LOG_ERROR("failed on m_context.Destroy()"); }
        return isSuccess;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int AttachStandardAtoms
    (XDisplay& xDisplay, XScreen& xScreen, int argc, char** argv, char** env) {
        int err = 1;
        XAtom xAtom;

        if ((xAtom = m_atomWmProtocols.AttachIntern
            (xDisplay, XOS_GUI_X11_ATOM_NAME_WM_PROTOCOLS)))

        if ((xAtom = m_atomWmDeleteWindow.AttachIntern
            (xDisplay, XOS_GUI_X11_ATOM_NAME_WM_DELETE_WINDOW)))
            err = 0;

        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int AllocateStandardColors
    (XDisplay& xDisplay, XScreen& xScreen, int argc, char** argv, char** env) {
        int err = 0;
        XColormap xColormap;
        if ((xColormap = m_colormap.AttachDefaultOfScreen(xDisplay, xScreen))) {
            if ((m_redColor.AllocateRGB8(xDisplay, xColormap, 255,0,0))) {
                if ((m_greenColor.AllocateRGB8(xDisplay, xColormap, 0,255,0))) {
                    if ((m_blueColor.AllocateRGB8(xDisplay, xColormap, 0,0,255))) {
                        if ((m_whiteColor.AttachWhiteOfScreen(xDisplay, xScreen))) {
                            if ((m_blackColor.AttachBlackOfScreen(xDisplay, xScreen))) {
                                return 0;
                            }
                        }
                        m_blueColor.Free();
                    }
                    m_greenColor.Free();
                }
                m_redColor.Free();
            }
        }
        return err;
    }
    virtual int FreeStandardColors
    (XDisplay& xDisplay, XScreen& xScreen, int argc, char** argv, char** env) {
        int err = 0;
        m_blackColor.Detach();
        m_whiteColor.Detach();
        m_blueColor.Free();
        m_greenColor.Free();
        m_redColor.Free();
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual XColormap GetColorMap() const {
        return m_colormap.AttachedTo();
    }
    virtual XPixel RedColor() const {
        return m_redColor.AttachedTo();
    }
    virtual XPixel GreenColor() const {
        return m_greenColor.AttachedTo();
    }
    virtual XPixel BlueColor() const {
        return m_blueColor.AttachedTo();
    }
    virtual XPixel WhiteColor() const {
        return m_whiteColor.AttachedTo();
    }
    virtual XPixel BlackColor() const {
        return m_blackColor.AttachedTo();
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int OnOption
    (int optval, const char* optarg,
     const char* optname, int optind,
     int argc, char**argv, char**env) {
        int err = 0;
        switch(optval)
        {
        case XOS_GUI_X11_MAIN_DISPLAY_OPTVAL_C:
            if ((optarg))
            if ((optarg[0]))
                m_displayNameChars = optarg;
            break;
        default:
            err = Extends::OnOption(optval, optarg, optname, optind, argc, argv, env);
        }
        return err;
    }
    virtual const char* OptionUsage
    (const char*& optarg, const struct option* longopt) {
        const char* chars = "";
        switch(longopt->val)
        {
        case XOS_GUI_X11_MAIN_DISPLAY_OPTVAL_C:
            optarg = XOS_GUI_X11_MAIN_DISPLAY_OPTARG;
            chars = XOS_GUI_X11_MAIN_DISPLAY_OPTUSE;
            break;
        default:
            chars = Extends::OptionUsage(optarg, longopt);
        }
        return chars;
    }
    virtual const char* Options(const struct option*& longopts) {
        int err = 0;
        static const char* chars = XOS_GUI_X11_MAIN_OPTIONS_CHARS;
        static struct option optstruct[]= {
            XOS_GUI_X11_MAIN_OPTIONS_OPTIONS
            {0, 0, 0, 0}};
        longopts = optstruct;
        return chars;
    }

protected:
    const char* m_displayNameChars;
    Display m_display;
    Context m_context;
    Event m_event;
    Color m_redColor;
    Color m_greenColor;
    Color m_blueColor;
    Color m_whiteColor;
    Color m_blackColor;
    Colormap m_colormap;
    Atom m_atomWmProtocols;
    Atom m_atomWmDeleteWindow;
    bool m_doneProcessingXEvents;
};

} // namespace x11 
} // namespace xos 

#endif // _XOS_GUI_X11_MAIN_HPP 
