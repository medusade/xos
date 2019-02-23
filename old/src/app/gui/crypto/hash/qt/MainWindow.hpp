///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2014 $organization$
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
///   File: MainWindow.hpp
///
/// Author: $author$
///   Date: 1/26/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_CRYPTO_HASH_QT_MAINWINDOW_HPP
#define _XOS_GUI_CRYPTO_HASH_QT_MAINWINDOW_HPP

#include "app/gui/crypto/hash/MainWindow.hpp"
#include "xos/gui/qt/WindowMain.hpp"

#if (!defined(WINDOWS) || !(QT_VERSION < 0x040700))
#define XOS_GUI_CRYPTO_HASH_QT_MAINWINDOW_ACCEPT_DROPS
#endif // (!defined(WINDOWS) || !(QT_VERSION < 0x040700))

namespace xos {
namespace gui {
namespace crypto {
namespace hash {
namespace qt {

typedef hash::MainWindow<QMainWindow> MainWindowExtend;
///////////////////////////////////////////////////////////////////////
///  Class: MainWindow
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS MainWindow: public MainWindowExtend {
Q_OBJECT
public:
    typedef MainWindowExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    MainWindow(xos::crypto::hash::Interface& hash, const char* hashName)
    : Extends(hash, hashName),
      m_okButton(0),
      m_cancelButton(0),
      m_hashLabel(0),
      m_fileLabel(0),
      m_textLabel(0),
      m_hashEdit(0),
      m_fileEdit(0),
      m_textEdit(0),
      m_progressBar(0) {
    }
    virtual ~MainWindow() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool GetHashText(String& hashText) {
        if ((m_textEdit)) {
            QString textString = m_textEdit->toPlainText();
            return GetEditText(hashText, textString);
        }
        return false;
    }
    virtual bool GetHashFileName(String& fileName) {
        if ((m_fileEdit)) {
            QString textString = m_fileEdit->text();
            return GetEditText(fileName, textString);
        }
        return false;
    }
    virtual bool PostUpdateFileHashEvent() {
        QApplication::postEvent(this, new UpdateFileHashQEvent());
        return true;
    }
    virtual bool ShowHash(const String& hashX) {
        if ((m_hashEdit)) {
            const char* chars;
            if ((chars = hashX.Chars())) {
                QString hashString(chars);
                m_hashEdit->setText(hashString);
                return true;
            }
        }
        return false;
    }
    virtual bool ClearHash() {
        if ((m_hashEdit)) {
            m_hashEdit->clear();
            return true;
        }
        return false;
    }
    virtual bool ShowProgress(size_t maximum, size_t amount) {
        if ((m_progressBar)) {
            m_progressBar->setMaximum(maximum);
            if ((UpdateProgress(amount))) {
                m_progressBar->show();
                return true;
            }
        }
        return false;
    }
    virtual bool UpdateProgress(size_t amount) {
        if ((m_progressBar)) {
            m_progressBar->setValue(amount);
            return true;
        }
        return false;
    }
    virtual bool HideProgress() {
        if ((m_progressBar)) {
            m_progressBar->hide();
            return true;
        }
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool GetEditText(String& text, QString& textString) {
        if (0 < (textString.length())) {
            QByteArray textArray = textString.toUtf8();
            const char* chars;
            size_t length;
            if ((chars = textArray.data()) && (length = textArray.length())) {
                text.Assign(chars, length);
                return true;
            }
        }
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Init() {
        setAcceptDrops(false);

        if ((m_cancelButton = new QPushButton("Cancel", this))) {
            connect(m_cancelButton, SIGNAL(released()), this, SLOT(cancelButtonReleased()));

            if ((m_okButton = new QPushButton("Ok", this))) {
                connect(m_okButton, SIGNAL(released()), this, SLOT(okButtonReleased()));

                if ((m_hashLabel = new QLabel((m_hashName)?(m_hashName):("Hash"), this))) {
                    m_hashLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
                    m_hashLabel->resize(m_cancelButton->width(), m_cancelButton->height());
                    m_hashLabel->move(m_cancelButton->x(), m_cancelButton->y());
                    m_cancelButton->move(m_cancelButton->x()+m_hashLabel->width(), m_cancelButton->y());

                    if ((m_fileLabel = new QLabel("File", this))) {
                        m_fileLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
                        m_fileLabel->resize(m_hashLabel->width(), m_hashLabel->height());
                        m_fileLabel->move(m_hashLabel->x(), m_hashLabel->y()+m_hashLabel->height());

                        if ((m_textLabel = new QLabel("Text", this))) {
                            m_textLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
                            m_textLabel->resize(m_hashLabel->width(), m_hashLabel->height());
                            m_textLabel->move(m_fileLabel->x(), m_fileLabel->y()+m_fileLabel->height());

                            if ((m_hashEdit = new QLineEdit(this))) {
                                QFontMetrics fontMetrics = m_hashEdit->fontMetrics();
                                int hashWidth = HashWidth(fontMetrics);
                                if (hashWidth < m_cancelButton->width())
                                    hashWidth = m_cancelButton->width();
                                m_hashEdit->setReadOnly(true);
                                m_hashEdit->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
                                m_hashEdit->resize(hashWidth, m_cancelButton->height());
                                m_hashEdit->move(m_cancelButton->x(), m_cancelButton->y());
                                m_cancelButton->move(m_cancelButton->x()+m_hashEdit->width(), m_cancelButton->y());

                                if ((m_fileEdit = new QLineEdit(this))) {
                                    m_fileEdit->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
                                    m_fileEdit->resize(m_hashEdit->width(), m_hashEdit->height());
                                    m_fileEdit->move(m_hashEdit->x(), m_hashEdit->y()+m_hashEdit->height());

                                    if ((m_textEdit = new QTextEdit(this))) {
                                        m_textEdit->setLineWrapMode(QTextEdit::NoWrap);
                                        m_textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
                                        m_textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
                                        m_textEdit->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
                                        m_textEdit->resize(m_hashEdit->width(), m_hashEdit->height());
                                        m_textEdit->move(m_fileEdit->x(), m_fileEdit->y()+m_fileEdit->height());

                                        if ((m_progressBar = new QProgressBar(this))) {
                                            m_progressBar->setMinimum(0);
                                            m_progressBar->setMaximum(100);
                                            m_progressBar->setValue(50);
                                            m_progressBar->setTextVisible(false);
                                            m_progressBar->resize(m_textEdit->width(), m_progressBar->height());
                                            m_progressBar->move(m_textEdit->x(), m_textEdit->y()+m_textEdit->height());

                                            m_okButton->resize(m_cancelButton->width(), m_cancelButton->height());
                                            m_okButton->move(m_cancelButton->x(), m_cancelButton->y());
                                            m_cancelButton->move(m_cancelButton->x(), m_cancelButton->y()+m_okButton->height());

                                            resize
                                            (m_hashLabel->width()+m_hashEdit->width()+m_cancelButton->width(),
                                             m_hashLabel->height()+m_fileLabel->height()+m_textLabel->height()+m_progressBar->height());

                                            m_progressBar->hide();

#if defined(XOS_GUI_CRYPTO_HASH_QT_MAINWINDOW_ACCEPT_DROPS)
                                            setAcceptDrops(true);
#endif // defined(XOS_GUI_CRYPTO_HASH_QT_MAINWINDOW_ACCEPT_DROPS)
                                            return true;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        return false;
    }
    virtual bool Finish(){
        bool success = true;
        HideProgress();
        CloseFile();
        return success;
    }
protected slots:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void okButtonReleased() {
        if (!(HashText()))
        if (!(HashFile()))
            HashBlank();
    }
    virtual void cancelButtonReleased() {
        if (m_file) {
            HideProgress();
            CloseFile();
        } else {
            QApplication::quit();
        }
    }
protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
#if defined(XOS_GUI_CRYPTO_HASH_QT_MAINWINDOW_ACCEPT_DROPS)
    virtual void dragEnterEvent(QDragEnterEvent* event) {
        event->acceptProposedAction();
    }
    virtual void dragMoveEvent(QDragMoveEvent* event) {
        event->acceptProposedAction();
    }
    virtual void dragLeavEvent(QDragLeaveEvent* event) {
        event->accept();
    }
    virtual void dropEvent(QDropEvent* event) {
        const QMimeData* mimeData = event->mimeData();
        if (mimeData->hasUrls()) {
            QList<QUrl> urlList = mimeData->urls();
            if (0 < (urlList.size())) {
                QString fileName = urlList.at(0).toLocalFile();
                if ((m_fileEdit)) {
                    m_fileEdit->setText(fileName);
                    HashFile();
                }
            }
        }
        event->acceptProposedAction();
    }
#endif // defined(XOS_GUI_CRYPTO_HASH_QT_MAINWINDOW_ACCEPT_DROPS)
    virtual void customEvent(QEvent* event) {
        switch((event->type())) {
        case UpdateFileHash:
            HashFileUpdate();
            break;
        }
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int HashWidth(QFontMetrics& font) const {
        ssize_t hashSize = m_hash.HashSize();
        if (0 < (hashSize)) {
            int fontWidth = font.width(QChar('X'));
            int hashWidth = (fontWidth*(hashSize+2)*2);
            return hashWidth;
        }
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    enum  {
        UpdateFileHash = QEvent::User+1
    };
    class UpdateFileHashQEvent: public QEvent {
    public:
        UpdateFileHashQEvent(): QEvent((Type)(UpdateFileHash)) {}
    };
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    QPushButton* m_okButton;
    QPushButton* m_cancelButton;
    QLabel* m_hashLabel;
    QLabel* m_fileLabel;
    QLabel* m_textLabel;
    QLineEdit* m_hashEdit;
    QLineEdit* m_fileEdit;
    QTextEdit* m_textEdit;
    QProgressBar* m_progressBar;
};

} // namespace qt 
} // namespace hash 
} // namespace crypto 
} // namespace gui 
} // namespace xos 

#endif // _XOS_GUI_CRYPTO_HASH_QT_MAINWINDOW_HPP 
