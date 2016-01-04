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
///   File: ServletInputStream.hpp
///
/// Author: $author$
///   Date: 2/26/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_JAVAX_SERVLET_SERVLETINPUTSTREAM_HPP
#define _XOS_JAVAX_SERVLET_SERVLETINPUTSTREAM_HPP

#include "xos/jdk/java/io/InputStream.hpp"

namespace xos {
namespace javax {
namespace servlet {

typedef java::io::InputStreamImplement ServletInputStreamImplement;
typedef java::io::InputStream ServletInputStreamExtend;
///////////////////////////////////////////////////////////////////////
///  Class: ServletInputStream
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS ServletInputStream
: virtual public ServletInputStreamImplement, public ServletInputStreamExtend {
public:
    typedef ServletInputStreamImplement Implements;
    typedef ServletInputStreamExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    ServletInputStream() {
    }
    virtual ~ServletInputStream() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

///////////////////////////////////////////////////////////////////////
///  Class: NullServletInputStream
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS NullServletInputStream
: virtual public ServletInputStreamImplement, public ServletInputStream {
public:
    typedef ServletInputStreamImplement Implements;
    typedef ServletInputStream Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    NullServletInputStream() {
    }
    virtual ~NullServletInputStream() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace servlet
} // namespace javax 
} // namespace xos 

#endif // _XOS_JAVAX_SERVLET_SERVLETINPUTSTREAM_HPP 
