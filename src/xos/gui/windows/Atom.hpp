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
///   File: Atom.hpp
///
/// Author: $author$
///   Date: 1/11/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_WINDOWS_ATOM_HPP
#define _XOS_GUI_WINDOWS_ATOM_HPP

#include "xos/base/Registered.hpp"
#include "xos/base/Created.hpp"
#include "xos/base/Attached.hpp"

namespace xos {
namespace windows {

typedef Attached<ATOM, int, 0, ExportBase> ATOMAttached;
typedef Created<ATOM, int, 0, ATOMAttached> ATOMCreated;
typedef Registered<ATOM, int, 0, ATOMAttached> ATOMRegistered;

} // namespace windows 
} // namespace xos 

#endif // _XOS_GUI_WINDOWS_ATOM_HPP 
