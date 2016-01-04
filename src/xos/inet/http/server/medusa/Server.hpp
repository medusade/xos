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
///   File: Server.hpp
///
/// Author: $author$
///   Date: 6/4/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_INET_HTTP_SERVER_MEDUSA_SERVER_HPP
#define _XOS_INET_HTTP_SERVER_MEDUSA_SERVER_HPP

#include "xos/inet/http/server/medusa/ServerConfig.hpp"
#include "xos/inet/http/server/medusa/Service.hpp"
#include "xos/inet/http/server/Processor.hpp"
#include "xos/inet/http/Response.hpp"
#include "xos/inet/http/Request.hpp"

namespace xos {
namespace http {
namespace server {
namespace medusa {

typedef InterfaceBase ServerImplement;
typedef ExportBase ServerExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Server
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Server: virtual public ServerImplement, public ServerExtend {
public:
    typedef ServerImplement Implements;
    typedef ServerExtend Extends;

    enum Exception {
        FailedToStart,
        FailedToFinish
    };

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Server(Processor& processor, const ServerConfig& config)
    : m_processor(processor), m_config(config) {
    }
    /*Server(const ServerConfig& config)
    : m_processor(Processor::GetTheInstance()), m_config(config) {
    }*/
    virtual ~Server() {
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual Processor& GetProcessor() const {
        return ((Processor&)m_processor);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    const ServerConfig& m_config;
    Processor& m_processor;
};

} // namespace medusa 
} // namespace server 
} // namespace http 
} // namespace xos 

#endif // _XOS_INET_HTTP_SERVER_MEDUSA_SERVER_HPP 
