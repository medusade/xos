///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2016 $organization$
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
///   Date: 1/7/2016
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_IO_FILE_ATTACHED_WRITER_HPP
#define _XOS_IO_FILE_ATTACHED_WRITER_HPP

#include "xos/io/file/Writer.hpp"

namespace xos {
namespace io {
namespace file {
namespace attached {

typedef AttacherT<FILE*, int, 0, file::Writer> WriterImplement;
typedef AttachedT<FILE*, int, 0, WriterImplement> WriterExtend;
///////////////////////////////////////////////////////////////////////
///  Class: WriterT
///////////////////////////////////////////////////////////////////////
template
<typename TWhat = void, typename TSized = char,
 typename TEnd = int, TEnd VEnd = 0,
 class TImplement = WriterImplement, class TExtend = WriterExtend>

class _EXPORT_CLASS WriterT: virtual public TImplement, public TExtend {
public:
    typedef TImplement Implements;
    typedef TExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    WriterT(FILE* attachedTo): Extends(attachedTo) {}
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef WriterT<> Writer;

} // namespace attached
} // namespace file
} // namespace io 
} // namespace xos 

#endif // _XOS_IO_FILE_ATTACHED_WRITER_HPP 

