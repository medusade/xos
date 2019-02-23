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
///   File: Joiner.hpp
///
/// Author: $author$
///   Date: 9/20/2014
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_MT_JOINER_HPP
#define _XOS_MT_JOINER_HPP

#include "xos/mt/Waiter.hpp"

namespace xos {
namespace mt {

typedef ImplementBase JoinerImplements;
///////////////////////////////////////////////////////////////////////
///  Class: JoinerT
///////////////////////////////////////////////////////////////////////
template <class TImplement = JoinerImplements>

class _EXPORT_CLASS JoinerT: virtual public TImplement {
public:
    typedef TImplement Implements;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Joined() = 0;
    virtual bool Join() = 0;
    virtual wait::Status TryJoin() = 0;
    virtual wait::Status TimedJoin(mseconds_t waitMilliSeconds) = 0;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool SetIsForked(bool to = true) = 0;
    virtual bool IsForked() const = 0;
};
typedef JoinerT<> Joiner;

///////////////////////////////////////////////////////////////////////
///  Class: JoinerImplementT
///////////////////////////////////////////////////////////////////////
template <class TImplement = Joiner>

class _EXPORT_CLASS JoinerImplementT: virtual public TImplement {
public:
    typedef TImplement Implements;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Joined() {
        if ((this->IsForked())) {
            return Join();
        }
        return true;
    }
    virtual bool Join() {
        this->SetIsForked(false);
        return true;
    }
    virtual wait::Status TryJoin() { return wait::Success; }
    virtual wait::Status TimedJoin(mseconds_t waitMilliSeconds) { return wait::Success; }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool SetIsForked(bool to = true) { return false; }
    virtual bool IsForked() const { return false; }
};
typedef JoinerImplementT<> JoinerImplement;

typedef Base JoinedImplements;
///////////////////////////////////////////////////////////////////////
///  Class: JoinedT
///////////////////////////////////////////////////////////////////////
template <class TImplement = JoinerImplement, class TExtend = JoinedImplements>

class _EXPORT_CLASS JoinedT: virtual public TImplement, public TExtend {
public:
    typedef TImplement Implements;
    typedef TExtend Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    JoinedT(bool isForked = false): m_isForked(isForked) {
    }
    virtual ~JoinedT() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    bool m_isForked;
};
typedef JoinedT<> Joined;

} // namespace mt
} // namespace xos 

#endif // _XOS_MT_JOINER_HPP 
