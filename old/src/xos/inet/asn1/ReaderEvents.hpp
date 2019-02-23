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
///   File: ReaderEvents.hpp
///
/// Author: $author$
///   Date: 5/13/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_INET_ASN1_READEREVENTS_HPP
#define _XOS_INET_ASN1_READEREVENTS_HPP

#include "xos/inet/asn1/Block.hpp"
#include "xos/inet/asn1/Length.hpp"
#include "xos/inet/asn1/Type.hpp"
#include "xos/inet/asn1/Form.hpp"
#include "xos/inet/asn1/Class.hpp"
#include "xos/inet/asn1/Base.hpp"
#include "xos/io/Reader.hpp"

namespace xos {
namespace asn1 {

///////////////////////////////////////////////////////////////////////
///  Class: ReaderEvents
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS ReaderEvents: virtual public Implement {
public:
    typedef Implement Implements;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1Block(io::BYTEReader& reader, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        ReaderEvents* delegatedTo = 0;

        if ((delegatedTo = DelegatedTo((ReaderEvents&)(*this))))
        if (0 != (count = delegatedTo->OnAsn1Block(reader, asn1Block)))
            return count;

        return count;
    }
    virtual ssize_t OnAsn1PrimativeBlock(io::BYTEReader& reader, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        ReaderEvents* delegatedTo = 0;

        if ((delegatedTo = DelegatedTo((ReaderEvents&)(*this))))
        if (0 != (count = delegatedTo->OnAsn1PrimativeBlock(reader, asn1Block)))
            return count;

        return count;
    }
    virtual ssize_t OnAsn1ConstructBlock(io::BYTEReader& reader, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        ReaderEvents* delegatedTo = 0;

        if ((delegatedTo = DelegatedTo((ReaderEvents&)(*this))))
        if (0 != (count = delegatedTo->OnAsn1ConstructBlock(reader, asn1Block)))
            return count;

        return count;
    }
    virtual ssize_t OnAsn1UndefinedBlock(io::BYTEReader& reader, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        ReaderEvents* delegatedTo = 0;

        if ((delegatedTo = DelegatedTo((ReaderEvents&)(*this))))
        if (0 != (count = delegatedTo->OnAsn1UndefinedBlock(reader, asn1Block)))
            return count;

        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1Construct(io::BYTEReader& reader, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        ReaderEvents* delegatedTo = 0;

        if ((delegatedTo = DelegatedTo((ReaderEvents&)(*this))))
        if (0 != (count = delegatedTo->OnAsn1Construct(reader, asn1Block)))
            return count;

        return count;
    }
    virtual ssize_t OnAsn1ConstructBegin(io::BYTEReader& reader, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        ReaderEvents* delegatedTo = 0;

        if ((delegatedTo = DelegatedTo((ReaderEvents&)(*this))))
        if (0 != (count = delegatedTo->OnAsn1ConstructBegin(reader, asn1Block)))
            return count;

        return count;
    }
    virtual ssize_t OnAsn1ConstructEnd(io::BYTEReader& reader, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        ReaderEvents* delegatedTo = 0;

        if ((delegatedTo = DelegatedTo((ReaderEvents&)(*this))))
        if (0 != (count = delegatedTo->OnAsn1ConstructEnd(reader, asn1Block)))
            return count;

        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1ConstructAny(io::BYTEReader& reader, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        ReaderEvents* delegatedTo = 0;

        if ((delegatedTo = DelegatedTo((ReaderEvents&)(*this))))
        if (0 != (count = delegatedTo->OnAsn1ConstructAny(reader, asn1Block)))
            return count;

        count = OnAsn1Construct(reader, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1ConstructBoolean(io::BYTEReader& reader, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        ReaderEvents* delegatedTo = 0;

        if ((delegatedTo = DelegatedTo((ReaderEvents&)(*this))))
        if (0 != (count = delegatedTo->OnAsn1ConstructBoolean(reader, asn1Block)))
            return count;

        count = OnAsn1Construct(reader, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1ConstructInteger(io::BYTEReader& reader, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        ReaderEvents* delegatedTo = 0;

        if ((delegatedTo = DelegatedTo((ReaderEvents&)(*this))))
        if (0 != (count = delegatedTo->OnAsn1ConstructInteger(reader, asn1Block)))
            return count;

        count = OnAsn1Construct(reader, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1ConstructBitString(io::BYTEReader& reader, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        ReaderEvents* delegatedTo = 0;

        if ((delegatedTo = DelegatedTo((ReaderEvents&)(*this))))
        if (0 != (count = delegatedTo->OnAsn1ConstructBitString(reader, asn1Block)))
            return count;

        count = OnAsn1Construct(reader, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1ConstructOctetString(io::BYTEReader& reader, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        ReaderEvents* delegatedTo = 0;

        if ((delegatedTo = DelegatedTo((ReaderEvents&)(*this))))
        if (0 != (count = delegatedTo->OnAsn1ConstructOctetString(reader, asn1Block)))
            return count;

        count = OnAsn1Construct(reader, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1ConstructNull(io::BYTEReader& reader, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        ReaderEvents* delegatedTo = 0;

        if ((delegatedTo = DelegatedTo((ReaderEvents&)(*this))))
        if (0 != (count = delegatedTo->OnAsn1ConstructNull(reader, asn1Block)))
            return count;

        count = OnAsn1Construct(reader, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1ConstructObjectID(io::BYTEReader& reader, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        ReaderEvents* delegatedTo = 0;

        if ((delegatedTo = DelegatedTo((ReaderEvents&)(*this))))
        if (0 != (count = delegatedTo->OnAsn1ConstructObjectID(reader, asn1Block)))
            return count;

        count = OnAsn1Construct(reader, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1ConstructObject(io::BYTEReader& reader, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        ReaderEvents* delegatedTo = 0;

        if ((delegatedTo = DelegatedTo((ReaderEvents&)(*this))))
        if (0 != (count = delegatedTo->OnAsn1ConstructObject(reader, asn1Block)))
            return count;

        count = OnAsn1Construct(reader, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1ConstructExternal(io::BYTEReader& reader, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        ReaderEvents* delegatedTo = 0;

        if ((delegatedTo = DelegatedTo((ReaderEvents&)(*this))))
        if (0 != (count = delegatedTo->OnAsn1ConstructExternal(reader, asn1Block)))
            return count;

        count = OnAsn1Construct(reader, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1ConstructReal(io::BYTEReader& reader, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        ReaderEvents* delegatedTo = 0;

        if ((delegatedTo = DelegatedTo((ReaderEvents&)(*this))))
        if (0 != (count = delegatedTo->OnAsn1ConstructReal(reader, asn1Block)))
            return count;

        count = OnAsn1Construct(reader, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1ConstructEnum(io::BYTEReader& reader, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        ReaderEvents* delegatedTo = 0;

        if ((delegatedTo = DelegatedTo((ReaderEvents&)(*this))))
        if (0 != (count = delegatedTo->OnAsn1ConstructEnum(reader, asn1Block)))
            return count;

        count = OnAsn1Construct(reader, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1ConstructSequence(io::BYTEReader& reader, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        ReaderEvents* delegatedTo = 0;

        if ((delegatedTo = DelegatedTo((ReaderEvents&)(*this))))
        if (0 != (count = delegatedTo->OnAsn1ConstructSequence(reader, asn1Block)))
            return count;

        count = OnAsn1Construct(reader, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1ConstructSet(io::BYTEReader& reader, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        ReaderEvents* delegatedTo = 0;

        if ((delegatedTo = DelegatedTo((ReaderEvents&)(*this))))
        if (0 != (count = delegatedTo->OnAsn1ConstructSet(reader, asn1Block)))
            return count;

        count = OnAsn1Construct(reader, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1ConstructNumericString(io::BYTEReader& reader, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        ReaderEvents* delegatedTo = 0;

        if ((delegatedTo = DelegatedTo((ReaderEvents&)(*this))))
        if (0 != (count = delegatedTo->OnAsn1ConstructNumericString(reader, asn1Block)))
            return count;

        count = OnAsn1Construct(reader, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1ConstructPrintableString(io::BYTEReader& reader, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        ReaderEvents* delegatedTo = 0;

        if ((delegatedTo = DelegatedTo((ReaderEvents&)(*this))))
        if (0 != (count = delegatedTo->OnAsn1ConstructPrintableString(reader, asn1Block)))
            return count;

        count = OnAsn1Construct(reader, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1ConstructTeletexString(io::BYTEReader& reader, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        ReaderEvents* delegatedTo = 0;

        if ((delegatedTo = DelegatedTo((ReaderEvents&)(*this))))
        if (0 != (count = delegatedTo->OnAsn1ConstructTeletexString(reader, asn1Block)))
            return count;

        count = OnAsn1Construct(reader, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1ConstructVideotexString(io::BYTEReader& reader, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        ReaderEvents* delegatedTo = 0;

        if ((delegatedTo = DelegatedTo((ReaderEvents&)(*this))))
        if (0 != (count = delegatedTo->OnAsn1ConstructVideotexString(reader, asn1Block)))
            return count;

        count = OnAsn1Construct(reader, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1ConstructIA5String(io::BYTEReader& reader, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        ReaderEvents* delegatedTo = 0;

        if ((delegatedTo = DelegatedTo((ReaderEvents&)(*this))))
        if (0 != (count = delegatedTo->OnAsn1ConstructIA5String(reader, asn1Block)))
            return count;

        count = OnAsn1Construct(reader, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1ConstructUTCTime(io::BYTEReader& reader, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        ReaderEvents* delegatedTo = 0;

        if ((delegatedTo = DelegatedTo((ReaderEvents&)(*this))))
        if (0 != (count = delegatedTo->OnAsn1ConstructUTCTime(reader, asn1Block)))
            return count;

        count = OnAsn1Construct(reader, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1ConstructGeneralizedTime(io::BYTEReader& reader, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        ReaderEvents* delegatedTo = 0;

        if ((delegatedTo = DelegatedTo((ReaderEvents&)(*this))))
        if (0 != (count = delegatedTo->OnAsn1ConstructGeneralizedTime(reader, asn1Block)))
            return count;

        count = OnAsn1Construct(reader, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1ConstructGraphicString(io::BYTEReader& reader, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        ReaderEvents* delegatedTo = 0;

        if ((delegatedTo = DelegatedTo((ReaderEvents&)(*this))))
        if (0 != (count = delegatedTo->OnAsn1ConstructGraphicString(reader, asn1Block)))
            return count;

        count = OnAsn1Construct(reader, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1ConstructVisibleString(io::BYTEReader& reader, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        ReaderEvents* delegatedTo = 0;

        if ((delegatedTo = DelegatedTo((ReaderEvents&)(*this))))
        if (0 != (count = delegatedTo->OnAsn1ConstructVisibleString(reader, asn1Block)))
            return count;

        count = OnAsn1Construct(reader, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1ConstructGeneralString(io::BYTEReader& reader, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        ReaderEvents* delegatedTo = 0;

        if ((delegatedTo = DelegatedTo((ReaderEvents&)(*this))))
        if (0 != (count = delegatedTo->OnAsn1ConstructGeneralString(reader, asn1Block)))
            return count;

        count = OnAsn1Construct(reader, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1Primative(const BYTE& byte, size_t bytes, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        ReaderEvents* delegatedTo = 0;

        if ((delegatedTo = DelegatedTo((ReaderEvents&)(*this))))
        if (0 != (count = delegatedTo->OnAsn1Primative(byte, bytes, asn1Block)))
            return count;

        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1Any(const BYTE& byte, size_t bytes, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        ReaderEvents* delegatedTo = 0;

        if ((delegatedTo = DelegatedTo((ReaderEvents&)(*this))))
        if (0 != (count = delegatedTo->OnAsn1Any(byte, bytes, asn1Block)))
            return count;

        count = OnAsn1PrimativeDefault(byte, bytes, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1Boolean(const BYTE& byte, size_t bytes, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        ReaderEvents* delegatedTo = 0;

        if ((delegatedTo = DelegatedTo((ReaderEvents&)(*this))))
        if (0 != (count = delegatedTo->OnAsn1Boolean(byte, bytes, asn1Block)))
            return count;

        count = OnAsn1PrimativeDefault(byte, bytes, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1Integer(const BYTE& byte, size_t bytes, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        ReaderEvents* delegatedTo = 0;

        if ((delegatedTo = DelegatedTo((ReaderEvents&)(*this))))
        if (0 != (count = delegatedTo->OnAsn1Integer(byte, bytes, asn1Block)))
            return count;

        count = OnAsn1PrimativeDefault(byte, bytes, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1BitString(const BYTE& byte, size_t bytes, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        ReaderEvents* delegatedTo = 0;

        if ((delegatedTo = DelegatedTo((ReaderEvents&)(*this))))
        if (0 != (count = delegatedTo->OnAsn1BitString(byte, bytes, asn1Block)))
            return count;

        count = OnAsn1PrimativeDefault(byte, bytes, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1OctetString(const BYTE& byte, size_t bytes, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        ReaderEvents* delegatedTo = 0;

        if ((delegatedTo = DelegatedTo((ReaderEvents&)(*this))))
        if (0 != (count = delegatedTo->OnAsn1OctetString(byte, bytes, asn1Block)))
            return count;

        count = OnAsn1PrimativeDefault(byte, bytes, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1Null(const BYTE& byte, size_t bytes, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        ReaderEvents* delegatedTo = 0;

        if ((delegatedTo = DelegatedTo((ReaderEvents&)(*this))))
        if (0 != (count = delegatedTo->OnAsn1Null(byte, bytes, asn1Block)))
            return count;

        count = OnAsn1PrimativeDefault(byte, bytes, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1ObjectID(const BYTE& byte, size_t bytes, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        ReaderEvents* delegatedTo = 0;

        if ((delegatedTo = DelegatedTo((ReaderEvents&)(*this))))
        if (0 != (count = delegatedTo->OnAsn1ObjectID(byte, bytes, asn1Block)))
            return count;

        count = OnAsn1PrimativeDefault(byte, bytes, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1Object(const BYTE& byte, size_t bytes, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        ReaderEvents* delegatedTo = 0;

        if ((delegatedTo = DelegatedTo((ReaderEvents&)(*this))))
        if (0 != (count = delegatedTo->OnAsn1Object(byte, bytes, asn1Block)))
            return count;

        count = OnAsn1PrimativeDefault(byte, bytes, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1External(const BYTE& byte, size_t bytes, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        ReaderEvents* delegatedTo = 0;

        if ((delegatedTo = DelegatedTo((ReaderEvents&)(*this))))
        if (0 != (count = delegatedTo->OnAsn1External(byte, bytes, asn1Block)))
            return count;

        count = OnAsn1PrimativeDefault(byte, bytes, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1Real(const BYTE& byte, size_t bytes, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        ReaderEvents* delegatedTo = 0;

        if ((delegatedTo = DelegatedTo((ReaderEvents&)(*this))))
        if (0 != (count = delegatedTo->OnAsn1Real(byte, bytes, asn1Block)))
            return count;

        count = OnAsn1PrimativeDefault(byte, bytes, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1Enum(const BYTE& byte, size_t bytes, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        ReaderEvents* delegatedTo = 0;

        if ((delegatedTo = DelegatedTo((ReaderEvents&)(*this))))
        if (0 != (count = delegatedTo->OnAsn1Enum(byte, bytes, asn1Block)))
            return count;

        count = OnAsn1PrimativeDefault(byte, bytes, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1Sequence(const BYTE& byte, size_t bytes, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        ReaderEvents* delegatedTo = 0;

        if ((delegatedTo = DelegatedTo((ReaderEvents&)(*this))))
        if (0 != (count = delegatedTo->OnAsn1Sequence(byte, bytes, asn1Block)))
            return count;

        count = OnAsn1PrimativeDefault(byte, bytes, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1Set(const BYTE& byte, size_t bytes, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        ReaderEvents* delegatedTo = 0;

        if ((delegatedTo = DelegatedTo((ReaderEvents&)(*this))))
        if (0 != (count = delegatedTo->OnAsn1Set(byte, bytes, asn1Block)))
            return count;

        count = OnAsn1PrimativeDefault(byte, bytes, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1NumericString(const BYTE& byte, size_t bytes, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        ReaderEvents* delegatedTo = 0;

        if ((delegatedTo = DelegatedTo((ReaderEvents&)(*this))))
        if (0 != (count = delegatedTo->OnAsn1NumericString(byte, bytes, asn1Block)))
            return count;

        count = OnAsn1PrimativeDefault(byte, bytes, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1PrintableString(const BYTE& byte, size_t bytes, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        ReaderEvents* delegatedTo = 0;

        if ((delegatedTo = DelegatedTo((ReaderEvents&)(*this))))
        if (0 != (count = delegatedTo->OnAsn1PrintableString(byte, bytes, asn1Block)))
            return count;

        count = OnAsn1PrimativeDefault(byte, bytes, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1TeletexString(const BYTE& byte, size_t bytes, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        ReaderEvents* delegatedTo = 0;

        if ((delegatedTo = DelegatedTo((ReaderEvents&)(*this))))
        if (0 != (count = delegatedTo->OnAsn1TeletexString(byte, bytes, asn1Block)))
            return count;

        count = OnAsn1PrimativeDefault(byte, bytes, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1VideotexString(const BYTE& byte, size_t bytes, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        ReaderEvents* delegatedTo = 0;

        if ((delegatedTo = DelegatedTo((ReaderEvents&)(*this))))
        if (0 != (count = delegatedTo->OnAsn1VideotexString(byte, bytes, asn1Block)))
            return count;

        count = OnAsn1PrimativeDefault(byte, bytes, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1IA5String(const BYTE& byte, size_t bytes, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        ReaderEvents* delegatedTo = 0;

        if ((delegatedTo = DelegatedTo((ReaderEvents&)(*this))))
        if (0 != (count = delegatedTo->OnAsn1IA5String(byte, bytes, asn1Block)))
            return count;

        count = OnAsn1PrimativeDefault(byte, bytes, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1UTCTime(const BYTE& byte, size_t bytes, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        ReaderEvents* delegatedTo = 0;

        if ((delegatedTo = DelegatedTo((ReaderEvents&)(*this))))
        if (0 != (count = delegatedTo->OnAsn1UTCTime(byte, bytes, asn1Block)))
            return count;

        count = OnAsn1PrimativeDefault(byte, bytes, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1GeneralizedTime(const BYTE& byte, size_t bytes, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        ReaderEvents* delegatedTo = 0;

        if ((delegatedTo = DelegatedTo((ReaderEvents&)(*this))))
        if (0 != (count = delegatedTo->OnAsn1GeneralizedTime(byte, bytes, asn1Block)))
            return count;

        count = OnAsn1PrimativeDefault(byte, bytes, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1GraphicString(const BYTE& byte, size_t bytes, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        ReaderEvents* delegatedTo = 0;

        if ((delegatedTo = DelegatedTo((ReaderEvents&)(*this))))
        if (0 != (count = delegatedTo->OnAsn1GraphicString(byte, bytes, asn1Block)))
            return count;

        count = OnAsn1PrimativeDefault(byte, bytes, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1VisibleString(const BYTE& byte, size_t bytes, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        ReaderEvents* delegatedTo = 0;

        if ((delegatedTo = DelegatedTo((ReaderEvents&)(*this))))
        if (0 != (count = delegatedTo->OnAsn1VisibleString(byte, bytes, asn1Block)))
            return count;

        count = OnAsn1PrimativeDefault(byte, bytes, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1GeneralString(const BYTE& byte, size_t bytes, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        ReaderEvents* delegatedTo = 0;

        if ((delegatedTo = DelegatedTo((ReaderEvents&)(*this))))
        if (0 != (count = delegatedTo->OnAsn1GeneralString(byte, bytes, asn1Block)))
            return count;

        count = OnAsn1PrimativeDefault(byte, bytes, asn1Block);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1ConstructDefault(io::BYTEReader& reader, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        ReaderEvents* delegatedTo = 0;

        if ((delegatedTo = DelegatedTo((ReaderEvents&)(*this))))
        if (0 != (count = delegatedTo->OnAsn1ConstructDefault(reader, asn1Block)))
            return count;

        return count;
    }
    virtual ssize_t OnAsn1PrimativeDefault(const BYTE& byte, size_t bytes, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        ReaderEvents* delegatedTo = 0;

        if ((delegatedTo = DelegatedTo((ReaderEvents&)(*this))))
        if (0 != (count = delegatedTo->OnAsn1PrimativeDefault(byte, bytes, asn1Block)))
            return count;

        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ReaderEvents* DelegatedTo(ReaderEvents& events) const {
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace asn1 
} // namespace xos 

#endif // _XOS_INET_ASN1_READEREVENTS_HPP 
