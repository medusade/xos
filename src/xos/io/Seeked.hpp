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
///   File: Seeked.hpp
///
/// Author: $author$
///   Date: 5/11/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_IO_SEEKED_HPP
#define _XOS_IO_SEEKED_HPP

#include "xos/io/Sequence.hpp"

namespace xos {
namespace io {

///////////////////////////////////////////////////////////////////////
///  Class: SeekedT
///////////////////////////////////////////////////////////////////////
template
<ssize_t VLength = 0,
 class TImplement = Sequence,
 class TExtend = InterfaceBase>

class _EXPORT_CLASS SeekedT: virtual public TImplement, public TExtend {
public:
    typedef TImplement Implements;
    typedef TExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    SeekedT(ssize_t size = VLength, ssize_t length = VLength, size_t tell = 0)
    : m_length(length), m_size(), m_tell(tell) {
    }
    virtual ~SeekedT() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Seek(size_t size, Whence whence = FromBegin) {
        switch (whence) {
        case FromCurrent:
            size += m_tell;
            break;
        case FromEnd:
            if (0 > (m_length)) {
                return -1;
            } else {
                if (size > (m_length)) {
                    size = 0;
                } else {
                    size = m_length - size;
                }
            }
            break;
        case FromBegin:
            break;
        default:
            return -1;
        }
        if ((size) != m_tell) {
            if ((size <= m_length) || (0 > m_length)) {
                return m_tell = size;
            } else {
                if (0 <= m_length) {
                    return m_tell = m_length;
                }
            }
        } else {
            return m_tell;
        }
        return -1;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t SetTell(size_t to) {
        return m_tell = to;
    }
    virtual ssize_t Tell() const {
        return m_tell;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t SetSize(ssize_t to) {
        return m_size = to;
    }
    virtual ssize_t Size() const {
        return m_size;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t SetLength(ssize_t to) {
        return m_length = to;
    }
    virtual ssize_t Length() const {
        return m_length;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    ssize_t m_length;
    ssize_t m_size;
    size_t m_tell;
};

} // namespace io 
} // namespace xos 

#endif // _XOS_IO_SEEKED_HPP 
