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
///   File: XsltProcessor.cpp
///
/// Author: $author$
///   Date: 4/13/2014
///////////////////////////////////////////////////////////////////////
#include "xos/inet/http/server/path/Processor.hpp"
#include "xos/inet/http/server/xslt/libxslt/Processor.hpp"

namespace xos {
namespace http {
namespace server {
namespace xslt {
namespace libxslt {

static Processor g_theProcessor;

} // namespace libxslt
} // namespace xslt
namespace path {

static ExtensionProcessor g_xsltProcessor
(XOS_INET_HTTP_SERVER_XSLT_PROCESSOR_XSLT_FILE_EXTENSION, &xslt::libxslt::g_theProcessor);

} // namespace path
} // namespace server 
} // namespace http 
} // namespace xos 
