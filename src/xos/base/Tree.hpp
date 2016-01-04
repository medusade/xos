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
///   File: Tree.hpp
///
/// Author: $author$
///   Date: 1/21/2014
///////////////////////////////////////////////////////////////////////
#if !defined(_XOS_TREE_HPP) || defined(_XOS_TREE_MEMBERS_ONLY)
#if !defined(_XOS_TREE_HPP) && !defined(_XOS_TREE_MEMBERS_ONLY)
#define _XOS_TREE_HPP
#endif // !defined(_XOS_TREE_HPP) && !defined(_XOS_TREE_MEMBERS_ONLY)

#if !defined(_XOS_TREE_MEMBERS_ONLY)
#include "xos/base/Branch.hpp"

#if !defined(_XOS_TREE_MEMBERS_EXPORT)
#define _XOS_TREE_MEMBERS_EXPORT
#endif // !defined(_XOS_TREE_MEMBERS_EXPORT)

namespace xos {

namespace tree {
template<typename TBranch, class TExtend>
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _XOS_TREE_MEMBERS_EXPORT iterator: public TExtend {
public:
    typedef TExtend Extends;
    iterator(TBranch* p): m_p(p) {}
    iterator(const iterator& copy): m_p(copy.m_p) {}
    bool operator !=(const iterator& to) const { return m_p != to.m_p; }
    bool operator ==(const iterator& to) const { return m_p == to.m_p; }
    TBranch& operator *() const { return m_p; }
    TBranch* operator ->() const { return m_p; }
    iterator& operator ++() { m_p = m_p->GetNext(); return *this; }
    iterator& operator --() { m_p = m_p->GetPrevious(); return *this; }
    iterator& operator =(const TBranch* p) { m_p = p; return *this; }
protected:
    TBranch* m_p;
};
} // namespace tree

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
template
<class TLeaf,
 class TBranch,
 class TTree,
 class TExtend = Base,
 class TImplement = ImplementBase,
 class TIteratorExtend = TExtend>

class Tree: virtual public TImplement, public TExtend {
#else // !defined(_XOS_TREE_MEMBERS_ONLY)
#endif // !defined(_XOS_TREE_MEMBERS_ONLY)
public:
    typedef TImplement Implements;
    typedef TExtend Extends;
    typedef TTree Derives;
    typedef tree::iterator<TBranch, TIteratorExtend> iterator;
    typedef tree::iterator<const TBranch, TIteratorExtend> const_iterator;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Tree(TBranch *root=0)
    : m_root(root) {
    }
    Tree(const Tree& copy)
    : m_root(copy.m_root) {
    }
    virtual ~Tree() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    void Clear() {
        m_root=0;
    }
    ///////////////////////////////////////////////////////////////////////
    void Insert(TBranch *branch) {
        TBranch *next, *tree;
        int unequal;

        if (!(next=GetRoot()))
            SetRoot(branch);

        else
        {
            do
            {
                tree=next;

                if ((unequal = branch->Compare(*tree)) < 0)
                {
                    if (!(next=tree->GetLeftBranch()))
                        tree->SetLeftBranch(branch);
                }
                else
                {
                    if (!(next=tree->GetRightBranch()))
                        tree->SetRightBranch(branch);
                }
            }
            while(next);

            branch->SetTree(tree);
        }
    }
    void Delete(TBranch *branch) {
        TBranch *next, *moved;

        if (!branch->GetLeftBranch() || !branch->GetRightBranch())
            moved = branch;

        else moved = GetNext(branch);

        if (!(next = moved->GetLeftBranch()))
            next = moved->GetRightBranch();

        if (next)
            next->SetTree(moved->GetTree());

        if (!moved->GetTree())
            SetRoot(next);

        else
        {
            if (moved == moved->GetTree()->GetLeftBranch())
                moved->GetTree()->SetLeftBranch(next);

            else moved->GetTree()->SetRightBranch(next);
        }

        if (moved != branch)
        {
            if ((next = moved->SetTree(branch->GetTree())))
                if (branch == next->GetRightBranch())
                    next->SetRightBranch(moved);
                else next->SetLeftBranch(moved);

            if ((next = moved->SetLeftBranch(branch->GetLeftBranch())))
                next->SetTree(moved);

            if ((next = moved->SetRightBranch(branch->GetRightBranch())))
                next->SetTree(moved);
        }
    }
    ///////////////////////////////////////////////////////////////////////
    TBranch *Find(const TLeaf &leaf, int length) const {
        TBranch *branch;
        int unequal;

        if ((branch=GetRoot()))
        do
        {
            if ((unequal = branch->Compare(leaf, length)) < 0)
                branch = branch->GetRightBranch();

            else if (unequal > 0)
                    branch = branch->GetLeftBranch();

            else break;
        }
        while(branch);

        return branch;
    }
    ///////////////////////////////////////////////////////////////////////
    TBranch *GetFirst() const {
        return GetFirstOf(GetRoot());
    }
    TBranch *GetLast() const {
        return GetLastOf(GetRoot());
    }
    ///////////////////////////////////////////////////////////////////////
    TBranch *GetNext(TBranch *branch) const {
        TBranch *tree;

        if ((tree=branch->GetRightBranch()))
            return GetFirstOf(tree);

        if ((tree = branch->GetTree()))
        do
        {
            if (branch != tree->GetRightBranch())
                break;

            branch = tree;
            tree = tree->GetTree();
        }
        while(tree);

        return tree;
    }
    TBranch *GetPrevious(TBranch *branch) const {
        TBranch *tree;

        if ((tree=branch->GetLeftBranch()))
            return GetLastOf(tree);

        if ((tree = branch->GetTree()))
        do
        {
            if (branch != tree->GetLeftBranch())
                break;

            branch = tree;
            tree = tree->GetTree();
        }
        while(tree);

        return tree;
    }
    ///////////////////////////////////////////////////////////////////////
    inline TBranch *SetRoot(TBranch *root) {
        return m_root=root;
    }
    inline TBranch *GetRoot() const {
        return m_root;
    }
protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    TBranch *GetFirstOf(TBranch *branch) const {
        TBranch *next;
        while ((next=branch->GetLeftBranch()))
            branch=next;
        return branch;
    }
    TBranch *GetLastOf(TBranch *branch) const {
        TBranch *next;
        while ((next=branch->GetRightBranch()))
            branch=next;
        return branch;
    }

    TBranch *GetLeftOf(TBranch *branch) const {
        if (branch)
            return branch->GetLeftBranch();
        return 0;
    }
    TBranch *GetRightOf(TBranch *branch) const {
        if (branch)
            return branch->GetRightBranch();
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    TBranch *m_root;
#if !defined(_XOS_TREE_MEMBERS_ONLY)
};

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
template
<class TLeaf,
 class TBranch,
 class TTree,
 class TExtend = ExportBase,
 class TImplement = InterfaceBase,
 class TIteratorExtend = TExtend>

class _EXPORT_CLASS ExportTree: virtual public TImplement, public TExtend {
#define _XOS_TREE_MEMBERS_ONLY
#define Tree ExportTree
#include "xos/base/Tree.hpp"
#undef Tree
#undef _XOS_TREE_MEMBERS_ONLY
};

} // namespace xos

#else // !defined(_XOS_TREE_MEMBERS_ONLY)
#endif // !defined(_XOS_TREE_MEMBERS_ONLY)

#endif // !defined(_XOS_TREE_HPP) || defined(_XOS_TREE_MEMBERS_ONLY)
