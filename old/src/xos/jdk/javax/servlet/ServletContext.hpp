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
///   File: ServletContext.hpp
///
/// Author: $author$
///   Date: 2/25/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_JAVAX_SERVLET_SERVLETCONTEXT_HPP
#define _XOS_JAVAX_SERVLET_SERVLETCONTEXT_HPP

#include "xos/jdk/java/Types.hpp"

namespace xos {
namespace javax {
namespace servlet {

typedef InterfaceBase ServletContextImplement;
///////////////////////////////////////////////////////////////////////
///  Class: ServletContext
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS ServletContext: virtual public ServletContextImplement {
public:
    typedef ServletContextImplement Implements;
};

typedef ServletContext NullServletContextImplement;
typedef ExportBase NullServletContextExtend;
///////////////////////////////////////////////////////////////////////
///  Class: NullServletContext
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS NullServletContext
: virtual public NullServletContextImplement, public NullServletContextExtend {
public:
    typedef NullServletContextImplement Implements;
    typedef NullServletContextExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    NullServletContext() {
    }
    virtual ~NullServletContext() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace servlet
} // namespace javax 
} // namespace xos 

#endif // _XOS_JAVAX_SERVLET_SERVLETCONTEXT_HPP 
