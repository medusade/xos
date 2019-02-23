///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2014 $organization$
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
///   File: Text.hpp
///
/// Author: $author$
///   Date: 1/1/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_JSON_TEXT_HPP
#define _XOS_JSON_TEXT_HPP

#include "xos/inet/json/Node.hpp"

namespace xos {
namespace json {

typedef StringImplement TextImplement;
typedef String TextExtend;
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Text
: virtual public TextImplement, public TextExtend {
public:
    typedef TextImplement Implements;
    typedef TextExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Text(const String& copy): Extends(copy) {
    }
    Text(const Text& copy): Extends(copy) {
    }
    Text() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual Node& To(Node& to) const;
};

} // namespace json
} // namespace xos 

#endif // _XOS_JSON_TEXT_HPP 
