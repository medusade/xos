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
///   File: Processor.hpp
///
/// Author: $author$
///   Date: 11/26/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_INET_HTTP_SERVER_PROCESSOR_HPP
#define _XOS_INET_HTTP_SERVER_PROCESSOR_HPP

#include "xos/inet/http/Response.hpp"

namespace xos {
namespace http {
namespace server {

typedef InterfaceBase ProcessorImplement;
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Processor: virtual public ProcessorImplement
{
public:
    typedef ProcessorImplement Implements;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Process(Response& response, const Request& request) {
        bool processed = false;
        Processor* delegatedToProcessor;
        if ((delegatedToProcessor = DelegatedToProcessor()))
            processed = delegatedToProcessor->Process(response, request);
        return processed;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual Processor* DelegateToProcessor(Processor* delegatedToProcessor) {
        return 0;
    }
    virtual Processor* DelegatedToProcessor() const {
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    static Processor& GetTheInstance();
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace server 
} // namespace http 
} // namespace xos 

#endif // _XOS_INET_HTTP_SERVER_PROCESSOR_HPP 
