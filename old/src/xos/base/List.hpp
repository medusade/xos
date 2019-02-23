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
///   File: List.hpp
///
/// Author: $author$
///   Date: 4/2/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_LIST_HPP
#define _XOS_LIST_HPP

#include "xos/base/Base.hpp"

namespace xos {

///////////////////////////////////////////////////////////////////////
///  Class: ListItem
///////////////////////////////////////////////////////////////////////
template 
<class TDerive,
 class TImplement = InterfaceBase, 
 class TExtend = ExportBase>

class _EXPORT_CLASS ListItem: virtual public TImplement, public TExtend {
public:
    typedef TImplement Implements;
    typedef TExtend Extends;
    typedef TDerive Derives;

    Derives *m_prevItem, *m_nextItem;
    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: ListItem
    ///////////////////////////////////////////////////////////////////////
    ListItem(Derives* prevItem=0, Derives* nextItem=0)
    : m_prevItem(prevItem), m_nextItem(nextItem) {
    }
    virtual ~ListItem() {
    }
#include "xos/base/ListItem_members.hpp"
};

///////////////////////////////////////////////////////////////////////
///  Class: List
///////////////////////////////////////////////////////////////////////
template 
<class TItem,
 class TImplement = InterfaceBase, 
 class TExtend = ExportBase>

class _EXPORT_CLASS List: virtual public TImplement, public TExtend {
public:
    typedef TImplement Implements;
    typedef TExtend Extends;
    typedef TItem tItem;

	TItem *m_firstItem, *m_lastItem;
    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: List
    ///////////////////////////////////////////////////////////////////////
    List(TItem* firstItem=0, TItem* lastItem=0)
    : m_firstItem(firstItem), m_lastItem(lastItem) {
    }
    virtual ~List() {
    }
#include "xos/base/List_members.hpp"
};


///////////////////////////////////////////////////////////////////////
///  Class: StaticList
///////////////////////////////////////////////////////////////////////
template 
<class TItem,
 class TImplement = InterfaceBase, 
 class TExtend = ExportBase>

class _EXPORT_CLASS StaticList: virtual public TImplement, public TExtend {
public:
    typedef TImplement Implements;
    typedef TExtend Extends;

	static TItem *m_firstItem;
    static TItem *m_lastItem;
    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: StaticList
    ///////////////////////////////////////////////////////////////////////
    StaticList() {
    }
    virtual ~StaticList() {
    }
#include "xos/base/List_members.hpp"
};

} // namespace xos 

#endif // _XOS_LIST_HPP 
