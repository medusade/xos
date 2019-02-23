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
///   Date: 10/27/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_FS_ENTRY_HPP
#define _XOS_FS_ENTRY_HPP

#include "xos/fs/Time.hpp"
#include "xos/base/String.hpp"
#include <vector>

namespace xos {
namespace fs {

class _EXPORT_CLASS Directory;
class _EXPORT_CLASS File;
class _EXPORT_CLASS Link;
class _EXPORT_CLASS SymbolicLink;

typedef InterfaceBase EntryImplement;
typedef ExportBase EntryExtend;
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Entry: virtual public EntryImplement, public EntryExtend {
public:
    typedef EntryImplement Implements;
    typedef EntryExtend Extends;

    typedef int Type;
    enum {
        None,
        File,
        Directory,
        Device,
        Ipc
    };
    typedef uint64_t Size;
    typedef int Attribute;
    typedef Attribute Attributes;
    enum {
        Normal       = (0),
        Archive      = (1 << 0),
        BlockDevice  = (1 << 1),
        Compressed   = (1 << 2),
        Encrypted    = (1 << 3),
        Fifo         = (1 << 4),
        Hidden       = (1 << 5),
        OffLine      = (1 << 6),
        ReadOnly     = (1 << 7),
        Socket       = (1 << 8),
        SymbolicLink = (1 << 9),
        System       = (1 << 10),
        Temporary    = (1 << 11),
        Virtual      = (1 << 12)
    };
    typedef TString Name;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    class _EXPORT_CLASS Time: public fs::Time {
    public:
        typedef fs::Time Extends;
        typedef int When;
        enum {
            None,
            Created,
            Modified,
            Accessed,
            Changed
        };
        Time
        (When when = None, Year year = 0, Month month = 0, Day day = 0, 
         Hour hour = 0, Minute minute = 0, Second second = 0,
         MSecond msecond = 0, USecond usecond = 0,
         Locale::Type locale =  Locale::Universal)
        : Extends(year, month, day, hour, minute, second, msecond, usecond, locale),
          m_when(when) {
        }
        Time(const Time& copy)
        : Extends(copy),
          m_when(copy.m_when) {
        }
        inline operator When() const {
            return m_when;
        }
    protected:
        When m_when;
    };
    typedef std::vector<Time> Times;

    class _EXPORT_CLASS Found;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Entry() {
    }
    virtual ~Entry() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    bool Exists(const std::string& string) {
        return Exists(string.c_str());
    }
    bool Exists(const std::wstring& string) {
        return Exists(string.c_str());
    }
    bool Exists(const String& string) {
        return Exists(string.Chars());
    }
    bool Exists(const WString& string) {
        return Exists(string.Chars());
    }
    bool Exists(const char* chars, size_t length) {
        String string(chars, length);
        return Exists(string.Chars());
    }
    bool Exists(const wchar_t* chars, size_t length) {
        WString string(chars, length);
        return Exists(string.Chars());
    }
    virtual bool Exists(const char* chars) {
        return false;
    }
    virtual bool Exists(const wchar_t* chars) {
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void SetProperties(const Found& found) {
        ClearProperties();
        SetType(found);
        SetSize(found);
        SetAttributes(found);
        SetName(found);
        SetTimes(found);
    }
    virtual void ClearProperties() {
        m_type = None;
        m_size = 0;
        m_attributes = None;
        m_name.Clear();
        m_times.clear();
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void SetType(const Found& found) {
    }
    virtual void SetSize(const Found& found) {
    }
    virtual void SetAttributes(const Found& found) {
    }
    virtual void SetName(const Found& found) {
    }
    virtual void SetTimes(const Found& found) {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Time GetTimeCreated() const {
        return GetTime(Time::Created);
    }
    Time GetTimeModified() const {
        return GetTime(Time::Modified);
    }
    Time GetTimeAccessed() const {
        return GetTime(Time::Accessed);
    }
    Time GetTimeChanged() const {
        return GetTime(Time::Changed);
    }
    virtual Time GetTime(Time::When when) const {
        Times::const_iterator end = m_times.end();
        Times::const_iterator i;
        Time time;
        int trys, tried;
        for (trys = 1, tried = 0; tried < trys; tried++) {
            for (i = m_times.begin(); i != end; ++i) {
                const Time& t = (*i);
                if (!(when != ((Time::When)(t)))) {
                    time = t;
                    return time;
                }
            }
            if ((SubstituteWhen(when))) {
                trys = 2;
            }
        }
        return time;
    }
    virtual bool SubstituteWhen(Time::When& when) const {
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    inline const Type& GetType() const {
        return m_type;
    }
    inline const Size& GetSize() const {
        return m_size;
    }
    inline const Attributes& GetAttributes() const {
        return m_attributes;
    }
    inline const Name& GetName() const {
        return m_name;
    }
    inline const Times& GetTimes() const {
        return m_times;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    Type m_type;
    Size m_size;
    Attributes m_attributes;
    Name m_name;
    Times m_times;
};

} // namespace fs 
} // namespace xos 

#endif // _XOS_FS_ENTRY_HPP 
