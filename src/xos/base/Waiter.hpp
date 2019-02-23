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
///   File: Waiter.hpp
///
/// Author: $author$
///   Date: 12/9/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_BASE_WAITER_HPP
#define _XOS_BASE_WAITER_HPP

#include "xos/base/Wait.hpp"

namespace xos {

template
<class TWaited,
 class TExtend = ExportBase,
 class TImplement = InterfaceBase>
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class EXPORT_CLASS Waiter: virtual public TImplement, public TExtend {
public:
    typedef TImplement Implements;
    typedef TExtend Extends;
    typedef TWaited WaitedT;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Waiter(WaitedT& waited, mseconds_t waitMilliseconds, bool continued = false)
    : m_waited(waited), m_continued(continued) {
        WaitInterface::Status status = WaitInterface::Failed;
        if (WaitInterface::Success != (status = m_waited.TimedWait(waitMilliseconds))) {
            if (WaitInterface::Busy != (status)) {
                Error error(Error::Failed);
                throw(error);
            } else {
                throw(status);
            }
        }
    }
    Waiter(WaitedT& waited, bool continued = false)
    : m_waited(waited), m_continued(continued) {
        if (!(m_waited.Wait())){
            Error error(Error::Failed);
            throw(error);
        }
    }
    virtual ~Waiter(){
        if ((m_continued)) {
            if (!(m_waited.Continue())) {
                Error error(Error::Failed);
                throw(error);
            }
        }
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    WaitedT& m_waited;
    bool m_continued;
};

} // namespace xos

#endif // _XOS_BASE_WAITER_HPP 
