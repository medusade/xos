///////////////////////////////////////////////////////////////////////
/// Copyright 2013, Google Inc.
///
/// Redistribution and use in source and binary forms, with or without
/// modification, are permitted provided that the following conditions are met:
/// 
///  1. Redistributions of source code must retain the above copyright notice,
///     this list of conditions and the following disclaimer.
///  2. Redistributions in binary form must reproduce the above copyright notice,
///     this list of conditions and the following disclaimer in the documentation
///     and/or other materials provided with the distribution.
///  3. The name of the author may not be used to endorse or promote products
///     derived from this software without specific prior written permission.
/// 
/// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
/// WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
/// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
/// EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
/// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
/// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
/// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
/// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
/// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
/// ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
///
///   File: Main.hpp
///
/// Author: $author$
///   Date: 2/24/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_WEBRTC_CLIENT_QT_MAIN_HPP
#define _XOS_WEBRTC_CLIENT_QT_MAIN_HPP

#include "xos/gui/qt/WindowMain.hpp"
#include "xos/webrtc/client/qt/MainWindow.hpp"

#define XOS_WEBRTC_CLIENT_QT_MAIN_OPENGL_OPT "use-opengl"
#define XOS_WEBRTC_CLIENT_QT_MAIN_OPENGL_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_NONE
#define XOS_WEBRTC_CLIENT_QT_MAIN_OPENGL_OPTARG "{on | off}"
#define XOS_WEBRTC_CLIENT_QT_MAIN_OPENGL_OPTARG_ON "on"
#define XOS_WEBRTC_CLIENT_QT_MAIN_OPENGL_OPTARG_OFF "off"
#define XOS_WEBRTC_CLIENT_QT_MAIN_OPENGL_OPTUSE "Use OpenGL Rendering"
#define XOS_WEBRTC_CLIENT_QT_MAIN_OPENGL_OPTVAL_S "g:"
#define XOS_WEBRTC_CLIENT_QT_MAIN_OPENGL_OPTVAL_C 'g'

#define XOS_WEBRTC_CLIENT_QT_MAIN_WINDOW_OPT "use-window"
#define XOS_WEBRTC_CLIENT_QT_MAIN_WINDOW_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_NONE
#define XOS_WEBRTC_CLIENT_QT_MAIN_WINDOW_OPTARG "{on | off}"
#define XOS_WEBRTC_CLIENT_QT_MAIN_WINDOW_OPTARG_ON "on"
#define XOS_WEBRTC_CLIENT_QT_MAIN_WINDOW_OPTARG_OFF "off"
#define XOS_WEBRTC_CLIENT_QT_MAIN_WINDOW_OPTUSE "Use Window Rendering"
#define XOS_WEBRTC_CLIENT_QT_MAIN_WINDOW_OPTVAL_S "w:"
#define XOS_WEBRTC_CLIENT_QT_MAIN_WINDOW_OPTVAL_C 'w'

#define XOS_WEBRTC_CLIENT_QT_MAIN_OPTIONS_CHARS \
    XOS_WEBRTC_CLIENT_QT_MAIN_OPENGL_OPTVAL_S \
    XOS_WEBRTC_CLIENT_QT_MAIN_WINDOW_OPTVAL_S \
    XOS_GUI_QT_MAIN_OPTIONS_CHARS

#define XOS_WEBRTC_CLIENT_QT_MAIN_OPTIONS_OPTIONS \
            {XOS_WEBRTC_CLIENT_QT_MAIN_OPENGL_OPT,\
             XOS_WEBRTC_CLIENT_QT_MAIN_OPENGL_OPTARG_REQUIRED, 0,\
             XOS_WEBRTC_CLIENT_QT_MAIN_OPENGL_OPTVAL_C},\
            {XOS_WEBRTC_CLIENT_QT_MAIN_WINDOW_OPT,\
             XOS_WEBRTC_CLIENT_QT_MAIN_WINDOW_OPTARG_REQUIRED, 0,\
             XOS_WEBRTC_CLIENT_QT_MAIN_WINDOW_OPTVAL_C},\
            XOS_GUI_QT_MAIN_OPTIONS_OPTIONS

namespace xos {
namespace webrtc {
namespace client {
namespace qt {

typedef xos::gui::qt::WindowMainImplement MainImplement;
typedef xos::gui::qt::WindowMain MainExtend;
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Main
: virtual public MainImplement, public MainExtend {
public:
    typedef MainImplement Implements;
    typedef MainExtend Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Main()
    : m_mainWindow(0), 
      m_useOpenGLRenderer(false),
      m_useWindowRenderer(false) {
    }
    virtual ~Main() {
    }

    ///////////////////////////////////////////////////////////////////////
    // main window
    ///////////////////////////////////////////////////////////////////////
    virtual QMainWindow* CreateMainWindow
    (QApplication& qApplication,
     int argc, char** argv, char** env)
    {
        if ((m_mainWindow = new MainWindow(m_useOpenGLRenderer, m_useWindowRenderer))) {
            if (!(m_mainWindow->OnWindowOpen())) {
                delete m_mainWindow;
                m_mainWindow = 0;
            }
        }
        return m_mainWindow;
    }
    virtual bool DestroyMainWindow
    (QMainWindow* mainWindow, QApplication& qApplication,
     int argc, char** argv, char** env)
    {
        bool isSuccess = false;
        if ((mainWindow) && (mainWindow == m_mainWindow)) {
            m_mainWindow->OnWindowClose();
            delete m_mainWindow;
            m_mainWindow = 0;
            isSuccess = true;
        }
        return isSuccess;
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int OnOption
    (int optval, const char* optarg,
     const char* optname, int optind,
     int argc, char**argv, char**env)
    {
        int err = 0;
        switch(optval)
        {
        case XOS_WEBRTC_CLIENT_QT_MAIN_OPENGL_OPTVAL_C:
            if ((optarg)) {
                std::string opt(optarg);
                m_useOpenGLRenderer = !(opt.compare
                (XOS_WEBRTC_CLIENT_QT_MAIN_OPENGL_OPTARG_ON));
            }
            break;
        case XOS_WEBRTC_CLIENT_QT_MAIN_WINDOW_OPTVAL_C:
            if ((optarg)) {
                std::string opt(optarg);
                m_useWindowRenderer = !(opt.compare
                (XOS_WEBRTC_CLIENT_QT_MAIN_WINDOW_OPTARG_ON));
            }
            break;
        default:
            err = Extends::OnOption
            (optval, optarg, optname, optind, argc, argv, env);
        }
        return err;
    }
    virtual const char* OptionUsage
    (const char*& optarg, const struct option* longopt)
    {
        const char* chars = "";
        switch(longopt->val)
        {
        case XOS_WEBRTC_CLIENT_QT_MAIN_OPENGL_OPTVAL_C:
            optarg = XOS_WEBRTC_CLIENT_QT_MAIN_OPENGL_OPTARG;
            chars = XOS_WEBRTC_CLIENT_QT_MAIN_OPENGL_OPTUSE;
            break;
        case XOS_WEBRTC_CLIENT_QT_MAIN_WINDOW_OPTVAL_C:
            optarg = XOS_WEBRTC_CLIENT_QT_MAIN_WINDOW_OPTARG;
            chars = XOS_WEBRTC_CLIENT_QT_MAIN_WINDOW_OPTUSE;
            break;
        default:
            chars = Extends::OptionUsage(optarg, longopt);
        }
        return chars;
    }
    virtual const char* Options
    (const struct option*& longopts)
    {
        int err = 0;
        static const char* chars = XOS_WEBRTC_CLIENT_QT_MAIN_OPTIONS_CHARS;
        static struct option optstruct[]= {
            XOS_WEBRTC_CLIENT_QT_MAIN_OPTIONS_OPTIONS
            {0, 0, 0, 0}};
        longopts = optstruct;
        return chars;
    }

protected:
    MainWindow* m_mainWindow;
    bool m_useOpenGLRenderer;
    bool m_useWindowRenderer;
};

} // namespace qt 
} // namespace client 
} // namespace webrtc 
} // namespace xos 

#endif // _XOS_WEBRTC_CLIENT_QT_MAIN_HPP 
