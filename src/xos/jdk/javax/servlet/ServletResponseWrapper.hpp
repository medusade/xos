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
///   File: ServletResponseWrapper.hpp
///
/// Author: $author$
///   Date: 3/1/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_JAVAX_SERVLET_SERVLETRESPONSEWRAPPER_HPP
#define _XOS_JAVAX_SERVLET_SERVLETRESPONSEWRAPPER_HPP

#include "xos/jdk/javax/servlet/ServletResponse.hpp"
#include "xos/jdk/java/lang/Object.hpp"
#include "xos/base/Wrapper.hpp"

namespace xos {
namespace javax {
namespace servlet {

typedef ServletResponse ServletResponseWrapperImplement;
typedef Wrapper
<ServletResponse, java::lang::Object,
 java::lang::ObjectImplement> ServletResponseWrapperExtend;
///////////////////////////////////////////////////////////////////////
///  Class: ServletResponseWrapper
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS ServletResponseWrapper
: virtual public ServletResponseWrapperImplement, public ServletResponseWrapperExtend {
public:
    typedef ServletResponseWrapperImplement Implements;
    typedef ServletResponseWrapperExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    ServletResponseWrapper(ServletResponse& servletResponse): Extends(servletResponse) {
    }
    virtual ~ServletResponseWrapper() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace servlet 
} // namespace javax 
} // namespace xos 

#endif // _XOS_JAVAX_SERVLET_SERVLETRESPONSEWRAPPER_HPP 
