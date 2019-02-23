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
///   Date: 3/17/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_X11_XCB_MAIN_HPP
#define _XOS_GUI_X11_XCB_MAIN_HPP

#include "xos/os/Main.hpp"
#include "xos/gui/x11/xcb/Connection.hpp"
#include "xos/gui/x11/xcb/Setup.hpp"
#include "xos/gui/x11/xcb/Screen.hpp"

#define XOS_GUI_X11_XCB_MAIN_OPT ""
#define XOS_GUI_X11_XCB_MAIN_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_REQUIRED
#define XOS_GUI_X11_XCB_MAIN_OPTARG ""
#define XOS_GUI_X11_XCB_MAIN_OPTUSE ""
#define XOS_GUI_X11_XCB_MAIN_OPTVAL_S ""
#define XOS_GUI_X11_XCB_MAIN_OPTVAL_C ''
#define XOS_GUI_X11_XCB_MAIN_OPTTION \
       {XOS_GUI_X11_XCB_MAIN_OPT, \
        XOS_GUI_X11_XCB_MAIN_OPTARG_REQUIRED, 0, \
        XOS_GUI_X11_XCB_MAIN_OPTVAL_C},

#define XOS_GUI_X11_XCB_MAIN_DISPLAY_OPT "display"
#define XOS_GUI_X11_XCB_MAIN_DISPLAY_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_REQUIRED
#define XOS_GUI_X11_XCB_MAIN_DISPLAY_OPTARG "name"
#define XOS_GUI_X11_XCB_MAIN_DISPLAY_OPTUSE "Display Name"
#define XOS_GUI_X11_XCB_MAIN_DISPLAY_OPTVAL_S "s:"
#define XOS_GUI_X11_XCB_MAIN_DISPLAY_OPTVAL_C 's'
#define XOS_GUI_X11_XCB_MAIN_DISPLAY_OPTTION \
       {XOS_GUI_X11_XCB_MAIN_DISPLAY_OPT, \
        XOS_GUI_X11_XCB_MAIN_DISPLAY_OPTARG_REQUIRED, 0, \
        XOS_GUI_X11_XCB_MAIN_DISPLAY_OPTVAL_C},

#define XOS_GUI_X11_XCB_MAIN_OPTIONS_CHARS \
        XOS_GUI_X11_XCB_MAIN_DISPLAY_OPTVAL_S \
        XOS_MAIN_OPTIONS_CHARS

#define XOS_GUI_X11_XCB_MAIN_OPTIONS_OPTIONS \
        XOS_GUI_X11_XCB_MAIN_DISPLAY_OPTTION \
        XOS_MAIN_OPTIONS_OPTIONS

namespace xos {
namespace x11 {
namespace xcb {

typedef xos::MainImplement MainImplement;
typedef xos::Main MainExtend;
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
    Main(): m_displayChars(0), m_screenNumbers(0), m_connection(0) {
    }
    virtual ~Main() {
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int BeforeOpenConnection(int argc, char** argv, char** env) {
        int err = 0;
        return err;
    }
    virtual int AfterOpenConnection
    (Connection& connection, int argc, char** argv, char** env) {
        int err = 0;
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int BeforeCloseConnection
    (Connection& connection, int argc, char** argv, char** env) {
        int err = 0;
        return err;
    }
    virtual int AfterCloseConnection(int argc, char** argv, char** env) {
        int err = 0;
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual Connection* OpenConnection
    (const char* displayChars, int* screenNumbers, 
     int argc, char** argv, char** env) {
        if (!(m_connection)) {
            String display("0"), screen("0");
            if ((m_displayChars)) {
                display << "\"";
                display << displayChars;
                display << "\"";
            }
            if ((m_screenNumbers)) {
                screen << "{";
                screen << *screenNumbers;
                screen << "}";
            }
            XOS_LOG_DEBUG("m_defaultConnection.Open(" << display << ", " << screen << ")...");
            if ((m_defaultConnection.Open(displayChars, screenNumbers))) {
                XOS_LOG_DEBUG("...m_defaultConnection.Open(" << display << ", " << screen << ")");
                return &m_defaultConnection;
            } else {
                XOS_LOG_ERROR("failed on m_defaultConnection.Open(" << display << ", " << screen << ")");
            }
        }
        return 0;
    }
    virtual bool CloseConnection
    (Connection* connection, int argc, char** argv, char** env) {
        if ((connection) && (connection == &m_defaultConnection)) {
            XOS_LOG_DEBUG("m_defaultConnection.Close()...");
            if ((m_defaultConnection.Close())) {
                XOS_LOG_DEBUG("...m_defaultConnection.Close()");
                return true;
            } else {
                XOS_LOG_ERROR("failed on m_defaultConnection.Close()");
            }
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const xcb_setup_t* AttachSetup
    (Connection& connection, int argc, char** argv, char** env) {
        const xcb_setup_t* xcbSetup = 0;
        XOS_LOG_DEBUG("connection.GetSetup()...");
        if ((xcbSetup = connection.GetSetup())) {
            xcb_screen_t* xcbScreen = 0;
            m_setup.Attach(xcbSetup);
            if (!(xcbScreen = AttachScreen(m_setup, argc, argv, env))) {
                XOS_LOG_ERROR("failed on AttachScreen()");
                m_setup.Detach();
                xcbSetup = 0;
            }
        } else {
            XOS_LOG_ERROR("failed on connection.GetSetup()");
        }
        return xcbSetup;
    }
    virtual const xcb_setup_t* DetachSetup
    (Connection& connection, int argc, char** argv, char** env) {
        const xcb_setup_t* xcbSetup = 0;
        DetachScreen(m_setup, argc, argv, env);
        XOS_LOG_DEBUG("...m_setup.Detach()");
        xcbSetup = m_setup.Detach();
        return xcbSetup;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual xcb_screen_t* AttachScreen
    (Setup& setup, int argc, char** argv, char** env) {
        xcb_screen_t* xcbScreen = 0;
        xcb_screen_iterator_t* xcbI = 0;
        XOS_LOG_DEBUG("setup.Screens()...");
        if ((xcbI = setup.Screens())) {
            Screen::iterator i(*xcbI);
            if ((xcbScreen = *i)) {
                XOS_LOG_INFO("xcbScreen->root == " << xcbScreen->root);
                m_screen.Attach(xcbScreen);
            } else {
                XOS_LOG_ERROR("failed 0 == *i");
            }
        } else {
            XOS_LOG_ERROR("failed 0 == setup.Screens()");
        }
        return xcbScreen;
    }
    virtual xcb_screen_t* DetachScreen
    (Setup& setup, int argc, char** argv, char** env) {
        xcb_screen_t* xcbScreen = 0;
        XOS_LOG_DEBUG("...m_screen.Detach()");
        xcbScreen = m_screen.Detach();
        return xcbScreen;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int BeforeRun(int argc, char** argv, char** env) {
        int err = 0;
        if (!(err = BeforeOpenConnection(argc, argv, env))) {
            if ((m_connection = OpenConnection(m_displayChars, m_screenNumbers, argc, argv, env))) {
                if ((AttachSetup(*m_connection, argc, argv, env))) {
                    if (!(err = AfterOpenConnection(*m_connection, argc, argv, env))) {
                        return err;
                    }
                    DetachSetup(*m_connection, argc, argv, env);
                } else {
                    err = 1;
                }
                BeforeCloseConnection(*m_connection, argc, argv, env);
                CloseConnection(m_connection, argc, argv, env);
                m_connection = 0;
            }
        }
        return err;
    }
    virtual int AfterRun(int argc, char** argv, char** env) {
        int err = 1;
        int err2;
        if ((m_connection)) {
            err = BeforeCloseConnection(*m_connection, argc, argv, env);
            DetachSetup(*m_connection, argc, argv, env);
            if ((err2 = CloseConnection(m_connection, argc, argv, env)))
            if (!(err))
                err = err2;
            m_connection = 0;
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual Connection& GetConnection() const {
        if ((m_connection))
            return (Connection&)(*m_connection);
        return (Connection&)(m_defaultConnection);
    }
    virtual Setup& GetSetup() const {
        return (Setup&)(m_setup);
    }
    virtual Screen& GetScreen() const {
        return (Screen&)(m_screen);
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
        case XOS_GUI_X11_XCB_MAIN_DISPLAY_OPTVAL_C:
            if ((optarg))
            if ((optarg[0]))
                m_displayChars = optarg;
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
        case XOS_GUI_X11_XCB_MAIN_DISPLAY_OPTVAL_C:
            optarg = XOS_GUI_X11_XCB_MAIN_DISPLAY_OPTARG;
            chars = XOS_GUI_X11_XCB_MAIN_DISPLAY_OPTUSE;
            break;
        default:
            chars = Extends::OptionUsage(optarg, longopt);
        }
        return chars;
    }
    virtual const char* Options(const struct option*& longopts) {
        int err = 0;
        static const char* chars = XOS_GUI_X11_XCB_MAIN_OPTIONS_CHARS;
        static struct option optstruct[]= {
            XOS_GUI_X11_XCB_MAIN_OPTIONS_OPTIONS
            {0, 0, 0, 0}};
        longopts = optstruct;
        return chars;
    }

protected:
    const char* m_displayChars;
    int* m_screenNumbers;
    Connection* m_connection;
    Connection m_defaultConnection;
    Setup m_setup;
    Screen m_screen;
};

} // namespace xcb 
} // namespace x11 
} // namespace xos 

#endif // _XOS_GUI_X11_XCB_MAIN_HPP 
