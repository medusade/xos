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
///   File: MainWindow.hpp
///
/// Author: $author$
///   Date: 2/18/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_NETWORK_UUID_MAINWINDOW_HPP
#define _XOS_GUI_NETWORK_UUID_MAINWINDOW_HPP

#include "xos/network/unique/os/Identifier.hpp"
#include "xos/network/ethernet/os/Address.hpp"
#include "xos/crypto/random/Pseudo.hpp"
#include "xos/crypto/hash/Md5.hpp"
#include "xos/crypto/hash/Sha1.hpp"
#include "xos/base/String.hpp"

namespace xos {
namespace gui {
namespace network {
namespace uuid {

typedef xos::network::unique::Identifier::From FromExtend;
///////////////////////////////////////////////////////////////////////
///  Class: From
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS From: public FromExtend {
public:
    typedef FromExtend Extends;
    typedef xos::crypto::random::Pseudo Random;
    typedef xos::crypto::hash::Md5 Md5;
    typedef xos::crypto::hash::Sha1 Sha1;
    typedef Extends::Ethernet EthernetExtend;
    ///////////////////////////////////////////////////////////////////////
    ///  Class: Ethernet
    ///////////////////////////////////////////////////////////////////////
    class _EXPORT_CLASS Ethernet: public EthernetExtend {
    public:
        typedef EthernetExtend Extends;
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        virtual const MacAddress* Address() const {
            return m_address.SetToFirstAdapter();
        }
        virtual const MacAddress* FirstAddress() const {
            return m_address.GetFirst();
        }
        virtual const MacAddress* NextAddress(const MacAddress* to) const {
            return m_address.GetNext(to);
        }
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
    protected:
        mutable xos::network::ethernet::os::Address m_address;
    };
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    From() {}
    virtual ~From() {}
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const MacAddress* FirstAddress() const {
        return m_ethernet.FirstAddress();
    }
    virtual const MacAddress* NextAddress(const MacAddress* to) const {
        return m_ethernet.NextAddress(to);
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual Extends::Ethernet& ethernet() const {
        return (Ethernet&)(m_ethernet);
    }
    virtual Extends::Random& random() const {
        return (Random&)(m_random);
    }
    virtual Extends::Md5& md5() const {
        return (Md5&)(m_md5);
    }
    virtual Extends::Sha1& sha1() const {
        return (Sha1&)(m_sha1);
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    Ethernet m_ethernet;
    Random m_random;
    Md5 m_md5;
    Sha1 m_sha1;
};

typedef ExportBase MainWindowExtend;
///////////////////////////////////////////////////////////////////////
///  Class: MainWindow
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS MainWindow: public MainWindowExtend {
public:
    typedef MainWindowExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    MainWindow(): m_hexA('A') {
    }
    virtual ~MainWindow() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Init() {
        return true;
    }
    virtual bool Finish() {
        return true;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool ShowUuid(const String& uuidX) {
        return false;
    }
    virtual bool ClearUuid() {
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool AddMacAddress(const String& macAddressX) {
        return false;
    }
    virtual bool ClearMacAddresses() {
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool SetMacAddress(const String& macAddressX) {
        return false;
    }
    virtual bool GetMacAddress(String& macAddressX) const {
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool GetMacAddresses() {
        const From::MacAddress* macAddress;
        From from;
        ClearMacAddresses();
        if ((macAddress = from.FirstAddress())) {
            do {
                HexString macAddressX(macAddress->m_b, sizeof(macAddress->m_b), ':');
                XOS_LOG_TRACE("add MAC address = " << macAddressX);
                AddMacAddress(macAddressX);
            } while ((macAddress = from.NextAddress(macAddress)));
        }
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool UuidGenerate() {
        From from;
        if ((m_uuid.Generate(from))) {
            return UpdateUuid();
        }
        return false;
    }
    virtual bool UuidGenerateUpdate() {
        return false;
    }
    virtual bool UuidGenerateCancel() {
        m_uuid.Clear();
        return ClearUuid();
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool UpdateUuid() {
        if ((m_uuid0 != m_uuid)) {
            String uuidX;
            StringWriter uuidWriter(uuidX);
            if (0 < (m_uuid.WriteX(uuidWriter, m_hexA))) {
                XOS_LOG_TRACE("UUID = " << uuidX);
                return ShowUuid(uuidX);
            }
        }
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool SetIsUpperX(bool to = true) {
        m_hexA = (to)?('A'):('a');
        UpdateUuid();
        return to;
    }
    virtual bool GetIsUpperX() const {
        return ('A' == m_hexA);
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    char m_hexA;
    xos::network::unique::os::Identifier m_uuid0;
    xos::network::unique::os::Identifier m_uuid;
};

} // namespace uuid 
} // namespace network 
} // namespace gui 
} // namespace xos 

#endif // _XOS_GUI_NETWORK_UUID_MAINWINDOW_HPP 
