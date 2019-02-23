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
///   File: Base.hpp
///
/// Author: $author$
///   Date: Jul 28, 2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_BASE_HPP_
#define _XOS_BASE_HPP_

#include "xos/base/InterfaceBase.hpp"
#include "xos/base/ExportBase.hpp"
#include "xos/base/Error.hpp"

#define XOS_STRINGX(value) "" #value ""
#define XOS_STRING(value) XOS_STRINGX(value)

namespace xos {

///////////////////////////////////////////////////////////////////////
///  Class: ImplementBase
///////////////////////////////////////////////////////////////////////
class ImplementBase {
public:
    virtual ~ImplementBase() {}
};

///////////////////////////////////////////////////////////////////////
///  Class: Base
///////////////////////////////////////////////////////////////////////
class Base {
public:
    virtual ~Base() {}
};

} // namespace xos

#endif // _XOS_BASE_HPP_ 
