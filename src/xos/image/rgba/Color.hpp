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
///   File: Color.hpp
///
/// Author: $author$
///   Date: 8/15/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_IMAGE_RGBA_COLOR_HPP
#define _XOS_IMAGE_RGBA_COLOR_HPP

#include "xos/base/Base.hpp"

namespace xos {
namespace image {
namespace rgba {
namespace color {

namespace channel {
///////////////////////////////////////////////////////////////////////
///    Enum: Channel
///////////////////////////////////////////////////////////////////////
enum {
    Red,
    Green,
    Blue,
    Alpha,
    
    First = Red,
    Last  = Alpha,
    Count = (Last - First) + 1
};
} // namespace channel 

typedef int Channel;
enum { Channels = channel::Count };

} // namespace color 
} // namespace rgba 
} // namespace image 
} // namespace xos 

#endif // _XOS_IMAGE_RGBA_COLOR_HPP 
