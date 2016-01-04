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
///   File: Thread.hpp
///
/// Author: $author$
///   Date: 4/15/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_MT_MACOSX_THREAD_HPP
#define _XOS_MT_MACOSX_THREAD_HPP

#include "xos/mt/unix/Thread.hpp"

namespace xos {
namespace mt {
namespace macosx {

///////////////////////////////////////////////////////////////////////
///  Class: ThreadT
///////////////////////////////////////////////////////////////////////
template
<class TAttached = unix::ThreadAttachedT,
 class TExtend = unix::Thread,
 class TImplement = unix::ThreadImplements>

class _EXPORT_CLASS ThreadT: virtual public TImplement, public TExtend {
public:
    typedef TImplement Implements;
    typedef TExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    ThreadT(TAttached attachedTo, bool isCreated)
    : Extends(attachedTo, isCreated) {
    }
    ThreadT(TAttached attachedTo)
    : Extends(attachedTo) {
    }
    ThreadT(Run& run, bool initiallySuspended)
    : Extends(run, initiallySuspended) {
    }
    ThreadT(bool initiallySuspended): Extends(initiallySuspended) {
    }
    ThreadT(Run& run): Extends(run) {
    }
    ThreadT() {
    }
    virtual ~ThreadT() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef ThreadT<> Thread;

} // namespace macosx 
} // namespace mt 
} // namespace xos 

#endif // _XOS_MT_MACOSX_THREAD_HPP 
