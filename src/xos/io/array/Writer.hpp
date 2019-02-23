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
///   Date: 5/18/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_IO_ARRAY_WRITER_HPP
#define _XOS_IO_ARRAY_WRITER_HPP

#include "xos/io/Writer.hpp"
#include "xos/io/Seeked.hpp"
#include "xos/base/Array.hpp"

namespace xos {
namespace io {
namespace array {

///////////////////////////////////////////////////////////////////////
///  Class: WriterT
///////////////////////////////////////////////////////////////////////
template
<typename TWhat = void, typename TSized = char,
 typename TEnd = int, TEnd VEnd = 0, class TArray = Array<TSized>,
 class TImplement = Sequence, class TExtend = SeekedT<0, Sequence> >

class _EXPORT_CLASS WriterT: virtual public TImplement, public TExtend {
public:
    typedef TImplement Implements;
    typedef TExtend Extends;
    typedef TWhat WhatT;
    typedef TSized SizedT;
    typedef TEnd EndT;
    enum { End = VEnd };
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    WriterT(TArray& array): m_array(array) {
    }
    virtual ~WriterT() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Write(const WhatT* what, ssize_t length = -1) {
        ssize_t told;
        if ((what) && (length) && (0 <= (told = this->Tell()))) {
            size_t size = m_array.Size();
            SizedT* sized;
            if (0 <= (length)) {
                if (size < (told + length)) {
                    if ((size = m_array.SetSize(told + length)) < (told + length))
                        length = size - told;
                }
            }
            if ((sized = (m_array.Elements())) && (0 < length)) {
                for (ssize_t i = 0; i < length; ++i) {
                    sized[i] = ((const SizedT*)what)[i];
                }
                if (0 > (told = this->Seek(told + length)))
                    return told;
                return length;
            }
        }
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    TArray& m_array;
};
typedef WriterT<> Writer;

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
typedef WriterT<char, char> CharWriter;
typedef WriterT<wchar_t, wchar_t> WCharWriter;
typedef WriterT<tchar_t, tchar_t> TCharWriter;

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
typedef WriterT<BYTE, BYTE> BYTEWriter;
typedef WriterT<WORD, WORD> WORDWriter;

} // namespace array
} // namespace io 
} // namespace xos 

#endif // _XOS_IO_ARRAY_WRITER_HPP 
