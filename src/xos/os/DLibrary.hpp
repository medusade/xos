///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2012 $organization$
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
///   File: DLibrary.hpp
///
/// Author: $author$
///   Date: 10/24/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_OS_DLIBRARY_HPP
#define _XOS_OS_DLIBRARY_HPP

#include "xos/base/String.hpp"

namespace xos {

typedef InterfaceBase DLibraryImplement;
///////////////////////////////////////////////////////////////////////
///  Class: DLibrary
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS DLibrary: virtual public DLibraryImplement {
public:
    typedef DLibraryImplement Implements;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Open(const std::string& fileName, bool resolve=true, bool global=false) {
        return Open(fileName.c_str(), resolve, global);
    }
    virtual bool Open(const wchar_t* fileName, bool resolve=true, bool global=false) {
        if ((fileName)) {
            String s(fileName);
            return Open(s.c_str(), resolve, global);
        }
        return false;
    }
    virtual bool Open(const char* fileName, bool resolve=true, bool global=false) {
        return false;
    }
    virtual bool Close() {
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void* GetAddress(const std::string& symbol) const {
        return GetAddress(symbol.c_str());
    }
    virtual void* GetAddress(const wchar_t* symbol) const {
        if ((symbol)) {
            String s(symbol);
            return GetAddress(s.c_str());
        }
        return 0;
    }
    virtual void* GetAddress(const char* symbol) const {
        return 0;
    }
};

} // namespace xos 

#endif // _XOS_OS_DLIBRARY_HPP 
