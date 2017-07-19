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
///   Date: 12/25/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_WEBRTC_PEERCONNECTION_CLIENT_VIDEORENDERER_HPP
#define _XOS_WEBRTC_PEERCONNECTION_CLIENT_VIDEORENDERER_HPP

#include "xos/webrtc/peerconnection/client/UserInterface.hpp"
#include "talk/media/base/videocommon.h"
#include "talk/media/base/videoframe.h"
#include "talk/media/base/videorenderer.h"
#include "talk/base/scoped_ptr.h"

namespace xos {
namespace webrtc {
namespace peerconnection {
namespace client {

typedef webrtc::VideoRendererInterface VideoRendererExtend;
class _EXPORT_CLASS VideoRendererDerived;
///////////////////////////////////////////////////////////////////////
///  Class: VideoRenderer
///
/// Author: $author$
///   Date: 12/25/2012
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS VideoRenderer: public VideoRendererExtend {
public:
    typedef VideoRendererExtend Extends;

    VideoRenderer
    (webrtc::VideoTrackInterface* track_to_render, 
     size_t width=0, size_t height=0, bool isRemote=false)
    : m_isRemote(isRemote), frame_width_(0), frame_height_(0),
      image_width_(width), image_height_(height),
      image_size_(width * height * 4),
      rendered_track_(track_to_render) {
        AddThisRenderer();
    }
    virtual ~VideoRenderer() {
        RemoveThisRenderer();
    }

    virtual void AddThisRenderer() {
        rendered_track_->AddRenderer(this);;
    }
    virtual void RemoveThisRenderer() {
        rendered_track_->RemoveRenderer(this);
    }

    virtual void SetSize(int width, int height) {
        AutoLock<VideoRenderer> lock(this);
        UpdateImageSize(width, height);
    }

    virtual void RenderFrame(const cricket::VideoFrame* frame) {
        if ((frame)) {
            AutoLock<VideoRenderer> lock(this);

            frame_height_ = frame->GetHeight();
            frame_width_ = frame->GetWidth();

            ASSERT(image_.get() != NULL);

            frame->ConvertToRgbBuffer
            (RenderImageFormat(), image_.get(),
             image_size_, image_width_ * 4);

            UpdateVisibleFrame();
        }
    }

    virtual void ConvertARGBToABGR() {
        enum { ARGB_B, ARGB_G, ARGB_R, ARGB_A };
        enum { ABGR_R, ABGR_G, ABGR_B, ABGR_A };
        uint8 argbImageT;
        uint8* argbImage;
        uint8* argbImageEnd;

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

    virtual VideoRendererDerived* RendererDerived() const
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
    talk_base::scoped_refptr<webrtc::VideoTrackInterface> rendered_track_;
};

} // namespace client 
} // namespace peerconnection 
} // namespace webrtc 
} // namespace xos 


#endif // _XOS_WEBRTC_PEERCONNECTION_CLIENT_VIDEORENDERER_HPP 
        

