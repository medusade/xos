///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2014 $organization$
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
///   File: iMain_main.mm
///
/// Author: $author$
///   Date: 2/1/2014
///////////////////////////////////////////////////////////////////////
#include "xos/gui/cocoa/iMain_main.hh"
#include "xos/gui/cocoa/os/StreamLogger.hh"
#include "xos/gui/cocoa/os/LoggerStream.hh"
#include "xos/os/MainOpt.hpp"
#include "xos/os/FILEStream.hpp"
#include "xos/base/Array.hpp"
#include "xos/base/Types.hpp"

#define XOS_GUI_COCOA_IMAIN_MAIN_ARGS_LONGOPT "--args"

static const char* options(const struct option*& longopts) {
    static const char* chars = XOS_MAIN_OPTIONS_CHARS;
    static struct option optstruct[]= {
        XOS_MAIN_OPTIONS_OPTIONS
        {0, 0, 0, 0}};
    longopts = optstruct;
    return chars;
}
static int onOption
(int optval, const char* optarg,
 const char* optname, int optind,
 int argc, char**argv, char**env) {
    int err = 0;
    switch(optval) {
    case XOS_MAIN_LOGGING_OPTVAL_C:
        err = xos::OnLoggingOption
        (optval, optarg, optname, optind, argc, argv, env);
        break;
    case XOS_MAIN_HELP_OPTVAL_C:
        XOS_SET_LOGGING_LEVEL(XOS_LOGGING_LEVELS_ERROR);
        break;
    }
    return err;
}
static int getOptions(int argc, char**argv, char**env) {
    int err = 0;
    int longindex = 0;
    const struct option* longopts = 0;
    char optvaluename[2] = {0,0};
    const char* optname = optvaluename;
    const char* optstring;
    int optvalue;

    if ((optstring = options(longopts)) && (longopts)) {
        int oldOptind = optind;
        int oldOpterr = opterr;
        opterr = 0;
        while (0 <= (optvalue = getopt_long
               (argc, argv, optstring, longopts, &longindex))) {
            optvaluename[0] = optvalue;
            optname = (longindex)?(longopts[longindex].name):(optvaluename);

            if ((err = onOption
               (optvalue, optarg, optname, longindex, argc, argv, env)))
                break;
        }
        opterr = oldOpterr;
        optind = oldOptind;
    }
    return err;
}

///////////////////////////////////////////////////////////////////////
/// Function: main
///////////////////////////////////////////////////////////////////////
int main(int argc, char** argv, char** env) {
    xos::cocoa::os::LoggerStream loggerStream;
    volatile xos::cocoa::os::StreamLogger logger(&loggerStream);
    int err = 1;
    xos::Array<char*>arguments;
    XOS_LOGGING_LEVELS oldLevels;
    XOS_LOGGING_LEVELS newLevels;
    XOS_LOGGER_INIT();
#if defined(XOS_DEFAULT_LOGGING_LEVELS_ID)
    xos::OnLoggingLevel(XOS_MAIN_2STRING(XOS_DEFAULT_LOGGING_LEVELS_ID));
#endif // defined(XOS_DEFAULT_LOGGING_LEVELS_ID)
    XOS_GET_LOGGING_LEVEL(oldLevels);
    if (2 <= (argc)) {
        if (!(xos::Chars::Compare(argv[1], XOS_GUI_COCOA_IMAIN_MAIN_ARGS_LONGOPT))) {
            arguments.Append(argv, 1);
            if (2 < (argc)) {
                arguments.Append(argv+2, argc-2);
            }
        }
    }
    if ((0 < (arguments.Length())) && (arguments.Elements())) {
        argc = (int)arguments.Length();
        argv = arguments.Elements();
    } else {
        if (1 <= (argc)) {
            argc = 1;
        }
    }
    getOptions(argc, argv, env);
    XOS_GET_LOGGING_LEVEL(newLevels);
    try {
        XOS_LOG_TRACE("in...");
        XOS_SET_LOGGING_LEVEL(oldLevels);
        id<iMain> main = 0;
        if ((main = [iMain create])) {
            if (!(err = [main beforeMain:argc argv:argv env:env])) {
                int err2 = 0;
                if ((err = [main main:argc argv:argv env:env]))
                    XOS_LOG_TRACE("...error " << err << " on [main main]");
                if ((err2 = [main afterMain:argc argv:argv env:env])) {
                    XOS_LOG_TRACE("...error " << err << " on [main afterMain]");
                    if (!err) err = err2;
                }
            } else {
                XOS_LOG_TRACE("...error " << err << " on [main beforeMain]");
            }
            [main destroy];
        } else {
            XOS_LOG_ERROR("failed on [iMain create]");
        }
        XOS_SET_LOGGING_LEVEL(newLevels);
        XOS_LOG_TRACE("...out");
    } catch(...) {
        XOS_LOG_FATAL("caught(...)");
    }
    XOS_LOGGER_FINI();
    return err;
}

namespace xos {
namespace gui {
namespace cocoa {

} // namespace cocoa 
} // namespace gui 
} // namespace xos 
