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
///   File: Processors.hpp
///
/// Author: $author$
///   Date: 4/13/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_INET_HTTP_SERVER_PROCESSORS_HPP
#define _XOS_INET_HTTP_SERVER_PROCESSORS_HPP

#include "xos/inet/http/server/Processor.hpp"

namespace xos {
namespace http {
namespace server {

typedef Processor ProcessorsImplement;
typedef ExportBase ProcessorsExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Processors
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Processors: virtual public ProcessorsImplement, public ProcessorsExtend {
public:
    typedef ProcessorsImplement Implements;
    typedef ProcessorsExtend Extends;

    typedef http::server::Processor ProcessorImplement;
    typedef ExportBase ProcessorExtend;
    ///////////////////////////////////////////////////////////////////////
    ///  Class: Processor
    ///////////////////////////////////////////////////////////////////////
    class _EXPORT_CLASS Processor: virtual public ProcessorImplement, public ProcessorExtend {
    public:
        typedef ProcessorImplement Implements;
        typedef ProcessorExtend Extends;
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        Processor(http::server::Processor* delegatedToProcessor = 0)
        : m_delegatedToProcessor(delegatedToProcessor) {
            Add();
        }
        virtual ~Processor() {
            Remove();
        }
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        virtual bool Add();
        virtual bool Remove();
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        virtual http::server::Processor* DelegateToProcessor(http::server::Processor* delegatedToProcessor) {
            m_delegatedToProcessor = delegatedToProcessor;
            return m_delegatedToProcessor;
        }
        virtual http::server::Processor* DelegatedToProcessor() const {
            return m_delegatedToProcessor;
        }
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
    protected:
        http::server::Processor* m_delegatedToProcessor;
    };

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Processors() {
    }
    virtual ~Processors() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Process(Response& response, const Request& request);
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace server 
} // namespace http 
} // namespace xos 

#endif // _XOS_INET_HTTP_SERVER_PROCESSORS_HPP 
