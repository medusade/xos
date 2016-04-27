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
///   File: MainOpt.hpp
///
/// Author: $author$
///   Date: 12/23/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_OS_MAIN_OPT_HPP
#define _XOS_OS_MAIN_OPT_HPP

#include "xos/base/Base.hpp"
#include "xos/os/Logger.hpp"
#include <getopt.h>

#define XOS_MAIN_2STRING_(id) "" #id ""
#define XOS_MAIN_2STRING(id) XOS_MAIN_2STRING_(id)

#define XOS_MAIN_LOGGING_OPT "logging-level"
#define XOS_MAIN_LOGGING_OPTARG_REQUIRED XOS_MAIN_OPT_ARGUMENT_REQUIRED
#define XOS_MAIN_LOGGING_OPTARG_N_ALL '7'
#define XOS_MAIN_LOGGING_OPTARG_N_NONE '0'
#define XOS_MAIN_LOGGING_OPTARG_N_FATAL '1'
#define XOS_MAIN_LOGGING_OPTARG_N_ERROR '2'
#define XOS_MAIN_LOGGING_OPTARG_N_WARN '3'
#define XOS_MAIN_LOGGING_OPTARG_N_INFO '4'
#define XOS_MAIN_LOGGING_OPTARG_N_DEBUG '5'
#define XOS_MAIN_LOGGING_OPTARG_N_TRACE '6'
#define XOS_MAIN_LOGGING_OPTARG_C_ALL 'a'
#define XOS_MAIN_LOGGING_OPTARG_C_NONE 'n'
#define XOS_MAIN_LOGGING_OPTARG_C_FATAL 'f'
#define XOS_MAIN_LOGGING_OPTARG_C_ERROR 'e'
#define XOS_MAIN_LOGGING_OPTARG_C_WARN 'w'
#define XOS_MAIN_LOGGING_OPTARG_C_INFO 'i'
#define XOS_MAIN_LOGGING_OPTARG_C_DEBUG 'd'
#define XOS_MAIN_LOGGING_OPTARG_C_TRACE 't'
#define XOS_MAIN_LOGGING_OPTARG_C_MESSAGE_ALL 'A'
#define XOS_MAIN_LOGGING_OPTARG_C_MESSAGE_NONE 'N'
#define XOS_MAIN_LOGGING_OPTARG_C_MESSAGE_FATAL 'F'
#define XOS_MAIN_LOGGING_OPTARG_C_MESSAGE_ERROR 'E'
#define XOS_MAIN_LOGGING_OPTARG_C_MESSAGE_WARN 'W'
#define XOS_MAIN_LOGGING_OPTARG_C_MESSAGE_INFO 'I'
#define XOS_MAIN_LOGGING_OPTARG_C_MESSAGE_DEBUG 'D'
#define XOS_MAIN_LOGGING_OPTARG_C_MESSAGE_TRACE 'T'
#define XOS_MAIN_LOGGING_OPTARG_ALL "(a)all"
#define XOS_MAIN_LOGGING_OPTARG_NONE "(n)none"
#define XOS_MAIN_LOGGING_OPTARG_FATAL "(f)fatal"
#define XOS_MAIN_LOGGING_OPTARG_ERROR "(e)error"
#define XOS_MAIN_LOGGING_OPTARG_WARN "(w)waring"
#define XOS_MAIN_LOGGING_OPTARG_INFO "(i)info"
#define XOS_MAIN_LOGGING_OPTARG_DEBUG "(d)debug"
#define XOS_MAIN_LOGGING_OPTARG_TRACE "(t)trace"
#define XOS_MAIN_LOGGING_OPTARG "{" \
    XOS_MAIN_LOGGING_OPTARG_ALL " | " \
    XOS_MAIN_LOGGING_OPTARG_NONE " | " \
    XOS_MAIN_LOGGING_OPTARG_FATAL " | " \
    XOS_MAIN_LOGGING_OPTARG_ERROR " | " \
    XOS_MAIN_LOGGING_OPTARG_WARN " | " \
    XOS_MAIN_LOGGING_OPTARG_INFO " | " \
    XOS_MAIN_LOGGING_OPTARG_DEBUG " | " \
    XOS_MAIN_LOGGING_OPTARG_TRACE "}"
#define XOS_MAIN_LOGGING_OPTUSE ""
#define XOS_MAIN_LOGGING_OPTVAL_S "l:"
#define XOS_MAIN_LOGGING_OPTVAL_C 'l'

#define XOS_MAIN_LOGGING_OPTIONS_OPTION \
   {XOS_MAIN_LOGGING_OPT, \
    XOS_MAIN_LOGGING_OPTARG_REQUIRED, 0, \
    XOS_MAIN_LOGGING_OPTVAL_C},

#define XOS_MAIN_HELP_OPT "help"
#define XOS_MAIN_HELP_OPTARG_REQUIRED XOS_MAIN_OPT_ARGUMENT_NONE
#define XOS_MAIN_HELP_OPTARG ""
#define XOS_MAIN_HELP_OPTUSE "Usage options"
#define XOS_MAIN_HELP_OPTVAL_S "h"
#define XOS_MAIN_HELP_OPTVAL_C 'h'

#define XOS_MAIN_HELP_OPTIONS_OPTION \
   {XOS_MAIN_HELP_OPT, \
    XOS_MAIN_HELP_OPTARG_REQUIRED, 0, \
    XOS_MAIN_HELP_OPTVAL_C},

#define XOS_MAIN_OPTIONS_CHARS \
    XOS_MAIN_LOGGING_OPTVAL_S \
    XOS_MAIN_HELP_OPTVAL_S

#define XOS_MAIN_OPTIONS_OPTIONS \
    XOS_MAIN_LOGGING_OPTIONS_OPTION \
    XOS_MAIN_HELP_OPTIONS_OPTION

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
enum {
    XOS_MAIN_OPT_ARGUMENT_NONE     = 0,
    XOS_MAIN_OPT_ARGUMENT_REQUIRED = 1,
    XOS_MAIN_OPT_ARGUMENT_OPTIONAL = 2
};

namespace xos {

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
typedef int MainOptArgument;
enum {
    MAIN_OPT_ARGUMENT_NONE     = XOS_MAIN_OPT_ARGUMENT_NONE,
    MAIN_OPT_ARGUMENT_REQUIRED = XOS_MAIN_OPT_ARGUMENT_REQUIRED,
    MAIN_OPT_ARGUMENT_OPTIONAL = XOS_MAIN_OPT_ARGUMENT_OPTIONAL
};

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
int OnLoggingLevel(const char* optarg);

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
int OnLoggingOption
(int optval, const char* optarg,
 const char* optname, int optind,
 int argc, char**argv, char**env);

} // namespace xos 

#endif // _XOS_OS_MAIN_OPT_HPP 
