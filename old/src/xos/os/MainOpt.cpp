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
///   File: MainOpt.cpp
///
/// Author: $author$
///   Date: 12/23/2012
///////////////////////////////////////////////////////////////////////
#include "xos/os/MainOpt.hpp"

namespace xos {

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
int OnLoggingLevel(const char* optarg) {
    int err = 1;
    char c;

    if ((optarg) && (c = optarg[0]) && !(optarg[1])) {
        err = 0;
        switch(c) {
        case XOS_MAIN_LOGGING_OPTARG_N_ALL:
        case XOS_MAIN_LOGGING_OPTARG_C_ALL:
            XOS_SET_LOGGING_LEVEL(XOS_LOGGING_LEVELS_ALL);
            break;

        case XOS_MAIN_LOGGING_OPTARG_N_NONE:
        case XOS_MAIN_LOGGING_OPTARG_C_NONE:
            XOS_SET_LOGGING_LEVEL(XOS_LOGGING_LEVELS_NONE);
            break;

        case XOS_MAIN_LOGGING_OPTARG_N_FATAL:
        case XOS_MAIN_LOGGING_OPTARG_C_FATAL:
            XOS_SET_LOGGING_LEVEL(XOS_LOGGING_LEVELS_FATAL);
            break;

        case XOS_MAIN_LOGGING_OPTARG_N_ERROR:
        case XOS_MAIN_LOGGING_OPTARG_C_ERROR:
            XOS_SET_LOGGING_LEVEL(XOS_LOGGING_LEVELS_ERROR);
            break;

        case XOS_MAIN_LOGGING_OPTARG_N_WARN:
        case XOS_MAIN_LOGGING_OPTARG_C_WARN:
            XOS_SET_LOGGING_LEVEL(XOS_LOGGING_LEVELS_WARN);
            break;

        case XOS_MAIN_LOGGING_OPTARG_N_INFO:
        case XOS_MAIN_LOGGING_OPTARG_C_INFO:
            XOS_SET_LOGGING_LEVEL(XOS_LOGGING_LEVELS_INFO);
            break;

        case XOS_MAIN_LOGGING_OPTARG_N_DEBUG:
        case XOS_MAIN_LOGGING_OPTARG_C_DEBUG:
            XOS_SET_LOGGING_LEVEL(XOS_LOGGING_LEVELS_DEBUG);
            break;

        case XOS_MAIN_LOGGING_OPTARG_N_TRACE:
        case XOS_MAIN_LOGGING_OPTARG_C_TRACE:
            XOS_SET_LOGGING_LEVEL(XOS_LOGGING_LEVELS_TRACE);
            break;

        case XOS_MAIN_LOGGING_OPTARG_C_MESSAGE_ALL:
            XOS_SET_LOGGING_LEVEL(XOS_LOGGING_LEVELS_ALL);
            break;

        //
        // Message
        //
        case XOS_MAIN_LOGGING_OPTARG_C_MESSAGE_NONE:
            XOS_SET_LOGGING_LEVEL(XOS_LOGGING_LEVELS_MESSAGE_NONE);
            break;

        case XOS_MAIN_LOGGING_OPTARG_C_MESSAGE_FATAL:
            XOS_SET_LOGGING_LEVEL(XOS_LOGGING_LEVELS_FATAL | XOS_LOGGING_LEVELS_MESSAGE_FATAL);
            break;

        case XOS_MAIN_LOGGING_OPTARG_C_MESSAGE_ERROR:
            XOS_SET_LOGGING_LEVEL(XOS_LOGGING_LEVELS_ERROR | XOS_LOGGING_LEVELS_MESSAGE_ERROR);
            break;

        case XOS_MAIN_LOGGING_OPTARG_C_MESSAGE_WARN:
            XOS_SET_LOGGING_LEVEL(XOS_LOGGING_LEVELS_ERROR | XOS_LOGGING_LEVELS_MESSAGE_WARN);
            break;

        case XOS_MAIN_LOGGING_OPTARG_C_MESSAGE_INFO:
            XOS_SET_LOGGING_LEVEL(XOS_LOGGING_LEVELS_ERROR | XOS_LOGGING_LEVELS_MESSAGE_INFO);
            break;

        case XOS_MAIN_LOGGING_OPTARG_C_MESSAGE_DEBUG:
            XOS_SET_LOGGING_LEVEL(XOS_LOGGING_LEVELS_ERROR | XOS_LOGGING_LEVELS_MESSAGE_DEBUG);
            break;

        case XOS_MAIN_LOGGING_OPTARG_C_MESSAGE_TRACE:
            XOS_SET_LOGGING_LEVEL(XOS_LOGGING_LEVELS_ERROR | XOS_LOGGING_LEVELS_MESSAGE_TRACE);
            break;

        default:
            err = 1;
        }
    }
    return err;
}

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
int OnLoggingOption
(int optval, const char* optarg,
 const char* optname, int optind,
 int argc, char**argv, char**env) {
    int err = 1;
    switch(optval) {
    case 'l':
        err = OnLoggingLevel(optarg);
        break;
    }
    return err;
}

} // namespace xos 
