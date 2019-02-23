///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2013 $organization$
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
///   Date: 12/25/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_OS_TIME_HPP
#define _XOS_OS_TIME_HPP

#include "xos/base/Base.hpp"

namespace xos {

typedef InterfaceBase TimeImplement;
typedef ExportBase TimeExtend;
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Time: virtual public TimeImplement, public TimeExtend {
public:
    typedef TimeImplement Implements;
    typedef TimeExtend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Time(bool getCurrent = false, bool isGmt = false)
    : m_year(0), m_month(0), m_day(0), m_hour(0), m_minute(0), m_second(0) {
    }
    virtual ~Time() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool GetCurrent() {
        bool success = false;
        return success;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int SetYear(int to) {
        int value = m_year;
        return value;
    }
    virtual int GetYear() const {
        int value = m_year;
        return value;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int SetMonth(int to) {
        int value = m_month;
        return value;
    }
    virtual int GetMonth() const {
        int value = m_month;
        return value;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int SetDay(int to) {
        int value = m_day;
        return value;
    }
    virtual int GetDay() const {
        int value = m_day;
        return value;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int SetHour(int to) {
        int value = m_hour;
        return value;
    }
    virtual int GetHour() const {
        int value = m_hour;
        return value;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int SetMinute(int to) {
        int value = m_minute;
        return value;
    }
    virtual int GetMinute() const {
        int value = m_minute;
        return value;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int SetSecond(int to) {
        int value = m_second;
        return value;
    }
    virtual int GetSecond() const {
        int value = m_second;
        return value;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    int m_year, m_month, m_day, m_hour, m_minute, m_second;
};

} // namespace xos 

#endif // _XOS_OS_TIME_HPP 
