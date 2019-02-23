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
///   File: msg.h
///
/// Author: $author$
///   Date: 10/13/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_WINDOWS_UNIX_SYS_MSG_H
#define _XOS_WINDOWS_UNIX_SYS_MSG_H

#include "xos/base/Base.hpp"

typedef int key_t;
typedef int msgqnum_t;
typedef int msglen_t;

typedef struct msqid_ds {
    char m_buff[1];
} msqid_ds_t;

int msgget(key_t key, int msgflg);
int msgclose(int msqid);
int msgctl(int msqid, int cmd, struct msqid_ds *buf);
int msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg);
ssize_t	msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp, int msgflg);

namespace xos {

} // namespace xos 

#endif // _XOS_WINDOWS_UNIX_SYS_MSG_H 
