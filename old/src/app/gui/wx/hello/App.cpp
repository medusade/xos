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
///   File: App.cpp
///
/// Author: $author$
///   Date: 7/6/2013
///////////////////////////////////////////////////////////////////////
#include "app/gui/wx/hello/App.hpp"
#include "xos/gui/wx/Main.hpp"
#include "xos/os/Main_main.cpp"

namespace xos {
namespace wx {
namespace hello {

///////////////////////////////////////////////////////////////////////
///  Class: GLCanvas
///////////////////////////////////////////////////////////////////////
BEGIN_EVENT_TABLE(GLCanvas, GLCanvasExtend)
    EVT_SIZE    (GLCanvas::OnSizeEvent)
    EVT_PAINT    (GLCanvas::OnPaintEvent)
    EVT_LEFT_UP    (GLCanvas::OnLButtonUpEvent)
END_EVENT_TABLE()

///////////////////////////////////////////////////////////////////////
///  Class: Panel
///////////////////////////////////////////////////////////////////////
BEGIN_EVENT_TABLE(Panel, PanelExtend)
    EVT_SIZE    (Panel::OnSizeEvent)
    EVT_BUTTON    (Panel::wxID_BUTTON, Panel::OnCommandEvent)
    EVT_LEFT_UP    (Panel::OnLButtonUpEvent)
END_EVENT_TABLE()

///////////////////////////////////////////////////////////////////////
///  Class: Frame
///////////////////////////////////////////////////////////////////////
BEGIN_EVENT_TABLE(Frame, FrameExtend)
    EVT_SIZE    (Frame::OnSizeEvent)
    EVT_LEFT_UP    (Frame::OnLButtonUpEvent)
END_EVENT_TABLE()

///////////////////////////////////////////////////////////////////////
///  Class: App
///////////////////////////////////////////////////////////////////////
wxIMPLEMENT_APP_NO_MAIN(App);

} // namespace hello 

///////////////////////////////////////////////////////////////////////
///  Class: Main
///////////////////////////////////////////////////////////////////////
Main g_main;

} // namespace wx 
} // namespace xos 
