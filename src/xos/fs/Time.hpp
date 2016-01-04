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
///   File: Time.hpp
///
/// Author: $author$
///   Date: 10/27/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_FS_TIME_HPP
#define _XOS_FS_TIME_HPP

#include "xos/base/Base.hpp"

namespace xos {
namespace fs {

typedef InterfaceBase TimeImplement;
typedef ExportBase TimeExtend;

class _EXPORT_CLASS Time: virtual public TimeImplement, public TimeExtend {
public:
    typedef TimeImplement Implements;
    typedef TimeExtend Extends;

    class _EXPORT_CLASS Locale {
    public:
        enum Type {
            Universal,
            Local
        };
        enum At {
            Anywhere
        };
        Locale(Type type = Universal, At at = Anywhere): m_type(type), m_at(at) {}
        Locale(const Locale& copy): m_type(copy.m_type), m_at(copy.m_at) {}
        virtual ~Locale() {}
    protected:
        Type m_type;
        At m_at;
    };

    typedef int Year;
    typedef int Month;
    enum {
        January = 1, Febuary, March, 
        April, May, June,
        July, August, September,
        October, November, December,
    };
    typedef int Day;
    typedef int Hour;
    typedef int Minute;
    typedef seconds_t Second;
    typedef mseconds_t MSecond;
    typedef useconds_t USecond;

    Time
    (Year year = 0, Month month = 0, Day day = 0, 
     Hour hour = 0, Minute minute = 0, Second second = 0,
     MSecond msecond = 0, USecond usecond = 0,
     Locale::Type locale =  Locale::Universal)
    : m_year(year), m_month(month), m_day(day), 
      m_hour(hour), m_minute(minute), m_second(second), 
      m_msecond(msecond), m_usecond(usecond),
      m_locale(locale) {
    }
    Time
    (const Time& copy)
    : m_year(copy.m_year), m_month(copy.m_month), m_day(copy.m_day), 
      m_hour(copy.m_hour), m_minute(copy.m_minute), m_second(copy.m_second), 
      m_msecond(copy.m_msecond), m_usecond(copy.m_usecond),
      m_locale(copy.m_locale) {
    }
    virtual ~Time() {
    }

    inline Year GetYear() const {
        return m_year;
    }
    inline Month GetMonth() const {
        return m_month;
    }
    inline Day GetDay() const {
        return m_day;
    }
    inline Hour GetHour() const {
        return m_hour;
    }
    inline Minute GetMinute() const {
        return m_minute;
    }
    inline Second GetSecond() const {
        return m_second;
    }
    inline MSecond GetMSecond() const {
        return m_msecond;
    }
    inline USecond GetUSecond() const {
        return m_usecond;
    }
    inline Locale GetLocale() const  {
        return m_locale;
    }

protected:
    Year m_year;
    Month m_month;
    Day m_day;
    Hour m_hour;
    Minute m_minute;
    Second m_second;
    MSecond m_msecond;
    USecond m_usecond;
    Locale m_locale;
};


} // namespace fs 
} // namespace xos 


#endif // _XOS_FS_TIME_HPP 
        

