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
///   File: Path.hpp
///
/// Author: $author$
///   Date: 10/28/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_FS_PATH_HPP
#define _XOS_FS_PATH_HPP

#include "xos/fs/PathParser.hpp"
#include "xos/fs/PathDirectory.hpp"
#include "xos/fs/PathDirectoryAppender.hpp"
#include "xos/os/Logger.hpp"
#include <vector>

#define PATH_EXTENSION_SEPARATOR_CHAR '.'
#define PATH_EXTENSION_SEPARATOR_CHARS "."

namespace xos {
namespace fs {

template 
<typename TChar = char, 
 class TDirectoryAppender = PathDirectoryAppender,
 class TDirectory = PathDirectory,
 class TParser = PathParser, 
 class TImplement = PathParserEvents, 
 class TExtend = String>

class _EXPORT_CLASS PathT: virtual public TImplement, public TExtend {
public:
    typedef TImplement Implements;
    typedef TExtend Extends;
    typedef TExtend TString;

    PathT(const char* chars) 
    : Extends(chars),
      m_isRootDirectory(false),
      m_isParentDirectory(false),
      m_isCurrentDirectory(false),
      m_isRoot(false),
      m_isParent(false),
      m_isCurrent(false),
      m_isCircular(false),
      m_appender(*this),
      m_directoryAppender(m_directory),
      m_fileDirectoryAppender(m_fileDirectory)
    {}
    PathT(const wchar_t* chars) 
    : Extends(chars),
      m_isRootDirectory(false),
      m_isParentDirectory(false),
      m_isCurrentDirectory(false),
      m_isRoot(false),
      m_isParent(false),
      m_isCurrent(false),
      m_isCircular(false),
      m_appender(*this),
      m_directoryAppender(m_directory),
      m_fileDirectoryAppender(m_fileDirectory)
    {}
    PathT() 
    : m_isRootDirectory(false),
      m_isParentDirectory(false),
      m_isCurrentDirectory(false),
      m_isRoot(false),
      m_isParent(false),
      m_isCurrent(false),
      m_isCircular(false),
      m_appender(*this),
      m_directoryAppender(m_directory),
      m_fileDirectoryAppender(m_fileDirectory)
    {}
    virtual ~PathT() {}

    virtual bool Separate(const char* chars, size_t length) {
        if ((chars)) {
            this->Assign(chars, length);
            return Separate();
        }
        return false;
    }
    virtual bool Separate(const char* chars) {
        if ((chars)) {
            this->Assign(chars);
            return Separate();
        }
        return false;
    }
    virtual bool Separate(const wchar_t* chars, size_t length) {
        if ((chars)) {
            this->Assign(chars, length);
            return Separate();
        }
        return false;
    }
    virtual bool Separate(const wchar_t* chars) {
        if ((chars)) {
            this->Assign(chars);
            return Separate();
        }
        return false;
    }
    virtual bool Separate() {
        TParser parser(*this);
        size_t length = 0;
        const TChar* chars = 0;
        if ((chars = this->Chars(length)) && (0 < length)) {
            if ((parser.Init())) {
                if ((parser.Write(chars, length))) {
                    if ((parser.Fini())) {
                        return true;
                    }
                }
            }
        }
        return false;
    }

    PathT& AssignDirectory(const char* chars) {
        this->clear();
        return AppendDirectory(chars);
    }
    PathT& AppendDirectory(const char* chars) {
        m_appender.Append(chars);
        return *this;
    }

    TString GetHost() const { return m_host; }
    TString GetVolume() const { return m_volume; }
    TString GetDirectory() const { return m_directory; }
    TString GetFileDirectory() const { return m_fileDirectory; }
    TString GetFileName() const { return m_fileName; }
    TString GetFileBase() const { return m_fileBase; }
    TString GetFileExtension() const { return m_fileExtension; }

protected:
    virtual bool OnInit() {
        XOS_LOG_TRACE("\n\nOnInit()\n\n");

        m_isRootDirectory = false;
        m_isParentDirectory = false;
        m_isCurrentDirectory = false;

        m_isRoot = false;
        m_isParent = false;
        m_isCurrent = false;
        m_isCircular = false;

        m_host.clear();
        m_volume.clear();
        m_directory.clear();
        m_fileDirectory.clear();
        m_fileName.clear();
        m_fileBase.clear();
        m_fileExtension.clear();

        m_directories.clear();
        return true;
    }
    virtual bool OnFini() {
        XOS_LOG_TRACE("\n\nOnFini()\n\n");
        return true;
    }
    virtual bool OnHost(const TChar* chars, ssize_t length = -1) {
        XOS_LOG_TRACE("\n\nOnHost(\"" << String(chars, length).c_str() << "\")\n\n");
        m_host.Assign(chars, length);
        return true;
    }
    virtual bool OnVolume(const TChar* chars, ssize_t length = -1) {
        XOS_LOG_TRACE("\n\nOnVolume(\"" << String(chars, length).c_str() << "\")\n\n");
        m_volume.Assign(chars, length);
        m_fileDirectoryAppender.AppendVolume(chars, length);
        return true;
    }
    virtual bool OnDirectory(const TChar* chars, ssize_t length = -1) {
        XOS_LOG_TRACE("\n\nOnDirectory(\"" << String(chars, length).c_str() << "\")\n\n");
        m_fileDirectoryAppender.Append(chars, length);
        m_directoryAppender.Append(chars, length);
        m_directories.push_back(PathDirectory(PathDirectory::Type::Named, chars, length));
        return true;
    }
    virtual bool OnParentDirectory(const TChar* chars, ssize_t length = -1) {
        XOS_LOG_TRACE("\n\nOnParentDirectory(\"" << String(chars, length).c_str() << "\")\n\n");
        m_fileDirectoryAppender.Append(chars, length);
        m_directoryAppender.Append(chars, length);
        m_directories.push_back(PathDirectory(PathDirectory::Type::Parent, chars, length));
        return true;
    }
    virtual bool OnCurrentDirectory(const TChar* chars, ssize_t length = -1) {
        XOS_LOG_TRACE("\n\nOnCurrentDirectory(\"" << String(chars, length).c_str() << "\")\n\n");
        m_fileDirectoryAppender.Append(chars, length);
        m_directoryAppender.Append(chars, length);
        m_directories.push_back(PathDirectory(PathDirectory::Type::Current, chars, length));
        return true;
    }
    virtual bool OnRootDirectory(const TChar* chars, ssize_t length = -1) {
        XOS_LOG_TRACE("\n\nOnRootDirectory(\"" << String(chars, length).c_str() << "\")\n\n");
        if ((!length) || (!chars[0])) {
            m_isRootDirectory = true;
        }
        m_fileDirectoryAppender.AppendRoot(chars, length);
        m_directoryAppender.AppendRoot(chars, length);
        m_directories.push_back(PathDirectory(PathDirectory::Type::Root, chars, length));
        return true;
    }
    virtual bool OnRootParentDirectory(const TChar* chars, ssize_t length = -1) {
        XOS_LOG_TRACE("\n\nOnRootParentDirectory(\"" << String(chars, length).c_str() << "\")\n\n");
        m_isRoot = (m_isParent = (m_isCircular = true));
        m_fileDirectoryAppender.AppendRoot(chars, length);
        m_directoryAppender.AppendRoot(chars, length);
        m_directories.push_back(PathDirectory(PathDirectory::Type::Parent, chars, length));
        return true;
    }
    virtual bool OnRootCurrentDirectory(const TChar* chars, ssize_t length = -1) {
        XOS_LOG_TRACE("\n\nOnRootCurrentDirectory(\"" << String(chars, length).c_str() << "\")\n\n");
        m_isRoot = (m_isCurrent = (m_isCircular = true));
        m_fileDirectoryAppender.AppendRoot(chars, length);
        m_directoryAppender.AppendRoot(chars, length);
        m_directories.push_back(PathDirectory(PathDirectory::Type::Current, chars, length));
        return true;
    }
    virtual bool OnRootFileName(const TChar* chars, ssize_t length = -1) {
        XOS_LOG_TRACE("\n\nOnRootFileName(\"" << String(chars, length).c_str() << "\")\n\n");
        m_isRoot = true;
        m_directoryAppender.AppendRoot();
        m_fileDirectoryAppender.AppendRoot(chars, length);
        m_fileBase.Assign(chars, length);
        m_fileName.Assign(chars, length);
        return true;
    }
    virtual bool OnFileName(const TChar* chars, ssize_t length = -1) {
        XOS_LOG_TRACE("\n\nOnFileName(\"" << String(chars, length).c_str() << "\")\n\n");
        m_fileBase.Assign(chars, length);
        m_fileName.Assign(chars, length);
        return true;
    }
    virtual bool OnFileExtension(const TChar* chars, ssize_t length = -1) {
        static const char ExtensionSeparatorChar = PATH_EXTENSION_SEPARATOR_CHAR;
        XOS_LOG_TRACE("\n\nOnFileExtension(\"" << String(chars, length).c_str() << "\")\n\n");
        m_fileExtension.Assign(chars, length);
        m_fileName.Append(&ExtensionSeparatorChar, 1);
        m_fileName.Append(chars, length);
        return true;
    }

protected:
    bool m_isRootDirectory;
    bool m_isParentDirectory;
    bool m_isCurrentDirectory;

    bool m_isRoot;
    bool m_isParent;
    bool m_isCurrent;
    bool m_isCircular;

    TString m_host;
    TString m_volume;
    TString m_directory;
    TString m_fileDirectory;
    TString m_fileName;
    TString m_fileBase;
    TString m_fileExtension;

    TDirectoryAppender m_appender;
    TDirectoryAppender m_directoryAppender;
    TDirectoryAppender m_fileDirectoryAppender;

    std::vector<TDirectory> m_directories;
};

typedef PathT<char, PathDirectoryAppender, PathDirectory, PathParser, PathParserEvents, String> Path;
typedef PathT<wchar_t, WPathDirectoryAppender, WPathDirectory, WPathParser, WPathParserEvents, WString> WPath;
typedef PathT<tchar_t, TPathDirectoryAppender, TPathDirectory, TPathParser, TPathParserEvents, TString> TPath;

} // namespace fs 
} // namespace xos 

#endif // _XOS_FS_PATH_HPP 
