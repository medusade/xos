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
///   File: Main.hpp
///
/// Author: $author$
///   Date: 4/29/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_CRYPTO_RSA_MAIN_HPP
#define _XOS_CRYPTO_RSA_MAIN_HPP

#include "xos/os/Main.hpp"
#include "xos/crypto/rsa/bn/KeyGenerator.hpp"
#include "xos/crypto/rsa/bn/PrivateKey.hpp"
#include "xos/crypto/rsa/bn/PublicKey.hpp"
#include "xos/crypto/rsa/PrivateKey.hpp"
#include "xos/crypto/rsa/PublicKey.hpp"
#include "xos/crypto/rsa/KeyReader.hpp"
#include "xos/crypto/random/Pseudo.hpp"
#include "xos/inet/asn1/Reader.hpp"
#include "xos/inet/asn1/Block.hpp"
#include "xos/inet/asn1/Type.hpp"
#include "xos/io/file/Reader.hpp"
#include "xos/io/file/Writer.hpp"
#include "xos/io/attached/Reader.hpp"
#include "xos/io/attached/Writer.hpp"
#include "xos/io/Seeked.hpp"
#include "xos/base/Attacher.hpp"
#include "xos/base/Array.hpp"

namespace xos {
namespace crypto {
namespace rsa {

#include "app/console/crypto/rsa/TestKeys.cpp"
#include "app/console/crypto/rsa/TestKeysPem.cpp"
#include "app/console/crypto/rsa/TestCert.cpp"
#include "app/console/crypto/rsa/TestCertPem.cpp"

///////////////////////////////////////////////////////////////////////
///  Class: MainImplement
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS MainImplement
: virtual public xos::MainImplement, virtual public bn::random::ReaderObserver {
public:
};
typedef xos::Main MainExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Main
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Main
: virtual asn1::ReaderEvents, virtual public MainImplement, public MainExtend {
public:
    typedef MainImplement Implements;
    typedef MainExtend Extends;
    typedef Main Derives;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Main():
        m_run(0),
        m_rsaModulusLength(128) {
        static const BYTE rsaExponentBytes[] = {0x01, 0x00, 0x01};
        m_rsaExponent.Assign(rsaExponentBytes, sizeof(rsaExponentBytes));
        m_rsaExponentBytes = m_rsaExponent.Chars();
        m_rsaExponentLength = m_rsaExponent.Length();
    }
    virtual ~Main() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    typedef int (Derives::*Runner)(int argc, char** argv, char** env);
    Runner m_run;

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int Run(int argc, char** argv, char** env) {
        int err = 0;
        if ((m_run)) {
            err = (this->*m_run)(argc, argv, env);
        } else {
            err = RunKeyTest(argc, argv, env);
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int RunPemKeyToC(int argc, char** argv, char** env) {
        int err = 0;
        rsa::KeyReader reader;
        if ((reader.Read64
            (m_rsaPublic, m_rsaPrivate, rsaPrivatePem, sizeof(rsaPrivatePem)))) {
            AttachedT<FILE*, int, 0, io::file::Writer> out(StdOut());
            BYTEArray b(m_rsaPublic.ModBytes());

            out.WriteL("///\n/// public\n///\n", 0);
            if (0 < (m_rsaPublic.GetExponentMSB(b.Elements(), b.Size()))) {
                out.WriteL("const BYTE rsaPublicE[] = {\n", 0);
                out.Write0xLn(b.Elements(), m_rsaPublic.ExpBytes());
                out.WriteL("};\n", 0);
            }
            if (0 < (m_rsaPublic.GetModulusMSB(b.Elements(), b.Size()))) {
                out.WriteL("const BYTE rsaPublicM[] = {\n", 0);
                out.Write0xLn(b.Elements(), m_rsaPublic.ModBytes());
                out.WriteL("};\n", 0);
            }

            out.WriteL("///\n/// private\n///\n", 0);
            if (0 < (b.Size())) {
                out.WriteL("const BYTE rsaPrivateD[] = {\n", 0);
                out.Write0xLn(reader.D().Elements(), m_rsaPublic.ModBytes());
                out.WriteL("};\n", 0);
            }
            if (0 < (m_rsaPrivate.GetPMSB(b.Elements(), b.Size()))) {
                out.WriteL("const BYTE rsaPrivateP[] = {\n", 0);
                out.Write0xLn(b.Elements(), m_rsaPrivate.PBytes());
                out.WriteL("};\n", 0);
            }
            if (0 < (m_rsaPrivate.GetQMSB(b.Elements(), b.Size()))) {
                out.WriteL("const BYTE rsaPrivateQ[] = {\n", 0);
                out.Write0xLn(b.Elements(), m_rsaPrivate.PBytes());
                out.WriteL("};\n", 0);
            }
            if (0 < (m_rsaPrivate.GetDmp1MSB(b.Elements(), b.Size()))) {
                out.WriteL("const BYTE rsaPrivateDmp1[] = {\n", 0);
                out.Write0xLn(b.Elements(), m_rsaPrivate.PBytes());
                out.WriteL("};\n", 0);
            }
            if (0 < (m_rsaPrivate.GetDmq1MSB(b.Elements(), b.Size()))) {
                out.WriteL("const BYTE rsaPrivateDmq1[] = {\n", 0);
                out.Write0xLn(b.Elements(), m_rsaPrivate.PBytes());
                out.WriteL("};\n", 0);
            }
            if (0 < (m_rsaPrivate.GetIqmpMSB(b.Elements(), b.Size()))) {
                out.WriteL("const BYTE rsaPrivateIqmp[] = {\n", 0);
                out.Write0xLn(b.Elements(), m_rsaPrivate.PBytes());
                out.WriteL("};\n", 0);
            }
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int RunPemKeyTest(int argc, char** argv, char** env) {
        int err = 0;
        rsa::KeyReader reader;
        if ((reader.Read64
            (m_rsaPublic, m_rsaPrivate, rsaPrivatePem, sizeof(rsaPrivatePem)))) {

            if ((m_eIn.Set(0x12, m_rsaPublic.ModBytes()))
                 && (m_eOut.Set(0x34, m_rsaPublic.ModBytes()))
                 && (m_dOut.Set(0x56, m_rsaPublic.ModBytes()))) {

                AttachedT<FILE*, int, 0, io::file::Writer> out(StdOut());

                out.WritexLn(m_eIn.Elements(), m_eIn.Length());

                out.WriteFormattedLn("public");
                m_rsaPublic(m_eOut.Elements(), m_eOut.Size(), m_eIn.Elements(), m_eIn.Length());
                out.WritexLn(m_eOut.Elements(), m_eOut.Length());

                out.WriteFormattedLn("private");
                m_rsaPrivate(m_dOut.Elements(), m_dOut.Size(), m_eOut.Elements(), m_eOut.Length());
                out.WritexLn(m_dOut.Elements(), m_dOut.Length());

                out.WriteFormattedLn("private");
                m_rsaPrivate(m_eOut.Elements(), m_eOut.Size(), m_dOut.Elements(), m_dOut.Length());
                out.WritexLn(m_eOut.Elements(), m_eOut.Length());

                out.WriteFormattedLn("public");
                m_rsaPublic(m_dOut.Elements(), m_dOut.Size(), m_eOut.Elements(), m_eOut.Length());
                out.WritexLn(m_dOut.Elements(), m_dOut.Length());
            }
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int RunPemTest(int argc, char** argv, char** env) {
        int err = 0;
        ssize_t count;
        BYTE* bytes;
        BYTEArray der;

        if (0 < (count = der.SetLength(sizeof(rsaPrivatePem))) && (bytes = der.Elements())) {
            AttachedT<const void*, int, 0, io::SeekedT<-1, io::attached::Reader> > pem(rsaPrivatePem);

            if (0 < (count = pem.Read64(bytes, count))) {
                AttachedT<const BYTE*, int, 0, io::SeekedT<0, io::attached::BYTEReader> > der(bytes);
                const BYTE* bytes;

                if ((0 < (count = der.SetLength(count))) && (bytes = der.AttachedTo())) {
                    AttachedT<FILE*, int, 0, io::file::Writer> out(StdOut());

                    out.WritexLn(bytes, count);
                    out.WriteLn();

                    asn1::Reader asn1(this);
                    asn1.Read(der);
                }
            }
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int RunKeyTest(int argc, char** argv, char** env) {
        int err = 0;
        if ((m_rsaPublic.CreateMSB
             (rsaPublicM, sizeof(rsaPublicM),
              rsaPublicE, sizeof(rsaPublicE)))) {

            if ((m_rsaPrivate.CreateMSB
                (rsaPrivateP, rsaPrivateQ,
                 rsaPrivateDmp1, rsaPrivateDmq1,
                 rsaPrivateIqmp, sizeof(rsaPrivateP)))) {

                if ((m_eIn.Set(0x12, m_rsaPublic.ModBytes()))
                     && (m_eOut.Set(0x34, m_rsaPublic.ModBytes()))
                     && (m_dOut.Set(0x56, m_rsaPublic.ModBytes()))) {

                    AttachedT<FILE*, int, 0, io::file::Writer> out(StdOut());

                    out.WritexLn(m_eIn.Elements(), m_eIn.Length());
                    out.Write64Ln(m_eIn.Elements(), m_eIn.Length());

                    out.WriteFormatted("public\n");
                    m_rsaPublic(m_eOut.Elements(), m_eOut.Size(), m_eIn.Elements(), m_eIn.Length());
                    out.WritexLn(m_eOut.Elements(), m_eOut.Length());
                    out.Write64Ln(m_eOut.Elements(), m_eOut.Length());

                    out.WriteFormatted("private\n");
                    m_rsaPrivate(m_dOut.Elements(), m_dOut.Size(), m_eOut.Elements(), m_eOut.Length());
                    out.WritexLn(m_dOut.Elements(), m_dOut.Length());

                    out.WriteFormatted("private\n");
                    m_rsaPrivate(m_eOut.Elements(), m_eOut.Size(), m_dOut.Elements(), m_dOut.Length());
                    out.WritexLn(m_eOut.Elements(), m_eOut.Length());
                    out.Write64Ln(m_eOut.Elements(), m_eOut.Length());

                    out.WriteFormatted("public\n");
                    m_rsaPublic(m_dOut.Elements(), m_dOut.Size(), m_eOut.Elements(), m_eOut.Length());
                    out.WritexLn(m_dOut.Elements(), m_dOut.Length());
                    out.Write64Ln(m_dOut.Elements(), m_dOut.Length());
                }
            }
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int RunGenerateKey(int argc, char** argv, char** env) {
        int err = 0;
        if (!(m_rsaGenerator.Generate
            (m_rsaPrivate, m_rsaPublic, m_pseudoRandom, m_rsaModulusLength,
             m_rsaExponentBytes, m_rsaExponentLength, this))) {
            printf("failed on m_rsaGenerator.Generate()\n");
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnRead(bn::BIGPRIME* n, size_t bytes) {
        Observer* delegated = ObserverDelegated(n);
        if ((delegated))
            return delegated->OnRead(n, bytes);
        printf(".");
        return bytes;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int RunAsn1CertTest(int argc, char** argv, char** env) {
        int err = 0;
        ssize_t count;

        if (0 < (count = sizeof(rsaCert))) {
            AttachedT<const BYTE*, int, 0, io::SeekedT<0, io::attached::BYTEReader> > der(rsaCert);
            const BYTE* bytes;

            if ((0 < (count = der.SetLength(count))) && (bytes = der.AttachedTo())) {
                AttachedT<FILE*, int, 0, io::file::Writer> out(StdOut());
                out.WritexLn(bytes, count);
                out.WriteLn();

                asn1::Reader asn1(this);
                asn1.Read(der);
                out.WriteLn();
            }
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1ConstructAny(io::BYTEReader& reader, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        OutLn("-- construct Any --");
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1ConstructBoolean(io::BYTEReader& reader, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        OutLn("-- construct Boolean --");
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1ConstructInteger(io::BYTEReader& reader, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        OutLn("-- construct Integer --");
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1ConstructBitString(io::BYTEReader& reader, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        OutLn("-- construct BitString --");
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1ConstructOctetString(io::BYTEReader& reader, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        OutLn("-- construct OctetString --");
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1ConstructNull(io::BYTEReader& reader, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        OutLn("-- construct Null --");
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1ConstructObjectID(io::BYTEReader& reader, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        OutLn("-- construct ObjectID --");
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1ConstructObject(io::BYTEReader& reader, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        OutLn("-- construct Object --");
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1ConstructExternal(io::BYTEReader& reader, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        OutLn("-- construct External --");
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1ConstructReal(io::BYTEReader& reader, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        OutLn("-- construct Real --");
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1ConstructEnum(io::BYTEReader& reader, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        OutLn("-- construct Enum --");
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1ConstructSequence(io::BYTEReader& reader, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        OutLn("-- construct Sequence --");
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1ConstructSet(io::BYTEReader& reader, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        OutLn("-- construct Set --");
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1ConstructNumericString(io::BYTEReader& reader, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        OutLn("-- construct NumericString --");
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1ConstructPrintableString(io::BYTEReader& reader, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        OutLn("-- construct PrintableString --");
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1ConstructTeletexString(io::BYTEReader& reader, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        OutLn("-- construct TeletexString --");
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1ConstructVideotexString(io::BYTEReader& reader, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        OutLn("-- construct VideotexString --");
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1ConstructIA5String(io::BYTEReader& reader, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        OutLn("-- construct IA5String --");
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1ConstructUTCTime(io::BYTEReader& reader, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        OutLn("-- construct UTCTime --");
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1ConstructGeneralizedTime(io::BYTEReader& reader, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        OutLn("-- construct GeneralizedTime --");
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1ConstructGraphicString(io::BYTEReader& reader, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        OutLn("-- construct GraphicString --");
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1ConstructVisibleString(io::BYTEReader& reader, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        OutLn("-- construct VisibleString --");
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1ConstructGeneralString(io::BYTEReader& reader, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        OutLn("-- construct GeneralString --");
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1Any(const BYTE& byte, size_t bytes, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        OutLn("-- Any --");
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1Boolean(const BYTE& byte, size_t bytes, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        OutLn("-- Boolean --");
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1Integer(const BYTE& byte, size_t bytes, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        OutFormattedLn("-- Integer[%d] --", bytes);
        AttachedT<FILE*, int, 0, io::file::Writer> out(StdOut());
        out.WritexLn(&byte, bytes);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1BitString(const BYTE& byte, size_t bytes, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        OutLn("-- BitString --");
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1OctetString(const BYTE& byte, size_t bytes, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        OutLn("-- OctetString --");
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1Null(const BYTE& byte, size_t bytes, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        OutLn("-- Null --");
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1ObjectID(const BYTE& byte, size_t bytes, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        OutLn("-- ObjectID --");
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1Object(const BYTE& byte, size_t bytes, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        OutLn("-- Object --");
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1External(const BYTE& byte, size_t bytes, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        OutLn("-- External --");
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1Real(const BYTE& byte, size_t bytes, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        OutLn("-- Real --");
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1Enum(const BYTE& byte, size_t bytes, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        OutLn("-- Enum --");
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1Sequence(const BYTE& byte, size_t bytes, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        OutLn("-- Sequence --");
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1Set(const BYTE& byte, size_t bytes, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        OutLn("-- Set --");
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1NumericString(const BYTE& byte, size_t bytes, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        OutLn("-- NumericString --");
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1PrintableString(const BYTE& byte, size_t bytes, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        OutLn("-- PrintableString --");
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1TeletexString(const BYTE& byte, size_t bytes, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        OutLn("-- TeletexString --");
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1VideotexString(const BYTE& byte, size_t bytes, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        OutLn("-- VideotexString --");
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1IA5String(const BYTE& byte, size_t bytes, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        OutLn("-- IA5String --");
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1UTCTime(const BYTE& byte, size_t bytes, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        OutLn("-- UTCTime --");
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1GeneralizedTime(const BYTE& byte, size_t bytes, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        OutLn("-- GeneralizedTime --");
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1GraphicString(const BYTE& byte, size_t bytes, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        OutLn("-- GraphicString --");
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1VisibleString(const BYTE& byte, size_t bytes, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        OutLn("-- VisibleString --");
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1GeneralString(const BYTE& byte, size_t bytes, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        OutLn("-- GeneralString --");
        return count;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int RunCertTo64Test(int argc, char** argv, char** env) {
        int err = 0;
        ssize_t count;

        if (0 < (count = sizeof(rsaCert))) {
            AttachedT<const BYTE*, int, 0, io::SeekedT<0, io::attached::BYTEReader> > der(rsaCert);
            const BYTE* bytes;

            if ((0 < (count = der.SetLength(count))) && (bytes = der.AttachedTo())) {
                AttachedT<FILE*, int, 0, io::file::Writer> out(StdOut());

                out.WritexLn(bytes, count);
                out.WriteLn();

                if (0 < (count = out.Write64Ln(bytes, count))) {
                    CharArray outPem;
                    char* outChars;

                    out.WriteLn();
                    if ((count <= (outPem.SetSize(count))) && (outChars = outPem.Elements())) {
                        AttachedT<char*, int, 0, io::SeekedT<0, io::attached::CharWriter> > pemOut(outChars);

                        if (count <= (pemOut.SetSize(count))) {
                            if (0 < (count = pemOut.Write64(bytes, der.Length()))) {

                                out.WriteLn(outChars, count);
                                out.WriteLn();

                                BYTEArray outDer;
                                BYTE* outBytes;

                                if ((0 < (count = outDer.SetLength(sizeof(rsaCert)))) && (outBytes = outDer.Elements())) {
                                    AttachedT<const void*, int, 0, io::SeekedT<-1, io::attached::Reader> > pemIn(outChars);

                                    if (0 < (count = pemIn.Read64(outBytes, count))) {
                                        AttachedT<const BYTE*, int, 0, io::SeekedT<0, io::attached::BYTEReader> > derIn(outBytes);

                                        out.WritexLn(outBytes, count);
                                        out.WriteLn();

                                        asn1::Reader asn1(this);
                                        asn1.Read(der);
                                        out.WriteLn();

                                        if ((0 < (count = derIn.SetLength(count))) && (bytes = derIn.AttachedTo())) {
                                            asn1::Reader asn1(this);
                                            asn1.Read(derIn);
                                            out.WriteLn();
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    crypto::random::Pseudo m_pseudoRandom;
    bn::KeyGenerator m_rsaGenerator;
    bn::PrivateKey m_rsaPrivate;
    bn::PublicKey m_rsaPublic;
    BYTEString m_rsaExponent;
    const BYTE* m_rsaExponentBytes;
    unsigned m_rsaExponentLength;
    unsigned m_rsaModulusLength;
    BYTEArray m_eIn, m_eOut, m_dOut;
};

} // namespace rsa 
} // namespace crypto 
} // namespace xos 

#endif // _XOS_CRYPTO_RSA_MAIN_HPP 
