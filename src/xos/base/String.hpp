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
///   File: String.hpp
///
/// Author: $author$
///   Date: Aug 14, 2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_STRING_HPP_
#define _XOS_STRING_HPP_

#include "xos/base/Base.hpp"
#include <string>

namespace xos {

typedef InterfaceBase StringImplement;

template 
<typename TChar, 
 class TExtend=std::basic_string<TChar>, 
 class TImplement=StringImplement>
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class EXPORT_CLASS StringT: virtual public TImplement, public TExtend {
public:
    typedef TImplement Implements;
    typedef TExtend Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    StringT(const StringT& copy): Extends(copy){}
    StringT(const Extends& copy): Extends(copy){}
    StringT(const char* chars, size_t length){
        Append(chars, length);
    }
    StringT(const char* chars){
        Append(chars);
    }
    StringT(const unsigned char* chars, size_t length){
        Append(chars, length);
    }
    StringT(const unsigned char* chars){
        Append(chars);
    }
    StringT(const wchar_t* chars, size_t length){
        Append(chars, length);
    }
    StringT(const wchar_t* chars){
        Append(chars);
    }
    StringT(int value){
        Append(value);
    }
    StringT(unsigned int value){
        Append(value);
    }
    StringT(){}
    virtual ~StringT(){}
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    StringT& Assign(const Extends& string) {
        this->clear();
        Append(string);
        return *this; }
    StringT& Assign(const char* chars, size_t length) {
        this->clear();
        Append(chars, length);
        return *this; }
    StringT& Assign(const char* chars) {
        this->clear();
        Append(chars);
        return *this; }
    StringT& Assign(const unsigned char* chars, size_t length) {
        this->clear();
        Append(chars, length);
        return *this; }
    StringT& Assign(const unsigned char* chars) {
        this->clear();
        Append(chars);
        return *this; }
    StringT& Assign(const wchar_t* chars, size_t length) {
        this->clear();
        Append(chars, length);
        return *this; }
    StringT& Assign(const wchar_t* chars) {
        this->clear();
        Append(chars);
        return *this; }

    StringT& Assign(int value) {
        this->clear();
        Append(value);
        return *this; }
    StringT& Assign(unsigned int value) {
        this->clear();
        Append(value);
        return *this; }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    StringT& Append(const Extends& string) {
        this->append(string);
        return *this; }
    StringT& Append(const char* chars, size_t length) {
        if ((chars)) {
            TChar c;
            while (0 < (length--)) {
                c = (TChar)(*chars++);
                this->append(&c, 1);
            }
        }
        return *this; }
    StringT& Append(const char* chars) {
        if ((chars)) {
            TChar c;
            while ((c = (TChar)(*chars++))) {
                this->append(&c, 1);
            }
        }
        return *this; }
    StringT& Append(const unsigned char* chars, size_t length) {
        if ((chars)) {
            TChar c;
            while (0 < (length--)) {
                c = (TChar)(*chars++);
                this->append(&c, 1);
            }
        }
        return *this; }
    StringT& Append(const unsigned char* chars) {
        if ((chars)) {
            TChar c;
            while ((c = (TChar)(*chars++))) {
                this->append(&c, 1);
            }
        }
        return *this; }
    StringT& Append(const wchar_t* chars, size_t length) {
        if ((chars)) {
            TChar c;
            while (0 < (length--)) {
                c = (TChar)(*chars++);
                this->append(&c, 1);
            }
        }
        return *this; }
    StringT& Append(const wchar_t* chars) {
        if ((chars)) {
            TChar c;
            while ((c = (TChar)(*chars++))) {
                this->append(&c, 1);
            }
        }
        return *this; }

    StringT& Append(int value) {
        TChar c = ((TChar)('0'));
        TChar s = ((TChar)('-'));
        size_t digits;
        unsigned msdValue;

        if (0 != value) {
            if (0 > value) {
                Append(&s, 1);
                value = -value;
            }
            for (digits = 0, msdValue = 0; 
                 value; value /= 10, digits++)
                msdValue = (msdValue*10) + (value%10);
            for (; msdValue; msdValue /= 10, --digits) {
                TChar d = c + (TChar)(msdValue%10);
                Append(&d, 1);
            }
            for (; digits; --digits)
                Append(&c, 1);
        } else {
            Append(&c, 1);
        }
        return *this; }
    StringT& Append(unsigned int value) {
        TChar c = ((TChar)('0'));
        size_t digits;
        unsigned msdValue;

        if (0 != value) {
            for (digits = 0, msdValue = 0; 
                 value; value /= 10, digits++)
                msdValue = (msdValue*10) + (value%10);
            for (; msdValue; msdValue /= 10, --digits) {
                TChar d = c + (TChar)(msdValue%10);
                Append(&d, 1);
            }
            for (; digits; --digits)
                Append(&c, 1);
        } else {
            Append(&c, 1);
        }
        return *this; }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    StringT& Assignx(const char* chars, size_t length, char A='a') {
        Clear();
        return AppendX((const uint8_t*)(chars), length, A);
    }
    StringT& AssignX(const char* chars, size_t length, char A='A') {
        Clear();
        return AppendX((const uint8_t*)(chars), length, A);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    StringT& Appendx(const char* chars, size_t length, char A='a') {
        return AppendX((const uint8_t*)(chars), length, A);
    }
    StringT& AppendX(const char* chars, size_t length, char A='A') {
        return AppendX((const uint8_t*)(chars), length, A);
    }

    StringT& Assignx(const uint8_t* bytes, size_t length, char A='a') {
        Clear();
        return AppendX(bytes, length, A);
    }
    StringT& AssignX(const uint8_t* bytes, size_t length, char A='A') {
        Clear();
        return AppendX(bytes, length, A);
    }

    StringT& Appendx(const uint8_t* bytes, size_t length, char A='a') {
        return AppendX(bytes, length, A);
    }
    StringT& AppendX(const uint8_t* bytes, size_t length, char A='A') {
        TChar x[2];
        uint8_t b;
        if (0 < length) {
            for (; 0 < length; --length) {
                b = (*bytes++);
                x[0] = DToX(b >> 4, A);
                x[1] = DToX(b & 15, A);
                Append(x, 2);
            }
        }
        else
        for (; (b = (*bytes++)); ) {
            x[0] = DToX(b >> 4, A);
            x[1] = DToX(b & 15, A);
            Append(x, 2);
        }
        return *this; 
    }
    StringT& AppendX(const uint8_t* bytes, size_t length, char A, char between) {
        if ((between)) {
            const uint8_t* b;
            if ((b = bytes)) {
                TChar t = (TChar)(between);
                if ((length)) {
                    do {
                        if ((b != bytes))
                            this->Append(&t, 1);
                        this->AppendX(b++, 1, A);
                    } while (--length);
                } else {
                    while (*b) {
                        if ((b != bytes))
                            this->Append(&t, 1);
                        this->AppendX(b++, 1, A);
                    }
                }
            }
        } else {
            this->AppendX(bytes, length, A);
        }
        return *this;
    }
    TChar DToX(uint8_t d, char A='A') const {
        TChar x = (TChar)(0);
        if ((0 <= d) && (9 >= d))
            x = (TChar)(('0') +  d);
        else
        if ((10 <= d) && (15 >= d))
            x = (TChar)((A) + (d - 10));
        return x;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    size_t Clear() {
        size_t count = this->length();
        this->clear();
        return count;
    }

    const TChar* Chars(size_t& length) const {
        length = this->length();
        return this->c_str();
    }
    const TChar* Chars() const {
        return this->c_str();
    }
    const TChar* HasChars(size_t& length) const {
        if (0 < (length = this->length()))
            return this->c_str();
        return 0;
    }
    const TChar* HasChars() const {
        if (0 < (this->length()))
            return this->c_str();
        return 0;
    }
    size_t Length() const  {
        return this->length();
    }

    int Compare(const StringT& to) const {
        return this->compare(to);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    int toInt() const { return ToInt(); }
    int ToInt() const {
        const TChar c0 = (TChar)('0');
        const TChar c9 = (TChar)('9');
        const TChar minus = (TChar)('-');
        bool negative = false;
        int value = 0;
        size_t length, digits, count;
        const TChar* chars;
        TChar c, d;

        if (((chars = Chars(length))) && (0 < length)) {
            for (digits = 0, count = 0; count < length; count++) {
                if (((c = chars[count]) >= c0) && (c <= c9)) {
                    value = (value*10) + (int)(d = (TChar)(c - c0));
                    if ((d != 0) || digits)
                        digits++;
                } else {
                    if ((minus == c) && !(digits))
                        negative = !negative;
                }
            }
        }
        if ((value) && (negative))
            value = -value;
        return value;
    }
    unsigned int toUnsignedInt() const { return ToUnsignedInt(); }
    unsigned int ToUnsignedInt() const {
        const TChar c0 = (TChar)('0');
        const TChar c9 = (TChar)('9');
        unsigned int value = 0;
        size_t length, digits, count;
        const TChar* chars;
        TChar c, d;

        if (((chars = Chars(length))) && (0 < length)) {
            for (digits = 0, count = 0; count < length; count++) {
                if (((c = chars[count]) >= c0) && (c <= c9)) {
                    value = (value*10) + (int)(d = (TChar)(c - c0));
                    if ((d != 0) || digits)
                        digits++;
                }
            }
        }
        return value;
    }

    StringT& toLiteral
    (StringT& to, char q = '"',
     const char* trueChars = "true",
     const char* falseChars = "false") const {
        return ToLiteral(to, q, trueChars, falseChars);
    }
    StringT& ToLiteral
    (StringT& to, char q = '"',
     const char* trueChars = "true",
     const char* falseChars = "false") const {
        const TChar cQ = (TChar)(q);
        const TChar ca = (TChar)('a');
        const TChar cf = (TChar)('f');
        const TChar cx = (TChar)('x');
        const TChar cA = (TChar)('A');
        const TChar cF = (TChar)('F');
        const TChar cX = (TChar)('X');
        const TChar c0 = (TChar)('0');
        const TChar c9 = (TChar)('9');
        const TChar minus = (TChar)('-');
        const StringT sTrue(trueChars);
        const StringT sFalse(falseChars);
        bool isQuoted = true;
        bool has0X = false;
        size_t length, count;
        const TChar* chars;
        TChar c;

        if ((!this->compare(sTrue)) || (!this->compare(sFalse))) {
            isQuoted = false;
        } else {
            if (((chars = Chars(length))) && (0 < length)) {
                for (isQuoted = false , count = 0; count < length; count++) {
                    if (((c = chars[count]) < c0) || (c > c9)) {
                        if (c != minus) {
                            if ((c != cx) && (c != cX)) {
                                if ((c < ca) || (c > cf)) {
                                    if ((c < cA) || (c > cF)) {
                                        isQuoted = true;
                                        break;
                                    } else {
                                        if ((2 > (count)) || !(has0X)) {
                                            isQuoted = true;
                                            break;
                                        }
                                    }
                                } else {
                                    if ((2 > (count)) || !(has0X)) {
                                        isQuoted = true;
                                        break;
                                    }
                                }
                            } else {
                                if ((c0 != chars[0]) || (1 != count)) {
                                    isQuoted = true;
                                    break;
                                } else {
                                    has0X = true;
                                }
                            }
                        } else {
                            if (0 < (count)) {
                                isQuoted = true;
                                break;
                            }
                        }
                    } else {
                        isQuoted = true;
                        break;
                    }
                }
            }
        }
        if ((isQuoted)) {
            to.Append(&cQ, 1);
        }
        if ((Length())) {
            to.Append(*this);
        }
        if ((isQuoted)) {
            to.Append(&cQ, 1);
        }
        return to;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    StringT& operator << (const Extends& str){ this->append(str); return *this; }
    StringT& operator << (const char* chars){ Append(chars); return *this; }
    StringT& operator << (const wchar_t* chars){ Append(chars); return *this; }
    StringT& operator << (int value){ Append(value); return *this; }
    StringT& operator << (unsigned int value){ Append(value); return *this; }

    int operator >> (int& value) {value = toInt(); return value; }
    unsigned int operator >> (unsigned int& value) {value = toUnsignedInt(); return value; }
};

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
typedef StringT<char> String;
typedef StringT<wchar_t> WString;
typedef StringT<tchar_t> TString;

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
typedef StringT<BYTE> BYTEString;
typedef StringT<WORD> WORDString;

///////////////////////////////////////////////////////////////////////
///  Class: XStringT
///////////////////////////////////////////////////////////////////////
template
<char VA = 'A', typename TChar = char,
 class TExtend = StringT<TChar>,
 class TImplement = StringImplement>

class _EXPORT_CLASS XStringT: virtual public TImplement, public TExtend {
public:
    typedef TImplement Implements;
    typedef TExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    XStringT(const uint8_t* bytes, size_t length, char A, char between) {
        this->AppendX(bytes, length, A, between);
    }
    XStringT(const uint8_t* bytes, size_t length, char A) {
        this->AppendX(bytes, length, A);
    }
    XStringT(const uint8_t* bytes, size_t length) {
        this->AppendX(bytes, length, VA);
    }
    XStringT(const XStringT& copy): Extends(copy){}
    XStringT(){}
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
typedef XStringT<'A'> XString;
typedef XStringT<'a'> xString;

} // namespace xos

#endif // _XOS_STRING_HPP_ 
