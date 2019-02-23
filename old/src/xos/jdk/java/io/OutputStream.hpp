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
///   File: OutputStream.hpp
///
/// Author: $author$
///   Date: 2/26/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_JAVA_IO_OUTPUTSTREAM_HPP
#define _XOS_JAVA_IO_OUTPUTSTREAM_HPP

#include "xos/jdk/java/lang/Object.hpp"
#include "xos/jdk/java/util/Array.hpp"

namespace xos {
namespace java {
namespace io {

typedef InterfaceBase OutputStreamImplement;
typedef java::lang::Object OutputStreamExtend;
///////////////////////////////////////////////////////////////////////
///  Class: OutputStream
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS OutputStream
: virtual public OutputStreamImplement, public OutputStreamExtend {
public:
    typedef OutputStreamImplement Implements;
    typedef OutputStreamExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    OutputStream() {
    }
    virtual ~OutputStream() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t write(const util::Array<byte_t>& b, int_t off, int_t len) {
        ssize_t count = 0;
        if ((0 <= off) && (0 < len)) {
            ssize_t length = b.length();
            ssize_t written;
            if ((off+len) > length)
                len = length-off;
            for (int_t i = 0; i < len; ++i) {
                if (0 >= (written = write(b[off+i])))
                    return written;
                count += written;
            }
        }
        return count;
    }
    virtual ssize_t write(const util::Array<byte_t>& b) {
        ssize_t length = b.length();
        ssize_t count = 0;
        if ((0 < length)) {
            ssize_t written;
            for (int_t i = 0; i < length; ++i) {
                if (0 >= (written = write(b[i])))
                    return written;
                count += written;
            }
        }
        return count;
    }
    virtual ssize_t write(int_t b) = 0;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

///////////////////////////////////////////////////////////////////////
///  Class: NullOutputStream
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS NullOutputStream
: virtual public OutputStreamImplement, public OutputStream {
public:
    typedef OutputStreamImplement Implements;
    typedef OutputStreamExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    NullOutputStream() {
    }
    virtual ~NullOutputStream() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t write(int_t b) {
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace io
} // namespace java 
} // namespace xos 

#endif // _XOS_JAVA_IO_OUTPUTSTREAM_HPP 
