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
///   File: Service.hpp
///
/// Author: $author$
///   Date: 5/31/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_INET_HTTP_SERVER_MEDUSA_SERVICE_HPP
#define _XOS_INET_HTTP_SERVER_MEDUSA_SERVICE_HPP

#include "xos/inet/http/server/medusa/ServerConfig.hpp"
#include "xos/inet/http/server/medusa/request/HeadersReader.hpp"
#include "xos/inet/http/server/medusa/request/HeaderReader.hpp"
#include "xos/inet/http/server/medusa/request/LineReader.hpp"
#include "xos/inet/http/server/medusa/Processor.hpp"
#include "xos/inet/http/Response.hpp"
#include "xos/inet/http/Request.hpp"
#include "xos/network/Sockets.hpp"
#include "xos/mt/os/Thread.hpp"
#include "xos/io/Writer.hpp"
#include "xos/io/Reader.hpp"
#include "xos/base/SizedReader.hpp"

namespace xos {
namespace http {
namespace server {
namespace medusa {

typedef mt::RunImplement ServiceImplement;
typedef mt::Run ServiceExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Service
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Service: virtual public ServiceImplement, public ServiceExtend {
public:
    typedef ServiceImplement Implements;
    typedef ServiceExtend Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Service(Processor& processor, const ServerConfig& serverConfig)
    : m_processor(processor),
      m_serverConfig(serverConfig) {
    }
    virtual ~Service() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Write(Response& response, io::Writer& writer) {
        if (!(response.line().version().Length())) {
            response.line().version().protocol().Assign(XOS_HTTP_VERSION_PROTOCOL);
            response.line().version().major().Assign(XOS_HTTP_VERSION_MAJOR);
            response.line().version().minor().Assign(XOS_HTTP_VERSION_MINOR);
            response.line().version().Combine();
        }
        if (!(response.line().status().Length())) {
            response.line().status().Assign(XOS_HTTP_STATUS_OK);
            response.line().reason().Assign(XOS_HTTP_STATUS_OK_REASON);
            response.line().Combine();
        }
        if ((response.line().Length())) {
            String responseData(response.line());
            if ((response.headers().Combine(responseData))) {
                if ((response.message().Length())) {
                    responseData.Append(response.message());
                }
                XOS_LOG_DEBUG("response = \"" << responseData << "\"");
                XOS_LOG_DEBUG("write response...");
                if (0 < (writer.Write(responseData.Chars(), responseData.Length()))) {
                    XOS_LOG_DEBUG("...wrote response");
                    return true;
                } else {
                    XOS_LOG_ERROR("...failed to write response");
                }
            }
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Read(Request& request, io::Reader& reader) {
        http::Request::Line& line = request.line();
        http::Headers& headers = request.headers();
        request::LineReader lineReader;
        request::HeadersReader headersReader;
        ssize_t count;

        XOS_LOG_DEBUG("read line...");
        if (0 < (count = lineReader.Read(line, reader))) {
            XOS_LOG_DEBUG("...read line");

            XOS_LOG_DEBUG("read headers...");
            if (0 < (count = headersReader.Read(headers, reader))) {
                XOS_LOG_DEBUG("...read headers");
                return true;
            } else {
                XOS_LOG_DEBUG("...failed to read headers");
            }
        } else {
            XOS_LOG_DEBUG("...failed to read line");
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Process(Response& response, Request& request) {
        Processor& processor = GetProcessor();

        XOS_LOG_DEBUG("get path translated...");
        if ((GetPathTranslated(request))) {
            XOS_LOG_DEBUG("...got path translated");
        }

        XOS_LOG_DEBUG("get form data...");
        if ((GetFormData(request))) {
            XOS_LOG_DEBUG("...got form data");
        }

        XOS_LOG_DEBUG("get query form data...");
        if ((GetQueryFormData(request))) {
            XOS_LOG_DEBUG("...got query form data");
        }

        XOS_LOG_DEBUG("process request...");
        if ((processor.Process(response, request))) {
            XOS_LOG_DEBUG("...processed request");
            return true;
        } else {
            XOS_LOG_DEBUG("...failed to process request");
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool GetPathTranslated(Request& request) {
        const String& path = request.GetPath();
        String& pathTranslated = request.pathTranslated();

        XOS_LOG_DEBUG("path = \"" << path << "\"");
        m_serverConfig.TranslatePath(pathTranslated, path);

        XOS_LOG_DEBUG("path translated = \"" << pathTranslated << "\"");
        return true;
    }


    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool GetFormData(Request& request) {
        const String contentType = request.GetContentType();

        if (0 < (contentType.Length())) {
            XOS_LOG_DEBUG(XOS_HTTP_HEADER_NAME_CONTENT_TYPE << " = \"" << contentType << "\"");

            if (!(contentType.compare(XOS_INET_HTTP_URL_ENCODED_FORM_CONTENT_TYPE_NAME))) {

                XOS_LOG_DEBUG("get \"" << XOS_INET_HTTP_URL_ENCODED_FORM_CONTENT_TYPE_NAME << "\" form data...");
                if ((GetUrlEncodedContentFormData(request))) {
                    XOS_LOG_DEBUG("...got \"" << XOS_INET_HTTP_URL_ENCODED_FORM_CONTENT_TYPE_NAME << "\" form data");
                    return true;
                } else {
                    XOS_LOG_ERROR("...failed to get \"" << XOS_INET_HTTP_URL_ENCODED_FORM_CONTENT_TYPE_NAME << "\" form data");
                }
            }
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool GetUrlEncodedContentFormData(Request& request) {
        CharReader reader = request.GetMessageReader();
        ssize_t contentLength = request.GetContentLengthNo();
        if (0 <= (contentLength)) {
            SizedCharReader sizedReader(reader, contentLength);
            XOS_LOG_DEBUG(XOS_HTTP_HEADER_NAME_CONTENT_LENGTH << " = " << contentLength << "");
            return GetUrlEncodedContentFormData(request, sizedReader);
        }
        return GetUrlEncodedContentFormData(request, reader);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool GetUrlEncodedContentFormData(Request& request, CharReader& reader) {
        const String transferEncoding = request.GetTransferEncoding();
        if (0 < (transferEncoding.Length())) {
            XOS_LOG_DEBUG(XOS_HTTP_HEADER_NAME_TRANSFER_ENCODING << " = \"" << transferEncoding << "\"");

            if ((transferEncoding.Compare(XOS_HTTP_TRANSFER_ENCODING_CHUNKED_NAME))) {
                XOS_LOG_DEBUG("get \"" << XOS_HTTP_TRANSFER_ENCODING_CHUNKED_NAME << "\" content...");
            }
        } else {
            if ((GetUrlEncodedFormData(request, reader))) {
                return true;
            }
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool GetQueryFormData(Request& request) {
        const String& query = request.GetQuery();

        if (0 < (query.Length())) {
            StringReader reader(query);
            XOS_LOG_DEBUG("query = \"" << query << "\"");

            XOS_LOG_DEBUG("reading form from query...");
            if ((GetUrlEncodedFormData(request, reader))) {
                XOS_LOG_DEBUG("...read form from query");
            } else {
                XOS_LOG_ERROR("...failed to read form from query");
            }
            return true;
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool GetUrlEncodedFormData(Request& request, CharReader& reader) {
        Form& form = request.form();
        UrlEncodedFormReader uReader;
        XOS_LOG_DEBUG("reading form...");
        uReader.Read(reader, form);
        XOS_LOG_DEBUG("...read form");
        return true;
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
    const ServerConfig& m_serverConfig;
    Processor& m_processor;
};

} // namespace medusa 
} // namespace server 
} // namespace http 
} // namespace xos 

#endif // _XOS_INET_HTTP_SERVER_MEDUSA_SERVICE_HPP 
