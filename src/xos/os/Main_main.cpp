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
///   File: Main_main.cpp
///
/// Author: $author$
///   Date: Aug 18, 2012
///////////////////////////////////////////////////////////////////////
#include "xos/os/Main_main.hpp"

///////////////////////////////////////////////////////////////////////
/// main
///////////////////////////////////////////////////////////////////////
int main(int argc, char** argv, char** env) {
    xos::os::Mutex locker;
    XOS_MAIN_LOGGER_STREAM(loggerStream, locker);
    xos::Main::Logger logger(&loggerStream);
    int err = 1;
    XOS_LOGGING_LEVELS oldLevels;
    XOS_LOGGING_LEVELS newLevels;

    // initialize logger
    //
    XOS_LOGGER_INIT();

    // set logging level to XOS_DEFAULT_LOGGING_LEVELS_ID
    //
    XOS_SET_LOGGING_LEVELS_TO_DEFAULT_LOGGING_LEVELS_ID();

    // get logging level options
    //
    XOS_GET_LOGGING_LEVEL(oldLevels);
    xos::main::GetOptions(argc, argv, env);
    XOS_GET_LOGGING_LEVEL(newLevels);

    try {
        XOS_LOG_DEBUG("in...");

        XOS_SET_LOGGING_LEVEL(oldLevels);
        err = xos::Main::TheMain(argc, argv, env);
        XOS_SET_LOGGING_LEVEL(newLevels);

        XOS_LOG_DEBUG("...out");
    } catch(...) {
        XOS_LOG_FATAL("caught(...)");
    }

    // finalize logger
    //
    XOS_LOGGER_FINI();
    return err;
}
