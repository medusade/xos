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
///   File: Entry.hpp
///
/// Author: $author$
///   Date: 10/31/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_FS_UNIX_ENTRY_HPP
#define _XOS_FS_UNIX_ENTRY_HPP

#include "xos/fs/Entry.hpp"
#include "xos/fs/Path.hpp"
#include "xos/base/Wrapped.hpp"
#include <sys/stat.h>
#include <sys/time.h>
#include <time.h>
#include <errno.h>
#include <unistd.h>

namespace xos {
namespace fs {

typedef Wrapped<struct stat> EntryFoundExtend;
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Entry::Found: public EntryFoundExtend {
public:
    typedef EntryFoundExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Found() {
    }
    virtual ~Found() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    String& name() const {
        return (String&)(m_name);
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    String m_name;
};

namespace unix {

typedef fs::EntryImplement EntryImplement;
typedef fs::Entry EntryExtend;
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Entry: virtual public EntryImplement, public EntryExtend {
public:
    typedef EntryImplement Implements;
    typedef EntryExtend Extends;
    using Extends::Exists;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Entry() {
    }
    virtual ~Entry() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Exists(const char* chars) {
        struct stat& st = m_found.wrapped();
        int err = 0;
        if (!(err = stat(chars, &st))) {
            Path path(chars);
            if ((path.Separate())) {
                m_name.Assign(path.GetFileName().Chars());
                SetProperties(m_found);
            } else {
                XOS_LOG_ERROR("failed on path.Separate()");
            }
            return true;
        } else {
            XOS_LOG_ERROR("failed " << errno << " on stat(\"" << chars << "\",...)");
        }
        return false;
    }
    virtual bool Exists(const wchar_t* chars) {
        String name(chars);
        return Exists(name.Chars());
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void SetType(const Found& found) {
        struct stat& st = found.wrapped();
        if ((S_IFDIR == (S_IFDIR & st.st_mode))) {
            m_type = Directory;
        } else {
            if ((S_IFBLK == (S_IFBLK & st.st_mode)) || (S_IFCHR == (S_IFCHR & st.st_mode))) {
                m_type = Device;
            } else {
            if ((S_IFIFO == (S_IFIFO & st.st_mode)) || (S_IFSOCK == (S_IFSOCK & st.st_mode))) {
                m_type = Ipc;
            } else {
                m_type = File;
            }
            }
        }
    }
    virtual void SetSize(const Found& found) {
        struct stat& st = found.wrapped();
        m_size = st.st_size;
    }
    virtual void SetAttributes(const Found& found) {
        struct stat& st = found.wrapped();

        if ((S_IFBLK == (S_IFBLK & st.st_mode))) {
            m_attributes |= BlockDevice;
        }
        if ((S_IFIFO == (S_IFIFO & st.st_mode))) {
            m_attributes |= Fifo;
        }
        if ((S_IFSOCK == (S_IFSOCK & st.st_mode))) {
            m_attributes |= Socket;
        }
        if ((S_IFLNK == (S_IFLNK & st.st_mode))) {
            m_attributes |= SymbolicLink;
        }
    }
    virtual void SetName(const Found& found) {
        m_name.Assign(found.name().Chars());
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void SetTimes(const Found& found) {
        struct stat& st = found.wrapped();
        SetTime(Time::Changed, st.st_ctime, true);
        SetTime(Time::Modified, st.st_mtime, true);
        SetTime(Time::Accessed, st.st_atime, true);
    }
    virtual void SetTime(Time::When when, const time_t& fileTime, bool isLocal=false) {
        struct tm systemTime;
        if ((ToSystemTime(systemTime, fileTime, isLocal))) {
            Time time
            (when, systemTime.tm_year+1900, systemTime.tm_mon+1, systemTime.tm_mday,
             systemTime.tm_hour, systemTime.tm_min, systemTime.tm_sec, 0, 0,
             (isLocal)?(Time::Locale::Local):(Time::Locale::Universal));
            m_times.push_back(time);
        }
    }
    virtual bool ToSystemTime(struct tm& systemTime, const time_t& fileTime, bool isLocal=false) {
        if ((isLocal)) {
            if ((localtime_r(&fileTime, &systemTime))) {
                return true;
            } else {
                XOS_LOG_ERROR("failed " << errno << " on localtime_r()");
            }
        } else {
            if ((gmtime_r(&fileTime, &systemTime))) {
                return true;
            } else {
                XOS_LOG_ERROR("failed " << errno << " on gmtime_r()");
            }
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual Found& found() const {
        return (Found&)(m_found);
    }

protected:
    Found m_found;
};

} // namespace unix 
} // namespace fs 
} // namespace xos 

#endif // _XOS_FS_UNIX_ENTRY_HPP 




        

