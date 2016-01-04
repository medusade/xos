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
///   File: iXosBaseMain.mm
///
/// Author: $author$
///   Date: 12/24/2012
///////////////////////////////////////////////////////////////////////
#include "xos/gui/cocoa/console/iXosBaseMain.hh"

#if defined(OBJC)  
///////////////////////////////////////////////////////////////////////
/// Implentation: iXosBaseMain
///
///       Author: $author$
///         Date: 12/24/2012
///////////////////////////////////////////////////////////////////////
@implementation iXosBaseMain
    - (int)Run:(int)argc argv:(char**)argv env:(char**)env {
        int err = 0;
        return err;
    }
    - (int)Main:(int)argc argv:(char**)argv env:(char**)env {
        int err = 0;
        [self Run:argc argv:argv env:env];
        return err;
    }
    - (void)Release {
    	[super release];
    }
@end
#else // defined(OBJC)  
#endif // defined(OBJC)  
