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
///   Date: 8/1/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_APP_WEBRTC_CLIENT_GUI_MAIN_HPP
#define _XOS_APP_WEBRTC_CLIENT_GUI_MAIN_HPP

#include "xos/os/Main.hpp"

#define XOS_APP_WEBRTC_CLIENT_GUI_MAIN_USE_OPENGL true
#define XOS_APP_WEBRTC_CLIENT_GUI_MAIN_USE_WINDOW false

#define XOS_APP_WEBRTC_CLIENT_GUI_MAIN_USE_OPENGL_OPT "opengl"
#define XOS_APP_WEBRTC_CLIENT_GUI_MAIN_USE_OPENGL_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_REQUIRED
#define XOS_APP_WEBRTC_CLIENT_GUI_MAIN_USE_OPENGL_OPTARG "{on | off}"
#define XOS_APP_WEBRTC_CLIENT_GUI_MAIN_USE_OPENGL_OPTUSE "Use OpenGL Rendering"
#define XOS_APP_WEBRTC_CLIENT_GUI_MAIN_USE_OPENGL_OPTVAL_S "g:"
#define XOS_APP_WEBRTC_CLIENT_GUI_MAIN_USE_OPENGL_OPTVAL_C 'g'

#define XOS_APP_WEBRTC_CLIENT_GUI_MAIN_USE_WINDOW_OPT "window"
#define XOS_APP_WEBRTC_CLIENT_GUI_MAIN_USE_WINDOW_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_REQUIRED
#define XOS_APP_WEBRTC_CLIENT_GUI_MAIN_USE_WINDOW_OPTARG "{on | off}"
#define XOS_APP_WEBRTC_CLIENT_GUI_MAIN_USE_WINDOW_OPTUSE "Use Window Rendering"
#define XOS_APP_WEBRTC_CLIENT_GUI_MAIN_USE_WINDOW_OPTVAL_S "w:"
#define XOS_APP_WEBRTC_CLIENT_GUI_MAIN_USE_WINDOW_OPTVAL_C 'w'

#define XOS_APP_WEBRTC_CLIENT_GUI_MAIN_OPTIONS_CHARS \
    XOS_APP_WEBRTC_CLIENT_GUI_MAIN_USE_OPENGL_OPTVAL_S \
    XOS_APP_WEBRTC_CLIENT_GUI_MAIN_USE_WINDOW_OPTVAL_S 

#define XOS_APP_WEBRTC_CLIENT_GUI_MAIN_OPTIONS_OPTIONS \
            {XOS_APP_WEBRTC_CLIENT_GUI_MAIN_USE_OPENGL_OPT, \
             XOS_APP_WEBRTC_CLIENT_GUI_MAIN_USE_OPENGL_OPTARG_REQUIRED, 0, \
             XOS_APP_WEBRTC_CLIENT_GUI_MAIN_USE_OPENGL_OPTVAL_C}, \
            {XOS_APP_WEBRTC_CLIENT_GUI_MAIN_USE_WINDOW_OPT,\
             XOS_APP_WEBRTC_CLIENT_GUI_MAIN_USE_WINDOW_OPTARG_REQUIRED, 0,\
             XOS_APP_WEBRTC_CLIENT_GUI_MAIN_USE_WINDOW_OPTVAL_C}, 

namespace xos {
namespace app {
namespace webrtc {
namespace client {
namespace gui {

///////////////////////////////////////////////////////////////////////
///  Class: MainT
///////////////////////////////////////////////////////////////////////
template <class TImplement, class TExtend>
class _EXPORT_CLASS MainT
: virtual public TImplement, public TExtend {
public:
    typedef TImplement Implements;
    typedef TExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: MainT
    ///////////////////////////////////////////////////////////////////////
    MainT
    (bool useOpenGL = XOS_APP_WEBRTC_CLIENT_GUI_MAIN_USE_OPENGL,
     bool useWindow = XOS_APP_WEBRTC_CLIENT_GUI_MAIN_USE_WINDOW)
    : m_useOpenGL(useOpenGL), m_useWindow(useWindow) {
    }
    virtual ~MainT() {
    }
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
        case XOS_APP_WEBRTC_CLIENT_GUI_MAIN_USE_OPENGL_OPTVAL_C:
            if ((optarg)) {
                String optArg(optarg);
                if (!(optArg.compare("on")) || !(optArg.compare("yes")))
                    m_useOpenGL = true;
                else
                if (!(optArg.compare("off")) || !(optArg.compare("no"))) 
                    m_useOpenGL = false;
            }
            break;
        case XOS_APP_WEBRTC_CLIENT_GUI_MAIN_USE_WINDOW_OPTVAL_C:
            if ((optarg)) {
                String optArg(optarg);
                if (!(optArg.compare("on")) || !(optArg.compare("yes")))
                    m_useWindow = true;
                else
                if (!(optArg.compare("off")) || !(optArg.compare("no"))) 
                    m_useWindow = false;
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
        case XOS_APP_WEBRTC_CLIENT_GUI_MAIN_USE_OPENGL_OPTVAL_C:
            optarg = XOS_APP_WEBRTC_CLIENT_GUI_MAIN_USE_OPENGL_OPTARG;
            chars = XOS_APP_WEBRTC_CLIENT_GUI_MAIN_USE_OPENGL_OPTUSE;
            break;
        case XOS_APP_WEBRTC_CLIENT_GUI_MAIN_USE_WINDOW_OPTVAL_C:
            optarg = XOS_APP_WEBRTC_CLIENT_GUI_MAIN_USE_WINDOW_OPTARG;
            chars = XOS_APP_WEBRTC_CLIENT_GUI_MAIN_USE_WINDOW_OPTUSE;
            break;
        default:
            chars = Extends::OptionUsage(optarg, longopt);
        }
        return chars;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    bool m_useOpenGL;
    bool m_useWindow;
};

} // namespace gui 
} // namespace client 
} // namespace webrtc 
} // namespace app 
} // namespace xos 


#endif // _XOS_APP_WEBRTC_CLIENT_GUI_MAIN_HPP 
        

