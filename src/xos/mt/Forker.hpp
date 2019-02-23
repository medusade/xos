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
///   File: Forker.hpp
///
/// Author: $author$
///   Date: 10/17/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_MT_FORKER_HPP
#define _XOS_MT_FORKER_HPP

#include "xos/base/Base.hpp"

namespace xos {
namespace mt {

typedef InterfaceBase ForkerImplements;
///////////////////////////////////////////////////////////////////////
///  Class: ForkerT
///////////////////////////////////////////////////////////////////////
template <class TImplement = ForkerImplements>
class _EXPORT_CLASS ForkerT: virtual public TImplement {
public:
    typedef TImplement Implements;
    ///////////////////////////////////////////////////////////////////////
    ///  Enum: Exception
    ///////////////////////////////////////////////////////////////////////
    enum Exception {
        FailedToFork,
        FailedToJoin
    };
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool SetIsForked(bool isTrue = true) = 0;
    virtual bool IsForked() const = 0;
    virtual bool IsJoined() const = 0;
    virtual bool Joined() = 0;
    virtual bool Join() = 0;
    virtual bool Fork() = 0;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef ForkerT<> Forker;

///////////////////////////////////////////////////////////////////////
///  Class: ForkerImplementT
///////////////////////////////////////////////////////////////////////
template <class TImplement = Forker>
class _EXPORT_CLASS ForkerImplementT: virtual public TImplement {
public:
    typedef TImplement Implements;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool SetIsForked(bool isTrue = true) { return false; }
    virtual bool IsForked() const { return false; }
    virtual bool IsJoined() const { return !IsForked(); }
    virtual bool Joined() {
        if ((IsForked()))
            return Join();
        return true; }
    virtual bool Join() { return false; }
    virtual bool Fork() { return false; }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef ForkerImplementT<> ForkerImplement;

} // namespace mt 
} // namespace xos 

#endif // _XOS_MT_FORKER_HPP 
