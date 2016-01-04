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
///   File: Process.hpp
///
/// Author: $author$
///   Date: 9/21/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_MT_WINDOWS_CRT_PROCESS_HPP
#define _XOS_MT_WINDOWS_CRT_PROCESS_HPP
#include "xos/mt/Waiter.hpp"

namespace xos {
namespace mt {
namespace windows {
namespace crt {


///////////////////////////////////////////////////////////////////////
///  Class: ProcessT
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS ProcessT: virtual public TImplement,public TExtend {
public:
    typedef TImplement Implements;
    typedef TExtend Extends;
    ProcessT() {
    }
    virtual ~ProcessT() {
    }
};


} // namespace crt 
} // namespace windows 
} // namespace mt 
} // namespace xos 


#endif // _XOS_MT_WINDOWS_CRT_PROCESS_HPP 
        

