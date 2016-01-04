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
///   File: File.hpp
///
/// Author: $author$
///   Date: 6/8/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_IO_FILE_HPP
#define _XOS_IO_FILE_HPP

#include "xos/io/file/Writer.hpp"
#include "xos/io/file/Reader.hpp"
#include "xos/base/Opener.hpp"
#include "xos/base/Attacher.hpp"

#define XOS_IO_FILE_MODE_READ "r"
#define XOS_IO_FILE_MODE_WRITE "w"

#define XOS_IO_FILE_MODE_BINARY "b"
#define XOS_IO_FILE_MODE_APPEND "+"

#define XOS_IO_FILE_MODE_READ_BINARY \
    XOS_IO_FILE_MODE_READ \
    XOS_IO_FILE_MODE_BINARY

#define XOS_IO_FILE_MODE_WRITE_BINARY \
    XOS_IO_FILE_MODE_WRITE \
    XOS_IO_FILE_MODE_BINARY

namespace xos {
namespace io {

///////////////////////////////////////////////////////////////////////
///  Class: FileImplements
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS FileImplements
: virtual public file::Reader,
  virtual public file::Writer {
};
typedef OpenerT<FileImplements> FileImplement;
typedef OpenedT
<FILE*, int, 0, FileImplement,
 AttachedT<FILE*, int, 0, FileImplement> > FileExtend;
///////////////////////////////////////////////////////////////////////
///  Class: FileT
///////////////////////////////////////////////////////////////////////
template
<typename TWhat = void, typename TSized = char,
 typename TEnd = int, TEnd VEnd = 0,
 class TExtend = FileExtend, class TImplement = FileImplement>

class _EXPORT_CLASS FileT: virtual public TImplement, public TExtend {
public:
    typedef TImplement Implements;
    typedef TExtend Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    FileT
    (FILE* attachedTo = 0, bool isOpen = false)
    : Extends(attachedTo, isOpen) {
    }
    virtual ~FileT() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Open
    (const String& fileName, const char* fileMode = XOS_IO_FILE_MODE_READ_BINARY) {
        return Open(fileName.Chars(), fileMode);
    }
    virtual bool Open
    (const char* fileName, const char* fileMode = XOS_IO_FILE_MODE_READ_BINARY) {
        if ((OpenAttached(fileName, fileMode)))
            return true;
        return false;
    }
    virtual bool Close() {
        FILE* detached;
        if ((detached = this->Detach())) {
            int err;
            if (!(err = fclose(detached))) {
                return true;
            } else {
                if ((this->Logging()))
                {   XOS_LOG_ERROR("failed "<< errno << " on fclose()"); }
            }
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual FILE* OpenAttached
    (const char* fileName, const char* fileMode = XOS_IO_FILE_MODE_READ_BINARY) {
        if (!(this->Closed()))
            return false;
        if ((fileName) && (fileMode)) {
            FILE* detached;
            if ((detached = fopen(fileName, fileMode))) {
                this->AttachOpened(detached);
                return detached;
            } else {
                if ((this->Logging()))
                {   XOS_LOG_ERROR("failed "<< errno << " on fopen(\"" << fileName << "\", " << fileMode << "\")"); }
            }
        }
        return 0;
    }
};
typedef FileT<> File;

} // namespace io
} // namespace xos 

#endif // _XOS_IO_FILE_HPP 
