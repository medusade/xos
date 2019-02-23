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
///   File: iXosMain.hh
///
/// Author: $author$
///   Date: 12/20/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_COCOA_CONSOLE_IXOSMAIN_HH
#define _XOS_GUI_COCOA_CONSOLE_IXOSMAIN_HH

#include <Foundation/Foundation.h>
#include "xos/os/StreamLogger.hpp"
#include "xos/base/Base.hpp"

#if defined(OBJC)  
///////////////////////////////////////////////////////////////////////
/// Protocol: iXosMain
///
///   Author: $author$
///     Date: 12/20/2012
///////////////////////////////////////////////////////////////////////
@protocol iXosMain
    - (int)Main:(int)argc argv:(char**)argv env:(char**)env;
    - (void)Release;
@end

///////////////////////////////////////////////////////////////////////
/// Interface: iXosMain
///
///    Author: $author$
///      Date: 12/20/2012
///////////////////////////////////////////////////////////////////////
@interface iXosMain: NSObject {
    }
    + (id<iXosMain>)Allocate;
@end
#else // defined(OBJC)  
#endif // defined(OBJC)  

namespace xos {
namespace gui {
namespace cocoa {
namespace console {

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

} // namespace console 
} // namespace cocoa 
} // namespace gui 
} // namespace xos 

#endif // _XOS_GUI_COCOA_CONSOLE_IXOSMAIN_HH 
