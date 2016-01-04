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
///   File: Processor.hpp
///
/// Author: $author$
///   Date: 4/13/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_INET_HTTP_SERVER_PATH_PROCESSOR_HPP
#define _XOS_INET_HTTP_SERVER_PATH_PROCESSOR_HPP

#include "xos/inet/http/server/Processors.hpp"

namespace xos {
namespace http {
namespace server {
namespace path {

typedef server::Processors::ProcessorImplement ProcessorImplement;
typedef server::Processors::Processor ProcessorExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Processor
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Processor: virtual public ProcessorImplement, public ProcessorExtend {
public:
    typedef ProcessorImplement Implements;
    typedef ProcessorExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Processor
    (const String& path, http::server::Processor* delegatedToProcessor = 0)
    : Extends(delegatedToProcessor), m_path(path) {
    }
    virtual ~Processor() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Process(Response& response, const Request& request) {
        bool processed = false;
        const String& path = request.GetPath();
        if ((Match(path))) {
            http::server::Processor* delegatedToProcessor;
            if ((delegatedToProcessor = DelegatedToProcessor()))
                processed = delegatedToProcessor->Process(response, request);
        }
        return processed;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Match(const String& path) const {
        if (!(m_path.Compare(path)))
            return true;
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    String m_path;
};

typedef ProcessorImplement ExtensionProcessorImplement;
typedef Processor ExtensionProcessorExtend;
///////////////////////////////////////////////////////////////////////
///  Class: ExtensionProcessor
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS ExtensionProcessor: virtual public ExtensionProcessorImplement, public ExtensionProcessorExtend {
public:
    typedef ExtensionProcessorImplement Implements;
    typedef ExtensionProcessorExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    ExtensionProcessor
    (const String& extension, http::server::Processor* delegatedToProcessor = 0)
    : Extends(extension, delegatedToProcessor), m_extensionSeparator('.') {
    }
    virtual ~ExtensionProcessor() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Match(const String& path) const {
        const char* chars;
        size_t length;
        if ((chars = path.Chars()) && (0 < (length = path.Length()))) {
            const char* extension = Chars::FindReverse(chars, m_extensionSeparator, length);
            if ((extension) && (extension != chars)) {
                if (!(m_path.Compare(String(extension+1))))
                    return true;
            }
        }
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    char m_extensionSeparator;
};

} // namespace path
} // namespace server 
} // namespace http 
} // namespace xos 

#endif // _XOS_INET_HTTP_SERVER_PATH_PROCESSOR_HPP 
