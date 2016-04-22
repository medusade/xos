///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2016 $organization$
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
///   Date: 4/22/2016
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_INET_TLS_HELLO_MAINOPT_HPP
#define _XOS_INET_TLS_HELLO_MAINOPT_HPP

#include "xos/os/Main.hpp"

#define XOS_TLS_HELLO_2STRING_(value) #value
#define XOS_TLS_HELLO_2STRING(value) XOS_TLS_HELLO_2STRING_(value)

#define XOS_TLS_HELLO_DEFAULT_PORTNO 443
#define XOS_TLS_HELLO_DEFAULT_PORT "" XOS_TLS_HELLO_2STRING(XOS_TLS_HELLO_DEFAULT_PORTNO) ""
#define XOS_TLS_HELLO_DEFAULT_HOST "localhost"

#define XOS_TLS_HELLO_DEFAULT_TRANSPORT "t"
#define XOS_TLS_HELLO_DEFAULT_FAMILY "4"

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
#define XOS_TLS_HELLO_CLIENT_OPT "client"
#define XOS_TLS_HELLO_CLIENT_OPTARG_REQUIRED XOS_MAIN_OPT_ARGUMENT_NONE
#define XOS_TLS_HELLO_CLIENT_OPTARG ""
#define XOS_TLS_HELLO_CLIENT_OPTUSE ""
#define XOS_TLS_HELLO_CLIENT_OPTVAL_S "c"
#define XOS_TLS_HELLO_CLIENT_OPTVAL_C 'c'

#define XOS_TLS_HELLO_CLIENT_OPTIONS_OPTION \
   {XOS_TLS_HELLO_CLIENT_OPT, \
    XOS_TLS_HELLO_CLIENT_OPTARG_REQUIRED, 0, \
    XOS_TLS_HELLO_CLIENT_OPTVAL_C},

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
#define XOS_TLS_HELLO_VERSION_OPT "tls-version"
#define XOS_TLS_HELLO_VERSION_OPTARG_REQUIRED XOS_MAIN_OPT_ARGUMENT_REQUIRED
#define XOS_TLS_HELLO_VERSION_OPTARG_1_0_S "0"
#define XOS_TLS_HELLO_VERSION_OPTARG_1_0_C '0'
#define XOS_TLS_HELLO_VERSION_OPTARG_1_1_S "1"
#define XOS_TLS_HELLO_VERSION_OPTARG_1_1_C '1'
#define XOS_TLS_HELLO_VERSION_OPTARG_1_2_S "2"
#define XOS_TLS_HELLO_VERSION_OPTARG_1_2_C '2'
#define XOS_TLS_HELLO_VERSION_OPTARG_1_2_HB_S "h"
#define XOS_TLS_HELLO_VERSION_OPTARG_1_2_HB_C 'h'
#define XOS_TLS_HELLO_VERSION_OPTARG "{(0)1.0 | (1)1.1 | (2)1.2 | (h)1.2-heartbeat}"
#define XOS_TLS_HELLO_VERSION_OPTUSE "TLS Version"
#define XOS_TLS_HELLO_VERSION_OPTVAL_S "v:"
#define XOS_TLS_HELLO_VERSION_OPTVAL_C 'v'

#define XOS_TLS_HELLO_VERSION_OPTIONS_OPTION \
   {XOS_TLS_HELLO_VERSION_OPT, \
    XOS_TLS_HELLO_VERSION_OPTARG_REQUIRED, 0, \
    XOS_TLS_HELLO_VERSION_OPTVAL_C},

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
#define XOS_TLS_HELLO_HOST_OPT "host"
#define XOS_TLS_HELLO_HOST_OPTARG_REQUIRED XOS_MAIN_OPT_ARGUMENT_REQUIRED
#define XOS_TLS_HELLO_HOST_OPTARG "name"
#define XOS_TLS_HELLO_HOST_OPTUSE "Host Name or Address"
#define XOS_TLS_HELLO_HOST_OPTVAL_S "o:"
#define XOS_TLS_HELLO_HOST_OPTVAL_C 'o'

#define XOS_TLS_HELLO_HOST_OPTIONS_OPTION \
   {XOS_TLS_HELLO_HOST_OPT, \
    XOS_TLS_HELLO_HOST_OPTARG_REQUIRED, 0, \
    XOS_TLS_HELLO_HOST_OPTVAL_C},

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
#define XOS_TLS_HELLO_PORT_OPT "port"
#define XOS_TLS_HELLO_PORT_OPTARG_REQUIRED XOS_MAIN_OPT_ARGUMENT_REQUIRED
#define XOS_TLS_HELLO_PORT_OPTARG "number"
#define XOS_TLS_HELLO_PORT_OPTUSE "Port Number"
#define XOS_TLS_HELLO_PORT_OPTVAL_S "p:"
#define XOS_TLS_HELLO_PORT_OPTVAL_C 'p'

#define XOS_TLS_HELLO_PORT_OPTIONS_OPTION \
   {XOS_TLS_HELLO_PORT_OPT, \
    XOS_TLS_HELLO_PORT_OPTARG_REQUIRED, 0, \
    XOS_TLS_HELLO_PORT_OPTVAL_C},

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
#define XOS_TLS_HELLO_FAMILY_OPT "address-family"
#define XOS_TLS_HELLO_FAMILY_OPTARG_REQUIRED XOS_MAIN_OPT_ARGUMENT_REQUIRED
#define XOS_TLS_HELLO_FAMILY_OPTARG_IPV4_S "4"
#define XOS_TLS_HELLO_FAMILY_OPTARG_IPV4_C '4'
#define XOS_TLS_HELLO_FAMILY_OPTARG_IPV6_S "6"
#define XOS_TLS_HELLO_FAMILY_OPTARG_IPV6_C '6'
#define XOS_TLS_HELLO_FAMILY_OPTARG_LOCAL_S "l"
#define XOS_TLS_HELLO_FAMILY_OPTARG_LOCAL_C 'l'
#define XOS_TLS_HELLO_FAMILY_OPTARG "{(4)ipv4 | (6)ipv6 | (l)local}"
#define XOS_TLS_HELLO_FAMILY_OPTUSE "Address Family"
#define XOS_TLS_HELLO_FAMILY_OPTVAL_S "f:"
#define XOS_TLS_HELLO_FAMILY_OPTVAL_C 'f'

#define XOS_TLS_HELLO_FAMILY_OPTIONS_OPTION \
   {XOS_TLS_HELLO_FAMILY_OPT, \
    XOS_TLS_HELLO_FAMILY_OPTARG_REQUIRED, 0, \
    XOS_TLS_HELLO_FAMILY_OPTVAL_C},

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
#define XOS_TLS_HELLO_OPTIONS_CHARS \
    XOS_TLS_HELLO_CLIENT_OPTVAL_S \
    XOS_TLS_HELLO_VERSION_OPTVAL_S \
    XOS_TLS_HELLO_HOST_OPTVAL_S \
    XOS_TLS_HELLO_PORT_OPTVAL_S \
    XOS_TLS_HELLO_FAMILY_OPTVAL_S \
    XOS_MAIN_OPTIONS_CHARS

#define XOS_TLS_HELLO_OPTIONS_OPTIONS \
    XOS_TLS_HELLO_CLIENT_OPTIONS_OPTION \
    XOS_TLS_HELLO_VERSION_OPTIONS_OPTION \
    XOS_TLS_HELLO_HOST_OPTIONS_OPTION \
    XOS_TLS_HELLO_PORT_OPTIONS_OPTION \
    XOS_TLS_HELLO_FAMILY_OPTIONS_OPTION \
    XOS_MAIN_OPTIONS_OPTIONS

namespace xos {
namespace tls {
namespace hello {

} // namespace hello 
} // namespace tls 
} // namespace xos 

#endif // _XOS_INET_TLS_HELLO_MAINOPT_HPP 
