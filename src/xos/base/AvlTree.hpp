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
///   File: AvlTree.hpp
///
/// Author: $author$
///   Date: 1/21/2014
///////////////////////////////////////////////////////////////////////
#if !defined(_XOS_AVLTREE_HPP) || defined(_XOS_AVLTREE_MEMBERS_ONLY)
#if !defined(_XOS_AVLTREE_HPP) && !defined(_XOS_AVLTREE_MEMBERS_ONLY)
#define _XOS_AVLTREE_HPP
#endif // !defined(_XOS_AVLTREE_HPP) && !defined(_XOS_AVLTREE_MEMBERS_ONLY)

#if !defined(_XOS_AVLTREE_MEMBERS_ONLY)
#include "xos/base/AvlBranch.hpp"
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

class AvlTree
: virtual public TImplement,
  public Tree<TLeaf,TBranch,TDerive,TExtend,TImplement> {
#else // !defined(_XOS_AVLTREE_MEMBERS_ONLY)
#endif // !defined(_XOS_AVLTREE_MEMBERS_ONLY)
public:
    typedef TImplement Implements;
    typedef Tree<TLeaf,TBranch,TDerive,TExtend,TImplement> Extends;
    typedef TDerive Derives;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    AvlTree(TBranch *root=0): Extends(root) {
    }
    AvlTree(const AvlTree& copy): Extends(copy) {
    }
    virtual ~AvlTree() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    TBranch *Insert(TBranch *branch) {
        branch->m_leftBranch=0;
        branch->m_rightBranch=0;
        return this->m_root=Inserted(this->m_root,branch);
    }
    TBranch *Delete(TBranch *branch) {
        return this->m_root=Deleted(this->m_root,branch);
    }
protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    TBranch *Inserted(TBranch *tree,TBranch *branch) {
        if (tree==0)
            return branch;

        if (branch!=0)
        if (branch->Compare(*tree)<0)
        {
            tree->m_leftBranch=Inserted(tree->m_leftBranch,branch);
            tree->m_leftBranch->m_tree=tree;
            if (Depth(tree->m_leftBranch)-Depth(tree->m_rightBranch)>1)
            {
                if (Depth(tree->m_leftBranch->m_rightBranch)
                    >Depth(tree->m_leftBranch->m_leftBranch))
                    tree->m_leftBranch=Left(tree->m_leftBranch);
                return Right(tree);
            }
            else tree->m_depth=tree->m_leftBranch->m_depth+1;
        }
        else
        {
            tree->m_rightBranch=Inserted(tree->m_rightBranch,branch);
            tree->m_rightBranch->m_tree=tree;
            if (Depth(tree->m_rightBranch)-Depth(tree->m_leftBranch)>1)
            {
                if (Depth(tree->m_rightBranch->m_leftBranch)
                    >Depth(tree->m_rightBranch->m_rightBranch))
                    tree->m_rightBranch=Right(tree->m_rightBranch);
                return Left(tree);
            }
            else tree->m_depth=tree->m_rightBranch->m_depth+1;
        }

        return tree;
    }
    TBranch *Deleted(TBranch *tree,TBranch *branch) {
        int c;

        if ((tree==0)||(branch==0))
            return tree;

        if ((c=branch->Compare(*tree))>0)
        {
            tree->m_rightBranch=Deleted(tree->m_rightBranch,branch);
            if (Depth(tree->m_leftBranch)-Depth(tree->m_rightBranch)>1)
            {
                if (Depth(tree->m_leftBranch->m_rightBranch)
                    >Depth(tree->m_leftBranch->m_leftBranch))
                    tree->m_leftBranch=Left(tree->m_leftBranch);
                tree=Right(tree);
            }
            else tree->m_depth=NewDepth(tree);
        }
        else if (c<0)
        {
            tree->m_leftBranch=Deleted(tree->m_leftBranch,branch);
            if (Depth(tree->m_rightBranch)-Depth(tree->m_leftBranch)>1)
            {
                if (Depth(tree->m_rightBranch->m_leftBranch)
                    >Depth(tree->m_rightBranch->m_rightBranch))
                    tree->m_rightBranch=Right(tree->m_rightBranch);
                tree=Left(tree);
            }
            else tree->m_depth=NewDepth(tree);
        }
        else if (branch->m_depth>1)
        {
            if (Depth(branch->m_rightBranch)>Depth(branch->m_leftBranch))
                tree=Least(&branch->m_rightBranch);
            else tree=Greatest(&branch->m_leftBranch);
            tree->m_depth=NewDepth(branch);
            if ((tree->m_leftBranch=branch->m_leftBranch)!=0)
                tree->m_leftBranch->m_tree=tree;
            if ((tree->m_rightBranch=branch->m_rightBranch)!=0)
                tree->m_rightBranch->m_tree=tree;
        }
        else tree=0;

        return tree;
    }
    ///////////////////////////////////////////////////////////////////////
    TBranch *Least(TBranch **tree) {
        TBranch *t;

        if ((*tree)->m_leftBranch!=0)
        {
            t=Least(&(*tree)->m_leftBranch);
            if (Depth((*tree)->m_rightBranch)-Depth((*tree)->m_leftBranch)>1)
            {
                if (Depth((*tree)->m_rightBranch->m_leftBranch)
                    >Depth((*tree)->m_rightBranch->m_rightBranch))
                    (*tree)->m_rightBranch=Right((*tree)->m_rightBranch);
                *tree=Left(*tree);
            }
            else (*tree)->m_depth=NewDepth(*tree);
        }
        else if ((*tree)->m_rightBranch!=0)
        {
            t=*tree;
            *tree=t->m_rightBranch;
        }
        else
        {
            t=*tree;
            *tree=0;
        }

        return t;
    }
    TBranch *Greatest(TBranch **tree) {
        TBranch *t;

        if ((*tree)->m_rightBranch!=0)
        {
            t=Greatest(&(*tree)->m_rightBranch);
            if (Depth((*tree)->m_leftBranch)-Depth((*tree)->m_rightBranch)>1)
            {
                if (Depth((*tree)->m_leftBranch->m_rightBranch)
                    >Depth((*tree)->m_leftBranch->m_leftBranch))
                    (*tree)->m_leftBranch=Left((*tree)->m_leftBranch);
                *tree=Right(*tree);
            }
            else (*tree)->m_depth=NewDepth(*tree);
        }
        else if ((*tree)->m_leftBranch!=0)
        {
            t=*tree;
            *tree=t->m_leftBranch;
        }
        else
        {
            t=*tree;
            *tree=0;
        }

        return t;
    }
    ///////////////////////////////////////////////////////////////////////
    TBranch *Left(TBranch *tree) {
        TBranch *rightBranch;

        if (tree)
        if ((rightBranch=tree->m_rightBranch))
        {
            if ((tree->m_rightBranch=rightBranch->m_leftBranch))
                tree->m_rightBranch->m_tree=tree;

            tree->m_depth=Depth(tree->m_leftBranch)+1;

            if (Depth(tree->m_rightBranch)>=tree->m_depth)
                tree->m_depth=tree->m_rightBranch->m_depth+1;

            rightBranch->m_depth=tree->m_depth+1;
            rightBranch->m_leftBranch=tree;
            rightBranch->m_tree=tree->m_tree;
            tree->m_tree=rightBranch;

            return rightBranch;
        }

        return 0;
    }
    TBranch *Right(TBranch *tree) {
        TBranch *leftBranch;

        if (tree)
        if ((leftBranch=tree->m_leftBranch))
        {
            if ((tree->m_leftBranch=leftBranch->m_rightBranch))
                tree->m_leftBranch->m_tree=tree;

            tree->m_depth=Depth(tree->m_rightBranch)+1;

            if (Depth(tree->m_leftBranch)>=tree->m_depth)
                tree->m_depth=tree->m_leftBranch->m_depth+1;

            leftBranch->m_depth=tree->m_depth+1;
            leftBranch->m_rightBranch=tree;
            leftBranch->m_tree=tree->m_tree;
            tree->m_tree=leftBranch;

            return leftBranch;
        }

        return 0;
    }
    ///////////////////////////////////////////////////////////////////////
    int NewDepth(TBranch *tree) {
        int ld,gd;

        if (tree!=0)
        if ((ld=Depth(tree->m_leftBranch))
            >(gd=Depth(tree->m_rightBranch)))
            return ld+1;
        else return gd+1;

        return 0;
    }
    int Depth(TBranch *tree) const {
        if (tree)
        if (tree->m_depth>0)
            return tree->m_depth;
        else return 1;

        return 0;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
#if !defined(_XOS_AVLTREE_MEMBERS_ONLY)
};

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
template
<class TLeaf,
 class TBranch,
 class TDerive,
 class TExtend = ExportBase,
 class TImplement = InterfaceBase>

class _EXPORT_CLASS ExportAvlTree
: virtual public TImplement,
  public ExportTree<TLeaf,TBranch,TDerive,TExtend,TImplement> {
#define _XOS_AVLTREE_MEMBERS_ONLY
#define AvlTree ExportAvlTree
#define Tree ExportTree
#include "xos/base/AvlTree.hpp"
#undef Tree
#undef AvlTree
#undef _XOS_AVLTREE_MEMBERS_ONLY
};

} // namespace xos

#else // !defined(_XOS_AVLTREE_MEMBERS_ONLY)
#endif // !defined(_XOS_AVLTREE_MEMBERS_ONLY)

#endif // !defined(_XOS_AVLTREE_HPP) || defined(_XOS_AVLTREE_MEMBERS_ONLY)
