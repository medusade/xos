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
#ifndef _XOS_NETWORK_UNIQUE_UNIX_IDENTIFIER_HPP
#define _XOS_NETWORK_UNIQUE_UNIX_IDENTIFIER_HPP

#include "xos/network/unique/Identifier.hpp"
#include "xos/base/HexString.hpp"
#include "xos/os/Logger.hpp"
#include <sys/time.h>

namespace xos {
namespace network {
namespace unique {
namespace unix {

typedef unique::IdentifierImplement IdentifierImplement;
typedef unique::Identifier IdentifierExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Identifier
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Identifier: virtual public IdentifierImplement, public IdentifierExtend {
public:
    typedef IdentifierImplement Implements;
    typedef IdentifierExtend Extends;
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
        if (!(which)) {
            return GenerateTimeBased(from);
        }
        return false;
    }
    virtual bool GenerateTimeBased(From& from) {
        From::Ethernet& ethernet = from.ethernet();
        From::Random& random = from.random();
        From::Md5& md5 = from.md5();

        // get current UUID time (64 bits)
        //
        uint64_t uuidTime = Time();

        // Encode the time into the UUID struct (host order).
        //
        m_wrapped.m_timeLow.m_l = (uint32_t)(uuidTime & XOS_NETWORK_UNIQUE_ACTUAL_IDENTIFIER_TIME_LOW_BM);
        m_wrapped.m_timeMid.m_w = (uint16_t)((uuidTime & XOS_NETWORK_UNIQUE_ACTUAL_IDENTIFIER_TIME_MID_BM) >> XOS_NETWORK_UNIQUE_ACTUAL_IDENTIFIER_TIME_MID_BS);
        m_wrapped.m_timeHiAndVersion.m_w = (uint16_t)((uuidTime & XOS_NETWORK_UNIQUE_ACTUAL_IDENTIFIER_TIME_HI_BM) >> XOS_NETWORK_UNIQUE_ACTUAL_IDENTIFIER_TIME_HI_BS);
        m_wrapped.m_timeHiAndVersion.m_w |= (uint16_t)(actual::Identifier::VERSION_TIME_BASED << XOS_NETWORK_UNIQUE_ACTUAL_IDENTIFIER_TIME_HI_VERSION_BS);

        // Convert time part to MSB (network order)
        //
        TimeToMsb();

        ssize_t count = 0;
        ssize_t length = 0;
        size_t size = 0;

        // get clock seqence from a crypto-quality
        // random number generator.
        //
        uint16_t uuidClockSeq = 0;
        size  = sizeof(uuidClockSeq);
        if (size != (count = random.Generate(&uuidClockSeq, size))) {
            XOS_LOG_ERROR("failed " << count << " on random.Generate(..., " << size << ")");
            return false;
        }

        // Encode the sequence into the UUID struct (network order).
        //
        m_wrapped.m_clockSeq.m_low = (uuidClockSeq & XOS_NETWORK_UNIQUE_ACTUAL_IDENTIFIER_CLOCK_SEQ_LOW_BM);
        m_wrapped.m_clockSeq.m_hiAndRes = ((uuidClockSeq & XOS_NETWORK_UNIQUE_ACTUAL_IDENTIFIER_CLOCK_SEQ_HI_BM) >> XOS_NETWORK_UNIQUE_ACTUAL_IDENTIFIER_CLOCK_SEQ_HI_BS);
        m_wrapped.m_clockSeq.m_hiAndRes |= (XOS_NETWORK_UNIQUE_ACTUAL_IDENTIFIER_RESERVED_VARIANT_RFC4122_BV << XOS_NETWORK_UNIQUE_ACTUAL_IDENTIFIER_CLOCK_SEQ_HI_RESERVED_BS);

        // get node ID from the MAC address.
        //
        const From::MacAddress* macAddress = ethernet.Address();
        if ((macAddress)) {
            XOS_LOG_TRACE("MAC address = " << HexString(macAddress->m_b, sizeof(macAddress->m_b), ':'));

            // copy MAC address to node ID (network order).
            //
            memcpy(m_wrapped.m_node.m_b, macAddress->m_b, sizeof(m_wrapped.m_node.m_b));
        } else {
            XOS_LOG_ERROR("failed 0 on ethernet.Address()");
            return false;
        }

        // Generate an MD5 hash of the MAC address to
        // hide it's identity.
        //
        uint8_t hash[16];
        if ((sizeof(hash)) != (count = md5(hash, sizeof(hash), m_wrapped.m_b, sizeof(m_wrapped.m_b)))) {
            XOS_LOG_ERROR("failed " << count << " on md5()");
            return false;
        } else {
            XOS_LOG_TRACE("MD5 hash = " << HexString(hash, sizeof(hash)));
            memcpy(m_wrapped.m_node.m_b, hash, sizeof(m_wrapped.m_node.m_b));
        }

        // Set MAC address multicast bit per RFC4122
        //
        m_wrapped.m_node.m_macAddress.m_oui.m_b[0] &= ~XOS_NETWORK_ETHERNET_ACTUAL_ADDRESS_OUI_BM_MULTICAST;
        m_wrapped.m_node.m_macAddress.m_oui.m_b[0] |= XOS_NETWORK_ETHERNET_ACTUAL_ADDRESS_OUI_BV_MULTICAST;
        return true;
    }
    virtual void Clear() {
        Extends::Clear();
    }
protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual uint64_t Time() const {
        uint64_t now = 0;
        struct timeval tv;

        // get current time
        //
        gettimeofday(&tv, (struct timezone*)0);

        // Offset between UUID formatted times and Unix formatted times.
        // UUID UTC base time is October 15, 1582.
        // Unix base time is January 1, 1970.
        //
        now = (tv.tv_sec * 10000000) + (tv.tv_usec * 10) + 0x01B21DD213814000LL;
        return now;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
};

} // namespace unix 
} // namespace unique 
} // namespace network 
} // namespace xos 

#endif // _XOS_NETWORK_UNIQUE_UNIX_IDENTIFIER_HPP 
