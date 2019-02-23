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
///   Date: 5/10/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_IO_ATTACHED_SEQUENCE_HPP
#define _XOS_IO_ATTACHED_SEQUENCE_HPP

#include "xos/io/Sequence.hpp"
#include "xos/base/Attacher.hpp"

namespace xos {
namespace io {
namespace attached {

typedef AttacherT<void*, int, 0, io::Sequence> SequenceImplement;
///////////////////////////////////////////////////////////////////////
///  Class: SequenceT
///////////////////////////////////////////////////////////////////////
template
<typename TWhat = void, typename TSized = char,
 typename TEnd = int, TEnd VEnd = 0,
 class TImplement = SequenceImplement>

class _EXPORT_CLASS SequenceT: virtual public TImplement {
public:
    typedef TImplement Implements;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t SetSize(ssize_t to) { return -1; }
    virtual ssize_t Size() const { return -1; }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t SetLength(ssize_t to) { return -1; }
    virtual ssize_t Length() const { return -1; }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef SequenceT<> Sequence;
typedef AttacherT<const void*, int, 0, io::Sequence> const_SequenceImplement;
typedef SequenceT<void, char, int, 0, const_SequenceImplement> const_Sequence;

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
typedef AttacherT<char*, int, 0, io::CharSequence> CharSequenceImplement;
typedef SequenceT<char, char, int, 0, CharSequenceImplement> CharSequence;
typedef AttacherT<const char*, int, 0, io::CharSequence> const_CharSequenceImplement;
typedef SequenceT<char, char, int, 0, const_CharSequenceImplement> const_CharSequence;

///////////////////////////////////////////////////////////////////////
typedef AttacherT<wchar_t*, int, 0, io::WCharSequence> WCharSequenceImplement;
typedef SequenceT<wchar_t, wchar_t, int, 0, WCharSequenceImplement> WCharSequence;
typedef AttacherT<const wchar_t*, int, 0, io::WCharSequence> const_WCharSequenceImplement;
typedef SequenceT<wchar_t, wchar_t, int, 0, const_WCharSequenceImplement> const_WCharSequence;

///////////////////////////////////////////////////////////////////////
typedef AttacherT<tchar_t*, int, 0, io::TCharSequence> TCharSequenceImplement;
typedef SequenceT<tchar_t, tchar_t, int, 0, TCharSequenceImplement> TCharSequence;
typedef AttacherT<const tchar_t*, int, 0, io::TCharSequence> const_TCharSequenceImplement;
typedef SequenceT<tchar_t, tchar_t, int, 0, const_TCharSequenceImplement> const_TCharSequence;

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
typedef AttacherT<BYTE*, int, 0, io::BYTESequence> BYTESequenceImplement;
typedef SequenceT<BYTE, BYTE, int, 0, BYTESequenceImplement> BYTESequence;
typedef AttacherT<const BYTE*, int, 0, io::BYTESequence> const_BYTESequenceImplement;
typedef SequenceT<BYTE, BYTE, int, 0, const_BYTESequenceImplement> const_BYTESequence;

///////////////////////////////////////////////////////////////////////
typedef AttacherT<WORD*, int, 0, io::WORDSequence> WORDSequenceImplement;
typedef SequenceT<WORD, WORD, int, 0, WORDSequenceImplement> WORDSequence;
typedef AttacherT<const WORD*, int, 0, io::WORDSequence> const_WORDSequenceImplement;
typedef SequenceT<WORD, WORD, int, 0, const_WORDSequenceImplement> const_WORDSequence;

} // namespace attached
} // namespace io 
} // namespace xos 

#endif // _XOS_IO_ATTACHED_SEQUENCE_HPP 
