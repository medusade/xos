///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2012 $organization$
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
///   File: PathDirectoryAppender.hpp
///
/// Author: $author$
///   Date: 10/29/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_FS_PATHDIRECTORYAPPENDER_HPP
#define _XOS_FS_PATHDIRECTORYAPPENDER_HPP

#include "xos/fs/PathDirectory.hpp"
#include "xos/base/String.hpp"

namespace xos {
namespace fs {

template <typename TChar = char, class TString = String>

class _EXPORT_CLASS PathDirectoryAppenderT {
public:
    PathDirectoryAppenderT(TString& string, const char* chars, ssize_t length, bool omitSeparator=false)
    : m_string(string), 
      m_separator(NORMAL_PATH_DIRECTORY_SEPARATOR_CHARS), 
      m_volumeSeparator(NORMAL_PATH_VOLUME_SEPARATOR_CHARS) {
          Append(chars, length, omitSeparator);
    }
    PathDirectoryAppenderT(TString& string, const wchar_t* chars, ssize_t length, bool omitSeparator=false)
    : m_string(string), 
      m_separator(NORMAL_PATH_DIRECTORY_SEPARATOR_CHARS), 
      m_volumeSeparator(NORMAL_PATH_VOLUME_SEPARATOR_CHARS) {
          Append(chars, length, omitSeparator);
    }
    PathDirectoryAppenderT(TString& string, const char* chars)
    : m_string(string), 
      m_separator(NORMAL_PATH_DIRECTORY_SEPARATOR_CHARS), 
      m_volumeSeparator(NORMAL_PATH_VOLUME_SEPARATOR_CHARS) {
          Append(chars);
    }
    PathDirectoryAppenderT(TString& string, const wchar_t* chars)
    : m_string(string), 
      m_separator(NORMAL_PATH_DIRECTORY_SEPARATOR_CHARS), 
      m_volumeSeparator(NORMAL_PATH_VOLUME_SEPARATOR_CHARS) {
          Append(chars);
    }
    PathDirectoryAppenderT(TString& string)
    : m_string(string), 
      m_separator(NORMAL_PATH_DIRECTORY_SEPARATOR_CHARS), 
      m_volumeSeparator(NORMAL_PATH_VOLUME_SEPARATOR_CHARS) {
    }

    PathDirectoryAppenderT& Append(const char* chars, size_t length, bool omitSeparator=false) {
        size_t size;
        if (!(omitSeparator) && (0 < (size = m_string.Length()))) {
            if ((m_string[size-1]) != (m_separator[0])) {
                m_string.Append(m_separator);
            }
        }
        m_string.Append(chars, length);
        return *this;
    }
    PathDirectoryAppenderT& Append(const wchar_t* chars, size_t length, bool omitSeparator=false) {
        size_t size;
        if (!(omitSeparator) && (0 < (size = m_string.Length()))) {
            if ((m_string[size-1]) != (m_separator[0])) {
                m_string.Append(m_separator);
            }
        }
        m_string.Append(chars, length);
        return *this;
    }
    PathDirectoryAppenderT& Append(const char* chars) {
        size_t size;
        if ((0 < (size = m_string.Length()))) {
            if ((m_string[size-1]) != (m_separator[0])) {
                m_string.Append(m_separator);
            }
        }
        m_string.Append(chars);
        return *this;
    }
    PathDirectoryAppenderT& Append(const wchar_t* chars) {
        size_t size;
        if ((0 < (size = m_string.Length()))) {
            if ((m_string[size-1]) != (m_separator[0])) {
                m_string.Append(m_separator);
            }
        }
        m_string.Append(chars);
        return *this;
    }

    PathDirectoryAppenderT& AppendRoot() {
        m_string.Append(m_separator);
        return *this;
    }
    PathDirectoryAppenderT& AppendRoot(const char* chars, size_t length) {
        m_string.Append(m_separator);
        m_string.Append(chars, length);
        return *this;
    }
    PathDirectoryAppenderT& AppendRoot(const wchar_t* chars, size_t length) {
        m_string.Append(m_separator);
        m_string.Append(chars, length);
        return *this;
    }
    PathDirectoryAppenderT& AppendVolume() {
        m_string.Append(m_volumeSeparator);
        return *this;
    }
    PathDirectoryAppenderT& AppendVolume(const char* chars, size_t length) {
        m_string.Append(chars, length);
        m_string.Append(m_volumeSeparator);
        return *this;
    }
    PathDirectoryAppenderT& AppendVolume(const wchar_t* chars, size_t length) {
        m_string.Append(chars, length);
        m_string.Append(m_volumeSeparator);
        return *this;
    }
protected:
    TString& m_string;
    TString m_separator;
    TString m_volumeSeparator;
};

typedef PathDirectoryAppenderT<char, String> PathDirectoryAppender;
typedef PathDirectoryAppenderT<wchar_t, WString> WPathDirectoryAppender;
typedef PathDirectoryAppenderT<tchar_t, TString> TPathDirectoryAppender;

} // namespace fs 
} // namespace xos 

#endif // _XOS_FS_PATHDIRECTORYAPPENDER_HPP 
