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
///   File: PluginWindow.hpp
///
/// Author: $author$
///   Date: 1/17/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_WEBRTC_PEERCONNECTION_CLIENT_FIREBREATH_WINDOWS_PLUGINWINDOW_HPP
#define _XOS_WEBRTC_PEERCONNECTION_CLIENT_FIREBREATH_WINDOWS_PLUGINWINDOW_HPP

#include "xos/webrtc/peerconnection/client/firebreath/PluginWindow.hpp"

namespace xos {
namespace webrtc {
namespace peerconnection {
namespace client {
namespace firebreath {
namespace windows {

typedef firebreath::PluginWindow<client::MainWindow> PluginWindowExtend;
///////////////////////////////////////////////////////////////////////
///  Class: PluginWindow
///
/// Author: $author$
///   Date: 1/17/2013
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS PluginWindow: public PluginWindowExtend {
public:
    typedef PluginWindowExtend Extends;

    PluginWindow
    (const char* serverName, int serverPort,
     bool autoConnectToPeerOn=XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOW_DEFAULT_AUTO_CONNECT_TO_PEER_ON, 
     bool autoConnectToPeerAfterOn=XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOW_DEFAULT_AUTO_CONNECT_TO_PEER_AFTER_ON,
     bool showConnectionState=XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOW_DEFAULT_SHOW_CONNECTION_STATE,
     bool handleButtonEvents=XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOW_DEFAULT_HANDLE_BUTTON_EVENTS,
     bool postButtonEventUIMessages=XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOW_DEFAULT_POST_BUTTON_EVENT_UI_MESSAGES,
     bool useUIMessageQueue=XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOW_DEFAULT_USE_UI_MESSAGE_QUEUE,
     bool useOpenGLRenderer=XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOW_DEFAULT_USE_OPENGL_RENDERER)
    : Extends
      (serverName, serverPort, 
       autoConnectToPeerOn, autoConnectToPeerAfterOn, 
       showConnectionState, handleButtonEvents, postButtonEventUIMessages,
       useUIMessageQueue, useOpenGLRenderer) {
    }
    virtual ~PluginWindow() {
    }
};

} // namespace windows 
} // namespace firebreath 
} // namespace client 
} // namespace peerconnection 
} // namespace webrtc 
} // namespace xos 

#endif // _XOS_WEBRTC_PEERCONNECTION_CLIENT_FIREBREATH_WINDOWS_PLUGINWINDOW_HPP 
