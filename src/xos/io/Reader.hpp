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
///   File: Reader.hpp
///
/// Author: $author$
///   Date: 4/17/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_IO_READER_HPP
#define _XOS_IO_READER_HPP

#include "xos/io/Sequence.hpp"
#include "xos/os/Logger.hpp"

namespace xos {
namespace io {

typedef Sequence ReaderImplement;
///////////////////////////////////////////////////////////////////////
///  Class: ReaderT
///////////////////////////////////////////////////////////////////////
template
<typename TWhat = void, typename TSized = char,
 typename TEnd = int, TEnd VEnd = 0, class TImplement = ReaderImplement>

class _EXPORT_CLASS ReaderT: virtual public TImplement {
public:
    typedef TImplement Implements;
    typedef TWhat WhatT;
    typedef TSized SizedT;
    typedef TEnd EndT;
    enum { End = VEnd };
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Read(WhatT* what, size_t size) { return 0; }
    virtual ssize_t Fill() { return 0; }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t ReadFormatted(const WhatT* format, ...) {
        ssize_t count = 0;
        va_list va;
        va_start(va, format);
        count = ReadFormattedV(format, va);
        va_end(va);
        return count;
    }
    virtual ssize_t ReadFormattedV(const WhatT* format, va_list va) {
        ssize_t count = 0;
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Count64() {
        ssize_t count = 0;
        ssize_t amount = 0;
        uint8_t carry = 0;
        uint8_t shift = 2;
        uint8_t b[2];
        do {
            if (0 > (amount = Get64(b, carry, shift))) {
                XOS_LOG_DEBUG("failed amount = " << amount << " on Get64(b, carry, shift)");
            } else {
                if (0 < (amount)) {
                    for (ssize_t i = 0; i < amount; ++i) {
                        SizedT x1 = this->DToX(b[i] >> 4), x2 = this->DToX(b[i] & 15);
                        XOS_LOG_TRACE(" x1 = " << x1 << " x2 = " << x2);
                    }
                    count += amount;
                } else {
                    XOS_LOG_DEBUG("amount = " << amount << " on Get64(b, carry, shift)");
                }
            }
        } while (0 < (amount));
        return count;
    }
    virtual ssize_t Read64(void* bytes, size_t size) {
        ssize_t count = 0;
        uint8_t* byte;
        if ((byte = (uint8_t*)(bytes)) && (0 < size)) {
            ssize_t amount;
            uint8_t b[2], carry, shift;
            for (carry = 0, shift = 2; 0 < size; size += amount, byte += amount) {
                if (0 > (amount = Get64(b, carry, shift))) {
                    XOS_LOG_DEBUG("failed amount = " << amount << " on Get64(b, carry, shift)");
                    return amount;
                } else {
                    if (0 < (amount)) {
                        for (ssize_t i = 0; i < amount; ++i) {
                            SizedT x1 = this->DToX(b[i] >> 4), x2 = this->DToX(b[i] & 15);
                            XOS_LOG_TRACE(" x1 = " << x1 << " x2 = " << x2);
                            byte[i] = b[i];
                        }
                        count += amount;
                    } else {
                        XOS_LOG_DEBUG("amount = " << amount << " on Get64(b, carry, shift)");
                        break;
                    }
                }
            }
        }
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Get64(uint8_t b[], uint8_t& carry, uint8_t& shift) {
        const uint8_t mask = ((uint8_t)-1);
        ssize_t count = 0;
        ssize_t amount;
        uint8_t n;
        int8_t d;
        SizedT x;
        if (2 == (shift)) {
            for (n = 0; n < 2;) {
                if (0 >= (amount = Read(&x, 1))) {
                    if (0 > (amount)) {
                        XOS_LOG_DEBUG("failed amount = " << amount << " on Read(&x, 1)");
                        return amount;
                    } else {
                        shift = 2;
                        if (n < 1) {
                            carry = 0;
                            return 0;
                        } else {
                            b[0] = carry;
                            carry = 0;
                            return 1;
                        }
                    }
                } else {
                    if (0 <= (d = this->B64ToD(x))) {
                        if (n < 1) {
                            carry = (((uint8_t)d) << 2);
                        } else {
                            shift += 2;
                            b[0] = (carry | (((uint8_t)d) >> 4));
                            carry = ((((uint8_t)d) & (mask >> 4)) << 4);
                            count = 1;
                        }
                        ++n;
                    }
                }
            }
        } else {
            if (4 == (shift)) {
                for (n = 0; n < 2;) {
                    if (0 >= (amount = Read(&x, 1))) {
                        if (0 > amount) {
                            XOS_LOG_DEBUG("failed amount = " << amount << " on Read(&x, 1)");
                            return amount;
                        } else {
                            b[n] = carry;
                            carry = 0;
                            shift = 2;
                            return 1;
                        }
                    } else {
                        if (0 <= (d = this->B64ToD(x))) {
                            b[n] = (carry | (((uint8_t)d) >> (6 - shift)));
                            if (n < 1) {
                                carry = ((((uint8_t)d) & (mask >> 6)) << 6);
                                shift += 2;
                            } else {
                                carry = 0;
                                shift = 2;
                                count = 2;
                            }
                            ++n;
                        }
                    }
                }
            } else {
                XOS_LOG_ERROR("unexpected shift value " << shift);
            }
        }
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef ReaderT<> Reader;

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
typedef ReaderT<char, char, int, 0, CharSequence> CharReader;
typedef ReaderT<wchar_t, wchar_t, int, 0, WCharSequence> WCharReader;
typedef ReaderT<tchar_t, tchar_t, int, 0, TCharSequence> TCharReader;

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
typedef ReaderT<BYTE, BYTE, int, 0, BYTESequence> BYTEReader;
typedef ReaderT<WORD, WORD, int, 0, WORDSequence> WORDReader;

} // namespace io
} // namespace xos 

#endif // _XOS_IO_READER_HPP 
