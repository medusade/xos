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
///   File: Directory.hpp
///
/// Author: $author$
///   Date: 10/27/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_FS_WINDOWS_DIRECTORY_HPP
#define _XOS_FS_WINDOWS_DIRECTORY_HPP

#include "xos/fs/Directory.hpp"
#include "xos/fs/PathDirectoryAppender.hpp"
#include "xos/fs/windows/Entry.hpp"
#include "xos/fs/Entry.hpp"
#include "xos/base/Opened.hpp"
#include "xos/base/Wrapped.hpp"
#include "xos/base/String.hpp"
#include "xos/os/Logger.hpp"
#include <direct.h>

namespace xos {
namespace fs {
namespace windows {

typedef fs::DirectoryImplement DirectoryImplement;
typedef Attached<HANDLE, int, 0, fs::Directory, DirectoryImplement> DirectoryAttached;
typedef Opened<HANDLE, int, 0, DirectoryAttached, DirectoryImplement> DirectoryOpened;
typedef DirectoryOpened DirectoryExtend;

class _EXPORT_CLASS Directory: virtual public DirectoryImplement, public DirectoryExtend {
public:
    typedef DirectoryImplement Implements;
    typedef DirectoryExtend Extends;

    Directory(HANDLE detached = 0, bool isOpen = false)
    : Extends(detached, isOpen) {
    }
    virtual ~Directory() {
        if (!(Closed())) {
            XOS_LOG_ERROR("failed on Close()");
        }
    }

    using Extends::Open;
    virtual bool Open(const char* name) {
        TString path(name);
        return Open(path);
    }
    virtual bool Open(const wchar_t* name) {
        TString path(name);
        return Open(path);
    }
    virtual bool Open(const TString& name) {
        TString path(name);
        TPathDirectoryAppender appender(path);
        LPWIN32_FIND_DATA lpFindFileData = &m_entry.found().wrapped();
        LPCWSTR lpFileName = 0;
        bool isOpen = false;
        HANDLE detached = 0;

        if (!(Closed())) {
            return false;
        }

        if (!(m_entry.Exists(name))) {
            return false;
        } else {
            if ((m_entry.GetType()) != (Entry::Directory)) {
                return false;
            }
        }

        appender.Append(PATH_DIRECTORY_WILDCARD_CHARS);
        lpFileName = path.Chars();

        if ((isOpen = (INVALID_HANDLE != (detached = (FindFirstFile(lpFileName, lpFindFileData)))))) {
            m_nextEntry.found().wrapper() = m_entry.found().wrapper();
            m_entry.SetProperties(m_entry.found());
            Attach(detached, isOpen);
            return true;
        } else {
            XOS_LOG_ERROR("failed " << GetLastError() << " on FindFirstFile(\"" << String(lpFileName).Chars() << "\")");
        }
        return false;
    }
    virtual bool Close() {
        bool isOpen = false;
        HANDLE detached = 0;
        if ((detached = Detach(isOpen))) {
            if ((FindClose(detached))) {
                return true;
            } else {
                XOS_LOG_ERROR("failed " << GetLastError() << " on FindClose()");
            }
        }
        return false;
    }

    virtual Entry* GetFirst() {
        HANDLE detached = 0;
        if ((detached = AttachedTo())) {
            return &m_entry;
        }
        return 0;
    }
    virtual Entry* GetNext() {
        LPWIN32_FIND_DATA lpFindFileData = &m_nextEntry.found().wrapped();
        HANDLE detached = 0;
        if ((detached = AttachedTo())) {
            if ((FindNextFile(detached, lpFindFileData))) {
                m_nextEntry.SetProperties(m_nextEntry.found());
                return &m_nextEntry;
            }
        }
        return 0;
    }

protected:
    Entry m_entry;
    Entry m_nextEntry;
};

} // namespace windows 
} // namespace fs 
} // namespace xos 

#endif // _XOS_FS_WINDOWS_DIRECTORY_HPP 
