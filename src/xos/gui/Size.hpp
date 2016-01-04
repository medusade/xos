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
///   File: Size.hpp
///
/// Author: $author$
///   Date: 3/1/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_SIZE_HPP
#define _XOS_GUI_SIZE_HPP

#include "xos/base/Base.hpp"

namespace xos {
namespace gui {

template <typename TNumber>
struct SizeT {
    TNumber width, height;
    SizeT(TNumber nw, TNumber nh) : width(nw), height(nh) { }
    SizeT() : width(0), height(0) { }
};

typedef SizeT<int> Size;

} // namespace gui 
} // namespace xos 

#endif // _XOS_GUI_SIZE_HPP 
