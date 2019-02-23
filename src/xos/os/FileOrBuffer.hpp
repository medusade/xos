///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2013 $organization$
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
///   File: FileOrBuffer.hpp
///
/// Author: $author$
///   Date: 8/16/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_OS_FILEORBUFFER_HPP
#define _XOS_OS_FILEORBUFFER_HPP

#include "xos/os/File.hpp"
#include "xos/Base/Buffer.hpp"
#include "xos/os/Logger.hpp"

namespace xos {

///////////////////////////////////////////////////////////////////////
///  Class: FileOrBufferT
///////////////////////////////////////////////////////////////////////
template
<typename TWhat,
 class TFile,
 class TImplement,
 class TExtend,
 typename TWhence = StreamBase::Whence,
 TWhence VFromBegin = StreamBase::FromBegin>

class _EXPORT_CLASS FileOrBufferT
: virtual public TImplement, public TExtend {
public:
    typedef TImplement Implements;
    typedef TExtend Extends;
    typedef TWhat WhatT;
    typedef TFile FileT;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    FileOrBufferT
    (FILE* detached, bool isOpen=false, 
     LockedInterface* locked=0, bool noLogging=false)
    : m_file(detached, isOpen, locked, noLogging) {
    }
    FileOrBufferT
    (const WhatT* buffer = 0,
     size_t bufferSize = 0,
     ssize_t bufferLength = -1,
     bool noLogging = false)
    : Extends(buffer, bufferSize, bufferLength),
      m_file(0, false, 0, noLogging) {
    }
    virtual ~FileOrBufferT() {
        if (!(m_file.Closed())) {
            if (!(m_file.noLogging())) 
            { XOS_LOG_ERROR("Failed on m_file.Closed()"); }
            throw(Error(Error::Failed));
        }
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Open(const char* fileName, const char* fileMode = "rb") {
        Detach();
        return m_file.Open(fileName, fileMode);
    }
    virtual bool Close() {
        Detach();
        return m_file.Close();
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const WhatT* Attach
    (const WhatT* buffer,
     size_t bufferSize,
     ssize_t bufferLength = -1) {
        if (!(m_file.Closed())) {
            if (!(m_file.noLogging())) 
            { XOS_LOG_ERROR("Failed on m_file.Closed()"); }
            return 0;
        }
        return Extends::Attach(buffer, bufferSize, bufferLength);
    }
    virtual const WhatT* Detach
    (size_t& bufferSize,
     ssize_t& bufferLength,
     ssize_t& bufferTell) {
        if (!(m_file.Closed())) {
            if (!(m_file.noLogging())) 
            { XOS_LOG_ERROR("Failed on m_file.Closed()"); }
            return 0;
        }
        return Extends::Detach(bufferSize, bufferLength, bufferTell);
    }
    virtual const WhatT* Detach() {
        if (!(m_file.Closed())) {
            if (!(m_file.noLogging())) 
            { XOS_LOG_ERROR("Failed on m_file.Closed()"); }
            return 0;
        }
        return Extends::Detach();
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Read(WhatT* buffer, size_t size) {
        ssize_t count = 0;
        if ((m_file.AttachedTo()))
            count = m_file.Read(buffer, size);
        else
        count = Extends::Read(buffer, size);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    TFile& file() const {
        return (TFile&)(m_file);
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    TFile m_file;
};

typedef FileOrBufferT<char, CharFile, CharStream, CharBuffer> CharFileOrBuffer;
typedef FileOrBufferT<uint8_t, ByteFile, ByteStream, ByteBuffer> ByteFileOrBuffer;

} // namespace xos 

#endif // _XOS_OS_FILEORBUFFER_HPP 
