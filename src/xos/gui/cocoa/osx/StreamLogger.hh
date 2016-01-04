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
///   File: StreamLogger.hh
///
/// Author: $author$
///   Date: 2/1/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_COCOA_OSX_STREAMLOGGER_HH
#define _XOS_GUI_COCOA_OSX_STREAMLOGGER_HH

#include "xos/gui/cocoa/osx/LoggerStream.hh"
#include "xos/os/StreamLogger.hpp"

namespace xos {
namespace cocoa {
namespace osx {

typedef StreamLogger StreamLoggerExtend;
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class EXPORT_CLASS StreamLogger: public StreamLoggerExtend {
public:
    typedef StreamLoggerExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    StreamLogger
    (LoggerStream* attachedTo = 0,
     Level::Enable levelEnabled = XOS_STREAMLOGGER_LEVELS_ENABLED)
    : Extends(attachedTo, levelEnabled),
      m_oldDefault(GetDefault()){
          SetDefault(this);
    }
    virtual ~StreamLogger(){
        if ((GetDefault() == this))
            SetDefault(m_oldDefault);
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    xos::Logger* m_oldDefault;
};

} // namespace osx
} // namespace cocoa 
} // namespace xos 

#endif // _XOS_GUI_COCOA_OSX_STREAMLOGGER_HH 
