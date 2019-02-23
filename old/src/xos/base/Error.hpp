///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2012 $organization$
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
///   File: Error.hpp
///
/// Author: $author$
///   Date: Aug 5, 2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_ERROR_HPP_
#define _XOS_ERROR_HPP_

#include "xos/base/Platform.hpp"

namespace xos {

class EXPORT_CLASS Error {
public:
    typedef int Code;
    enum {
        None = 0,
        Failed,
        NotImplemented,
        NotAllowed,
        InvalidParameter,
        InvalidParameterSize,
        InvalidParameterValue,

        Next,
        First = None,
        Last = Next-1
    };
    Error(Code code = None): m_code(code) {}
    inline Error& operator = (Code code) {
        m_code = code;
        return *this;
    }
    inline operator Code() const {
        return m_code;
    }
protected:
    Code m_code;
};

} // namespace xos

#endif // _XOS_ERROR_HPP_ 
