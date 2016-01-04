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
///   File: MainWindow.hpp
///
/// Author: $author$
///   Date: 7/27/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_APP_GUI_QT_CRYPTO_HASH_MAINWINDOW_HPP
#define _XOS_APP_GUI_QT_CRYPTO_HASH_MAINWINDOW_HPP

#include "xos/gui/qt/WindowMain.hpp"
#include "xos/crypto/hash/Interface.hpp"
#include "xos/base/Array.hpp"
#include "xos/base/String.hpp"
#include <sys/stat.h>

#define XOS_APP_GUI_QT_CRYPTO_HASH_MAINWINDOW_FILE_BUFFER_SIZE (1024*64)

#if (!defined(WINDOWS) || !(QT_VERSION < 0x040700))
#define XOS_APP_GUI_QT_CRYPTO_HASH_MAINWINDOW_ACCEPT_DROPS
#endif // (!defined(WINDOWS) || !(QT_VERSION < 0x040700))

namespace xos {
namespace app {
namespace gui {
namespace qt {
namespace crypto {
namespace hash {

typedef QMainWindow MainWindowExtend;
///////////////////////////////////////////////////////////////////////
///  Class: MainWindow
///
/// Author: $author$
///   Date: 7/27/2013
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS MainWindow: public MainWindowExtend {
Q_OBJECT
public:
    typedef MainWindowExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: MainWindow
    ///////////////////////////////////////////////////////////////////////
    MainWindow(xos::crypto::hash::Interface& hash, const char* hashName = 0)
    : m_hash(hash),
      m_hashName(hashName),
      m_okButton(0), 
      m_cancelButton(0),
      m_hashLabel(0),
      m_fileLabel(0),
      m_textLabel(0),
      m_hashEdit(0),
      m_fileEdit(0),
      m_textEdit(0),
      m_progressBar(0),
      m_file(0),
      m_fileSize(0),
      m_fileAmount(0),
      m_fileBufferLength(0),
      m_fileBufferSize(XOS_APP_GUI_QT_CRYPTO_HASH_MAINWINDOW_FILE_BUFFER_SIZE) {
    }
    virtual ~MainWindow() {
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

#if defined(XOS_APP_GUI_QT_CRYPTO_HASH_MAINWINDOW_ACCEPT_DROPS)
                                            setAcceptDrops(true);
#endif // defined(XOS_APP_GUI_QT_CRYPTO_HASH_MAINWINDOW_ACCEPT_DROPS)
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
#if defined(XOS_APP_GUI_QT_CRYPTO_HASH_MAINWINDOW_ACCEPT_DROPS)
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
#endif // defined(XOS_APP_GUI_QT_CRYPTO_HASH_MAINWINDOW_ACCEPT_DROPS)
    virtual void customEvent(QEvent* event) {
        switch((event->type())) {
        case UpdateFileHash:
            HashFileUpdate();
            break;
        }
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool HashText() {
        CloseFile();
        if ((m_hashEdit)) {
            m_hashEdit->clear();
            if ((BeginHash())) {
                if ((m_textEdit)) {
                    QString textString = m_textEdit->toPlainText();
                    if (0 < (textString.length())) {
                        QByteArray textArray = textString.toUtf8();
                        if ((Hash(textArray.data(), textArray.length())))
                            EndHash();
                        return true;
                    }
                }
            }
        }
        return false;
    }
    virtual bool HashFile() {
        CloseFile();
        if ((m_hashEdit)) {
            m_hashEdit->clear();
            if ((BeginHash())) {
                if ((m_fileEdit)) {
                    QString fileString = m_fileEdit->text();
                    if (0 < (fileString.length())) {
                        QByteArray fileArray = fileString.toUtf8();
                        xos::String string(fileArray.data(), fileArray.length());
                        const char* chars = string.Chars();
                        if ((chars)) {
                            int err;
                            struct stat st;
                            if (!(err = stat(chars, &st))) {
                                m_fileSize = st.st_size;
                            }
                            if ((m_file = fopen(chars, "rb"))) {
                                HashFileUpdate(true);
                            }
                        }
                        return true;
                    }
                }
            }
        }
        return false;
    }
    virtual bool HashFileUpdate(bool isShow = false) {
        if ((m_file)) {
            m_fileBuffer[m_fileBufferSize-1] = 0;
            if (0 < (m_fileBufferLength = fread(m_fileBuffer, 1,m_fileBufferSize-1, m_file))) {
                if ((Hash(m_fileBuffer, m_fileBufferLength)))
                if ((m_fileBufferSize-1) > m_fileBufferLength)
                    EndHash();
                else {
                    if (isShow)
                        ShowProgress();
                    else UpdateProgress();
                    QApplication::postEvent(this, new UpdateFileHashQEvent());
                    return true;
                }
            } else {
                EndHash();
            }
            CloseFile();
            if (!isShow)
                HideProgress();
            return true;
        }
        return false;
    }
    virtual bool HashBlank() {
        CloseFile();
        if ((m_hashEdit)) {
            m_hashEdit->clear();
            if ((BeginHash())) {
                EndHash();
            }
        }
        return false;
    }
    virtual bool CloseFile() {
        if ((m_file)) {
            fclose(m_file);
            m_file = 0;
            m_fileSize = 0;
            m_fileAmount = 0;
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
    virtual bool ShowProgress() {
        if ((0 < (m_fileSize)) && (m_progressBar)) {
            m_progressBar->setMaximum(m_fileSize);
            if ((UpdateProgress())) {
                m_progressBar->show();
                return true;
            }
        }
        return false;
    }
    virtual bool UpdateProgress() {
        if ((0 < (m_fileSize)) && (m_progressBar)) {
            m_progressBar->setValue(m_fileAmount += m_fileBufferLength);
            return true;
        }
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool BeginHash() {
        ssize_t hashSize = m_hash.HashSize();
        if (0 < (hashSize))
        if (0 < (m_hashArray.SetLength(hashSize)))
        if (0 <= (m_hash.Initialize()))
            return true;
        return false;
    }
    virtual bool Hash(const void* in, ssize_t inlen) {
        if (0 <= (m_hash.Hash(in, inlen)))
            return true;
        return false;
    }
    virtual bool EndHash() {
        if ((m_hashEdit)) {
            if (0 < (m_hash.Finalize(m_hashArray.Elements(), m_hashArray.Length()))) {
                xos::String hashString;
                const char* hashXChars;
                if ((hashXChars = hashString.AppendX(m_hashArray.Elements(), m_hashArray.Length()).Chars())) {
                    QString hashString(hashXChars);
                    m_hashEdit->setText(hashString);
                    return true;
                }
            }
        }
        return false;
    }
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
        UpdateFileHash = QEvent::User+1,
    };
    class UpdateFileHashQEvent: public QEvent {
    public:
        UpdateFileHashQEvent(): QEvent((Type)(UpdateFileHash)) {}
    };
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    xos::crypto::hash::Interface& m_hash;
    const char* m_hashName;
    xos::CharArray m_hashArray;
    QPushButton* m_okButton;
    QPushButton* m_cancelButton;
    QLabel* m_hashLabel;
    QLabel* m_fileLabel;
    QLabel* m_textLabel;
    QLineEdit* m_hashEdit;
    QLineEdit* m_fileEdit;
    QTextEdit* m_textEdit;
    QProgressBar* m_progressBar;
    FILE* m_file;
    size_t m_fileSize;
    size_t m_fileAmount;
    size_t m_fileBufferLength;
    size_t m_fileBufferSize;
    uint8_t m_fileBuffer[XOS_APP_GUI_QT_CRYPTO_HASH_MAINWINDOW_FILE_BUFFER_SIZE];
};

} // namespace hash 
} // namespace crypto 
} // namespace qt 
} // namespace gui 
} // namespace app 
} // namespace xos 

#endif // _XOS_APP_GUI_QT_CRYPTO_HASH_MAINWINDOW_HPP 
