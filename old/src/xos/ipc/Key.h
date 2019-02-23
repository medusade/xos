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
///   File: Key.hpp
///
/// Author: $author$
///   Date: 11/23/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_IPC_KEY_HPP
#define _XOS_IPC_KEY_HPP
#include "xos/base/Base.hpp"

namespace xos {
namespace ipc {


typedef InterfaceBase KeyImplement;
typedef ExportBase KeyExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Key
///
/// Author: $author$
///   Date: 11/23/2013
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Key
: virtual public KeyImplement,
  public KeyExtend
{
public:
    typedef KeyImplement Implements;
    typedef KeyExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: Key
    ///
    ///       Author: $author$
    ///         Date: 11/23/2013
    ///////////////////////////////////////////////////////////////////////
    Key()
    {
    }
    virtual ~Key()
    {
    }
    virtual bool Create()
    {
        bool success = false;
        return success;
    }
    virtual bool Destroy()
    {
        bool success = false;
        return success;
    }
};


} // namespace ipc 
} // namespace xos 


#endif // _XOS_IPC_KEY_HPP 
        

