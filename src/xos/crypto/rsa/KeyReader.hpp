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
///   File: KeyReader.hpp
///
/// Author: $author$
///   Date: 5/18/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_CRYPTO_RSA_KEYREADER_HPP
#define _XOS_CRYPTO_RSA_KEYREADER_HPP

#include "xos/crypto/rsa/PrivateKey.hpp"
#include "xos/crypto/rsa/PublicKey.hpp"
#include "xos/crypto/rsa/Key.hpp"
#include "xos/inet/asn1/Reader.hpp"
#include "xos/io/attached/Reader.hpp"
#include "xos/io/attached/Writer.hpp"
#include "xos/io/array/Writer.hpp"
#include "xos/io/Seeked.hpp"
#include "xos/base/Attacher.hpp"
#include "xos/base/Array.hpp"

namespace xos {
namespace crypto {
namespace rsa {

///////////////////////////////////////////////////////////////////////
///  Class: KeyReaderImplement
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS KeyReaderImplement: virtual public asn1::ReaderEvents {
};
typedef ExportBase KeyReaderExtend;
///////////////////////////////////////////////////////////////////////
///  Class: KeyReader
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS KeyReader
: virtual public KeyReaderImplement, public KeyReaderExtend {
public:
    typedef KeyReaderImplement Implements;
    typedef KeyReaderExtend Extends;
    typedef KeyReader Derives;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    KeyReader()
    : m_onAsn1Sequence(0), m_onAsn1Integer(0),
      m_onAsn1Construct(0), m_onAsn1Primative(0) {
    }
    virtual ~KeyReader() {
    }
    ///////////////////////////////////////////////////////////////////////
    /// -----BEGIN RSA PUBLIC KEY-----
    /// BASE64 ENCODED DATA (DER RSAPublicKey)
    /// -----END RSA PUBLIC KEY-----
    ///////////////////////////////////////////////////////////////////////
    virtual bool ReadPem
    (PublicKeyImplement& publicKey,
     const char* pemChars, ssize_t length = -1) {
        if ((pemChars) && (length)) {
        }
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    /// -----BEGIN RSA PRIVATE KEY-----
    /// BASE64 ENCODED DATA (DER RSAPrivateKey)
    /// -----END RSA PRIVATE KEY-----
    ///////////////////////////////////////////////////////////////////////
    virtual bool ReadPem
    (PublicKeyImplement& publicKey,
     PrivateKeyImplement& privateKey,
     const char* pemChars, ssize_t length = -1) {
        if ((pemChars) && (length)) {
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    /// BASE64 ENCODED DATA (DER RSAPublicKey)
    ///////////////////////////////////////////////////////////////////////
    virtual bool Read64
    (PublicKeyImplement& publicKey,
     const char* base64Chars, ssize_t length = -1) {
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    /// BASE64 ENCODED DATA (DER RSAPrivateKey)
    ///////////////////////////////////////////////////////////////////////
    virtual bool Read64
    (PublicKeyImplement& publicKey,
     PrivateKeyImplement& privateKey,
     const char* base64Chars, ssize_t length = -1) {
        if ((base64Chars) && (0 < length)) {
            AttachedT<const void*, int, 0, io::SeekedT<-1, io::attached::Reader> > base64(base64Chars);
            ssize_t count;

            if ((0 < (count = base64.Count64())) && (0 <= (base64.Seek(0)))) {
                BYTEArray byteArray;
                BYTE* bytes;
                size_t size;

                if ((0 < (size = byteArray.SetLength(count))) && (bytes = byteArray.Elements())) {

                    if (0 < (count = base64.Read64(bytes, size))) {
                        return ReadDer(publicKey, privateKey, bytes, size);
                    }
                }
            }
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    /// DER RSAPublicKey ::= SEQUENCE {
    ///     modulus           INTEGER,  -- n
    ///     publicExponent    INTEGER   -- e
    /// }
    ///////////////////////////////////////////////////////////////////////
    virtual bool ReadDer
    (PublicKeyImplement& publicKey,
     const BYTE* derBytes, size_t length) {
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    /// DER RSAPrivateKey ::= SEQUENCE {
    ///   version           Version,
    ///   modulus           INTEGER,  -- n
    ///   publicExponent    INTEGER,  -- e
    ///   privateExponent   INTEGER,  -- d
    ///   prime1            INTEGER,  -- p
    ///   prime2            INTEGER,  -- q
    ///   exponent1         INTEGER,  -- d mod (p-1)
    ///   exponent2         INTEGER,  -- d mod (q-1)
    ///   coefficient       INTEGER,  -- (inverse of q) mod p
    ///   otherPrimeInfos   OtherPrimeInfos OPTIONAL
    /// }
    ///////////////////////////////////////////////////////////////////////
    virtual bool ReadDer
    (PublicKeyImplement& publicKey,
     PrivateKeyImplement& privateKey,
     const BYTE* derBytes, size_t length) {
        if ((derBytes) && (length)) {
            AttachedT<const BYTE*, int, 0, io::SeekedT<0, io::attached::BYTEReader> > der(derBytes);
            ssize_t count;

            if ((0 < (count = der.SetLength(length)))) {
                asn1::Reader asn1(this);

                m_onAsn1Sequence = &Derives::OnPrivateSequence;
                m_onAsn1Integer = 0;
                m_onAsn1Primative = 0;
                m_onAsn1Construct = 0;

                if (length <= (count = asn1.Read(der))) {
                    size_t modsize, psize;

                    if ((0 < (length = m_d.Length()))
                        && (0 < (modsize = length))
                        && (0 < (psize = modsize/2))) {
                        if ((CreateMsb(publicKey, m_modulus, m_exponent, modsize))) {

                            if ((CreateMsb(privateKey, m_p,m_q, m_dmp1,m_dmq1, m_iqmp, psize))) {
                                return true;
                            }
                            publicKey.Destroy();
                        }
                    }
                }
            }
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual BYTEArray& Exponent() const {
        return ((BYTEArray&)m_exponent);
    }
    virtual BYTEArray& Modulus() const {
        return ((BYTEArray&)m_modulus);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual BYTEArray& D() const {
        return ((BYTEArray&)m_d);
    }
    virtual BYTEArray& P() const {
        return ((BYTEArray&)m_p);
    }
    virtual BYTEArray& Q() const {
        return ((BYTEArray&)m_q);
    }
    virtual BYTEArray& Dmp1() const {
        return ((BYTEArray&)m_dmp1);
    }
    virtual BYTEArray& Dmq1() const {
        return ((BYTEArray&)m_dmq1);
    }
    virtual BYTEArray& Iqmp() const {
        return ((BYTEArray&)m_iqmp);
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnPrivateSequence(io::BYTEReader& reader, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        m_onAsn1Sequence = 0;
        m_onAsn1Construct = &Derives::OnPrivateConstruct;
        return count;
    }
    virtual ssize_t OnPrivateConstruct(io::BYTEReader& reader, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        m_onAsn1Construct = 0;
        m_onAsn1Integer = &Derives::OnPrivateVersion;
        return count;
    }
    virtual ssize_t OnPrivatePrimative(const BYTE& byte, size_t bytes, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        m_onAsn1Primative = 0;
        return count;
    }
    virtual ssize_t OnPrivateVersion(const BYTE& byte, size_t bytes, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        m_onAsn1Integer = &Derives::OnPrivateModulus;
        XOS_LOG_DEBUG("version[" << bytes << "]");
        return count;
    }
    virtual ssize_t OnPrivateModulus(const BYTE& byte, size_t bytes, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        size_t zeros = LeadingZeros(byte, bytes);
        m_onAsn1Integer = &Derives::OnPrivateExponent;
        XOS_LOG_DEBUG("modulus[" << bytes-zeros << "]");
        m_modulus.Assign(&byte+zeros, bytes-zeros);
        return count;
    }
    virtual ssize_t OnPrivateExponent(const BYTE& byte, size_t bytes, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        size_t zeros = LeadingZeros(byte, bytes);
        m_onAsn1Integer = &Derives::OnPrivateD;
        XOS_LOG_DEBUG("exponent[" << bytes-zeros << "]");
        m_exponent.Assign(&byte+zeros, bytes-zeros);
        return count;
    }
    virtual ssize_t OnPrivateD(const BYTE& byte, size_t bytes, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        size_t zeros = LeadingZeros(byte, bytes);
        m_onAsn1Integer = &Derives::OnPrivateP;
        XOS_LOG_DEBUG("D[" << bytes-zeros << "]");
        m_d.Assign(&byte+zeros, bytes-zeros);
        return count;
    }
    virtual ssize_t OnPrivateP(const BYTE& byte, size_t bytes, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        size_t zeros = LeadingZeros(byte, bytes);
        m_onAsn1Integer = &Derives::OnPrivateQ;
        XOS_LOG_DEBUG("P[" << bytes-zeros << "]");
        m_p.Assign(&byte+zeros, bytes-zeros);
        return count;
    }
    virtual ssize_t OnPrivateQ(const BYTE& byte, size_t bytes, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        size_t zeros = LeadingZeros(byte, bytes);
        m_onAsn1Integer = &Derives::OnPrivateDmP1;
        XOS_LOG_DEBUG("Q[" << bytes-zeros << "]");
        m_q.Assign(&byte+zeros, bytes-zeros);
        return count;
    }
    virtual ssize_t OnPrivateDmP1(const BYTE& byte, size_t bytes, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        size_t zeros = LeadingZeros(byte, bytes);
        m_onAsn1Integer = &Derives::OnPrivateDmQ1;
        XOS_LOG_DEBUG("DmP1[" << bytes-zeros << "]");
        m_dmp1.Assign(&byte+zeros, bytes-zeros);
        return count;
    }
    virtual ssize_t OnPrivateDmQ1(const BYTE& byte, size_t bytes, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        size_t zeros = LeadingZeros(byte, bytes);
        m_onAsn1Integer = &Derives::OnPrivateIQmP;
        XOS_LOG_DEBUG("DmQ1[" << bytes-zeros << "]");
        m_dmq1.Assign(&byte+zeros, bytes-zeros);
        return count;
    }
    virtual ssize_t OnPrivateIQmP(const BYTE& byte, size_t bytes, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        size_t zeros = LeadingZeros(byte, bytes);
        m_onAsn1Integer = 0;
        XOS_LOG_DEBUG("IQmP[" << bytes-zeros << "]");
        m_iqmp.Assign(&byte+zeros, bytes-zeros);
        return count;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1ConstructSequence(io::BYTEReader& reader, const asn1::Block& asn1Block) {
        ssize_t count = -1;
        if ((m_onAsn1Sequence))
            count = (this->*m_onAsn1Sequence)(reader, asn1Block);
        else {
            XOS_LOG_ERROR("unexpected Sequence");
        }
        return count;
    }
    virtual ssize_t OnAsn1Construct(io::BYTEReader& reader, const asn1::Block& asn1Block) {
        ssize_t count = -1;
        if ((m_onAsn1Construct))
            count = (this->*m_onAsn1Construct)(reader, asn1Block);
        else {
            XOS_LOG_ERROR("unexpected Contstruct");
        }
        return count;
    }
    virtual ssize_t OnAsn1Integer(const BYTE& byte, size_t bytes, const asn1::Block& asn1Block) {
        ssize_t count = -1;
        if ((m_onAsn1Integer)) {
            m_onAsn1Primative = &Derives::OnPrivatePrimative;
            count = (this->*m_onAsn1Integer)(byte, bytes, asn1Block);
        } else {
            XOS_LOG_ERROR("unexpected Integer");
        }
        return count;
    }
    virtual ssize_t OnAsn1PrimativeDefault(const BYTE& byte, size_t bytes, const asn1::Block& asn1Block) {
        ssize_t count = -1;
        if ((m_onAsn1Primative))
            count = (this->*m_onAsn1Primative)(byte, bytes, asn1Block);
        else {
            XOS_LOG_ERROR("unexpected Primative");
        }
        return count;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual size_t LeadingZeros(const BYTE& byte, size_t bytes) const {
        size_t zeros = 0;
        for (const BYTE* b = &byte; (0 < bytes) && !(*b); ++b, --bytes) {
            ++zeros;
        }
        return zeros;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool CreateMsb
    (PublicKeyImplement& publicKey,
     const BYTEArray& modulus, const BYTEArray& exponent, size_t modsize) const {
        const BYTE* modbytes;
        size_t length;

        if ((modbytes = Justify(modulus, length, modsize))) {
            const BYTE* expbytes;
            size_t expsize;

            if ((0 < (expsize = exponent.Length())) && (expbytes = exponent.Elements())) {
                if ((publicKey.CreateMSB(modbytes, modsize, expbytes, expsize))) {
                    return true;
                }
            }
        }
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool CreateMsb
    (PrivateKeyImplement& privateKey,
     const BYTEArray& p, const BYTEArray& q,
     const BYTEArray& dmp1,const BYTEArray& dmq1,
     const BYTEArray& iqmp, size_t psize) const {
        const BYTE *pBytes, *qBytes, *dmp1Bytes, *dmq1Bytes, *iqmpBytes;
        size_t length;

        if ((pBytes = Justify(p, length, psize))) {
            if ((qBytes = Justify(q, length, psize))) {
                if ((dmp1Bytes = Justify(dmp1, length, psize))) {
                    if ((dmq1Bytes = Justify(dmq1, length, psize))) {
                        if ((iqmpBytes = Justify(iqmp, length, psize))) {
                            if ((privateKey.CreateMSB
                                (pBytes,qBytes, dmp1Bytes,dmq1Bytes, iqmpBytes, psize))) {
                                return true;
                            }
                        }
                    }
                }
            }
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const BYTE* Justify
    (const BYTEArray& array, size_t& length, size_t toSize) const {
        const BYTE* bytes;
        if ((0 < (length = array.Length())) && (bytes = array.Elements())) {
            if (toSize == (length = Justify(bytes, length, toSize))) {
                return bytes;
            }
        }
        return 0;
    }
    virtual size_t Justify
    (const BYTE*& bytes, size_t length, size_t toSize) const {
        BYTE byte;
        for (size_t i = length; i > toSize; --i, ++bytes) {
            if ((byte = *bytes) != 0) {
                XOS_LOG_DEBUG("bytes[" << (i - toSize) << "] != 0 (" << byte << ")");
                return 0;
            }
        }
        return toSize;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    typedef ssize_t (Derives::*MOnAsn1Construct)(io::BYTEReader& reader, const asn1::Block& asn1Block);
    typedef ssize_t (Derives::*MOnAsn1Primative)(const BYTE& byte, size_t bytes, const asn1::Block& asn1Block);

protected:
    MOnAsn1Construct m_onAsn1Sequence;
    MOnAsn1Primative m_onAsn1Integer;
    MOnAsn1Construct m_onAsn1Construct;
    MOnAsn1Primative m_onAsn1Primative;
    BYTEArray m_modulus, m_exponent;
    BYTEArray m_d, m_p, m_q, m_dmp1, m_dmq1, m_iqmp;
};

} // namespace rsa 
} // namespace crypto 
} // namespace xos 

#endif // _XOS_CRYPTO_RSA_KEYREADER_HPP 
