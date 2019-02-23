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
///   File: Address.hpp
///
/// Author: $author$
///   Date: 2/14/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_NETWORK_ETHERNET_MACOSX_ADDRESS_HPP
#define _XOS_NETWORK_ETHERNET_MACOSX_ADDRESS_HPP

#include "xos/network/ethernet/Address.hpp"
#include "xos/os/Logger.hpp"
#include <sys/socket.h>
#include <net/if.h>
#include <net/if_dl.h>
#include <net/if_types.h>
#include <ifaddrs.h>

namespace xos {
namespace network {
namespace ethernet {
namespace macosx {

typedef ethernet::AddressImplement AddressImplement;
typedef ethernet::Address AddressExtend;
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class EXPORT_CLASS Address: virtual public AddressImplement, public AddressExtend {
public:
    typedef AddressImplement Implements;
    typedef AddressExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Address(const Address& copy): Extends(copy) {
    }
    Address() {
    }
    virtual ~Address() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual Actual* SetToAdapter(const String& named) {
        size_t namedLength;
        const char* namedChars;

        if ((namedChars = named.Chars(namedLength)) && (0 < (namedLength))) {
            struct ifaddrs* ifa = 0;
            const Actual* actual;

            Clear();

            if ((actual = GetFirst(ifa))) {
                struct sockaddr_dl* dl;
                const char* nameChars;
                size_t nameLength;
                int unequal;
                do {
                    if ((dl = (struct sockaddr_dl*)(ifa->ifa_addr))) {
                        if ((nameChars = (const char*)(dl->sdl_data))
                             && (0 < (nameLength = (size_t)(dl->sdl_nlen)))) {
                            String name(nameChars, nameLength);
                            if (!(unequal = name.Compare(named))) {
                                XOS_LOG_TRACE("matched address of interface \"" << name << "\"");
                                Set(*actual, name, dl->sdl_index);
                                return &m_wrapped;
                            }
                        }
                    }
                } while ((actual = GetNext(ifa)));
            }
        }
        return 0;
    }
    virtual Actual* SetToFirstAdapter() {
        return SetToAdapter(0);
    }
    virtual Actual* SetToLastAdapter() {
        return SetToAdapter(-1);
    }
    virtual Actual* SetToAdapter(int index) {
        struct ifaddrs* ifa = 0;
        const Actual* actual;

        Clear();

        if ((actual = GetFirst(ifa))) {
            struct sockaddr_dl* dl = 0;
            const char* nameChars = 0;
            size_t nameLength = 0;
            do {
                if ((dl = (struct sockaddr_dl*)(ifa->ifa_addr))) {
                    if ((nameChars = (const char*)(dl->sdl_data))
                         && (0 < (nameLength = (size_t)(dl->sdl_nlen)))) {
                        if ((1 > index) || ((dl->sdl_index) && (index == dl->sdl_index))) {
                            XOS_LOG_TRACE("matched address of interface [" << dl->sdl_index << "]");
                            Set(*actual, String(nameChars, nameLength), dl->sdl_index);
                            return &m_wrapped;
                        }
                    }
                }
            } while ((actual = GetNext(ifa)));
            if ((dl) && (nameChars) && (nameLength)) {
                if ((0 > index)) {
                    XOS_LOG_TRACE("matched address of interface [" << dl->sdl_index << "]");
                    Set(*actual, String(nameChars, nameLength), dl->sdl_index);
                    return &m_wrapped;
                }
            }
        }
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const Actual* GetFirst() const {
        return GetNext(0);
    }
    virtual const Actual* GetNext(const Actual* to) const {
        struct ifaddrs* ifa = 0;
        const Actual* actual = 0;
        if ((actual = GetFirst(ifa))) {
            if ((to)) {
                do {
                    if ((*to) == (*actual)) {
                        actual = GetNext(ifa);
                        break;
                    }
                } while ((actual = GetNext(ifa)));
            }
        }
        return actual;
    }
    virtual const Actual* GetLast() const {
        return 0;
    }
    virtual const Actual* GetPrev(const Actual* to) const {
        return 0;
    }
protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const Actual* GetFirst(struct ifaddrs*& ifa) const {
        int err;
        if (!(err = getifaddrs(&ifa)) && (ifa)) {
            const Actual* actual;
            do {
                if ((actual = Get(ifa)))
                    return actual;
            } while ((ifa = ifa->ifa_next));
        } else {
            XOS_LOG_ERROR("failed err = " << err << "on getifaddrs()");
        }
        return 0;
    }
    virtual const Actual* GetNext(struct ifaddrs*& ifa) const {
        if ((ifa)) {
            const Actual* actual;
            while ((ifa = ifa->ifa_next)) {
                if ((actual = Get(ifa)))
                    return actual;
            }
        }
        return 0;
    }
    virtual const Actual* Get(struct ifaddrs*& ifa) const {
        if ((ifa)) {
            struct sockaddr* sa;
            struct sockaddr_dl* dl;
            const Actual* actual;
            const char* nameChars;
            size_t nameLength;
            if ((sa = (ifa->ifa_addr))) {
                if ((AF_LINK == (sa->sa_family))
                    && (dl = (struct sockaddr_dl*)(ifa->ifa_addr))) {
                    if ((IFT_ETHER == (dl->sdl_type))
                         && (sizeof(WrappedT) == (dl->sdl_alen))
                         && (actual = (const Actual*)(LLADDR(dl)))
                         && (nameChars = (const char*)(dl->sdl_data))
                         && (0 < (nameLength = (size_t)(dl->sdl_nlen)))) {
                        String name(nameChars, nameLength);
                        XOS_LOG_TRACE("got address of interface \"" << name << "\"");
                        return actual;
                    }
                }
            }
        }
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace macosx
} // namespace ethernet 
} // namespace network 
} // namespace xos 

#endif // _XOS_NETWORK_ETHERNET_MACOSX_ADDRESS_HPP 
