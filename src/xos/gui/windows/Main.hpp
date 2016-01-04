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
///   File: Main.hpp
///
/// Author: $author$
///   Date: 1/11/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_WINDOWS_MAIN_HPP
#define _XOS_GUI_WINDOWS_MAIN_HPP

#include "xos/base/Base.hpp"
#include "xos/os/StreamLogger.hpp"

namespace xos {
namespace windows {

typedef InterfaceBase MainImplement;
typedef ExportBase MainExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Main
///
/// Author: $author$
///   Date: 1/11/2013
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Main: virtual public MainImplement, public MainExtend {
public:
    typedef MainImplement Implements;
    typedef MainExtend Extends;

    ///////////////////////////////////////////////////////////////////////
    ///  Class: Logger
    ///
    /// Author: $author$
    ///   Date: 1/11/2013
    ///////////////////////////////////////////////////////////////////////
    class EXPORT_CLASS Logger: public StreamLogger {
    public:
        typedef StreamLogger Extends;
        Logger
        (Stream* attachedTo = 0,
         Level::Enable levelEnabled = XOS_STREAMLOGGER_LEVELS_ENABLED)
        : Extends(attachedTo, levelEnabled),
          m_oldDefault(GetDefault()){
              SetDefault(this);
        }
        virtual ~Logger(){
            if ((GetDefault() == this))
                SetDefault(m_oldDefault);
        }
    protected:
        xos::Logger* m_oldDefault;
    };

    Main(): m_theMain(TheMain()) {
        TheMain() = this;
    }
    virtual ~Main() {
        if (this == TheMain())
            TheMain() = m_theMain;
    }

protected:
    virtual int WinMain
    (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int cmdShow) {
        int err = 0;
        return err;
    }
    virtual int BeforeWinMain
    (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int cmdShow) {
        int err = 0;
        return err;
    }
    virtual int AfterWinMain
    (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int cmdShow) {
        int err = 0;
        return err;
    }

public:
    static int TheWinMain
    (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int cmdShow) {
        int err = 1;
        int err2;
        Main* theMain = 0;
        if ((theMain = TheMain())) {
            if (!(err = theMain->BeforeWinMain(hInstance, hPrevInstance, cmdLine, cmdShow))) {
                err = theMain->WinMain(hInstance, hPrevInstance, cmdLine, cmdShow);
                if ((err2 = theMain->AfterWinMain(hInstance, hPrevInstance, cmdLine, cmdShow))) {
                    if (!(err)) err = err2;
                }
            }
        } else {
            XOS_LOG_ERROR("failed on 0 == TheMain()");
        }
        return err;
    }

protected:
    static Main*& TheMain() {
        static Main* theMain = 0;
        return theMain;
    }

protected:
    Main* m_theMain;
};

} // namespace windows 
} // namespace xos 

#endif // _XOS_GUI_WINDOWS_MAIN_HPP 
