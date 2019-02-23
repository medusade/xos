///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2014 $organization$
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
///   File: Acquirer.hpp
///
/// Author: $author$
///   Date: 4/14/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_MT_ACQUIRER_HPP
#define _XOS_MT_ACQUIRER_HPP

#include "xos/mt/Waiter.hpp"

namespace xos {
namespace mt {

///////////////////////////////////////////////////////////////////////
///  Class: AcquirerT
///////////////////////////////////////////////////////////////////////
template <class TImplement  = InterfaceBase>

class _EXPORT_CLASS AcquirerT: virtual public TImplement {
public:
    typedef TImplement Implements;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Acquire() = 0;
    virtual bool Release() = 0;
    virtual wait::Status TryAcquire() = 0;
    virtual wait::Status TimedAcquire(mseconds_t waitMilliSeconds) = 0;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef AcquirerT<> Acquirer;

///////////////////////////////////////////////////////////////////////
///  Class: AcquirerImplementT
///////////////////////////////////////////////////////////////////////
template <class TImplement  = Acquirer>

class _EXPORT_CLASS AcquirerImplementT: virtual public TImplement {
public:
    typedef TImplement Implements;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Acquire() { return true; }
    virtual bool Release() { return true; }
    virtual wait::Status TryAcquire() { return wait::Success; }
    virtual wait::Status TimedAcquire(mseconds_t waitMilliSeconds) { return wait::Success; }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef AcquirerImplementT<> AcquirerImplement;

///////////////////////////////////////////////////////////////////////
///  Class: AcquiredT
///////////////////////////////////////////////////////////////////////
template <class TAcquirer = Acquirer, class TExtend = ExportBase, class TImplement = InterfaceBase>
class _EXPORT_CLASS AcquiredT: virtual public TImplement, public TExtend {
public:
    typedef TImplement Implements;
    typedef TExtend Extends;
    typedef TAcquirer Acquirer;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    AcquiredT(Acquirer& acquirer, mseconds_t waitMilliSeconds): m_acquirer(acquirer) {
        wait::Status status;
        if (wait::Success != (status = m_acquirer.TimedAcquire(waitMilliSeconds))) {
            throw (status);
        }
    }
    AcquiredT(Acquirer& acquirer): m_acquirer(acquirer) {
        if (!(m_acquirer.Acquire())) {
            wait::Status status = wait::Failed;
            throw (status);
        }
    }
    virtual ~AcquiredT() {
        if (!(m_acquirer.Release())) {
            wait::Status status = wait::Failed;
            throw (status);
        }
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    Acquirer& m_acquirer;
};
typedef AcquiredT<> Acquired;

///////////////////////////////////////////////////////////////////////
///  Class: AcquireT
///////////////////////////////////////////////////////////////////////
template <class TAcquirer = Acquirer, class TExtend = ExportBase, class TImplement = InterfaceBase>
class _EXPORT_CLASS AcquireT: virtual public TImplement, public TExtend {
public:
    typedef TImplement Implements;
    typedef TExtend Extends;
    typedef TAcquirer Acquirer;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    AcquireT(Acquirer& acquirer, mseconds_t waitMilliSeconds) {
        wait::Status status;
        if (wait::Success != (status = acquirer.TimedAcquire(waitMilliSeconds))) {
            throw (status);
        }
    }
    AcquireT(Acquirer& acquirer) {
        if (!(acquirer.Acquire())) {
            wait::Status status = wait::Failed;
            throw (status);
        }
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef AcquireT<> Acquire;

///////////////////////////////////////////////////////////////////////
///  Class: ReleaseT
///////////////////////////////////////////////////////////////////////
template <class TAcquirer = Acquirer, class TExtend = ExportBase, class TImplement = InterfaceBase>
class _EXPORT_CLASS ReleaseT: virtual public TImplement, public TExtend {
public:
    typedef TImplement Implements;
    typedef TExtend Extends;
    typedef TAcquirer Acquirer;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    ReleaseT(Acquirer& acquirer) {
        if (!(acquirer.Acquire())) {
            wait::Status status = wait::Failed;
            throw (status);
        }
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef ReleaseT<> Release;

} // namespace mt
} // namespace xos 

#endif // _XOS_MT_ACQUIRER_HPP 
