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
///   File: Types.hpp
///
/// Author: $author$
///   Date: 1/25/2014
///////////////////////////////////////////////////////////////////////
#if !defined(_XOS_TYPES_HPP) || defined(XOS_TYPES_MEMBERS_ONLY)
#if !defined(_XOS_TYPES_HPP) && !defined(XOS_TYPES_MEMBERS_ONLY)
#define _XOS_TYPES_HPP
#endif // !defined(_XOS_TYPES_HPP) && !defined(XOS_TYPES_MEMBERS_ONLY)

#if !defined(XOS_TYPES_MEMBERS_ONLY)
#include "xos/base/Base.hpp"

#undef XOS_TYPES_EXPORT_CLASS
#define XOS_TYPES_EXPORT_CLASS _EXPORT_CLASS

#undef XOS_TYPES_MEMBERS_STATIC
#define XOS_TYPES_MEMBERS_STATIC static

#undef XOS_TYPES_MEMBERS_INLINE
#define XOS_TYPES_MEMBERS_INLINE inline

#undef XOS_TYPES_MEMBERS_CONST
#define XOS_TYPES_MEMBERS_CONST

namespace xos {

///////////////////////////////////////////////////////////////////////
///  Class: TypesT
///////////////////////////////////////////////////////////////////////
template
<class TWhat = char,
 class TEndWhat = TWhat,
 TEndWhat VEndWhat = 0,
 class TInt = int,
 class TUInt = unsigned,
 class TSize = size_t,
 class TLength = ssize_t,
 TLength VUndefinedLength = -1>

class XOS_TYPES_EXPORT_CLASS TypesT {
#else // !defined(XOS_TYPES_MEMBERS_ONLY)
#endif // !defined(XOS_TYPES_MEMBERS_ONLY)
public:
    typedef TWhat tWhat;
    typedef TEndWhat tEndWhat;
    typedef TInt tInt;
    typedef TUInt tUInt;
    typedef TSize tSize;
    typedef TLength tLength;
    enum { vEndWhat = VEndWhat };
    enum { vUndefinedLength = VUndefinedLength };

    XOS_TYPES_MEMBERS_STATIC const tWhat* Find
    (const tWhat* inWhat, tWhat what,
     tLength length=vUndefinedLength,
     tEndWhat endWhat=vEndWhat) XOS_TYPES_MEMBERS_CONST {
        if (inWhat) {
            tWhat c;
            if (0 > length) {
                while ((c = (*inWhat)) != endWhat) {
                    if (c == what)
                        return inWhat;
                    ++inWhat;
                }
            } else {
                while (0 < length) {
                    if ((c = (*inWhat)) == what)
                        return inWhat;
                    ++inWhat;
                    --length;
                }
            }
        }
        return 0;
    }
    XOS_TYPES_MEMBERS_STATIC const tWhat* FindReverse
    (const tWhat* inWhat, tWhat what,
     tLength length=vUndefinedLength,
     tEndWhat endWhat=vEndWhat) XOS_TYPES_MEMBERS_CONST {
        if (inWhat) {
            const tWhat* inWhatEnd = inWhat;
            tWhat c;
            if (0 > length) {
                while ((c = (*inWhatEnd)) != endWhat) {
                    ++inWhatEnd;
                }
            } else {
                inWhatEnd += length;
            }
            while (inWhatEnd != inWhat) {
                --inWhatEnd;
                if ((c = (*inWhatEnd)) == what)
                    return inWhatEnd;
            }
        }
        return 0;
    }

    XOS_TYPES_MEMBERS_STATIC tLength Set
    (void* toWhat, tWhat what,
     tLength length=vUndefinedLength,
     tEndWhat endWhat=vEndWhat) XOS_TYPES_MEMBERS_CONST {
        return Set((tWhat*)toWhat, what, length, endWhat);
    }

    XOS_TYPES_MEMBERS_STATIC tLength Set
    (tWhat* toWhat, tWhat what,
     tLength length=vUndefinedLength,
     tEndWhat endWhat=vEndWhat) XOS_TYPES_MEMBERS_CONST {
        tLength count = 0;
        tWhat c;

        if (toWhat)
        if (0 > length) {
            // strset
            //
            while ((c = (*toWhat)) != endWhat) {
                (*toWhat++) = what;
                count++;
            }
        } else {
            // memset
            //
            while (count < length) {
                (*toWhat++) = what;
                count++;
            }
        }
        return count;
    }

    XOS_TYPES_MEMBERS_STATIC tLength Copy
    (void* toWhat, const void* what,
     tLength length=vUndefinedLength,
     tEndWhat endWhat=vEndWhat) XOS_TYPES_MEMBERS_CONST {
        return Copy((tWhat*)toWhat, (const tWhat*)what, length, endWhat);
    }

    XOS_TYPES_MEMBERS_STATIC tLength Copy
    (tWhat* toWhat, const tWhat* what,
     tLength length=vUndefinedLength,
     tEndWhat endWhat=vEndWhat) XOS_TYPES_MEMBERS_CONST {
        tLength count = 0;
        tWhat c;

        if (toWhat && what)
        if (0 > length) {
            // strcpy
            //
            while ((c = (*what++)) != endWhat) {
                (*toWhat++) = c;
                count++;
            }
            (*toWhat) = c;
        } else {
            // memcpy
            //
            while (count < length) {
                (*toWhat++) = (c = (*what++));
                count++;
            }
        }
        return count;
    }

    XOS_TYPES_MEMBERS_STATIC tLength Count
    (const void* what,
     tEndWhat endWhat=vEndWhat,
     tLength length=vUndefinedLength) XOS_TYPES_MEMBERS_CONST {
        return Count((const tWhat*)what, endWhat, length);
    }

    XOS_TYPES_MEMBERS_STATIC tLength Count
    (const tWhat* what,
     tEndWhat endWhat=vEndWhat,
     tLength length=vUndefinedLength) XOS_TYPES_MEMBERS_CONST {
        tLength count = 0;

        if (what && ((0 > length) || (count < length)))
        while ((*what++) != (tWhat)(endWhat)) {
            if ((0 <= length) && (count >= length))
                break;
            count++;
        }
        return count;
    }

    XOS_TYPES_MEMBERS_STATIC int Compare
    (const tWhat* what,
     const tWhat* toWhat,
     tLength length=vUndefinedLength,
     tEndWhat endWhat=vEndWhat) XOS_TYPES_MEMBERS_CONST {
        int unequal = Compare
        (what, length, toWhat, length, endWhat);
        return unequal;
    }

    XOS_TYPES_MEMBERS_STATIC int Compare
    (const tWhat* what,
     tLength length,
     const tWhat* toWhat,
     tLength toLength=vUndefinedLength,
     tEndWhat endWhat=vEndWhat) XOS_TYPES_MEMBERS_CONST {
        int unequal = 0;

        if (what != toWhat)
        if (what) {
            if (toWhat) {
                if (0 > length)
                    length = Count(what, endWhat);

                if (0 > toLength)
                    toLength = Count(toWhat, endWhat);

                if (length > toLength) {
                    unequal = 1;
                    length = toLength;
                }
                else
                if (toLength > length)
                    unequal = -1;
                else
                unequal = 0;

                for (; 0 < length; --length, what++, toWhat++) {
                    if (*what > *toWhat)
                        return 1;
                    else
                    if (*what < *toWhat)
                        return -1;
                }
            }
            else
            unequal = 1;
        }
        else
        unequal = -1;

        return unequal;
    }

    XOS_TYPES_MEMBERS_STATIC int CompareCase
    (const tWhat* what,
     const tWhat* toWhat,
     tLength length=vUndefinedLength,
     tEndWhat endWhat=vEndWhat) XOS_TYPES_MEMBERS_CONST {
        int unequal = CompareCase
        (what, length, toWhat, length, endWhat);
        return unequal;
    }

    XOS_TYPES_MEMBERS_STATIC int CompareCase
    (const tWhat* what,
     tLength length,
     const tWhat* toWhat,
     tLength toLength=vUndefinedLength,
     tEndWhat endWhat=vEndWhat) XOS_TYPES_MEMBERS_CONST {
        int unequal = 0;

        if (what != toWhat)
        if (what) {
            if (toWhat) {
                if (0 > length)
                    length = Count(what, endWhat);

                if (0 > toLength)
                    toLength = Count(toWhat, endWhat);

                if (length > toLength) {
                    unequal = 1;
                    length = toLength;
                }
                else
                if (toLength > length)
                    unequal = -1;
                else
                unequal = 0;

                for (; 0 < length; --length, what++, toWhat++) {
                    tWhat u = ToLower(*what);
                    tWhat toU = ToLower(*toWhat);
                    if (u > toU)
                        return 1;
                    else
                    if (u < toU)
                        return -1;
                }
            }
            else
            unequal = 1;
        }
        else
        unequal = -1;

        return unequal;
    }

    XOS_TYPES_MEMBERS_STATIC XOS_TYPES_MEMBERS_INLINE tWhat ToLower(tWhat what) XOS_TYPES_MEMBERS_CONST {
        static const tWhat A = ((tWhat)'A');
        static const tWhat Z = ((tWhat)'Z');
        static const tWhat a = ((tWhat)'a');
        if ((what >= A) && (what <= Z))
            what = a + (what - A);
        return what;
    }
    XOS_TYPES_MEMBERS_STATIC XOS_TYPES_MEMBERS_INLINE tWhat ToUpper(tWhat what) XOS_TYPES_MEMBERS_CONST {
        static const tWhat A = ((tWhat)'A');
        static const tWhat a = ((tWhat)'a');
        static const tWhat z = ((tWhat)'z');
        if ((what >= a) && (what <= z))
            what = A + (what - a);
        return what;
    }
#if !defined(XOS_TYPES_MEMBERS_ONLY)
};

typedef TypesT<char> Chars;
typedef TypesT<tchar_t> TChars;
typedef TypesT<wchar_t> WChars;
typedef TypesT<unsigned char> UChars;

typedef TypesT<uint8_t> Bytes;
typedef TypesT<uint16_t> Words;

} // namespace xos

#else // !defined(XOS_TYPES_MEMBERS_ONLY)
#endif // !defined(XOS_TYPES_MEMBERS_ONLY)

#endif // !defined(_XOS_TYPES_HPP) || defined(XOS_TYPES_MEMBERS_ONLY)
