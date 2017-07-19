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
///   File: VideoRenderer.hpp
///
/// Author: $author$
///   Date: 10/19/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_WEBRTC_CLIENT_VIDEORENDERER_HPP
#define _XOS_WEBRTC_CLIENT_VIDEORENDERER_HPP

#include "xos/base/Base.hpp"
#include "talk/session/phone/mediachannel.h"
#include "talk/session/phone/videocommon.h"
#include "talk/session/phone/videoframe.h"
#include "talk/session/phone/videorenderer.h"
#include <map>
#include <string>

namespace xos {
namespace webrtc {
namespace client {

typedef cricket::VideoRenderer VideoRendererExtend;

class _EXPORT_CLASS VideoRendererImplemented;

class _EXPORT_CLASS VideoRenderer: public VideoRendererExtend {
public:
    typedef VideoRendererExtend Extends;
    
    VideoRenderer
    (size_t width=0, size_t height=0, bool isRemote=false)
    : frame_width_(0), frame_height_(0),
      image_width_(width), image_height_(height),
      image_size_(width * height * 4),
      m_isRemote(isRemote){
    }
    virtual ~VideoRenderer() {
    }

    virtual bool SetSize(int width, int height, int reserved = 0) {
        AutoLock<VideoRenderer> lock(this);
        UpdateImageSize(width, height);
        return true;
    }

    virtual bool RenderFrame(const cricket::VideoFrame* frame) {
        if ((frame)) {
            AutoLock<VideoRenderer> lock(this);

            frame_height_ = frame->GetHeight();
            frame_width_ = frame->GetWidth();

            ASSERT(image_.get() != NULL);

            frame->ConvertToRgbBuffer
            (RenderImageFormat(), image_.get(),
             image_size_, image_width_ * 4);

            UpdateVisibleFrame();
            return true;
        }
        return false;
    }

    virtual void ConvertARGBToABGR() {
        enum { ARGB_B, ARGB_G, ARGB_R, ARGB_A };
        enum { ABGR_R, ABGR_G, ABGR_B, ABGR_A };
        uint8 argbImageT;
        uint8* argbImage;
        uint8* argbImageEnd;

        //
        // Convert from ARGB to ABGR
        //
        if ((argbImage = image_.get())) {
            for (argbImageEnd = argbImage+image_size_; 
                 argbImage < argbImageEnd; argbImage += 4)
            {
                argbImageT = argbImage[ARGB_B];
                argbImage[ABGR_R] = argbImage[ARGB_R];
                argbImage[ABGR_B] = argbImageT;
            }
        }
    }

    virtual cricket::FourCC RenderImageFormat() const 
    { return cricket::FOURCC_ARGB; }

    virtual VideoRendererImplemented* RendererImplemented() const
    { return 0; }

    virtual void UpdateImageSize(int width, int height) {
        if ((image_size_ = (image_width_ = width) * (image_height_ = height) * 4))
            image_.reset(new uint8[image_size_]);
    }
    virtual void UpdateVisibleFrame() {}

    virtual void Lock() {}
    virtual void Unlock() {}

    size_t frame_width() const { return frame_width_; }
    size_t frame_height() const { return frame_height_; }

    size_t image_width() const { return image_width_; }
    size_t image_height() const { return image_height_; }

    const uint8* image() const { return image_.get(); }
    uint8* d_image() const { return image_.get(); }

protected:
    template <typename T>
    class AutoLock
    {
     public:
      explicit AutoLock(T* obj) : obj_(obj) { obj_->Lock(); }
      ~AutoLock() { obj_->Unlock(); }
     protected:
      T* obj_;
    };

protected:
    bool m_isRemote;
    size_t frame_width_;
    size_t frame_height_;
    size_t image_width_;
    size_t image_height_;
    size_t image_size_;
    talk_base::scoped_array<uint8> image_;
};

} // namespace client 
} // namespace webrtc 
} // namespace xos 

#endif // _XOS_WEBRTC_CLIENT_VIDEORENDERER_HPP 
