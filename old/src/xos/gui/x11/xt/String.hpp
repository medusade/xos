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
///   File: String.hpp
///
/// Author: $author$
///   Date: 3/29/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_X11_XT_STRING_HPP
#define _XOS_GUI_X11_XT_STRING_HPP

#include "xos/gui/x11/Intrinsic.hpp"
#include "xos/base/StringBase.hpp"
#include "xos/base/String.hpp"

namespace xos {
namespace x11 {
namespace xt {

typedef XtChar Char;
typedef StringBaseT<Char> StringBase;
typedef StringT<Char, StringBase> StringExtend;
///////////////////////////////////////////////////////////////////////
///  Class: String
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS String: public StringExtend {
public:
    typedef StringExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: String
    ///////////////////////////////////////////////////////////////////////
    String(const wchar_t* chars, size_t length): Extends(chars, length) {
    }
    String(const wchar_t* chars): Extends(chars) {
    }
    String(const Char* chars, size_t length): Extends(chars, length) {
    }
    String(const Char* chars): Extends(chars) {
    }
    String(const String& copy): Extends(copy) {
    }
    String(const std::string& copy) {
        this->append(copy.c_str());
    }
    String() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual XtString AttachedTo() const {
        return str();
    }
};

} // namespace xt 
} // namespace x11 
} // namespace xos 

#endif // _XOS_GUI_X11_XT_STRING_HPP 
