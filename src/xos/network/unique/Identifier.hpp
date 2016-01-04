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
///   File: Identifier.hpp
///
/// Author: $author$
///   Date: 2/16/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_NETWORK_UNIQUE_IDENTIFIER_HPP
#define _XOS_NETWORK_UNIQUE_IDENTIFIER_HPP

#include "xos/network/unique/actual/Identifier.hpp"
#include "xos/network/ethernet/actual/Address.hpp"
#include "xos/crypto/hash/Interface.hpp"
#include "xos/crypto/random/Generator.hpp"
#include "xos/base/Writer.hpp"
#include "xos/base/Wrapped.hpp"

namespace xos {
namespace network {
namespace unique {

typedef InterfaceBase IdentifierImplement;
typedef Wrapped
<actual::Identifier, int,
 IdentifierImplement, ExportBase> IdentifierExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Identifier
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Identifier: virtual public IdentifierImplement, public IdentifierExtend {
public:
    typedef IdentifierImplement Implements;
    typedef IdentifierExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///  Class: Version
    ///////////////////////////////////////////////////////////////////////
    class _EXPORT_CLASS Version {
    public:
        typedef int Which;
        enum {
            None          = actual::Identifier::VERSION_NONE,
            TimeBased     = actual::Identifier::VERSION_TIME_BASED,
            DceSecurity   = actual::Identifier::VERSION_DCE_SECURITY,
            NameBasedMd5  = actual::Identifier::VERSION_NAME_BASED_MD5,
            Random        = actual::Identifier::VERSION_RANDOM,
            NameBasedSha1 = actual::Identifier::VERSION_NAME_BASED_SHA1
        };
        Version(const Version& copy): m_which(copy.m_which) {}
        Version(Which which = None): m_which(which) {}
        operator int () const { return m_which; }
    protected:
        Which m_which;
    };
    ///////////////////////////////////////////////////////////////////////
    ///  Class: From
    ///////////////////////////////////////////////////////////////////////
    class _EXPORT_CLASS From {
    public:
        typedef xos::crypto::random::Generator Random;
        typedef xos::crypto::hash::Interface Md5;
        typedef xos::crypto::hash::Interface Sha1;
        typedef xos::network::ethernet::actual::Address MacAddress;
        ///////////////////////////////////////////////////////////////////////
        ///  Class: Ethernet
        ///////////////////////////////////////////////////////////////////////
        class _EXPORT_CLASS Ethernet {
        public:
            virtual const MacAddress* Address() const = 0;
        };
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        virtual Ethernet& ethernet() const = 0;
        virtual Random& random() const = 0;
        virtual Md5& md5() const = 0;
        virtual Sha1& sha1() const = 0;
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
    };
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Identifier(const Identifier& copy): Extends(copy) {
    }
    Identifier() {
    }
    virtual ~Identifier() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Generate(From& from, Version::Which which = Version::None) {
        return false;
    }
    virtual void Clear() {
        memset(&m_wrapped, 0, sizeof(WrappedT));
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t WriteX(StringWriter& writer, char A = 'A', char separator = '-') const {
        ssize_t count = 0;
        ssize_t count2;
        if (0 < (count = WriteX
            (writer, m_wrapped.m_timeLow.m_b,
             sizeof(m_wrapped.m_timeLow.m_b), A, separator)))

        if (0 < (count2 = WriteX
            (writer, m_wrapped.m_timeMid.m_b,
             sizeof(m_wrapped.m_timeMid.m_b), A, separator)))

        if (0 < (count2 = WriteX
            (writer, m_wrapped.m_timeHiAndVersion.m_b,
             sizeof(m_wrapped.m_timeHiAndVersion.m_b), A, separator)))

        if (0 < (count2 = WriteX
            (writer, m_wrapped.m_clockSeq.m_b,
             sizeof(m_wrapped.m_clockSeq.m_b), A, separator)))

        if (0 < (count2 = WriteX
            (writer, m_wrapped.m_node.m_b,
             sizeof(m_wrapped.m_node.m_b), A)))
            count += count2;
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool operator != (const Identifier& to) {
        return (0 != (memcmp(&m_wrapped, &to.m_wrapped, sizeof(WrappedT))));
    }
    virtual bool operator == (const Identifier& to) {
        return (0 == (memcmp(&m_wrapped, &to.m_wrapped, sizeof(WrappedT))));
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    inline actual::Identifier& actual() const {
        return m_wrapped;
    }
protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t WriteX
    (StringWriter& writer, const uint8_t* value, size_t size, char A = 'A', char separator = 0) const {
        ssize_t count = 0;
        ssize_t count2;
        if (0 < (count = writer.WriteX(value, size, A)))
        if (separator)
        if (0 < (count2 = writer.Write(&separator, sizeof(separator))))
            count += count2;
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual uint8_t& TimeToMsb() {
        ToMsb(*m_wrapped.m_timeLow.m_b, m_wrapped.m_timeLow.m_l, sizeof(m_wrapped.m_timeLow.m_l));
        ToMsb(*m_wrapped.m_timeMid.m_b, m_wrapped.m_timeMid.m_w, sizeof(m_wrapped.m_timeMid.m_w));
        ToMsb(*m_wrapped.m_timeHiAndVersion.m_b, m_wrapped.m_timeHiAndVersion.m_w, sizeof(m_wrapped.m_timeHiAndVersion.m_w));
        return *m_wrapped.m_b;
    }
    virtual uint8_t& ToMsb(uint8_t& to, unsigned long value, size_t size) const {
        unsigned long msbValue = 0;
        for (int b = 0; b < size; ++b) {
            msbValue <<= 8;
            msbValue |= (value & 0xFF);
            value >>= 8;
        }
        for (int b = 0; b < size; ++b) {
            (&to)[b] = (msbValue & 0xFF);
            msbValue >>= 8;
        }
        return to;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace unique 
} // namespace network 
} // namespace xos 

#endif // _XOS_NETWORK_UNIQUE_IDENTIFIER_HPP 
