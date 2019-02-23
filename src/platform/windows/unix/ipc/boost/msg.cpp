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
///   File: msg.cpp
///
/// Author: $author$
///   Date: 9/5/2012
///////////////////////////////////////////////////////////////////////
#include "msg.hpp"
#include "xos/os/Logger.hpp"
#include "xos/base/Array.hpp"
#include <boost/interprocess/ipc/message_queue.hpp>
#include <boost/shared_ptr.hpp>
#include <sstream>
#include <map>

#define XOS_WINDOWS_UNIX_BOOST_MSG_KEY_PREFIX "boost_message_queue_"

class msg {
public:
    class pool: xos::Array<int> {
    public:
        int next, last;
        pool(): next(-1), last(0) {}
        virtual ~pool(){}
        int alloc(){
            if ((0 < next) && (next < last)){
                int old = next;
                next = Elements()[next];
                return old;
            } else {
                if (0 > (last)){
                    SetLength(last+1);
                    return last++;
                }
            }
            return -1;
        }
        void free(int old){
            if ((0 < old) && (old < (last))){
                Elements()[old] = next;
                next = old;
            }
        }
        static pool& Instance(){
            static pool instance;
            return instance;
        }
    };
    class map;
    class pair;

    key_t key;
    boost::shared_ptr<boost::interprocess::message_queue> q;

    msg(int __key, boost::interprocess::message_queue* __q)
    : key(__key), q(__q, destroy) {}
    msg(const msg& __msg)
    : key(__msg.key), q(__msg.q) {}

    static void destroy(boost::interprocess::message_queue* q){
        delete q;
    }
};
class msg::map: public std::map<int, msg>{
public:
    typedef std::map<int, msg> Extends;
    map(){}
    static map& Instance(){
        static map theMap;
        return theMap;
    }
};
class msg::pair: public std::pair<int, msg>{
public:
    typedef std::pair<int, msg> Extends;
    pair(int __id, msg __msg): Extends(__id, __msg){}
};

int msgget (key_t __key, int __msgflg) {
    int msqid = -1;
    boost::interprocess::message_queue* mq = 0;
    std::stringstream name(XOS_WINDOWS_UNIX_BOOST_MSG_KEY_PREFIX);
    name << __key;

    if (0 <= (msqid = msg::pool::Instance().alloc())){
        if (IPC_CREAT != (__msgflg & IPC_CREAT)){
            try {
                if ((mq  = new boost::interprocess::message_queue
                    (boost::interprocess::open_only, name.str().c_str()))){
                    msg::pair pair(msqid, msg(__key, mq));
                    msg::map::Instance().insert(pair);
                } else {
                    msg::pool::Instance().free(msqid);
                    msqid = -1;
                }
            } catch(boost::interprocess::interprocess_exception &ex) {
                XOS_LOG_ERROR("caught interprocess_exception \"" << ex.what() << "\"");
                msg::pool::Instance().free(msqid);
                msqid = -1;
            }
        }
    } else {
        XOS_LOG_ERROR("failed on msg::pool::Instance().alloc()");
    }
    return msqid;
}
ssize_t msgrcv (int __msqid, void *__msgp, size_t __msgsz, long int __msgtyp, int __msgflg) {
    ssize_t count = -1;
    return count;
}
int msgsnd (int __msqid, __const void *__msgp, size_t __msgsz, int __msgflg) {
    int count = -1;
    return count;
}
int msgctl (int __msqid, int __cmd, struct msqid_ds *__buf) {
    int err = -1;
    return err;
}