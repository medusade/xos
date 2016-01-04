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
///   File: Test.hpp
///
/// Author: $author$
///   Date: 1/14/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_CRYPTO_RSA_TEST_HPP
#define _XOS_CRYPTO_RSA_TEST_HPP

#include "xos/os/Main.hpp"
#include "xos/os/FILEStream.hpp"
#include "xos/crypto/rsa/bn/PublicKey.hpp"
#include "xos/crypto/rsa/bn/PrivateKey.hpp"
#include "xos/crypto/rsa/mp/PublicKey.hpp"
#include "xos/crypto/rsa/mp/PrivateKey.hpp"
#include "app/console/crypto/rsa/TestKeys.cpp"

namespace xos {
namespace crypto {
namespace rsa {

typedef xos::Main TestExtend;
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Test: public TestExtend {
public:
    typedef TestExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Test() {
    }
    virtual ~Test() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int Run
    (int argc, char** argv, char** env) {
        int err = 0;
        CodedFILEStream o(StdOut());
        BYTE m_in[sizeof(rsaPublicM)];
        BYTE m_eout[sizeof(rsaPublicM)];
        BYTE m_dout[sizeof(rsaPublicM)];

        memset(m_in, 0x12, sizeof(m_in));
        memset(m_eout, 0x34, sizeof(m_eout));
        memset(m_dout, 0x56, sizeof(m_dout));

        o.Writex(m_in, sizeof(m_in));
        o.WriteFormatted("\n");
        o.Flush();

        try {
            xos::crypto::rsa::mp::PublicKey pub
            (rsaPublicM, sizeof(rsaPublicM), rsaPublicE, sizeof(rsaPublicE));

            xos::crypto::rsa::mp::PrivateKey prv
            (rsaPrivateP, rsaPrivateQ,
             rsaPrivateDmp1, rsaPrivateDmq1,
             rsaPrivateIqmp, sizeof(rsaPrivateP));

            pub(m_eout, sizeof(m_eout), m_in, sizeof(m_in));

            o.Writex(m_eout, sizeof(m_eout));
            o.WriteFormatted("\n");
            o.Flush();

            prv(m_dout, sizeof(m_dout), m_eout, sizeof(m_eout));

            o.Writex(m_dout, sizeof(m_dout));
            o.WriteFormatted("\n");
            o.Flush();

            prv(m_eout, sizeof(m_eout), m_dout, sizeof(m_dout));

            o.Writex(m_eout, sizeof(m_eout));
            o.WriteFormatted("\n");
            o.Flush();

            pub(m_dout, sizeof(m_dout), m_eout, sizeof(m_eout));

            o.Writex(m_dout, sizeof(m_dout));
            o.WriteFormatted("\n");
            o.Flush();
        } catch(const Error& e) {
            XOS_LOG_ERROR("caught error = " << e);
            return 1;
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace rsa 
} // namespace crypto 
} // namespace xos 

#endif // _XOS_CRYPTO_RSA_TEST_HPP 
