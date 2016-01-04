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
///   File: Main.hpp
///
/// Author: $author$
///   Date: 6/8/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_APP_GUI_QT_HELLO_MAIN_HPP
#define _XOS_APP_GUI_QT_HELLO_MAIN_HPP

#include "xos/gui/qt/WindowMain.hpp"
#include "xos/gui/qt/ImageRenderer.hpp"
#include "app/gui/opengl/hello/Main.hpp"

#define XOS_APP_GUI_QT_HELLO_DEFAULT_BACKGROUND_RED   255
#define XOS_APP_GUI_QT_HELLO_DEFAULT_BACKGROUND_GREEN 0
#define XOS_APP_GUI_QT_HELLO_DEFAULT_BACKGROUND_BLUE  0

#define XOS_APP_GUI_QT_HELLO_MAIN_OPTIONS_CHARS \
        XOS_GUI_OPENGL_HELLO_OPTIONS_CHARS XOS_GUI_QT_MAIN_OPTIONS_CHARS

#define XOS_APP_GUI_QT_HELLO_MAIN_OPTIONS_OPTIONS \
            XOS_GUI_OPENGL_HELLO_OPTIONS_OPTIONS \
            XOS_GUI_QT_MAIN_OPTIONS_OPTIONS

namespace xos {
namespace app {
namespace gui {
namespace qt {
namespace hello {

typedef xos::gui::qt::ImageRendererImplement ImageRendererImplement;
typedef xos::gui::qt::ImageRenderer ImageRendererExtendExtend;
typedef opengl::hello::MainT
<ImageRendererImplement, ImageRendererExtendExtend> ImageRendererExtend;
///////////////////////////////////////////////////////////////////////
///  Class: ImageRenderer
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS ImageRenderer: public ImageRendererExtend {
public:
    typedef ImageRendererImplement Implements;
    typedef ImageRendererExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    ImageRenderer() {
    }
    virtual ~ImageRenderer() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual xos::gui::ImageRendererInterface& GlRenderer() const {
	    return (xos::gui::ImageRendererInterface&)(*this);
    }
};
typedef QWidget WidgetExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Widget
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Widget: public WidgetExtend {
public:
    typedef WidgetExtend Extends;
    typedef Widget Derives;

    typedef void (Derives::*M)();

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Widget
    (QWidget* parent, const QColor& bgColor)
    : Extends(parent), 
      m_sibling(0),
      m_bgColor(bgColor), 
      m_switchRender(0),
      m_render(0) {
    }
    virtual ~Widget() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Init(){
        initializeRenderer();
        return true;
    }
    virtual bool Finish(){
        return true;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void Invalidate() {
        int width = this->width();
        int height = this->height();
        update(0,0, width,height);
    }
    virtual void Resize() {
        int width = this->width();
        int height = this->height();
        resizeRenderer(width, height);
        update(0,0, width,height);
    }
    virtual void Show() {
        int width = this->width();
        int height = this->height();
        resizeRenderer(width, height);
        show();
    }

protected:
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
        if ((m_sibling)) {
            hide();
            m_sibling->show();
        }
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void RenderRaw() {
        m_renderer.RenderRaw();
    }
    virtual void Render() {
        m_renderer.Render();
    }
    virtual void RenderIn() {
        m_renderer.RenderIn();
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void PaintBackground() {
        int width = this->width();
        int height = this->height();
        QPainter qp(this);
        QRect rc(0,0, width, height);
        qp.fillRect(rc, m_bgColor);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void resizeEvent(QResizeEvent *event) {
        resizeRenderer(width(), height());
        Extends::resizeEvent(event);
    }
    virtual void paintEvent(QPaintEvent *event) {
        paintRenderer();
        Extends::paintEvent(event);
    }
    virtual void mouseReleaseEvent(QMouseEvent *event) {
        Qt::MouseButton button = Qt::NoButton;
        switch((button = event->button())) {
        case Qt::LeftButton:
            if ((m_switchRender))
                (this->*m_switchRender)();
            else
            SwitchRender();
            Invalidate();
            break;
        case Qt::RightButton:
        default:
            break;
        }
        Extends::mouseReleaseEvent(event);
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void initializeRenderer() {
        m_renderer.Init(this);
        m_renderer.LoadImageFile();
    }
    virtual void resizeRenderer(int width, int height) {
        m_renderer.Reshape(width, height);
    }
    virtual void paintRenderer() {
        if ((m_renderer.Image())) {
            if ((m_render))
                (this->*m_render)();
            else
            RenderRaw();
        } else {
            PaintBackground();
        }
    }

public:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual QWidget* SetSibling(QWidget* sibling) {
        return m_sibling = sibling;
    }
    virtual QWidget* Sibling() const {
        return m_sibling;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    QWidget* m_sibling;
    QColor m_bgColor;
    ImageRenderer m_renderer;
    M m_switchRender;
    M m_render;
};

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
typedef QGLWidget GLWidgetExtend;
///////////////////////////////////////////////////////////////////////
///  Class: GLWidget
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS GLWidget: public GLWidgetExtend {
public:
    typedef GLWidgetExtend Extends;
    typedef GLWidget Derives;

    typedef void (Derives::*M)();

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    GLWidget
    (QWidget* parent, const QColor& bgColor)
    : Extends(parent), 
      m_sibling(0),
      m_bgColor(bgColor), 
      m_switchRender(0),
      m_render(0) {
    }
    virtual ~GLWidget() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void Invalidate() {
        int width = this->width();
        int height = this->height();
        update(0,0, width,height);
    }
    virtual void Resize() {
        int width = this->width();
        int height = this->height();
        resizeGL(width, height);
        update(0,0, width,height);
    }
    virtual void Show() {
        int width = this->width();
        int height = this->height();
        resizeGL(width, height);
        show();
    }

protected:
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
        if ((m_sibling)) {
            hide();
            m_sibling->show();
        }
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void RenderRaw() {
        m_glRenderer.RenderRaw();
    }
    virtual void Render() {
        m_glRenderer.Render();
    }
    virtual void RenderIn() {
        m_glRenderer.RenderIn();
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void PaintBackground() {
        int width = this->width();
        int height = this->height();
        QPainter qp(this);
        QRect rc(0,0, width, height);
        qp.fillRect(rc, m_bgColor);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void mouseReleaseEvent(QMouseEvent *event) {
        Qt::MouseButton button = Qt::NoButton;
        switch((button = event->button())) {
        case Qt::LeftButton:
            if ((m_switchRender))
                (this->*m_switchRender)();
            else
            SwitchRender();
            Invalidate();
            break;
        case Qt::RightButton:
        default:
            break;
        }
        Extends::mouseReleaseEvent(event);
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void initializeGL() {
        m_glRenderer.LoadImageFile();
        m_glRenderer.Prepare();
    }
    virtual void resizeGL(int width, int height) {
        m_glRenderer.Reshape(width, height);
    }
    virtual void paintGL() {
        if ((m_glRenderer.Image())) {
            if ((m_render))
                (this->*m_render)();
            else
            RenderRaw();
        } else {
            PaintBackground();
        }
    }

public:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual QWidget* SetSibling(QWidget* sibling) {
        return m_sibling = sibling;
    }
    virtual QWidget* Sibling() const {
        return m_sibling;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    QWidget* m_sibling;
    QColor m_bgColor;
    GLImageRenderer m_glRenderer;
    M m_switchRender;
    M m_render;
};

typedef QWidget FormWidgetExtend;
///////////////////////////////////////////////////////////////////////
///  Class: FormWidget
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS FormWidget: public FormWidgetExtend {
Q_OBJECT
public:
    typedef FormWidgetExtend Extends;
    typedef FormWidget Derives;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    FormWidget(QWidget* parent)
    : Extends(parent),
      m_sibling(0),
      m_button(0) {
    }
    virtual ~FormWidget() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Init(){
        if ((m_button = new QPushButton("Hello", this))) {
            m_button->resize(width(), height());
            connect(m_button, SIGNAL(released()), this, SLOT(buttonReleased()));
        }
        return true;
    }
    virtual bool Finish(){
        return true;
    }
protected slots:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void buttonReleased() {
        if ((m_sibling)) {
            hide();
            m_sibling->show();
        }
    }
protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void resizeEvent(QResizeEvent *event) {
        if ((m_button))
            m_button->resize(width(), height());
        Extends::resizeEvent(event);
    }
    virtual void mouseReleaseEvent(QMouseEvent *event) {
        Qt::MouseButton button = Qt::NoButton;
        switch((button = event->button())) {
        case Qt::LeftButton:
            buttonReleased();
            break;
        case Qt::RightButton:
        default:
            break;
        }
        Extends::mouseReleaseEvent(event);
    }
public:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual QWidget* SetSibling(QWidget* sibling) {
        return m_sibling = sibling;
    }
    virtual QWidget* Sibling() const {
        return m_sibling;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    QWidget* m_sibling;
    QPushButton *m_button;
};

typedef InterfaceBase MainWindowImplement;
typedef QMainWindow MainWindowExtend;
///////////////////////////////////////////////////////////////////////
///  Class: MainWindow
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS MainWindow
: virtual public MainWindowImplement, public MainWindowExtend {
public:
    typedef MainWindowImplement Implements;
    typedef MainWindowExtend Extends;
    typedef MainWindow Derives;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    MainWindow()
    : m_formWidget(0),
      m_glWidget(0),
      m_widget(0),
      m_bgColor
      (XOS_APP_GUI_QT_HELLO_DEFAULT_BACKGROUND_RED,
       XOS_APP_GUI_QT_HELLO_DEFAULT_BACKGROUND_GREEN,
       XOS_APP_GUI_QT_HELLO_DEFAULT_BACKGROUND_BLUE) {
    }
    virtual ~MainWindow() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Init(bool noOpenGL = false){
        if ((m_formWidget = new FormWidget(this))) {
            if ((m_formWidget->Init())) {
                if ((noOpenGL)) {
                    if ((m_widget = new Widget(this, m_bgColor))) {
                        if ((m_widget->Init())) {
                            m_widget->hide();
                            m_widget->SetSibling(m_formWidget);
                            m_formWidget->SetSibling(m_widget);
                            m_formWidget->show();
                            return true;
                        }
                        delete m_formWidget;
                        m_formWidget = 0;
                    }
                }
                if ((m_glWidget = new GLWidget(this, m_bgColor))) {
                    m_glWidget->hide();
                    m_glWidget->SetSibling(m_formWidget);
                    m_formWidget->SetSibling(m_glWidget);
                    m_formWidget->show();
                    return true;
                }
                delete m_formWidget;
                m_formWidget = 0;
            }
        }
        return false;
    }
    virtual bool Finish(){
        bool success = false;
        if ((m_widget)) {
            if (m_widget == (centralWidget()))
                setCentralWidget(0);
            else
            delete m_widget;
            m_widget = 0;
            success = true;
        }
        if ((m_glWidget)) {
            if (m_glWidget == (centralWidget()))
                setCentralWidget(0);
            else
            delete m_glWidget;
            m_glWidget = 0;
            success = true;
        }
        if ((m_formWidget)) {
            if (m_formWidget == (centralWidget()))
                setCentralWidget(0);
            else
            delete m_glWidget;
            m_glWidget = 0;
            success = true;
        }
        return success;
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void resizeEvent(QResizeEvent *event) {
        if ((m_formWidget))
            m_formWidget->resize(width(), height());
        if ((m_glWidget))
            m_glWidget->resize(width(), height());
        if ((m_widget))
            m_widget->resize(width(), height());
        Extends::resizeEvent(event);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    FormWidget* m_formWidget;
    GLWidget* m_glWidget;
    Widget* m_widget;
    QColor m_bgColor;
};

typedef xos::gui::qt::WindowMainImplement MainImplement;
typedef xos::gui::qt::WindowMain MainExtend;
///////////////////////////////////////////////////////////////////////
///  Class: Main
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Main
: virtual public MainImplement, public MainExtend {
public:
    typedef MainImplement Implements;
    typedef MainExtend Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Main(): m_mainWindow(0), m_noOpenGL(false) {
    }
    virtual ~Main(){
        if ((m_mainWindow))
            delete m_mainWindow;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual QMainWindow* CreateMainWindow
    (QApplication& qApplication,
     int argc, char** argv, char** env)
    {
        if ((m_mainWindow = new MainWindow())) {
            if (!(m_mainWindow->Init(m_noOpenGL))) {
                delete m_mainWindow;
                m_mainWindow = 0;
            }
        }
        return m_mainWindow;
    }
    virtual bool DestroyMainWindow
    (QMainWindow* mainWindow, QApplication& qApplication,
     int argc, char** argv, char** env)
    {
        bool isSuccess = false;
        if ((mainWindow) && (mainWindow == m_mainWindow)) {
            m_mainWindow->Finish();
            delete m_mainWindow;
            m_mainWindow = 0;
            isSuccess = true;
        }
        return isSuccess;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int OnOption
    (int optval, const char* optarg,
     const char* optname, int optind,
     int argc, char**argv, char**env)
    {
        int err = 0;
        switch(optval)
        {
        case XOS_GUI_OPENGL_HELLO_OPENGL_OPTVAL_C:
            if ((optarg)) {
                String optArg(optarg);
                if (!(optArg.compare("off"))) 
                    m_noOpenGL = true;
                else
                if (!(optArg.compare("on"))) 
                    m_noOpenGL = false;
            }
            break;
        default:
            err = Extends::OnOption
            (optval, optarg, optname, optind, argc, argv, env);
        }
        return err;
    }
    virtual const char* OptionUsage
    (const char*& optarg, const struct option* longopt)
    {
        const char* chars = "";
        switch(longopt->val)
        {
        case XOS_GUI_OPENGL_HELLO_OPENGL_OPTVAL_C:
            optarg = XOS_GUI_OPENGL_HELLO_OPENGL_OPTARG;
            chars = XOS_GUI_OPENGL_HELLO_OPENGL_OPTUSE;
            break;
        default:
            chars = Extends::OptionUsage(optarg, longopt);
        }
        return chars;
    }
    virtual const char* Options
    (const struct option*& longopts)
    {
        int err = 0;
        static const char* chars = XOS_APP_GUI_QT_HELLO_MAIN_OPTIONS_CHARS;
        static struct option optstruct[]= {
            XOS_APP_GUI_QT_HELLO_MAIN_OPTIONS_OPTIONS
            {0, 0, 0, 0}};
        longopts = optstruct;
        return chars;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    MainWindow* m_mainWindow;
    bool m_noOpenGL;
};

} // namespace hello 
} // namespace qt 
} // namespace gui 
} // namespace app 
} // namespace xos 

#endif // _XOS_APP_GUI_QT_HELLO_MAIN_HPP 
