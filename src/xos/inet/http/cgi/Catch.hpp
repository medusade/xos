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
///   File: Catch.hpp
///
/// Author: $author$
///   Date: 3/9/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_INET_HTTP_CGI_CATCH_HPP
#define _XOS_INET_HTTP_CGI_CATCH_HPP

#include "xos/base/Base.hpp"

#define XOS_HTTP_CGI_CATCH_ENV_FILENAME "cgienv.txt"
#define XOS_HTTP_CGI_CATCH_ARGV_FILENAME "cgiargv.txt"
#define XOS_HTTP_CGI_CATCH_STDIN_FILENAME "cgistdin.txt"
#define XOS_HTTP_CGI_CATCH_STDOUT_FILENAME "cgistdout.txt"

#define XOS_HTTP_CGI_CATCH_ENV_FILE_PATTERN "GATEWAY_INTERFACE="
#define XOS_HTTP_CGI_CATCH_ARGV_FILE_PATTERN "argv[0]="
#define XOS_HTTP_CGI_CATCH_STDIN_FILE_PATTERN "CONTENT_LENGTH="

namespace xos {
namespace http {
namespace cgi {

} // namespace cgi 
} // namespace http 
} // namespace xos 

#endif // _XOS_INET_HTTP_CGI_CATCH_HPP
