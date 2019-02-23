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
#ifndef _XOS_OS_UNIX_TIME_HPP
#define _XOS_OS_UNIX_TIME_HPP

#include "xos/os/Time.hpp"
#include "xos/os/Logger.hpp"

namespace xos {
namespace unix {

typedef TimeImplement TimeImplement;
typedef Time TimeExtend;
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Time: virtual public TimeImplement, public TimeExtend {
public:
    typedef TimeImplement Implements;
    typedef TimeExtend Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Time(bool getCurrent = false, bool isGmt = false): m_time(0) {
        if ((getCurrent)) {
            if (!(GetCurrent(isGmt))) {
                XOS_LOG_ERROR("failed on GetCurrent()");
            }
        }
    }
    virtual ~Time() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool GetCurrent(bool isGmt = false) {
        bool success = true;
        struct tm tm;
        time(&m_time);
        if ((isGmt)) {
            gmtime_r(&m_time, &tm);
        } else {
            localtime_r(&m_time, &tm);
        }
        m_year = tm.tm_year+1900;
        m_month = tm.tm_mon+1;
        m_day = tm.tm_mday;
        m_hour = tm.tm_hour;
        m_minute = tm.tm_min;
        m_second = tm.tm_sec;
        return success;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual uint32_t ToUint32() const {
        return m_time;
    }
    virtual operator uint32_t() const {
        return m_time;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    time_t m_time;
};

namespace current {
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Time: public unix::Time {
public:
    typedef unix::Time Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Time(bool isGmt = false): Extends(true, isGmt) {}
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
namespace gmt {
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Time: public current::Time {
public:
    typedef current::Time Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Time(): Extends(true) {}
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
} // namespace gmt
} // namespace current

} // namespace unix 
} // namespace xos 

#endif // _XOS_OS_UNIX_TIME_HPP 
