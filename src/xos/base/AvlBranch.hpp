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
///   File: AvlBranch.hpp
///
/// Author: $author$
///   Date: 1/21/2014
///////////////////////////////////////////////////////////////////////
#if !defined(_XOS_AVLBRANCH_HPP) || defined(_XOS_AVLBRANCH_MEMBERS_ONLY)
#if !defined(_XOS_AVLBRANCH_HPP) && !defined(_XOS_AVLBRANCH_MEMBERS_ONLY)
#define _XOS_AVLBRANCH_HPP
#endif // !defined(_XOS_AVLBRANCH_HPP) && !defined(_XOS_AVLBRANCH_MEMBERS_ONLY)

#if !defined(_XOS_AVLBRANCH_MEMBERS_ONLY)
#include "xos/base/Branch.hpp"

namespace xos {

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
template
<class TLeaf,
 class TDerives,
 class TExtend = Base,
 class TImplement = ImplementBase>

class AvlBranch
: virtual public TImplement,
  public Branch<TLeaf, TDerives, TExtend, TImplement> {
#else // !defined(_XOS_AVLBRANCH_MEMBERS_ONLY)
#endif // !defined(_XOS_AVLBRANCH_MEMBERS_ONLY)
public:
    typedef TImplement Implements;
    typedef Branch<TLeaf, TDerives, TExtend, TImplement> Extends;
    typedef TDerives Derives;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    AvlBranch
    (int depth=1, TDerives *tree=0,
     TDerives *leftBranch=0, TDerives *rightBranch=0)
    : Extends(tree,leftBranch,rightBranch),
      m_depth(depth) {
    }
    AvlBranch(const AvlBranch& copy): Extends(copy) {
    }
    virtual ~AvlBranch() {
    }
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
protected:
    int m_depth;
#if !defined(_XOS_AVLBRANCH_MEMBERS_ONLY)
};

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
template
<class TLeaf,
 class TDerives,
 class TExtend = ExportBase,
 class TImplement = InterfaceBase>

class _EXPORT_CLASS ExportAvlBranch
: virtual public TImplement,
  public ExportBranch<TLeaf, TDerives, TExtend, TImplement> {
#define _XOS_AVLBRANCH_MEMBERS_ONLY
#define AvlBranch ExportAvlBranch
#define Branch ExportBranch
#include "xos/base/AvlBranch.hpp"
#undef Branch
#undef AvlBranch
#undef _XOS_AVLBRANCH_MEMBERS_ONLY
};

} // namespace xos

#else // !defined(_XOS_AVLBRANCH_MEMBERS_ONLY)
#endif // !defined(_XOS_AVLBRANCH_MEMBERS_ONLY)

#endif // !defined(_XOS_AVLBRANCH_HPP) || defined(_XOS_AVLBRANCH_MEMBERS_ONLY)
