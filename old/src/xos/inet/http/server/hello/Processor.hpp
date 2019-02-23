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
///   Date: 3/2/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_INET_HTTP_SERVER_HELLO_PROCESSOR_HPP
#define _XOS_INET_HTTP_SERVER_HELLO_PROCESSOR_HPP

#include "xos/inet/http/server/Processor.hpp"
#include "xos/inet/http/server/Daemon.hpp"
#include "xos/inet/http/Content.hpp"

#define XOS_INET_HTTP_SERVER_HELLO_PATH "/hello"

namespace xos {
namespace http {
namespace server {
namespace hello {

typedef server::ProcessorImplement ProcessorImplement;
typedef server::Processor ProcessorExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Processor
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Processor
: virtual public ProcessorImplement, public ProcessorExtend {
public:
    typedef ProcessorImplement Implements;
    typedef ProcessorExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Processor() {
    }
    virtual ~Processor() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Process(Response& response, const Request& request) {
        String contentType(XOS_HTTP_CONTENT_TYPE_NAME_HTML);
        String action;
        http::Form::Field formField;

        XOS_LOG_TRACE("in...");

        if ((request.form().GetField(formField, "content_type"))) {
            const String& fieldValue(formField.GetValue());

            if (0 < (fieldValue.Length())) {
                XOS_LOG_DEBUG("content_type = \"" << fieldValue << "\"");
                contentType.Assign(fieldValue);
            }
        }

        response.headers().SetContentType(contentType);

        if ((request.form().GetField(formField, "action"))) {
            const String& fieldValue(formField.GetValue());

            if (0 < (fieldValue.Length())) {
                XOS_LOG_DEBUG("action = \"" << fieldValue << "\"");
                action.Assign(fieldValue);
            }
        }

        if (!(action.Compare("stop")))
            response.message().Assign("<b>Bye</b>");
        else response.message().Assign("<b>Hello</b>");

        if ((request.form().GetField(formField, "who"))) {
            const String& fieldValue(formField.GetValue());

            if (0 < (fieldValue.Length())) {
                XOS_LOG_DEBUG("who = \"" << fieldValue << "\"");
                response.message().Append(" <b>");
                response.message().Append(fieldValue);
                response.message().Append("</b>");
            }
        }

        if (!(action.Compare("true"))) {
            XOS_LOG_DEBUG("...return true");
            return true;
        } else
        if (!(action.Compare("false"))) {
            XOS_LOG_DEBUG("...return false");
            return false;
        } else {
            xos::Daemon& daemon = xos::Daemon::GetTheInstance();

            if (!(action.Compare("restart"))) {
                XOS_LOG_DEBUG("restart...");
                daemon.Restart();
            } else
            if (!(action.Compare("stop"))) {
                XOS_LOG_DEBUG("stop...");
                daemon.Stop();
            }
        }

        XOS_LOG_TRACE("...out");
        return true;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace hello 
} // namespace server 
} // namespace http 
} // namespace xos 

#endif // _XOS_INET_HTTP_SERVER_HELLO_PROCESSOR_HPP 
