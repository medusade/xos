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
///   File: ServerView.hpp
///
/// Author: $author$
///   Date: 8/1/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_APP_WEBRTC_CLIENT_GUI_QT_SERVERFORM_HPP
#define _XOS_APP_WEBRTC_CLIENT_GUI_QT_SERVERFORM_HPP

#include "xos/gui/qt/Gui.hpp"
#include "app/webrtc/client/PluginInterface.hpp"
#include "xos/base/String.hpp"

#define XOS_APP_WEBRTC_CLIENT_DEFAULT_HOST "localhost"
#define XOS_APP_WEBRTC_CLIENT_DEFAULT_PORT 8888

#define XOS_APP_WEBRTC_CLIENT_GUI_QT_SERVERFORM_WIDTH_RATIO    4
#define XOS_APP_WEBRTC_CLIENT_GUI_QT_SERVERFORM_WIDTH_RATIO_TO 3
#define XOS_APP_WEBRTC_CLIENT_GUI_QT_SERVERFORM_HEIGHT_RATIO    10
#define XOS_APP_WEBRTC_CLIENT_GUI_QT_SERVERFORM_HEIGHT_RATIO_TO 1

namespace xos {
namespace app {
namespace webrtc {
namespace client {
namespace gui {
namespace qt {

typedef QWidget ServerViewExtend;
///////////////////////////////////////////////////////////////////////
///  Class: ServerView
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS ServerView: public ServerViewExtend {
Q_OBJECT
public:
    typedef ServerViewExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: ServerView
    ///////////////////////////////////////////////////////////////////////
    ServerView(PluginInterface& plugin, QWidget* parent)
    : Extends(parent), 
      m_plugin(plugin),
      m_form(0),
      m_canvas(0),
      m_connectButton(0), 
      m_portEdit(0),
      m_portLabel(0), 
      m_hostEdit(0),
      m_hostLabel(0),
      m_resizeParent(false),
      m_defaultHost(XOS_APP_WEBRTC_CLIENT_DEFAULT_HOST),
      m_defaultPort(XOS_APP_WEBRTC_CLIENT_DEFAULT_PORT) {
    }
    virtual ~ServerView() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Init() {
        if ((m_canvas = new QWidget(this))) {
            m_canvas->setAutoFillBackground(true);
            m_canvas->setAttribute(Qt::WA_NoMousePropagation);
        if ((m_form = new QWidget(m_canvas))) {

            if ((m_connectButton = new QPushButton("Connect", m_form))) {

                connect(m_connectButton, SIGNAL(released()), this, SLOT(connectButtonReleased()));

                if ((m_portEdit = new QLineEdit(m_form))) {
                    xos::String portString(m_defaultPort);
                    QString portQString = portString.c_str();

                    m_portEdit->setText(portQString);
                    m_portEdit->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

                    if ((m_portLabel = new QLabel(":", m_form))) {

                        m_portLabel->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);

                        if ((m_hostEdit = new QLineEdit(m_form))) {

                            m_hostEdit->setText(m_defaultHost);
                            m_hostEdit->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

                            if ((m_hostLabel = new QLabel("Server", m_form))) {
                                m_hostLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
                                ResizeForm();
                                hide();
                                m_resizeParent = true;
                                return true;
                            }
                            delete m_hostEdit;
                            m_hostEdit = 0;
                        }
                        delete m_portLabel;
                        m_portLabel = 0;
                    }
                    delete m_portEdit;
                    m_portEdit = 0;
                }
                delete m_connectButton;
                m_connectButton = 0;
            }
            delete m_form;
            m_form = 0;
        }
            delete m_form;
            m_form = 0;
        }
        return false;
    }
    virtual bool Finish() {
        return true;
    }
    virtual bool Show(int width, int height) {
        show();
        resize(width, height);
        update();
        return true;
    }

protected slots:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void connectButtonReleased() {
        if ((m_hostEdit)) {
            QString hostQString = m_hostEdit->text();
            QByteArray hostBytes = hostQString.toUtf8();

            if (0 < (hostBytes.length())) {
                xos::String host(hostBytes.data(), hostBytes.length());

                if ((m_portEdit)) {
                    QString portQString = m_portEdit->text();
                    QByteArray portBytes = portQString.toUtf8();

                    if (0 < (portBytes.length())) {
                        xos::String portString(portBytes.data(), portBytes.length());
                        int port = portString.toInt();

                        if (0 < (port)) {
                            m_plugin.ConnectToServer(host, port);
                            return;
                        }
                    }
                }
                m_plugin.ConnectToServer(host);
            }
        }
    }
protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void showEvent(QShowEvent *event) {
        if ((m_form)) {
            ResizeForm();
            if ((m_resizeParent)) {
                QWidget* widget = parentWidget();
                m_resizeParent = false;
                if ((widget))
                    widget->resize
                    ((m_form->width()*m_widthRatio)/m_widthRatioTo, 
                     (m_form->height()*m_heightRatio)/m_heightRatioTo);
            }
        }
    }
    virtual void resizeEvent(QResizeEvent *event) {
        if ((m_canvas))
            m_canvas->resize(width(), height());
        if ((m_form)) {
            ResizeForm();
        }
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void ResizeForm() {
        int formX = 0;
        int formY = 0;
        m_hostLabel->resize(TextWidth(m_hostLabel, m_hostLabel->text().length()), m_connectButton->height());
        m_hostEdit->resize(m_connectButton->width()*2, m_connectButton->height());
        m_portLabel->resize(TextWidth(m_hostLabel, m_hostLabel->text().length()), m_connectButton->height());
        m_portEdit->resize(m_connectButton->width(), m_connectButton->height());
        m_hostLabel->move(0, 0);
        m_hostEdit->move(m_hostLabel->width(), 0);
        m_portLabel->move(m_hostEdit->x()+m_hostEdit->width(), 0);
        m_portEdit->move(m_portLabel->x()+m_portLabel->width(), 0);
        m_connectButton->move(m_portEdit->x()+m_portEdit->width(), 0);
        m_form->resize
        (m_hostLabel->width()+m_hostEdit->width()+
         m_portLabel->width()+m_portEdit->width()+
         m_connectButton->width(), m_connectButton->height());

        if ((m_form->width() < width()))
            formX = (width()-m_form->width())/2;

        if ((m_form->height() < height()))
            formY = (height()-m_form->height())/2;

        m_form->move(formX, formY);
    }
    virtual int TextWidth(QWidget* widget, int textLength) const {
        if ((widget) && (0 < textLength)) {
            QFontMetrics font = widget->fontMetrics();
            int fontWidth = font.width(QChar('X'));
            return fontWidth*textLength;
        }
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    static const int m_widthRatio = XOS_APP_WEBRTC_CLIENT_GUI_QT_SERVERFORM_WIDTH_RATIO;
    static const int m_widthRatioTo = XOS_APP_WEBRTC_CLIENT_GUI_QT_SERVERFORM_WIDTH_RATIO_TO;
    static const int m_heightRatio = XOS_APP_WEBRTC_CLIENT_GUI_QT_SERVERFORM_HEIGHT_RATIO;
    static const int m_heightRatioTo = XOS_APP_WEBRTC_CLIENT_GUI_QT_SERVERFORM_HEIGHT_RATIO_TO;

    PluginInterface& m_plugin;
    QWidget* m_form;
    QWidget* m_canvas;
    QPushButton* m_connectButton;
    QLineEdit* m_portEdit;
    QLabel* m_portLabel;
    QLineEdit* m_hostEdit;
    QLabel* m_hostLabel;
    bool m_resizeParent;
    const char* m_defaultHost;
    int m_defaultPort;
};

} // namespace qt 
} // namespace gui 
} // namespace client 
} // namespace webrtc 
} // namespace app 
} // namespace xos 

#endif // _XOS_APP_WEBRTC_CLIENT_GUI_QT_SERVERFORM_HPP 
