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
///   File: PrintWriter.hpp
///
/// Author: $author$
///   Date: 2/26/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_JAVA_IO_PRINTWRITER_HPP
#define _XOS_JAVA_IO_PRINTWRITER_HPP

#include "xos/jdk/java/io/Writer.hpp"
#include "xos/jdk/java/lang/String.hpp"

namespace xos {
namespace java {
namespace io {

typedef WriterImplement PrintWriterImplement;
typedef Writer PrintWriterExtend;
///////////////////////////////////////////////////////////////////////
///  Class: PrintWriter
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS PrintWriter
: virtual public PrintWriterImplement, public PrintWriterExtend {
public:
    typedef PrintWriterImplement Implements;
    typedef PrintWriterExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    PrintWriter() {
    }
    virtual ~PrintWriter() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t print(char_t c) {
        return 0;
    }
    virtual ssize_t print(const java::lang::String& s) {
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t println() {
        return 0;
    }
    virtual ssize_t println(const java::lang::String& s) {
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

typedef PrintWriterImplement NullPrintWriterImplement;
typedef PrintWriter NullPrintWriterExtend;
///////////////////////////////////////////////////////////////////////
///  Class: NullPrintWriter
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS NullPrintWriter
: virtual public NullPrintWriterImplement, public NullPrintWriterExtend {
public:
    typedef NullPrintWriterImplement Implements;
    typedef NullPrintWriterExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    NullPrintWriter() {
    }
    virtual ~NullPrintWriter() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

typedef NullPrintWriterImplement BasePrintWriterImplement;
typedef NullPrintWriter BasePrintWriterExtend;
///////////////////////////////////////////////////////////////////////
///  Class: BasePrintWriter
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS BasePrintWriter
: virtual public BasePrintWriterImplement, public BasePrintWriterExtend {
public:
    typedef BasePrintWriterImplement Implements;
    typedef BasePrintWriterExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    BasePrintWriter(): m_newLine('\n') {
    }
    virtual ~BasePrintWriter() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t print(const java::lang::String& s) {
        int_t length = s.length();
        ssize_t count = 0;
        ssize_t written;
        for (int_t i = 0; i < length; i++) {
            if (0 >= (written = ((Extends&)(*this)).print(s.charAt(i))))
                return written;
            count += written;
        }
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t println() {
        ssize_t count = 0;
        ssize_t written;
        if (0 >= (written = ((Extends&)(*this)).print(m_newLine)))
            return written;
        count += written;
        return count;
    }
    virtual ssize_t println(const java::lang::String& s) {
        ssize_t count = 0;
        ssize_t written;
        if (0 >= (written = print(s)))
            return written;
        count += written;
        if (0 >= (written = println()))
            return written;
        count += written;
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    const char_t m_newLine;
};

} // namespace io
} // namespace java 
} // namespace xos 


#endif // _XOS_JAVA_IO_PRINTWRITER_HPP 
        

