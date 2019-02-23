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
///   File: Main_main.hpp
///
/// Author: $author$
///   Date: 3/6/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_OS_MAIN_MAIN_HPP
#define _XOS_OS_MAIN_MAIN_HPP

#include "xos/os/Main.hpp"
#include "xos/os/StreamLogger.hpp"
#include "xos/os/FILEStream.hpp"
#include "xos/os/os/Mutex.cpp"
#include "xos/base/NULLStream.hpp"

#if !defined(XOS_MAIN_LOGGER_STREAM)
#if defined(WINDOWS) && !defined(_CONSOLE)
#define XOS_MAIN_LOGGER_STREAM(loggerStream, locker) \
    xos::NULLStream loggerStream(&locker);
#else // defined(WINDOWS) && !defined(_CONSOLE)
#define XOS_MAIN_LOGGER_STREAM(loggerStream, locker) \
    xos::FILEStream loggerStream(stderr, &locker);
#endif // defined(WINDOWS) && !defined(_CONSOLE)
#endif // !defined(XOS_MAIN_LOGGER_STREAM)

namespace xos {

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS main {
public:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    static const char* Options
    (const struct option*& longopts)
    {
        int err = 0;
        static const char* chars = XOS_MAIN_OPTIONS_CHARS;
        static struct option optstruct[]= {
            XOS_MAIN_OPTIONS_OPTIONS
            {0, 0, 0, 0}};
        longopts = optstruct;
        return chars;
    }
    ///////////////////////////////////////////////////////////////////////
    static int OnOption
    (int optval, const char* optarg,
     const char* optname, int optind,
     int argc, char**argv, char**env)
    {
        int err = 0;
        switch(optval)
        {
        case XOS_MAIN_LOGGING_OPTVAL_C:
            err = xos::Main::OnLoggingOption
            (optval, optarg, optname, optind, argc, argv, env);
            break;
        case XOS_MAIN_HELP_OPTVAL_C:
            XOS_SET_LOGGING_LEVEL(XOS_LOGGING_LEVELS_ERROR);
            break;
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
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
    ///////////////////////////////////////////////////////////////////////
};

} // namespace xos

#endif // _XOS_OS_MAIN_MAIN_HPP 
