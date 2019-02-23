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
///   File: AsyncContext.hpp
///
/// Author: $author$
///   Date: 2/26/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_JAVAX_SERVLET_ASYNCCONTEXT_HPP
#define _XOS_JAVAX_SERVLET_ASYNCCONTEXT_HPP

#include "xos/jdk/java/lang/String.hpp"

namespace xos {
namespace javax {
namespace servlet {

typedef InterfaceBase AsyncContextImplement;
///////////////////////////////////////////////////////////////////////
///  Class: AsyncContext
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS AsyncContext: virtual public AsyncContextImplement {
public:
    typedef AsyncContextImplement Implements;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

typedef AsyncContext NullAsyncContextImplement;
typedef ExportBase NullAsyncContextExtend;
///////////////////////////////////////////////////////////////////////
///  Class: NullAsyncContext
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS NullAsyncContext
: virtual public NullAsyncContextImplement, public NullAsyncContextExtend {
public:
    typedef NullAsyncContextImplement Implements;
    typedef NullAsyncContextExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    NullAsyncContext() {
    }
    virtual ~NullAsyncContext() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace servlet
} // namespace javax 
} // namespace xos 

#endif // _XOS_JAVAX_SERVLET_ASYNCCONTEXT_HPP 
        

