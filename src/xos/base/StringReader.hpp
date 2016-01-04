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
///   File: StringReader.hpp
///
/// Author: $author$
///   Date: 11/26/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_BASE_STRINGREADER_HPP
#define _XOS_BASE_STRINGREADER_HPP

#include "xos/base/Reader.hpp"
#include "xos/base/String.hpp"

namespace xos {

typedef CharReader StringReaderImplement;
typedef ExportBase StringReaderExtend;
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS StringReader
: virtual public StringReaderImplement, public StringReaderExtend {
public:
    typedef StringReaderImplement Implements;
    typedef StringReaderExtend Extends;
    typedef String StringT;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    StringReader(const StringT& s)
    : m_s(s), m_chars(s.c_str()), m_length(s.length()), m_tell(0) {
    }
    virtual ~StringReader() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Read(WhatT* what, size_t size) {
        ssize_t count = -1;
        if (0 < (m_length)) {
            if (m_length < (m_tell + size))
                size = m_length - m_tell;
            if (0 < (size)) {
                memcpy(what, m_chars + m_tell, size);
                m_tell += (count = size);
            }
        } else {
            WhatT c;
            for (count = 0; count < size; ++count, ++what) {
                if (!(c = m_chars[m_tell]))
                    break;
                *what = c;
            }
        }
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    const StringT& m_s;
    const WhatT* m_chars;
    ssize_t m_length;
    size_t m_tell;
};

} // namespace xos 

#endif // _XOS_BASE_STRINGREADER_HPP 
