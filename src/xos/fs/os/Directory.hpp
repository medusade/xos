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
///   File: Directory.hpp
///
/// Author: $author$
///   Date: 10/27/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_FS_OS_DIRECTORY_HPP
#define _XOS_FS_OS_DIRECTORY_HPP

#include "xos/fs/Directory.hpp"
#include "xos/fs/os/Os.hpp"

#if defined(WINDOWS_API) 
// Windows
#include <direct.h>
typedef HANDLE DIRECTORY_T;
typedef int INVALID_DIRECTORY_T;
#define mkdir(path, mode) _mkdir(path)
#define getcwd(buf, size) _getcwd(buf, size)
#define INVALID_DIRECTORY ((INVALID_DIRECTORY_T)0)
#else // defined(WINDOWS_API) 
// Unix
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
typedef DIR* DIRECTORY_T;
typedef int INVALID_DIRECTORY_T;
#define INVALID_DIRECTORY ((INVALID_DIRECTORY_T)0)
#endif // defined(WINDOWS_API)

#define DIRECTORY_WILDCARD_CHAR '*'
#define DIRECTORY_CURRENT_CHAR '.'
#define DIRECTORY_CURRENT_CHARS "."
#define DIRECTORY_PARENT_CHARS ".."

#if defined(WINDOWS_API) 
// Windows
#include "xos/fs/windows/Directory.hpp"
#else // defined(WINDOWS_API) 
// Unix
#include "xos/fs/unix/Directory.hpp"
#endif // defined(WINDOWS_API)

namespace xos {
namespace fs {
namespace os {

typedef xos::fs::os::os::Directory Directory;

} // namespace os 
} // namespace fs 
} // namespace xos 

#endif // _XOS_FS_OS_DIRECTORY_HPP 
