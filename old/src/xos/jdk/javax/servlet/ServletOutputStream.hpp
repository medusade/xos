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
///   File: ServletOutputStream.hpp
///
/// Author: $author$
///   Date: 2/26/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_JAVAX_SERVLET_SERVLETOUTPUTSTREAM_HPP
#define _XOS_JAVAX_SERVLET_SERVLETOUTPUTSTREAM_HPP

#include "xos/jdk/java/io/OutputStream.hpp"

namespace xos {
namespace javax {
namespace servlet {

typedef java::io::OutputStreamImplement ServletOutputStreamImplement;
typedef java::io::OutputStream ServletOutputStreamExtend;
///////////////////////////////////////////////////////////////////////
///  Class: ServletOutputStream
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS ServletOutputStream
: virtual public ServletOutputStreamImplement, public ServletOutputStreamExtend {
public:
    typedef ServletOutputStreamImplement Implements;
    typedef ServletOutputStreamExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    ServletOutputStream() {
    }
    virtual ~ServletOutputStream() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

///////////////////////////////////////////////////////////////////////
///  Class: NullServletOutputStream
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS NullServletOutputStream
: virtual public ServletOutputStreamImplement, public ServletOutputStream {
public:
    typedef ServletOutputStreamImplement Implements;
    typedef ServletOutputStream Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    NullServletOutputStream() {
    }
    virtual ~NullServletOutputStream() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t write(int_t b) {
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace servlet
} // namespace javax 
} // namespace xos 

#endif // _XOS_JAVAX_SERVLET_SERVLETOUTPUTSTREAM_HPP 
