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
///   File: App.hpp
///
/// Author: $author$
///   Date: 7/6/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_WX_APP_HPP
#define _XOS_GUI_WX_APP_HPP

#include "xos/gui/wx/Base.hpp"
#include <wx/app.h>

namespace xos {
namespace wx {

typedef InterfaceBase AppImplement;
typedef wxApp AppExtend;
///////////////////////////////////////////////////////////////////////
///  Class: App
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS App
: virtual public AppImplement,
  public AppExtend
{
public:
    typedef AppImplement Implements;
    typedef AppExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: App
    ///////////////////////////////////////////////////////////////////////
    App() {
    }
    virtual ~App() {
    }
};

} // namespace wx 
} // namespace xos 

#endif // _XOS_GUI_WX_APP_HPP 
