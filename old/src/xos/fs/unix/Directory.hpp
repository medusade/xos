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
///   Date: 11/1/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_FS_UNIX_DIRECTORY_HPP
#define _XOS_FS_UNIX_DIRECTORY_HPP

#include "xos/fs/Directory.hpp"
#include "xos/fs/PathDirectoryAppender.hpp"
#include "xos/fs/unix/Entry.hpp"
#include "xos/base/Opened.hpp"
#include "xos/base/Attached.hpp"
#include "xos/os/Logger.hpp"
#include <dirent.h>
#include <errno.h>

namespace xos {
namespace fs {
namespace unix {

typedef fs::DirectoryImplement DirectoryImplement;
typedef Attached<DIR*, int, 0, fs::Directory, DirectoryImplement> DirectoryAttached;
typedef Opened<DIR*, int, 0, DirectoryAttached, DirectoryImplement> DirectoryOpened;
typedef DirectoryOpened DirectoryExtend;
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Directory: virtual public DirectoryImplement, public DirectoryExtend {
public:
    typedef DirectoryImplement Implements;
    typedef DirectoryExtend Extends;
    using Extends::Open;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Directory() {
    }
    virtual ~Directory() {
        if (!(Closed())) {
            XOS_LOG_ERROR("failed  on Closed()");
        }
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Open(const wchar_t* name) {
        String path(name);
        return Open(path.Chars());
    }
    virtual bool Open(const char* name) {
        bool isOpen = false;
        DIR* detached = 0;

        if (!(Closed())) {
            return false;
        }

        if ((isOpen = (0 != (detached = opendir(name))))) {
            m_path.Assign(name);
            Attach(detached, isOpen);
            return true;
        } else {
            XOS_LOG_ERROR("failed " << errno << " on opendir(\"" << name << "\")");
        }
        return false;
    }
    virtual bool Close() {
        bool isOpen = false;
        DIR* detached = 0;
        if ((detached = Detach(isOpen))) {
            int err = 0;
            if (!(err = closedir(detached))) {
                return true;
            } else {
                XOS_LOG_ERROR("failed " << errno << " on closedir()");
            }
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual Entry* GetFirst() {
        DIR* detached = 0;
        if ((detached = AttachedTo())) {
            rewinddir(detached);
        }
        return GetNext();
    }
    virtual Entry* GetNext() {
        Entry::Found& found = m_entry.found();
        struct stat& st = found.wrapped();
        String& name = found.name();
        struct dirent* de = 0;
        DIR* detached = 0;

        if ((detached = AttachedTo())) {
            if ((de = readdir(detached))) {
                int err = 0;
                PathDirectoryAppender da(m_name);
                m_name.Assign(m_path);
                da.Append(de->d_name);
                if (!(err = stat(m_name.Chars(), &st))) {
                    name.Assign(de->d_name);
                    m_entry.SetProperties(found);
                    return &m_entry;
                } else {
                    XOS_LOG_ERROR("failed " << errno << " on stat(\"" << m_name << "\",...)");
                }
            } else {
                XOS_LOG_TRACE("failed " << errno << " on readdir()");
            }
        }
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    String m_path;
    String m_name;
    Entry m_entry;
};

} // namespace unix 
} // namespace fs 
} // namespace xos 

#endif // _XOS_FS_UNIX_DIRECTORY_HPP 
