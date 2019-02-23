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
///   File: Rectangle.hpp
///
/// Author: $author$
///   Date: 3/1/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_RECTANGLE_HPP
#define _XOS_GUI_RECTANGLE_HPP

#include "xos/gui/Size.hpp"
#include "xos/gui/Point.hpp"
#include "xos/base/Base.hpp"

namespace xos {
namespace gui {

template 
<typename TNumber, 
 typename TPoint = PointT<TNumber>, 
 typename TSize = SizeT<TNumber> >

struct RectangleT {
    TPoint origin;
    TSize size;
    RectangleT(const TSize& fromSize, const TSize& toSize): origin(0,0), size(0,0) {
        Resize(fromSize, toSize);
    }
    RectangleT(int nx, int ny, int nw, int nh): origin(nx, ny), size(nw, nh) { }
    RectangleT(): origin(0,0), size(0,0) { }

    RectangleT& Resize(const TSize& fromSize, const TSize& toSize) {
        return Resize(*this, fromSize, toSize);
    }
    RectangleT& Normalize(const TSize& fromSize, const TSize& toSize) {
        return Normalize(*this, fromSize, toSize);
    }
    RectangleT& Normalize(const TSize& toSize) {
        return Normalize(*this, toSize);
    }
    static RectangleT& Resize
    (RectangleT& rect, const TSize& fromSize, const TSize& toSize) {
        if (toSize.height < toSize.width) {
            if ((rect.size.width = (toSize.height * fromSize.width) / fromSize.height) > toSize.width) {
                rect.size.height = (toSize.width * fromSize.height) / fromSize.width;
                rect.size.width = toSize.width;
            } else {
                rect.size.height = toSize.height;
            }
        } else {
            if ((rect.size.height = (toSize.width * fromSize.height) / fromSize.width) > toSize.height) {
                rect.size.width = (toSize.height * fromSize.width) / fromSize.height;
                rect.size.height = toSize.height;
            } else {
                rect.size.width = toSize.width;
            }
        }
        rect.origin.x = (toSize.width - rect.size.width) / 2;
        rect.origin.y = (toSize.height - rect.size.height) / 2;
        return rect;
    }
    static RectangleT& Normalize
    (RectangleT& rect, const TSize& fromSize, const TSize& toSize) {
        Resize(rect, fromSize, toSize);
        Normalize(rect, toSize);
        return rect;
    }
    static RectangleT& Normalize
    (RectangleT& rect, const TSize& toSize) {
        rect.origin.x /= toSize.width; rect.origin.y /= toSize.height;
        rect.size.width /= toSize.width; rect.size.height /= toSize.height;
        return rect;
    }
};

typedef RectangleT<int, Point, Size> Rectangle;

} // namespace gui 
} // namespace xos 

#endif // _XOS_GUI_RECTANGLE_HPP 
