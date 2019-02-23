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
///   File: Entry.hpp
///
/// Author: $author$
///   Date: 10/31/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_FS_OS_ENTRY_HPP
#define _XOS_FS_OS_ENTRY_HPP

#include "xos/fs/os/Os.hpp"

#if defined(WINDOWS_API) 
// Windows 
#include "xos/fs/windows/Entry.hpp"
#else // defined(WINDOWS_API) 
// Unix 
#include "xos/fs/unix/Entry.hpp"
#endif // defined(WINDOWS_API) 

namespace xos {
namespace fs {
namespace os {

typedef fs::os::os::Entry Entry;

} // namespace os 
} // namespace fs 
} // namespace xos 

#endif // _XOS_FS_OS_ENTRY_HPP 
