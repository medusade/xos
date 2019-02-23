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
///   File: RedblackBranch.hpp
///
/// Author: $author$
///   Date: 1/21/2014
///////////////////////////////////////////////////////////////////////
#if !defined(_XOS_REDBLACKBRANCH_HPP) || defined(_XOS_REDBLACKBRANCH_MEMBERS_ONLY)
#if !defined(_XOS_REDBLACKBRANCH_HPP) && !defined(_XOS_REDBLACKBRANCH_MEMBERS_ONLY)
#define _XOS_REDBLACKBRANCH_HPP
#endif // !defined(_XOS_REDBLACKBRANCH_HPP) && !defined(_XOS_REDBLACKBRANCH_MEMBERS_ONLY)

#if !defined(_XOS_REDBLACKBRANCH_MEMBERS_ONLY)
#include "xos/base/Branch.hpp"

namespace xos {

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
template
<class TLeaf,
 class TDerives,
 class TExtend = Base,
 class TImplement = ImplementBase>

class RedblackBranch
: virtual public TImplement,
  public Branch<TLeaf, TDerives, TExtend, TImplement> {
#else // !defined(_XOS_REDBLACKBRANCH_MEMBERS_ONLY)
#endif // !defined(_XOS_REDBLACKBRANCH_MEMBERS_ONLY)
public:
    typedef TImplement Implements;
    typedef Branch<TLeaf, TDerives, TExtend, TImplement> Extends;
    typedef TDerives Derives;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    RedblackBranch() {
    }
    RedblackBranch(const RedblackBranch& copy): Extends(copy) {
    }
    virtual ~RedblackBranch() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    inline bool SetIsRed(bool isRed=true) {
        return m_isRed=isRed;
    }
    inline bool GetIsRed() const {
        return m_isRed;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    bool m_isRed;
#if !defined(_XOS_REDBLACKBRANCH_MEMBERS_ONLY)
};

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
template
<class TLeaf,
 class TDerives,
 class TExtend = ExportBase,
 class TImplement = InterfaceBase>

class _EXPORT_CLASS ExportRedblackBranch
: virtual public TImplement,
  public Branch<TLeaf, TDerives, TExtend, TImplement> {
#define _XOS_REDBLACKBRANCH_MEMBERS_ONLY
#define RedblackBranch ExportRedblackBranch
#define Branch ExportBranch
#include "xos/base/RedblackBranch.hpp"
#undef Branch
#undef RedblackBranch
#undef _XOS_REDBLACKBRANCH_MEMBERS_ONLY
};

} // namespace xos

#else // !defined(_XOS_REDBLACKBRANCH_MEMBERS_ONLY)
#endif // !defined(_XOS_REDBLACKBRANCH_MEMBERS_ONLY)

#endif // !defined(_XOS_REDBLACKBRANCH_HPP) || defined(_XOS_REDBLACKBRANCH_MEMBERS_ONLY)
        

