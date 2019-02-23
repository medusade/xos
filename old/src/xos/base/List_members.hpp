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
///   File: List_members.hpp
///
/// Author: $author$
///   Date: 4/2/2013
///////////////////////////////////////////////////////////////////////

    virtual TItem* AddItem(TItem& item) {
        TItem* memberItem = &item;
		item.m_nextItem = 0;

		if ((item.m_prevItem = m_lastItem))
			m_lastItem->m_nextItem = &item;
		else m_firstItem = &item;

		m_lastItem = &item;
        return memberItem;
    }
    virtual TItem* PushItem(TItem& item) {
        TItem* memberItem = &item;
		item.m_prevItem = 0;

		if ((item.m_nextItem = m_firstItem))
			m_firstItem->m_prevItem = &item;
		else m_lastItem = &item;

		m_firstItem = &item;
        return memberItem;
    }
    virtual TItem* InsertBeforeItem(TItem& otherItem, TItem& item) {
        TItem* memberItem = &item;
        if ((item.m_prevItem = otherItem.m_prevItem))
            otherItem.m_prevItem->m_nextItem = &item;
        else m_firstItem = &item;

        item.m_nextItem = &otherItem;
        otherItem.m_prevItem = &item;
        return memberItem;
    }
    virtual TItem* InsertAfterItem(TItem& otherItem, TItem& item) {
        TItem* memberItem = &item;
        if ((item.m_nextItem = otherItem.m_nextItem))
            otherItem.m_nextItem->m_prevItem = &item;
        else m_lastItem = &item;

        item.m_prevItem = &otherItem;
        otherItem.m_nextItem = &item;
        return memberItem;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual TItem* DeleteItem(TItem& item) {
        TItem* memberItem = &item;
		if (item.m_nextItem)
			item.m_nextItem->m_prevItem = item.m_prevItem;
		else m_lastItem = item.m_prevItem;

		if (item.m_prevItem)
			item.m_prevItem->m_nextItem = item.m_nextItem;
		else m_firstItem = item.m_nextItem;

		item.m_nextItem = 0;
		item.m_prevItem = 0;
        return memberItem;
    }
    virtual TItem* PopItem() {
        TItem* item = 0;

		if ((item = m_firstItem))
		{
			TItem* nextItem;

			if ((nextItem = item->m_nextItem))
				nextItem->m_prevItem = 0;
			else m_lastItem = 0;

			m_firstItem = nextItem;
			item->m_nextItem = 0;
			item->m_prevItem = 0;
		}
        return item;
    }
    virtual TItem* PullItem() {
        TItem* item = 0;

		if ((item = m_lastItem))
		{
			TItem* prevItem;

			if ((prevItem = item->m_prevItem))
				prevItem->m_nextItem = 0;
			else m_firstItem = 0;

			m_lastItem = prevItem;
			item->m_nextItem = 0;
			item->m_prevItem = 0;
		}
        return item;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual TItem* AddItems(TItem& firstItem, TItem& lastItem) {
        TItem* memberItem = &firstItem;
		lastItem.m_nextItem = 0;

		if ((firstItem.m_prevItem = m_lastItem) != 0)
			m_lastItem->m_nextItem = &firstItem;
		else m_firstItem = &firstItem;

		m_lastItem = &lastItem;
        return memberItem;
    }
    virtual TItem* PushItems(TItem& firstItem, TItem& lastItem) {
        TItem* memberItem = &firstItem;
		firstItem.m_prevItem = 0;

		if ((lastItem.m_nextItem = m_firstItem) != 0)
			m_firstItem->m_prevItem = &lastItem;
		else m_lastItem = &lastItem;

		m_firstItem = &firstItem;
        return memberItem;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual TItem* InsertItemsBefore
    (TItem& otherItem, TItem& firstItem, TItem& lastItem) {
        TItem* memberItem = &firstItem;
        if ((firstItem.m_prevItem = otherItem.m_prevItem) != 0)
            otherItem.m_prevItem->m_nextItem = &firstItem;
        else m_firstItem = &firstItem;

        lastItem.m_nextItem = &otherItem;
        otherItem.m_prevItem = &lastItem;
        return memberItem;
    }
    virtual TItem* InsertItemsAfter
    (TItem& otherItem, TItem& firstItem, TItem& lastItem) {
        TItem* memberItem = &otherItem;
        if ((lastItem.m_nextItem = otherItem.m_nextItem) != 0)
            otherItem.m_nextItem->m_prevItem = &lastItem;
        else m_lastItem = &lastItem;

        firstItem.m_prevItem = &otherItem;
        otherItem.m_nextItem = &firstItem;
        return memberItem;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual TItem* DeleteItems(TItem& firstItem, TItem& lastItem) {
        TItem* memberItem = &firstItem;
		if (lastItem.m_nextItem)
			lastItem.m_nextItem->m_prevItem = firstItem.m_prevItem;
		else m_lastItem = firstItem.m_prevItem;

		if (firstItem.m_prevItem)
			firstItem.m_prevItem->m_nextItem = lastItem.m_nextItem;
		else m_firstItem = lastItem.m_nextItem;

		lastItem.m_nextItem = 0;
		firstItem.m_prevItem = 0;
        return memberItem;
    }
    virtual TItem* DeleteAllItems() {
        TItem* memberItem = m_firstItem;
        m_firstItem = m_lastItem = 0;
        return memberItem;
    }
    virtual void ClearItems() {
        DeleteAllItems();
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual TItem* SetFirstItem(TItem* toItem) {
        m_firstItem = toItem;
        return m_firstItem;
    }
    virtual TItem* GetFirstItem() const {
        return m_firstItem;
    }
    virtual TItem* SetLastItem(TItem* toItem) {
        m_lastItem = toItem;
        return m_lastItem;
    }
    virtual TItem* GetLastItem() const {
        return m_lastItem;
    }
