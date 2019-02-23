///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2015 $organization$
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
///   File: Main.hpp
///
/// Author: $author$
///   Date: 4/21/2015
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_APP_CONSOLE_CRYPTO_RSA_GENERATOR_MAIN_HPP
#define _XOS_APP_CONSOLE_CRYPTO_RSA_GENERATOR_MAIN_HPP

#include "xos/os/Main.hpp"
#include "xos/crypto/rsa/bn/KeyGenerator.hpp"
#include "xos/crypto/rsa/mp/KeyGenerator.hpp"
#include "xos/crypto/rsa/bn/random/prime/Generator.hpp"
#include "xos/crypto/rsa/mp/random/prime/Generator.hpp"
#include "xos/crypto/rsa/bn/random/Reader.hpp"
#include "xos/crypto/rsa/mp/random/Reader.hpp"
#include "xos/crypto/rsa/bn/Number.hpp"
#include "xos/crypto/rsa/mp/Number.hpp"
#include "xos/crypto/random/Pseudo.hpp"
#include "xos/io/file/Reader.hpp"
#include "xos/io/file/Writer.hpp"
#include "xos/base/Array.hpp"
#include "xos/os/Logger.hpp"
#include "app/console/crypto/rsa/generator/MainOpt.hpp"

#define XOS_APP_CONSOLE_CRYPTO_RSA_GENERATOR_EXPONTENT 0x010001
#define XOS_APP_CONSOLE_CRYPTO_RSA_GENERATOR_EXPONTENT_BITS 24

namespace xos {
namespace app {
namespace console {
namespace crypto {
namespace rsa {
namespace generator {

///////////////////////////////////////////////////////////////////////
///  Class: ReaderObserver
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS ReaderObserver
: virtual public xos::crypto::rsa::bn::random::ReaderObserver, 
  virtual public xos::crypto::rsa::mp::random::ReaderObserver {
public:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef AttachedT<FILE*, int, 0, io::file::Writer> IoWriterExtends;
///////////////////////////////////////////////////////////////////////
///  Class: IoWriter
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS IoWriter
: virtual public ReaderObserver, public IoWriterExtends {
public:
    typedef IoWriterExtends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    IoWriter(FILE* file): Extends(file), m_dot(".") {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnRead(xos::crypto::rsa::bn::BIGPRIME* n, size_t bytes) {
        this->Write(m_dot);
        return bytes;
    }
    virtual ssize_t OnRead(xos::crypto::rsa::mp::BIGPRIME* n, size_t bytes) {
        this->Write(m_dot);
        return bytes;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    const char* m_dot;
};
///////////////////////////////////////////////////////////////////////
///  Class: MainImplement
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS MainImplement
: virtual public xos::MainImplement, virtual public ReaderObserver {
public:
};
typedef xos::Main MainExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Main
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Main: virtual public MainImplement, public MainExtend {
public:
    typedef MainImplement Implements;
    typedef MainExtend Extends;
    typedef Main Derives;
    typedef char char_t;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Main()
    : m_run(0), m_runGenerate(0), m_runGeneratePrime(0),
      m_primeBits(0), m_modulusBits(0), 
      m_exponentBits(XOS_APP_CONSOLE_CRYPTO_RSA_GENERATOR_EXPONTENT_BITS), 
      m_exponent(XOS_APP_CONSOLE_CRYPTO_RSA_GENERATOR_EXPONTENT) {
    }
    virtual ~Main() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    typedef int (Derives::*Runner)(int argc, char** argv, char** env);

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int Run(int argc, char** argv, char** env) { 
        int err = 0;
        if ((m_run)) {
            err = (this->*m_run)(argc, argv, env);
        } else {
            err = Usage(argc, argv, env);
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int RunGenerate(int argc, char** argv, char** env) { 
        int err = 0;
        if ((m_runGenerate)) {
            err = (this->*m_runGenerate)(argc, argv, env);
        } else {
            err = Run_mp_Generate(argc, argv, env);
        }
        return err;
    }
    virtual int Run_mp_Generate(int argc, char** argv, char** env) { 
        int error = 0;
        IoWriter out(StdOut());
        IoWriter err(StdErr());
        unsigned bits = (m_modulusBits);
        unsigned bytes = ((bits + 7) >> 3);
        unsigned eBits = (m_exponentBits);
        unsigned eBytes = ((eBits + 7) >> 3);
        unsigned pBits = (m_primeBits);
        unsigned pBytes = ((pBits + 7) >> 3);
        BYTE exponentByte[sizeof(m_exponent)];
        BYTE* exponent = Exponent(exponentByte);
        xos::crypto::Reader& random = RandomReader();
        xos::crypto::rsa::mp::KeyGenerator g(&err);
        xos::crypto::rsa::mp::PublicKey publicKey;
        xos::crypto::rsa::mp::PrivateKey privateKey;

        if ((bytes) && (eBytes)) {
            ssize_t size = 0;

            err.WriteFormatted("Generating %d bit key...\n", bits);
            if ((g.Generate(privateKey, publicKey, random, bytes, exponent, eBytes))) {
                xos::BYTEArray a(bytes);
                BYTE* b = a.Elements();

                err.WriteFormatted("...Generated %d bit key\n", bits);
                if ((b) && (bytes == (size = publicKey.GetModulusMSB(b, bytes)))) {
                    out.WritexLn(b, bytes);
                }
                if ((eBytes == (size = publicKey.GetExponentMSB(b, eBytes)))) {
                    out.WritexLn(b, eBytes);
                }
                if ((pBytes == (size = privateKey.GetPMSB(b, pBytes)))) {
                    out.WritexLn(b, pBytes);
                }
                if ((pBytes == (size = privateKey.GetQMSB(b, pBytes)))) {
                    out.WritexLn(b, pBytes);
                }
                if ((pBytes == (size = privateKey.GetDmp1MSB(b, pBytes)))) {
                    out.WritexLn(b, pBytes);
                }
                if ((pBytes == (size = privateKey.GetDmq1MSB(b, pBytes)))) {
                    out.WritexLn(b, pBytes);
                }
                if ((pBytes == (size = privateKey.GetIqmpMSB(b, pBytes)))) {
                    out.WritexLn(b, pBytes);
                }
            }
        }
        return error;
    }
    virtual int Run_bn_Generate(int argc, char** argv, char** env) { 
        int error = 0;
        IoWriter out(StdOut());
        IoWriter err(StdErr());
        unsigned bits = (m_modulusBits);
        unsigned bytes = ((bits + 7) >> 3);
        unsigned eBits = (m_exponentBits);
        unsigned eBytes = ((eBits + 7) >> 3);
        unsigned pBits = (m_primeBits);
        unsigned pBytes = ((pBits + 7) >> 3);
        BYTE exponentByte[sizeof(m_exponent)];
        BYTE* exponent = Exponent(exponentByte);
        xos::crypto::Reader& random = RandomReader();
        xos::crypto::rsa::bn::KeyGenerator g(&err);
        xos::crypto::rsa::bn::PublicKey publicKey;
        xos::crypto::rsa::bn::PrivateKey privateKey;

        if ((bytes) && (eBytes)) {
            ssize_t size = 0;

            err.WriteFormatted("Generating %d bit key...\n", bits);
            if ((g.Generate(privateKey, publicKey, random, bytes, exponent, eBytes))) {
                xos::BYTEArray a(bytes);
                BYTE* b = a.Elements();

                err.WriteFormatted("...Generated %d bit key\n", bits);
                if ((b) && (bytes == (size = publicKey.GetModulusMSB(b, bytes)))) {
                    out.WritexLn(b, bytes);
                }
                if ((eBytes == (size = publicKey.GetExponentMSB(b, eBytes)))) {
                    out.WritexLn(b, eBytes);
                }
                if ((pBytes == (size = privateKey.GetPMSB(b, pBytes)))) {
                    out.WritexLn(b, pBytes);
                }
                if ((pBytes == (size = privateKey.GetQMSB(b, pBytes)))) {
                    out.WritexLn(b, pBytes);
                }
                if ((pBytes == (size = privateKey.GetDmp1MSB(b, pBytes)))) {
                    out.WritexLn(b, pBytes);
                }
                if ((pBytes == (size = privateKey.GetDmq1MSB(b, pBytes)))) {
                    out.WritexLn(b, pBytes);
                }
                if ((pBytes == (size = privateKey.GetIqmpMSB(b, pBytes)))) {
                    out.WritexLn(b, pBytes);
                }
            }
        }
        return error;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int RunGeneratePrime(int argc, char** argv, char** env) { 
        int err = 0;
        if ((m_runGeneratePrime)) {
            err = (this->*m_runGeneratePrime)(argc, argv, env);
        } else {
            err = Run_mp_GeneratePrime(argc, argv, env);
        }
        return err;
    }
    virtual int Run_mp_GeneratePrime(int argc, char** argv, char** env) { 
        int error = 0;
        IoWriter out(StdOut());
        IoWriter err(StdErr());
        unsigned bits = (m_primeBits);
        unsigned bytes = ((bits + 7) >> 3);
        xos::crypto::Reader& random = RandomReader();
        xos::crypto::rsa::mp::Number n(0);
        xos::crypto::rsa::mp::random::prime::Generator g(&err);

        if ((bytes) && (g.Create())) {
            ssize_t size = 0;

            err.WriteFormatted("Generating %d bit prime...\n", bits);
            if (bytes == (size = g.Generate(n, bytes, random))) {
                xos::BYTEArray a(size);
                BYTE* b = a.Elements();

                if ((b) && (bytes == (size = n.ToMSB(b, bytes)))) {
                    err.WriteFormatted("...Generated %d bit prime\n", bits);
                    out.WritexLn(b, bytes);
                }
            }
            g.Destroy();
        }
        return error;
    }
    virtual int Run_bn_GeneratePrime(int argc, char** argv, char** env) { 
        int error = 0;
        IoWriter out(StdOut());
        IoWriter err(StdErr());
        unsigned bits = (m_primeBits);
        unsigned bytes = ((bits + 7) >> 3);
        xos::crypto::Reader& random = RandomReader();
        xos::crypto::rsa::bn::Number n(0);
        xos::crypto::rsa::bn::random::prime::Generator g(&err);

        if ((bytes) && (g.Create())) {
            ssize_t size = 0;

            err.WriteFormatted("Generating %d bit prime...\n", bits);
            if (bytes == (size = g.Generate(n, bytes, random))) {
                xos::BYTEArray a(size);
                BYTE* b = a.Elements();

                err.WriteFormatted("...Generated %d bit prime\n", bits);
                if ((b) && (bytes == (size = n.ToMSB(b, bytes)))) {
                    out.WritexLn(b, bytes);
                }
            }
            g.Destroy();
        }
        return error;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual xos::crypto::Reader& RandomReader() const {
        return (xos::crypto::Reader&)m_pseudo;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual BYTE* Exponent(BYTE* byte) const {
        unsigned long exponent = m_exponent;
        if ((byte) && (exponent)) {
            unsigned long msb = 0;
            unsigned n = 0;
            for (n = 0; (exponent != 0) && (n < sizeof(m_exponent)); ++n) {
                msb = ((msb << 8) | (exponent & 255));
                exponent >>= 8;
            }
            for (unsigned i = 0; i < n; ++i) {
                byte[i] = (msb & 255);
                msb >>= 8;
            }
            return byte;
        }
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const char_t* set_Generate(const char_t* to) {
        if ((to) && (to[0])) {
            String sTo(to);
            unsigned bits = 0;
            if (0 < (bits = sTo.ToUnsignedInt())) {
                m_modulusBits = (((bits + 7) >> 3) << 3);
                m_primeBits = (m_modulusBits >> 1);
                XOS_LOG_MESSAGE_DEBUG("modulus bits = " << m_modulusBits << " (" << (m_modulusBits >> 3) << " bytes)");
                m_run = &Derives::RunGenerate;
            }
        }
        return to;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual const char_t* set_GeneratePrime(const char_t* to) {
        if ((to) && (to[0])) {
            String sTo(to);
            unsigned bits = 0;
            if (0 < (bits = sTo.ToUnsignedInt())) {
                m_primeBits = (((bits + 7) >> 3) << 3);
                XOS_LOG_MESSAGE_DEBUG("prime bits = " << m_primeBits << " (" << (m_primeBits >> 3) << " bytes)");
                m_run = &Derives::RunGeneratePrime;
            }
        }
        return to;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual const char_t* set_Bignum(const char_t* to) {
        XOS_LOG_MESSAGE_DEBUG("use BIGNUM");
        m_runGenerate = &Derives::Run_bn_Generate;
        m_runGeneratePrime = &Derives::Run_bn_GeneratePrime;
        return to;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual const char_t* set_Mpint(const char_t* to) {
        XOS_LOG_MESSAGE_DEBUG("use MP_INT");
        m_runGenerate = &Derives::Run_mp_Generate;
        m_runGeneratePrime = &Derives::Run_mp_GeneratePrime;
        return to;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual const char_t* set_RandomSeed(const char_t* to) {
        if ((to) && (to[0])) {
            String sTo(to);
            unsigned seed = 0;
            if (0 < (seed = sTo.ToUnsignedInt())) {
                XOS_LOG_MESSAGE_DEBUG("RandomSeed = " << seed << "");
                m_pseudo.Seed(seed);
            }
        }
        return to;
    }

#include "app/console/crypto/rsa/generator/MainOpt.cpp"
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    Runner m_run, m_runGenerate, m_runGeneratePrime;
    unsigned m_primeBits, m_modulusBits, m_exponentBits;
    unsigned long m_exponent;
    xos::crypto::random::Pseudo m_pseudo;
};

} // namespace generator 
} // namespace rsa 
} // namespace crypto 
} // namespace console 
} // namespace app 
} // namespace xos 

#endif // _XOS_APP_CONSOLE_CRYPTO_RSA_GENERATOR_MAIN_HPP 
