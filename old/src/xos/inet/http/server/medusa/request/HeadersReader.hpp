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
///   File: HeadersReader.hpp
///
/// Author: $author$
///   Date: 5/26/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_INET_HTTP_SERVER_MEDUSA_REQUEST_HEADERSREADER_HPP
#define _XOS_INET_HTTP_SERVER_MEDUSA_REQUEST_HEADERSREADER_HPP

#include "xos/inet/http/server/medusa/request/HeaderReader.hpp"

namespace xos {
namespace http {
namespace server {
namespace medusa {
namespace request {

///////////////////////////////////////////////////////////////////////
///  Class: HeadersReaderT
///////////////////////////////////////////////////////////////////////
template
<typename THeaders = http::Headers,
 typename THeader = http::Header,
 class THeaderReader = HeaderReader,
 class TReader = io::Reader,
 class TExtend = ExportBase,
 class TImplement = InterfaceBase>

class _EXPORT_CLASS HeadersReaderT: virtual public TImplement, public TExtend {
public:
    typedef TImplement Implements;
    typedef TExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    HeadersReaderT() {
    }
    virtual ~HeadersReaderT() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Read(THeaders& headers, TReader& reader) {
        ssize_t count = 0;
        ssize_t amount;
        THeader header;
        THeaderReader headerReader;

        do {
            if (0 > (amount = headerReader.Read(header, reader))) {
                return amount;
            } else {
                if (0 < (amount)) {
                    headers.Add(header);
                    count += amount;
                }
            }
        } while (0 < (amount));
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

typedef HeadersReaderT<> HeadersReader;

} // namespace request 
} // namespace medusa 
} // namespace server 
} // namespace http 
} // namespace xos 

#endif // _XOS_INET_HTTP_SERVER_MEDUSA_REQUEST_HEADERSREADER_HPP 
