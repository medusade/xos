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
///   File: Mutex.hpp
///
/// Author: $author$
///   Date: 4/15/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_MT_MUTEX_HPP
#define _XOS_MT_MUTEX_HPP

#include "xos/mt/Locker.hpp"
#include "xos/base/Creator.hpp"

namespace xos {
namespace mt {

///////////////////////////////////////////////////////////////////////
///  Class: MutexImplements
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS MutexImplements
: virtual public Locker, virtual public Creator {
public:
};
///////////////////////////////////////////////////////////////////////
///  Class: MutexT
///////////////////////////////////////////////////////////////////////
template <class TImplement = MutexImplements>
class _EXPORT_CLASS MutexT: virtual public TImplement {
public:
    typedef TImplement Implements;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Create(bool initallyLocked) = 0;
    virtual bool Create() = 0;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef MutexT<> Mutex;

} // namespace mt 
} // namespace xos 

#endif // _XOS_MT_MUTEX_HPP 
