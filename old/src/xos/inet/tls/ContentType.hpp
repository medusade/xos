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
///   File: ContentType.hpp
///
/// Author: $author$
///   Date: 4/27/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_TLS_CONTENTTYPE_HPP
#define _XOS_TLS_CONTENTTYPE_HPP

#include "xos/inet/tls/Base.hpp"

namespace xos {
namespace tls {

/* RFC 2246
    enum {
        change_cipher_spec(20), alert(21), handshake(22),
        application_data(23), (255)
    } ContentType;
*/

typedef uint8_t ContentType;

} // namespace tls
} // namespace xos 

#endif // _XOS_TLS_CONTENTTYPE_HPP
