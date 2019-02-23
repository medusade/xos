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
#ifndef _XOS_GUI_CRYPTO_HASH_MAINWINDOW_HPP
#define _XOS_GUI_CRYPTO_HASH_MAINWINDOW_HPP

#include "xos/crypto/hash/Interface.hpp"
#include "xos/base/Array.hpp"
#include "xos/base/String.hpp"
#include "xos/os/Logger.hpp"
#include <sys/stat.h>

#define XOS_APP_GUI_CRYPTO_HASH_MAINWINDOW_FILE_BUFFER_SIZE (1024*64)

namespace xos {
namespace gui {
namespace crypto {
namespace hash {

///////////////////////////////////////////////////////////////////////
///  Class: MainWindow
///////////////////////////////////////////////////////////////////////
template <class TExtend>
class _EXPORT_CLASS MainWindow: public TExtend {
public:
    typedef TExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    MainWindow(xos::crypto::hash::Interface& hash, const char* hashName)
    : m_hash(hash),
      m_hashName(hashName),
      m_hexA('A'),
      m_file(0),
      m_fileSize(0),
      m_fileAmount(0),
      m_fileBufferLength(0),
      m_fileBufferSize(XOS_APP_GUI_CRYPTO_HASH_MAINWINDOW_FILE_BUFFER_SIZE) {
    }
    virtual ~MainWindow() {
    }
protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool GetHashText(String& hashText) = 0;
    virtual bool GetHashFileName(String& fileName) = 0;
    virtual bool PostUpdateFileHashEvent() = 0;
    virtual bool ShowHash(const String& hashX) = 0;
    virtual bool ClearHash() = 0;
    virtual bool ShowProgress(size_t maximum, size_t amount) = 0;
    virtual bool UpdateProgress(size_t amount) = 0;
    virtual bool HideProgress() = 0;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool HashText() {
        CloseFile();
        if ((ClearHash())) {
            if ((BeginHash())) {
                String textString;
                if ((GetHashText(textString))) {
                    const char* textChars;
                    size_t textLength;
                    if ((0 < (textLength = textString.length()))
                        && (textChars = textString.Chars())) {
                        if ((Hash(textChars, textLength)))
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
        if ((ClearHash())) {
            if ((BeginHash())) {
                String fileString;
                if ((GetHashFileName(fileString))) {
                    if (0 < (fileString.length())) {
                        const char* chars;
                        if ((chars = fileString.Chars())) {
                            int err;
                            struct stat st;
                            if (!(err = stat(chars, &st))) {
                                m_fileSize = st.st_size;
                            } else {
                                XOS_LOG_DEBUG("unable to stat \"" << chars << "\"");
                            }
                            if ((m_file = fopen(chars, "rb"))) {
                                HashFileUpdate(true);
                            } else {
                                XOS_LOG_DEBUG("unable to open \"" << chars << "\"");
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
                    PostUpdateFileHashEvent();
                    return true;
                }
            } else {
                EndHash();
            }
            CloseFile();
            return true;
        }
        return false;
    }
    virtual bool HashBlank() {
        CloseFile();
        if ((ClearHash())) {
            if ((BeginHash())) {
                EndHash();
                return true;
            }
        }
        return false;
    }
    virtual bool HashCancel() {
        CloseFile();
        ClearHash();
        return true;
    }
    virtual bool CloseFile() {
        HideProgress();
        if ((m_file)) {
            fclose(m_file);
            m_file = 0;
            m_fileSize = 0;
            m_fileAmount = 0;
        }
        return false;
    }
    virtual bool ShowProgress() {
        if ((0 < (m_fileSize))) {
            if ((ShowProgress(m_fileSize, m_fileAmount += m_fileBufferLength))) {
                return true;
            }
        }
        return false;
    }
    virtual bool UpdateProgress() {
        if ((0 < (m_fileSize))) {
            UpdateProgress(m_fileAmount += m_fileBufferLength);
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
        if (0 < (m_hash.Finalize(m_hashArray.Elements(), m_hashArray.Length()))) {
            UpdateHash();
            return true;
        }
        return false;
    }
    virtual bool UpdateHash() {
        String hashXString;
        const char* hashChars;
        size_t hashLength;
        if ((hashChars = (m_hashArray.Elements()))
            && ((hashLength = m_hashArray.Length()))) {
            hashXString.AppendX(hashChars, hashLength, m_hexA);
            ShowHash(hashXString);
            return true;
        }
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool SetIsUpperX(bool to = true) {
        m_hexA = (to)?('A'):('a');
        UpdateHash();
        return to;
    }
    virtual bool GetIsUpperX() const {
        return ('A' == m_hexA);
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    xos::crypto::hash::Interface& m_hash;
    const char* m_hashName;
    char m_hexA;
    xos::CharArray m_hashArray;
    FILE* m_file;
    size_t m_fileSize;
    size_t m_fileAmount;
    size_t m_fileBufferLength;
    size_t m_fileBufferSize;
    uint8_t m_fileBuffer[XOS_APP_GUI_CRYPTO_HASH_MAINWINDOW_FILE_BUFFER_SIZE];
};

} // namespace hash 
} // namespace crypto 
} // namespace gui 
} // namespace xos 

#endif // _XOS_GUI_CRYPTO_HASH_MAINWINDOW_HPP 
