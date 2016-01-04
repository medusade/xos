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

int OnLoggingLevel(const char* optarg)
{
    int err = 1;
    char c;

    if ((optarg))
    if ((c = optarg[0]))
    if (!(optarg[1]))
    {
        err = 0;
        switch(c)
        {
        case 'a':
            XOS_SET_LOGGING_LEVEL(XOS_LOGGING_LEVELS_ALL);
            break;

        case '0':
        case 'n':
            XOS_SET_LOGGING_LEVEL(XOS_LOGGING_LEVELS_NONE);
            break;

        case '1':
        case 'f':
            XOS_SET_LOGGING_LEVEL(XOS_LOGGING_LEVELS_FATAL);
            break;

        case '2':
        case 'e':
            XOS_SET_LOGGING_LEVEL(XOS_LOGGING_LEVELS_ERROR);
            break;

        case '3':
        case 'w':
            XOS_SET_LOGGING_LEVEL(XOS_LOGGING_LEVELS_WARN);
            break;

        case '4':
        case 'i':
            XOS_SET_LOGGING_LEVEL(XOS_LOGGING_LEVELS_INFO);
            break;

        case '5':
        case 'd':
            XOS_SET_LOGGING_LEVEL(XOS_LOGGING_LEVELS_DEBUG);
            break;

        case '6':
        case 't':
            XOS_SET_LOGGING_LEVEL(XOS_LOGGING_LEVELS_TRACE);
            break;

        default:
            err = 1;
        }
    }
    return err;
}

int OnLoggingOption
(int optval, const char* optarg,
 const char* optname, int optind,
 int argc, char**argv, char**env)
{
    int err = 1;
    switch(optval)
    {
    case 'l':
        err = OnLoggingLevel(optarg);
        break;
    }
    return err;
}

} // namespace xos 
