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
///   File: PeerView.hpp
///
/// Author: $author$
///   Date: 8/1/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_APP_WEBRTC_CLIENT_GUI_QT_PEERFORM_HPP
#define _XOS_APP_WEBRTC_CLIENT_GUI_QT_PEERFORM_HPP

#include "xos/gui/qt/Gui.hpp"
#include "app/webrtc/client/PluginInterface.hpp"

namespace xos {
namespace app {
namespace webrtc {
namespace client {
namespace gui {
namespace qt {

typedef QWidget PeerViewExtend;
///////////////////////////////////////////////////////////////////////
///  Class: PeerView
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS PeerView: public PeerViewExtend {
Q_OBJECT
public:
    typedef PeerViewExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: PeerView
    ///////////////////////////////////////////////////////////////////////
    PeerView(PluginInterface& plugin, QWidget* parent)
    : Extends(parent), 
      m_plugin(plugin),
      m_canvas(0),
      m_label(0),
      m_listBox(0), 
      m_disconnectButton(0) {
    }
    virtual ~PeerView() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Init() {
        if ((m_canvas = new QWidget(this))) {
            m_canvas->setAutoFillBackground(true);
            m_canvas->setAttribute(Qt::WA_NoMousePropagation);

            if ((m_label = new QLabel("Peers", m_canvas))) {
                m_label->setAlignment(Qt::AlignCenter | Qt::AlignBottom);

                if ((m_listBox = new QListWidget(m_canvas))) {
                    connect(m_listBox, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(itemDoubleClicked(QListWidgetItem*)));
                    m_listBox->addItem(QString("Hello"));

                    if ((m_disconnectButton = new QPushButton("Disconnect", m_canvas))) {
                        connect(m_disconnectButton, SIGNAL(released()), this, SLOT(disconnectButtonReleased()));
                        ResizeListBox();
                        return true;

                        delete m_disconnectButton;
                        m_disconnectButton = 0;
                    }

                    delete m_listBox;
                    m_listBox = 0;
                }
                delete m_label;
                m_label = 0;
            }
            delete m_canvas;
            m_canvas = 0;
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
        Clear();
        return true;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool AddPeer(const std::string& peerName) {
        if ((m_listBox) && (0 < (peerName.length()))) {
            m_listBox->addItem(peerName.c_str());
            return true;
        }
        return false;
    }
    virtual bool RemovePeer(const std::string& peerName) {
        if ((m_listBox) && (0 < (peerName.length()))) {
            QList<QListWidgetItem*> items = m_listBox->findItems(peerName.c_str(), Qt::MatchExactly);
            QList<QListWidgetItem*>::iterator item;
            for (item = items.begin(); item != items.end(); ++item) {
                m_listBox->removeItemWidget(*item);
                return true;
            }
        }
        return false;
    }
    virtual bool Clear() {
        if ((m_listBox)) {
            m_listBox->clear();
            return true;
        }
        return false;
    }

protected slots:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void disconnectButtonReleased() {
        m_plugin.DisconnectFromServer();
    }
    void itemDoubleClicked(QListWidgetItem* item) {
        QString itemString = item->text();
        if (0 < (itemString.length())) {
            QByteArray itemArray = itemString.toUtf8();
            if (0 < (itemArray.length())) {
                std::string peerName(itemArray.data());
                m_plugin.ConnectToPeer(peerName);
            }
        }
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void resizeEvent(QResizeEvent *event) {
        ResizeListBox();
    }
    virtual void ResizeListBox() {
        if ((m_canvas))
            m_canvas->resize(width(), height());
        if ((m_listBox)) {
            if ((m_label)) {
                int labelWidth = m_label->width();
                int labelHeight = m_label->height();
                m_label->move((labelWidth < width())?((width()-labelWidth)/2):(0), 0);
                m_listBox->move(0, labelHeight);
                if ((m_disconnectButton)) {
                    int buttonWidth = m_disconnectButton->width();
                    int buttonHeight = m_disconnectButton->height();
                    m_listBox->resize
                    (width(), ((labelHeight+buttonHeight) < height())?(height()-(labelHeight+buttonHeight)):(0));
                    m_disconnectButton->move
                    ((buttonWidth < width())?((width()-buttonWidth)/2):(0), labelHeight+m_listBox->height());
                } else {
                    m_listBox->resize(width(), (labelHeight < height())?(height()-labelHeight):(0));
                }
            } else {
                m_listBox->move(0,0);
                m_listBox->resize(width(), height());
            }
        }
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    PluginInterface& m_plugin;
    QWidget* m_canvas;
    QLabel* m_label;
    QListWidget* m_listBox;
    QPushButton* m_disconnectButton;
};

} // namespace qt 
} // namespace gui 
} // namespace client 
} // namespace webrtc 
} // namespace app 
} // namespace xos 

#endif // _XOS_APP_WEBRTC_CLIENT_GUI_QT_PEERFORM_HPP 
