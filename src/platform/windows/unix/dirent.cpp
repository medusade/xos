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
///   File: dirent.cpp
///
/// Author: $author$
///   Date: 11/1/2012
///////////////////////////////////////////////////////////////////////
#include "xos/fs/windows/Directory.hpp"
#include "xos/fs/windows/Entry.hpp"
#include "xos/os/Logger.hpp"
#include "xos/base/Wrapped.hpp"
#include <direct.h>
#include <dirent.h>
#include <errno.h>

using namespace xos;

typedef InterfaceBase DirectoryImplement;
typedef ExportBase Directory;

typedef Attached<HANDLE, int, 0, Directory, DirectoryImplement> DirectoryAttached;
typedef Opened<HANDLE, int, 0, DirectoryAttached, DirectoryImplement> DirectoryOpened;
typedef DirectoryOpened DirectoryExtend;

struct DIR: virtual public DirectoryImplement, public DirectoryExtend {
    typedef DirectoryImplement Implements;
    typedef DirectoryExtend Extends;

    typedef InterfaceBase EntryImplement;
    typedef ExportBase EntryExtend;

    class _EXPORT_CLASS Entry: virtual public EntryImplement, public EntryExtend {
    public:
        typedef Wrapped<WIN32_FIND_DATA> FoundExtend;
        class _EXPORT_CLASS Found: public FoundExtend {
        public:
            typedef FoundExtend Extends;
            Found(): Extends(true) {}
            Found(const Found& copy): Extends(copy) {}
            virtual ~Found() {}
        };
        typedef EntryImplement Implements;
        typedef EntryExtend Extends;

        Entry(): m_type(fs::Entry::None) {
        }
        virtual bool Exists(const char* chars) {
            TString name(chars);
            return Exists(name);
        }
        bool Exists(const TString& name) {
            HANDLE hFF = 0;
            ClearProperties();
            if (INVALID_HANDLE != (hFF = FindFirstFile(name.Chars(), &m_found.wrapped()))) {
                SetProperties(m_found);
                if (!(FindClose(hFF))) {
                    XOS_LOG_ERROR("failed " << GetLastError() << " on FindClose()");
                } else {
                    return true;
                }
            } else {
                XOS_LOG_TRACE("failed " << GetLastError() << " on FindFirstFile(\"" << String(name.Chars()).Chars() << "\",...)");
            }
            return false;
        }
        virtual void SetProperties(const Found& found) {
            SetType(found);
            SetName(found);
        }
        virtual void ClearProperties() {
            m_type = fs::Entry::None;
            m_name.Clear();
        }
        virtual void SetType(const Found& found) {
            Found::WrappedT& ff = found.wrapped();
            if (FILE_ATTRIBUTE_DIRECTORY == (FILE_ATTRIBUTE_DIRECTORY & ff.dwFileAttributes)) {
                m_type = fs::Entry::Directory;
            } else {
                m_type = fs::Entry::File;
            }
        }
        virtual void SetName(const Found& found) {
            Found::WrappedT& ff = found.wrapped();
            m_name.Assign(ff.cFileName);
        }
        inline fs::Entry::Type GetType() const {
            return m_type;
        }
        inline fs::Entry::Name GetName() const {
            return m_name;
        }
        inline Found& found() const {
            return (Found&)(m_found);
        }
    protected:
        fs::Entry::Type m_type;
        fs::Entry::Name m_name;
        Found m_found;
    };
    DIR(): m_read(0), m_dirEntry(0) {}
    virtual ~DIR() {
        if (!(Closed())) {
            XOS_LOG_ERROR("failed on Close()");
        }
    }
    virtual bool Open(const char* name) {
        TString path(name);
        return Open(path);
    }
    virtual bool Open(const TString& name) {
        TString path(name);
        fs::TPathDirectoryAppender appender(path);
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
            if ((m_entry.GetType()) != (fs::Entry::Directory)) {
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
            m_read = &DIR::GetNext;
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
    void Rewind() {
        HANDLE detached = 0;
        if ((detached = AttachedTo())) {
            m_read = &DIR::GetFirst;
        }
    }
    Entry* Read() {
        if ((m_read)) {
            return (this->*m_read)();
        }
        return 0;
    }
    struct dirent& dirEntry() const {
        return (struct dirent&)(m_dirEntry);
    }
protected:
    typedef Entry* (DIR::*MRead)();
    MRead m_read;
    Entry m_entry;
    Entry m_nextEntry;
    Wrapped<struct dirent> m_dirEntry;
};

DIR* opendir(const char *name) {
    DIR* d = 0;
    if ((d = new DIR())) {
        if ((d->Open(name))) {
            return d;
        }
        delete d;
    }
    errno = EFAULT;
    return 0;
}
DIR* fdopendir(int fd) {
    errno = EINVAL;
    return 0;
}
int closedir(DIR* dirp) {
    if ((dirp)) {
        if ((dirp->Close())) {
            delete dirp;
            return 0;
        }
        delete dirp;
    }
    errno = EFAULT;
    return -1;
}
void rewinddir(DIR *dirp) {
    if ((dirp)) {
        dirp->Rewind();
    }
}
struct dirent* readdir(DIR *dirp) {
    DIR::Entry* e = 0;
    if ((dirp)) {
        if ((e = dirp->Read())) {
            struct dirent& de = dirp->dirEntry();
            String name(e->GetName().Chars());
            memset(de.d_name, 0, sizeof(de.d_name));
            strncpy(de.d_name, name.Chars(), sizeof(de.d_name)-1);
            return &de;
        }
    }
    errno = EFAULT;
    return 0;
}
int readdir_r(DIR* dirp, struct dirent* entry, struct dirent** result) {
    errno = EINVAL;
    return -1;
}

namespace xos {
namespace windows {
namespace unix {

} // namespace unix 
} // namespace windows 
} // namespace xos 
