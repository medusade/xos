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
///   File: Semaphores.hpp
///
/// Author: $author$
///   Date: 10/10/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_OS_UNIX_SEMAPHORES_HPP
#define _XOS_OS_UNIX_SEMAPHORES_HPP

#include "xos/base/Base.hpp"

#if defined(MACOSX)
#include "xos/os/macosx/Semaphore.hpp"
#else // defined(MACOSX)
#include "xos/os/unix/Semaphore.hpp"
#endif // defined(MACOSX)

namespace xos {
namespace unix {

} // namespace unix 
} // namespace xos 

#endif // _XOS_OS_UNIX_SEMAPHORES_HPP 
