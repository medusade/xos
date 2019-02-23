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
///   File: Foundation.mm
///
/// Author: $author$
///   Date: 12/23/2012
///////////////////////////////////////////////////////////////////////
#include <Foundation/Foundation.h>

#if defined(OBJC)  
#if !__OBJC2__
///////////////////////////////////////////////////////////////////////
/// Implentation: NSObject
///
///       Author: $author$
///         Date: 12/20/2012
///////////////////////////////////////////////////////////////////////
@implementation NSObject
    - (void)release {
		[super free];
    }
@end
#endif // !__OBJC2__
#else // defined(OBJC)  
#endif // defined(OBJC)  

namespace xos {
namespace windows {
namespace cocoa {

} // namespace cocoa 
} // namespace windows 
} // namespace xos 
