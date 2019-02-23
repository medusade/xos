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
///   File: BufferedReader.hpp
///
/// Author: $author$
///   Date: 2/26/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_JAVA_IO_BUFFEREDREADER_HPP
#define _XOS_JAVA_IO_BUFFEREDREADER_HPP

#include "xos/jdk/java/io/Reader.hpp"

namespace xos {
namespace java {
namespace io {

typedef ReaderImplement BufferedReaderImplement;
typedef Reader BufferedReaderExtend;
///////////////////////////////////////////////////////////////////////
///  Class: BufferedReader
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS BufferedReader
: virtual public BufferedReaderImplement, public BufferedReaderExtend {
public:
    typedef BufferedReaderImplement Implements;
    typedef BufferedReaderExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    BufferedReader() {
    }
    virtual ~BufferedReader() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

///////////////////////////////////////////////////////////////////////
///  Class: NullBufferedReader
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS NullBufferedReader
: virtual public BufferedReaderImplement, public BufferedReader {
public:
    typedef BufferedReaderImplement Implements;
    typedef BufferedReader Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    NullBufferedReader() {
    }
    virtual ~NullBufferedReader() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace io
} // namespace java 
} // namespace xos 

#endif // _XOS_JAVA_IO_BUFFEREDREADER_HPP 
