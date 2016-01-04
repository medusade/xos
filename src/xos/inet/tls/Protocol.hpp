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
///   File: Protocol.hpp
///
/// Author: $author$
///   Date: 4/26/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_TLS_PROTOCOL_HPP
#define _XOS_TLS_PROTOCOL_HPP

#include "xos/base/Base.hpp"

#define TLS_PROTOCOL_VERSION_1_0_MAJOR 3
#define TLS_PROTOCOL_VERSION_1_0_MINOR 1

#define TLS_PROTOCOL_VERSION_MAJOR TLS_PROTOCOL_VERSION_1_0_MAJOR
#define TLS_PROTOCOL_VERSION_MINOR TLS_PROTOCOL_VERSION_1_0_MINOR

#define TLS_CLIENT_LABEL "client"
#define TLS_SERVER_LABEL "server"

#define TLS_PRE_MASTER_SECRET_RANDOM_SIZE 46

#define TLS_MASTER_SECRET_SIZE 48
#define TLS_MASTER_SECRET_LABEL "master secret"

#define TLS_FINISHED_SIZE 12
#define TLS_FINISHED_LABEL "finished"

#define TLS_CLIENT_FINISHED_LABEL \
    TLS_CLIENT_LABEL \
    " " TLS_FINISHED_LABEL

#define TLS_SERVER_FINISHED_LABEL \
    TLS_SERVER_LABEL \
    " " TLS_FINISHED_LABEL

#define TLS_KEY_BLOCK_LABEL "key expansion"

namespace xos {
namespace tls {

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
enum {
    COMPRESSION_METHOD_UNKNOWN = -1,
    COMPRESSION_METHOD_NULL = 0
};

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
enum {
    MAC_ALGORITHM_UNKNOWN = -1,
    MAC_ALGORITHM_NULL,

    MAC_ALGORITHM_MD5,
    MAC_ALGORITHM_SHA1
};

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
enum {
    BULK_CIPHER_ALGORITHM_UNKNOWN = -1,
    BULK_CIPHER_ALGORITHM_NULL,

    BULK_CIPHER_ALGORITHM_RC4,
    BULK_CIPHER_ALGORITHM_RC2,
    BULK_CIPHER_ALGORITHM_DES,
    BULK_CIPHER_ALGORITHM_3DES,
    BULK_CIPHER_ALGORITHM_DES40,
    BULK_CIPHER_ALGORITHM_IDEA,

    BULK_CIPHER_ALGORITHM_AES128
};

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
enum {
    CIPHER_TYPE_UNKNOWN = -1,
    CIPHER_TYPE_STREAM,
    CIPHER_TYPE_BLOCK
};

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
enum {
    CIPHER_EXPORTABE_UNKNOWN = -1,
    CIPHER_UNEXPORTABE,
    CIPHER_EXPORTABLE
};

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
enum {
    CONNECTION_END_UNKNOWN = -1,
    CONNECTION_END_SERVER,
    CONNECTION_END_CLIENT
};

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
enum {
    HANDSHAKE_TYPE_UKNOWN = -1,

    HANDSHAKE_TYPE_HELLO_REQUEST       = 0,

    HANDSHAKE_TYPE_CLIENT_HELLO        = 1,
    HANDSHAKE_TYPE_SERVER_HELLO        = 2,

    HANDSHAKE_TYPE_CLIENT_KEY_EXCHANGE = 16,
    HANDSHAKE_TYPE_SERVER_KEY_EXCHANGE = 12,
    HANDSHAKE_TYPE_SERVER_HELLO_DONE   = 14,

    HANDSHAKE_TYPE_CERTIFICATE         = 11,
    HANDSHAKE_TYPE_CERTIFICATE_REQUEST = 13,
    HANDSHAKE_TYPE_CERTIFICATE_VERIFY  = 15,

    HANDSHAKE_TYPE_FINISHED            = 20,

    HANDSHAKE_TYPE_NONE                = 255
};

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
enum {
    CONTENT_TYPE_UNKNOWN = -1,

    CONTENT_TYPE_CHANGE_CIPHER_SPEC = 20,
    CONTENT_TYPE_ALERT              = 21,
    CONTENT_TYPE_HANDSHAKE          = 22,
    CONTENT_TYPE_APPLICATION_DATA   = 23
};

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
enum {
    CHANGE_CIPHER_SPEC_TYPE_UNKNOWN = -1,
    CHANGE_CIPHER_SPEC_TYPE_CHANGE_CIPHER_SPEC = 1
};

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
enum {
    CIPHER_SUITE_UNKNOWN = -1,

    NULL_WITH_NULL_NULL                = 0x00,

    RSA_WITH_NULL_MD5                  = 0x01,
    RSA_WITH_NULL_SHA                  = 0x02,
    RSA_EXPORT_WITH_RC4_40_MD5         = 0x03,
    RSA_WITH_RC4_128_MD5               = 0x04,
    RSA_WITH_RC4_128_SHA               = 0x05,
    RSA_EXPORT_WITH_RC2_CBC_40_MD5     = 0x06,
    RSA_WITH_IDEA_CBC_SHA              = 0x07,
    RSA_EXPORT_WITH_DES40_CBC_SHA      = 0x08,
    RSA_WITH_DES_CBC_SHA               = 0x09,
    RSA_WITH_3DES_EDE_CBC_SHA          = 0x0A,

    DH_DSS_EXPORT_WITH_DES40_CBC_SHA   = 0x0B,
    DH_DSS_WITH_DES_CBC_SHA            = 0x0C,
    DH_DSS_WITH_3DES_EDE_CBC_SHA       = 0x0D,
    DH_RSA_EXPORT_WITH_DES40_CBC_SHA   = 0x0E,
    DH_RSA_WITH_DES_CBC_SHA            = 0x0F,
    DH_RSA_WITH_3DES_EDE_CBC_SHA       = 0x10,

    DHE_DSS_EXPORT_WITH_DES40_CBC_SHA  = 0x11,
    DHE_DSS_WITH_DES_CBC_SHA           = 0x12,
    DHE_DSS_WITH_3DES_EDE_CBC_SHA      = 0x13,
    DHE_RSA_EXPORT_WITH_DES40_CBC_SHA  = 0x14,
    DHE_RSA_WITH_DES_CBC_SHA           = 0x15,
    DHE_RSA_WITH_3DES_EDE_CBC_SHA      = 0x16,

    //
    // AES RFC-3268
    //

    RSA_WITH_AES_128_CBC_SHA           = 0x2F,
    DH_DSS_WITH_AES_128_CBC_SHA        = 0x30,
    DH_RSA_WITH_AES_128_CBC_SHA        = 0x31,
    DHE_DSS_WITH_AES_128_CBC_SHA       = 0x32,
    DHE_RSA_WITH_AES_128_CBC_SHA       = 0x33,
    DH_anon_WITH_AES_128_CBC_SHA       = 0x34,

    RSA_WITH_AES_256_CBC_SHA           = 0x35,
    DH_DSS_WITH_AES_256_CBC_SHA        = 0x36,
    DH_RSA_WITH_AES_256_CBC_SHA        = 0x37,
    DHE_DSS_WITH_AES_256_CBC_SHA       = 0x38,
    DHE_RSA_WITH_AES_256_CBC_SHA       = 0x39,
    DH_anon_WITH_AES_256_CBC_SHA       = 0x3A
};

} // namespace tls
} // namespace xos 

#endif // _XOS_TLS_PROTOCOL_HPP 
