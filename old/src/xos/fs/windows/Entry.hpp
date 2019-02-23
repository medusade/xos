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
#ifndef _XOS_FS_WINDOWS_ENTRY_HPP
#define _XOS_FS_WINDOWS_ENTRY_HPP

#include "xos/fs/Entry.hpp"
#include "xos/base/Wrapped.hpp"
#include "xos/os/Logger.hpp"

namespace xos {
namespace fs {

typedef Wrapped<WIN32_FIND_DATA> EntryFoundExtend;

class _EXPORT_CLASS Entry::Found: public EntryFoundExtend {
public:
    typedef EntryFoundExtend Extends;
    Found(): Extends(true) {
    }
    Found(const Found& copy): Extends(copy) {
    }
    virtual ~Found() {}
};

} // namespace fs 
} // namespace xos 

namespace xos {
namespace fs {
namespace windows {

typedef fs::EntryImplement EntryImplement;
typedef fs::Entry EntryExtend;

class _EXPORT_CLASS Entry: virtual public EntryImplement, public EntryExtend {
public:
    typedef EntryImplement Implements;
    typedef EntryExtend Extends;

    Entry() {
    }
    virtual ~Entry() {
    }

    virtual bool Exists(const char* chars) {
        TString name(chars);
        return Exists(name);
    }
    virtual bool Exists(const wchar_t* chars) {
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

    virtual void SetType(const Found& found) {
        Found::WrappedT& ff = found.wrapped();
        if (FILE_ATTRIBUTE_DIRECTORY == (FILE_ATTRIBUTE_DIRECTORY & ff.dwFileAttributes)) {
            m_type = Directory;
        } else {
            if (FILE_ATTRIBUTE_DEVICE == (FILE_ATTRIBUTE_DEVICE & ff.dwFileAttributes)) {
                m_type = Device;
            } else {
                m_type = File;
            }
        }
    }
    virtual void SetSize(const Found& found) {
        Found::WrappedT& ff = found.wrapped();
        m_size = ff.nFileSizeHigh;
        m_size <<= (sizeof(LONG) << 3);
        m_size |= ff.nFileSizeLow;
    }
    virtual void SetAttributes(const Found& found) {
        Found::WrappedT& ff = found.wrapped();
        if (FILE_ATTRIBUTE_READONLY == (FILE_ATTRIBUTE_READONLY & ff.dwFileAttributes)) {
            m_attributes |= ReadOnly;
        }
        if (FILE_ATTRIBUTE_OFFLINE == (FILE_ATTRIBUTE_OFFLINE & ff.dwFileAttributes)) {
            m_attributes |= OffLine;
        }
        if (FILE_ATTRIBUTE_ARCHIVE == (FILE_ATTRIBUTE_ARCHIVE & ff.dwFileAttributes)) {
            m_attributes |= Archive;
        }
        if (FILE_ATTRIBUTE_HIDDEN == (FILE_ATTRIBUTE_HIDDEN & ff.dwFileAttributes)) {
            m_attributes |= Hidden;
        }
        if (FILE_ATTRIBUTE_SYSTEM == (FILE_ATTRIBUTE_SYSTEM & ff.dwFileAttributes)) {
            m_attributes |= System;
        }
        if (FILE_ATTRIBUTE_TEMPORARY == (FILE_ATTRIBUTE_TEMPORARY & ff.dwFileAttributes)) {
            m_attributes |= Temporary;
        }
        if (FILE_ATTRIBUTE_VIRTUAL == (FILE_ATTRIBUTE_VIRTUAL & ff.dwFileAttributes)) {
            m_attributes |= Virtual;
        }
        if (FILE_ATTRIBUTE_REPARSE_POINT == (FILE_ATTRIBUTE_REPARSE_POINT & ff.dwFileAttributes)) {
            m_attributes |= SymbolicLink;
        }
        if (FILE_ATTRIBUTE_COMPRESSED == (FILE_ATTRIBUTE_COMPRESSED & ff.dwFileAttributes)) {
            m_attributes |= Compressed;
        }
        if (FILE_ATTRIBUTE_ENCRYPTED == (FILE_ATTRIBUTE_ENCRYPTED & ff.dwFileAttributes)) {
            m_attributes |= Encrypted;
        }
    }
    virtual void SetName(const Found& found) {
        Found::WrappedT& ff = found.wrapped();
        m_name.Assign(ff.cFileName);
    }
    virtual void SetTimes(const Found& found) {
        Found::WrappedT& ff = found.wrapped();
        SetTime(Time::Created, ff.ftCreationTime, true);
        SetTime(Time::Modified, ff.ftLastWriteTime, true);
        SetTime(Time::Accessed, ff.ftLastAccessTime, true);
    }
    void SetTime(Time::When when, const FILETIME& fileTime, bool isLocal=false) {
        SYSTEMTIME systemTime;
        if ((ToSystemTime(systemTime, fileTime, isLocal))) {
            Time time
            (when, systemTime.wYear, systemTime.wMonth, systemTime.wDay,
             systemTime.wHour, systemTime.wMinute, systemTime.wSecond, 
             systemTime.wMilliseconds, 0, 
             (isLocal)?(Time::Locale::Local):(Time::Locale::Universal));
            m_times.push_back(time);
        }
    }
    bool ToSystemTime(SYSTEMTIME& systemTime, const FILETIME& fileTime, bool isLocal=false) const {
        if ((isLocal)) {
            FILETIME localFileTime;
            if ((FileTimeToLocalFileTime(&fileTime, &localFileTime))) {
                if ((FileTimeToSystemTime(&localFileTime, &systemTime))) {
                    return true;
                }
            }
        } else {
            if ((FileTimeToSystemTime(&fileTime, &systemTime))) {
                return true;
            }
        }
        return false;
    }

    virtual bool SubstituteWhen(Time::When& when) const {
        if ((when == Time::Changed)) {
            when = Time::Modified;
            return true;
        }
        return false;
    }

    inline Found& found() const {
        return (Found&)(m_found);
    }

protected:
    Found m_found;
};

} // namespace windows 
} // namespace fs 
} // namespace xos 

#endif // _XOS_FS_WINDOWS_ENTRY_HPP 
