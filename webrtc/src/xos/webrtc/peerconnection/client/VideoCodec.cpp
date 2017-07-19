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
///   File: VideoCodec.cpp
///
/// Author: $author$
///   Date: 1/18/2013
///////////////////////////////////////////////////////////////////////
#include "xos/webrtc/peerconnection/client/VideoCodec.hpp"

namespace xos {
namespace webrtc {
namespace peerconnection {
namespace client {

///////////////////////////////////////////////////////////////////////
///  Class: VideoCodec
///
/// Author: $author$
///   Date: 1/18/2013
///////////////////////////////////////////////////////////////////////
std::string VideoCodec::ModeToString(Mode mode) {
    std::string s;
    switch (mode)
    {
    case XOS_WEBRTC_PEERCONNECTION_CLIENT_VIDEO_CODEC_MODE_CIF:
        s = XOS_WEBRTC_PEERCONNECTION_CLIENT_VIDEO_CODEC_MODE_NAME_CIF;
        break;

    case XOS_WEBRTC_PEERCONNECTION_CLIENT_VIDEO_CODEC_MODE_4CIF:
        s = XOS_WEBRTC_PEERCONNECTION_CLIENT_VIDEO_CODEC_MODE_NAME_4CIF;
        break;

    case XOS_WEBRTC_PEERCONNECTION_CLIENT_VIDEO_CODEC_MODE_QQVGA:
        s = XOS_WEBRTC_PEERCONNECTION_CLIENT_VIDEO_CODEC_MODE_NAME_QQVGA;
        break;

    case XOS_WEBRTC_PEERCONNECTION_CLIENT_VIDEO_CODEC_MODE_QVGA:
        s = XOS_WEBRTC_PEERCONNECTION_CLIENT_VIDEO_CODEC_MODE_NAME_QVGA;
        break;

    case XOS_WEBRTC_PEERCONNECTION_CLIENT_VIDEO_CODEC_MODE_VGA:
        s = XOS_WEBRTC_PEERCONNECTION_CLIENT_VIDEO_CODEC_MODE_NAME_VGA;
        break;

    case XOS_WEBRTC_PEERCONNECTION_CLIENT_VIDEO_CODEC_MODE_HD:
        s = XOS_WEBRTC_PEERCONNECTION_CLIENT_VIDEO_CODEC_MODE_NAME_HD;
        break;

    case XOS_WEBRTC_PEERCONNECTION_CLIENT_VIDEO_CODEC_MODE_FHD:
        s = XOS_WEBRTC_PEERCONNECTION_CLIENT_VIDEO_CODEC_MODE_NAME_FHD;
        break;
    }
    return s;
}
VideoCodec::Mode VideoCodec::StringToMode(const std::string& s) {
    Mode mode = XOS_WEBRTC_PEERCONNECTION_CLIENT_VIDEO_CODEC_MODE_UNKNOWN;

    if (!(s.compare(XOS_WEBRTC_PEERCONNECTION_CLIENT_VIDEO_CODEC_MODE_NAME_CIF)))
        mode = XOS_WEBRTC_PEERCONNECTION_CLIENT_VIDEO_CODEC_MODE_CIF;
    else
    if (!(s.compare(XOS_WEBRTC_PEERCONNECTION_CLIENT_VIDEO_CODEC_MODE_NAME_4CIF)))
        mode = XOS_WEBRTC_PEERCONNECTION_CLIENT_VIDEO_CODEC_MODE_4CIF;
    else
    if (!(s.compare(XOS_WEBRTC_PEERCONNECTION_CLIENT_VIDEO_CODEC_MODE_NAME_QQVGA)))
        mode = XOS_WEBRTC_PEERCONNECTION_CLIENT_VIDEO_CODEC_MODE_QQVGA;
    else
    if (!(s.compare(XOS_WEBRTC_PEERCONNECTION_CLIENT_VIDEO_CODEC_MODE_NAME_QVGA)))
        mode = XOS_WEBRTC_PEERCONNECTION_CLIENT_VIDEO_CODEC_MODE_QVGA;
    else
    if (!(s.compare(XOS_WEBRTC_PEERCONNECTION_CLIENT_VIDEO_CODEC_MODE_NAME_VGA)))
        mode = XOS_WEBRTC_PEERCONNECTION_CLIENT_VIDEO_CODEC_MODE_VGA;
    else
    if (!(s.compare(XOS_WEBRTC_PEERCONNECTION_CLIENT_VIDEO_CODEC_MODE_NAME_HD)))
        mode = XOS_WEBRTC_PEERCONNECTION_CLIENT_VIDEO_CODEC_MODE_HD;
    else
    if (!(s.compare(XOS_WEBRTC_PEERCONNECTION_CLIENT_VIDEO_CODEC_MODE_NAME_FHD)))
        mode = XOS_WEBRTC_PEERCONNECTION_CLIENT_VIDEO_CODEC_MODE_FHD;

    return mode;
}

} // namespace client 
} // namespace peerconnection 
} // namespace webrtc 
} // namespace xos 
