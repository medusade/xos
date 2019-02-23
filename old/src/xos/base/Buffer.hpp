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
///   File: Buffer.hpp
///
/// Author: $author$
///   Date: 8/15/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_BASE_BUFFER_HPP
#define _XOS_BASE_BUFFER_HPP

#include "xos/base/Stream.hpp"

namespace xos {

///////////////////////////////////////////////////////////////////////
///  Class: Buffer
///////////////////////////////////////////////////////////////////////
template
<typename TWhat,
 class TImplement,
 class TExtend,
 typename TWhence=StreamBase::Whence,
 TWhence VFromBegin=StreamBase::FromBegin>

class _EXPORT_CLASS Buffer
: virtual public TImplement, public TExtend {
public:
    typedef TImplement Implements;
    typedef TExtend Extends;
    typedef TWhat WhatT;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Buffer
    (const WhatT* buffer = 0,
     size_t bufferSize = 0,
     ssize_t bufferLength = -1)
    : m_readBuffer(buffer), 
      m_bufferSize(bufferSize), 
      m_bufferLength((bufferLength<0)?(bufferSize):(bufferLength)),
      m_bufferTell(0) {
    }
    virtual ~Buffer() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Read(WhatT* buffer, size_t size) {
        ssize_t count = 0;

        if ((buffer) && (size) && (m_bufferTell<m_bufferLength)) {

            if (m_bufferTell + (count = (ssize_t)(size)) >= m_bufferLength)
                size = (size_t)(count = (m_bufferLength - m_bufferTell));

            CopyBuffer(buffer, m_readBuffer+m_bufferTell, size);
            m_bufferTell += count;
        }
        return count;
    }
    virtual ssize_t Write(const WhatT* buffer, ssize_t size = -1) {
        return -Error::NotImplemented;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Fill() {
        return -Error::NotImplemented;
    }
    virtual ssize_t Flush() {
        return -Error::NotImplemented;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Seek(size_t size, TWhence whence = VFromBegin) {
        return -Error::NotImplemented;
    }
    virtual ssize_t Tell() const {
        return m_bufferTell;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const WhatT* Attach
    (const WhatT* buffer,
     size_t bufferSize,
     ssize_t bufferLength = -1) {
        m_readBuffer = buffer;
        m_bufferSize = bufferSize;
        m_bufferLength = (bufferLength<0)?(bufferSize):(bufferLength);
        m_bufferTell = 0;
        return m_readBuffer;
    }
    virtual const WhatT* Detach
    (size_t& bufferSize,
     ssize_t& bufferLength,
     ssize_t& bufferTell) {
        const WhatT* buffer = m_readBuffer;
        bufferSize = m_bufferSize;
        bufferLength = m_bufferLength;
        bufferTell = m_bufferTell;
        m_readBuffer = 0;
        m_bufferSize = 0;
        m_bufferLength = 0;
        m_bufferTell = 0;
        return buffer;
    }
    virtual const WhatT* Detach() {
        size_t bufferSize;
        ssize_t bufferLength;
        ssize_t bufferTell;
        return Detach(bufferSize, bufferLength, bufferTell);
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual size_t CopyBuffer
    (TWhat* to, const TWhat* from, size_t size) const {
        size_t count = 0;
        if ((to) && (from))
        for (count = 0; size > 0; --size, count++)
            (*to++) = (*from++);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    const WhatT* m_readBuffer;
    size_t m_bufferSize;
    ssize_t m_bufferLength;
    ssize_t m_bufferTell;
};

typedef Buffer<char, CharStream, ExportBase> CharBuffer;
typedef Buffer<wchar_t, WCharStream, ExportBase> WCharBuffer;
typedef Buffer<tchar_t, TCharStream, ExportBase> TCharBuffer;

typedef Buffer<uint8_t, ByteStream, ExportBase> ByteBuffer;
typedef Buffer<uint16_t, WordStream, ExportBase> WordBuffer;
typedef Buffer<uint32_t, LongWordStream, ExportBase> LongWordBuffer;

} // namespace xos 

#endif // _XOS_BASE_BUFFER_HPP 
