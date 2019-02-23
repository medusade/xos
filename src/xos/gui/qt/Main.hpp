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
///   Date: 2/22/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_QT_MAIN_HPP
#define _XOS_GUI_QT_MAIN_HPP

#include "xos/os/Main.hpp"
#include "xos/gui/qt/Gui.hpp"

#define XOS_GUI_QT_MAIN_DISPLAY_OPT "display"
#define XOS_GUI_QT_MAIN_DISPLAY_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_REQUIRED
#define XOS_GUI_QT_MAIN_DISPLAY_OPTARG "display:screen"
#define XOS_GUI_QT_MAIN_DISPLAY_OPTUSE "Display and Screen"
#define XOS_GUI_QT_MAIN_DISPLAY_OPTVAL_S "s:"
#define XOS_GUI_QT_MAIN_DISPLAY_OPTVAL_C 's'

#define XOS_GUI_QT_MAIN_OPTIONS_CHARS XOS_GUI_QT_MAIN_DISPLAY_OPTVAL_S XOS_MAIN_OPTIONS_CHARS
#define XOS_GUI_QT_MAIN_OPTIONS_OPTIONS \
            {XOS_GUI_QT_MAIN_DISPLAY_OPT, XOS_GUI_QT_MAIN_DISPLAY_OPTARG_REQUIRED, 0, XOS_GUI_QT_MAIN_DISPLAY_OPTVAL_C},\
            XOS_MAIN_OPTIONS_OPTIONS

namespace xos {
namespace gui {
namespace qt {

typedef xos::MainImplement MainImplement;
typedef xos::Main MainExtend;
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Main: virtual public MainImplement, public MainExtend {
public:
    typedef MainImplement Implements;
    typedef MainExtend Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Main() {
    }
    virtual ~Main() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int Exec
    (QApplication& qApplication,
     int argc, char** argv, char** env)
    {
        int err = qApplication.exec();
        return err;
    }
    virtual int BeforeExec
    (QApplication& qApplication,
     int argc, char** argv, char** env)
    {
        int err = 0;
        return err;
    }
    virtual int AfterExec
    (QApplication& qApplication,
     int argc, char** argv, char** env)
    {
        int err = 0;
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int Run
    (int argc, char** argv, char** env)
    {
        int err = 0;
        QApplication qApplication(argc, argv);
        if (!(err = BeforeExec(qApplication, argc, argv, env)))
        {
            int err2;
            err = Exec(qApplication, argc, argv, env);
            if ((err2 = AfterExec(qApplication, argc, argv, env)) && (!err))
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
        case XOS_GUI_QT_MAIN_DISPLAY_OPTVAL_C:
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
        case XOS_GUI_QT_MAIN_DISPLAY_OPTVAL_C:
            optarg = XOS_GUI_QT_MAIN_DISPLAY_OPTARG;
            chars = XOS_GUI_QT_MAIN_DISPLAY_OPTUSE;
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

} // namespace qt 
} // namespace gui 
} // namespace xos 

#endif // _XOS_GUI_QT_MAIN_HPP 
