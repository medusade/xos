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
///   File: Main.cpp
///
/// Author: $author$
///   Date: 3/17/2013
///////////////////////////////////////////////////////////////////////
#include "app/gui/x11/xcb/hello/Main.hpp"
#include "xos/os/Main_main.cpp"

namespace xos {
namespace x11 {
namespace xcb {
namespace hello {

static Main g_main;

} // namespace hello 

EventTargets& EventTargets::Instance() 
{ return hello::g_main.GetEventTargets(); }

} // namespace xcb 
} // namespace x11 
} // namespace xos 
