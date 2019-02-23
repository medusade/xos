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
///   File: StringBase.hpp
///
/// Author: $author$
///   Date: 3/30/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_BASE_STRINGBASE_HPP
#define _XOS_BASE_STRINGBASE_HPP

#include "xos/base/Base.hpp"

#define XOS_BASE_STRINGBASE_DEFAULT_SIZE 128

namespace xos {

typedef InterfaceBase StringBaseImplement;
typedef ExportBase StringBaseExtend;
///////////////////////////////////////////////////////////////////////
///  Class: StringBaseT
///////////////////////////////////////////////////////////////////////
template 
<typename TChar, 
 size_t VDefaultSize = XOS_BASE_STRINGBASE_DEFAULT_SIZE,
 typename TEndChar = TChar, TEndChar VEndChar = 0,
 class TExtend = StringBaseExtend, class TImplement = StringBaseImplement>

class _EXPORT_CLASS StringBaseT: virtual public TImplement, public TExtend {
public:
    typedef TImplement Implements;
    typedef TExtend Extends;

    enum { vDefaultSize = VDefaultSize };
    enum { vEndChar = VEndChar };
    typedef TChar tChar;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: StringBaseT
    ///////////////////////////////////////////////////////////////////////
    StringBaseT(const TChar* chars, size_t length){
        Construct();
        append(chars, length);
    }
    StringBaseT(const TChar* chars){
        Construct();
        append(chars);
    }
    StringBaseT(const StringBaseT& copy) {
        Construct();
        append(copy.c_str(), copy.length());
    }
    StringBaseT(){
        Construct();
    }
    virtual ~StringBaseT(){
        if ((m_writeBuffer != m_defaultBuffer))
        if ((m_writeBuffer) && (m_freeBuffer))
            _free_buffer(m_writeBuffer);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    StringBaseT& assign(const TChar* chars, size_t length) {
        clear();
        return append(chars, length);
    }
    StringBaseT& assign(const TChar* chars) {
        clear();
        return append(chars);
    }
    StringBaseT& assign(const StringBaseT& copy) {
        clear();
        return append(copy.c_str(), copy.length());
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    StringBaseT& append(const TChar* chars, size_t length) {
        if ((chars) && (0 < length)) {
            size_t newSize = (m_tell+length);
            if (m_size <= newSize) {
                if (m_fixedSize)
                    length = m_size-m_tell;
                else
                if (!(_adjust_to_size(_new_size_of(newSize))))
                    length = 0;
            }
            if (length) {
                _copy_to(m_writeBuffer+m_tell, chars, length);
                if ((m_tell += length) > m_length)
                if ((m_length = m_tell) < m_size)
                    m_writeBuffer[m_tell] = (tChar)(vEndChar);
            }
        }
        return *this;
    }
    StringBaseT& append(const TChar* chars) {
        return append(chars, _length_of(chars));
    }
    StringBaseT& append(const StringBaseT& copy) {
        return append(copy.c_str(), copy.length());
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    StringBaseT& clear() {
        if ((m_writeBuffer))
        if (m_size > (m_length = (m_tell = 0)))
            m_writeBuffer[m_tell] = (tChar)(vEndChar);
        return *this;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int compare(const StringBaseT& to) {
        return compare(to.c_str(), to.length());
    }
    virtual int compare(const tChar* toChars, size_t toLength) {
        int unequal = 2;
        const tChar* thisChars;
        tChar toChar, thisChar;
        size_t thisLength;
        ssize_t lendiff;

        if (!(thisChars = (c_str())))
            return (toChars)?(-1):(1);

        if (0 < (lendiff = (toLength - (thisLength = length())))) {
            toLength = thisLength;
            unequal = -1;
        }
        else if (lendiff)
                unequal = 1;
 
        if (toLength > 0)
        do {
            if ((thisChar = *(thisChars++)) > (toChar = *(toChars++)))
                return 1;
            else
            if (thisChar < toChar)
                return -1;
        } while (--toLength > 0);

        return unequal;
    }
    virtual int compare(const tChar* toChars) {
        return compare(toChars, _length_of(toChars));
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual StringBaseT& operator = (const StringBaseT& copy) {
        assign(copy.c_str(), copy.length());
        return *this;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    TChar* str() const {
        return m_writeBuffer;
    }
    const TChar* c_str() const {
        return m_readBuffer;
    }
    virtual size_t length() const {
        return m_length;
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void Construct() {
        m_freeBuffer = (false);
        m_fixedSize = (false);
        m_size = (vDefaultSize);
        m_length = (0);
        m_tell = (0);
        m_readBuffer = (m_defaultBuffer);
        m_writeBuffer = (m_defaultBuffer);
    }
    virtual size_t adjust_size(size_t newSize) {
        if (!m_writeBuffer)
            return 0;

        if (m_size < (newSize))
        if (m_fixedSize)
            return 0;
        else 
        if (1 > (_adjust_to_size(_new_size_of(newSize))))
            return 0;

        return m_size;
    }
    virtual size_t _adjust_to_size(size_t size) {
        bool freeBuffer;
        tChar* buffer;

        if (!m_writeBuffer)
            return 0;

        if (size <= m_size)
            return m_size;

        if (!(freeBuffer = m_freeBuffer))
            m_freeBuffer = true;

        if (!(buffer = _alloc_buffer(size))) {
            m_freeBuffer = freeBuffer;
            return 0;
        }

        if (m_writeBuffer) {
            if (m_length > 0)
                _copy_to(buffer, m_writeBuffer, m_length);

            if ((m_writeBuffer != m_defaultBuffer) && (freeBuffer))
                _free_buffer(m_writeBuffer);
        }

        m_writeBuffer = buffer;
        m_readBuffer = buffer;
        m_size = size;
        return m_size;
    }
    virtual tChar* _alloc_buffer(size_t size) const {
        tChar* chars = new tChar[size];
        return chars;
    }
    virtual void _free_buffer(tChar* buffer) const {
        delete[] buffer;
    }
    virtual size_t _new_size_of(size_t size) const {
        // Lets increase the buffer size by default buffer
        // sized chunks. Note the desired new size is always
        // needed size + 1. The size in chunks is calculated
        // as (new size + (chunk size - 1)) / chunk size.
        // since new size = needed size + 1 then we have
        // chunks = (needed size + chunk size) / chunk size.
        // Finally we need bytes which is chunks * chunk size
        // which can be reduced to
        // ((needed size / chunk size) + 1) * chunk size
        //
        return ((size/vDefaultSize)+1)*vDefaultSize;
    }
    virtual size_t _copy_to(TChar* to, const TChar* from, size_t size) const {
		size_t length;
        for (length = size; size; --size)
            (*to++) = (*from++);
		return length;
    }
    virtual size_t _length_of(const TChar* chars) const {
        const tChar endChar((tChar)(vEndChar));
        size_t length;

        for (length = 0; (*chars != endChar); chars++)
            length++;
        return length;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    bool m_freeBuffer;
    bool m_fixedSize;

    size_t m_size;
    size_t m_length;
    size_t m_tell;

    const tChar* m_readBuffer;
    tChar* m_writeBuffer;
    tChar m_defaultBuffer[vDefaultSize];
};

typedef StringBaseT<char> StringBase;
typedef StringBaseT<wchar_t> WStringBase;
typedef StringBaseT<tchar_t> TStringBase;

typedef StringBaseT<uint8_t> ByteStringBase;
typedef StringBaseT<uint16_t> WordtSringBase;
typedef StringBaseT<uint32_t> LongWordSringBase;

} // namespace xos

#endif // _XOS_BASE_STRINGBASE_HPP 
