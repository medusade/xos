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
///   File: Connection.hpp
///
/// Author: $author$
///   Date: 10/17/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_WEBRTC_CLIENT_CONNECTION_HPP
#define _XOS_WEBRTC_CLIENT_CONNECTION_HPP

#include "xos/webrtc/client/ConnectionInterface.hpp"
#include "xos/webrtc/talk/base/os/SocketServer.hpp"
#include "talk/base/sigslot.h"

#define XOS_WEBRTC_CLIENT_CONNECTION_BYE_MESSAGE "BYE"
#define XOS_WEBRTC_CLIENT_CONNECTION_DEFAULT_SERVER_PORT 8888

namespace xos {
namespace webrtc {
namespace client {

typedef ConnectionInterface ConnectionImplement;
typedef sigslot::has_slots<> ConnectionExtend;

class _EXPORT_CLASS Connection: virtual public ConnectionImplement, public ConnectionExtend {
public:
    typedef ConnectionImplement Implements;
    typedef ConnectionExtend Extends;
    typedef Connection Derives;

    enum State 
    {
        NOT_CONNECTED,
        SIGNING_IN,
        CONNECTED,
        SIGNING_OUT_WAITING,
        SIGNING_OUT,
    };

    Connection();
    virtual ~Connection();

    int id() const { return my_id_; }
    bool is_connected() const { return ( my_id_ != -1); }
    bool is_not_connected() const { return (state_ == NOT_CONNECTED); }
    const Peers& peers() const { return peers_; }

    void RegisterObserver
    (ConnectionObserverInterface* callback);
    void UnregisterObserver
    (ConnectionObserverInterface* callback);

    bool Connect(const std::string& server, int port,
                 const std::string& client_name);

    bool SendToPeer(int peer_id, const std::string& message, bool doingClose=false);
    bool SendHangUp(int peer_id, bool doingClose=false);
    bool IsSendingMessage();

    bool SignOut(bool doClose=false);

protected:

    void Close();
    bool ConnectControlSocket(bool doingClose=false);
    void OnConnect(talk_base::AsyncSocket* socket);
    void OnHangingGetConnect(talk_base::AsyncSocket* socket);
    void OnMessageFromPeer(int peer_id, const std::string& message);

    // Quick and dirty support for parsing HTTP header values.
    bool GetHeaderValue(const std::string& data, size_t eoh,
                        const char* header_pattern, size_t* value);

    bool GetHeaderValue(const std::string& data, size_t eoh,
                        const char* header_pattern, std::string* value);

    // Returns true if the whole response has been read.
    bool ReadIntoBuffer(talk_base::AsyncSocket* socket, std::string* data,
                        size_t* content_length);

    void OnRead(talk_base::AsyncSocket* socket);

    void OnHangingGetRead(talk_base::AsyncSocket* socket);

    // Parses a single line entry in the form "<name>,<id>,<connected>"
    bool ParseEntry(const std::string& entry, std::string* name, int* id,
                    bool* connected);

    int GetResponseStatus(const std::string& response);

    bool ParseServerResponse(const std::string& response, size_t content_length,
                             size_t* peer_id, size_t* eoh);

    void OnClose(talk_base::AsyncSocket* socket, int err);

    static talk_base::AsyncSocket* CreateClientSocket();

    ConnectionObserverInterface* callback_;
    talk_base::SocketAddress server_address_;
    talk_base::scoped_ptr<talk_base::AsyncSocket> control_socket_;
    talk_base::scoped_ptr<talk_base::AsyncSocket> hanging_get_;
    std::string onconnect_data_;
    std::string control_data_;
    std::string notification_data_;
    std::string bye_message_;
    int default_server_port_;
    Peers peers_;
    State state_;
    int my_id_;

public:
    static void SetSocketServer(talk::base::os::SocketServer* socketServer);
    static talk::base::os::SocketServer* GetSocketServer(void);
};

} // namespace client 
} // namespace webrtc 
} // namespace xos 

#endif // _XOS_WEBRTC_CLIENT_CONNECTION_HPP 
