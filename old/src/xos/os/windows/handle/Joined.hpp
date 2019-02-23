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
///   File: Joined.hpp
///
/// Author: $author$
///   Date: 10/9/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_OS_WINDOWS_HANDLE_JOINED_HPP
#define _XOS_OS_WINDOWS_HANDLE_JOINED_HPP

#include "xos/base/Join.hpp"
#include "xos/base/Attached.hpp"
#include "xos/os/Logger.hpp"

namespace xos {
namespace windows {
namespace handle {

typedef JoinInterface JoinedImplement;
typedef JoinedImplement::Status JoinedStatus;
typedef Attached<HANDLE, int, 0, ExportBase, JoinedImplement> JoinedExtend;

template 
<typename THANDLE = HANDLE,
 typename TStatus = JoinedStatus,
 class TExtend = JoinedExtend, 
 class TImplement = JoinedImplement>

class _EXPORT_CLASS Joined: virtual public TImplement, public TExtend {
public:
    typedef TImplement Implements;
    typedef TExtend Extends;

    Joined(THANDLE detached = 0): Extends(detached) {}
    virtual ~Joined() {}

    virtual bool Join() {
        if (TImplement::Success == (TimedJoin(INFINITE))) {
            return true; }
        return false; }
    virtual bool Separate() {
        Detach();
        return true; }

    virtual TStatus TryJoin() {
        return TimedJoin(0); }

    virtual TStatus TimedJoin(mseconds_t waitMilliSeconds) {
        HANDLE handle = 0;
        if ((handle = (HANDLE)(this->m_attachedTo))) {
            DWORD dwResult = 0;
            XOS_LOG_TRACE("wait on WaitForSingleObject()...");
            if (WAIT_OBJECT_0 == (WaitForSingleObject(handle, (DWORD)(waitMilliSeconds)))) {
                XOS_LOG_TRACE("...WAIT_OBJECT_0 on WaitForSingleObject()");
                return TImplement::Success;
            } else {
                switch(dwResult) {
                case WAIT_TIMEOUT:
                    XOS_LOG_TRACE("...WAIT_TIMEOUT on WaitForSingleObject()");
                    return TImplement::Busy;
                    break;
                case WAIT_ABANDONED:
                     XOS_LOG_ERROR("...WAIT_ABANDONED on WaitForSingleObject()");
                     return TImplement::Interrupted;
                    break;
                default:
                    XOS_LOG_ERROR("...failed on WaitForSingleObject()");
                }
            }
        }
        return TImplement::Failed; }
};

} // namespace handle 
} // namespace windows 
} // namespace xos 

#endif // _XOS_OS_WINDOWS_HANDLE_JOINED_HPP 

