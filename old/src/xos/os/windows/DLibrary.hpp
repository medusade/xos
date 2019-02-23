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
#ifndef _XOS_OS_WINDOWS_DLIBRARY_HPP
#define _XOS_OS_WINDOWS_DLIBRARY_HPP

#include "xos/os/os/DLibrarySymbol.hpp"
#include "xos/os/DLibrary.hpp"
#include "xos/os/Logger.hpp"
#include "xos/base/Opened.hpp"
#include "xos/base/Attached.hpp"

namespace xos {
namespace windows {

typedef DLibraryImplement DLibraryImplementImplement;

typedef AttachedImplement
<DLIBRARY_T, INVALID_DLIBRARY_T, INVALID_DLIBRARY, 
 DLibraryImplementImplement> DLibraryImplement;

typedef Attached
<DLIBRARY_T, INVALID_DLIBRARY_T, INVALID_DLIBRARY, 
 ExportBase, DLibraryImplement> DLibraryAttached;

typedef Opened
<DLIBRARY_T, INVALID_DLIBRARY_T, INVALID_DLIBRARY, 
 DLibraryAttached, DLibraryImplement> DLibraryExtend;
///////////////////////////////////////////////////////////////////////
///  Class: DLibrary
///
/// Author: $author$
///   Date: 8/14/2013
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS DLibrary: virtual public DLibraryImplement, public DLibraryExtend {
public:
    typedef DLibraryImplement Implements;
    typedef DLibraryExtend Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    DLibrary
    (DLIBRARY_T attachedTo = INVALID_DLIBRARY, bool isOpen = false)
    : Extends(attachedTo, isOpen) {
    }
    virtual ~DLibrary() {
        if (!(Closed())) {
            Error error = Error::Failed;
            XOS_LOG_ERROR("failed on Closed()");
            throw(error);
        }
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Open(const wchar_t* fileName, bool resolve=true, bool global=false) {
        if ((Closed())) {
            if ((fileName)) {
                TPathT<wchar_t> path(fileName);
                const tchar_t* chars;
                if ((path.length()) && (chars = path.c_str())) {
                    AttachedT detached;
                    if (INVALID_DLIBRARY != (detached = LoadLibrary(chars))) {
                        AttachOpened(detached);
                        return true;
                    } else { 
                        String cFileName(fileName);
                        XOS_LOG_ERROR("failed on LoadLibrary(\"" << cFileName.c_str() << "\")"); 
                    }
                }
            }
        }
        return false;
    }
    virtual bool Open(const char* fileName, bool resolve=true, bool global=false) {
        if ((Closed())) {
            if ((fileName)) {
                TPathT<char> path(fileName);
                const tchar_t* chars;
                if ((path.length()) && (chars = path.c_str())) {
                    AttachedT detached;
                    if (INVALID_DLIBRARY != (detached = LoadLibrary(chars))) {
                        AttachOpened(detached);
                        return true;
                    } else { XOS_LOG_ERROR("failed on LoadLibrary(\"" << fileName << "\")"); }
                }
            }
        }
        return false;
    }
    virtual bool Close() {
        bool success = false;
        AttachedT detached;
        if (INVALID_DLIBRARY != (detached = Detach())) {
            if (!(success = (FALSE != (FreeLibrary(detached)))))
            {   XOS_LOG_ERROR("failed on FreeLibrary()"); }
            detached = INVALID_DLIBRARY;
        }
        return success;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void* GetAddress(const char* symbol) const {
        AttachedT attachedTo;
        if ((attachedTo = AttachedTo()) && symbol) {
            void* address = GetProcAddress(attachedTo, symbol);
            return address;
        }
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    template <typename TChar>
    class TPathT: public TString {
    public:
        typedef TString Extends;
        TPathT(const TChar* chars) {
            if ((chars)) {
                for (TChar c; (c=*chars); chars++) {
                    if (c == (TChar)('/')) c = (TChar)('\\');
                    this->Append(&c, 1);
                }
            }
        }
    };
};

} // namespace windows 
} // namespace xos 

#endif // _XOS_OS_WINDOWS_DLIBRARY_HPP 
