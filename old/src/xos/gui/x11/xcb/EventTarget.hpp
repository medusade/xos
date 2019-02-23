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
///   File: EventTarget.hpp
///
/// Author: $author$
///   Date: 3/18/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_GUI_X11_XCB_EVENTTARGET_HPP
#define _XOS_GUI_X11_XCB_EVENTTARGET_HPP

#include "xos/base/InterfaceBase.hpp"
#include <xcb/xcb.h>
#include <map>

namespace xos {
namespace x11 {
namespace xcb {

typedef InterfaceBase EventTargetImplement;
///////////////////////////////////////////////////////////////////////
///  Class: EventTarget
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS EventTarget: virtual public EventTargetImplement {
public:
    typedef EventTargetImplement Implements;

#include "xos/gui/x11/xcb/EventTarget_members.hpp"
    virtual bool OnEvent(const xcb_generic_event_t& xcbEvent) {
        bool isDone = false;
        switch (xcbEvent.response_type) {
#include "xos/gui/x11/xcb/EventTarget_cases.hpp"
        default:
            isDone = OnEventDefault(xcbEvent);
        }
        return isDone;
    }
    virtual bool OnEventDefault(const xcb_generic_event_t& xcbEvent) {
        bool isDone = false;
        return isDone;
    }
};

typedef InterfaceBase EventTargetsImplement;
typedef ExportBase EventTargetsExtend;
///////////////////////////////////////////////////////////////////////
///  Class: EventTargets
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS EventTargets
: virtual public EventTargetsImplement, public EventTargetsExtend {
public:
    typedef EventTargetsImplement Implements;
    typedef EventTargetsExtend Extends;

    EventTargets() {}
    virtual ~EventTargets() {}

    virtual bool Insert(uint32_t id, EventTarget* target) {
        bool isSuccess = false;
        if ((isSuccess = !Find(id)))
            m_map.insert(Pair(id, target));
        return isSuccess;
    }
    virtual bool Delete(uint32_t id) {
        bool isSuccess = false;
        Map::iterator i;
        if (isSuccess = ((i = m_map.find(id)) != m_map.end()))
            m_map.erase(i);
        return isSuccess;
    }
    virtual EventTarget* Find(uint32_t id) const {
        EventTarget* target = 0;
        Map::const_iterator i;
        if ((i = m_map.find(id)) != m_map.end())
            target = i->second;
        return target;
    }
    static EventTargets& Instance();

protected:
    typedef std::pair<uint32_t, EventTarget*> Pair;
    typedef std::map<uint32_t, EventTarget*> Map;
    Map m_map;
};

} // namespace xcb 
} // namespace x11 
} // namespace xos 

#endif // _XOS_GUI_X11_XCB_EVENTTARGET_HPP 
