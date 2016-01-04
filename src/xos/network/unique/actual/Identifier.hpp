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
#ifndef _XOS_NETWORK_UNIQUE_ACTUAL_IDENTIFIER_HPP
#define _XOS_NETWORK_UNIQUE_ACTUAL_IDENTIFIER_HPP

#include "xos/network/ethernet/actual/Address.hpp"

#define XOS_NETWORK_UNIQUE_ACTUAL_IDENTIFIER_TIME_LOW_BM 0x00000000FFFFFFFFLL
#define XOS_NETWORK_UNIQUE_ACTUAL_IDENTIFIER_TIME_LOW_BS 0

#define XOS_NETWORK_UNIQUE_ACTUAL_IDENTIFIER_TIME_MID_BM 0x0000FFFF00000000LL
#define XOS_NETWORK_UNIQUE_ACTUAL_IDENTIFIER_TIME_MID_BS 32

#define XOS_NETWORK_UNIQUE_ACTUAL_IDENTIFIER_TIME_HI_BM 0x0FFF000000000000LL
#define XOS_NETWORK_UNIQUE_ACTUAL_IDENTIFIER_TIME_HI_BS 48

#define XOS_NETWORK_UNIQUE_ACTUAL_IDENTIFIER_TIME_HI_VERSION_BM 0xF000
#define XOS_NETWORK_UNIQUE_ACTUAL_IDENTIFIER_TIME_HI_VERSION_BS 12

#define XOS_NETWORK_UNIQUE_ACTUAL_IDENTIFIER_VERSION_BM 0xF0
#define XOS_NETWORK_UNIQUE_ACTUAL_IDENTIFIER_VERSION_BS 4

#define XOS_NETWORK_UNIQUE_ACTUAL_IDENTIFIER_CLOCK_SEQ_LOW_BM 0x00FF
#define XOS_NETWORK_UNIQUE_ACTUAL_IDENTIFIER_CLOCK_SEQ_LOW_BS 0

#define XOS_NETWORK_UNIQUE_ACTUAL_IDENTIFIER_CLOCK_SEQ_HI_BM 0x1F00
#define XOS_NETWORK_UNIQUE_ACTUAL_IDENTIFIER_CLOCK_SEQ_HI_BS 8

#define XOS_NETWORK_UNIQUE_ACTUAL_IDENTIFIER_CLOCK_SEQ_HI_RESERVED_BM 0xE0
#define XOS_NETWORK_UNIQUE_ACTUAL_IDENTIFIER_CLOCK_SEQ_HI_RESERVED_BS 5

#define XOS_NETWORK_UNIQUE_ACTUAL_IDENTIFIER_RESERVED_VARIANT_NCS_COMPATIBILITY_BM 0x4
#define XOS_NETWORK_UNIQUE_ACTUAL_IDENTIFIER_RESERVED_VARIANT_NCS_COMPATIBILITY_BV 0x0

#define XOS_NETWORK_UNIQUE_ACTUAL_IDENTIFIER_RESERVED_VARIANT_RFC4122_BM 0x6
#define XOS_NETWORK_UNIQUE_ACTUAL_IDENTIFIER_RESERVED_VARIANT_RFC4122_BV 0x4

#define XOS_NETWORK_UNIQUE_ACTUAL_IDENTIFIER_RESERVED_VARIANT_MICROSOFT_COMPATIBILITY_BM 0x7
#define XOS_NETWORK_UNIQUE_ACTUAL_IDENTIFIER_RESERVED_VARIANT_MICROSOFT_COMPATIBILITY_BV 0x6

#define XOS_NETWORK_UNIQUE_ACTUAL_IDENTIFIER_RESERVED_VARIANT_FUTURE_DEFINITION_BM 0x7
#define XOS_NETWORK_UNIQUE_ACTUAL_IDENTIFIER_RESERVED_VARIANT_FUTURE_DEFINITION_BV 0x7

namespace xos {
namespace network {
namespace unique {
namespace actual {

#include "xos/base/Platform_packed_begin.hpp"
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
struct PACKED_STRUCT Identifier {
    enum {
        VERSION_NONE            = 0x0,

        VERSION_TIME_BASED      = 0x1,
        VERSION_DCE_SECURITY    = 0x2,
        VERSION_NAME_BASED_MD5  = 0x3,
        VERSION_RANDOM          = 0x4,
        VERSION_NAME_BASED_SHA1 = 0x5,

        VERSION_NEXT,
        VERSION_FIRST = VERSION_NONE+1,
        VERSION_LAST = VERSION_NEXT-1,
        VERSION_COUNT = VERSION_LAST-VERSION_FIRST+1
    };
    enum {
        RESERVED_VARIANT_FIRST,

        RESERVED_VARIANT_FUTURE_DEFINITION = RESERVED_VARIANT_FIRST,
        RESERVED_VARIANT_MICROSOFT_COMPATIBILITY,
        RESERVED_VARIANT_RFC4122,
        RESERVED_VARIANT_NCS_COMPATIBILITY,

        RESERVED_VARIANT_NEXT,
        RESERVED_VARIANT_LAST = RESERVED_VARIANT_NEXT-1,
        RESERVED_VARIANT_COUNT = RESERVED_VARIANT_LAST-RESERVED_VARIANT_FIRST+1
    };
    typedef ethernet::actual::Address MacAddress;

    union {
        uint8_t m_b[16];
        uint16_t m_w[8];
        uint32_t m_l[4];

        struct PACKED_STRUCT {
            union {
                uint8_t m_b[4];
                uint16_t m_w[2];
                uint32_t m_l;
            } m_timeLow;

            union {
                uint8_t m_b[2];
                uint16_t m_w;
            } m_timeMid;

            union {
                uint8_t m_b[2];
                uint16_t m_w;

                struct PACKED_STRUCT {
                    uint8_t m_version;
                    uint8_t m_hi;
                };
            } m_timeHiAndVersion;

            union {
                uint8_t m_b[2];
                uint16_t m_w;

                struct PACKED_STRUCT {
                    uint8_t m_hiAndRes;
                    uint8_t m_low;
                };
            } m_clockSeq;

            union {
                uint8_t m_b[6];
                uint16_t m_w[3];

                struct PACKED_STRUCT {
                    union {
                        uint8_t m_b[2];
                        uint16_t m_w;
                    } m_nodeHi;

                    union {
                        uint8_t m_b[4];
                        uint16_t m_w[2];
                        uint32_t m_l;
                    } m_nodeLow;
                };

                MacAddress m_macAddress;
            } m_node;
        };
    };
};
#include "xos/base/Platform_packed_end.hpp"

} // namespace actual
} // namespace unique 
} // namespace network 
} // namespace xos 

#endif // _XOS_NETWORK_UNIQUE_ACTUAL_IDENTIFIER_HPP
