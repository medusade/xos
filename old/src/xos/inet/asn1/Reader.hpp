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
///   File: Reader.hpp
///
/// Author: $author$
///   Date: 5/13/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_INET_ASN1_READER_HPP
#define _XOS_INET_ASN1_READER_HPP

#include "xos/inet/asn1/ReaderEvents.hpp"
#include "xos/io/sized/Reader.hpp"
#include "xos/base/Array.hpp"

namespace xos {
namespace asn1 {

///////////////////////////////////////////////////////////////////////
///  Class: Reader
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Reader: virtual public ReaderEvents, public Extend {
public:
    typedef ReaderEvents Implements;
    typedef Extend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Reader(ReaderEvents* delegatedTo = 0): m_delegatedTo(delegatedTo) {
    }
    virtual ~Reader() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t Read(io::BYTEReader& reader) {
        ssize_t count = 0;
        ssize_t amount;
        asn1::Block asn1Block;

        do {
            if (0 < (amount = asn1Block.Read(reader))) {
                count += amount;

                if (0 < (amount = OnAsn1Block(reader, asn1Block)))
                    count += amount;
            }
        } while (amount > 0);
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1Block(io::BYTEReader& reader, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        ReaderEvents* delegatedTo = 0;

        if ((delegatedTo = DelegatedTo((ReaderEvents&)(*this))))
        if (0 != (count = delegatedTo->OnAsn1Block(reader, asn1Block)))
            return count;

        asn1::form_t asn1Form = asn1Block.Form();

        switch(asn1Form) {
        case FORM_Primative:
            count = OnAsn1PrimativeBlock(reader, asn1Block);
            break;

        case FORM_Construct:
            count = OnAsn1ConstructBlock(reader, asn1Block);
            break;

        default:
            count = OnAsn1UndefinedBlock(reader, asn1Block);
        }
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1ConstructBlock(io::BYTEReader& reader, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        ReaderEvents* delegatedTo = 0;

        if ((delegatedTo = DelegatedTo((ReaderEvents&)(*this))))
        if (0 != (count = delegatedTo->OnAsn1ConstructBlock(reader, asn1Block)))
            return count;

        type_t asn1Type;

        switch(asn1Type = asn1Block.Type()) {

        case TYPE_Any:
            count = OnAsn1ConstructAny(reader, asn1Block);
            break;

        case TYPE_Boolean:
            count = OnAsn1ConstructBoolean(reader, asn1Block);
            break;

        case TYPE_Integer:
            count = OnAsn1ConstructInteger(reader, asn1Block);
            break;

        case TYPE_BitString:
            count = OnAsn1ConstructBitString(reader, asn1Block);
            break;

        case TYPE_OctetString:
            count = OnAsn1ConstructOctetString(reader, asn1Block);
            break;

        case TYPE_Null:
            count = OnAsn1ConstructNull(reader, asn1Block);
            break;

        case TYPE_ObjectID:
            count = OnAsn1ConstructObjectID(reader, asn1Block);
            break;

        case TYPE_Object:
            count = OnAsn1ConstructObject(reader, asn1Block);
            break;

        case TYPE_External:
            count = OnAsn1ConstructExternal(reader, asn1Block);
            break;

        case TYPE_Real:
            count = OnAsn1ConstructReal(reader, asn1Block);
            break;

        case TYPE_Enum:
            count = OnAsn1ConstructEnum(reader, asn1Block);
            break;

        case TYPE_Sequence:
            count = OnAsn1ConstructSequence(reader, asn1Block);
            break;

        case TYPE_Set:
            count = OnAsn1ConstructSet(reader, asn1Block);
            break;

        case TYPE_NumericString:
            count = OnAsn1ConstructNumericString(reader, asn1Block);
            break;

        case TYPE_PrintableString:
            count = OnAsn1ConstructPrintableString(reader, asn1Block);
            break;

        case TYPE_TeletexString:
            count = OnAsn1ConstructTeletexString(reader, asn1Block);
            break;

        case TYPE_VideotexString:
            count = OnAsn1ConstructVideotexString(reader, asn1Block);
            break;

        case TYPE_IA5String:
            count = OnAsn1ConstructIA5String(reader, asn1Block);
            break;

        case TYPE_UTCTime:
            count = OnAsn1ConstructUTCTime(reader, asn1Block);
            break;

        case TYPE_GeneralizedTime:
            count = OnAsn1ConstructGeneralizedTime(reader, asn1Block);
            break;

        case TYPE_GraphicString:
            count = OnAsn1ConstructGraphicString(reader, asn1Block);
            break;

        case TYPE_VisibleString:
            count = OnAsn1ConstructVisibleString(reader, asn1Block);
            break;

        case TYPE_GeneralString:
            count = OnAsn1ConstructGeneralString(reader, asn1Block);
            break;

        default:
            count = OnAsn1Construct(reader, asn1Block);
        }
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1Construct(io::BYTEReader& reader, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        ReaderEvents* delegatedTo = 0;

        if ((delegatedTo = DelegatedTo((ReaderEvents&)(*this))))
        if (0 != (count = delegatedTo->OnAsn1Construct(reader, asn1Block)))
            return count;

        io::sized::BYTEReader sizedReader(reader, asn1Block.Length());
        ssize_t amount;

        if (0 > (amount = OnAsn1ConstructBegin(reader, asn1Block)))
            return amount;

        if (0 > (count = Read(sizedReader)))
            return count;

        if (0 > (amount = OnAsn1ConstructEnd(reader, asn1Block)))
            return amount;

        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1PrimativeBlock(io::BYTEReader& reader, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        ReaderEvents* delegatedTo = 0;

        if ((delegatedTo = DelegatedTo((ReaderEvents&)(*this))))
        if (0 != (count = delegatedTo->OnAsn1PrimativeBlock(reader, asn1Block)))
            return count;

        size_t  asn1Length = asn1Block.Length();
        ssize_t amount;
        BYTE* bytes;
        Array<BYTE> primativeData;

        if ((asn1Length == (primativeData.SetLength(asn1Length)))
            && (bytes = primativeData.Elements())) {

            if (asn1Length == (count = reader.Read(bytes, asn1Length))) {

                if (0 > (amount = OnAsn1Primative(*bytes, asn1Length, asn1Block))) {
                    return amount;
                }
            }
        }
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t OnAsn1Primative(const BYTE& byte, size_t bytes, const asn1::Block& asn1Block) {
        ssize_t count = 0;
        ReaderEvents* delegatedTo = 0;

        if ((delegatedTo = DelegatedTo((ReaderEvents&)(*this))))
        if (0 != (count = delegatedTo->OnAsn1Primative(byte, bytes, asn1Block)))
            return count;

        type_t asn1Type;

        switch(asn1Type = asn1Block.Type()) {

        case TYPE_Any:
            count = OnAsn1Any(byte, bytes, asn1Block);
            break;

        case TYPE_Boolean:
            count = OnAsn1Boolean(byte, bytes, asn1Block);
            break;

        case TYPE_Integer:
            count = OnAsn1Integer(byte, bytes, asn1Block);
            break;

        case TYPE_BitString:
            count = OnAsn1BitString(byte, bytes, asn1Block);
            break;

        case TYPE_OctetString:
            count = OnAsn1OctetString(byte, bytes, asn1Block);
            break;

        case TYPE_Null:
            count = OnAsn1Null(byte, bytes, asn1Block);
            break;

        case TYPE_ObjectID:
            count = OnAsn1ObjectID(byte, bytes, asn1Block);
            break;

        case TYPE_Object:
            count = OnAsn1Object(byte, bytes, asn1Block);
            break;

        case TYPE_External:
            count = OnAsn1External(byte, bytes, asn1Block);
            break;

        case TYPE_Real:
            count = OnAsn1Real(byte, bytes, asn1Block);
            break;

        case TYPE_Enum:
            count = OnAsn1Enum(byte, bytes, asn1Block);
            break;

        case TYPE_Sequence:
            count = OnAsn1Sequence(byte, bytes, asn1Block);
            break;

        case TYPE_Set:
            count = OnAsn1Set(byte, bytes, asn1Block);
            break;

        case TYPE_NumericString:
            count = OnAsn1NumericString(byte, bytes, asn1Block);
            break;

        case TYPE_PrintableString:
            count = OnAsn1PrintableString(byte, bytes, asn1Block);
            break;

        case TYPE_TeletexString:
            count = OnAsn1TeletexString(byte, bytes, asn1Block);
            break;

        case TYPE_VideotexString:
            count = OnAsn1VideotexString(byte, bytes, asn1Block);
            break;

        case TYPE_IA5String:
            count = OnAsn1IA5String(byte, bytes, asn1Block);
            break;

        case TYPE_UTCTime:
            count = OnAsn1UTCTime(byte, bytes, asn1Block);
            break;

        case TYPE_GeneralizedTime:
            count = OnAsn1GeneralizedTime(byte, bytes, asn1Block);
            break;

        case TYPE_GraphicString:
            count = OnAsn1GraphicString(byte, bytes, asn1Block);
            break;

        case TYPE_VisibleString:
            count = OnAsn1VisibleString(byte, bytes, asn1Block);
            break;

        case TYPE_GeneralString:
            count = OnAsn1GeneralString(byte, bytes, asn1Block);
            break;

        default:
            count = OnAsn1PrimativeDefault(byte, bytes, asn1Block);
        }
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ReaderEvents* DelegatedTo(ReaderEvents& events) const {
        return m_delegatedTo;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    ReaderEvents* m_delegatedTo;
};

} // namespace asn1 
} // namespace xos 

#endif // _XOS_INET_ASN1_READER_HPP 
