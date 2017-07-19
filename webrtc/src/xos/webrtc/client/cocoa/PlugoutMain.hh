///////////////////////////////////////////////////////////////////////
/// Copyright 2013, Google Inc.
///
/// Redistribution and use in source and binary forms, with or without
/// modification, are permitted provided that the following conditions are met:
/// 
///  1. Redistributions of source code must retain the above copyright notice,
///     this list of conditions and the following disclaimer.
///  2. Redistributions in binary form must reproduce the above copyright notice,
///     this list of conditions and the following disclaimer in the documentation
///     and/or other materials provided with the distribution.
///  3. The name of the author may not be used to endorse or promote products
///     derived from this software without specific prior written permission.
/// 
/// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
/// WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
/// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
/// EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
/// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
/// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
/// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
/// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
/// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
/// ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
///
///   File: PlugoutMain.hh
///
/// Author: $author$
///   Date: 3/10/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_WEBRTC_CLIENT_COCOA_PLUGOUTMAIN_HH
#define _XOS_WEBRTC_CLIENT_COCOA_PLUGOUTMAIN_HH

#include "xos/webrtc/client/console/PlugoutWindowPeer.hpp"
#include "xos/os/Main.hpp"

namespace xos {
namespace webrtc {
namespace client {
namespace cocoa {

///////////////////////////////////////////////////////////////////////
///  Class: PlugoutMainImplement
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS PlugoutMainImplement
: virtual public xos::MainImplement,
  virtual public ImageInterface
{
public:
    typedef xos::MainImplement Implements;
    typedef ImageInterface ImageImplements;
};
typedef Main PlugoutMainExtend;
///////////////////////////////////////////////////////////////////////
///  Class: PlugoutMain
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS PlugoutMain
: virtual public PlugoutMainImplement, public PlugoutMainExtend {
public:
    typedef PlugoutMainImplement Implements;
    typedef PlugoutMainExtend Extends;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: PlugoutMain
    ///////////////////////////////////////////////////////////////////////
    PlugoutMain() 
    : m_autoConnectToPeerOn(false),
      m_connectedToServer(false)
    {
    }
    virtual ~PlugoutMain() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int BeforeRun(int argc, char**argv, char**env) {
        int err = 1;
        if ((m_mainWindow.Open())) {
            XOS_LOG_DEBUG("ConnectToServer()...");
            m_mainWindow.SetAutoConnectToPeerOn(m_autoConnectToPeerOn);
            m_mainWindow.SetAutoConnectToPeerAfterOn(m_autoConnectToPeerOn);
            m_connectedToServer = m_mainWindow.ConnectToServer();
            err = 0;
        }
        return err;
    }
    virtual int AfterRun(int argc, char**argv, char**env) {
        int err = 1;
        if ((m_connectedToServer)) {
            XOS_LOG_DEBUG("DisconnectFromServer()..");
            m_mainWindow.DisconnectFromServer();
            m_connectedToServer = false;
        }
        if ((m_mainWindow.Close())) {
            err = 0;
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ImageInterface* ImageInterfaceDelegated() const {
        return (ImageInterface*)(&m_mainWindow);
    }

protected:
    console::PlugoutWindowPeer m_mainWindow;
    bool m_autoConnectToPeerOn;
    bool m_connectedToServer;
};

} // namespace cocoa 
} // namespace client 
} // namespace webrtc 
} // namespace xos 

#endif // _XOS_WEBRTC_CLIENT_COCOA_PLUGOUTMAIN_HH 
