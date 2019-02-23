///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2016 $organization$
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
///   File: DLibraryMain.hpp
///
/// Author: $author$
///   Date: 10/5/2016
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_OS_DLIBRARYMAIN_HPP
#define _XOS_OS_DLIBRARYMAIN_HPP

#include "xos/os/os/DLibrarySymbol.hpp"

namespace xos {

typedef ImplementBase DLibraryMainImplements;
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS DLibraryMain: virtual public DLibraryMainImplements {
public:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Init() { return true; }
    virtual bool Fini() { return true; }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    static DLibraryMain* GetTheDLibraryMain() {
        return TheDLibraryMain();
    }
protected:
    static DLibraryMain*& TheDLibraryMain() {
        static DLibraryMain* theDLibraryMain = 0;
        return theDLibraryMain;
    }
};

typedef DLibraryMain DLibraryMainExtendImplements;
typedef ExportBase DLibraryMainExtendExtends;
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS DLibraryMainExtend:
virtual public DLibraryMainExtendImplements, public DLibraryMainExtendExtends {
public:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    DLibraryMainExtend() {
        DLibraryMain*& theDLibraryMain = TheDLibraryMain();
        if (!(theDLibraryMain)) {
            theDLibraryMain = this;
        }
    }
    virtual ~DLibraryMainExtend() {
        DLibraryMain*& theDLibraryMain = TheDLibraryMain();
        if (this == (theDLibraryMain)) {
            theDLibraryMain = 0;
        }
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace xos

#endif // _XOS_OS_DLIBRARYMAIN_HPP 
