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
///   File: Coded.hpp
///
/// Author: $author$
///   Date: 1/22/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_CODED_HPP
#define _XOS_CODED_HPP

#include "xos/base/Stream.hpp"

namespace xos {

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
template <typename TChar=char, class TImplement=StreamBaseT<TChar> >

class _EXPORT_CLASS Coded: virtual public TImplement {
public:
    typedef TImplement Implements;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Write0x(const void* out,ssize_t length = -1, char d = ',') {
        return WriteX(out, length, 'a', 'x', d);
    }
    virtual ssize_t Write0X(const void* out,ssize_t length = -1, char d = ',') {
        return WriteX(out, length, 'A', 'X', d);
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Writex(const void* out,ssize_t length = -1) {
        return WriteX(out, length, 'a');
    }
    virtual ssize_t WriteX(const void* out,ssize_t length = -1) {
        return WriteX(out, length, 'A');
    }
    virtual ssize_t WriteX(const void* out,ssize_t length, char a, char x = 0, char d = ',') {
        const TChar X[3] = {((TChar)d), ((TChar)'0'), ((TChar)x)};
        const TChar c0 = (TChar)('0');
        const TChar cA = (TChar)(a);
        ssize_t count = 0;
        ssize_t iX;
        uint8_t b,x1,x2;
        TChar c[2];
        const uint8_t* bytes;
        if ((bytes = ((const uint8_t*)out))) {
            for (iX = 1; length; ++bytes) {
                if (!(b = *bytes) && (0 > length))
                    break;
                if (x) {
                    if ((this->Write(X+iX,3-iX)) != (3-iX))
                        break;
                    if (iX) iX = 0;
                }
                x2 = ((b) & 0xF);
                x1 = ((b >> 4) & 0xF);
                c[0] = (x1 > 9)?(cA + (x1-10)):(c0 + x1);
                c[1] = (x2 > 9)?(cA + (x2-10)):(c0 + x2);
                if (2 != (this->Write(c, 2)))
                    break;
                else count += 2;
                if (0 < length)
                    --length;
            }
        }
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t ReadX(void* in,size_t size) {
        ssize_t count = 0;
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Write64(const void* out,ssize_t length) {
        ssize_t count = 0;
        return count;
    }
    virtual ssize_t Read64(void* in,size_t size) {
        ssize_t count = 0;
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace xos 

#endif // _XOS_CODED_HPP 
