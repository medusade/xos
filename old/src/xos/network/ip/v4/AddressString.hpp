///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2012 $organization$
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
///   File: AddressString.hpp
///
/// Author: $author$
///   Date: 10/18/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_NETWORK_IP_V4_ADDRESSSTRING_HPP
#define _XOS_NETWORK_IP_V4_ADDRESSSTRING_HPP

#include "xos/base/String.hpp"

namespace xos {
namespace network {
namespace ip {
namespace v4 {

typedef String AddressStringExtend;

class _EXPORT_CLASS AddressString: public AddressStringExtend {
public:
    typedef AddressStringExtend Extends;

    AddressString(const char* chars, size_t length): Extends(chars, length) {
    }
    AddressString(const char* chars): Extends(chars) {
    }
    AddressString(const std::string& copy): Extends(copy) {
    }
    AddressString() {
    }

    virtual uint32_t ToUInt32() const {
        uint32_t addr = 0;
        uint8_t octet;
        size_t octetLen;
        const char* chars;
        size_t len;
        char c;

        if (0 < (len = length()))
        if ((chars = c_str()))
        {
            for (octet = 0, octetLen = 0; len; ++chars, --len)
            {
                switch(c = *chars)
                {
                case '.':
                    addr = ((addr << 8) | octet);
                    octet = 0;
                    octetLen = 0;
                    break;

                default:
                    if ((c < '0') || (c > '9'))
                        return 0;
                    octet = ((octet * 10) + (c - '0'));
                    ++octetLen;
                }
            }
            if ((octetLen))
                addr = ((addr << 8) | octet);
        }
        return addr;
    }
    virtual operator uint32_t() const {
        uint32_t addr = ToUInt32();
        return addr;
    }
};

} // namespace v4 
} // namespace ip 
} // namespace network 
} // namespace xos 

#endif // _XOS_NETWORK_IP_V4_ADDRESSSTRING_HPP 
