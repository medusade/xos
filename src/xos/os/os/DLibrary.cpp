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
///   File: DLibrary.cpp
///
/// Author: $author$
///   Date: 10/24/2012
///////////////////////////////////////////////////////////////////////
#include "xos/os/os/DLibrary.hpp"

#if defined(WINDOWS_API) 
// Windows
#include "xos/os/windows/DLibrary.cpp"
#elif defined(MACOSX) 
// MacOSX
#include "xos/os/macosx/DLibrary.cpp"
#else // defined(WINDOWS_API) 
// Unix
#include "xos/os/unix/DLibrary.cpp"
#endif // defined(WINDOWS_API)

namespace xos {
namespace os {

} // namespace os 
} // namespace xos 
