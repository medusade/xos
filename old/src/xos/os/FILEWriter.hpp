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
///   File: FILEWriter.hpp
///
/// Author: $author$
///   Date: 4/8/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_OS_FILEWRITER_HPP
#define _XOS_OS_FILEWRITER_HPP

#include "xos/base/Writer.hpp"
#include "xos/base/Attached.hpp"
#include "xos/os/Logger.hpp"

namespace xos {

///////////////////////////////////////////////////////////////////////
///  Class: FILEWriterT
///////////////////////////////////////////////////////////////////////
template
<typename TWhat,
 typename TSized = TWhat, typename TEnd = TWhat, TEnd VEnd = 0,
 class TImplement = WriterT<TWhat, TEnd, VEnd, InterfaceBase>,
 class TExtend = Attached<FILE*, int, 0, ExportBase, TImplement> >

class c_EXPORT_CLASS FILEWriterT: virtual public TImplement, public TExtend {
public:
    typedef TImplement Implements;
    typedef TExtend Extends;
    typedef TWhat What;
    typedef TSized Sized;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    FILEWriterT(FILE* attachedTo = 0): Extends(attachedTo) {
    }
    virtual ~FILEWriterT() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Write(const What* what, ssize_t length=-1) {
        ssize_t count = 0;
        FILE* file;
        if ((file = this->m_attachedTo)) {
            if (0 < (length)) {
                if (0 >= (count = fwrite(what, sizeof(Sized), length, file))) {
                    if (!(NoLogging())) {
                        XOS_LOG_ERROR("failed on fwrite(what, sizeof(Sized) = " << sizeof(Sized) << ", length = " << length << ", file)");
                    }
                }
            } else {
                for (size_t written = 0; (*what) != 0; ++what) {
                    if (0 >= (written = fwrite(what, sizeof(Sized), 1, file))) {
                        if (!(NoLogging())) {
                            XOS_LOG_ERROR("failed on fwrite(what, sizeof(Sized) = " << sizeof(Sized) << ", length = 1, file)");
                        }
                        break;
                    }
                    ++count;
                }
            }
        }
        return count;
    }
    virtual ssize_t Flush() {
        ssize_t count = 0;
        FILE* file;
        if ((file = this->m_attachedTo)) {
            int err;
            if ((err = fflush(file))) {
                if (!(NoLogging())) {
                    XOS_LOG_ERROR("failed on fflush(file)");
                }
            }
        }
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool NoLogging() const {
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

typedef FILEWriterT<void, char, char, 0, WriterBase> FILEWriter;
typedef FILEWriterT<char, char, char, 0, CharWriter> CharFILEWriter;
typedef FILEWriterT<tchar_t, tchar_t, tchar_t, 0, TCharWriter> TCharFILEWriter;
typedef FILEWriterT<wchar_t, wchar_t, wchar_t, 0, WCharWriter> WCharFILEWriter;

} // namespace xos 

#endif // _XOS_OS_FILEWRITER_HPP 
