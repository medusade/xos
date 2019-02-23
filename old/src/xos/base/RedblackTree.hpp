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
///   File: RedblackTree.hpp
///
/// Author: $author$
///   Date: 1/21/2014
///////////////////////////////////////////////////////////////////////
#if !defined(_XOS_REDBLACKTREE_HPP) || defined(_XOS_REDBLACKTREE_MEMBERS_ONLY)
#if !defined(_XOS_REDBLACKTREE_HPP) && !defined(_XOS_REDBLACKTREE_MEMBERS_ONLY)
#define _XOS_REDBLACKTREE_HPP
#endif // !defined(_XOS_REDBLACKTREE_HPP) && !defined(_XOS_REDBLACKTREE_MEMBERS_ONLY)

#if !defined(_XOS_REDBLACKTREE_MEMBERS_ONLY)
#include "xos/base/RedblackBranch.hpp"
#include "xos/base/Tree.hpp"

namespace xos {

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
template
<class TLeaf,
 class TBranch,
 class TDerive,
 class TExtend = Base,
 class TImplement = ImplementBase>

class RedblackTree
: virtual public TImplement,
  public Tree<TLeaf,TBranch,TDerive,TExtend,TImplement> {
#else // !defined(_XOS_REDBLACKTREE_MEMBERS_ONLY)
#endif // !defined(_XOS_REDBLACKTREE_MEMBERS_ONLY)
public:
    typedef TImplement Implements;
    typedef Tree<TLeaf,TBranch,TDerive,TExtend,TImplement> Extends;
    typedef TDerive Derives;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    RedblackTree(TBranch *root=0): Extends(root) {
    }
    RedblackTree(const RedblackTree& copy): Extends(copy) {
    }
    virtual ~RedblackTree() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    void Insert(TBranch *branch) {
        TBranch *tree;

        Extends::Insert(branch);

        branch->SetIsRed();

        while ((branch != this->GetRoot())
               && (GetIsRed(branch->GetTree())))
        {
            if (branch->GetTree()
                == branch->GetTree()->GetTree()->GetLeftBranch())
             {
                tree = branch->GetTree()->GetTree()->GetRightBranch();

                if (GetIsRed(tree))
                {
                    tree->SetIsRed(false);
                    branch->GetTree()->SetIsRed(false);
                    branch->GetTree()->GetTree()->SetIsRed();
                    branch = branch->GetTree()->GetTree();
                }
                else
                {
                    if (branch == branch->GetTree()->GetRightBranch())
                    {
                        branch = branch->GetTree();
                        RotateLeft(branch);
                    }

                    branch->GetTree()->SetIsRed(false);
                    branch->GetTree()->GetTree()->SetIsRed();
                    RotateRight(branch->GetTree()->GetTree());
                }
            }
            else
            {
                tree = branch->GetTree()->GetTree()->GetLeftBranch();

                if (GetIsRed(tree))
                {
                    tree->SetIsRed(false);
                    branch->GetTree()->SetIsRed(false);
                    branch->GetTree()->GetTree()->SetIsRed();
                    branch = branch->GetTree()->GetTree();
                }
                else
                {
                    if (branch == branch->GetTree()->GetLeftBranch())
                    {
                        branch = branch->GetTree();
                        RotateRight(branch);
                    }

                    branch->GetTree()->SetIsRed(false);
                    branch->GetTree()->GetTree()->SetIsRed();
                    RotateLeft(branch->GetTree()->GetTree());
                }
            }
        }

        this->GetRoot()->SetIsRed(false);
    }
    void Delete(TBranch *branch) {
        TBranch *next, *moved, *child;

        if (!branch->GetLeftBranch() || !branch->GetRightBranch())
            moved = branch;

        else moved = GetNext(branch);

        if (!(child = moved->GetLeftBranch()))
            child = moved->GetRightBranch();

        if (!moved->GetTree())
            SetRoot(child);

        else
        {
            if (moved == moved->GetTree()->GetLeftBranch())
                moved->GetTree()->SetLeftBranch(child);

            else moved->GetTree()->SetRightBranch(child);
        }

        if (child)
            child->SetTree(moved->GetTree());

        else child = moved->GetTree();

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

            moved->SetIsRed(branch->GetIsRed());
        }

        if (child)
        {
            while ((child != this->GetRoot()) && (!child->GetIsRed()))
            {
                if (child->GetTree()->GetLeftBranch() == child)
                {
                    next = child->GetTree()->GetRightBranch();

                    if (GetIsRed(next))
                    {
                        next->SetIsRed(false);
                        child->GetTree()->SetIsRed();
                        RotateLeft(child->GetTree());
                        next = child->GetTree()->GetRightBranch();
                    }

                    if (!next)
                        child = child->GetTree();

                    else if ((!GetIsRed(next->GetLeftBranch()))
                             && (!GetIsRed(next->GetRightBranch())))
                    {
                        next->SetIsRed();
                        child = child->GetTree();
                    }
                    else
                    {
                        if (!GetIsRed(next->GetRightBranch()))
                        {
                            SetIsRed(next->GetLeftBranch(),false);
                            next->SetIsRed();
                            RotateRight(next);
                            next = child->GetTree()->GetRightBranch();
                        }

                        next->SetIsRed(child->GetTree()->GetIsRed());
                        SetIsRed(next->GetRightBranch(),false);
                        child->GetTree()->SetIsRed(false);
                        RotateLeft(child->GetTree());
                        child = this->GetRoot();
                    }
                }
                else
                {
                    next = child->GetTree()->GetLeftBranch();

                    if (GetIsRed(next))
                    {
                        next->SetIsRed(false);
                        child->GetTree()->SetIsRed();
                        RotateRight(child->GetTree());
                        next = child->GetTree()->GetLeftBranch();
                    }

                    if (!next)
                        child = child->GetTree();

                    else if ((!GetIsRed(next->GetRightBranch()))
                             && (!GetIsRed(next->GetLeftBranch())))
                    {
                        next->SetIsRed();
                        child = child->GetTree();
                    }
                    else
                    {
                        if (!GetIsRed(next->GetLeftBranch()))
                        {
                            SetIsRed(next->GetRightBranch(),false);
                            next->SetIsRed();
                            RotateLeft(next);
                            next = child->GetTree()->GetLeftBranch();
                        }

                        next->SetIsRed(child->GetTree()->GetIsRed());
                        SetIsRed(next->GetLeftBranch(),false);
                        child->GetTree()->SetIsRed(false);
                        RotateRight(child->GetTree());
                        child = this->GetRoot();
                    }
                }
            }

            child->SetIsRed(false);
        }
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    void RotateLeft(TBranch *branch) {
        TBranch *rightBranch = branch->GetRightBranch();

        branch->SetRightBranch(rightBranch->GetLeftBranch());

        if (rightBranch->GetLeftBranch())
            rightBranch->GetLeftBranch()->SetTree(branch);

        rightBranch->SetTree(branch->GetTree());

        if (!branch->GetTree())
            SetRoot(rightBranch);
        else
        {
            if (branch == branch->GetTree()->GetLeftBranch())
                branch->GetTree()->SetLeftBranch(rightBranch);
            else
                branch->GetTree()->SetRightBranch(rightBranch);
        }

        rightBranch->SetLeftBranch(branch);
        branch->SetTree(rightBranch);
    }
    void RotateRight(TBranch *branch) {
        TBranch *leftBranch = branch->GetLeftBranch();

        branch->SetLeftBranch(leftBranch->GetRightBranch());

        if (leftBranch->GetRightBranch())
            leftBranch->GetRightBranch()->SetTree(branch);

        leftBranch->SetTree(branch->GetTree());

        if (!branch->GetTree())
            SetRoot(leftBranch);
        else
        {
            if (branch == branch->GetTree()->GetRightBranch())
                branch->GetTree()->SetRightBranch(leftBranch);
            else
                branch->GetTree()->SetLeftBranch(leftBranch);
        }

        leftBranch->SetRightBranch(branch);
        branch->SetTree(leftBranch);
    }
    ///////////////////////////////////////////////////////////////////////
    bool SetIsRed(TBranch *branch,bool isRed=true) {
        if (branch)
            return branch->SetIsRed(isRed);
        return false;
    }
    bool GetIsRed(TBranch *branch) const {
        if (branch)
            return branch->GetIsRed();
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
#if !defined(_XOS_REDBLACKTREE_MEMBERS_ONLY)
};

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
template
<class TLeaf,
 class TBranch,
 class TDerive,
 class TExtend = ExportBase,
 class TImplement = InterfaceBase>

class ExportRedblackTree
: virtual public TImplement,
  public ExportTree<TLeaf,TBranch,TDerive,TExtend,TImplement> {
#define _XOS_REDBLACKTREE_MEMBERS_ONLY
#define RedblackTree ExportRedblackTree
#define Tree ExportTree
#include "xos/base/RedblackTree.hpp"
#undef Tree
#undef RedblackTree
#undef _XOS_REDBLACKTREE_MEMBERS_ONLY
};

} // namespace xos

#else // !defined(_XOS_REDBLACKTREE_MEMBERS_ONLY)
#endif // !defined(_XOS_REDBLACKTREE_MEMBERS_ONLY)

#endif // !defined(_XOS_REDBLACKTREE_HPP) || defined(_XOS_REDBLACKTREE_MEMBERS_ONLY)
