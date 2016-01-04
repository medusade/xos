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
///   Date: 7/8/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_WX_MAIN_HPP
#define _XOS_GUI_WX_MAIN_HPP

#include "xos/gui/wx/App.hpp"
#include "xos/os/Main.hpp"

#define XOS_GUI_MAIN_DISPLAY_OPT "display"
#define XOS_GUI_MAIN_DISPLAY_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_REQUIRED
#define XOS_GUI_MAIN_DISPLAY_OPTARG "display:screen"
#define XOS_GUI_MAIN_DISPLAY_OPTUSE "Display and Screen"
#define XOS_GUI_MAIN_DISPLAY_OPTVAL_S "s:"
#define XOS_GUI_MAIN_DISPLAY_OPTVAL_C 's'
#define XOS_GUI_MAIN_DISPLAY_OPTION \
        {XOS_GUI_MAIN_DISPLAY_OPT, \
         XOS_GUI_MAIN_DISPLAY_OPTARG_REQUIRED, 0, \
         XOS_GUI_MAIN_DISPLAY_OPTVAL_C},

#define XOS_GUI_QT_MAIN_OPTIONS_CHARS \
    XOS_GUI_MAIN_DISPLAY_OPTVAL_S \
    XOS_MAIN_OPTIONS_CHARS

#define XOS_GUI_QT_MAIN_OPTIONS_OPTIONS \
            XOS_GUI_MAIN_DISPLAY_OPTION \
            XOS_MAIN_OPTIONS_OPTIONS

namespace xos {
namespace wx {

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
    Main() {
    }
    virtual ~Main() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int Entry
    (int argc, char** argv, char** env) {
        int err = wxEntry(argc, argv);
        return err;
    }
    virtual int BeforeEntry
    (int argc, char** argv, char** env) {
        int err = 0;
        return err;
    }
    virtual int AfterEntry
    (int argc, char** argv, char** env) {
        int err = 0;
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int Run
    (int argc, char** argv, char** env)
    {
        int err = 0;
        if (!(err = BeforeEntry(argc, argv, env)))
        {
            int err2;
            err = Entry(argc, argv, env);
            if ((err2 = AfterEntry(argc, argv, env)) && (!err))
                err = err2;
        }
        return err;
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
        case XOS_GUI_MAIN_DISPLAY_OPTVAL_C:
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
        case XOS_GUI_MAIN_DISPLAY_OPTVAL_C:
            optarg = XOS_GUI_MAIN_DISPLAY_OPTARG;
            chars = XOS_GUI_MAIN_DISPLAY_OPTUSE;
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
        static const char* chars = XOS_GUI_QT_MAIN_OPTIONS_CHARS;
        static struct option optstruct[]= {
            XOS_GUI_QT_MAIN_OPTIONS_OPTIONS
            {0, 0, 0, 0}};
        longopts = optstruct;
        return chars;
    }
};

} // namespace wx 
} // namespace xos 

#endif // _XOS_GUI_WX_MAIN_HPP 
