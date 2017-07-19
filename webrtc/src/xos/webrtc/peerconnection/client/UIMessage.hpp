///////////////////////////////////////////////////////////////////////
/// Copyright 2012, Google Inc.
///
/// Redistribution and use in source and binary forms, with or without
/// modification, are permitted provided that the following conditions are met:
/// 
///  1. Redistributions of source code must retain the above copyright notice,
///     this list of conditions and the following disclaimer.
///  2. Redistributions in binary form must reproduce the above copyright notice,
///     this list of conditions and the following disclaimer in the documentation
///     and/or other materials provided with the distribution.
///  3. The name of the author may not be used to endorse or promote products
///     derived from this software without specific prior written permission.
/// 
/// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
/// WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
/// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
/// EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
/// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
/// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
/// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
/// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
/// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
/// ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
///
///   File: UIMessage.hpp
///
/// Author: $author$
///   Date: 12/26/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_WEBRTC_PEERCONNECTION_CLIENT_UIMESSAGE_HPP
#define _XOS_WEBRTC_PEERCONNECTION_CLIENT_UIMESSAGE_HPP

#include "xos/webrtc/peerconnection/client/UserInterface.hpp"
#include "xos/os/os/Mutexes.hpp"
#include "xos/os/os/Semaphores.hpp"
#include "xos/os/os/Threads.hpp"
#include "xos/os/Logger.hpp"
#include <deque>

namespace xos {
namespace webrtc {
namespace peerconnection {
namespace client {

///////////////////////////////////////////////////////////////////////
///  Class: UIMessage
///
/// Author: $author$
///   Date: 12/26/2012
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS UIMessage {
public:
    class _EXPORT_CLASS Queue;
    class _EXPORT_CLASS Thread;
    typedef Thread* ThreadId;

    UIMessage
    (int msg_id, int msg, void* data)
    : m_msg_id(msg_id), m_msg(msg), m_data(data) 
    {}
    UIMessage
    (const UIMessage& copy)
    : m_msg_id(copy.m_msg_id), m_msg(copy.m_msg), m_data(copy.m_data) 
    {}
protected:
    int m_msg_id; int m_msg; void* m_data;
};

class _EXPORT_CLASS UIMessage::Queue {
public:
    Queue(){}
    virtual ~Queue(){}

    virtual bool Init() {
        bool isSuccess = false;
        if ((isSuccess = (m_mtx.Create())))
        {
            if (!(isSuccess = (m_sem.Create())))
                m_mtx.Destroy();
        }
        return isSuccess;
    }
    virtual bool Finish() {
        bool isSuccess = false;
        
        if (!(m_q.empty()))
            XOS_LOG_DEBUG("m_q not empty");

        isSuccess = m_sem.Destroy();

        if (!(m_mtx.Destroy()))
            isSuccess = false;
        return isSuccess;
    }

    virtual bool PostUIMessage
    (int msg_id, int msg, void* data)
    {
        UIMessage uiMsg(msg_id, msg, data);
        bool isSuccess = false;
        if ((isSuccess = (m_mtx.Lock())))
        {
            XOS_LOG_TRACE("post message...");
            m_q.push_back(uiMsg);
            m_sem.Release();
            m_mtx.Unlock();
        }
        return isSuccess;
    }
    virtual bool GetUIMessage
    (int& msg_id, int& msg, void*& data,
     int filterMin = -1, int filterMax = -1)
    {
        bool isSuccess = false;
        bool qIsEmpty;
        if ((m_mtx.Lock()))
        {
            do
            {
                if (!(qIsEmpty = m_q.empty()))
                {
                    if ((0 < filterMin) && (0 < filterMax)) {
                        Deque::iterator end = m_q.end();
                        Deque::iterator i;
                        for (qIsEmpty = true, i = m_q.begin(); i != end; ++i) {
                            UIMessage& uiMsg = *i;
                            if ((uiMsg.m_msg_id >= filterMin) && (uiMsg.m_msg_id <= filterMax)) {
                                msg_id = uiMsg.m_msg_id;
                                msg = uiMsg.m_msg;
                                data = uiMsg.m_data;
                                XOS_LOG_TRACE("...received message");
                                m_q.erase(i);
                                qIsEmpty = false;
                                break;
                            }
                        }
                    } else {
                        UIMessage& uiMsg = m_q.front();
                        msg_id = uiMsg.m_msg_id;
                        msg = uiMsg.m_msg;
                        data = uiMsg.m_data;
                        XOS_LOG_TRACE("...received message");
                        m_q.pop_front();
                    }
                }
                m_mtx.Unlock();
                if (!(isSuccess = !(qIsEmpty)))
                {
                    XOS_LOG_TRACE("waiting for message...");
                    if ((m_sem.Acquire()))
                    if ((m_mtx.Lock()))
                    {
                        XOS_LOG_TRACE("...waited for message");
                        continue;
                    }
                    return false;
                }
            }
            while((qIsEmpty));
        }
        return isSuccess;
    }
    virtual bool PeekUIMessage
    (int& msg_id, int& msg, void*& data,
     int filterMin = -1, int filterMax = -1, 
     bool dontRemove=false, int dontRemoveMin = -1, int dontRemoveMax = -1)
    {
        bool isSuccess = false;
        bool qIsEmpty;
        if ((m_mtx.Lock()))
        {
            if ((isSuccess = !(qIsEmpty = m_q.empty())))
            {
                if ((0 < filterMin) && (0 < filterMax)) {
                    Deque::iterator end = m_q.end();
                    Deque::iterator i;
                    for (isSuccess = false, i = m_q.begin(); i != end; ++i) {
                        UIMessage& uiMsg = *i;
                        if ((uiMsg.m_msg_id >= filterMin) && (uiMsg.m_msg_id <= filterMax)) {
                            msg_id = uiMsg.m_msg_id;
                            msg = uiMsg.m_msg;
                            data = uiMsg.m_data;
                            XOS_LOG_TRACE("...received message");
                            if ((0 < dontRemoveMin) && (0 < dontRemoveMax)) {
                                if ((msg_id >= dontRemoveMin) && (msg_id <= dontRemoveMax))
                                    dontRemove = true;
                            }
                            if (!(dontRemove)) {
                                m_q.erase(i);
                            }
                            isSuccess = true;
                            break;
                        }
                    }
                } else {
                    UIMessage& uiMsg = m_q.front();
                    msg_id = uiMsg.m_msg_id;
                    msg = uiMsg.m_msg;
                    data = uiMsg.m_data;
                    XOS_LOG_TRACE("...received message");
                    if ((0 < dontRemoveMin) && (0 < dontRemoveMax)) {
                        if ((msg_id >= dontRemoveMin) && (msg_id <= dontRemoveMax))
                            dontRemove = true;
                    }
                    if (!(dontRemove)) {
                        m_q.pop_front();
                    }
                }
            }
            m_mtx.Unlock();
        }
        return isSuccess;
    }

protected:
    typedef std::deque<UIMessage> Deque;
    xos::os::Mutex m_mtx;
    xos::os::Semaphore m_sem;
    Deque m_q;
};

} // namespace client 
} // namespace peerconnection 
} // namespace webrtc 
} // namespace xos 


#endif // _XOS_WEBRTC_PEERCONNECTION_CLIENT_UIMESSAGE_HPP 
        

