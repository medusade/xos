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
///   File: GCRenderer.hpp
///
/// Author: $author$
///   Date: 1/15/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOWS_GCRENDERER_HPP
#define _XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOWS_GCRENDERER_HPP

#include "xos/webrtc/peerconnection/client/LocalWindow.hpp"
#include "xos/base/Base.hpp"

namespace xos {
namespace webrtc {
namespace peerconnection {
namespace client {
namespace windows {

typedef InterfaceBase GCRendererImplement;
typedef ExportBase GCRendererExtend;
///////////////////////////////////////////////////////////////////////
///  Class: GCRenderer
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS GCRenderer
: virtual public GCRendererImplement,
  public GCRendererExtend
{
public:
    typedef GCRendererImplement Implements;
    typedef GCRendererExtend Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    GCRenderer()
    : m_localWindowMinimum(XOS_WEBRTC_PEERCONNECTION_CLIENT_LOCAL_WINDOW_MINIMUM),
      m_localWindowOffet(XOS_WEBRTC_PEERCONNECTION_CLIENT_LOCAL_WINDOW_OFFSET),
      m_localWindowRatio(XOS_WEBRTC_PEERCONNECTION_CLIENT_LOCAL_WINDOW_RATIO),
      m_hWnd(0) {
    }
    virtual ~GCRenderer() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Init(HWND hWnd) { 
        if ((hWnd) && (!m_hWnd)) {
            m_hWnd = hWnd;
            ZeroMemory(&m_bmi, sizeof(m_bmi));
            m_bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
            m_bmi.bmiHeader.biPlanes = 1;
            m_bmi.bmiHeader.biBitCount = 32;
            m_bmi.bmiHeader.biCompression = BI_RGB;
            return true; 
        }
        return false;
    }
    virtual bool Finish(HWND hWnd) { 
        if ((hWnd) && (m_hWnd == hWnd)) {
            ZeroMemory(&m_bmi, sizeof(m_bmi));
            m_hWnd = 0;
            return true; 
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void Render
    (const void* remoteImage, int remoteImageWidth, int remoteImageHeight,
     const void* localImage, int localImageWidth, int localImageHeight) {
        PAINTSTRUCT ps;
        RECT rc;

        BeginPaint(m_hWnd, &ps);
        GetClientRect(m_hWnd, &rc);

        Reshape(remoteImageWidth, remoteImageHeight);
        remoteImageHeight = abs(m_bmi.bmiHeader.biHeight);
        remoteImageWidth = m_bmi.bmiHeader.biWidth;

        HDC dc_mem = CreateCompatibleDC(ps.hdc);
        SetStretchBltMode(dc_mem, HALFTONE);

        HDC all_dc[] = { ps.hdc, dc_mem, NULL };
        for (int i = 0; all_dc[i]; ++i) {
            SetMapMode(all_dc[i], MM_ISOTROPIC);
            SetWindowExtEx(all_dc[i], remoteImageWidth, remoteImageHeight, NULL);
            SetViewportExtEx(all_dc[i], rc.right, rc.bottom, NULL);
        }

        HBITMAP bmp_mem = CreateCompatibleBitmap(ps.hdc, rc.right, rc.bottom);
        HGDIOBJ bmp_old = SelectObject(dc_mem, bmp_mem);

        POINT logical_area = { rc.right, rc.bottom };
        DPtoLP(ps.hdc, &logical_area, 1);

        HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
        RECT logical_rect = {0, 0, logical_area.x, logical_area.y };
        FillRect(dc_mem, &logical_rect, brush);
        DeleteObject(brush);

        int max_unit = max(remoteImageWidth, remoteImageHeight);
        int x = (logical_area.x / 2) - (remoteImageWidth / 2);
        int y = (logical_area.y / 2) - (remoteImageHeight / 2);

        StretchDIBits
        (dc_mem, x, y, remoteImageWidth, remoteImageHeight,
         0, 0, remoteImageWidth, remoteImageHeight, 
         remoteImage, &m_bmi, DIB_RGB_COLORS, SRCCOPY);

        bool isALocalImage = ((localImage) && ((rc.right - rc.left) >= m_localWindowMinimum) && ((rc.bottom - rc.top) > m_localWindowMinimum));
        if ((isALocalImage))
        {
            Reshape(localImageWidth, localImageHeight);
            int thumb_width = (m_bmi.bmiHeader.biWidth / m_localWindowRatio);
            int thumb_height = (abs(m_bmi.bmiHeader.biHeight) / m_localWindowRatio);
            int thumb_x = (logical_area.x - (thumb_width + m_localWindowOffet));
            int thumb_y = (logical_area.y - (thumb_height + m_localWindowOffet));
            localImageWidth = (m_bmi.bmiHeader.biWidth);
            localImageHeight = (abs(m_bmi.bmiHeader.biHeight));

            StretchDIBits
            (dc_mem, thumb_x, thumb_y, thumb_width, thumb_height,
             0, 0, localImageWidth, localImageHeight,
             localImage, &m_bmi, DIB_RGB_COLORS, SRCCOPY);
        }

        BitBlt
        (ps.hdc, 0, 0, logical_area.x, logical_area.y,
         dc_mem, 0, 0, SRCCOPY);

        SelectObject(dc_mem, bmp_old);
        DeleteObject(bmp_mem);
        DeleteDC(dc_mem);

        EndPaint(m_hWnd, &ps);
    }
    virtual void Render
    (const void* remoteImage, int remoteImageWidth, int remoteImageHeight) {
        Render(remoteImage, remoteImageWidth, remoteImageHeight, 0,0,0);
    }

protected:
    inline void Reshape(int width, int height) {
        m_bmi.bmiHeader.biWidth = width;
        m_bmi.bmiHeader.biHeight = -height;
        m_bmi.bmiHeader.biSizeImage = width * height * 4;
    }
    inline int abs(int x) { return (((x) < (0)) ? (-(x)) : (x)); }
    inline int max(int a, int b) { return (((a) > (b)) ? (a) : (b)); }

protected:
    int m_localWindowMinimum;
    int m_localWindowOffet;
    int m_localWindowRatio;
    HWND m_hWnd;
    BITMAPINFO m_bmi;
};

} // namespace windows 
} // namespace client 
} // namespace peerconnection 
} // namespace webrtc 
} // namespace xos 

#endif // _XOS_WEBRTC_PEERCONNECTION_CLIENT_WINDOWS_GCRENDERER_HPP 
