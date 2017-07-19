///////////////////////////////////////////////////////////////////////
/// Copyright 2012, Google Inc.
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
///   Date: 10/18/2012
///////////////////////////////////////////////////////////////////////
#include "xos/webrtc/client/VideoCodec.hpp"

#if !defined(NO_WEBRTC_VCM_PATCH)
namespace webrtc
{
extern int vcm_default_codec_width;
extern int vcm_default_codec_height;
extern int vcm_default_frame_rate;
extern int vcm_default_min_bitrate;
extern int vcm_default_flush_inicator;
}
#else // !defined(NO_WEBRTC_VCM_PATCH)
#endif // !defined(NO_WEBRTC_VCM_PATCH)

namespace xos {
namespace webrtc {
namespace client {

VideoCodec::VideoCodec(Mode mode) {
    if (0 < (mode))
        SetDefaultMode(mode);
}
VideoCodec::~VideoCodec() {
}

VideoCodec::Mode VideoCodec::SetDefaultMode(Mode toMode) {
    Mode mode = XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_NONE;
#if !defined(NO_WEBRTC_VCM_PATCH)
    int video_codec_cols;
    int video_codec_rows;

    if (0 < (video_codec_cols = XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_COLS(toMode)))
    if (0 < (video_codec_rows = XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_ROWS(toMode)))
    {
        ::webrtc::vcm_default_codec_width = video_codec_cols;
        ::webrtc::vcm_default_codec_height = video_codec_rows;
        mode = toMode;
    }
#else // !defined(NO_WEBRTC_VCM_PATCH)
#endif // !defined(NO_WEBRTC_VCM_PATCH)
    return mode;
}

#if !defined(NO_WEBRTC_VCM_PATCH)
VideoCodec::Mode
MatchMode(VideoCodec::Mode toMode, int width, int height)
{
    VideoCodec::Mode mode = XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_NONE;
    int video_codec_cols;
    int video_codec_rows;

    if (0 < (video_codec_cols = XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_COLS(toMode)))
    if (0 < (video_codec_rows = XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_ROWS(toMode)))
    if ((video_codec_cols == width) && (video_codec_rows == height))
        return toMode;
    return mode;
}
#else // !defined(NO_WEBRTC_VCM_PATCH)
#endif // !defined(NO_WEBRTC_VCM_PATCH)

VideoCodec::Mode VideoCodec::GetDefaultMode() const {
    Mode mode = XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_NONE;
#if !defined(NO_WEBRTC_VCM_PATCH)
    int width = ::webrtc::vcm_default_codec_width;
    int height = ::webrtc::vcm_default_codec_height;

    if (0 >= (mode = MatchMode(XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_CIF, width, height)))
    if (0 >= (mode = MatchMode(XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_4CIF, width, height)))
    if (0 >= (mode = MatchMode(XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_QQVGA, width, height)))
    if (0 >= (mode = MatchMode(XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_QVGA, width, height)))
    if (0 >= (mode = MatchMode(XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_VGA, width, height)))
    if (0 >= (mode = MatchMode(XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_HD, width, height)))
    if (0 >= (mode = MatchMode(XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_FHD, width, height)))
        return mode;
#else // !defined(NO_WEBRTC_VCM_PATCH)
#endif // !defined(NO_WEBRTC_VCM_PATCH)
    return mode;
}

void VideoCodec::SetDefaultOptions
(int codecWidth, int codecHeight, int frameRate, int minBitrate) {
#if !defined(NO_WEBRTC_VCM_PATCH)
    ::webrtc::vcm_default_codec_width = codecWidth;
    ::webrtc::vcm_default_codec_height = codecHeight;
    ::webrtc::vcm_default_frame_rate = frameRate;
    ::webrtc::vcm_default_min_bitrate =  minBitrate;
#else // !defined(NO_WEBRTC_VCM_PATCH)
#endif // !defined(NO_WEBRTC_VCM_PATCH)
}
void VideoCodec::GetDefaultOptions
(int& codecWidth, int& codecHeight, int& frameRate, int& minBitrate) const {
#if !defined(NO_WEBRTC_VCM_PATCH)
    codecWidth = ::webrtc::vcm_default_codec_width;
    codecHeight = ::webrtc::vcm_default_codec_height;
    frameRate = ::webrtc::vcm_default_frame_rate;
    minBitrate = ::webrtc::vcm_default_min_bitrate;
#else // !defined(NO_WEBRTC_VCM_PATCH)
#endif // !defined(NO_WEBRTC_VCM_PATCH)
}

std::string VideoCodec::ModeToString(Mode mode) {
    std::string s;
    switch (mode)
    {
    case XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_CIF:
        s = XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_NAME_CIF;
        break;

    case XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_4CIF:
        s = XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_NAME_4CIF;
        break;

    case XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_QQVGA:
        s = XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_NAME_QQVGA;
        break;

    case XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_QVGA:
        s = XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_NAME_QVGA;
        break;

    case XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_VGA:
        s = XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_NAME_VGA;
        break;

    case XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_HD:
        s = XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_NAME_HD;
        break;

    case XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_FHD:
        s = XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_NAME_FHD;
        break;
    }
    return s;
}
VideoCodec::Mode VideoCodec::StringToMode(const std::string& s) {
    Mode mode = XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_UNKNOWN;

    if (!(s.compare(XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_NAME_CIF)))
        mode = XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_CIF;
    else
    if (!(s.compare(XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_NAME_4CIF)))
        mode = XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_4CIF;
    else
    if (!(s.compare(XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_NAME_QQVGA)))
        mode = XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_QQVGA;
    else
    if (!(s.compare(XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_NAME_QVGA)))
        mode = XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_QVGA;
    else
    if (!(s.compare(XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_NAME_VGA)))
        mode = XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_VGA;
    else
    if (!(s.compare(XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_NAME_HD)))
        mode = XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_HD;
    else
    if (!(s.compare(XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_NAME_FHD)))
        mode = XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_FHD;

    return mode;
}

} // namespace client 
} // namespace webrtc 
} // namespace xos 
