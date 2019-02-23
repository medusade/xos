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
///   File: Main_main.cpp
///
/// Author: $author$
///   Date: 3/6/2014
///////////////////////////////////////////////////////////////////////
#include "xos/inet/http/cgi/Main_main.hpp"
#include "xos/base/StringStream.hpp"

namespace xos {
namespace http {
namespace cgi {

} // namespace cgi 
} // namespace http 
} // namespace xos 

///////////////////////////////////////////////////////////////////////
/// main
///////////////////////////////////////////////////////////////////////
int main(int argc, char** argv, char** env) {
    xos::os::Mutex locker;
    xos::String loggerString;
    xos::StringStream loggerStream(loggerString, &locker);
    xos::Main::Logger logger(&loggerStream);
    int err = 1;
    XOS_LOGGING_LEVELS levels;
    XOS_LOGGING_LEVELS mainLevels;

    // initialize cgi main
    //
    XOS_HTTP_CGI_MAIN_MAIN_INIT();

    // initialize logger
    //
    XOS_LOGGER_INIT();

    // set logging level to XOS_DEFAULT_LOGGING_LEVELS_ID
    //
    XOS_SET_LOGGING_LEVELS_TO_DEFAULT_LOGGING_LEVELS_ID();

    // get logging level options
    //
    XOS_GET_LOGGING_LEVEL(levels);
    xos::main::GetOptions(argc, argv, env);
    XOS_GET_LOGGING_LEVEL(mainLevels);

    try {
        XOS_LOG_DEBUG("in...");

        XOS_SET_LOGGING_LEVEL(levels);
        err = xos::Main::TheMain(argc, argv, env);
        XOS_SET_LOGGING_LEVEL(mainLevels);

        XOS_LOG_DEBUG("...out");
    } catch(...) {
        XOS_LOG_FATAL("caught(...)");
    }

    // finalize logger
    //
    XOS_LOGGER_FINI();
    return err;
}
