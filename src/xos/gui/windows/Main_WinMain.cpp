///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2013 $organization$
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
///   File: Main_WinMain.cpp
///
/// Author: $author$
///   Date: 1/11/2013
///////////////////////////////////////////////////////////////////////
#include "xos/gui/windows/Main_WinMain.hpp"
#include "xos/os/FILEStream.hpp"
#include "xos/os/os/Mutex.cpp"

namespace xos {
namespace windows {

int GetOptions
(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int cmdShow) {
    int err = 0;
    return err;
}

} // namespace windows 
} // namespace xos 

int WINAPI WinMain
(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int cmdShow) {
    xos::os::Mutex locker;
    xos::FILEStream errStream(stderr, &locker, true);
    xos::windows::Main::Logger errLogger(&errStream);
    int err = 1;
    XOS_LOGGING_LEVELS oldLevels;
    XOS_LOGGING_LEVELS newLevels;
    
    XOS_LOGGER_INIT();
    XOS_GET_LOGGING_LEVEL(oldLevels);

    xos::windows::GetOptions
    (hInstance, hPrevInstance, cmdLine, cmdShow);
    XOS_GET_LOGGING_LEVEL(newLevels);

    try {
        XOS_LOG_TRACE("in...");
        XOS_SET_LOGGING_LEVEL(oldLevels);

        err = xos::windows::Main::TheWinMain
        (hInstance, hPrevInstance, cmdLine, cmdShow);

        XOS_SET_LOGGING_LEVEL(newLevels);
        XOS_LOG_TRACE("...out");
    } catch(...) {
        XOS_LOG_FATAL("caught(...)");
    }
    XOS_LOGGER_FINI();
    return err;
}
