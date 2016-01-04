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
///   File: ServletProcessor.hpp
///
/// Author: $author$
///   Date: 3/1/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_HTTP_SERVER_JAVAX_SERVLETPROCESSOR_HPP
#define _XOS_HTTP_SERVER_JAVAX_SERVLETPROCESSOR_HPP

#include "xos/inet/http/server/hello/Processor.hpp"
#include "xos/inet/http/server/javax/ServletRequest.hpp"
#include "xos/inet/http/server/javax/ServletResponse.hpp"
#include "xos/jdk/javax/servlet/http/RootHttpServlet.hpp"

namespace xos {
namespace http {
namespace server {
namespace javax {

typedef hello::ProcessorImplement ServletProcessorImplement;
typedef hello::Processor ServletProcessorExtend;
///////////////////////////////////////////////////////////////////////
///  Class: ServletProcessor
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS ServletProcessor
: virtual public ServletProcessorImplement, public ServletProcessorExtend {
public:
    typedef ServletProcessorImplement Implements;
    typedef ServletProcessorExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    ServletProcessor() {
    }
    virtual ~ServletProcessor() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Process(Response& response, const Request& request) {
        ServletRequest servletReq(request);
        ServletResponse servletResp(response);
        xos::javax::servlet::http::RootHttpServlet& servlet
        = xos::javax::servlet::http::RootHttpServlet::getTheInstance();
        bool processed;

        XOS_LOG_TRACE("servlet.service(...)...");
        if (!(processed = servlet.service(servletReq, servletResp))) {
            XOS_LOG_TRACE("failed on servlet.service(...)...");
            processed = Extends::Process(response, request);
        } else {
            XOS_LOG_TRACE("...servlet.service(...)");
        }
        return processed;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace javax 
} // namespace server 
} // namespace http 
} // namespace xos 

#endif // _XOS_HTTP_SERVER_JAVAX_SERVLETPROCESSOR_HPP 
