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
///   File: Stream.hpp
///
/// Author: $author$
///   Date: 4/17/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_IO_STREAM_HPP
#define _XOS_IO_STREAM_HPP

#include "xos/io/IStream.hpp"
#include "xos/io/OStream.hpp"

namespace xos {
namespace io {

///////////////////////////////////////////////////////////////////////
///  Class: StreamImplements
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS StreamImplements
: virtual public IStream, virtual public OStream {
public:
};
///////////////////////////////////////////////////////////////////////
///  Class: StreamT
///////////////////////////////////////////////////////////////////////
template
<typename TWhat = void, typename TSized = char,
 typename TEnd = int, TEnd VEnd = 0, class TImplement = StreamImplements>

class _EXPORT_CLASS StreamT: virtual public TImplement {
public:
    typedef TImplement Implements;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef StreamT<> Stream;

} // namespace io 
} // namespace xos 

#endif // _XOS_IO_STREAM_HPP 
