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
///   File: Branch.hpp
///
/// Author: $author$
///   Date: 1/21/2014
///////////////////////////////////////////////////////////////////////
#if !defined(_XOS_BRANCH_HPP) || defined(_XOS_BRANCH_MEMBERS_ONLY)
#if !defined(_XOS_BRANCH_HPP) && !defined(_XOS_BRANCH_MEMBERS_ONLY)
#define _XOS_BRANCH_HPP
#endif // !defined(_XOS_BRANCH_HPP) && !defined(_XOS_BRANCH_MEMBERS_ONLY)

#if !defined(_XOS_BRANCH_MEMBERS_ONLY)
#include "xos/base/Base.hpp"

namespace xos {

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
template
<class TLeaf,
 class TDerives,
 class TExtend = Base,
 class TImplement = ImplementBase>

class Branch: virtual public TImplement, public TExtend {
#else // !defined(_XOS_BRANCH_MEMBERS_ONLY)
#endif // !defined(_XOS_BRANCH_MEMBERS_ONLY)
public:
    typedef TImplement Implements;
    typedef TExtend Extends;
    typedef TDerives Derives;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Branch
    (TDerives *tree=0, TDerives *leftBranch=0, TDerives *rightBranch=0)
    : m_tree(tree),
      m_leftBranch(leftBranch),
      m_rightBranch(rightBranch) {
    }
    Branch(const Branch& copy)
    : m_tree(copy.m_tree),
      m_leftBranch(copy.m_leftBranch),
      m_rightBranch(copy.m_rightBranch) {
    }
    virtual ~Branch() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int Compare(const TDerives& toBranch) const = 0;
    virtual int Compare(const TLeaf& toLeaf) const = 0;
    virtual int Compare(const TLeaf& toLeaf, int length) const = 0;

    inline TDerives *SetTree(TDerives *tree) {
        return m_tree = tree;
    }
    inline TDerives *GetTree() const {
        return m_tree;
    }

    inline TDerives *SetLeftBranch(TDerives *leftBranch) {
        return m_leftBranch=leftBranch;
    }
    inline TDerives *GetLeftBranch() const {
        return m_leftBranch;
    }

    inline TDerives *SetRightBranch(TDerives *rightBranch) {
        return m_rightBranch=rightBranch;
    }
    inline TDerives *GetRightBranch() const {
        return m_rightBranch;
    }
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
protected:
    TDerives *m_tree, *m_leftBranch, *m_rightBranch;
#if !defined(_XOS_BRANCH_MEMBERS_ONLY)
};

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
template
<class TLeaf,
 class TDerives,
 class TExtend = ExportBase,
 class TImplement = InterfaceBase>

class _EXPORT_CLASS ExportBranch: virtual public TImplement, public TExtend {
#define _XOS_BRANCH_MEMBERS_ONLY
#define Branch ExportBranch
#include "xos/base/Branch.hpp"
#undef Branch
#undef _XOS_BRANCH_MEMBERS_ONLY
};

} // namespace xos

#else // !defined(_XOS_BRANCH_MEMBERS_ONLY)
#endif // !defined(_XOS_BRANCH_MEMBERS_ONLY)

#endif // !defined(_XOS_BRANCH_HPP) || defined(_XOS_BRANCH_MEMBERS_ONLY)
