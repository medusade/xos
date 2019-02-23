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
///   File: MessageQueue.hpp
///
/// Author: $author$
///   Date: Sep 2, 2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_IPC_UNIX_MESSAGEQUEUE_HPP_
#define _XOS_IPC_UNIX_MESSAGEQUEUE_HPP_

#include "xos/base/Opened.hpp"
#include "xos/base/Attached.hpp"
#include "xos/os/Logger.hpp"
#include <sys/msg.h>

namespace xos {
namespace ipc {
namespace unix {

typedef Attached<int, int, -1> MsgAttached;
typedef Opened<int, int, -1, MsgAttached> MsgOpened;

typedef InterfaceBase MessageQueueImplement;
typedef MsgOpened MessageQueueExtend;

class EXPORT_CLASS MessageQueue: virtual public MessageQueueImplement, public MessageQueueExtend {
public:
    typedef MessageQueueImplement Implements;
    typedef MessageQueueExtend Extends;

    MessageQueue
    (AttachedT detached=(AttachedT)(Unattached), bool isOpen=false)
    : Extends(detached, isOpen){}
    virtual ~MessageQueue(){
        Error error = xos::Error::Failed;
        if (!(Closed()))
            throw(error);
    }

    virtual bool Create(key_t msgKey = IPC_PRIVATE){
        int msgFlag = IPC_CREAT | S_IRUSR | S_IWUSR;
        return Get(msgKey, msgFlag);
    }
    virtual bool Open(key_t msgKey){
        int msgFlag = 0;
        return Get(msgKey, msgFlag);
    }

    virtual bool Get(key_t msgKey, int msgFlag){
        AttachedT detached=(AttachedT)(Unattached);
        if ((AttachedT)(Unattached) != (detached = msgget(msgKey, msgFlag))){
            AttachOpened(detached);
            return true;
        } else {
            XOS_LOG_ERROR("failed on msgget()");
        }
        return false;
    }

    virtual ssize_t Snd(const void* msg, size_t msgSize, int msgFlag){
        ssize_t count = -1;
        if ((AttachedT)(Unattached) != (m_attachedTo))
        if (0 > (count = msgsnd(m_attachedTo, msg, msgSize, msgFlag)))
            XOS_LOG_ERROR("failed on msgsnd()");
        return count;
    }
    virtual ssize_t Rcv(void* msg, size_t msgSize, long int msgType, int msgFlag){
        ssize_t count = -1;
        if ((AttachedT)(Unattached) != (m_attachedTo))
        if (0 > (count = msgrcv(m_attachedTo, msg, msgSize, msgType, msgFlag)))
            XOS_LOG_ERROR("failed on msgrcv()");
        return count;
    }
};

} // namespace unix
} // namespace ipc
} // namespace xos

#endif // _XOS_IPC_UNIX_MESSAGEQUEUE_HPP_
