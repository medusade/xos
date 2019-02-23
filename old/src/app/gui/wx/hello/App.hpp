///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2013 $organization$
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
///   File: App.hpp
///
/// Author: $author$
///   Date: 7/6/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_WX_HELLO_APP_HPP
#define _XOS_GUI_WX_HELLO_APP_HPP

#include "xos/gui/wx/Base.hpp"
#include "app/gui/opengl/hello/Main.hpp"
#include <wx/app.h>
#include <wx/frame.h>
#include <wx/panel.h>
#include <wx/button.h>
#include <wx/glcanvas.h>

namespace xos {
namespace wx {
namespace hello {

typedef xos::gui::opengl::ImageRendererImplement GLImageRendererImplement;
typedef xos::gui::opengl::ImageRenderer GLImageRendererExtendExtend;
typedef opengl::hello::MainT
<GLImageRendererImplement, GLImageRendererExtendExtend> GLImageRendererExtend;
///////////////////////////////////////////////////////////////////////
///  Class: GLImageRenderer
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS GLImageRenderer: public GLImageRendererExtend {
public:
    typedef GLImageRendererImplement Implements;
    typedef GLImageRendererExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: GLImageRenderer
    ///////////////////////////////////////////////////////////////////////
    GLImageRenderer() {
    }
    virtual ~GLImageRenderer() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual xos::gui::ImageRendererInterface& GlRenderer() const {
        return (xos::gui::ImageRendererInterface&)(*this);
    }
};

typedef InterfaceBase GLCanvasImplement;
typedef wxGLCanvas GLCanvasExtend;
///////////////////////////////////////////////////////////////////////
///  Class: GLCanvas
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS GLCanvas
: virtual public GLCanvasImplement, public GLCanvasExtend {
public:
    typedef GLCanvasImplement Implements;
    typedef GLCanvasExtend Extends;
    typedef GLCanvas Derives;
    typedef void (Derives::*M)();
    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: GLCanvas
    ///////////////////////////////////////////////////////////////////////
    GLCanvas
    (wxWindow* parent, 
     const wxPoint& pos=wxDefaultPosition, 
     const wxSize& size=wxDefaultSize)
    : Extends(parent, wxID_ANY, pos, size),
      m_sibling(0),
      m_isPrepared(false),
      m_switchRender(0),
      m_render(0) {
    }
    virtual ~GLCanvas() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Init() {
        m_glRenderer.LoadImageFile();
        return true;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void Render() {
        m_glRenderer.Render();
    }
    virtual void RenderIn() {
        m_glRenderer.RenderIn();
    }
    virtual void RenderRaw() {
        m_glRenderer.RenderRaw();
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void SwitchRender() {
        m_switchRender = &Derives::SwitchRenderIn;
        m_render = &Derives::Render;
    }
    virtual void SwitchRenderIn() {
        m_switchRender = &Derives::SwitchRenderRaw;
        m_render = &Derives::RenderIn;
    }
    virtual void SwitchRenderRaw() {
        m_switchRender = &Derives::SwitchRender;
        m_render = &Derives::RenderRaw;
        Hide();
        if ((m_sibling))
            m_sibling->Show();
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void OnLButtonUpEvent(wxMouseEvent& event) {
        if ((m_switchRender))
            (this->*m_switchRender)();
        else
        SwitchRender();
        Refresh();
    }
    virtual void OnSizeEvent(wxSizeEvent& event) {
        if ((IsPrepared())) {
            wxSize size(event.GetSize());
            m_glRenderer.Reshape(size.GetWidth(), size.GetHeight());
            Refresh();
        }
    }
    virtual void OnPaintEvent(wxPaintEvent& event) {
        if ((IsPrepared())) {
            if ((m_render))
                (this->*m_render)();
            else
            RenderRaw();
            SwapBuffers();
        }
    }
    virtual bool IsPrepared() {
        if ((IsShown()))
        if (!(m_isPrepared)) {
            wxSize size(GetSize());
            SetCurrent();
            m_glRenderer.Prepare();
            m_glRenderer.Reshape(size.GetWidth(), size.GetHeight());
            m_isPrepared = true;
        }
        return m_isPrepared;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual wxWindow* SetSibling( wxWindow* sibling) {
        return m_sibling = sibling;
    }
    virtual wxWindow* Sibling() {
        return m_sibling;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    wxWindow* m_sibling;
    bool m_isPrepared;
    M m_switchRender;
    M m_render;
    GLImageRenderer m_glRenderer;
    DECLARE_EVENT_TABLE()
};

typedef InterfaceBase PanelImplement;
typedef wxPanel PanelExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Panel
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Panel
: virtual public PanelImplement, public PanelExtend {
public:
    typedef PanelImplement Implements;
    typedef PanelExtend Extends;
    enum { wxID_BUTTON = wxID_HIGHEST + 1 };
    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: Panel
    ///////////////////////////////////////////////////////////////////////
    Panel
    (wxWindow* parent, 
     const wxPoint& pos=wxDefaultPosition, 
     const wxSize& size=wxDefaultSize)
    : Extends(parent, wxID_ANY, pos, size),
      m_sibling(0), m_button(0) {
    }
    virtual ~Panel() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Init() {
        wxSize size(GetClientSize());
        if ((m_button = new wxButton
            (this, wxID_BUTTON, _T("Hello"), wxPoint(0,0), size)))
            m_button->Show();
        return true;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void OnCommandEvent(wxCommandEvent& event) {
        Hide();
        if ((m_sibling))
            m_sibling->Show();
    }
    virtual void OnLButtonUpEvent(wxMouseEvent& event) {
        Hide();
        if ((m_sibling))
            m_sibling->Show();
    }
    virtual void OnSizeEvent(wxSizeEvent& event) {
        if ((m_button)) {
            wxSize size(GetClientSize());
            m_button->SetSize(size.GetWidth(),size.GetHeight());
        }
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual wxWindow* SetSibling(wxWindow* sibling) {
        return m_sibling = sibling;
    }
    virtual wxWindow* Sibling() {
        return m_sibling;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    wxWindow* m_sibling;
    wxButton* m_button;
    DECLARE_EVENT_TABLE()
};

typedef InterfaceBase FrameImplement;
typedef wxFrame FrameExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Frame
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Frame
: virtual public FrameImplement, public FrameExtend {
public:
    typedef FrameImplement Implements;
    typedef FrameExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: Frame
    ///////////////////////////////////////////////////////////////////////
    Frame
    (const wxString& title, const wxPoint& pos, const wxSize& size)
    : Extends(0, wxID_ANY, title, pos, size), 
      m_panel(0), m_glCanvas(0) {
    }
    virtual ~Frame() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Init() {
        if ((m_panel = new Panel(this, wxPoint(0,0), GetSize()))) {
            if ((m_panel->Init())) {
                m_panel->Show();
                if ((m_glCanvas = new GLCanvas(this, wxPoint(0,0), GetSize()))) {
                    if ((m_glCanvas->Init())) {
                        m_glCanvas->Hide();
                        m_glCanvas->SetSibling(m_panel);
                        m_panel->SetSibling(m_glCanvas);
                        return true;
                    }
                }
            }
        }
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void OnLButtonUpEvent(wxMouseEvent& event) {
        if ((m_glCanvas)) {
            m_glCanvas->Show();
        }
    }
    virtual void OnSizeEvent(wxSizeEvent& event) {
        wxWindow* window;
        if ((window = m_panel)) {
            wxSize size(GetClientSize());
            do {
                window->SetSize(size.GetWidth(),size.GetHeight());
            } while (window = ((window != m_panel)?(0):(m_glCanvas)));
        }
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    Panel* m_panel;
    GLCanvas* m_glCanvas;
    DECLARE_EVENT_TABLE()
};

typedef InterfaceBase AppImplement;
typedef wxApp AppExtend;
///////////////////////////////////////////////////////////////////////
///  Class: App
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS App
: virtual public AppImplement, public AppExtend {
public:
    typedef AppImplement Implements;
    typedef AppExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: App
    ///////////////////////////////////////////////////////////////////////
    App(): m_name("wxXosHello"), m_width(200), m_height(100) {
    }
    virtual ~App() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool OnInit() {
        Frame* frame = 0;
        if ((frame = new Frame
            (m_name.Chars(), wxDefaultPosition, wxSize(m_width,m_height)))) {
            if ((frame->Init())) {
                frame->Show();
                return true;
            }
        }
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    String m_name;
    int m_width, m_height;
};

} // namespace hello 
} // namespace wx 
} // namespace xos 

#endif // _XOS_GUI_WX_HELLO_APP_HPP 
