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
///   File: Array.hpp
///
/// Author: $author$
///   Date: Sep 9, 2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_ARRAY_HPP_
#define _XOS_ARRAY_HPP_

#include "xos/base/Base.hpp"

#define XOS_ARRAY_DEFAULT_SIZE 128

namespace xos {

template
<class TWhat, size_t VDefaultSize=XOS_ARRAY_DEFAULT_SIZE,
 class TExtend=ExportBase, class TImplement=InterfaceBase>

class EXPORT_CLASS Array: virtual public TImplement, public TExtend {
public:
    Array(ssize_t length)
    : m_elements(m_defaultElements),
      m_elementsSize(VDefaultSize),
      m_elementsLength(0) {
        SetLength(length);
    }
    Array()
    : m_elements(m_defaultElements),
      m_elementsSize(VDefaultSize),
      m_elementsLength(0) {
    }
    virtual ~Array(){
        Clear();
    }

    virtual size_t Assign(const TWhat* elements, size_t elementsLength){
        size_t count = 0;
        size_t newElementsLength;

        if ((!elements) || (!m_elements) || (elementsLength < 1))
            return 0;

        if (m_elementsSize < (newElementsLength = (elementsLength)))
        if (0 >= (count = AdjustToSize(NewSize(newElementsLength))))
            return count;
            
        CopyElements(m_elements, elements, elementsLength);
        m_elementsLength = (count = elementsLength);
        return count;
    }
    virtual size_t Append(const TWhat* elements, size_t elementsLength){
        size_t count = 0;
        size_t newElementsLength;

        if ((!elements) || (!m_elements) || (elementsLength < 1))
            return 0;

        if (m_elementsSize < (newElementsLength = (m_elementsLength + elementsLength)))
        if (0 >= (count = AdjustToSize(NewSize(newElementsLength))))
            return count;
            
        CopyElements(m_elements+m_elementsLength, elements, elementsLength);
        m_elementsLength += (count = elementsLength);
        return count;
    }
    virtual size_t Set(const TWhat& element){
        return Set(element, m_elementsLength);
    }
    virtual size_t Set(const TWhat& element, size_t elementsLength){
        size_t count = 0;
        size_t newElementsLength;

        if ((!m_elements) || (elementsLength < 1))
            return 0;

        if (m_elementsSize < (newElementsLength = (elementsLength)))
        if (0 >= (count = AdjustToSize(NewSize(newElementsLength))))
            return count;

        SetElements(m_elements, element, elementsLength);
        m_elementsLength = (count = elementsLength);
        return count;
    }
    virtual size_t Clear(){
        size_t count = m_elementsLength;
        if (m_elements)
        if (m_elements != m_defaultElements)
            delete m_elements;
        m_elements = m_defaultElements;
        m_elementsSize = VDefaultSize;
        m_elementsLength = 0;
        return count;
    }

    virtual size_t SetLength(ssize_t toLength){
        size_t toSize;

        if (!m_elements)
            return 0;

        if (0 > toLength)
            toLength = VDefaultSize;

        if ((toSize = (size_t)(toLength)) > m_elementsSize)
        if (toLength > ((ssize_t)(SetSize(toSize))))
            return 0;
        
        m_elementsLength = toLength;
        return m_elementsLength;
    }
    virtual size_t Length() const {
        return m_elementsLength;
    }
    virtual size_t SetSize(size_t toSize){
        if (toSize != m_elementsSize){
            AdjustToSize(NewSize(toSize));
        }
        return m_elementsSize;
    }
    virtual size_t Size() const {
        return m_elementsSize;
    }
    virtual TWhat* Elements() const {
        return m_elements;
    }
    virtual TWhat& operator[](size_t index) const {
        return (TWhat&)(m_elements[index]);
    }
    virtual operator TWhat*() const {
        return (TWhat*)(m_elements);
    }

protected:
    virtual size_t AdjustToSize(size_t size) {
        size_t count = 0;
        TWhat* elements;

        if (!m_elements)
            return 0;

        if (size <= m_elementsSize)
            // elements is already big enough
            //
            return m_elementsSize;

        if (!(elements = new TWhat[size]))
            return 0;

        if (m_elements)
        {
            if (m_elementsLength > 0)
                CopyElements(elements, m_elements, m_elementsLength);

            if (m_elements != m_defaultElements)
                delete m_elements;
        }

        m_elements = elements;
        m_elementsSize = size;
        count = m_elementsSize;
        return count;
    }
    virtual size_t SetElements
    (TWhat* to, const TWhat& from, size_t size) const {
        size_t count = 0;
        if ((to))
        for (count = 0; size > 0; --size, count++)
            (*to++) = from;
        return count;
    }
    virtual size_t CopyElements
    (TWhat* to, const TWhat* from, size_t size) const {
        size_t count = 0;
        if ((to) && (from))
        for (count = 0; size > 0; --size, count++)
            (*to++) = (*from++);
        return count;
    }
    virtual size_t NewSize(size_t size) const {
        size_t count = 0;
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
        count = (size = ((size/VDefaultSize)+1)*VDefaultSize);
        return count;
    }

protected:
    TWhat m_defaultElements[VDefaultSize];
    TWhat* m_elements;
    size_t m_elementsSize;
    size_t m_elementsLength;
};

typedef Array<tchar_t> TCharArray;
typedef Array<wchar_t> WCharArray;
typedef Array<char> CharArray;

typedef Array<uint8_t> ByteArray;
typedef Array<uint16_t> WordArray;
typedef Array<uint32_t> LongWordArray;

typedef Array<BYTE> BYTEArray;
typedef Array<WORD> WORDArray;

} // namespace xos

#endif // _XOS_ARRAY_HPP_ 
