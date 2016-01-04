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

    typedef uint32_t Uint32GmtCurrent;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Time(bool getCurrent = false, bool isGmt = false) {
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
        time_t t;
        time(&t);
        if ((isGmt)) {
            gmtime_r(&t, &tm);
        } else {
            localtime_r(&t, &tm);
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
    virtual operator Uint32GmtCurrent() const {
        time_t t;
        time(&t);
        return t;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace unix 
} // namespace xos 

#endif // _XOS_OS_UNIX_TIME_HPP 
