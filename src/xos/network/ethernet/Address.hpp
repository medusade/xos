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
#ifndef _XOS_NETWORK_ETHERNET_ADDRESS_HPP
#define _XOS_NETWORK_ETHERNET_ADDRESS_HPP

#include "xos/network/ethernet/actual/Address.hpp"
#include "xos/os/Logger.hpp"
#include "xos/base/String.hpp"
#include "xos/base/Wrapped.hpp"

namespace xos {
namespace network {
namespace ethernet {

typedef InterfaceBase AddressImplement;
typedef Wrapped<actual::Address, int, ExportBase, AddressImplement> AddressExtend;
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class EXPORT_CLASS Address: virtual public AddressImplement, public AddressExtend {
public:
    typedef AddressImplement Implements;
    typedef AddressExtend Extends;
    typedef actual::Address Actual;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Address(const String& adapterNamed): m_adapterIndex(-1) {
        if (!(SetToAdapter(adapterNamed))) {
            Error error = Error::Failed;
            XOS_LOG_ERROR("failed on SetToAdapter(\"" << adapterNamed << "\")");
            throw (error);
        }
    }
    Address(const Address& copy)
    : Extends(copy),
      m_adapterName(copy.m_adapterName),
      m_adapterIndex(copy.m_adapterIndex) {
    }
    Address(): m_adapterIndex(-1) {
    }
    virtual ~Address() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual Actual* SetToAdapter(const String& named) {
        return 0;
    }
    virtual Actual* SetToAdapter(int index) {
        return 0;
    }
    virtual Actual* SetToFirstAdapter() {
        return 0;
    }
    virtual Actual* SetToLastAdapter() {
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const Actual* GetFirst() const {
        return 0;
    }
    virtual const Actual* GetLast() const {
        return 0;
    }
    virtual const Actual* GetNext(const Actual* to) const {
        return 0;
    }
    virtual const Actual* GetPrev(const Actual* to) const {
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void Set(const Actual& actual, const String& adapterName, int adapterIndex) {
        memcpy(&m_wrapped, &actual, sizeof(WrappedT));
        m_adapterName.Assign(adapterName);
        m_adapterIndex = adapterIndex;
    }
    virtual void Clear() {
        memset(&m_wrapped, 0, sizeof(WrappedT));
        m_adapterName.Clear();
        m_adapterIndex = -1;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    inline Actual& actual() const {
        return (Actual&)(m_wrapped);
    }
    inline String& adapterName() const {
        return (String&)(m_adapterName);
    }
    inline int adapterIndex() const {
        return (m_adapterIndex);
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    String m_adapterName;
    int m_adapterIndex;
};

} // namespace ethernet
} // namespace network 
} // namespace xos 

#endif // _XOS_NETWORK_ETHERNET_ADDRESS_HPP 
