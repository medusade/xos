///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2012 $organization$
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
///   File: iXosMain_main.mm
///
/// Author: $author$
///   Date: 12/23/2012
///////////////////////////////////////////////////////////////////////
#include "xos/gui/cocoa/console/iXosMain_main.hh"
#include "xos/os/MainOpt.hpp"
#include "xos/os/FILEStream.hpp"

static const char* Options
(const struct option*& longopts)
{
    static const char* chars = XOS_MAIN_OPTIONS_CHARS;
    static struct option optstruct[]= {
        XOS_MAIN_OPTIONS_OPTIONS
        {0, 0, 0, 0}};
    longopts = optstruct;
    return chars;
}
static int OnOption
(int optval, const char* optarg,
 const char* optname, int optind,
 int argc, char**argv, char**env)
{
    int err = 0;
    switch(optval)
    {
    case 'l':
        err = xos::OnLoggingOption
        (optval, optarg, optname, optind, argc, argv, env);
        break;
    case 'h':
        XOS_SET_LOGGING_LEVEL(XOS_LOGGING_LEVELS_ERROR);
        break;
    }
    return err;
}
static int GetOptions
(int argc, char**argv, char**env)
{
    int err = 0;
    int longindex = 0;
    const struct option* longopts = 0;
    char optvaluename[2] = {0,0};
    const char* optname = optvaluename;
    const char* optstring;
    int optvalue;

    if ((optstring = Options(longopts)) && (longopts)) {
        int oldOptind = optind;
        int oldOpterr = opterr;
        opterr = 0;
        while (0 <= (optvalue = getopt_long
               (argc, argv, optstring, longopts, &longindex)))
        {
            optvaluename[0] = optvalue;
            optname = (longindex)?(longopts[longindex].name):(optvaluename);

            if ((err = OnOption
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
///
///   Author: $author$
///     Date: 12/20/2012
///////////////////////////////////////////////////////////////////////
int main(int argc, char** argv, char** env) {
    xos::FILEStream errStream(stderr);
    xos::gui::cocoa::console::Logger errLogger(&errStream);
    int err = 1;
    XOS_LOGGING_LEVELS oldLevels;
    XOS_LOGGING_LEVELS newLevels;
    XOS_LOGGER_INIT();
#if defined(XOS_DEFAULT_LOGGING_LEVELS_ID)
    xos::OnLoggingLevel(XOS_MAIN_2STRING(XOS_DEFAULT_LOGGING_LEVELS_ID));
#endif // defined(XOS_DEFAULT_LOGGING_LEVELS_ID)
    XOS_GET_LOGGING_LEVEL(oldLevels);
    GetOptions(argc, argv, env);
    XOS_GET_LOGGING_LEVEL(newLevels);
    try {
        XOS_LOG_TRACE("in...");
        XOS_SET_LOGGING_LEVEL(oldLevels);
#if defined(OBJC)  
        id<iXosMain> main = 0;
        if ((main = [iXosMain Allocate])) {
    	    err = [main Main:argc argv:argv env:env];
    	    [main Release];
        } else {
            XOS_LOG_ERROR("failed on [iXosMain Allocate]");
        }
#else // defined(OBJC)  
        XOS_LOG_ERROR("not built with Objective-C++ compiler");
#endif // defined(OBJC)  
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
namespace console {

} // namespace console 
} // namespace cocoa 
} // namespace gui 
} // namespace xos 
