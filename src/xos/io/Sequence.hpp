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
///   File: Sequence.hpp
///
/// Author: $author$
///   Date: 4/17/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_IO_SEQUENCE_HPP
#define _XOS_IO_SEQUENCE_HPP

#include "xos/io/Locker.hpp"

namespace xos {
namespace io {

///////////////////////////////////////////////////////////////////////
///  Enum: Whence
///////////////////////////////////////////////////////////////////////
enum Whence {
    FromBegin,
    FromEnd,
    FromCurrent
};

///////////////////////////////////////////////////////////////////////
///  Class: SequenceT
///////////////////////////////////////////////////////////////////////
template
<typename TWhat = void, typename TSized = char,
 typename TEnd = int, TEnd VEnd = 0,
 class TImplement = Locker>

class _EXPORT_CLASS SequenceT: virtual public TImplement {
public:
    typedef TImplement Implements;
    typedef TWhat WhatT;
    typedef TSized SizedT;
    typedef TEnd EndT;
    enum { End = VEnd };
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Reset() { return Seek(0); }
    virtual ssize_t Seek(size_t size, Whence whence = FromBegin) { return -1; }
    virtual ssize_t Tell() const { return -1; }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Count(const WhatT* what) const {
        size_t count = 0;
        const SizedT* sized;
        if ((sized = (const SizedT*)(what))) {
             while (*(sized) != End) {
                 ++count;
                 ++sized;
             }
        }
        return count;
    }
    virtual size_t SizeOf(size_t length) const {
        if (1 < (sizeof(SizedT)))
            return (length/sizeof(SizedT));
        return length;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    inline SizedT DToX(uint8_t d, char A = 'A') const {
        SizedT x = (SizedT)(0);
        if ((0 <= d) && (9 >= d))
            x = (SizedT)(('0') +  d);
        else
        if ((10 <= d) && (15 >= d))
            x = (SizedT)((A) + (d - 10));
        return x;
    }
    inline int8_t XToD(const SizedT& x) const {
        int8_t d = -1;
        if (((SizedT)('A') <= x) && ((SizedT)('F') >= x))
            d = ((x - (SizedT)('A')) + 10);
        else
        if (((SizedT)('a') <= x) && ((SizedT)('f') >= x))
            d = ((x - (SizedT)('a')) + 10);
        else
        if (((SizedT)('0') <= x) && ((SizedT)('9') >= x))
            d = ((x - (SizedT)('0')));
        return d;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    inline SizedT DTo64(uint8_t d) const {
        SizedT x = (SizedT)(0);
        if ((0 <= d) && (25 >= d))
            x = (SizedT)(('A') + d);
        else
        if ((26 <= d) && (51 >= d))
            x = (SizedT)(('a') + (d - 26));
        else
        if ((52 <= d) && (61 >= d))
            x = (SizedT)(('0') + (d - 52));
        else
        if ((62 == d))
            x = (SizedT)(('+'));
        else
        if ((63 == d))
            x = (SizedT)(('/'));
        return x;
    }
    inline int8_t B64ToD(const SizedT& x) const {
        int8_t d = -1;
        if (((SizedT)('A') <= x) && ((SizedT)('Z') >= x))
            d = (x - (SizedT)('A'));
        else
        if (((SizedT)('a') <= x) && ((SizedT)('z') >= x))
            d = ((x - (SizedT)('a')) + 26);
        else
        if (((SizedT)('0') <= x) && ((SizedT)('9') >= x))
            d = ((x - (SizedT)('0')) + 52);
        else
        if (((SizedT)('+') == x))
            d = (62);
        else
        if (((SizedT)('/') == x))
            d = (63);
        return d;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef SequenceT<> Sequence;

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
typedef SequenceT<char, char> CharSequence;
typedef SequenceT<wchar_t, wchar_t> WCharSequence;
typedef SequenceT<tchar_t, tchar_t> TCharSequence;

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
typedef SequenceT<BYTE, BYTE> BYTESequence;
typedef SequenceT<WORD, WORD> WORDSequence;

} // namespace io 
} // namespace xos 

#endif // _XOS_IO_SEQUENCE_HPP 
