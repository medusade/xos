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
///   File: Writer.hpp
///
/// Author: $author$
///   Date: 4/17/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_IO_WRITER_HPP
#define _XOS_IO_WRITER_HPP

#include "xos/io/Sequence.hpp"

namespace xos {
namespace io {

///////////////////////////////////////////////////////////////////////
///  Class: WriterT
///////////////////////////////////////////////////////////////////////
template
<typename TWhat = void, typename TSized = char,
 typename TEnd = int, TEnd VEnd = 0, class TImplement = Sequence>

class _EXPORT_CLASS WriterT: virtual public TImplement {
public:
    typedef TImplement Implements;
    typedef TWhat WhatT;
    typedef TSized SizedT;
    typedef TEnd EndT;
    enum { End = VEnd };
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Write(const WhatT* what, ssize_t size = -1) { return 0; }
    virtual ssize_t Flush() { return 0; }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t WriteL(const WhatT* what, ...) {
        ssize_t count = 0;
        va_list va;
        va_start(va, what);
        count = WriteV(what, va);
        va_end(va);
        return count;
    }
    virtual ssize_t WriteV(const WhatT* what, va_list va) {
        ssize_t count = 0;
        ssize_t length = 0;
        for (count = 0; what; count += length) {
            if (0 > (length = Write(what)))
                return count;
            what = va_arg(va, const SizedT*);
        }
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t WriteFormattedLn(const WhatT* format, ...) {
        ssize_t count = 0;
        va_list va;
        va_start(va, format);
        count = WriteFormattedVLn(format, va);
        va_end(va);
        return count;
    }
    virtual ssize_t WriteFormattedVLn(const WhatT* format, va_list va) {
        ssize_t count = 0;
        if (0 <= (count = WriteFormattedV(format, va))) {
            ssize_t amount;
            if (0 <= (amount = WriteLn()))
                count += amount;
            else count = amount;
        }
        return count;
    }
    virtual ssize_t WriteFormatted(const WhatT* format, ...) {
        ssize_t count = 0;
        va_list va;
        va_start(va, format);
        count = WriteFormattedV(format, va);
        va_end(va);
        return count;
    }
    virtual ssize_t WriteFormattedV(const WhatT* format, va_list va) {
        ssize_t count = 0;
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t WriteLn(const WhatT* what, ssize_t size = -1, char lf = '\n') {
        ssize_t count;
        if (0 <= (count = Write(what, size))) {
            TSized sizedLF(lf);
            ssize_t amount;
            if (0 <= (amount = Write(&sizedLF, 1))) {
                count += amount;
            }
        }
        return count;
    }
    virtual ssize_t WriteLn(char lf = '\n') {
        TSized sizedLF(lf);
        ssize_t count = Write(&sizedLF, 1);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t WritexLn
    (const void* bytes, ssize_t length=-1, char A = 'a', char between = 0, char lf = '\n') {
        ssize_t count = WriteXLn(bytes, length, A, between, lf);
        return count;
    }
    virtual ssize_t WriteXLn
    (const void* bytes, ssize_t length=-1, char A = 'A', char between = 0, char lf = '\n') {
        ssize_t count;
        if (0 <= (count = WriteX(bytes, length, A, between))) {
            TSized sizedLF(lf);
            ssize_t amount;
            if (0 <= (amount = Write(&sizedLF, 1))) {
                count += amount;
            }
        }
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Writex(const void* bytes, ssize_t length=-1, char A = 'a', char between = 0) {
        ssize_t count = WriteX(bytes, length, A, between);
        return count;
    }
    virtual ssize_t WriteX(const void* bytes, ssize_t length=-1, char A = 'a', char between = 0) {
        ssize_t count = Write0X(bytes, length, A, 0, between);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Write0xLn
    (const void* bytes, ssize_t length=-1,
     char A = 'a', char X = 'x', char between = ',', char lf = '\n') {
        ssize_t count = Write0XLn(bytes, length, A, X, between);
        return count;
    }
    virtual ssize_t Write0XLn
    (const void* bytes, ssize_t length=-1,
     char A = 'A', char X = 'X', char between = ',', char lf = '\n') {
        ssize_t count;
        if (0 <= (count = Write0X(bytes, length, A, X, between))) {
            TSized sizedLF(lf);
            ssize_t amount;
            if (0 <= (amount = Write(&sizedLF, 1))) {
                count += amount;
            }
        }
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Write0x
    (const void* bytes, ssize_t length=-1,
     char A = 'a', char X = 'x', char between = ',', char space = ' ') {
        ssize_t count = Write0X(bytes, length, A, X, between, space);
        return count;
    }
    virtual ssize_t Write0X
    (const void* bytes, ssize_t length=-1,
     char A = 'A', char X = 'X', char between = ',', char space = ' ') {
        ssize_t count = 0;
        const uint8_t* byte;
        if ((byte = (const uint8_t*)(bytes))) {
            SizedT zz = (SizedT)('0');
            SizedT zx = (SizedT)(X);
            SizedT t = (SizedT)(between);
            SizedT s = (SizedT)(space);
            ssize_t amount;
            uint8_t b;
            SizedT x[2];
            if (0 <= length) {
                for (; 0 < length; --length) {
                    if ((byte != bytes) && (between)) {
                        if (0 > (amount = Write((const WhatT*)(&t), 1)))
                            return amount;
                        count += amount;
                        if ((space)) {
                            if (0 > (amount = Write((const WhatT*)(&s), 1)))
                                return amount;
                            count += amount;
                        }
                    }
                    if ((X)) {
                        if (0 > (amount = Write((const WhatT*)(&zz), 1)))
                            return amount;
                        count += amount;
                        if (0 > (amount = Write((const WhatT*)(&zx), 1)))
                            return amount;
                        count += amount;
                    }
                    b = (*byte++);
                    x[0] = this->DToX(b >> 4, A);
                    x[1] = this->DToX(b & 15, A);
                    if (0 > (amount = Write((const WhatT*)(x), 2)))
                        return amount;
                    count += amount;
                }
            } else {
                for (; (b = (*byte)); ++byte) {
                    if ((byte != bytes) && (between)) {
                        if (0 > (amount = Write((const WhatT*)(&t), 1)))
                            return amount;
                        count += amount;
                        if ((space)) {
                            if (0 > (amount = Write((const WhatT*)(&s), 1)))
                                return amount;
                            count += amount;
                        }
                    }
                    if ((X)) {
                        if (0 > (amount = Write((const WhatT*)(&zz), 1)))
                            return amount;
                        count += amount;
                        if (0 > (amount = Write((const WhatT*)(&zx), 1)))
                            return amount;
                        count += amount;
                    }
                    x[0] = this->DToX(b >> 4, A);
                    x[1] = this->DToX(b & 15, A);
                    if (0 > (amount = Write((const WhatT*)(x), 2)))
                        return amount;
                    count += amount;
                }
            }
        }
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Write64Ln(const void* bytes, ssize_t length=-1, char lf = '\n') {
        ssize_t count;
        if (0 <= (count = Write64(bytes, length))) {
            TSized sizedLF(lf);
            ssize_t amount;
            if (0 <= (amount = Write(&sizedLF, 1))) {
                count += amount;
            }
        }
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Write64(const void* bytes, ssize_t length=-1) {
        ssize_t count = 0;
        const uint8_t* byte;
        if ((byte = (const uint8_t*)(bytes))) {
            ssize_t amount;
            uint8_t b, carry, shift;
            if (0 <= length) {
                for (carry = 0, shift = 2; 0 < length; --length, ++byte) {
                    b = (*byte);
                    if (0 > (amount = Put64(b, carry, shift)))
                        return amount;
                    count += amount;
                }
            } else {
                for (carry = 0, shift = 2; (b = (*byte)); ++byte) {
                    if (0 > (amount = Put64(b, carry, shift)))
                        return amount;
                    count += amount;
                }
            }
            if ((2 != (shift))) {
                if (0 > (amount = Put64End(carry, shift)))
                    return amount;
                count += amount;
            }
        }
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Put64(uint8_t b, uint8_t& carry, uint8_t& shift) {
        const uint8_t mask = ((uint8_t)-1);
        ssize_t count = 0;
        ssize_t amount;
        SizedT x;
        x = this->DTo64(carry | (b >> shift));
        if (0 > (amount = Write((const WhatT*)(&x), 1)))
            return amount;
        count += amount;
        carry = (b & (mask >> (8 - shift))) << (6 - shift);
        if (6 > (shift)) {
            shift += 2;
        } else {
            x = this->DTo64(carry);
            if (0 > (amount = Write((const WhatT*)(&x), 1)))
                return amount;
            count += amount;
            carry = 0;
            shift = 2;
        }
        return count;
    }
    virtual ssize_t Put64End(uint8_t& carry, uint8_t& shift) {
        ssize_t count = 0;
        ssize_t amount;
        SizedT x;
        x = this->DTo64(carry);
        if (0 > (amount = Write((const WhatT*)(&x), 1)))
            return amount;
        count += amount;
        for (x = ((SizedT)'='); shift != 2;) {
            if (0 > (amount = Write((const WhatT*)(&x), 1)))
                return amount;
            count += amount;
            if (6 > (shift)) {
                shift += 2;
            } else {
                shift = 2;
            }
        }
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef WriterT<> Writer;

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
typedef WriterT<char, char, int, 0, CharSequence> CharWriter;
typedef WriterT<wchar_t, wchar_t, int, 0, WCharSequence> WCharWriter;
typedef WriterT<tchar_t, tchar_t, int, 0, TCharSequence> TCharWriter;

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
typedef WriterT<BYTE, BYTE, int, 0, BYTESequence> BYTEWriter;

} // namespace io
} // namespace xos 

#endif // _XOS_IO_WRITER_HPP 
